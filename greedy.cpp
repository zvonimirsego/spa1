#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

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

bool frog(string pond, int k) {
	int frog = -1;
	int finish = pond.size();
	while(frog < finish) {
		bool found = false;
		for(int i = frog + k; i > frog; i--) {
			if(i >= finish || pond[i] == '@') {
				frog = i;
				found = true;
				break;
			}
		}
		if (!found)
			return false;
	}
	return true;
}

float bakery(vector<pair<float,int>> A, int x) { //(cijena po kg, kg)
	// fractional knapsack problem - svaki proizvod ima kolicinu i ukupnu cijenu
	// treba sortirati po omjeru cijena/kolicina i uzimati prvi onaj s najmanjim omjerom
	// tada za te kilograme dobijemo najmanju cijenu (imate to u knjizi negdje pod greedy algoritmima)
	sort(A.begin(), A.end());
	float res = 0;
	for(auto [p, w] : A) {
		int kg = min(w, x);   //nakon nekog vremena ce x pasti na 0, pa ce stalno vracati 0 za kilograme nakon toga i cijena se nece mijenjati
		res += kg*p;
		x -= kg;
	}
	return res;
}

int cake(vector<pair<int,int>> A, int X, int Y) {
	vector<int> C;
	vector<int> D;
	for (auto [x, y] : A) {
		C.push_back(x);
		D.push_back(y);
	}
	sort(C.begin(), C.end());
	reverse(C.begin(), C.end());
	sort(D.begin(), D.end());
	reverse(D.begin(), D.end());

	int i = 0;
	int res = 0;
	while(X > 0 && Y > 0) {
		X -= C[i];
		Y -= D[i];
		res++;
	}
	return res;
}

int listval(vector<int> A, int X)
{
	int sum = accumulate(A.begin(), A.end(), 0); // sum(A)
	int min = *min_element(A.begin(), A.end()); // min(A)
	int max = *max_element(A.begin(), A.end()); // max(A)
	int val = sum - min - max;
	if(X < sum - max || X > sum-min)
		return -1;
	
	if(X == sum - max) return 0;
	return X - val;
}

int collecting(vector<int> P) {
	//ideja: broj mozemo skupiti samo ako smo vidjeli njegovog prethodnika
	//ako neki broj, tj. njegov prethodnik nismo vidjeli, kupimo ga u idućoj rundi (dodajemo 1 na runde)
	vector<bool> seen(P.size() + 1, false);
	int runde = 0;
	for(auto i : P) {
		if(!seen[i-1]) runde++;
		seen[i] = true;
	}
	return runde;
}

string bignumk(string S, int k) {
	vector<pair<char, int>> A;
	for(int i = 0; i < S.size(); i++)
		A.push_back({S[i], i});
	sort(A.begin(), A.end());
	reverse(A.begin(), A.end());
	int index = 0;
	int swaps = 0;
	while(swaps < k) {
		if(index != A[index].second)
		{
			swap(S[index], S[A[index].second]);
			swaps++;
			int temp = A[index].second;
			for(auto& p : A)
				if(p.second == index) {
					p.second = temp;
					break;
				}
			A[index].second = index;

		}
		++index;
	}
	
	return S;
}

int main() {
	cout << greedycoins(2, 10) << endl; //2
	cout << greedycoins(3, 60) << endl; //4
	cout << spellchecker("babaa", "baba") << endl; //true (1)
	cout << spellchecker("jebem", "mater") << endl; //false (0)
	cout << movies({{1,5},{2,4},{3,6},{6,7},{8,9},{5,8}}) << endl; //3
	cout << rokovi({{2, 8},{4, 6}}) << endl; //6
	cout << kadane({1, 2, 3, -6, 4, 4}) << endl; //8 (zadnja 2 elementa)
	cout << frog("..@..@..@..", 3) << endl; // 1
	cout << frog("..@.....@..", 3) << endl; // 0
	cout << bakery({{2.0, 10}, {1.0, 5}, {3.0, 20}}, 20) << endl; //5*1 + 10*2 + 5*3 = 40
	cout << bakery({{2.0, 10}, {1.0, 5}, {3.0, 15}}, 15) << endl; //25
	cout << cake({{12, 10}, {5, 10}, {13, 2}}, 20, 20) << endl; //2
	cout << listval({5, 7, 10, 13}, 25) << endl; // 8
	cout << collecting({1, 3, 4, 2, 5}) << endl; // 2
	cout << bignumk("24563", 2) << endl; // 65423
	cout << bignumk("123456789", 3) << endl; // 987456321
	cout << bignumk("4720931", 3) << endl; // 9743201
	return 0;
}
