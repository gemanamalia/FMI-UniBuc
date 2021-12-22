/// Tema 2 - Atlas Zoologic
#include <bits/stdc++.h>

using namespace std;

class Nevertebrate;
class Vertebrate;

class Animal
{
private:
    string denumire;
public:
    // constructor de initializare fara parametri
    Animal(){ denumire = "NoName"; }
    // constructor cu parametri
    Animal(string s) { denumire = s; }
    // constructor de copiere
    Animal(const Animal& A) { denumire = A.denumire; }
    // destructor
    ~Animal() {}

    // supraincarcare pe operatori
    friend ostream& operator <<(ostream& in, Animal& A);
    friend istream& operator >>(istream& out, Animal& A);
    Animal& operator =(const Animal& A);

    // alte functii
    virtual void Afisare() { cout << "Denumire animal: " << denumire << "\n"; }
};

ostream& operator <<(ostream& out, Animal& A)
{
    out << "Denumire animal: " << A.denumire << "\n";
    return out;
}

istream& operator >>(istream& in, Animal& A)
{
    cout << "Dati denumirea animalului: ";
    in >> A.denumire;
    return in;
}

Animal& Animal::operator =(const Animal& A)
{
    denumire = A.denumire;
    return *this;
}




class Nevertebrate:public Animal
{
private:
    int cod;
public:
    // constructori si destructor
    Nevertebrate() { cod = 0; }
    Nevertebrate(string s, int c) : Animal(s) { cod = 0; }
    Nevertebrate(const Nevertebrate& A) : Animal(A) { cod = A.cod; }
    ~Nevertebrate() {}

    // supraincarcari pe operatori
    friend ostream& operator <<(ostream& out, Nevertebrate& A);
    friend istream& operator >>(istream& in, Nevertebrate& A);
    Nevertebrate& operator =(const Nevertebrate& A);

    // alte functii
    void afis(){cout<<((Animal&)*this);cout<<" ";cout<<cod;}

};

ostream& operator <<(ostream& out, Nevertebrate& A)
{
    out << (Animal&) A;
    out << "Cod animal nevertebrat: " << A.cod << "\n";
    return out;
}

istream& operator >>(istream& in, Nevertebrate& A)
{
    in >> (Animal&) A;
    cout << "Dati codul animalului nevertebrat: ";
    in >> A.cod;
    return in;
}

Nevertebrate& Nevertebrate::operator =(const Nevertebrate& A)
{
    Animal::operator=(A);
    cod = A.cod;
    return *this;
}




class Vertebrate:public Animal
{
private:
    int cod;
public:
    // constructori si destructor
    Vertebrate() { cod = 0; }
    Vertebrate(int c) { cod = c; }
    Vertebrate(string s, int c) : Animal(s) { cod = 0; }
    Vertebrate(const Vertebrate& A) : Animal(A) { cod = A.cod; }
    ~Vertebrate() {}

    // supraincarcari pe operatori
    friend ostream& operator <<(ostream& out, Vertebrate& A);
    friend istream& operator >>(istream& in, Vertebrate& A);
    Vertebrate& operator =(const Vertebrate& A);

    // alte functii
    void afis(){cout<<((Animal&)*this);cout<<" ";cout<<cod;}
};

ostream& operator <<(ostream& out, Vertebrate& A)
{
    out << (Animal&) A;
    out << "Cod animal vertebrat: " << A.cod << "\n";
    return out;
}

istream& operator >>(istream& in, Vertebrate& A)
{
    in >> (Animal&) A;
    cout << "Dati codul animalului vertebrat: ";
    in >> A.cod;
    return in;
}

Vertebrate& Vertebrate::operator =(const Vertebrate& A)
{
    Animal::operator=(A);
    cod = A.cod;
    return *this;
}




class Pesti : public Vertebrate
{
private:
    string specie;
    double lungime;
public:
    Pesti(): Vertebrate() { specie = "NoName"; lungime = 0; }
    Pesti(int cod, string s, double l) : Vertebrate(cod) { specie = s; lungime = l; }
    Pesti(const Pesti& p):Vertebrate(p)
    {
        specie = p.specie;
        lungime = p.lungime;
    }
    ~Pesti(){}

