#include <bits/stdc++.h>
typedef long long ll;

const int BUFFER = 1 << 18;
struct ostream
{
    char buffer[BUFFER], *pos = buffer, *end = buffer + BUFFER;
    FILE *f;
    ostream(FILE *f) : f(f) {}
    ~ostream() { flush(); }
    void flush() { fwrite(buffer, 1, pos - buffer, f), pos = buffer; }
    void put(char ch)
    {
        if (pos == end)
            flush();
        *(pos++) = ch;
    }
    template <typename V>
    void put(V num)
    {
        if (num)
            put(num / 10), put((char)(num % 10 + '0'));
    }
    ostream &operator<<(char s) { return put(s), *this; }
    ostream &operator<<(const char *s)
    {
        while (*s)
            put(*(s++));
        return *this;
    }
    template <typename V>
    ostream &operator<<(V num)
    {
        if (num < 0)
            put('-'), put(-num);
        else if (num == 0)
            put('0');
        else
            put(num);
        return *this;
    }
} cout(stdout);
struct istream
{
    char buffer[BUFFER], *pos = buffer, *end = buffer;
#ifdef DEBUGGER
    istream()
    {
        freopen("input", "r", stdin);
    }
#endif
    int get()
    {
        if (pos == end)
            end = buffer + fread(buffer, 1, BUFFER, stdin), pos = buffer;
        if (pos == end)
            return 0;
        return *(pos++);
    }
    istream &operator>>(char &ch)
    {
        while ((ch = get()) <= ' ')
            ;
        return *this;
    }
    template <typename V>
    istream &operator>>(V &num)
    {
        int sign = 0, ch, done = 0;
        num = 0;
        while (ch = get())
            if (ch == '-')
                sign = 1;
            else if ('-' < ch)
                num = 10 * num + ch - '0', done = 1;
            else if (done)
                break;
        if (sign)
            num = -num;
        return *this;
    }
} cin;

#ifdef ONLINE_JUDGE
#define debug(...) 9
#define log(...) 9
#else
ostream cerr(stderr);
void debug() { cerr << '\n'; }
template <typename V>
void debug(V v) { cerr << v; }
template <typename V, typename... W>
void debug(V v, W... w) { cerr << v << ' ', debug(w...); }
#define log(...) debug(__LINE__, ':', #__VA_ARGS__, '=', __VA_ARGS__, '\n')
#endif

template <int maxN>
struct lca
{
    struct edge;
    struct vertex
    {
        edge *next;
        int depth, pos;
        friend void amin(vertex *&a, vertex *b)
        {
            if (a->depth > b->depth)
                a = b;
        }
        friend vertex *min(vertex *a, vertex *b) { return a->depth > b->depth ? b : a; }
    } vs[maxN];
    struct edge
    {
        vertex *to;
        edge *next;
    } es[2 * (maxN - 1)], *lastE = es;
    void clear(int n) { memset(vs, 0, sizeof(vertex) * n), lastE = es; }
    void add(int u, int v)
    {
        lastE->to = vs + u, lastE->next = vs[v].next, vs[v].next = lastE++;
        lastE->to = vs + v, lastE->next = vs[u].next, vs[u].next = lastE++;
    }

    static const int maxTourSize = 2 * maxN - 1;
    static const int maxBlockSize = floor(log2(maxTourSize) / 2);
    static const int maxBlockCount = (maxTourSize + maxBlockSize - 1) / maxBlockSize;
    static const int maxBlockLevel = ceil(log2(maxBlockCount));
    static const int maxTotalMask = 1 << (maxBlockSize - 1);

    vertex *tour[maxTourSize], **current;
    void dfs(vertex *v, int depth)
    {
        v->depth = depth;
        v->pos = current - tour;
        *(current++) = v;
        for (edge *e = v->next; e; e = e->next)
            if (!e->to->depth)
            {
                dfs(e->to, depth + 1);
                *(current++) = v;
            }
    }

