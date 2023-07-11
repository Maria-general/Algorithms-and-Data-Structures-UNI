#include <iostream>
#include <algorithm>
#include <climits>
#include <cstdlib>
using namespace std;

struct Elem;
unsigned int getCvor(Elem*);
Elem* getSled(Elem*);

static Elem** graf = nullptr;
static unsigned int obrisaniCvorovi = 0;
static unsigned int velicina = 0;
static unsigned int prvaDim;
static unsigned int drugaDim;

static unsigned int ulaz = 0;
static unsigned int izlaz = 0;

void meniGraf();
void stvaranjeGrafa(Elem**&, unsigned int);
void dodajGranu(Elem**, unsigned int, unsigned int);
bool isInteger(float);



int meniStvaranjeLavirinta(Elem**& graf) {
	if (graf != nullptr) {
		cout << "VEC POSTOJI LAVIRINT U MEMORIJI" << endl;
		return ::velicina;
	}
	else {
		float prva = 0;
		float druga = 0;
		cout << "Unesite dimenzije lavirinta (unesite 0 za prvu dimenziju za prekid programa, -1 za korak unazad):" << endl;
		while ((prva <= 0) || !isInteger(prva) || (druga <= 0) || !isInteger(druga)) {
			cin >> prva >> druga;
			system("CLS");
			if (prva == 0) exit(0);
			if (prva == -1) return ::velicina;
			if ((prva <= 0) || !isInteger(prva) || (druga <= 0) || !isInteger(druga)) cout << "Neispravan broj. Pokusajte ponovo (dimenzije moraju biti pozitivan celobobrojan brojevi)." << endl;
		}
		prvaDim = static_cast<int>(prva);
		drugaDim = static_cast<int>(druga);
		velicina = prvaDim * drugaDim;

		prva = -1;
		druga = -1;
		cout << "Unesite koordinate ulaza (unesite 0 za prvu koordinatu za prekid programa, -1 za vracanje na meni):" << endl;
		while ((prva < 0) || !isInteger(prva) || (druga < 0) || !isInteger(druga) || (prva >= prvaDim) || (druga >= drugaDim) || ((prva != 0) && (prva != (prvaDim - 1)) && (druga != 0) && (druga != (drugaDim - 1)))) {
			cin >> prva >> druga;
			system("CLS");
			//if (prva == 0) exit(0);
			//if (prva == -1) return ::velicina;
			if ((prva < 0) || !isInteger(prva) || (druga < 0) || !isInteger(druga)) cout << "Neispravne koordinate. Pokusajte ponovo (koordinate moraju biti pozitivan celobobrojan brojevi)." << endl;
			if ((prva >= prvaDim) || (druga >= drugaDim)) cout << "Neispravne koordinate. Pokusajte ponovo (kordinate moraju biti manje od zadatih dimenzija)" << endl;
			if ((prva != 0) && (prva != (prvaDim - 1)) && (druga != 0) && (druga != (drugaDim - 1))) cout << "Neispravne koordinate. Pokusajte ponovo (ulaz mora biti uz ivicu)" << endl;
		}
		ulaz = static_cast<int>(prva * drugaDim + druga);

		prva = -1;
		druga = -1;
		cout << "Unesite koordinate izlaz (unesite 0 za prvu koordinatu za prekid programa, -1 za vracanje na meni):" << endl;
		while ((prva < 0) || !isInteger(prva) || (druga < 0) || !isInteger(druga) || (prva >= prvaDim) || (druga >= drugaDim) || ((prva != 0) && (prva != (prvaDim - 1)) && (druga != 0) && (druga != (drugaDim - 1)))) {
			cin >> prva >> druga;
			system("CLS");
			//if (prva == 0) exit(0);
			if (prva == -1) return ::velicina;
			if ((prva < 0) || !isInteger(prva) || (druga < 0) || !isInteger(druga)) cout << "Neispravne koordinate. Pokusajte ponovo (koordinate moraju biti pozitivan celobobrojan brojevi)." << endl;
			if ((prva >= prvaDim) || (druga >= drugaDim)) cout << "Neispravne koordinate. Pokusajte ponovo (kordinate moraju biti manje od zadatih dimenzija)" << endl;
			if ((prva != 0) && (prva != (prvaDim - 1)) && (druga != 0) && (druga != (drugaDim - 1))) cout << "Neispravne koordinate. Pokusajte ponovo (izlaz mora biti uz ivicu)" << endl;
		}
		izlaz = static_cast<int>(prva * drugaDim + druga);
		
		stvaranjeGrafa(graf, velicina);
		return velicina;
	}
}

