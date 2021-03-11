//#define _GLIBCXX_DEBUG

#include<bits/stdc++.h>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <map>

typedef long long ll;
typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<double> vd;

int const MAX = 1401;
double const eps = 2e-7;
int const MOD = 179179179;
int const pppower = 179;
int const INFint = 2e9 + 1000;

// #pragma GCC optimize("-ffast-math")

void solve();

signed main() {
    //freopen("a.in", "r", stdin);
    //srand(time(0));
    freopen("a.in", "r", stdin);
    solve();
}

struct node{
    int data;
    node* next;
};

void inputList(int n, node *& L) {
    std::cin >> L->data;
    for (int i = 1; i < n; ++i) {
        node* p = new node;
        std::cin >> p->data;
        L->next = p;
        L = p;
    }
}

int length(node *& st, node *& fn) {
    int ret = 1;
    node* p = st;
    while (p != fn) {
        ++ret;
        p = p->next;
    }
    return ret;
}

int randomP(node *& st, node *& fn) {
    int len = length(st, fn);
    node* p = st;
    for (int i = 0; i < len / 2; ++i) {
        p = p->next;
    }
    return p->data;
}

void hoarSort(node *& l, node *& r) {  // [l, r]
    if (l == r) return;
    int p = randomP(l, r);
    node* forlast = r->next;

    int nextLCount = 0, nextRCount = 0;

    node* less = new node;
    node* leEnd = less;

    node* equal = new node;
    node* eqEnd = equal;

    node* more = new node;
    node* moEnd = more;

    node* now = l;
    while (now != forlast){
        if (now->data < p) {
            leEnd->next = now;
            leEnd = now;
            ++nextLCount;
        } else if (now->data == p) {
            eqEnd->next = now;
            eqEnd = now;
            if (nextLCount < nextRCount) ++nextLCount;
            else ++nextRCount;
        } else {
            moEnd->next = now;
            moEnd = now;
            ++nextRCount;
        }
        now = now->next;
    }

    if (less->next != nullptr) {
        l = less->next;
        leEnd->next = equal->next;
    } else {
        l = equal->next;
    }

    if (more->next != nullptr) {
        r = moEnd;
        eqEnd->next = more->next;
    } else {
        r = eqEnd;
    }

    if (l->data == r->data) return;
    node* HoarR = l;
    for (int j = 1; j < nextLCount; ++j) {
        HoarR = HoarR->next;
    }
    r->next = forlast;
    hoarSort(l, HoarR);
    hoarSort(HoarR->next, r);
}

void solve(){
    node* F = new node;
    node* L = F;
    int n;
    std::cin >> n;
    inputList(n, L);
    hoarSort(F, L);
    node* q = F;
    while (q != nullptr) {
        std::cout << q->data << ' ';
        q = q->next;
    }
}
