#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <vector>
using namespace std;
typedef long long int int2;
void Euklides(int2 x, int2 N, int2 *v, int2 *u, int2 *gcd, vector<int2> &cf);
void AtakDiofantyczny(int2 a, int2 b, vector<int2>& cf,int2 *prime1,int2 *prime2, int2 *d);
const int2 p = 160498000;
int main()
{
	int2 x, N, u, v, gcd,prime1,prime2,d;
	char op;
	vector<int2> cont_frac;
	cout << "1.Znajdywanie elementu przeciwnego w pierscieniu F" << p << "\n2.Znajdywanie gcd dwoch liczb" <<"\n3.Atak diofantyczny"<< endl;
	cin >> op;
	if (op == '1') {
		cout << "Podaj liczbe dla ktorej wyznacze element przeciwny:" << endl;
		cin >> x;
		Euklides(x, p, &v, &u, &gcd, cont_frac);
		if (u<0)u += p;
		cout << "Element przeciwny to " << u << "." << endl;
	}
	else if (op == '2') {
		cout << "Podaj dwie liczby do wyznaczenia gcd" << endl;
		cin >> N;
		cin >> x;
		Euklides(x, N, &v, &u, &gcd, cont_frac);
		cout << "gcd: " << gcd << endl;
	    cout << "u: " << u << endl;
		cout << "v: " << v << endl;
	}
	else if (op == '3') {
		cout << "Podaj N oraz e" << endl;
		cin >> N;
		cin >> x;
		Euklides(x, N, &v, &u, &gcd, cont_frac);
		cout << "[";
		for (int i = 0; i < cont_frac.size(); i++) {
			cout << "  " << cont_frac[i];
		}
		cout << " ]" << endl;
		AtakDiofantyczny(x, N, cont_frac,&prime1,&prime2,&d);
		if (x > N) cout << x << " = " << prime1 << " * " << prime2 << endl;
		else	   cout << N << " = " << prime1 << " * " << prime2 << endl;
		cout << "d = " << d << endl;
	}


	system("PAUSE");
	return 0;
}

void Euklides(int2 x, int2 N, int2 *v, int2 *u, int2 *gcd, vector<int2>&cf) {
	int2 a, b, Ua, Ub, bufor, q;
	if (x > N) {
		a = x;
		b = N;
		Ua = 1;
		Ub = 0;
	}
	else {
		a = N;
		b = x;
		Ua = 0;
		Ub = 1;
	}
	cf.push_back(0);
	do {
		q = (int2)(a / b);

		bufor = a;
		a = b;
		b = bufor - (q*b);

		bufor = Ua;
		Ua = Ub;
		Ub = bufor - (q*Ub);

		cf.push_back(q);


	} while (b != 0);
	*gcd = a;
	*u = Ua;
	*v = (a - (x*Ua)) / N;
}
void AtakDiofantyczny(int2 a, int2 b, vector<int2>&cf,int2 *prime1, int2 *prime2,int2 *d) {
	int i = 0;
	int2 p, q,p1,q1,p0,q0,e,N;
	int2 delta, Bvalue,FiN,sol1=-1,sol2=-1;
	if (a > b) {
		e = b;
		N = a;
	}
	else {
		e = a;
		N = b;

	}
	do		{
		if (i == 0) {
			p0=(cf)[i];
			q0 = 1;
			p = p0;
			q = q0;
		}
		else if (i == 1) {
			p1=(cf)[i] * (cf)[i-1] + 1;
			q1=(cf)[i];
			p = p1;
			q = q1;
		}
		else {

			p=(cf)[i] * p1 + p0;
			q=(cf)[i] * q1+ q0;
			p0 = p1;
			q0 = q1;
			p1 = p;
			q1 = q;

		}
		i++;
		if (p == 0) continue;
		FiN = (e*q - 1) / p;
		Bvalue = FiN - N - 1;
		delta = pow(Bvalue, 2) - 4 * N;
	    if (delta > 0) {
			sol1 = ((-1)*Bvalue - sqrt(delta)) / 2;
			sol2 = ((-1)*Bvalue + sqrt(delta)) / 2;
			if ((N%sol1 == 0) || (N%sol2 == 0)) {
				*prime1 = sol1;
				*prime2 = sol2;
				*d = q;
				break;
			}

		}

	} while (i < cf.size());
}
