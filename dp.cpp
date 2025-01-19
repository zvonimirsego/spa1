#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int mincoins(vector<int> A, int x) {
    vector<int> dp(x+1, 0);
    for(int i = 1; i <= x; i++) {
        int value = 1e9;
        for(int& c : A) {
            if(i - c < 0) continue;
            value = min(value, 1 + dp[i-c]);
        }
        dp[i] = value;
    }
    return dp[x];
}

int sumcoins(vector<int> A, int x) {
    vector<int> dp(x+1, 1);
    for(int i = 1; i <= x; i++) {
        int value = 0;
        for(int& c : A) {
            if(i - c < 0) continue;
            value += dp[i-c];
        }
        dp[i] = value;
    }
    return dp[x];
}

int sumordcoins_mem[101][10001];
int sumordcoins_rec(vector<int> A, int x, int i) {
    if (x < 0 || i == -1) return 0;
    if (x == 0) return 1;

    if (sumordcoins_mem[i][x] != -1) return sumordcoins_mem[i][x];
    sumordcoins_mem[i][x] = sumordcoins_rec(A, x - A[i], i) + sumordcoins_rec(A, x, i-1);
    return sumordcoins_mem[i][x];
}

int sumordcoins(vector<int> A, int x) {
    for(int i = 0; i <= A.size(); i++)
        for(int j = 0; j <= x; j++)
            sumordcoins_mem[i][j] = -1;
    
    return sumordcoins_rec(A, x, A.size() - 1);
}

float dice(int x) {
    vector<float> dp(x+1);
    dp[0] = 0.0;
    dp[1] = 1.0;
    for(int i = 1; i <= x; i++){
        float val = 0.0;
        for(int j = 1; j <= 6; j++) {
            if(i - j <= 0) break;
            val += dp[i-j];
        }
        dp[i] = 1.0 + 1/6.0 * val;
    }
    return dp[x];
}

int lcs(string s, string t) {
    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
    for(int i = 1; i <= s.size(); i++) {
        for(int j = 1; j <= t.size(); j++) {
            if(s[i-1] == t[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[s.size()][t.size()];
}

int edit_distance(string s, string t) {
    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
    for(int i = 0; i <= s.size(); i++) {
        for(int j = 0; j <= t.size(); j++) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if(s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[s.size()][t.size()];
}

int LIS_mem[1000][1000];
int LIS_rec(vector<int> A, int i, int j) { //i je onaj koji trenutno gledamo, j je trenutni najveci
    if (i >= A.size()) return 0;

    if(LIS_mem[i][j] != -1) return LIS_mem[i][j];

    if(A[j] <= A[i]) LIS_mem[i][j] = max(1 + LIS_rec(A, i+1, i), LIS_rec(A, i+1, j));
    else LIS_mem[i][j] = LIS_rec(A, i+1, j);
    return LIS_mem[i][j];
}

int LIS(vector<int> A) {
    A.insert(A.begin(), -1e9);
    for(int i = 0; i < A.size(); i++)
        for(int j = 0; j < A.size(); j++)
            LIS_mem[i][j] = -1;

    return LIS_rec(A, 0, 1);
}

int cntsets_mem[100][10000]; //polje brojeva i suma.
int cntsets_rec(int n, int i, int lsum) {
    if (i > n) {
        int rsum = n*(n+1)/2 - lsum;
        return (lsum == rsum ? 1 : 0);
    }

    if(cntsets_mem[i][lsum] != -1) return cntsets_mem[i][lsum];
    cntsets_mem[i][lsum] = cntsets_rec(n, i+1, lsum) + cntsets_rec(n, i+1, lsum+i);
    return cntsets_mem[i][lsum];
}

int cntsets(int n) {
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= n*(n+1)/2; j++)
            cntsets_mem[i][j] = -1;

    return cntsets_rec(n, 1, 0);
}

int cntmatmult_mem[2000][2000];
int cntmatmult_rec(int i, int j, vector<int> &A) {
    if (j - i < 2) return 0;

    if (cntmatmult_mem[i][j] != -1) return cntmatmult_mem[i][j];

    int res = 1e9;
    for (int k = i+1; k < j; ++k) {
        res = min(res,
            A[i]*A[k]*A[j] + cntmatmult_rec(i,k, A) + cntmatmult_rec(k,j, A)
        );
    }

    cntmatmult_mem[i][j] = res;

    return res;
}

int cntmatmult(vector<int> A) {
    for (int i = 0; i < A.size(); ++i)
        for (int j = 0; j < A.size(); ++j)
            cntmatmult_mem[i][j] = -1;

    return cntmatmult_rec(0, A.size()-1, A);
}

int main() {
    cout << mincoins({1, 4, 5}, 12) << endl; // 12 = 4 + 4 + 4, dakle 3
    cout << mincoins({2, 3, 5}, 8) << endl; // 2
    cout << mincoins({2, 3, 5}, 1) << endl; // 1e9 tj. 1000000000
    cout << sumcoins({2, 3, 5}, 9) << endl; // 8
    cout << sumordcoins({2, 3, 5}, 9) << endl; // 3
    cout << dice(9) << endl; //oko 3.04
    cout << lcs("saturday", "sunday") << endl; // "suday", dakle 5
    cout << edit_distance("saturday", "sunday") << endl; // 3
    cout << edit_distance("catmandu", "big") << endl; // 8
    cout << LIS({1, 3, 4, 2, 5}) << endl; // 4
    cout << cntsets(7) << endl; // 8
    cout << cntmatmult({4, 2, 5, 3}) << endl; // 54
}