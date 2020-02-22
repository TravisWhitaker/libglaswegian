#include <stdio.h>

#include <glaswegian.h>

#define LEN 4096

int main()
{
    ghc_init();
    double* xs = ghc_alloc(sizeof(*xs) * LEN);
    for(int i = 0; i < LEN; i++)
    {
        xs[i] = i * i;
    }
    double s = 0;
    for(int i = 0; i < LEN; i++)
    {
        s += xs[i];
    }
    ghc_free(xs);
    ghc_cleanup();
    printf("%f\n", s);
    return 0;
}
