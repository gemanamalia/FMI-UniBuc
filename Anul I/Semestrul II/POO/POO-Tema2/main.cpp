#include <bits/stdc++.h>

using namespace std;

/// CLASA DE BAZA
class Avocat
{
    static int nra;
    int cod, nr_procese, *vector_procese;
    string nume;

public:
    // constructori si destructor
    Avocat();
    Avocat(string nume, int cod, int nr_procese, int *vector_procese);
    Avocat(const Avocat& a);
    ~Avocat();

    // supraincarcare pe operatori
    friend ostream& operator <<(ostream& out, const Avocat& a);
    friend istream& operator >>(istream&in, Avocat& a);
    Avocat& operator =(const Avocat& a);
    friend bool operator >(const Avocat&, const Avocat&);

    // alte functii
    static void afis_avocat() { cout << "\nNr total avocati = " << nra << "\n";}
    virtual void afis()
    {
        cout << "\nNume: " << nume << "\nCod: " << cod << "\nNr procese: " << nr_procese;
        for(int i = 0; i < nr_procese; i++)
            cout << "\nSuma proces " << i+1 << ": " << vector_procese[i];
    }
};

int Avocat::nra;


/// CLASA DERIVATA
class Avocat_Oficiu: public Avocat
{
    static int nraof;
    int durata;
    string nume_client;

public:
    // constructori si destructor
    Avocat_Oficiu() { durata = 0; nume_client = "Necunoscut"; nraof++; }
    Avocat_Oficiu(string s, int c, int nr, int* v, string t, int d) : Avocat(s, c, nr, v) { nume_client = t; durata = d; nraof++; }
    Avocat_Oficiu(const Avocat_Oficiu& a) : Avocat(a) { nume_client = a.nume_client; durata = a.durata; nraof++; };
    ~Avocat_Oficiu() { /*cout << "\nDestructor derivata\n";*/ }

    // supraincarcare pe operatori
    friend ostream& operator <<(ostream& out, const Avocat_Oficiu& a);
    friend istream& operator >>(istream& in, Avocat_Oficiu& a);
     Avocat_Oficiu& operator =(const Avocat_Oficiu& a);

    // alte functii
    int get_durata() { return durata; };
    static void afis_avocat(){ cout << "\nNr total avocati din oficiu = " << nraof << "\n";}
    void afis()
    {
        Avocat::afis();
        cout << "\nNume client: " << nume_client << "\nTimp petrecut cu clientul: " << durata;
    }
    void Solve(Avocat_Oficiu v[], int n)
    {
         // aflare avocat din oficiu care a petrecut timpul maxim cu un client
        int vmax = -1, d, poz;
        Avocat_Oficiu rasp;
        for(int i = 0; i < n; i++)
        {
            d = v[i].get_durata();
            if(d > vmax)
            {
                vmax = d;
                rasp = v[i];
                poz = i+1;
            }
        }

        // afisare
        cout << "\nAvocatul " << poz << " a petrecut cel mai mult timp cu clientul sau: " << vmax << "\nDatele despre avocat si client:" << rasp;
    }
};

int Avocat_Oficiu::nraof;


/// CLASA BAZA
// constructori si destructor
Avocat::Avocat()
{
    nume = "Necunoscut";
    cod = 0;
    nr_procese = 0;
    nra++;
}

Avocat::Avocat(string name, int c, int nr, int *v)
{
    nume = name;
    cod = c;
    nr_procese = nr;
    vector_procese = new int[nr];
    for(int i = 0; i< nr; i++)
        vector_procese[i] = v[i];
    nra++;
}

Avocat::Avocat(const Avocat& a) // constructor de copiere
{
    nume = a.nume;
    cod = a.cod;
    nr_procese = a.nr_procese;
    vector_procese = new int[a.nr_procese];
    for(int i = 0; i < a.nr_procese; i++)
        vector_procese[i] = a.vector_procese[i];
    nra++;
}

