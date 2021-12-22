#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

class Carte
{
    int nr_pagini;
    float rating, pret;
    string denumire_carte, autor_principal, autor_secundar;

public:
    //set
    void set_autor_principal(string);
    void set_autor_secundar(string);
    void set_denumire_carte(string);
    void set_nr_pagini(int);
    void set_rating(float);
    void set_pret(float);
    //get
    string get_autor_principal();
    string get_autor_secundar();
    string get_denumire_carte();
    int get_nr_pagini();
    int get_rating();
    int get_pret();

    //constructori
    Carte();        //constructor implicit fara parametri
    Carte(string denumire, string autor1, string autor2, int pagini, int pret, int rating);  //constructor cu parametri
    // constructor de copiere
    Carte(const Carte& c);
    // destructor
    ~Carte();

    // supraincarcare pe operatori
    friend ostream& operator <<(ostream& out, const Carte& c);
    friend istream& operator >>(istream&in, Carte& c);
    Carte& operator =(const Carte& c);
    friend bool operator <(const Carte&, const Carte&);
    friend bool operator >(const Carte&, const Carte&);
    friend bool operator ==(const Carte&, const Carte&);

    //functii citire-afisare
    friend Carte* Citire_Afisare(int n);
    friend Carte* Citire(int n);
    void Afisare();
};

//set
void Carte::set_autor_principal(string s){autor_principal = s;}
void Carte::set_autor_secundar(string s) {autor_secundar = s; }
void Carte::set_denumire_carte(string s) {denumire_carte = s; }
void Carte::set_nr_pagini(int x) {nr_pagini = x;}
void Carte::set_rating(float x) {rating = x; }
void Carte::set_pret(float x) {pret = x;}

//get
string Carte::get_autor_principal() {return autor_principal;}
string Carte::get_autor_secundar() {return autor_secundar; }
string Carte::get_denumire_carte() {return denumire_carte; }
int Carte::get_nr_pagini() {return nr_pagini; }
int Carte::get_rating() {return rating; }
int Carte::get_pret() {return pret; }


// constructori
Carte::Carte()      //constructor implicit fara parametri
{
    nr_pagini = 0;
    rating = 0;
    pret = 0;
    denumire_carte= "NoTitle";
    autor_principal = "Anonim";
    autor_secundar = "Anonim";
}

Carte::Carte(string denumire, string autor1, string autor2, int pagini, int p, int r) //constructor cu parametri
{
    denumire_carte = denumire;
    autor_principal = autor1;
    autor_secundar = autor2;
    nr_pagini = pagini;
    pret = p;
    rating = r;
}

// constructor de copiere
Carte::Carte(const Carte& c)
{
    nr_pagini = c.nr_pagini;
    pret = c.pret;
    rating = c.rating;
    denumire_carte = c.denumire_carte;
    autor_principal = c.autor_principal;
    autor_secundar = c.autor_secundar;
    cout << "Constr de copiere apelat.\n";
}


// destructor
Carte::~Carte()
{
    //cout << "Obiect distrus." << "\n";
}


// supraincarcare pe operatori
ostream& operator <<(ostream& out, const Carte& c)
{
    out << "Titlu: ";
    out << c.denumire_carte << "\n";
    out << "Autori: ";
    out << c.autor_principal << "; " << c.autor_secundar << "\n";
    out << "Pret: " << c.pret << "\n";
    out << "Numar de pagini: " << c.nr_pagini << "\n";
    out << "Rating: " << c.rating << "\n";
    out << "\n";
    return out;
}

istream& operator >>(istream& in, Carte& c)
{
    cout << "\n";
    cout << "Dati titlul: ";
    getline(in, c.denumire_carte);
    cout << "Dati primul autor: ";
    getline(in, c.autor_principal);
    cout << "Dati al doilea autor: ";
    getline(in, c.autor_secundar);
    cout << "Dati numarul de pagini(int), pretul(float), rating-ul(float): ";
    in >> c.nr_pagini >> c.pret >> c.rating;
    in.get();
    cout << "\n";
    return in;
}

Carte& Carte::operator =(const Carte& c)
{
    denumire_carte = c.denumire_carte;
    autor_principal = c.autor_principal;
    autor_secundar = c.autor_secundar;
    nr_pagini = c.nr_pagini;
    pret = c.pret;
    rating = c.rating;
    return *this;
}

bool operator <(const Carte& c1, const Carte& c2)
{
    if(c1.rating < c2.rating) return true;
    return false;
}

bool operator >(const Carte& c1, const Carte& c2)
{
    if(c1.rating > c2.rating) return true;
    return false;
}

bool operator ==(const Carte& c1, const Carte& c2)
{
    if(c1.rating == c2.rating) return true;
    return false;
}

// functii de citire si afisare
Carte* Citire_Afisare(int n)
{
    Carte* v = new Carte[n];
    for(int i=0; i < n; ++i)
        cin >> v[i];
    cout << "\nCarti initiale:\n";
    for(int i=0; i < n; ++i)
        cout << v[i];
    cout << "\n";
    return v;
}
Carte* Citire(int n)
{
    Carte* v = new Carte[n];
    for(int i=0; i < n; ++i)
        cin >> v[i];
    return v;
}
void Carte::Afisare()
{
    cout << "Titlu: ";
    cout << denumire_carte << "\n";
    cout << "Autori: ";
    cout << autor_principal << "; " << autor_secundar << "\n";
    cout << "Pret: " << pret << "\n";
    cout << "Numar de pagini: " << nr_pagini << "\n";
    cout << "Rating: " << rating << "\n";
    cout << "\n";
}


int main()
{
    int n; // nr de carti
    cout << "Dati numarul de carti: ";
    cin >> n;
    cin.get();
    if(n == 0) {cout << "Nu au fost introduse detalii despre nicio carte. :("; return 0;}


    /// CITIRE si AFISARE date intiale
    Carte* v = Citire_Afisare(n);
    cout << "\n";


    /// COMPARARE carti
    // afisare cartea cu rating maxim si cea cu rating minim
    Carte vmax, vmin;
    int pozmax = 1, pozmin = 1;
    vmax = v[0];
    vmin = v[0];

    for(int i=1; i < n; ++i)
    {
        if(v[i] > vmax)
            vmax = v[i], pozmax = i+1;
        if(v[i] < vmin)
            vmin = v[i], pozmin = i+1;
    }

    cout << "Cartea cu rating maxim este cea cu numarul: " << pozmax << "\n";
    cout << vmax;
    cout << "Cartea cu rating minim este cea cu numarul: " << pozmin << "\n";
    cout << vmin;

    cout << "\n\n";


    /// MODIFICARE carte/carti
    // modificam cartea cu rating maxim si pe cea cu rating minim
    // modificam titlul spre exemplu
    string s, t;
    s = v[pozmax-1].get_denumire_carte();
    t = "-PREMIUM";
    s.append(t);
    v[pozmax-1].set_denumire_carte(s);
    cout << "Modificare:\n" << v[pozmax-1];

    s = v[pozmin-1].get_denumire_carte();
    t = "-RUDIMENTARY";
    s.append(t);
    v[pozmin-1].set_denumire_carte(s);
    cout << "Modificare:\n" << v[pozmin-1];

    cout << "\n\n";

    /// AFISARE toate cartile - dupa modificari
    cout << "Toate cartile dupa modificari:\n";
    for(int i=0; i < n; ++i)
        v[i].Afisare();

    delete[] v;

    return 0;
}
