#include <bits/stdc++.h>
#include <vector>

using namespace std;

ifstream fin("DFA.in");
ofstream fout("DFA.out");

int n, m;
int stare_initiala, nr_stari_finale, stare_finala[10001];
int nr_cuvinte;
char cuvant[1001];


struct nod
{
    int info;
    char lit;
    nod* urm;
};

nod* g[10001];

void Adaugare(nod*& prim, int x, char c)
{
    nod* q = new nod;
    q -> info = x;
    q -> lit = c;
    q -> urm = prim;
    prim = q;
}

void Read()
{
    int x, y;
    char c;

    fin >> n >> m;      // nr de stari, nr de tranzitii
    for(int i = 0; i <= m; ++i)
    {
        fin >> x >> y >> c;
        Adaugare(g[x], y, c);       // adaugare in lista de liste
    }

    fin >> stare_initiala;
    fin >> nr_stari_finale;
    for(int i = 1; i <= nr_stari_finale; i++)
        fin >> stare_finala[i];
}


void Solve(char s[1001])
{
    bool ok, acceptat;
    vector <int> rezultat;
    int x = stare_initiala;     // nod curent
    rezultat.push_back(x);

    for(int i = 0; s[i]; i++)   // parcurgem cuvantul
    {
        ok = 0;
        for(nod* p = g[x]; p != NULL; p = p -> urm) // parcurgem lista nodului curent
            if(p -> lit == s[i])
            {
                rezultat.push_back(p->info);
                x = p ->info;
                ok = 1;
                break;
            }

        if(ok == 0)
        {
            fout << "NU" << "\n";
            return;
        }
    }

    if(ok == 1)
    {
        //cautam daca ultimul nod din rezultat este stare finala
        acceptat = 0;
        for(int i = 1; i <= nr_stari_finale; i++)
            if(rezultat[strlen(s)] == stare_finala[i])
            {
                acceptat = 1;
                break;
            }
        if(acceptat == 1)
        {
            fout << "DA" << "\n";
            // afisam traseul
            for(int i=0; i < rezultat.size(); i++)
                fout << rezultat[i] << " ";
            fout << "\n";
        }
        else
            fout << "NU" << "\n";
    }
}


int main()
{
    Read();

    fin >> nr_cuvinte;
    for(int i = 1; i <= nr_cuvinte; i++)
    {
        fin >> cuvant;
        // verificare cuvant acceptat
        Solve(cuvant);
    }

    return 0;
}
