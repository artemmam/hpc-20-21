#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <x86intrin.h>

int n = 128;

void mat_mul_simple(float *a, float *b, float *c) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}

void mat_mul_avx(float *a, float *b, float *c) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j += 8) {
            __m256 m0 = _mm256_setzero_ps();
            for (int k = 0; k < n; k++) {
                __m256 m1 = _mm256_broadcast_ss(a + i * n + k);
                __m256 m2 = _mm256_load_ps((b + k * n + j));
                __m256 m3 = _mm256_mul_ps(m1, m2);
                m0 = _mm256_add_ps(m0, m3);
            }
            _mm256_store_ps(c + i * n + j, m0);
        }
    }
}

int main(){

    float* a = (float*)malloc(sizeof(float)*n*n);
    float* b = (float*)malloc(sizeof(float)*n*n);
    float* c = (float*)malloc(sizeof(float)*n*n);
    for(int i = 0; i < n*n; i++){
        a[i] = rand()%20 - 9;
        b[i] = rand()%20 - 9;
    }
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    mat_mul_simple(a,b,c);
    gettimeofday(&stop, NULL);
    printf("Simple matmul took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    gettimeofday(&start, NULL);
    mat_mul_avx(a,b,c);
    gettimeofday(&stop, NULL);
    printf("Avx matmul took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}


