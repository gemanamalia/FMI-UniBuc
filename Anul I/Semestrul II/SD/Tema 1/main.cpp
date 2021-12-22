#include <bits/stdc++.h>
#include <cstdlib>
#include <chrono>
#define Nmax 10000001

using namespace std;
using namespace std::chrono;

ifstream fin("Teste.in");
ofstream fout("Teste.out");

int m;          // nr de teste
int n;          // nr elemente din array
int vmax;       // val max din array
int a[Nmax], copie_a[Nmax];
int f[Nmax];    //pt countsort
int aux[Nmax];  // pt countsort, mergesort, radix
int aux0[Nmax], ct0, aux1[Nmax], ct1;   // pt radix2
int nr[101], val[101];                  // pt date de intrare

int Random_Number(int vmax);
bool Sorted_Vector(int n, int v[]);
void Restabilire_Array(int a[], int copie_a[],int n);
void Task1();
void Task2();


/// Bubble Sort
void Bubble_Sort(int n, int v[])
{
    bool ordo = 0;
    while(ordo == 0)
    {
        ordo = 1;
        for(int i = 0; i < n - 1; i++)
            if(v[i] > v[i+1])
            {
                ordo = 0;
                swap(v[i], v[i+1]);
            }
    }
}

/// Count Sort
void Count_Sort(int n, int v[])
{
    int maxim = v[0], k = 0;

    for(int i = 1; i < n; ++i)
        if(v[i] > maxim)
            maxim = v[i];

    for(int i = 0; i <= maxim; ++i)
        f[i] = 0;

    for(int i=0; i < n; ++i)
        f[v[i]] ++;

    for(int i=0; i <= maxim; ++i)
        while(f[i] != 0)
        {
            f[i] --;
            aux[k++] = i;
        }

    for(int i=0; i < n; ++i)
        v[i] = aux[i];
}

/// Merge Sort
void Interclasare(int s, int m, int d, int v[])
{
    int k = 0, i, j;
    i = s;
    j = m + 1;
    while (i <= m && j <= d)
        if (v[i] < v[j])
            aux[++k] = v[i++];
        else
            aux[++k] = v[j++];

    while (i <= m) aux[++k] = v[i++];
    while (j <= d) aux[++k] = v[j++];

    for (i=s, j=1; i <= d; ++i, ++j) v[i] = aux[j];
}

void Merge_Sort(int s, int d, int v[])
{
    if(s < d)
    {
        int m = (s+d)/2;
        Merge_Sort(s, m, v);
        Merge_Sort(m+1, d, v);
        Interclasare(s, m, d, v);
    }
}

/// Quick Sort - V1
int Pivotare(int s, int d, int v[])
{
    int i, j, pasi, pasj;
    i = s;
    j = d;
    pasi = 0;
    pasj = 1;
    while(i < j)
    {
        if(v[i] > v[j])
        {
            swap(v[i], v[j]);
            pasi = 1 - pasi;
            pasj = 1 - pasj;
        }
        i = i + pasi;
        j = j - pasj;
    }
    return i;
}

void Quick_Sort1(int s, int d, int v[])
{
    if(s < d)
    {
        int p = Pivotare(s, d, v);
        Quick_Sort1(s, p-1, v);
        Quick_Sort1(p+1, d, v);
    }
}

/// Quick Sort - V2 - mediana din 3
int Pivotare2(int s, int d, int v[])
{
    int m = (s+d) / 2;

    /// aranjam cresc cele 3 valori in array
    if(v[s] > v[m]) swap(v[s], v[m]);   // stanga, mijloc
    if(v[s] > v[d]) swap(v[s], v[d]);   // stanga, dreapta
    if(v[m] > v[d]) swap(v[m], v[d]);    // mijloc, dreapta

    int x = v[m];   /// pivotul
    int i = s, j = d;
    bool ok = 1;

    while(ok)
    {
        while(v[i] <= x) i++;
        while(v[j] > x) j--;
        if(i >= j)
            return j;
        swap(v[i], v[j]);
    }
}

void Quick_Sort2(int s, int d, int v[])
{
    if(s < d)
    {
        int p = Pivotare2(s, d, v);
        Quick_Sort2(s, p-1, v);
        Quick_Sort2(p+1, d, v);
    }
}

