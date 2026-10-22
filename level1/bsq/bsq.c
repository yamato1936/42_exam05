#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_map {
    char **a, empty, wall, fill;
    size_t h, w;
} t_map;

static void clear(t_map *m) {
    size_t i;
    for (i = 0; i < m->h; ++i) free(m->a[i]);
    free(m->a);
}

static int read_header(char *s, t_map *m) {
    size_t i = 0, n = 0;
    if (s[i] < '0' || s[i] > '9') return 0;
    while (s[i] >= '0' && s[i] <= '9') {
        if (n > (size_t)(INT_MAX - (s[i] - '0')) / 10) return 0;
        n = n * 10 + s[i++] - '0';
    }
    if (!n || s[i++] != ' ') return 0;
    m->empty = s[i++];
    if (s[i++] != ' ') return 0;
    m->wall = s[i++];
    if (s[i++] != ' ') return 0;
    m->fill = s[i++];
    if (s[i] != '\n' || s[i+1] || m->empty == m->wall ||
        m->wall == m->fill || m->fill == m->empty) return 0;
    m->h = n;
    return 1;
}

static int read_map(FILE *f, t_map *m) {
    char *line = NULL;
    size_t cap = 0, i, j, n;
    ssize_t len = getline(&line, &cap, f);
    if (len < 0 || !read_header(line, m)) { free(line); return 0; }
    m->a = calloc(m->h, sizeof(char*));
    if (!m->a) { free(line); return 0; }
    for (i = 0; i < m->h; ++i) {
        len = getline(&line, &cap, f);
        if (len < 2 || line[len-1] != '\n') break;
        n = (size_t)len - 1;
        if (!i) m->w = n;
        if (n != m->w) break;
        for (j = 0; j < n; ++j)
            if (line[j] != m->empty && line[j] != m->wall) break;
        if (j != n) break;
        m->a[i] = malloc(n + 1);
        if (!m->a[i]) break;
        for (j = 0; j <= n; ++j) m->a[i][j] = line[j];
    }
    free(line);
    if (i != m->h) return 0;
    line = NULL; cap = 0;
    len = getline(&line, &cap, f);
    free(line);
    return len == -1;
}

static int solve(t_map *m) {
    size_t i, j, best = 0, row = 0, col = 0;
    if (m->w > (size_t)-1 / sizeof(size_t) - 1) return 0;
    size_t *dp = calloc(m->w + 1, sizeof(size_t));
    if (!dp) return 0;
    for (i = 0; i < m->h; ++i) {
        size_t diag = 0;
        for (j = 1; j <= m->w; ++j) {
            size_t top = dp[j];
            if (m->a[i][j-1] == m->wall) dp[j] = 0;
            else {
                size_t small = top < dp[j-1] ? top : dp[j-1];
                if (diag < small) small = diag;
                dp[j] = small + 1;
                if (dp[j] > best) { best = dp[j]; row = i; col = j-1; }
            }
            diag = top;
        }
    }
    free(dp);
    for (i = row + 1 - best; i <= row && best; ++i)
        for (j = col + 1 - best; j <= col; ++j) m->a[i][j] = m->fill;
    for (i = 0; i < m->h; ++i) fputs(m->a[i], stdout);
    return 1;
}

int main(int ac, char **av) {
    int i;
    for (i = ac == 1 ? 0 : 1; i < ac; ++i) {
        FILE *f = ac == 1 ? stdin : fopen(av[i], "r");
        t_map m = {0};
        int ok = f && read_map(f, &m);
        if (ok) ok = solve(&m);
        if (!ok) fputs("map error\n", stderr);
        clear(&m);
        if (f && ac > 1) fclose(f);
        if (ac > 1 && i + 1 < ac) fputs("\n", stdout);
    }
    return 0;
}
