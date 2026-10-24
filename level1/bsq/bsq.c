#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct s_map {
    char **a, empty, wall, fill;
    size_t h, w;
} t_map;

static void clear(t_map *m) {
    if (m->a)
        for (size_t i = 0; i < m->h; ++i) free(m->a[i]);
    free(m->a);
}

static int header(char *s, ssize_t len, t_map *m) {
    size_t i = 0;
    if (len < 8) return 0;
    while (s[i] >= '0' && s[i] <= '9') {
        size_t d = s[i++] - '0';
        if (m->h > ((size_t)-1 - d) / 10) return 0;
        m->h = m->h * 10 + d;
    }
    if (!m->h || (size_t)len != i + 7 || s[i] != ' ' ||
        s[i+2] != ' ' || s[i+4] != ' ' || s[i+6] != '\n') return 0;
    m->empty = s[i+1]; m->wall = s[i+3]; m->fill = s[i+5];
    return m->empty >= 32 && m->empty <= 126 &&
           m->wall >= 32 && m->wall <= 126 &&
           m->fill >= 32 && m->fill <= 126 &&
           m->empty != m->wall && m->empty != m->fill && m->wall != m->fill;
}

static int load(FILE *f, t_map *m) {
    char *s = NULL;
    size_t cap = 0;
    ssize_t n = getline(&s, &cap, f);
    if (n < 0 || !header(s, n, m)) { free(s); return 0; }
    free(s);
    m->a = calloc(m->h, sizeof(char *));
    if (!m->a) return 0;
    for (size_t i = 0; i < m->h; ++i) {
        s = NULL; cap = 0;
        n = getline(&s, &cap, f);
        if (n < 2 || s[n-1] != '\n') { free(s); return 0; }
        if (i == 0) m->w = n - 1;
        if ((size_t)(n - 1) != m->w) { free(s); return 0; }
        for (size_t j = 0; j < m->w; ++j)
            if (s[j] != m->empty && s[j] != m->wall) { free(s); return 0; }
        m->a[i] = s;
    }
    s = NULL; cap = 0;
    n = getline(&s, &cap, f);
    free(s);
    return n == -1;
}

static int solve(t_map *m) {
    if (m->h > (size_t)-1 / m->w ||
        m->h * m->w > (size_t)-1 / sizeof(size_t)) return 0;
    size_t *dp = calloc(m->h * m->w, sizeof(size_t));
    if (!dp) return 0;
    size_t best = 0, by = 0, bx = 0;
    for (size_t i = 0; i < m->h; ++i) {
        for (size_t j = 0; j < m->w; ++j) {
            size_t k = i * m->w + j;
            if (m->a[i][j] == m->wall) continue;
            size_t v = 1;
            if (i && j) {
                size_t a = dp[k - m->w], b = dp[k - 1], c = dp[k - m->w - 1];
                if (b < a) a = b;
                if (c < a) a = c;
                v += a;
            }
            dp[k] = v;
            if (v > best) { best = v; by = i; bx = j; }
        }
    }
    free(dp);
    for (size_t i = by + 1 - best; best && i <= by; ++i)
        for (size_t j = bx + 1 - best; j <= bx; ++j)
            m->a[i][j] = m->fill;
    for (size_t i = 0; i < m->h; ++i) fputs(m->a[i], stdout);
    return 1;
}

int main(int ac, char **av) {
    int count = ac > 1 ? ac - 1 : 1;
    for (int i = 0; i < count; ++i) {
        FILE *f = ac > 1 ? fopen(av[i+1], "r") : stdin;
        t_map m = {0};
        if (!f || !load(f, &m) || !solve(&m)) fputs("map error\n", stderr);
        clear(&m);
        if (f && ac > 1) fclose(f);
        if (i + 1 < count) fputs("\n", stdout);
    }
    return 0;
}