    friend ostream& operator <<(ostream& out, Pesti& p);
    friend istream& operator >>(istream& in, Pesti& p);
    Pesti& operator =(const Pesti& p);

    double get_lungime()const { return lungime; }
};

ostream& operator <<(ostream& out, Pesti& p)
{
    out<<(Vertebrate&)p;
    out<<"Nume specie peste: " << p.specie << "\n";
    out<<"Lungime peste: " << p.lungime << "\n";
    return out;
}


istream& operator >>(istream& in, Pesti& p)
{
    cout << "Introduceti datele despre un peste:\n";
    in >> (Vertebrate&) p;
    cout << "Dati specia de peste: ";
    in >> p.specie;
    cout << "Dati lungimea pestelui: ";
    in >> p.lungime;
    return in;
}

Pesti& Pesti::operator =(const Pesti& p)
{
    Vertebrate::operator =(p);
    specie = p.specie;
    lungime = p.lungime;
    return *this;
}




class Pasari : public Vertebrate
{
private:
    string specie;
public:
    Pasari(): Vertebrate() { specie = "NoName"; }
    Pasari( int cod, string s) : Vertebrate(cod) { specie = s; }
    Pasari(const Pasari& p):Vertebrate(p)
    {
        specie = p.specie;
    }
    ~Pasari(){}

    friend ostream& operator <<(ostream& out, Pasari& p);
    friend istream& operator >>(istream& in, Pasari& p);
    Pasari& operator =(const Pasari& p);
};

ostream& operator <<(ostream& out, Pasari& p)
{
    out<<(Vertebrate&)p;
    out<<"Nume specie pasare: " << p.specie << "\n";
    return out;
}


istream& operator >>(istream& in, Pasari& p)
{
    cout << "Introduceti datele despre o pasare:\n";
    in >> (Vertebrate&) p;
    cout << "Dati specia de pasare: ";
    in >> p.specie;
    return in;
}

Pasari& Pasari::operator =(const Pasari& p)
{
    Vertebrate::operator =(p);
    specie = p.specie;
    return *this;
}




class Mamifere : public Vertebrate
{
private:
    string specie;
public:
    Mamifere(): Vertebrate() { specie = "NoName"; }
    Mamifere( int cod, string s) : Vertebrate(cod) { specie = s; }
    Mamifere(const Mamifere& p):Vertebrate(p)
    {
        specie = p.specie;
    }
    ~Mamifere(){}

    friend ostream& operator <<(ostream& out, Mamifere& p);
    friend istream& operator >>(istream& in, Mamifere& p);
    Mamifere& operator =(const Mamifere& p);
};

ostream& operator <<(ostream& out, Mamifere& p)
{
    out<<(Vertebrate&)p;
    out<<"Nume specie mamifer: " << p.specie << "\n";
    return out;
}


istream& operator >>(istream& in, Mamifere& p)
{
    cout << "Introduceti datele despre un mamifer:\n";
    in >> (Vertebrate&) p;
    cout << "Dati specia de mamifer: ";
    in >> p.specie;
    return in;
}

Mamifere& Mamifere::operator =(const Mamifere& p)
{
    Vertebrate::operator =(p);
    specie = p.specie;
    return *this;
}



class Reptile : public Vertebrate
{
private:
    string specie;
public:
    Reptile(): Vertebrate() { specie = "NoName"; }
    Reptile( int cod, string s) : Vertebrate(cod) { specie = s; }
    Reptile(const Reptile& p):Vertebrate(p)
    {
        specie = p.specie;
    }
    ~Reptile(){}

    friend ostream& operator <<(ostream& out, Reptile& p);
    friend istream& operator >>(istream& in, Reptile& p);
    Reptile& operator =(const Reptile& p);
};

ostream& operator <<(ostream& out, Reptile& p)
{
    out<<(Vertebrate&)p;
    out<<"Nume specie reptila: " << p.specie << "\n";
    return out;
}


istream& operator >>(istream& in, Reptile& p)
{
    cout << "Introduceti datele despre o reptila:\n";
    in >> (Vertebrate&) p;
    cout << "Dati specia de reptila: ";
    in >> p.specie;
    return in;
}

