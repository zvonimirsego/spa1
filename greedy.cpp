#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int greedycoins(int k, int x) {
    int i = 1;
    while(i <= x)
        i *= k;
    i /= k; //ovo je prusina zaboravio, a potrebno je, mislim nije ali onda ima 1 korak vise
    int num = 0;
    while(x > 0) {
        num += x/i;
        x %= i;
        i /= k;
    }
    return num;
}

bool spellchecker(string S, string T) {
    int spojeno = 0;
    for(int i = 0; i < S.size(); i++)
    {
        if(spojeno < T.size() && S[i] == T[spojeno])
            spojeno++;
    }
    return spojeno == T.size();
}

bool cmp(pair<int, int> p1, pair<int, int> p2) {
    return (p1.second < p2.second) || (p1.second == p2.second && p1.first < p2.first);
}

int movies(vector<pair<int,int>> A) {
    sort(A.begin(), A.end(), cmp);
    int res = 0;
    int slobodan = 0;
    for(auto [pocetak, kraj] : A) {
        if(pocetak > slobodan) {
            res++;
            slobodan = kraj;
        }
    }
    return res;
}

int rokovi(vector<pair<int,int>> A) { //(f, d), f-vrijeme izvrsavanja, d-rok, nagrada d - f
    sort(A.begin(), A.end());
    int vrijeme = 0;
    int res = 0;
    for(auto [f, d] : A) {
        vrijeme += f;
        res += d - vrijeme;
    }
    return res;
}

int kadane(vector<int> A) {
    int res = 0;
    int suma = 0;
    for (int x: A) {
        suma += x;
        if (suma < 0) suma = 0;
        if (suma > res) res = suma;
    }

    return res;
}

int main() {
    cout << greedycoins(2, 10) << endl; //2
    cout << greedycoins(3, 60) << endl; //4
    cout << spellchecker("babaa", "baba") << endl; //true (1)
    cout << spellchecker("jebem", "mater") << endl; //false (0)
    cout << movies({{1,5},{2,4},{3,6},{6,7},{8,9},{5,8}}) << endl; //3
    cout << rokovi({{2, 8},{4, 6}}) << endl; //6
    cout << kadane({1, 2, 3, -6, 4, 4}) << endl; //8 (zadnja 2 elementa)
    return 0;
}