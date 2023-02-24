#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
//#include "Vehicul.h"
//#include "Masina.h"
//#include "Autocar.h"
#include <vector>
#include<string>
#include<sstream>
#include<list>
#include<fstream>
using namespace std;


class Vehicul {
private:
	const string marca = "ANONIM";
	bool inchiriat[365];
	int* zileInchiriere = NULL;
	int nrZileInchiriere = 0;
	float pret = 0;
	static int nrVehicule;

public:
	const string getmarca() {
		return this->marca;
	}
	bool getInchiriat() {
		return this->inchiriat;
	}
	int* getZileInchiriere() {
		return this->zileInchiriere;
	}
	int getNrZile() {
		return this->nrZileInchiriere;
	}
	float getPret() {
		return this->pret;
	}

	void setPret(float pret) {
		if (pret > 1000) {
			this->pret = pret;
		}
		else cout << "pretul trb sa fie mai mare de 1000";
	}
	void setZileInchirire(int nrZileInchiriere, int* zileInchiriere) {
		delete[]this->zileInchiriere;
		this->nrZileInchiriere = nrZileInchiriere;
		fill(begin(this->inchiriat), end(this->inchiriat), 0);
		this->zileInchiriere = new int[this->nrZileInchiriere];
		for (int i = 0; i < this->nrZileInchiriere; i++) {
			this->zileInchiriere[i] = zileInchiriere[i];
			this->inchiriat[zileInchiriere[i]] = 1;
		}
	}

	void addZileInchiriere(int nrZile, int* zile) {
		int* zileInchiriereVechi = zileInchiriere;
		nrZileInchiriere += nrZile;
		delete[]zileInchiriere;
		zileInchiriere = new int[nrZileInchiriere];
		for (int i = 0; i < nrZileInchiriere - nrZile; i++)
			zileInchiriere[i] = zileInchiriereVechi[i];
		int j = 0;
		for (int i = nrZileInchiriere - nrZile; i < nrZileInchiriere; i++){
			if (this->inchiriat[zile[j]] == 1)
				cout << "in ziua " << zile[j] << " vehiculul e deja inchiriat";
			else {
				zileInchiriere[i] = zile[j]; 
				this->inchiriat[zileInchiriere[i]] = 1;
			}
			j++;
		}
		if (zileInchiriereVechi == nullptr)
			delete[]zileInchiriereVechi;
	}

	float PretSaptamana() {
		return this->pret * 7 - 1 / 10 * this->pret;
	}
	float PretLuna() {
		return (this->pret * 7 * 4 - 1 / 5 * (this->pret));
	}
	Vehicul(string marca) :marca(marca) {
		nrVehicule++;
		for (int i = 0; i < 365; i++) this->inchiriat[i] = 0;
		this->zileInchiriere = NULL;
		this->nrZileInchiriere = 0;
		this->pret = 0;

	}

	Vehicul(string marca, int* zileInchiriere, int nrZileInchiriere, float pret) :marca(marca) {
		nrVehicule++;
		fill(begin(this->inchiriat), end(this->inchiriat), 0);
		if (nrZileInchiriere > 0 && zileInchiriere != NULL) {
			this->nrZileInchiriere = nrZileInchiriere;
			this->zileInchiriere = new int[this->nrZileInchiriere];
			for (int i = 0; i < this->nrZileInchiriere; i++) {
				this->zileInchiriere[i] = zileInchiriere[i];
				this->inchiriat[zileInchiriere[i]] = 1;
			}
			this->pret = pret;
		}
		else {
			this->zileInchiriere = NULL;
			this->nrZileInchiriere = 0;
		}
	}

	Vehicul(const Vehicul& a) :marca(a.marca) {
		nrVehicule++;
		if (a.nrZileInchiriere > 0 && a.zileInchiriere != NULL) {
			fill(begin(this->inchiriat), end(this->inchiriat), 0);
			this->nrZileInchiriere = a.nrZileInchiriere;
			this->zileInchiriere = new int[this->nrZileInchiriere];
			for (int i = 0; i < this->nrZileInchiriere; i++) {
				this->zileInchiriere[i] = a.zileInchiriere[i];
				this->inchiriat[zileInchiriere[i]] = 1;
			}
		}
		else {
			this->zileInchiriere = NULL;
			this->nrZileInchiriere = 0;
		}
		this->pret = a.pret;
	}

	Vehicul& operator=(const Vehicul& a) {
		if (this != &a) {
			if (a.nrZileInchiriere > 0 && a.zileInchiriere != NULL) {
				delete[]this->zileInchiriere;
				fill(begin(this->inchiriat), end(this->inchiriat), 0);
				this->nrZileInchiriere = a.nrZileInchiriere;
				this->zileInchiriere = new int[this->nrZileInchiriere];
				for (int i = 0; i < this->nrZileInchiriere; i++) {
					this->zileInchiriere[i] = a.zileInchiriere[i];
					this->inchiriat[zileInchiriere[i]] = 1;
				}
			}
			else {
				this->zileInchiriere = NULL;
				this->nrZileInchiriere = 0;
			}
			this->pret = a.pret;
		}
		return *this;
	}
	

