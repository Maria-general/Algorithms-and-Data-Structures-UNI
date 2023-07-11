#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct Elem {
	unsigned int cvor;
	Elem* sled;
	Elem(unsigned int cv) : cvor(cv), sled(nullptr) {}
};

unsigned int getCvor(Elem* ls) {
	return ls->cvor;
}

Elem* getSled(Elem* ls) {
	return ls->sled;
}

static Elem** graf = nullptr;
static unsigned int obrisaniCvorovi = 0;
static unsigned int velicina = 0;

bool isInteger(float a) {
	return a == floor(a);
}

void stvaranjeGrafa(Elem**& graf, unsigned int velicina) {
	Elem** tmp = new Elem * [velicina];
	for (int i = 0; i < velicina; i++) {
		tmp[i] = nullptr;
	}
	graf = tmp;
}

int meniStvaranjeGrafa(Elem**& graf) {
	if (graf != nullptr) {
		cout << "VEC POSTOJI GRAF U MEMORIJI" << endl;
		return ::velicina;
	}
	else {
		float unetaVelicina = 0;
		cout << "Unesite broj cvorova grafa (0 za prekid programa, -1 za korak unazad):" << endl;
		while ((unetaVelicina <= 0) || !isInteger(unetaVelicina)) {
			cin >> unetaVelicina;
			system("CLS");
			if (unetaVelicina == 0) exit(0);
			if (unetaVelicina == -1) return ::velicina;
			if ((unetaVelicina <= 0) || !isInteger(unetaVelicina)) cout << "Neispravan broj. Pokusajte ponovo (mora biti pozitivan celobobrojan broj)." << endl;
		}
		int velicina = static_cast<int>(unetaVelicina);
		stvaranjeGrafa(graf, velicina);
		return velicina;
	}
	
}

void dodajCvor(Elem**& graf) {
	if (graf == nullptr) {
		cout << "Ne postoji graf u memoriji" << endl;
	}
	else {
		Elem** tmp = new Elem *[velicina + 1];
		copy(graf, graf + velicina, tmp);
		delete[] graf;
		graf = tmp;
		graf[velicina] = nullptr;
		velicina++;
	}
}

void ukloniCvor(Elem** graf, unsigned int indeks) {
	if (obrisaniCvorovi & (1 << indeks)) {
		while (1) {
			cout << "Taj cvor je vec obrisan" << endl;
			cout << "Unesite 0 za prekid programa ili -1 za vracanje na meni" << endl;
			int a;
			cin >> a;
			if (a == 0) exit(0);
			if (a == -1) return;
			system("CLS");
		}
	}
	else {
		void ukloniGranu(Elem**, unsigned int, unsigned int);
		while (graf[indeks] != nullptr) {
			ukloniGranu(graf, indeks, graf[indeks]->cvor);
		}
		obrisaniCvorovi |= 1 << indeks;
	}
}

void meniUkloniCvor(Elem** graf) {
	if (graf == nullptr) {
		cout << "Ne postoji graf u memoriji" << endl;
	}
	else {
		float unetiIndeks = 0;
		cout << "Unesite redni br. cvora, mora biti u rasponu od 1 do " << velicina << " (0 za prekid programa, -1 za korak unazad):" << endl;
		while ((unetiIndeks <= 0) || !isInteger(unetiIndeks) || (unetiIndeks > velicina)) {
			cin >> unetiIndeks;
			system("CLS");
			if (unetiIndeks == 0) exit(0);
			if (unetiIndeks == -1) return;
			if ((unetiIndeks < 0) || !isInteger(unetiIndeks) || (unetiIndeks > velicina)) cout << "Neispravan broj. Pokusajte ponovo (mora biti celobrojan broj od 1 do " << velicina << ")." << endl;
		}
		int indeks = static_cast<int>(unetiIndeks);
		ukloniCvor(graf, indeks - 1);
	}
}

void dodajGranu(Elem** graf, unsigned int prvi, unsigned int drugi) {
	Elem* tmp, *novi;

	tmp = graf[prvi];
	if ((graf[prvi] == nullptr) || (graf[prvi]->cvor > drugi)) {
		tmp = new Elem(drugi);
		tmp->sled = graf[prvi];
		graf[prvi] = tmp;
	}
	else {
		while ((tmp->sled != nullptr) && (tmp->sled->cvor < drugi)) {
			tmp = tmp->sled;
		}
		if ((tmp->sled == nullptr) || (tmp->sled->cvor > drugi)) {
			novi = new Elem(drugi);
			novi->sled = tmp->sled;
			tmp->sled = novi;
		}
		else {
			while (1) {
				system("CLS");
				cout << "Vec postoji grana izmedju datih cvorova" << endl;
				cout << "Unesite 0 za prekid programa ili -1 za korak unazad" << endl;
				int a;
				cin >> a;
				if (a == 0) exit(0);
				if (a == -1) return;
			}
		}
	}

	tmp = graf[drugi];
	if ((graf[drugi] == nullptr) || (graf[drugi]->cvor > prvi)) {
		tmp = new Elem(prvi);
		tmp->sled = graf[drugi];
		graf[drugi] = tmp;
	}
	else {
		while ((tmp->sled != nullptr) && (tmp->sled->cvor < prvi)) {
			tmp = tmp->sled;
		}
		novi = new Elem(prvi);
		novi->sled = tmp->sled;
		tmp->sled = novi;
	}
}

