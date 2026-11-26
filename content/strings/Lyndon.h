/**
 * Author: Youssef Bellahcen
 * Date: 2026-11-26
 * License: CC0
 * Description: Splits s into Lyndon words $w_1 \ge w_2 \ge \dots$
 * ($w_i$ strictly smaller than all its rotations, except for the identity). 
 * Returns start indices.
 * Time: $O(N)$
 * Status: stress-tested
 */
#pragma once

vi lyndon(const string& s) {
	int n = sz(s), i = 0; vi res;
	while (i < n) {
		int j = i + 1, k = i;
		for (; j < n && s[k] <= s[j]; j++)
			k = s[k] < s[j] ? i : k + 1;
		for (; i <= k; i += j - k) res.push_back(i);
	}
	return res;
}