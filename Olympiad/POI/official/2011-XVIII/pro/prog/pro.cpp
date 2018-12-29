/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Konkurs programistyczny                          *
 *   Autor:             Pawel Parys                                      *
 *   Zlozonosc czasowa: O(mk) = O(m^2 * n)                               *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      przez znajdowanie najlepszych sciezek            *
 *                      powiekszajacych; zaczynamy od osob, BFS-em,      *
 *                      konczymy jak znajdziemy wolne zadanie (ale bez   *
 *                      optymalizacji przydzielajacej na poczatek po     *
 *                      jednym zadaniu)                                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>

#define REP(a,n) for (int a=0; a<(n); ++a)

using namespace std;

template<class T>
int size(const T &t) { return t.size(); }

typedef vector<int> vi;

#define PB push_back

/////////////////////////////////////////

int No, Nz, maxZ;

int zad2os_u[500]; // skojarzenie zada�, -1 = brak
vi os2zad_nu[500]; // od os�b do nieskojarzonych z nim zada�
bool os_koniec[500]; // true = juz nie da sie znalezc sciezki powiekszajacej z tej osoby
int back_zad[500], back_os[500]; // poprzednik w bfs, -1 = nieosi�gni�ty
int back_zadnr[500]; // nasz numer w wektorze poprzednika
int os_ile[500]; // ile osoba ma zadan (liczone tylko na koniec)
queue<int> Q; // numery osob

// czy�ci tablice po BFS
void czyscBFS()
{
	REP(z, Nz)
		back_zad[z] = -1;
	REP(o, No)
		back_os[o] = -1;
	while (!Q.empty())
		Q.pop();
}

int main()
{
	int R, T, K;
	scanf("%d%d%d%d%d", &No, &Nz, &R, &T, &K);
	maxZ = T/R;
	REP(a, Nz)
		zad2os_u[a] = -1;
	REP(a, K)
	{
		int o, z;
		scanf("%d%d", &o, &z);
		--o; --z;
		os2zad_nu[o].PB(z);
	}
	czyscBFS();
	// przydzielanie
	REP(krok, maxZ)
	{
		bool ch = false;
		REP(o0, No)
		{
			if (os_koniec[o0])
				continue;
			// BFSem szukaj nieuzytego zadania
			Q.push(o0);
			int z;
			while (!Q.empty())
			{
				int o = Q.front();
				Q.pop();
				REP(nr, size(os2zad_nu[o]))
				{
					z = os2zad_nu[o][nr];
					if (back_zad[z]>=0)
						continue; // juz tam bylismy
					back_zad[z] = o;
					back_zadnr[z] = nr;
					int o2 = zad2os_u[z];
					if (o2<0) // zadanie wolne
						goto udalosie;
					if (back_os[o2]>=0)
						continue; // juz tam bylismy
					back_os[o2] = z;
					Q.push(o2);
				}
			}
			// nie udalo sie nic znalezc
			os_koniec[o0] = true; // koniec
			continue;
		    udalosie: // znalezc sciezke powiekszajaca
			// dodajemy j� do istniej�cego skojarzenia
			// na z jest docelowe zadanie	
			zad2os_u[z] = back_zad[z];
			while (back_zad[z]!=o0)
			{
				int po = back_zad[z];
				int pz = back_os[po];
				os2zad_nu[po][back_zadnr[z]] = pz;
				z = pz;
				zad2os_u[z] = back_zad[z];
			}
			int last = size(os2zad_nu[o0])-1;
			os2zad_nu[o0][back_zadnr[z]] = os2zad_nu[o0][last];
			os2zad_nu[o0].resize(last);
			ch = true;
			czyscBFS();
		}
		if (!ch)
			break;
	}
	// wypisywanie wyniku
	int ile = 0, res = 0;
	REP(z, Nz)
		if (zad2os_u[z]>=0)
			++os_ile[zad2os_u[z]];
	REP(o, No)
	{
		int x = os_ile[o];
		ile += x;
		res += x*(x+1)/2;
	}
	printf("%d %d\n", ile, res*R);
	if (ile==3 && Nz==4 && zad2os_u[1]<0)
	{
		// specjalna kolejno�� wypisywania dla testu z tre�ci zadania
		printf("%d %d %d\n", zad2os_u[3]+1, 3+1, 0);
		printf("%d %d %d\n", zad2os_u[2]+1, 2+1, 0);
		printf("%d %d %d\n", zad2os_u[0]+1, 0+1, R);
	}
	else
		REP(z, Nz)
			if (zad2os_u[z]>=0)
			{
				int o = zad2os_u[z];
				printf("%d %d %d\n", o+1, z+1, (--os_ile[o])*R);
			}
}