	friend ostream& operator<<(ostream& out, Vehicul& a) {
		out << "\n Marca: " << a.marca;
		out << "\n Pretul: " << a.pret;
		out << "\n nrZileInchiriere: " << a.nrZileInchiriere;
		out << "\n ZileInchiriere ";
		if (a.nrZileInchiriere > 0) {
			for (int i = 0; i < a.nrZileInchiriere; i++)
				out << a.zileInchiriere[i] << " ";
		}
		else out << "nu este inchiriata pe nicio zi";
		return out;
	}

	friend istream& operator>>(istream& in, Vehicul& a) {
		cout << "\n introduceti marca: ";
		//in.ignore(); getline(in, a.marca);
		cout << "\n introduceti pretul: ";
		in >> a.pret;
		cout << "\n introduceti nr zile inchiriate: ";
		in >> a.nrZileInchiriere;
		if (a.nrZileInchiriere > 0 && a.zileInchiriere != NULL)	{
			cout << "introduceti zilele pt inchiriere ";
			for (int i = 0; i < a.nrZileInchiriere; i++){
				in >> a.zileInchiriere[i];
				a.inchiriat[a.zileInchiriere[i]] = 1;
			}
		}
	}

	bool operator[](int pozitie) {
		if (pozitie >= 0)
			return this->inchiriat[pozitie];
		else return "pozitia nu exista";
	}
	Vehicul operator+(float val) {
		Vehicul copie = *this;
		copie.pret += val;
		return copie;
	}
	Vehicul& operator++() {
		this->pret++;
		return *this;
	}
	Vehicul operator++(int) {
		Vehicul copie = *this;
		this->pret++;
		return copie;
	}
	Vehicul& operator-(int val) {
		for (int i = 1; i <= val; i++) {
			if (this->inchiriat[i] == 1) 
				this->inchiriat[i] = 0;
		}
		return *this;
	}
	bool operator>(Vehicul a) {
		return this->pret > a.pret;
	}

	~Vehicul() {
		if (zileInchiriere != NULL) {
			delete[]this->zileInchiriere;
		}
	}

	virtual string toString() {
		return "\n Vehicul";
	};
	virtual string getUnique() {
		return "\n Vehicul";
	};
	virtual void setAttributes() {};
	virtual Vehicul operator!() { return *this; };

};
class IVehicul:public Vehicul {
public:
	virtual string toString() = 0;
	virtual string getUnique() = 0;
};

enum class Culoare {
	gri, negru, alb, albastru
};

class DouaRoti :public Vehicul {
public:
	bool isTrike;
	Culoare culoare;

	DouaRoti(string marca) :Vehicul(marca) {
		isTrike = false;
		culoare = Culoare::negru;
	}

	DouaRoti(string marca, int* zileInchiriere, int nrZileInchiriere, float pret, bool isTrike, Culoare culoare) 
		:Vehicul(marca, zileInchiriere, nrZileInchiriere, pret) {
		this->isTrike = isTrike;
		this->culoare = culoare;
	}

	~DouaRoti() {
	}

	DouaRoti(DouaRoti& a) : Vehicul::Vehicul(a) {
		this->isTrike = a.isTrike;
		this->culoare = a.culoare;
	}

	void operator=(DouaRoti a) {
		this->Vehicul::operator=(a);
		this->isTrike = a.isTrike;
		this->culoare = a.culoare;
	}
	bool getIsTrike() {
		return this->isTrike;
	}
	string toString() {
		return "DouaRoti";
	}
	string getUnique() {
		return "\n Vehicul";
	}
};

class Motocicleta :public DouaRoti {
public:
	bool atas;

	Motocicleta(string marca) :DouaRoti(marca) {
		this->atas = false;
	}

	Motocicleta(string marca, int* zileInchiriere, int nrZileInchiriere, float pret, bool isTrike, Culoare culoare,bool atas)
		:DouaRoti(marca, zileInchiriere, nrZileInchiriere, pret,isTrike,culoare) {
		this->atas = atas;
	}

	~Motocicleta() {
	}

	Motocicleta(Motocicleta& a) : DouaRoti::DouaRoti(a) {
		this->atas = a.atas;
	}

