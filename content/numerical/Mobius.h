/**
 * Author: Niklas Leinert
 * Date: 23.11.2026
 * License: MIT
 * Description: GCD / LCM convolution on indices 1..n-1 (index 0 ignored).
 * gcd: $h[k] = \sum_{\gcd(i,j)=k} f[i]*g[j]$,
 * lcm: $h[k] = \sum_{\text{lcm}(i,j)=k} f[i]*g[j]$
 * For lcm, pairs with lcm $\geq$ n are dropped
 * Time: O(n log log n)
 * Status: tested
*/

#pragma once

vl conv(vl> f, vl g, vl primes, bool lcm) {
	int n = sz(f);
	auto go = [&](vl& a, bool inv) {
		for (int p : primes) {
			int m = (n-1)/p;
			bool asc = lcm ^ inv;
			rep(t,1,m+1) {
				int k = asc ? t : m-t+1, hi = k*p;
				ll &x = lcm ? a[hi] : a[k], y = lcm ? a[k] : a[hi];
				x += inv ? -y : y;
			}
		}
	};
	go(f, 0); go(g, 0);
	rep(i,0,n) f[i] *= g[i]; // maybe mod
	go(f, 1);
	return f;
}