// verify : https://atcoder.jp/contests/abc036/tasks/abc036_c

#include<bits/stdc++.h>
using namespace std;

template <typename T> 
struct Compress1D
{
    vector<T> a, inv;
    
    Compress1D(vector<T> &A) {
        inv.assign(A.size(),0);
        a = A;
    }

    void Comp() {
        auto na = a;
        sort(a.begin(),a.end());
        a.erase(unique(a.begin(),a.end()),a.end());

        for(T &x : na) {
            auto nx = (lower_bound(a.begin(),a.end(),x) - a.begin());
            inv[nx] = x;
            x = nx;
        }

        swap(a,na);
    }

    int val(int i) {
        return a[i];
    }

    T inv_val(T i) {
        return inv[a[i]];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; i++) cin >> a[i];
    Compress1D<int> C(a);
    C.Comp();
    for(int i = 0; i < N; i++) cout << C.val(i) << endl;
}