void meniUkloniZid(Elem** graf) {
	if (graf == nullptr) {
		cout << "Ne postoji lavirint u memoriji" << endl;
	}
	else {
		float prva = -1;
		float druga = -1;
		float treca = -1;
		float cetvrta = -1;
		cout << "Unesite koordinate koje zelite spojiti putem (ukloniti izmedju njih zid) - prva dimenzija mora biti u rasponu od 0 do " << prvaDim << ", a druga dimenzija mora biti u rasponu od 0 do " << drugaDim << endl;
		cout << "(unesite 0 za prvu koordinatu za prekid programa, -1 za korak unazad):" << endl;
		while ((prva < 0) || !isInteger(prva) || (prva >= prvaDim) || (druga < 0) || !isInteger(druga) || (druga >= drugaDim) || (treca < 0) || !isInteger(treca) || (treca >= prvaDim) || (cetvrta < 0) || !isInteger(cetvrta) || (cetvrta >= drugaDim) || ((1 != abs(prva - treca)) && (1 != abs(druga - cetvrta)))) {
			cin >> prva >> druga >> treca >> cetvrta;
			system("CLS");
			//if (prva == 0) exit(0);
			if (prva == -1) return;
			if ((prva < 0) || !isInteger(prva) || (druga < 0) || !isInteger(druga) || (treca < 0) || !isInteger(treca) || (cetvrta < 0) || !isInteger(cetvrta)) cout << "Neispravne koordinate. Pokusajte ponovo (koordinate moraju biti pozitivan celobobrojan brojevi)." << endl;
			if ((prva >= prvaDim) || (druga >= drugaDim)) cout << "Neispravne koordinate. Pokusajte ponovo (kordinate moraju biti manje od zadatih dimenzija)" << endl;
			if ((1 != abs(prva-treca)) && (1 != abs(druga-cetvrta))) cout << "Neispravne koordinate. Pokusajte ponovo (koordinate moraju da budu susedne)" << endl;
		}
		unsigned int prvaKoord = static_cast<int>(prva * drugaDim + druga);
		unsigned int drugaKoord = static_cast<int>(treca * drugaDim + cetvrta);
		dodajGranu(graf, prvaKoord, drugaKoord);
	}
}

void meniIspis(Elem** graf) {
	while (1) {
		if (graf == nullptr) {
			cout << "Ne postoji lavirint u memoriji" << endl;
		}
		else {
			for (int i = 0; i < velicina; i++) {
				// prvi red
				if ((i % drugaDim) == 0) {
					for (int j = i; j < (i + drugaDim); j++) {
						cout << "+";
						if (j < drugaDim) {
							cout << "--";
						}
						else {
							Elem* tmp = graf[j];
							while ((tmp != nullptr) && (getCvor(tmp) < (j - drugaDim))) {
								tmp = getSled(tmp);
							}
							if ((tmp == nullptr) || (getCvor(tmp) > (j - drugaDim))) {
								cout << "--";
							}
							else {
								cout << "  ";
							}
						}
						if ((j % drugaDim) == (drugaDim - 1)) cout << "+" << endl;
					}
				}

				// drugi red
				if ((i % drugaDim) == 0) {
					cout << "|";
				}
				else {
					Elem* tmp = graf[i];
					while ((tmp != nullptr) && (getCvor(tmp) < (i - 1))) {
						tmp = getSled(tmp);
					}
					if ((tmp == nullptr) || (getCvor(tmp) > (i - 1))) {
						cout << "|";
					}
					else {
						cout << " ";
					}
				}
				if (i == ulaz) {
					cout << "oo";
				}
				else if (i == izlaz) {
					cout << "xx";
				}
				else {
					cout << "  ";
				}
				if ((i % drugaDim) == (drugaDim - 1)) { 
					cout << "|" << endl;
				}
			}
			
		}
		for (int i = 0; i < drugaDim; i++) {
			cout << "+--";
		}
		cout << "+" << endl;
		cout << "Unesite 0 za prekid programa ili -1 za korak unazad" << endl;
		float a;
		cin >> a;
		system("CLS");
		if (a == 0) exit(0);
		if (a == -1) return;
	}
}