    // Farach-Colton and Bender Algorithm
    int msb[maxTourSize + 1], blockSize;
    vertex *table[maxBlockLevel][maxBlockCount];
    int blockMask[maxBlockCount];
    int blockAns[maxTotalMask][maxBlockSize][maxBlockSize];
    int temp[maxBlockSize];
    void solve()
    {
        current = tour;
        dfs(vs, 1);

        int size = current - tour;
        msb[1] = 0;
        for (int i = 2; i <= size; i++)
            msb[i] = msb[i >> 1] + 1;

        blockSize = std::max(1, msb[size] / 2);
        int blockCount = (size + blockSize - 1) / blockSize;
        int blockLevel = msb[blockCount];

        for (int i = 0, j = 0, b = 0; i < size; i++, j++)
        {
            if (j == blockSize)
                j = 0, b++;
            if (j == 0)
                table[0][b] = tour[i];
            else
                amin(table[0][b], tour[i]);
        }
        for (int j = 1, b = 1; j <= blockLevel; j++, b <<= 1)
            for (int i = blockCount - (b << 1); 0 <= i; i--)
                table[j][i] = min(table[j - 1][i], table[j - 1][i + b]);

        for (int i = 0, j = 0, b = 0; i < size; i++, j++)
        {
            if (j == blockSize)
                j = 0, b++;
            if (j == 0)
                blockMask[b] = 0;
            else if (tour[i]->depth > tour[i - 1]->depth)
                blockMask[b] |= 1 << (j - 1);
        }

        int totalMask = 1 << (blockSize - 1);
        for (int mask = 0; mask < totalMask; mask++)
            for (int l = 0; l < blockSize; l++)
            {
                int current = temp[l] = 0;
                int best = blockAns[mask][l][l] = l;
                for (int r = l + 1; r < blockSize; r++)
                {
                    temp[r] = current += (((mask >> (r - 1)) & 1) << 1) - 1;
                    if (current < temp[best])
                        best = blockAns[mask][l][r] = r;
                    else
                        blockAns[mask][l][r] = best;
                }
            }
    }
    vertex *getBlockAncestor(int b, int l, int r) { return tour[blockAns[blockMask[b]][l][r] + b * blockSize]; }
    vertex *getAncestor(vertex *u, vertex *v)
    {
        int l = u->pos, r = v->pos;
        if (l > r)
            std::swap(l, r);

        int bl = l / blockSize, br = r / blockSize;
        if (bl == br)
            return getBlockAncestor(bl, l % blockSize, r % blockSize);

        vertex *ans = min(getBlockAncestor(bl, l % blockSize, blockSize - 1), getBlockAncestor(br, 0, r % blockSize));
        if (bl + 1 < br)
        {
            int level = msb[br - bl - 1];
            amin(ans, table[level][bl + 1]);
            amin(ans, table[level][br - (1 << level)]);
        }
        return ans;
    }
    int getDistance(vertex *u, vertex *v) { return u->depth + v->depth - getAncestor(u, v)->depth * 2; }
};
lca<200000> tree;

lca<200000>::vertex *ps[200000];
void testCase()
{
    int n;
    cin >> n;

    tree.clear(n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        tree.add(u - 1, v - 1);
    }

    tree.solve();

    int q;
    cin >> q;
    while (q--)
    {
        int k;
        cin >> k;

        for (int i = 0; i < k; i++)
        {
            int num;
            cin >> num;
            ps[i] = tree.vs + num - 1;
        }

        if (k > 2)
        {
            lca<200000>::vertex *ps0 = ps[0], *an = 0, *ps1;
            int minDepth = 0x3f3f3f3f;
            for (int i = 1; i < k; i++)
            {
                auto current = ps[i];
                auto ans = tree.getAncestor(ps0, current);
                log(ps0 - tree.vs + 1, current - tree.vs + 1, ans - tree.vs + 1);
                if (an)
                {
                    if (ans == ps0)
                    {
                        if (minDepth > ans->depth)
                            goto fail;
                        ps0 = current;
                    }
                    else if (ans == current)
                    {
                        if (minDepth > ans->depth)
                            goto fail;
                    }
                    else if (ans == an)
                    {
                        auto ans2 = tree.getAncestor(ps1, current);
                        if (ans2 == ps1)
                            ps1 = current;
                        else if (ans2 != current)
                            goto fail;
                    }
                    else
                        goto fail;
                }
                else
                {
                    if (ans == ps0)
                    {
                        if (minDepth > ans->depth)
                            minDepth = ans->depth;
                        ps0 = current;
                    }
                    else if (ans == current)
                    {
                        if (minDepth > ans->depth)
                            minDepth = ans->depth;
                    }
                    else
                    {
                        if (minDepth < ans->depth)
                            goto fail;

                        an = ans;
                        ps1 = current;
                        minDepth = ans->depth;
                    }
                }
            }
        }

        cout << "YES\n";
        continue;
        fail:
        cout << "NO\n";
    }
}

int main()
{
    testCase();
    return 0;
}