	void operator=(Motocicleta a) {
		this->Vehicul::operator=(a);
		this->atas = a.atas;
	}
	bool getAtas() {
		return this->atas;
	}
	string toString() {
		return "Marca: " + this->getmarca() +
			"\nPret: " + to_string(this->getPret()) +
			"\nNr zile inchiriere: " + to_string(this->getNrZile()) +
			"\nEste tip Trike: " + (this->getIsTrike() ? "Da" : "Nu") +
			"\nAtas: " + (this->getAtas() ? "Da" : "Nu") +
			"\n";
	}
	string getUnique() {
		return "\nPret: " + to_string(this->getPret()) +
			"\nEste tip Trike: " + (this->getIsTrike() ? "Da" : "Nu") +
			"\nAtas: " + (this->getAtas() ? "Da" : "Nu") +
			"\n";
	}
	Vehicul operator!() {
		if (this->atas == 1) {
			this->atas = 0;
		}
		else {
			this->atas = 1;
		}
		return *this;
	}
	void setAtas(bool val) {
		this->atas = val;
	}
	void setAttributes() {
		bool boolIn;
		float fIn;
		int intIn;
		int* zile;
		cout << "\n introduceti pretul: ";
		cin >> fIn;
		setPret(fIn);
		cout << "\n introduceti nr zilelor inchiriate: ";
		cin >> intIn;
		zile = new int[intIn];
		cout << "\n introduceti zilele de inchiriere: ";
		for (int i = 0; i < intIn; i++)
			cin >> zile[i];
		setZileInchirire(intIn, zile);
		delete[]zile;
		cout << "\n introduceti daca are atas 1-da, 0-nu: ";
		cin >> boolIn;
		setAtas(boolIn);
	}
};

class VMari :public Vehicul {
public:
	bool roataRezerva;

	VMari(string marca) :Vehicul(marca) {
		this->roataRezerva = 0;
	}

	VMari(string marca, int* zileInchiriere, int nrZileInchiriere, float pret, bool roataRezerva)
		:Vehicul(marca, zileInchiriere, nrZileInchiriere, pret) {
		this->roataRezerva = roataRezerva;
	}

	~VMari() {
	}

	VMari(VMari& a) : Vehicul::Vehicul(a) {
		this->roataRezerva = a.roataRezerva;
	}

	void operator=(VMari a) {
		this->Vehicul::operator=(a);
		this->roataRezerva = a.roataRezerva;
	}
	bool getRoata() {
		return this->roataRezerva;
	}
	string toString() {
		return "VMari";
	}
	string getUnique() {
		return "VMari";
	}
};

class Autocar : public VMari {
private:
	int nrLocuri;
	bool microfon;
public:

	Autocar(string marca) :VMari(marca) {
		this->nrLocuri = 0;
		this->microfon = 0;
	}

	Autocar(string marca, int* zileInchiriere, int nrZileInchiriere, float pret, bool roataRezerva, int nrLocuri,bool microfon) :
		VMari(marca, zileInchiriere, nrZileInchiriere, pret,roataRezerva) {
		this->nrLocuri = nrLocuri;
		this->microfon = microfon;
	}

	Autocar(Autocar& a) : VMari::VMari(a) {
		this->nrLocuri = a.nrLocuri;
		this->microfon = a.microfon;
	}

	void operator=(Autocar a) {
		this->VMari::operator=(a);
		this->nrLocuri = a.nrLocuri;
		this->microfon = a.microfon;
	}
	bool getMicrofon() { 
		return this->microfon; 
	}
	int getNrLocuri() {
		return this->nrLocuri;
	}
	string toString() {
		return "Marca: " + this->getmarca() +
			"\nPret: " + to_string(this->getPret()) +
			"\nNr zile inchiriere: " + to_string(this->getNrZile()) +
			"\nNrLocuri: " + to_string(this->getNrLocuri()) +
			"\nMicrofon: " + (this->getMicrofon() ? "Da" : "Nu") +
			"\nRoata rezerva: " + (this->getRoata() ? "Da" : "Nu") +
			"\n";
	}
	string getUnique() {
		return "\nNrLocuri: " + to_string(this->getNrLocuri()) +
			"\nMicrofon: " + (this->getMicrofon() ? "Da" : "Nu") +
			"\nRoata rezerva: " + (this->getRoata() ? "Da" : "Nu") +
			"\n";
	}
	Vehicul operator!() {
		if (this->microfon == 1) {
			this->microfon = 0;
		}
		else {
			this->microfon = 1;
		}
		return *this;
	}
	void setMicrofon(bool val) {
		this->microfon = val;
	}
	void setAttributes() {
		bool boolIn;
		float fIn;
		int intIn;
		int* zile;
		cout << "\n introduceti pretul: ";
		cin >> fIn;
		setPret(fIn);
		cout << "\n introduceti nr zilelor inchiriate: ";
		cin >> intIn;
		zile = new int[intIn];
		cout << "\n introduceti zilele de inchiriere: ";
		for (int i = 0; i < intIn; i++)
			cin >> zile[i];
		setZileInchirire(intIn, zile);
		delete[]zile;
		cout << "\n introduceti daca are microfon 1-da, 0-nu: ";
		cin >> boolIn;
		setMicrofon(boolIn);

	}
	~Autocar() {
	}
};
class Masina : public VMari {
private:
	bool remorca;//doar pe benzina

public:
	Masina(string marca) :VMari(marca) {
		this->remorca = 0;
	}

