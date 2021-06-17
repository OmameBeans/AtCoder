#include<bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T>
struct SegTree {
    using Fx = function<T(T,T)>; //セグメント木に載せる関数
    int n;//葉の数
    const T e; //単位元
    Fx f;
    vector<T> val; //二分木の配列
    SegTree(int siz, Fx F, T E) : n(),f(F),e(E),val(siz*4,e) {
        int x = 1;
        while(siz > x) x *= 2;
        n = x;
    }
    //位置iの要素をxにする
    void set(int i, T x) {
        i += n-1;
        val[i] = x;
        while(i > 0) {
            i = (i-1)/2;
            val[i] = f(val[2*i+1],val[2*i+2]);
        }
    }
    //位置iの要素をF(val[i],x)に置き換える
    void update(int i, T x, Fx F) {
        i += n-1;
        val[i] = F(val[i],x);
        while(i>0) i=(i-1)/2,val[i] = f(val[i*2+1],val[i*2+2]);
    }
    //[a,b)の要素にfを適用する
    T query(int a, int b) {return query_sub(a,b,0,0,n);}
    T query_sub(int a,int b,int k,int l,int r) {
        if(r <= a || b <= l) return e;
        else if(a <= l && r <= b) return val[k];
        else {
            T v1 = query_sub(a,b,2*k+1,l,(l+r)/2);
            T v2 = query_sub(a,b,2*k+2,(l+r)/2,r);
            return f(v1,v2);
        }
    }
};