void meniDodajGranu(Elem** graf) {
	if (graf == nullptr) {
		cout << "Ne postoji graf u memoriji" << endl;
	}
	else {
		float prvi = 0, drugi = 0;
		int prviCvor = 1, drugiCvor = 1;
		cout << "Unesite redni br. cvorova koje zelite spojiti granom, mora biti u rasponu od 1 do " << velicina << " (za prvi cvor unesite 0 za prekid programa, -1 za korak unazad):" << endl;
		while ((prvi <= 0) || !isInteger(prvi) || (prvi > velicina) || (drugi <= 0) || !isInteger(drugi) || (drugi > velicina) || ((obrisaniCvorovi >> (prviCvor - 1)) == 1) || ((obrisaniCvorovi >> (drugiCvor - 1)) == 1)) {
			cin >> prvi >> drugi;
			prviCvor = static_cast<int>(prvi);
			drugiCvor = static_cast<int>(drugi);
			system("CLS");
			if (prvi == 0) exit(0);
			if (prvi == -1) return;
			if ((prvi <= 0) || !isInteger(prvi) || (prvi > velicina) || (drugi <= 0) || !isInteger(drugi) || (drugi > velicina)) {
				cout << "Neispravan broj. Pokusajte ponovo (mora biti celobrojan broj od 1 do " << velicina << ")." << endl;
			}
			else if ((obrisaniCvorovi >> (prviCvor - 1)) == 1) {
				cout << "Prvi cvor je obrisan. Pokusajte ponovo." << endl;
			}
			else if ((obrisaniCvorovi >> (drugiCvor - 1)) == 1) {
				cout << "Drugi cvor je obrisan. Pokusajte ponovo." << endl;
			}
			else {
				dodajGranu(graf, prvi - 1, drugi - 1);
			}
		}
	}
}

void ukloniGranu(Elem** graf, unsigned int prvi, unsigned int drugi) {
	Elem* stari, * novi;
	novi = graf[prvi];
	stari = graf[prvi];
	if (graf[prvi]->cvor == drugi) {
		graf[prvi] = novi->sled;
		delete novi;
	}
	else {
		novi = graf[prvi];
		while ((novi != nullptr) && (novi->cvor < drugi)) {
			stari = novi;
			novi = novi->sled;
		}
		if ((novi == nullptr) || (novi->cvor > drugi)) {
			while (1) {
				system("CLS");
				cout << "Ne postoji grana izmedju datih cvorova" << endl;
				cout << "Unesite 0 za prekid programa ili -1 za korak unazad" << endl;
				int a;
				cin >> a;
				if (a == 0) exit(0);
				if (a == -1) return;
			}
		}
		else {
			stari->sled = novi->sled;
			delete novi;
		}
	}
	novi = graf[drugi];
	stari = graf[drugi];
	if (graf[drugi]->cvor == prvi) {
		graf[drugi] = novi->sled;
		delete novi;
	}
	else {
		novi = graf[drugi];
		while (novi->cvor < prvi) {
			stari = novi;
			novi = novi->sled;
		}
		stari->sled = novi->sled;
		delete novi;
	}
}

void meniUkloniGranu(Elem** graf) {
	if (graf == nullptr) {
		cout << "Ne postoji graf u memoriji" << endl;
	}
	else {
		float prvi = 0, drugi = 0;
		int prviCvor = 1, drugiCvor = 1;
		cout << "Unesite redni br. cvorova izmedju kojih se nalazi zeljenja grana, mora biti u rasponu od 1 do " << velicina << " (za prvi cvor unesite 0 za prekid programa, -1 za korak unazad):" << endl;
		while ((prvi <= 0) || !isInteger(prvi) || (prvi > velicina) || (drugi <= 0) || !isInteger(drugi) || (drugi > velicina) || ((obrisaniCvorovi >> (prviCvor - 1)) == 1) || ((obrisaniCvorovi >> (drugiCvor - 1)) == 1)) {
			cin >> prvi >> drugi;
			prviCvor = static_cast<int>(prvi);
			drugiCvor = static_cast<int>(drugi);
			system("CLS");
			if (prvi == 0) exit(0);
			if (prvi == -1) return;
			if ((prvi <= 0) || !isInteger(prvi) || (prvi > velicina) || (drugi <= 0) || !isInteger(drugi) || (drugi > velicina)) {
				cout << "Neispravan broj. Pokusajte ponovo (mora biti celobrojan broj od 1 do " << velicina << ")." << endl;
			}
			else if ((obrisaniCvorovi >> (prviCvor - 1)) == 1) {
				cout << "Prvi cvor je obrisan. Pokusajte ponovo." << endl;
			}
			else if ((obrisaniCvorovi >> (drugiCvor - 1)) == 1) {
				cout << "Drugi cvor je obrisan. Pokusajte ponovo." << endl;
			}
			else {
				ukloniGranu(graf, prviCvor - 1, drugiCvor - 1);
			}
		}
	}
}

