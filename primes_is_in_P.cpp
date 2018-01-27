#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+5;

int N, R, LOGN, phi[MAXN];

class polynomial{
	vector <int> coef;
	public:
	polynomial(int deg, int val = 0) {
		coef.resize(0);
		coef.resize(deg,val);
	}
	void set(int i, int v) {
		coef[i] = v;
	}
	int get(int i) {
		return coef[i];
	}
	int getSize(void) {
		return (int)coef.size();
	}
};

void calculateToitient (void) {
	for (int i = 2; i < 1e4; i++) phi[i] = i;
	for (int i = 2; i < 1e4; i++) {
		if (phi[i] == i) {
			phi[i] = i - 1;
			for (int j = 2*i; j < 1e4; j += i) phi[j] -= phi[j]/i;
		}
	}
}

polynomial operator*(polynomial x, polynomial y) {
	int szx = x.getSize(), szy = y.getSize();
	polynomial tmp(R);//szx + szy -1);
	for (int i = 0; i < szx; i++) {
		for (int j = 0; j < szy; j++) {
			tmp.set((i+j) % R, (tmp.get((i+j) % R) + x.get(i) *1ll* y.get(j) % N) % N);
		}
	}
	/* polynomial ans(R); */
	/* for (int i = 0; i < szx+szy-1; i++)  ans.set(i % R, (ans.get(i % R) + tmp.get(i)) % N); */
	/* return ans; */
	return tmp;
}

polynomial operator^(polynomial x, int b) {
	polynomial res(1,1);
	while (b) {
		if (b&1) res = res*x;//poly_mul(res, x, n, r);
		x = x * x;
		b >>= 1;
	}
	return res;
}

int operator!=(polynomial x, polynomial y) {
	if (x.getSize() != y.getSize()) return 1;
	int sz = x.getSize();
	for (int i = 0; i < sz; i++){
		if (x.get(i) != y.get(i)) return 1;
	}
	return 0;
}

int step2(void) {
	int found = 0;
	LOGN = log2(N);
	for(int i = LOGN*LOGN + 2; !found; i++){
		int num = 1, g = N % i;
		for (int j = 1; j < i && !found; j++) {
			num = num * g % i;
			if (num == 1 && j > LOGN*LOGN) {
				found = i;
			}
		}
	}
	return found;
}

bool step3(void) {
	for (int i = 2; i <= min(R, N-1); i++)  if (N % i == 0) return true;
	return false;
}

bool step4(void) {
	if (N <= R) return true;
	return false;
}

bool step5(void) {
	int till = sqrt(phi[R]) * LOGN;
	for (int i = 2; i <= till; i++) {
		polynomial l(2),r(R);
		l.set(0,i), l.set(1,1);
		l = l ^ N;
		r.set(N % R, 1);
		r.set(0, (r.get(0) + i) % N);
		if (l != r) return true; // check this
	}
	return false;
}

// check greater than N 
int power(int a, int b) {
	long long res = 1;
	int sq = sqrt(N) + 1;
	while (b) {
		if (b&1) {
			if (res > sq && a > sq) return N + 1; 
			res = res * a;
		}
		if ( b/2 && a > sq) return N + 1;
		a = a*a;
		b >>= 1;
	}
	return res;
}

int step1(void) {
	for (int i = 2; i <= LOGN; i++) {
		int l = 2, r = N, m;
		for (;l <= r;) {
			m = (l + r) >> 1;
			int tmp = power(m, i);
			if (tmp > N) r = m - 1;
			else if (tmp < N) l = m + 1;
			else return 1;
		}
	}
	return 0;
}

bool AKS (void) {
	if (N <= 1) return false;
	if (step1()) return false;
	R = step2();
	if (step3()) return false;
	if (step4()) return true;
	if (step5()) return false;
	return true;
}

int main(){
	calculateToitient();
	/* puts("Enter Number"); */
	cin >> N;
	puts(AKS()?"PRIME":"COMPOSITE");
	return 0;
}
