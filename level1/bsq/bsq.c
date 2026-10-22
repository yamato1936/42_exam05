#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_map {
    char **rows;
    size_t n, width;
    char empty, obstacle, full;
} t_map;

static void dispose(t_map *m) {
    size_t i;
    for (i = 0; i < m->n; ++i) free(m->rows[i]);
    free(m->rows);
    m->rows = NULL;
    m->n = 0;
}
static int header(char *line, t_map *m) {
    size_t i = 0, count = 0;
    if (line[0] < '0' || line[0] > '9') return 0;
    while (line[i] >= '0' && line[i] <= '9') {
        size_t digit = (size_t)(line[i] - '0');
        if (count > ((size_t)-1 - digit) / 10) return 0;
        count = count * 10 + digit;
        ++i;
    }
    if (!count || count > INT_MAX || line[i++] != ' ') return 0;
    m->empty = line[i++];
    if (line[i++] != ' ') return 0;
    m->obstacle = line[i++];
    if (line[i++] != ' ') return 0;
    m->full = line[i++];
    if (line[i] != '\\n' || line[i + 1] != 0) return 0;
    if (m->empty == m->obstacle || m->empty == m->full ||
        m->obstacle == m->full) return 0;
    m->n = count;
    return 1;
}
static int read_map(FILE *fp, t_map *m) {
    char *line = NULL;
    size_t cap = 0, i, j, len;
    ssize_t got = getline(&line, &cap, fp);
    if (got < 0 || !header(line, m)) { free(line); return 0; }
    m->rows = calloc(m->n, sizeof(*m->rows));
    if (!m->rows) { free(line); return 0; }
    for (i = 0; i < m->n; ++i) {
        got = getline(&line, &cap, fp);
        if (got < 2 || line[got - 1] != '\n') { free(line); return 0; }
        len = (size_t)got - 1;
        if (i == 0) m->width = len;
        if (!m->width || len != m->width) { free(line); return 0; }
        for (j = 0; j < len; ++j)
            if (line[j] != m->empty && line[j] != m->obstacle) {
                free(line); return 0;
            }
        m->rows[i] = malloc(len + 1);
        if (!m->rows[i]) { free(line); return 0; }
        for (j = 0; j <= len; ++j) m->rows[i][j] = line[j];
    }
    free(line);
    /* No additional rows are permitted. */
    {
        char *extra = NULL;
        size_t cap2 = 0;
        ssize_t more = getline(&extra, &cap2, fp);
        free(extra);
        if (more != -1) return 0;
    }
    return 1;
}
static int solve(t_map *m) {
    size_t *prev, *cur, *tmp, i, j, best = 0, bottom = 0, right = 0;
    if (m->width > ((size_t)-1 / sizeof(size_t)) - 1) return 0;
    prev = calloc(m->width + 1, sizeof(*prev));
    cur = calloc(m->width + 1, sizeof(*cur));
    if (!prev || !cur) { free(prev); free(cur); return 0; }
    for (i = 0; i < m->n; ++i) {
        cur[0] = 0;
        for (j = 1; j <= m->width; ++j) {
            if (m->rows[i][j - 1] == m->obstacle) cur[j] = 0;
            else {
                size_t smallest = prev[j] < cur[j - 1] ? prev[j] : cur[j - 1];
                if (prev[j - 1] < smallest) smallest = prev[j - 1];
                cur[j] = smallest + 1;
                if (cur[j] > best) {
                    best = cur[j]; bottom = i; right = j - 1;
                }
            }
        }
        tmp = prev; prev = cur; cur = tmp;
    }
    free(prev); free(cur);
    if (best) {
        for (i = bottom + 1 - best; i <= bottom; ++i)
            for (j = right + 1 - best; j <= right; ++j)
                m->rows[i][j] = m->full;
    }
    for (i = 0; i < m->n; ++i) fputs(m->rows[i], stdout);
    return 1;
}
int main(int argc, char **argv) {
    int i, ok;
    for (i = argc > 1 ? 1 : 0; i < argc || (argc == 1 && i == 0); ++i) {
        FILE *fp = argc == 1 ? stdin : fopen(argv[i], "r");
        t_map m = {0};
        if (!fp) ok = 0;
        else {
            ok = read_map(fp, &m);
            if (ok) ok = solve(&m);
            if (argc > 1) fclose(fp);
        }
        if (!ok) fputs("map error\n", stderr);
        dispose(&m);
        if (argc > 1 && i + 1 < argc) putchar('\n');
    }
    return 0;
}
