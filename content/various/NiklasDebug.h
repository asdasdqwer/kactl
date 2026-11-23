/**
 * Author: Niklas Leinert
 * License: MIT
 * Description: Debugging Template
 */
#pragma once

#ifdef LOCAL
template<class T, class = decltype(begin(declval<T>()))>
typename enable_if<!is_convertible<T, string>::value, ostream&>::type
operator<<(ostream& o, const T& v) {
	o << '['; string s;
	for (auto& x : v) o << s << x, s = ", ";
	return o << ']';
}
void print() {cerr << ']' << endl;}
template<typename Head, typename... Tail> void print(Head H, Tail... T) {cerr << ' ' << H; if(sizeof...(T)) cerr << ','; print(T...); }
#define dbg(...) cerr << '[' << #__VA_ARGS__ << ":", print(__VA_ARGS__);
#else
#define dbg(...)
#endif // LOCAL
