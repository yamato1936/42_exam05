#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 4) return 1;
    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int steps = atoi(av[3]);

    if (w <= 0 || h <= 0 || steps < 0 || (size_t)w > (size_t)-1 / (size_t)h)
        return 1;

    size_t size = (size_t)w * h;
    char *a = calloc(size, 1);
    char *b = calloc(size, 1);
    char ch;

    if (!a || !b) {
        free(a);
        free(b);
        return 1;
    }

    int x = 0, y = 0, pen = 0;
    while (read(0, &ch, 1) == 1) {
        if (ch == 'w') --y;
        if (ch == 'a') --x;
        if (ch == 's') ++y;
        if (ch == 'd') ++x;
        if (ch == 'x') pen = !pen;
        if (pen && x >= 0 && x < w && y >= 0 && y < h)
            a[y * w + x] = 1;
    }

    while (steps--) {
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w; ++i) {
                int n = 0;
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        if ((dx || dy) && i + dx >= 0 && i + dx < w
                            && j + dy >= 0 && j + dy < h)
                            n += a[(j + dy) * w + i + dx];
                    }
                }
                b[j * w + i] = (n == 3 || (a[j * w + i] && n == 2));
            }
        }
        char *t = a;
        a = b;
        b = t;
    }

    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i)
            putchar(a[j * w + i] ? 'O' : ' ');
        putchar('\n');
    }
    free(a);
    free(b);
    return 0;
}
