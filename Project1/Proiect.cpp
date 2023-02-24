#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
//#include "Vehicul.h"
//#include "Masina.h"
//#include "Autocar.h"
#include"clase.cpp"
#include <vector>
#include<string>
#include<list>
#include<fstream>
#include <utility>
using namespace std;

int Vehicul::nrVehicule = 0;

int main(int argc,char**argv) {


	int zile[] = { 2,3 };
	int zile2[] = { 3,4,5 };
	Motocicleta motocicleta("Honda",zile,2,1500,1,Culoare::alb,1);
	Autocar autocar("Volvo",zile2,3,3000,1,20,1);
	Masina masina("Audi",zile,2,6000,1,4);

	vector<Vehicul*> vehicule;
	vehicule.push_back(&motocicleta);
	vehicule.push_back(&autocar);
	vehicule.push_back(&masina);


	vector<Client> clienti;
	Client cl;
	float pretInchirieri[] = { 3000,4000 };
	Client cl2("0756135413", "Popescu Ion", 2, pretInchirieri), cl3(cl2);
	clienti.push_back(cl);
	clienti.push_back(cl2);
	//cout << cl.getNrInchirieri() << cl.getNume() << cl.mediePret();
	//cl.setNume("alal"); cl.setInchirieri(2, prett);

	Controller controller;


	int input = 1;
	cout << "\nBun venit";
	cout << "\napasa tasta 1 pentru a intra in aplicatie si tasta 0 pentru a iesi ";
	cin >> input;
	while (input != 0) {
		cout << "\nintrodu informatiile pentru un parc auto";
		ParcAuto parc;
		parc.setCod(controller.addStringInfo("\nCodul este: "));
		parc.setNume(controller.addStringInfo("Numele parcului auto este: "));
		parc.setNrVehicule(vehicule.size());
		cout << "Parcul are " << vehicule.size() << " vehicule";
		for (int i = 0; i < vehicule.size(); i++)
			parc.addToParcAuto(vehicule[i]);

		cout << "\nApasa tasta 1 pentru a intra introduce datele tale de angajat\nApasa tasta 2 pentru a vedea functionalitatile aplicatiei: ";
		cin >> input;
		if (input == 1) {
			cout << "\nSeteaza datele profilului: ";
			Angajat angajat;
			angajat.setNume(controller.addStringInfo("\nIntroduceti numele: "));
			angajat.setExperienta(controller.addBoolValue("Introduceti 1 daca aveti experienta in domeniu si 0 daca nu: "));
			int n;
			cout << "\nIntroduceti anii de vechime: "; cin >> n;
			double* salariu = new double[n];
			cout << "\nIntroduceti salariul din fiecare an: " ;
			for (int i = 0; i < n; i++)
				cin >> salariu[i];
			angajat.setSalarii(n, salariu);

			//Angajat aj,aj2("1231234564565", "Georgescu", 2, 1, salariu), aj3(aj2);
			//aj = aj2;
			//cout << aj2 << aj3 << aj;
			//cout << aj.getExperienta() << aj.getNrAniVechime() << aj.getNume() << aj.medieSalariu();
		}

		while (input !=0 ) {
			cout << "\nCe actiune doriti sa realizati?\n";
			cout << "1. Afiseaza vehiculele\n";
			cout << "2. Adauga un vehicul\n";
			cout << "3. Editeaza datelei unui vehicul\n";
			cout << "4. Afiseaza nr de zile inchiriate pentru fiecare masina si pentru parcul auto per total\n";
			cout << "5. Returnati un vehicul\n";
			cout << "6. Crearea unui fisier cu istoricul clientilor\n";
			cout << "0. Exit\n";

			cin >> input;

			if (input == 1) {
				controller.afiseazaVehiculele(vehicule);
			}

			else if (input == 2) {
				cout << endl << "\nCe tip de vehicul doriti sa adaugati in sistem?\n";
				cout << "1. Motocicleta\n";
				cout << "2. Masina\n";
				cout << "3. Autocar\n";
				cout << "\nIntroduceti numarul corespunzator: ";
				cin >> input;
				string marca;
				cout << "Introduceti marca: "; cin >> marca;
				if (input == 1) {
					controller.adaugaVehicul(vehicule, new Motocicleta(marca));
				}
				else if (input == 2) {
					controller.adaugaVehicul(vehicule, new Masina(marca));
				}
				else if (input == 3) {
					controller.adaugaVehicul(vehicule, new Autocar(marca));
				}
				parc.addToParcAuto(vehicule.back());
				cout << "Vehiculul a fost adaugat in registrul parcului auto";
			}
			else if (input == 3) {
				controller.afiseazaVehiculele(vehicule);
				if (vehicule.size()) {
					cout << "\nCe vehicul doriti sa editati?\n";
					cin >> input;
					controller.editVehicul(vehicule, input);
				};

			}
			else if (input == 4) {
				cout << "\nNr de zile inchiriate la fiecare masina la momentul actual: ";
				vector<Vehicul*>::iterator it;
				int s = 0;
				for (it = vehicule.begin(); it != vehicule.end(); it++) {
					cout << endl;
					cout << (*it)->getNrZile()<<" ";
					cout << "\nzilele in care au fost inchiriate: ";
					for (int i = 0; i < (*it)->getNrZile();i++) cout << (*it)->getZileInchiriere()[i]<<" ";
					s += (*it)->getNrZile();
				}
				cout << "\nNr de zile inchiriate la nivel de parc auto pe tot anul: " << s;
			}
			else if (input == 5) {
				//controller.afiseazaVehiculele(vehicule);
				if (vehicule.size()) {
					cout << "\nCe vehicul doriti sa returnati?\n";
					cin >> input;
					int ziua;
					cout << "\nIn care zi vreti sa il returnati?\n";
					cin >> ziua;
					*vehicule[input - 1]=*vehicule[input-1] -(ziua);
					if ((*vehicule[input-1])[ziua] == 0) cout << "\nvehicului nu mai e inchiriat";
				}
			}
			else if (input == 6) {
				ofstream outFile("clienti.txt", ios_base::app);
				for (auto c : clienti) {
					outFile << c<<endl;
					cout << c<<endl;
				}
			}
			cout << "\nDoriti sa continuati? Apasati oricare tasta pentru Da si 0 pentru Nu\n";
			cin >> input;

		}

	}

	Contract c;
	//cout << c;
	string per[2] = {"1.05.2022","2.06.2022"};
	string autot[] = { "bmw","audi" };
	float pret[] = { 1000,1500 };
	Contract c2(per,2,autot,pret), c3(c2);
	c = c2;
	//cout << c2 << c3 << c;

	//cout <<endl << c.getNrVehicule() << c.mediePret();
	string aut[] = { "ceva","altceva" }; float prett[] = { 3400,5000 }; string perr[] = { "7/05","8/06" };
	c.setVehicule(2,aut,prett); c.setPerioada(perr);
	//cout << c;


	controller.citiresicitireCSV(cl2);


}