	Masina(string marca, int* zileInchiriere, int nrZileInchiriere, float pret, bool roataRezerva, int nrLocuri) :
		VMari(marca, zileInchiriere, nrZileInchiriere, pret, roataRezerva) {
		this->remorca = remorca;
	}

	Masina(Masina& a) : VMari::VMari(a) {
		this->remorca = a.remorca;
	}

	void operator=(Masina a) {
		this->VMari::operator=(a);
		this->remorca = a.remorca;
	}
	bool getRemorca() {
		return this->remorca;
	}
	void setRemorca(bool val) {
		this->remorca = val;
	}
	string toString() {
		return "Marca: " + this->getmarca() +
			"\nPret: " + to_string(this->getPret()) +
			"\nNr zile inchiriere: " + to_string(this->getNrZile()) +
			"\nRemorca: " + (this->getRemorca() ? "Da" : "Nu") +
			"\nRoata rezerva: " + (this->getRoata() ? "Da" : "Nu") +
			"\n";
	}
	string getUnique() {
		return"\nPret: " + to_string(this->getPret()) +
			"\nRemorca: " + (this->getRemorca() ? "Da" : "Nu") +
			"\nRoata rezerva: " + (this->getRoata() ? "Da" : "Nu") +
			"\n";
	}
	Vehicul operator!() {
		if (this->remorca == 1) {
			this->remorca = 0;
		}
		else {
			this->remorca = 1;
		}
		return *this;
	}
	void setAttributes() {
		bool boolIn;
		float fIn;
		int intIn;
		int* zile;
		cout << "\n introduceti pretul: ";
		cin >> fIn;
		setPret(fIn);
		cout << "\n introduceti nr zilelor inchiriate: ";
		cin >> intIn;
		zile = new int[intIn];
		cout << "\n introduceti zilele de inchiriere: ";
		for (int i = 0; i < intIn; i++)
			cin >> zile[i];
		setZileInchirire(intIn, zile);
		delete[]zile;
		cout << "\n introduceti daca are roata de rezerva 1-da, 0-nu: ";
		cin >> boolIn;
		setRemorca(boolIn);
	}
	~Masina() {
	}
};

class ParcAuto {
private:
	string numeParcAuto;
	string cod;
	int nrVehicule;
	vector<Vehicul*> vehicule;
public:
	string getNume() {
		return this->numeParcAuto;
	}
	int getNrVehicule() {
		return this->nrVehicule;
	}
	void setCod(string cod) {
		this->cod = cod;
	}
	string getCod() {
		return this->cod;
	}
	void setNume(string numeParcAuto) {
		if (numeParcAuto.size() > 2) {
			this->numeParcAuto = numeParcAuto;
		}
	}
	void setNrVehicule(int nrVehicule) {
		if (nrVehicule > 2)
			this->nrVehicule = nrVehicule;
	}
	

	ParcAuto() {
		this->numeParcAuto = "NULL";
		this->cod= "null";
		nrVehicule = 0;
	}

	ParcAuto(vector<Vehicul*> vehicule, int nrVehicule, string numeParcAuto, string cod) {
		this->nrVehicule = nrVehicule;
		this->vehicule = vehicule;
		this->numeParcAuto = numeParcAuto;
		this->cod=cod;
	}

	ParcAuto(const ParcAuto& p) {
		this->nrVehicule = p.nrVehicule;
		this->vehicule.assign(p.vehicule.begin(), p.vehicule.end());
		this->numeParcAuto = p.numeParcAuto;
		this->cod = p.cod;
	}

	ParcAuto& operator=(const ParcAuto& p) {
		if (this != &p) {
			this->nrVehicule = p.nrVehicule;
			this->vehicule.assign(p.vehicule.begin(), p.vehicule.end());
			this->numeParcAuto = p.numeParcAuto;
			this->cod = p.cod;
		}
		return *this;
	}
	
	void addToParcAuto(Vehicul* vehicul) {
		this->vehicule.push_back(vehicul);
	}

	~ParcAuto() {
		
	}

	friend ostream& operator<<(ostream& out, ParcAuto& p) {
		out << "\n Nume Parc Auto: " << p.numeParcAuto;
		out << "\n Cod:" << p.cod;
		out << " \n Numar Vehicule: " << p.nrVehicule;
		if (p.nrVehicule > 0) {
			for (int i = 0; i < p.nrVehicule; i++)
				out << p.vehicule[i] << " ";
		}
		else {
			out << "\n nu exista vehicule ";
		}
		return out;
	}

