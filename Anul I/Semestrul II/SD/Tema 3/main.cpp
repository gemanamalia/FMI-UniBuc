#include <bits/stdc++.h>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");


struct nod
{
    int val;
    nod* parent;
    nod* child;
    nod* stanga;
    nod* dreapta;
};

// declarare doua heap-uri
nod* minim_h1 = nullptr;
int nrNoduri_h1;
nod* minim_h2 = nullptr;
int nrNoduri_h2;


// creare un nou nod in care pune valoarea x iar legaturile din stanga si din dreapta vor fi tot cu el
nod* CreareNod(int x)
{
    nod* aux = new nod;
    aux -> val = x;
    aux -> parent = nullptr;
    aux -> child = nullptr;
    aux -> stanga = aux;
    aux -> dreapta = aux;
    return aux;
}

//adauga un nod nou in stanga minimului in root list
void Inserare(int x, int& nrNoduri, nod*& minim) // inserare nod nou "x" in heap
{
    nrNoduri += 1;
    nod* aux = CreareNod(x);
    // cout << aux -> val << " ";

    // formeaza legaturi cu minimul si cu fostul nod din stanga minimului
    if(minim != nullptr)    // verificam daca heapul este gol
    {
        (minim -> stanga) -> dreapta = aux;
        aux -> dreapta = minim;
        aux -> stanga = minim -> stanga;
        minim -> stanga = aux;
        if(aux -> val < minim -> val)
            minim = aux;
    }
    else  minim = aux;
}

// Afisare Fibonacci Heap
void Afisare_Fibonacci_Heap(nod* minim)
{
    nod* aux = minim;
    if(aux == nullptr) // inseamna ca nu avem elemente in heap
        fout << "Heap fara elemente(gol)." << "\n\n";
    else
    {
        do
        {
            fout << aux -> val << " ";
            aux = aux -> dreapta;
        }
        while(aux != minim && aux -> dreapta != NULL);
        fout << "\n";
    }
}


void Delete_Min_Heap(nod* toDelete, int nrNoduri, nod*& mini)
{
    nod *aux, *newMini;
    // daca heap-ul are o singura radacina
    if(toDelete -> dreapta == toDelete)
    {
        if(toDelete -> child == nullptr)    //  verificam daca nu are copii
        {                                   //  deci heap ul are 1 singur nod si anume minimul si il stergem direct
            delete toDelete;
            mini = nullptr;
            nrNoduri = 0;
            return;
        }
        else
            newMini = mini;  //daca are o singura radacina dar si copii si trb sa cautam ulterior minimul printre copii
    }
    else // daca are mai multe radacini
    {

    }
}



void Merge(nod*& minim_h1, int& nrNoduri_h1, nod*& minim_h2, int& nrNoduri_h2)
{
    if(minim_h1 == nullptr) // daca primul heap este gol -> il facem sa fie egal cu al doilea si il stergem pe al doilea
    {
        if(minim_h2 != nullptr)
        {
            minim_h1 = minim_h2;
            nrNoduri_h1 = nrNoduri_h2;

            minim_h2 = nullptr;
            nrNoduri_h2 = 0;
        }
    }
    else if(minim_h1 != nullptr)        // daca primul heap are elemente
            if(minim_h2 != nullptr)     // si daca si al doilea heap are elemente
            {
            //  insereaza heapul 2 in stanga min-ului din heap 1
            //  mai intai insereaza min-ul (minimul de la heap 2) apoi restul nodurilor din rootlist 2
                (minim_h1->stanga) -> dreapta = minim_h2;
                (minim_h2->stanga) -> dreapta = minim_h1;
                nod* aux = minim_h1 -> stanga;
                minim_h1 -> stanga = minim_h2 -> stanga;
                minim_h2 -> stanga = aux;
            // aduna nr de noduri
                nrNoduri_h1 += nrNoduri_h2;
                if(minim_h1 -> val  >  minim_h2 -> val) // restabilim valoarea minima
                    minim_h1 = minim_h2;
            // facem min-ul heap-ului doi sa fie null
                minim_h2 = nullptr;
                nrNoduri_h2 = 0;
            }
}

//construire heap nou si fara elemente
nod* CreareFibonacciHeap(nod*& minim, int& nrNoduri)
{
    minim = nullptr;
    nrNoduri = 0;
    return minim;
}

void Task1();
void Task2();
void Task3();

int main()
{
    Task1();
    Task2();
    Task3();
    return 0;
}

// citire + afisare heap: (insert, build)
void Task1()
{
    int n, x, y;
    fin >> n;
    for(int i = 1; i <= n; i++)
    {
        fin >> x;
        if(x == 1)
        {
            fin >> y;
            Inserare(y, nrNoduri_h1, minim_h1);
        }
    }

    fout << "Task 1: \n";
    Afisare_Fibonacci_Heap(minim_h1);
    if(minim_h1 != nullptr)
        fout << "Minimul heap-ului este: " << minim_h1 -> val << "\n\n";
}

// stergere minim din heap-ul initial + afisare heap dupa modificare
void Task2()
{
    fout << "Task 2: \n";
    if(minim_h1 != nullptr)
    {
        Delete_Min_Heap(minim_h1, nrNoduri_h1, minim_h1);
        Afisare_Fibonacci_Heap(minim_h1);
    }
    else
        fout << "Nu poate fi afisata nicio valoare deoarece heapul este gol." << "\n\n";
    fout << "\n";
}


// merge intre doua heap-uri
void Task3()
{
    int n, x, y;
    fin >> n;
    for(int i = 1; i <= n; i++)
    {
        fin >> x;
        if(x == 1)
        {
            fin >> y;
            Inserare(y, nrNoduri_h2, minim_h2);
        }
    }
    fout << "Task 3: \n";
    Afisare_Fibonacci_Heap(minim_h2);
    Merge(minim_h1, nrNoduri_h1, minim_h2, nrNoduri_h2);
    fout << "Heap-uri dupa merge: ";
    Afisare_Fibonacci_Heap(minim_h1);
    fout << "\n\n";
}














/*
void Consolidate()
{
    int i;
    int degr = (log(nrNodes)) / (log(2));
    node* current;
    node* aux;
    node* d[degr + 1]; //vector de pointeri pt heapurile de diferite grade
    for(i = 0; i <= degr; i++)
        d[i] = nullptr;
    d[mini->degree] = mini;

    aux = mini->right;
    while(aux != mini)
    {
        current = aux;
        aux = aux->right;
        while(d[current->degree] != nullptr)
        {
            current = link(current, d[current->degree]);
            //dupa ce linkuim 2 heapuri de aceeasi lungime, se elibereaza d[lungimea celor unite]
            d[current->degree - 1] = nullptr;
        }
        d[current->degree] = current;
    }
}*/
