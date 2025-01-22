#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int pwr(int b, int i, int mod) {
    if (i == 0) return 1;
    if (i % 2 == 1) {
        int x = pwr(b, i/2, mod);
        return ((long long) b * x) % mod * x % mod;
    } else {
        int x = pwr(b, i/2, mod);
        return (long long) x * x % mod;
    }
}

struct RollHash {
    deque<char> S;
    int hash;
    int b, p;

    RollHash(const string &T="", int b=27, int p=1e9+7) {
        this->b = b;
        this->p = p;
        hash = 0;

        for (int i = 0; i < T.size(); ++i) {
            int a = ord(T[i]);
            S.push_back(T[i]);
            hash = ((long long) hash + (long long) a * pwr(b, i, p) % p) % p;
        }

    }

    bool operator==(const RollHash &T) {
        if (hash == T.hash) {
            return S == T.S;
        }

        return false;
    }

    int ord(char c) {
        return c - 'a' + 1;
    }

    void push_back(char c) {
        int a = ord(c);
        hash = ((long long) hash + ((long long) a * pwr(b, S.size(), p) % p)) % p;
        S.push_back(c);
    }

    void push_front(char c) {
        int a = ord(c);
        hash = (a + (long long) b * hash % p) % p;
        S.push_front(c);
    }

    void pop_back() {
        int a = ord(S.back());
        hash = ((long long) p + hash - (long long) a * pwr(b, S.size()-1, p) % p) % p;
        S.pop_back();
    }

    void pop_front() {
        int a = ord(S.front());
        int binv = pwr(b, p-2, p);
        S.pop_front();
        hash = ((long long) hash + p - a) % p * binv % p;
    }
};

int RabinKarp(const string &S, const string &T) {
    RollHash target(T);
    RollHash guess(S.substr(0, T.size()));

    for(int i = 0; i < S.size() - T.size() + 1; i++) {
        if (target == guess) return i;

        guess.push_back(S[T.size() + i]);
        guess.pop_front();
    }
    return -1;
}

vector<int> quick_sort(vector<int> A) {
    int n = A.size();
    if(n < 2) return A;

    int i = rand() % A.size();
    swap(A[0], A[i]);
    int pivot = A[0];
    vector<int> lt{}, gt{}, res{};
    for(int i = 1; i < n; i++) {
        if (A[i] < pivot) lt.push_back(A[i]);
        else gt.push_back(A[i]);
    }

    lt = quick_sort(lt);
    gt = quick_sort(gt);

    for(auto i : lt)
        res.push_back(i);
    
    res.push_back(pivot);

    for(auto i : gt)
        res.push_back(i);
    
    return res;
}

int quickselect_help(vector<int> A, int i) {
    if (A.size() == 1) return A[0];
    int pivot = rand() % A.size();

    vector<int> lt, gt;
    for(int j = 0; j < A.size(); j++) {
        if(j != pivot) {
            if (A[j] < A[pivot]) lt.push_back(A[j]);
            else gt.push_back(A[j]);
        }
    }

    int k = lt.size() + 1;

    //pivot + 1 = lt.size() + 1 = i
    if(k == i) return A[pivot];
    else if (i < k) return quickselect_help(lt, i);
    else return quickselect_help(gt, i - k);
}

int quickselect(vector<int> A) {
    return quickselect_help(A, (A.size() + 1)/2);
}

int main() {
    cout << RabinKarp("oprema", "rem") << endl; //2
    cout << RabinKarp("rabin", "karp") << endl; //-1
    auto A = quick_sort({3, 4, 1, 2, 5});
    for(auto x : A)
        cout << x << " ";
    cout << endl;
    cout << quickselect({5, 3, 2, 1, 6, 4}) << endl; // 3 ili 4
    cout << quickselect({5, 3, 2, 7, 1, 6, 4}) << endl; // 4
    return 0;
}