	friend istream& operator>>(istream& in, ParcAuto& p) {
		cout << "\n introduceti numele parcului: ";
		getline(in, p.numeParcAuto);
		cout << "\n introduceti codul: ";
		in >> p.cod;;
		cout << "\n introduceti nr de vehciule: "; in >> p.nrVehicule;
		if (p.nrVehicule > 0) {
			cout << "\n vehiculele sunt: ";
			//for (int i = 0; i < p.nrVehicule; i++)
				//in >> p.vehicule[i];
		}
		else cout << "nu exista vehicule";
	}
	explicit operator string() {
		return this->numeParcAuto;
	}
	bool operator >=(ParcAuto p) {
		return this->nrVehicule >= p.nrVehicule;
	}

};

class Contract {
private:
	string perioada[2];
	int nrVehicule;
	string* Vehicule;
	float* pret;//pret suma si mediu
public:
	string* getPerioada() {
		return this->perioada;
	}
	int getNrVehicule() {
		return this->nrVehicule;
	}
	string* getVehicule() {
		return this->Vehicule;
	}
	float* getPret() {
		return this->pret;
	}
	void setPerioada(string* perioada) {
		if (perioada != NULL)
			for (int i = 0; i < 2; i++)
				this->perioada[i] = perioada[i];
	}
	void setVehicule(int nrVehicule, string* Vehicule, float* pret) {
		if (nrVehicule > 0 && Vehicule != NULL && pret != NULL) {
			this->nrVehicule = nrVehicule;
			for (int i = 0; i < nrVehicule; i++) {
				this->Vehicule[i] = Vehicule[i];
				this->pret[i] = pret[i];
			}
		}
	}
	float sumaPret() {
		float suma = 0;
		for (int i = 0; i < this->nrVehicule; i++) {
			suma = suma + this->pret[i];
		}
		return suma;
	}
	float mediePret() {
		float suma = 0;
		for (int i = 0; i < this->nrVehicule; i++) {
			suma = suma + this->pret[i];
		}
		return suma / this->nrVehicule;
	}
	Contract() {
		for (int i = 0; i < 2; i++)this->perioada[i] = "null";
		this->nrVehicule = 0;
		this->Vehicule = NULL;
		this->pret = NULL;
	}
	Contract(string perioada[2], int nrVehicule, string* Vehicule, float* pret) {
		for (int i = 0; i < 2; i++)this->perioada[i] = perioada[i];
		this->nrVehicule = nrVehicule;
		if (nrVehicule > 0 && Vehicule != NULL) {
			this->Vehicule = new string[nrVehicule];
			this->pret = new float[nrVehicule];
			for (int i = 0; i < nrVehicule; i++) {
				this->Vehicule[i] = Vehicule[i];
				this->pret[i] = pret[i];
			}
		}
		else {
			this->Vehicule = NULL;
			this->pret = NULL;
		}
	}
	Contract(const Contract& c) {
		for (int i = 0; i < 2; i++)this->perioada[i] = c.perioada[i];
		this->nrVehicule = c.nrVehicule;
		if (c.nrVehicule > 0 && c.Vehicule != NULL) {
			this->Vehicule = new string[c.nrVehicule];
			this->pret = new float[c.nrVehicule];
			for (int i = 0; i < c.nrVehicule; i++) {
				this->Vehicule[i] = c.Vehicule[i];
				this->pret[i] = c.pret[i];
			}
		}
		else {
			this->Vehicule = NULL;
			this->pret = NULL;
		}

	}

	Contract& operator=(const Contract& c) {
		if (this != &c) {
			delete[]this->Vehicule;
			delete[] this->pret;
			for (int i = 0; i < 2; i++)this->perioada[i] = c.perioada[i];
			this->nrVehicule = c.nrVehicule;
			if (c.nrVehicule > 0 && c.Vehicule != NULL) {
				this->Vehicule = new string[c.nrVehicule];
				this->pret = new float[c.nrVehicule];
				for (int i = 0; i < c.nrVehicule; i++) {
					this->Vehicule[i] = c.Vehicule[i];
					this->pret[i] = c.pret[i];
				}
			}
			else {
				this->Vehicule = NULL;
				this->pret = NULL;
			}
			return *this;
		}
	}

	~Contract() {
		if (this->Vehicule != NULL) {
			delete[]this->Vehicule;
			delete[]this->pret;
		}
	}

