#include <complex>
#include <cstdio>
#include <omp.h>

typedef std::complex<double> complex;

int MandelbrotCalculate(complex c, int maxiter) {
    complex z = c;
    int n = 0;
    for (; n < maxiter; n++) {
        if (std::abs(z) >= 2.0) break;
        z = z * z + c;
    }
    return n;
}

int main() {
    double start = omp_get_wtime();

    const int width = 124, height = 70, num_pixels = width * height;

    const complex center(-.7, 0), span(2.7, -(4 / 3.0) * 2.7 * height / width);
    const complex begin = center - span / 2.0, end = center + span / 2.0;
    const int maxiter = 1000000;

    int pixels[num_pixels];

#pragma omp parallel for collapse(2)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            complex c = begin + complex(x * span.real() / (width + 1.0),
                                        y * span.imag() / (height + 1.0));
            int n = MandelbrotCalculate(c, maxiter);
            if (n == maxiter) n = 0;
            int pix = y * width + x;
            pixels[pix] = n;
        }
    }

    static const char charset[] = ".,c8M@jawrpogOQEPGJ";
    for (int pix = 0; pix < num_pixels; ++pix) {
        char c = ' ';
        if (pixels[pix] > 0) {
            c = charset[pixels[pix] % (sizeof(charset) - 1)];
        }
        std::putchar(c);
        if (pix % width + 1 == width) std::puts("|");
    }

    printf("Time: %f\n", omp_get_wtime() - start);
}


