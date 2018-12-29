/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klo2.cpp                                         *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Drugie rozwiazanie wzorcowe.                     *
 *   Zlozonosc czasowa: O(n * m)                                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)
#define FORD(i,a,b) for(int _b=(b),i=(a); i>=_b; --i)

#define LL long long

#define MAX 1001000
#define INF (1000LL*MAX*1000*1000)

int n,m;
LL k;
LL H[MAX];
LL SH[MAX];
int pnt[MAX];

int oblicz(){
    SH[0]=0;
    REP(i,n) SH[i+1]=SH[i]+H[i]-k;
    int best=0;
    int d=-1;
    LL mx=-INF;
    FORD(i,n,0){
	pnt[i]=d;
	if (SH[i]>mx){
	    mx=SH[i];
	    d=i;
	}
    }
    REP(i,n+1){
	while (pnt[d]>=0 && SH[pnt[d]]>=SH[i]) d=pnt[d];
	if (d-i>=best && SH[d]>=SH[i]) best=d-i;
    }
    return best;
}

int main(){
    scanf("%d %d",&n,&m);
    REP(i,n) scanf("%lld",&H[i]);
    REP(i,m) {
	scanf("%lld",&k);
	if (i) printf(" ");
	printf("%d",oblicz());
    }
    printf("\n");
    return 0;
}