	friend ostream& operator<<(ostream& out, Contract& c) {

		out << "\n Perioada contractului: ";
		for (int i = 0; i < 2; i++) out << c.perioada[i] << " ";
		out << "\n Nr autotursime inchiriate: " << c.nrVehicule;
		if (c.nrVehicule > 0) {
			out << "\n Vehiculele inchiriate sunt:  ";
			for (int i = 0; i < c.nrVehicule; i++)
				out << c.Vehicule[i] << " ";
			out << "\n Preturile:";
			for (int i = 0; i < c.nrVehicule; i++)
				out << c.pret[i] << " ";
		}
		else {
			out << "\n nu exista inchirieri ";
		}
		return out;
	}
	friend istream& operator>>(istream& in, Contract& c) {
		cout << "\n introduceti Perioada contractului: ";
		for (int i = 0; i < 2; i++) in >> c.perioada[i];
		cout << "\n introduceti nr de Vehicule inchiriate: "; in >> c.nrVehicule;
		if (c.nrVehicule > 0) {
			cout << "\n Preturile:";
			for (int i = 0; i < c.nrVehicule; i++)
				in >> c.pret[i];
			cout << "\n  Vehiculele inchiriate sunt: ";
			for (int i = 0; i < c.nrVehicule; i++)
				in >> c.Vehicule[i];
		}
		else cout << "nu s au inchiriat Vehicule";
	}
};


class Client {
private:
	string nume;
	char telefon[10];
	int nrInchirieri;
	float* pretInchirieri; //pret suma mediu
public:
	string getNume() {
		return this->nume;
	}
	int getNrInchirieri() {
		return this->nrInchirieri;
	}
	float* getPret() {
		return this->pretInchirieri;
	}
	void setNume(string nume) {
		if (nume.size() > 1)
			this->nume = nume;
	}
	void setInchirieri(int nrInchirieri, float* pretInchirieri) {
		if (nrInchirieri > 0 && pretInchirieri != NULL) {
			this->nrInchirieri = nrInchirieri;
			this->pretInchirieri = new float[nrInchirieri];
			for (int i = 0; i < nrInchirieri; i++) {
				this->pretInchirieri[i] = pretInchirieri[i];
			}
		}
	}
	float sumaPret() {
		float suma = 0;
		for (int i = 0; i < this->nrInchirieri; i++) {
			suma = suma + this->pretInchirieri[i];
		}
		return suma;
	}
	float mediePret() {
		float suma = 0;
		for (int i = 0; i < this->nrInchirieri; i++) {
			suma = suma + this->pretInchirieri[i];
		}
		return suma / this->nrInchirieri;
	}
	Client() {
		strcpy(this->telefon, "NULL");
		this->nume = "null";
		this->nrInchirieri = 0;
		this->pretInchirieri = NULL;
	};
	Client(const char telefon[10], string nume, int nrInchirieri, float* pretInchirieri) {
		strcpy(this->telefon, telefon);
		this->nume = nume;
		this->nrInchirieri = nrInchirieri;
		if (nrInchirieri > 0) {
			this->pretInchirieri = new float[nrInchirieri];
			for (int i = 0; i < nrInchirieri; i++)
				this->pretInchirieri[i] = pretInchirieri[i];
		}
		else {
			this->pretInchirieri = NULL;
		}
	}

	Client(const Client& c) {
		strcpy(this->telefon, c.telefon);
		this->nume = c.nume;
		this->nrInchirieri = c.nrInchirieri;
		if (c.nrInchirieri > 0) {
			this->pretInchirieri = new float[c.nrInchirieri];
			for (int i = 0; i < c.nrInchirieri; i++)
				this->pretInchirieri[i] = c.pretInchirieri[i];
		}
		else {
			this->pretInchirieri = NULL;
		}
	}

	Client& operator=(const Client& c) {
		if (this != &c) {
			delete[]this->pretInchirieri;
			strcpy(this->telefon, c.telefon);
			this->nume = c.nume;
			this->nrInchirieri = c.nrInchirieri;
			if (c.nrInchirieri > 0) {
				this->pretInchirieri = new float[c.nrInchirieri];
				for (int i = 0; i < c.nrInchirieri; i++)
					this->pretInchirieri[i] = c.pretInchirieri[i];
			}
			else {
				this->pretInchirieri = NULL;
			}
		}
		return *this;
	}

	~Client() {
		if (this->pretInchirieri != NULL) {
			delete[]this->pretInchirieri;
		}
	}

	friend ostream& operator<<(ostream& out, Client& c) {
		out << "\n Nume: " << c.nume;
		out << "\n Telefon:" << c.telefon;
		out << "\n A inchiriat pana acum: " << c.nrInchirieri << " Vehicule";
		if (c.nrInchirieri > 0) {
			out << "\n Preturile inchirierilor: ";
			for (int i = 0; i < c.nrInchirieri; i++)
				out << c.pretInchirieri[i] << " ";
		}
		else {
			out << "\n nu exista inchirieri ";
		}
		return out;
	}
	friend istream& operator>>(istream& in, Client& c) {
		cout << "\n introduceti numele: ";
		getline(in, c.nume);
		cout << "\n introduceti telefonul: ";
		in >> c.telefon;;
		cout << "\n introduceti nr de Vehicule inchiriate: "; in >> c.nrInchirieri;
		if (c.nrInchirieri > 0) {
			cout << "\n Preturi Vehicule: ";
			for (int i = 0; i < c.nrInchirieri; i++)
				in >> c.pretInchirieri[i];
		}
		else cout << "nu ati introdus o valoare pozitiva >0";
	}

