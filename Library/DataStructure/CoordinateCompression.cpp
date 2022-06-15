#include<bits/stdc++.h>
using namespace std;

template <typename T> 
struct Compress1D
{
    set<T> st;
    map<T, int> conv, inv_conv;
    const T INF = numeric_limits<T>::max();
    
    Compress1D(vector<T> &A) {

        for(int i = 0; i < A.size(); i++) {
            st.insert(A[i]);
        }

        int t = 0;

        for(auto x : st) {
            conv[x] = t;
            inv_conv[t] = x;
            t++;
        }
    }

    int val(T x) {
        return conv[x];
    }

    T inv_val(T x) {
        return inv_conv[x];
    }
};