Avocat::~Avocat()
{
    delete[] vector_procese;
    //cout << " \nDestructor baza\n";
}

// supraincarcare pe operatori
ostream& operator <<(ostream& out, const Avocat& a)
{
    out << "\nNume: " << a.nume;
    out << "\nCod: " << a.cod;
    out << "\nNr procese: " << a.nr_procese;
    for(int i = 0; i < a.nr_procese; i++)
        out << "\nSuma proces " << i+1 << ": " << a.vector_procese[i];
    return out;
}

istream& operator >>(istream& in, Avocat& c)
{
    cout << "\nDati numele avocatului: ";
    in >> c.nume;
    cout << "\nDati codul avocatului: ";
    in >> c.cod;
    cout << "\nDati numarul de procese ale avocatului: ";
    in >> c.nr_procese;
    c.vector_procese = new int[c.nr_procese];
    for(int i = 0; i < c.nr_procese;  i++)
    {
        cout << "\nDati suma procesului " << i+1 << ": ";
        in >> c.vector_procese[i];
    }
}

Avocat& Avocat::operator =(const Avocat& a)
{
    nume = a.nume;
    cod = a.cod;
    nr_procese = a.nr_procese;
    vector_procese = new int[a.nr_procese];
    for(int i = 0; i < a.nr_procese; i++)
        vector_procese[i] = a.vector_procese[i];
    return *this;
}

bool operator >(const Avocat& a, const Avocat& b)
{
    if(a.nr_procese > b.nr_procese) return 1;
    return 0;
}


/// CLASA DERIVATA
// supraincarcare pe operatori
ostream& operator <<(ostream& out, const Avocat_Oficiu& a)
{
    out << (Avocat&) a;
    out << "\nNume client: " << a.nume_client;
    out << "\nTimp petrecut cu clientul: " << a.durata;
    return out;
}

istream& operator >>(istream& in, Avocat_Oficiu& a)
{
    in >> (Avocat&) a;
    cout << "\nDati numele clientului: ";
    in >> a.nume_client;
    cout << "\nDati timpul petrecut cu clientul: ";
    in >> a.durata;
    return in;
}

Avocat_Oficiu& Avocat_Oficiu::operator =(const Avocat_Oficiu& a)
{
    Avocat::operator=(a);
    nume_client = a.nume_client;
    durata = a.durata;
    return *this;
}


void Task1();
void Task2();
void Task3();
void Task4();


int main()
{
    int cerinta;
    cout << "Dati cerinta (1/2/3/4): ";
    cin >> cerinta;
    cout << "\n";
    if(cerinta == 1)
        Task1();
    else if(cerinta == 2)
            Task2();
    else if(cerinta == 3)
            Task3();
    else if(cerinta == 4)
            Task4();

    return 0;
}



void Task1()
{

// upcasting
    cout << "Exemplu de upcasting:\n";
    int y[] = {11, 22};
    int x[] = {33, 44, 55};
    Avocat a("Alin", 1, 2, y);
    Avocat_Oficiu b("Maria", 2, 3, x, "Mihai", 100);

    Avocat *p;
    p = &a;
    p -> afis();
    cout << "\n";
    p = &b;     /// upcasting - memoria stack
    p -> afis();

    cout <<"\n\n\n";

// citire, stocare, afisare a n obiecte + downcasting, upcasting, try-throw-catch
    Avocat **v;
    int n, optiune;


try
{
    cout << "Dati numarul de avocati: ";
    cin >> n;
    cout << "\n";
    if(n <= 0) throw 1;
}
catch(int x)
{
    cout << "Dimensiunea vectorului nu poate fi nula sau negativa! Mai incercati o data.\n";
    return;
}


try
{
    v = new Avocat* [n];
}
catch(bad_alloc v)
{
    cout << "AllocationFailure\n";
    exit(EXIT_FAILURE);
}


    // citire
    for(int i = 0; i < n; i++)
    {
        cout << "\nDati optiunea (par-avocat-oficiu, impar-avocat): ";
        cin >> optiune;
        if(optiune % 2 == 0)
        {
           v[i] = new Avocat_Oficiu(); /// tot upcasting - memoria heap
           cin >> *dynamic_cast<Avocat_Oficiu*>(v[i]); /// downcasting
        }

        else
        {
            v[i] = new Avocat();
            cin >> *v[i];
        }
    }

    // afisare
    for(int i = 0; i < n; i++)
    {
        v[i] -> afis();
        cout << "\n";
    }

    Avocat::afis_avocat();
    Avocat_Oficiu::afis_avocat();
}