	bool operator==(const Client& c) {
		if (this->telefon == c.telefon && this->nrInchirieri == c.nrInchirieri)
			return true;
		else return false;
	}

	friend ofstream& operator<< (ofstream& ofst, const Client c) {
		ofst << c.nume << " "<< c.telefon <<" " << c.nrInchirieri <<" ";
		for (int i = 0; i < c.nrInchirieri; i++) {
			ofst << c.pretInchirieri[i] << " ";
		}
		return ofst;
	}
	
	//creare fisier csv
	void writeToFile(fstream&fout) {
		cout << "nume:"; 
		cin >> std::ws;
		getline(cin, this->nume);
		cout << "telefon:"; cin >> this->telefon;
		cout << "nr de Vehicule:"; cin >> this->nrInchirieri;
		cout << "\n Preturi Vehicule: ";
		for (int i = 0; i < this->nrInchirieri; i++)
			cin >> this->pretInchirieri[i];
		fout << this->nume << ',' << this->telefon << ',' << this->nrInchirieri;
		for(int i=0;i<this->nrInchirieri;i++)
		fout << ',' << this->pretInchirieri[i];
	}

	//citire din csv
	void readFromFile(fstream& fin) {
		//vector<string>row;
		//string line, word, temp;
		if (fin.is_open())cout << "eheeee";
		//while (fin >> line) {
		//	row.clear(); 
		//	getline(fin, line);
		//	cout << endl << temp; int t = 0;
		//	stringstream s(line);//used for breaking words
		//	while (getline(s, word, ',')) {
		//		row.push_back(word);
		//		cout << word <<"lalala" << endl;
		//	}
		//	for (auto it = row.begin(); it != row.end(); it++)
		//		cout << *it << endl;
		//}
		string data;
		getline(fin, data);
		cout << data << "\n";
	}

	
};
class Angajat {
private:
	char cnp[14];
	string nume;
	int aniVechime;
	bool experienta;
	double* salariuAnual;//salariu mediu si suma
public:
	string getNume() {
		return this->nume;
	}
	int getNrAniVechime() {
		return this->aniVechime;
	}
	bool getExperienta() {
		return this->experienta;
	}
	double* getSalariuAnual() {
		return this->salariuAnual;
	}
	void setNume(string nume) {
		if (nume.size() > 2)
			this->nume = nume;
	}
	void setExperienta(bool experienta) {
		if (experienta == 0 || experienta == 1)
			this->experienta = experienta;
	}
	void setSalarii(int aniVechime, double* salariuAnual) {
		delete[] this->salariuAnual;
		this->aniVechime = aniVechime;
		this->salariuAnual = new double[this->aniVechime];
		for (int i = 0; i < this->aniVechime; i++)
			this->salariuAnual[i] = salariuAnual[i];
	}
	float sumaSalarii() {
		float suma = 0;
		for (int i = 0; i < this->aniVechime; i++) {
			suma = suma + this->salariuAnual[i];
		}
		return suma;
	}
	float medieSalariu() {
		float suma = 0;
		for (int i = 0; i < this->aniVechime; i++) {
			suma = suma + this->salariuAnual[i];
		}
		return suma / this->aniVechime;
	}
	Angajat() {
		strcpy(this->cnp, "NULL");
		this->nume = "null";
		this->aniVechime = 0;
		this->experienta = 0;
		this->salariuAnual = NULL;
	};
	Angajat(const char cnp[14], string nume, int aniVechime, bool experienta, double* salariuAnual) {
		strcpy(this->cnp, cnp);
		this->nume = nume;
		this->aniVechime = aniVechime;
		this->experienta = experienta;
		if (aniVechime > 0) {
			this->salariuAnual = new double[aniVechime];
			for (int i = 0; i < aniVechime; i++)
				this->salariuAnual[i] = salariuAnual[i];
		}
		else {
			this->salariuAnual = NULL;
		}
	}

	Angajat(const Angajat& a) {
		strcpy(this->cnp, a.cnp);
		this->nume = a.nume;
		this->aniVechime = a.aniVechime;
		this->experienta = a.experienta;
		if (a.aniVechime > 0) {
			this->salariuAnual = new double[a.aniVechime];
			for (int i = 0; i < a.aniVechime; i++)
				this->salariuAnual[i] = a.salariuAnual[i];
		}
		else {
			this->salariuAnual = NULL;
		}
	}