/// Quick Sort - V3 - cu pivot random
int Pick_Random(int s, int d)
{
    // alegem pozitia random din intervalul [s,d]
    int n;
    n = rand();
    return (s + n % (d-s+1));
}

int Partitionare_QS3(int s, int d, int v[])
{
    // alegere random
    int poz = Pick_Random(s,d);
    swap(v[d], v[poz]);

    // partitionarea propriu-zisa
    int x = v[d];    // pivotul
    int i = s;
    for(int j = s; j < d; ++j)
        if(v[j] <= x)
        {
            swap(v[i], v[j]);
            i ++;
        }
    swap(v[i], v[d]);
    return i;
}

void Quick_Sort3(int s, int d, int v[])
{
    if(s < d)
    {
        int p = Partitionare_QS3(s, d, v);
        Quick_Sort3(s, p-1, v);
        Quick_Sort3(p+1, d, v);
    }
}

/// Radix Sort - V1 - baza 10 - LSD
void Radix(int n, int pow, int v[])
{
    int m = 0;
    for(int i = 0; i <= 9; ++i)
    {
        for(int j = 0; j < n; ++j)
            if((v[j] / pow) % 10 == i)
            {
                aux[m] = v[j];
                m ++;
            }
    }
    for(int i = 0; i < n; ++i)
        v[i] = aux[i];
}

void Radix_Sort(int n, int v[])
{
    int maxim, ordin = 0, pow = 1;

    // determinare element maxim
    maxim = v[0];
    for(int i = 1; i < n; ++i)
        if(v[i] > maxim)
            maxim  = v[i];

    // aflare ordin
    while(maxim != 0)
    {
        maxim /= 10;
        ordin ++;
    }

    for(int i = 0; i < ordin; ++i)
    {
        Radix(n, pow, v);
        pow *= 10;
    }
}