void Task2()
{
    Avocat **v;
    int n;


try
{
    cout << "Dati numarul de avocati: ";
    cin >> n;
    cout << "\n";
    if(n <= 0) throw 1;
}
catch(int x)
{
    cout << "Dimensiunea vectorului nu poate fi nula sau negativa! Mai incercati o data.\n";
    return;
}


try
{
    v = new Avocat* [n];
}
catch(bad_alloc v)
{
    cout << "AllocationFailure\n";
    exit(EXIT_FAILURE);
}


    // citire
    for(int i = 0; i < n; i++)
    {
        cout << "\nDati datele despre avocat: ";
        v[i] = new Avocat();
        cin >> *v[i];
    }

    // sortare avocati in functie de nr de procese
    bool ordo = 0;
    while(ordo == 0)
    {
        ordo = 1;
        for(int i = 0; i < n-1; i++)
            if(*v[i] > *v[i+1])
        {
            Avocat *aux;
            aux = new Avocat();
            aux = v[i];
            v[i] = v[i+1];
            v[i+1] = aux;
            ordo = 0;
        }
    }

    // afisare
    cout << "\n\nAvocatii sortati descrescator in functie de numarul de procese:\n";
    for(int i = 0; i < n; i++)
    {
        v[i] -> afis();
        cout << "\n";
    }
}


void Task3()
{
    Avocat_Oficiu **v;
    int n;


try
{
    cout << "Dati numarul de avocati: ";
    cin >> n;
    cout << "\n";
    if(n <= 0) throw 1;
}
catch(int x)
{
    cout << "Dimensiunea vectorului nu poate fi nula sau negativa! Mai incercati o data.\n";
    return;
}


try
{
    v = new Avocat_Oficiu* [n];
}
catch(bad_alloc v)
{
    cout << "AllocationFailure\n";
    exit(EXIT_FAILURE);
}


    // citire
    for(int i = 0; i < n; i++)
    {
        cout << "\nDati datele despre avocatul din oficiu: ";
        v[i] = new Avocat_Oficiu();
        cin >> *v[i];
    }

    // aflare avocat din oficiu care a petrecut timpul maxim cu un client
    int vmax = -1, d, poz;
    Avocat_Oficiu *rasp;
    rasp = new Avocat_Oficiu();
    for(int i = 0; i < n; i++)
    {
        d = v[i] -> get_durata();
        if(d > vmax)
        {
            vmax = d;
            rasp = v[i];
            poz = i+1;
        }
    }

    // afisare
    cout << "\nAvocatul " << poz << " a petrecut cel mai mult timp cu clientul sau: " << vmax << "\nDatele despre avocat si client:" << *rasp;
}


void Task4()
{
    Avocat_Oficiu v[1001];
    int n;


try
{
    cout << "Dati numarul de avocati: ";
    cin >> n;
    cout << "\n";
    if(n <= 0) throw 1;
}
catch(int x)
{
    cout << "Dimensiunea vectorului nu poate fi nula sau negativa! Mai incercati o data.\n";
    return;
}


    // citire
    for(int i = 0; i < n; i++)
    {
        cout << "\nDati datele despre avocatul din oficiu: ";
        cin >> v[i];
    }

   v[0].Solve(v, n);
}