void ResiLavirint(Elem** graf) {
	if (graf == nullptr) {
		cout << "Ne postoji lavirint u memoriji" << endl;
	}
	else {
		unsigned int** matrDostiznosti = new unsigned int* [velicina];
		unsigned int** matrPrethodnika = new unsigned int* [velicina];
		for (unsigned int i = 0; i < velicina; i++) {
			matrDostiznosti[i] = new unsigned int[velicina];
			matrPrethodnika[i] = new unsigned int[velicina];
			for (unsigned int j = 0; j < velicina; j++) {
				if (i == j) {
					matrDostiznosti[i][j] = 0;
				}
				else {
					matrDostiznosti[i][j] = UINT_MAX/2;
				}
				matrPrethodnika[i][j] = -1;
			}
		}
		for (unsigned int i = 1; i < velicina; i++) {
			Elem* tmp = graf[i];
			while ((tmp != nullptr) && getCvor(tmp) < i) {
				unsigned int j = getCvor(tmp);
				matrDostiznosti[i][j] = 1;
				matrPrethodnika[i][j] = i;
				matrDostiznosti[j][i] = 1;
				matrPrethodnika[j][i] = j;
				tmp = getSled(tmp);
			}
		}
		unsigned int m = 0;
		unsigned int** D = new unsigned int* [velicina];
		unsigned int** P = new unsigned int* [velicina];
		for (unsigned int i = 0; i < velicina; i++) {
			D[i] = new unsigned int[velicina];
			P[i] = new unsigned int[velicina];
			for (unsigned int j = 0; j < velicina; j++) {
				D[i][j] = matrDostiznosti[i][j];
				P[i][j] = matrPrethodnika[i][j];
			}
		}
		while ((m < velicina) && (matrDostiznosti[ulaz][izlaz] == (UINT_MAX/2))) {
			for (unsigned int k = 0; k < velicina; k++) {
				for (unsigned int i = 0; i < velicina; i++) {
					if (matrDostiznosti[i][k] != (UINT_MAX/2)) {
						for (unsigned int j = 0; j < velicina; j++) {
							if (matrDostiznosti[i][j] > (matrDostiznosti[i][k] + matrDostiznosti[k][j])) {
								P[i][j] = matrPrethodnika[k][j];
								D[i][j] = matrDostiznosti[i][k] + matrDostiznosti[k][j];
							}
						}
					}
				}
			}
			++m;
			for (unsigned int i = 0; i < velicina; i++) {
				for (unsigned int j = 0; j < velicina; j++) {
					matrDostiznosti[i][j] = D[i][j];
					matrPrethodnika[i][j] = P[i][j];
				}
			}
		}
		for (unsigned int i = 0; i < velicina; i++) {
			delete[] D[i];
			delete[] P[i];
		}
		for (unsigned int i = 0; i < velicina; i++) {
			for (unsigned int j = 0; j < velicina; j++) {
				if (matrDostiznosti[i][j] == (UINT_MAX/2)) {
					cout << -1;
				}
				else {
					cout << matrDostiznosti[i][j] << " ";
				}
			}
			cout << endl;
		}
		for (unsigned int i = 0; i < velicina; i++) {
			for (unsigned int j = 0; j < velicina; j++) {
				if (matrPrethodnika[i][j] == (UINT_MAX / 2)) {
					cout << -1;
				}
				else {
					cout << matrPrethodnika[i][j] << " ";
				}
			}
			cout << endl;
		}
		if (matrPrethodnika[ulaz][izlaz] == -1) {
			cout << "Izlaz nije dostizan od ulaza" << endl;
		}
		else {
			unsigned int t = matrPrethodnika[izlaz][ulaz];
			cout << "(" << floor(ulaz / drugaDim) << ", " << ulaz % drugaDim << ") -> ";
			while (t != -1) {
				cout << "(" << floor(t / drugaDim) << ", " << t % drugaDim << ") -> ";
				t = matrPrethodnika[izlaz][matrPrethodnika[izlaz][t]];
			}
			cout << "(" << floor(izlaz / drugaDim) << ", " << izlaz % drugaDim << ")" << endl;
		}
	}
}

void meniLavirint() {
	float izbor = 1;
	while (izbor) {
		cout << "Izaberite opciju:" << endl;
		cout << "[1] Stvarnje lavirinta ";
		if (graf == nullptr) {
			cout << "(nema nijednog lavirinta u memoriji)" << endl;
		}
		else {
			cout << "(Vec postoji lavirint u memoriji)" << endl;
		}
		cout << "[2] Dodaj granu (ukloni zid)" << endl;
		cout << "[3] Ispis lavirinta" << endl;
		cout << "[4] Resavanje lavirinta" << endl;
		cout << "Upisite 0 za prekid programa ili -1 za povratak unazad" << endl;
		if ((izbor > 5) || (izbor < 0) || !isInteger(izbor)) cout << "Neispravan izbor. Pokusajte ponovo." << endl;
		cin >> izbor;
		system("CLS");

		if (izbor == -1) return;

		if (isInteger(izbor)) {
			switch (int izb = static_cast<int>(izbor)) {
			case 1:
				velicina = meniStvaranjeLavirinta(graf);
				break;
			case 2:
				meniUkloniZid(graf);
				break;
			case 3:
				meniIspis(graf);
				break;
			case 4:
				ResiLavirint(graf);
				break;
			}
		}
	}
}

void meni() {
	float izbor = 1;
	while (izbor) {
		cout << "Izaberite opciju" << endl;
		cout << "[1] Graf - 1. zadatak" << endl;
		cout << "[2] Lavirint - 2. zadatak" << endl;
		cout << "Upisite 0 za prekid programa" << endl;
		if ((izbor > 2) || (izbor < 0) || !(isInteger(izbor))) cout << "Neispravan izbor. Pokusajte ponovo." << endl;
		cin >> izbor;
		system("CLS");
		if (isInteger(izbor)) {
			switch (int izb = static_cast<int>(izbor)) {
			case 1:
				meniGraf();
				break;
			case 2:
				meniLavirint();
				break;
			}
		}
	}
}

int main() {

	meni();

	return 0;
}