/// Radix Sort - V2 - operatii pe biti
void Radix_Sort2(int n, int v[])
{
    int maxim = v[0], nrbiti = 0, bit = 1;

    for(int i=1; i < n; ++i)
        if(v[i] > maxim)
            maxim = v[i];

    while(maxim != 0)
    {
        maxim /= 2;
        nrbiti++;
    }

    for(int k=1; k <= nrbiti; ++k)
    {
        ct0 = 0;
        ct1 = 0;

        /// impartim in doua grupe
        for(int i=0; i < n; ++i)
            if((v[i] & bit) == 0)
            {
                aux0[ct0] = v[i];
                ++ ct0;
            }
            else
            {
                aux1[ct1] = v[i];
                ++ ct1;
            }
        /// reuniune
        int i = 0;
        for(int j=0; j < ct0; ++j, ++i)
            v[i] = aux0[j];
        for(int j=0; j < ct1; ++j, ++i)
            v[i] = aux1[j];

        bit = bit << 1; // shiftare
    }
}
void Task1()
{
    for(int i = 1; i <= m; ++i)
    {
        fin >> n >> vmax;
        nr[i] = n;
        val[i] = vmax;

        /// creare array cu elemente random
        for(int j = 0; j < n; ++j)
        {
            a[j] = Random_Number(vmax);
            copie_a[j] = a[j];
        }

        fout << "Elemente: " << n << " " << "Valoare maxima: " << vmax << "\n\n";


        auto timp_start = high_resolution_clock::now();
        auto timp_end = high_resolution_clock::now();
        auto timp_total = duration_cast<milliseconds>(timp_end - timp_start);


        /// Bubble Sort
        if(n <= 50000)  // am pus o limita pt a arata ineficienta
        {
            timp_start = high_resolution_clock::now();
            Bubble_Sort(n, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Bubble Sort: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }
        else
            fout << "Bubble Sort este ineficient pe tablouri foarte mari." << "\n";


        /// Count Sort
        if(vmax <= 100000)
        {
            timp_start = high_resolution_clock::now();
            Count_Sort(n, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Count Sort: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }
        else
            fout << "Count Sort nu functioneaza bine pe numere mari (am pus limita 100000)." << "\n";
            // datele nu pot fi memorate cu ajutorul unui array de tip int daca valorile sunt prea mari


        /// Merge Sort
        {
            timp_start = high_resolution_clock::now();
            Merge_Sort(0, n-1, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Merge Sort: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }


        /// Quick Sort - V1
        {
            timp_start = high_resolution_clock::now();
            Quick_Sort1(0, n-1, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Quick Sort - V1: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }


        /// Quick Sort - V2 - mediana din 3
        {
            timp_start = high_resolution_clock::now();
            Quick_Sort2(0, n-1, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Quick Sort - V2 - mediana din 3: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }


        /// Quick Sort - V3 - cu pivot random
        {
            timp_start = high_resolution_clock::now();
            Quick_Sort3(0, n-1, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Quick Sort - V3 - pivot random: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }


        /// Radix Sort - V1 - baza 10 - LSD
        {
            timp_start = high_resolution_clock::now();
            Radix_Sort(n, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Radix Sort - LSD: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }


        /// Radix Sort - V2 - operatii pe biti
        {
            timp_start = high_resolution_clock::now();
            Radix_Sort2(n, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Radix Sort - op. pe biti: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }


        /// Functia Sort din STL
        {
            timp_start = high_resolution_clock::now();
            sort(a, a+n);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Sort din STL: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }

        fout << "\n\n";
    }
}


void Task2()
{
/// Cazul in care avem un array deja sortat
    fout << "\n\n\n";

    for(int i = 1; i <= m; ++i)
    {

        /// creare array cu elemente random
        for(int j = 0; j < nr[i]; ++j)
        {
            a[j] = Random_Number(val[i]);
            copie_a[j] = a[j];
        }

        fout << "Array deja sortat :" << "\n";
        fout << "Elemente: " << nr[i] << " " << "Valoare maxima: " << val[i] << "\n\n";
        sort(a,a+nr[i]);

        auto timp_start = high_resolution_clock::now();
        auto timp_end = high_resolution_clock::now();
        auto timp_total = duration_cast<milliseconds>(timp_end - timp_start);


        /// Bubble Sort
        if(n <= 50000)
        {
            timp_start = high_resolution_clock::now();
            Bubble_Sort(n, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Bubble Sort: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
        }
        else
            fout << "Bubble Sort este ineficient pe tablouri foarte mari." << "\n";


        /// Count Sort
        if(vmax <= 100000)
        {
            timp_start = high_resolution_clock::now();
            Count_Sort(n, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Count Sort: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
        }
        else
            fout << "Count Sort nu functioneaza bine pe numere mari (am pus limita 100000)" << "\n";


        /// Merge Sort
        {
            timp_start = high_resolution_clock::now();
            Merge_Sort(0, n-1, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Merge Sort: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
        }


        /// Quick Sort - V1
        {
            timp_start = high_resolution_clock::now();
            Quick_Sort1(0, n-1, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Quick Sort - V1: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
        }


        /// Quick Sort - V2 - mediana din 3
        {
            timp_start = high_resolution_clock::now();
            Quick_Sort2(0, n-1, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Quick Sort - V2 - mediana din 3: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
            Restabilire_Array(a, copie_a, n);
        }


        /// Quick Sort - V3 - cu pivot random
        {
            timp_start = high_resolution_clock::now();
            Quick_Sort3(0, n-1, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Quick Sort - V3 - pivot random: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
        }


        /// Radix Sort - V1 - baza 10 - LSD
        {
            timp_start = high_resolution_clock::now();
            Radix_Sort(n, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Radix Sort - LSD: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
        }


        /// Radix Sort - V2 - operatii pe biti
        {
            timp_start = high_resolution_clock::now();
            Radix_Sort2(n, a);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Radix Sort - op. pe biti: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
        }


        /// Functia Sort din STL
        {
            timp_start = high_resolution_clock::now();
            sort(a, a+n);
            timp_end = high_resolution_clock::now();
            timp_total = duration_cast<milliseconds>(timp_end - timp_start);
            fout << "Sort din STL: " << timp_total.count() << " milisecunde " << Sorted_Vector(n,a) << "\n";
        }

        fout << "\n\n";
    }

}
int main()
{
    fin >> m;
    Task1();
    Task2();

    fin.close();
    fout.close();

    return 0;
}


/// alte functii

int Random_Number(int vmax)
{
    int x;
    x = rand();
    return x % vmax;
}

void Restabilire_Array(int a[], int copie_a[],int n)
{
    for(int i=0; i < n; ++i)
    {
        a[i] = copie_a[i];
    }
}

bool Sorted_Vector(int n, int v[])
{
    for(int i=0; i < n-1; ++i)
        if(v[i] > v[i+1])
            return 0;
    return 1;
}
