

#include "bmtree_helpers.h"

// ompi_coll_base_topo_build_tree
ompi_coll_tree_t* ompi_coll_base_topo_build_tree( int fanout, int rank, int num_procs, int root ) {

    int size, schild, sparent, shiftedrank, i;
    int level; /* location of my rank in the tree structure of size */
    int delta; /* number of nodes on my level */
    int slimit; /* total number of nodes on levels above me */
    ompi_coll_tree_t* tree;

    // OPAL_OUTPUT((ompi_coll_base_framework.framework_output, "coll:base:topo_build_tree Building fo %d rt %d", fanout, root));

    if (fanout<1) {
        // OPAL_OUTPUT((ompi_coll_base_framework.framework_output, "coll:base:topo_build_tree invalid fanout %d", fanout));
        return NULL;
    }
    if (fanout>MAXTREEFANOUT) {
        // OPAL_OUTPUT((ompi_coll_base_framework.framework_output,"coll:base:topo_build_tree invalid fanout %d bigger than max %d", fanout, MAXTREEFANOUT));
        return NULL;
    }

    /*
     * Get size and rank of the process in this communicator
     */
    size = num_procs;

    // tree = std::vector<int>();

    tree = (ompi_coll_tree_t*)malloc(COLL_TREE_SIZE(MAXTREEFANOUT));
    if (!tree) {
        // OPAL_OUTPUT((ompi_coll_base_framework.framework_output,"coll:base:topo_build_tree PANIC::out of memory"));
        return NULL;
    }

    tree->tree_root     = -1;
    tree->tree_nextsize = -1;

    /*
     * Set root
     */
    tree->tree_root = root;

    /*
     * Initialize tree
     */
    tree->tree_fanout   = fanout;
    tree->tree_bmtree   = 0;
    tree->tree_root     = root;
    tree->tree_prev     = -1;
    tree->tree_nextsize = 0;
    for( i = 0; i < fanout; i++ ) {
        tree->tree_next[i] = -1;
    }

    /* return if we have less than 2 processes */
    if( size < 2 ) {
        return tree;
    }

    /*
     * Shift all ranks by root, so that the algorithm can be
     * designed as if root would be always 0
     * shiftedrank should be used in calculating distances
     * and position in tree
     */
    shiftedrank = rank - root;
    if( shiftedrank < 0 ) {
        shiftedrank += size;
    }

    /* calculate my level */
    level = calculate_level( fanout, shiftedrank );
    delta = pown( fanout, level );

    /* find my children */
    for( i = 0; i < fanout; i++ ) {
        schild = shiftedrank + delta * (i+1);
        if( schild < size ) {
            tree->tree_next[i] = (schild+root)%size;
            tree->tree_nextsize = tree->tree_nextsize + 1;
        } else {
            break;
        }
    }

    /* find my parent */
    slimit = calculate_num_nodes_up_to_level( fanout, level );
    sparent = shiftedrank;
    if( sparent < fanout ) {
        sparent = 0;
    } else {
        while( sparent >= slimit ) {
            sparent -= delta/fanout;
        }
    }
    tree->tree_prev = (sparent+root)%size;

    return tree;
}

ompi_coll_tree_t* ompi_coll_base_topo_build_kmtree(int root, int rank, int num_procs, int radix)
{
    //OPAL_OUTPUT((ompi_coll_base_framework.framework_output,
    //             "coll:base:topo:build_kmtree root %d, radix %d", root, radix));
    int comm_size = num_procs;
    //int rank = rank;
    ompi_coll_tree_t* kmtree;
    /* nchilds <= (radix - 1) * \ceil(\log_{radix}(comm_size)) */
    int log_radix = 0;
    for (int i = 1; i < comm_size; i *= radix)
        log_radix++;
    int nchilds_max = (radix - 1) * log_radix;

    int vrank = (rank - root + comm_size) % comm_size;
    kmtree = (ompi_coll_tree_t*)malloc(COLL_TREE_SIZE(nchilds_max));
    if (NULL == kmtree) {
        // OPAL_OUTPUT((ompi_coll_base_framework.framework_output,
        //              "coll:base:topo:build_kmtree PANIC out of memory"));
        return NULL;
    }

    kmtree->tree_bmtree = 0;
    kmtree->tree_root = root;
    kmtree->tree_prev = 0;
    kmtree->tree_nextsize = 0;

    /* Setup parent */
    int mask = 0x1;
    while (mask < comm_size) {
        if (vrank % (radix * mask)) {
            kmtree->tree_prev = vrank / (radix * mask) * (radix * mask);
            kmtree->tree_prev = (kmtree->tree_prev + root) % comm_size;
            break;
        }
        mask *= radix;
    }

    /* Setup childs */
    mask /= radix;
    int nchilds = 0;
    while (mask > 0) {
        for (int r = 1; r < radix; r++) {
            int child = vrank + mask * r;
            if (child < comm_size) {
                child = (child + root) % comm_size;
                kmtree->tree_next[nchilds] = child;
                nchilds++;
            }
        }
        mask /= radix;
    }
    kmtree->tree_nextsize = nchilds;
    return kmtree;
}

static inline int opal_next_poweroftwo(int value)
{
    int power2;
    power2 = 1 << (8 * sizeof (int) - __builtin_clz(value));
    //for (power2 = 1; value > 0; value >>= 1, power2 <<= 1) /* empty */;

    return power2;
}
ompi_coll_tree_t*
ompi_coll_base_topo_build_bmtree( int root, int rank, int num_procs )
{
    int childs = 0, size, mask = 1, index, remote, i;
    ompi_coll_tree_t *bmtree;

    //OPAL_OUTPUT((ompi_coll_base_framework.framework_output,"coll:base:topo:build_bmtree rt %d", root));

    /*
     * Get size and rank of the process in this communicator
     */
    size = num_procs;
    //rank = num_procs;

    index = rank -root;

    bmtree = (ompi_coll_tree_t*)malloc(COLL_TREE_SIZE(MAXTREEFANOUT));
    if (!bmtree) {
        //       OPAL_OUTPUT((ompi_coll_base_framework.framework_output,"coll:base:topo:build_bmtree PANIC out of memory"));
        return NULL;
    }

    bmtree->tree_bmtree   = 1;

    bmtree->tree_root     = -1;
    bmtree->tree_nextsize = -1;
    for( i = 0;i < MAXTREEFANOUT; i++ ) {
        bmtree->tree_next[i] = -1;
    }

    if( index < 0 ) index += size;

    //mask = opal_next_poweroftwo(index);
    int u = 1;
    while (u <= index)
    {
        mask += 1;
        u *= 2;
    }
    mask = u;
    /* Now I can compute my father rank */
    if( root == rank ) {
        bmtree->tree_prev = root;
    } else {
        remote = (index ^ (mask >> 1)) + root;
        if( remote >= size ) remote -= size;
        bmtree->tree_prev = remote;
    }
    /* And now let's fill my childs */
    while( mask < size ) {
        remote = (index ^ mask);
        if( remote >= size ) break;
        remote += root;
        if( remote >= size ) remote -= size;
        if (childs==MAXTREEFANOUT) {
            //OPAL_OUTPUT((ompi_coll_base_framework.framework_output,"coll:base:topo:build_bmtree max fanout incorrect %d needed %d", MAXTREEFANOUT, childs));
            free(bmtree);
            return NULL;
        }
        bmtree->tree_next[childs] = remote;
        mask <<= 1;
        childs++;
    }
    bmtree->tree_nextsize = childs;
    bmtree->tree_root     = root;
    return bmtree;
}