Reptile& Reptile::operator =(const Reptile& p)
{
    Vertebrate::operator =(p);
    specie = p.specie;
    return *this;
}


template <class T> class AtlasZoologic
{
    int nrAnimale;
    list < T > v;

public:
    AtlasZoologic() { nrAnimale = 0; }

    void operator +=(const T& animal)
    {
        this -> v.push_back(animal);
        nrAnimale += 1;
    }

    void Afisare()
    {
        cout << "Numarul total de animale este: " << nrAnimale << "\n";
        int ct = 1;
        typename list <T>::iterator it;
        for(it = v.begin(); it != v.end(); it++)
        {
            cout << "Animal " << ct << ":\n" << *it << "\n";
            ct ++;
        }
    }

    ~AtlasZoologic()
    {
        v.clear();
    }
};


template <> class AtlasZoologic <Pesti>
{
    int nrPesti, nrPestiMari;
    list <Pesti> v;
public:
    AtlasZoologic(){ nrPesti = 0; nrPestiMari = 0; }

    void operator +=(const Pesti& p)
    {
        double metru = 1.000;
        if(p.get_lungime() >= metru)
            nrPestiMari += 1;
        this->v.push_back(p);
        nrPesti +=1;
    }

    void Afisare()
    {
        cout << "Numar total de pesti: " << nrPesti << "\n";
        cout << "Numar de pesti rapitori mai mari de 1 metru: " << nrPestiMari << "\n";
        list <Pesti>::iterator it;
        for(it = v.begin(); it != v.end(); it++)
            cout << *it << "\n";
    }
};

/*
template <class T> class Enciclopedie : public AtlasZoologic<T>
{
    public:
        void operator +=(const T& animal)
        {
            this -> v.push_back(animal);
            nrAnimale += 1;
        }

        void Afisare()
        {
            cout << "Enciclopedie";
            cout << "Numarul total de animale este: " << nrAnimale << "\n";

            int ct = 1;
            typename list <T>::iterator it;
            for(it = v.begin(); it != v.end(); it++)
            {
                cout << "Animal " << ct << ":\n" << *it << "\n";
                ct ++;
            }
        }
}
*/

void Task1();
void Task2();
void Task3();

int main()
{
    int c;
    cout << "Dati cerinta: ";
    cin >> c;
    if(c == 1)
        Task1(); // verificare cum se formeaza atlasul zoologic
    else
        Task2(); // // verificare cum se formeaza atlasul zoologic pt pesti

    return 0;
}



void Task1()
{
    int n;

    Pesti a;
    AtlasZoologic <Pesti> AtlasPesti;
    cout << "Dati nr de pesti: ";
    cin >> n;
    for(int i = 1; i<=n; i++)
    {
        cin >> a;
        AtlasPesti += a;
    }
    cout << "\n\n";
    AtlasPesti.Afisare();
    cout << "\n";


    Pasari b;
    AtlasZoologic <Pasari> AtlasPasari;
    cout << "Dati nr de pasari: ";
    cin >> n;
    for(int i = 1; i<=n; i++)
    {
        cin >> b;
        AtlasPasari += b;
    }
    cout << "\n\n";
    AtlasPasari.Afisare();


    Mamifere c;
    AtlasZoologic <Mamifere> AtlasMamifere;
    cout << "Dati nr de mamifere: ";
    cin >> n;
    for(int i = 1; i<=n; i++)
    {
        cin >> c;
        AtlasMamifere += c;
    }
    cout << "\n\n";
    AtlasMamifere.Afisare();


    Reptile d;
    AtlasZoologic <Reptile> AtlasReptile;
    cout << "Dati nr de reptile: ";
    cin >> n;
    for(int i = 1; i<=n; i++)
    {
        cin >> d;
        AtlasReptile += d;
    }
    cout << "\n\n";
    AtlasReptile.Afisare();
}

void Task2()
{
    int n;
    Pesti a;
    AtlasZoologic <Pesti> AtlasPesti;

    cout << "Dati nr de pesti: ";
    cin >> n;
    cout << "\n\n";
    for(int i = 1; i<=n; i++)
    {
        cin >> a;
        AtlasPesti+=a;
    }

    AtlasPesti.Afisare();
    cout << "\n";
}

void Task3()
{

}
