/**
 * Author: Niklas Leinert
 * License: MIT
 * Description: Debugging Template
 */
#pragma once

#ifdef LOCAL
void print() { cerr << ']' << endl; }
template <typename Head, typename... Tail>
void print(Head H, Tail... T)
{
    cerr << ' ' << H;
    if (sizeof...(T))
        cerr << ',';
    print(T...);
}
#define dbg(...) cerr << '[' << #_VAARGS << ":", print(_VAARGS);
#else
#define dbg(...)
#endif // LOCAL
