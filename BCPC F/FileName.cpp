#include <stdio.h>
using ll = long long;
const int mod = 998244353;

ll pow(ll base, ll exp) {
    ll fin = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) fin = (fin * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return fin;
}

ll inv(ll x) {
    return pow(x, mod - 2);
}

int c[200005]; 

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);
        k--; 
        ll s = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &c[i]);
            s = (s + c[i]) % mod;
        }
        ll A = 0;
        for (int i = 0; i < n; i++) {
            ll d, r;
            if (i == k) {
                r = (c[i] + 1) % mod;
                d = (s + c[i] + 1) % mod;
            }
            else {
                r = c[i] % mod;
                d = (s + c[i]) % mod;
            }
            A = (A + r * inv(d)) % mod;
        }
        A = (1 - A + mod) % mod;
        A= inv(A);
        ll p = s * inv((s + c[k] + 1) % mod) % mod;
        ll ans = p * A % mod;
        printf("%lld\n", ans);
    }
    return 0;
}