	Angajat& operator=(const Angajat& a) {
		if (this != &a) {
			delete[]this->salariuAnual;
			strcpy(this->cnp, a.cnp);
			this->nume = a.nume;
			this->aniVechime = a.aniVechime;
			this->experienta = a.experienta;
			if (a.aniVechime > 0) {
				this->salariuAnual = new double[a.aniVechime];
				for (int i = 0; i < a.aniVechime; i++)
					this->salariuAnual[i] = a.salariuAnual[i];
			}
			else {
				this->salariuAnual = NULL;
			}
		}
		return *this;
	}

	~Angajat() {
		if (salariuAnual != NULL) {
			delete[]this->salariuAnual;
		}
	}

	friend ostream& operator<<(ostream& out, Angajat& a) {
		out << "\n Nume: " << a.nume;
		out << "\n CNP:" << a.cnp;
		out << "\n Experienta:" << a.experienta;
		if (a.aniVechime == 0) {
			out << "\n nu are niciun an vechime";
			if (a.salariuAnual != NULL)
				out << "\n salariul este: " << a.salariuAnual[0];
			else out << "\n nu exista salariul";
		}
		else {
			out << "\n salariul este: ";
			for (int i = 0; i < a.aniVechime; i++)
				out << a.salariuAnual[i] << " ";
		}
		return out;
	}
	friend istream& operator>>(istream& in, Angajat& a) {
		cout << "\n introduceti numele: ";
		getline(in, a.nume);
		cout << "\n introduceti CNP: ";
		in >> a.cnp;
		cout << "\n introduceti daca are experiente anterioare(1 sau 0)";
		in >> a.experienta;
		cout << "\n introduceti anii de vechime: "; in >> a.aniVechime;
		if (a.aniVechime >= 0)
			for (int i = 0; i < a.aniVechime; i++)
				in >> a.salariuAnual[i];
		else cout << "nu ati introdus o valoare pozitiva";
	}

	bool operator!() {
		if (experienta == 1) {
			experienta = 0;
			return true;
		}
		else {
			experienta = 1;
			return false;
		}
	}
};



class Controller {
public:
	string addStringInfo(string s) {
		cout << endl << s;
		string input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, input);
		return input;
	}
	bool addBoolValue(string s) {
		cout << endl << s;
		bool input;
		cin >> input;
		return input;
	}
	int addIntValue(string s) {
		cout << endl << s;
		int input;
		cin >> input;
		return input;
	}
	void afiseazaVehiculele(vector<Vehicul*> vehicule) {
		vector<Vehicul*>::iterator it;
		cout << "\nAfisare vehicule" << endl;
		int counter = 1;
		if (vehicule.size()) {
			for (it = vehicule.begin(); it != vehicule.end(); it++) {
				cout << counter << ". " << (*it)->toString() << endl;
				counter++;
			}
		}
		else {
			cout << "\nNu sunt vehicule inregistrate momentan\n";
		}
	}
	void adaugaVehicul(vector<Vehicul*>& vehicule, Vehicul* const& vehicul) {
		vehicul->setAttributes();
		vehicule.push_back(vehicul);
	}
	void editVehicul(vector < Vehicul * > & vehicule, int index) {
		vehicule[index - 1]->setAttributes();
	}
	
	void getVehiculeFisier() {
		ifstream in;
		string item;
		in.open("vehicule.bin", ios::in | ios::binary);
		if (in.fail()) {
			cout << "failed to get info";
			exit(1);
		}
		while (getline(in, item)) {
			cout << item << endl;
		}
		in.close();
	}
	void addVehiculFisier(Vehicul* vehicul) {
		ofstream out("vehicule.bin", ios::binary | ios_base::app);
		out.write((char*)vehicul, sizeof(vehicul));
		out.close();
	}

	void readVehiculFisier() {
		ifstream f("vehicule.bin", ios::binary);
		if (f.is_open()) {
			f.seekg(0, ios::beg);

			Vehicul* aux;
			while (!f.eof())	{
				f.read((char*)&aux, sizeof(Vehicul*));
				cout << aux->getmarca();
			}
			cout << endl;
			f.close();
		}
		else
			cerr << "Eroare la deschiderea Vehicul.dat";
	}

	void addClientFisier(Client& client) {
		ofstream f1("clienti.txt", ios::out | ios_base::app);
		if (!f1)
			cerr << "Nu exista fisierul;";
		else
			f1 << endl<<client;
		f1.close();
	}
	void scriereClientInBinar() {
		ifstream in("clienti.txt");
		ofstream out("out.bin", ios::binary);
		double d;
		while (in >> d) {
			out.write((char*)&d, sizeof d);
		}
		out.close();
	}

	void scrieresicitireCSV(Client cl2) {
		fstream fout("fisier.csv", ios::out | ios::binary);
		cl2.writeToFile(fout);
		fout.close();
		fstream fin("fisier.csv", ios::in | ios::binary);
		cl2.readFromFile(fin);
	}
};