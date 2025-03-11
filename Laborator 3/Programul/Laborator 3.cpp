
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Vehicul {
protected:
    string nrInmatriculare;
    int oraIntrare, oraIesire;
public:
    Vehicul(string nr, int intrare, int iesire) : nrInmatriculare(nr), oraIntrare(intrare), oraIesire(iesire) {}
    virtual ~Vehicul() {}
    int calculTimpParcare() { return oraIesire - oraIntrare; }
    virtual double calculTarif() = 0;
    virtual void afisare() {
        cout << "Numar: " << nrInmatriculare << ", Timp: " << calculTimpParcare() << " ore, Tarif: " << calculTarif() << " lei\n";
    }
};

class Masina : public Vehicul {
public:
    Masina(string nr, int intrare, int iesire) : Vehicul(nr, intrare, iesire) {}
    double calculTarif() override { return calculTimpParcare() * 5; }
};

class Motocicleta : public Vehicul {
public:
    Motocicleta(string nr, int intrare, int iesire) : Vehicul(nr, intrare, iesire) {}
    double calculTarif() override { return calculTimpParcare() * 3; }
};

class Camion : public Vehicul {
public:
    Camion(string nr, int intrare, int iesire) : Vehicul(nr, intrare, iesire) {}
    double calculTarif() override { return calculTimpParcare() * 10; }
};

class Bicicleta : public Vehicul {
public:
    Bicicleta(string nr, int intrare, int iesire) : Vehicul(nr, intrare, iesire) {}
    double calculTarif() override {
        int timp = calculTimpParcare();
        return (timp <= 2) ? 0 : (timp - 2) * 2;
    }
};

void citireFisier(vector<Vehicul*>& vehicule, const string& numeFisier) {
    ifstream file(numeFisier);
    string tip, nr, oraIntrareStr, oraIesireStr;
    int oraIntrare, oraIesire;
    while (file >> tip >> nr >> oraIntrareStr >> oraIesireStr) {
        oraIntrare = stoi(oraIntrareStr.substr(0, 2));
        oraIesire = stoi(oraIesireStr.substr(0, 2));

        if (tip == "Masina") vehicule.push_back(new Masina(nr, oraIntrare, oraIesire));
        else if (tip == "Motocicleta") vehicule.push_back(new Motocicleta(nr, oraIntrare, oraIesire));
        else if (tip == "Camion") vehicule.push_back(new Camion(nr, oraIntrare, oraIesire));
        else if (tip == "Bicicleta") vehicule.push_back(new Bicicleta(nr, oraIntrare, oraIesire));
    }
}

int main() {
    vector<Vehicul*> vehicule;
    citireFisier(vehicule, "parcare.txt");
    for (auto v : vehicule) {
        v->afisare();
        delete v;
    }
    return 0;
}