void ispisGrafa(Elem** graf) {
	while (1) {
		if (graf == nullptr) {
			cout << "Ne postoji graf u memoriji" << endl;
		}
		else {
			unsigned int tmpObrisani = obrisaniCvorovi;
			for (int i = 0; i < velicina; i++) {
				if (!(tmpObrisani & 1)) {
					cout << "[" << i + 1 << "]";
					Elem* tmp = graf[i];
					while (tmp != nullptr) {
						cout << " -> " << tmp->cvor + 1;
						tmp = tmp->sled;
					}
					cout << endl;
				}
				tmpObrisani >>= 1;
			}
		}
		cout << "Unesite 0 za prekid programa ili -1 za korak unazad" << endl;
		float a;
		cin >> a;
		system("CLS");
		if (a == 0) exit(0);
		if (a == -1) return;
	}
}

void izbrisiGraf(Elem**& graf) {
	for (int i = 0; i < velicina; i++) {
		ukloniCvor(graf, i);
	}
	delete[] graf;
	graf = nullptr;
	obrisaniCvorovi = 0;
	velicina = 0;
}

void meniGraf() {
	float izbor = 1;
	while (izbor) {
		cout << "Izaberite opciju:" << endl;
		cout << "[1] Stvaranje grafa ";
		if (graf == nullptr) {
			cout << "(nema nijednog grafa u memoriji)" << endl;
		}
		else {
			cout << "(Vec postoji graf u memoriji)" << endl;
		}
		cout << "[2] Dodaj cvor" << endl;
		cout << "[3] Ukloni cvor" << endl;
		cout << "[4] Dodaj granu" << endl;
		cout << "[5] Ukloni granu" << endl;
		cout << "[6] Ispis reprezentacije grafa" << endl;
		cout << "[7] Brisanje grafa" << endl;
		cout << "Upisite 0 za prekid programa ili -1 za povratak unazad" << endl;
		if ((izbor > 7) || (izbor < 0) || !isInteger(izbor)) cout << "Neispravan izbor. Pokusajte ponovo." << endl;
		cin >> izbor;
		system("CLS");

		if (izbor == -1) return;

		if (isInteger(izbor)) {
			switch (int izb = static_cast<int>(izbor)) {
			case 1:
				velicina = meniStvaranjeGrafa(graf);
				break;
			case 2:
				dodajCvor(graf);
				break;
			case 3:
				meniUkloniCvor(graf);
				break;
			case 4:
				meniDodajGranu(graf);
				break;
			case 5:
				meniUkloniGranu(graf);
				break;
			case 6:
				ispisGrafa(graf);
				break;
			case 7:
				izbrisiGraf(graf);
				break;
			}
		}
	}
}

/*class Graf { // neusmeren
public:
	Graf(unsigned int n);

	void dodajCvor();
	void ukloniCvor(unsigned int indeks);
	void dodajGranu();
	void ukloniGranu();
private:
	struct Elem {
		unsigned int cvor;
		Elem* sled;
		Elem(unsigned int cv) : cvor(cv), sled(nullptr) {}
	};
	Elem** listaSusednosti = nullptr;
	unsigned int velicina = 0;
};

Graf::Graf(unsigned int n)
{
	Elem** p = new Elem * [n];
	listaSusednosti = p;
	velicina = n;
}

void Graf::dodajCvor()
{
	Elem** p = new Elem * [velicina + 1];
	copy(listaSusednosti, listaSusednosti + velicina, p);
	delete[] listaSusednosti;
	listaSusednosti = p;
}

void Graf::ukloniCvor(unsigned int indeks)
{
	Elem* trenutni = listaSusednosti[indeks];
	Elem* sledeci;
	while (trenutni != nullptr) {
		unsigned int sused = trenutni->cvor;
		Elem* lstSused = listaSusednosti[sused];
		while (lstSused->cvor != indeks) {
			lstSused = lstSused->sled;
		}
		Elem* zaBrisanje = lstSused->sled;
		lstSused->sled = zaBrisanje->sled;
		lstSused->cvor = zaBrisanje->cvor;
		delete zaBrisanje;

		sledeci = trenutni->sled;
		delete trenutni;
		trenutni = sledeci;
	}
	listaSusednosti[indeks] = nullptr;

	// da li trebam da samnjim citav niz pokazivaca?
}*/
