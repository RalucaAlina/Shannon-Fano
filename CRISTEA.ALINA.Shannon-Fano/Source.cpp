#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

float p[100], suma, aux;
int w, i, j, n;
string cod[100];

void recursiv(int init, int fin) {
    float dif_min = 1, suma1, suma2, gr1[50], gr2[50]; int k = 0;
    for (i = init; i < fin; i++) {
        suma1 = suma2 = 0;
        for (j = init; j <= fin; j++) { gr1[i] = 0; gr2[i] = 0; }

        for (j = init; j <= i; j++) {
            gr1[j] = p[j];
            suma1 += gr1[j];
        }
        for (j = i + 1; j <= fin; j++) {
            gr2[j - init - 1] = p[j];
            suma2 += gr2[j - init - 1];
        }
        if (abs(suma1 - suma2) < dif_min) {
            dif_min = abs(suma1 - suma2);
            k = i;
        }
    }
    cout << endl << "GR1: [";
    for (j = init; j <= k; j++) {
        gr1[j - init + 1] = p[j];
        cout << gr1[j - init + 1] << "  ";
    }
    cout << "] - (0)" << endl;
    cout << "GR2: [";
    for (j = k + 1; j <= fin; j++) {
        gr2[j - k] = p[j];
        cout << gr2[j - k] << "  ";
    }
    cout << "] - (1)" << endl;

    for (i = init; i <= k; i++) {
        cod[i] += "0";
    }
    for (i = k + 1; i <= fin; i++) {
        cod[i] += "1";
    }

    if (k - init + 1 > 1) recursiv(init, k);
    if (fin - k > 1)recursiv(k + 1, fin);
}

int main()
{
    //Etapa 1: lista de probabilitati
    cout << "0-random; 1-de la tastatura" << endl;
    cin >> w;
    if (w == 0) {
        cout << endl << "Numarul de simboluri/probabilitati: "; cin >> n;
        for (i = 1; i <= n; i++) {
            p[i] = rand() + 1;
            suma += p[i];
        }
        for (i = 1; i <= n; i++) {
            p[i] /= suma;
            cout << "p" << i << "=" << p[i] << "  ";
        }
        cout << endl;
    }
    else if (w == 1) {
        cout << endl << "Numarul de mesaje/probabilitati: "; cin >> n;
        cout << "Probabilitatile:" << endl;
        for (i = 1; i <= n; i++) {
            cout << "p" << i << "="; cin >> p[i];
            suma += p[i];
        }
        while (suma > 1 || suma < 1) {
            cout << "Suma probabilitatilor nu este 1. Introduceti din nou:" << endl;
            suma = 0;
            for (i = 1; i <= n; i++) {
                cout << "p" << i << "="; cin >> p[i];
                suma += p[i];
            }
        }
    }
    //Etapa 2: sortare vector descrescator
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n - i; j++) {
            if (p[j] < p[j + 1]) {
                aux = p[j];
                p[j] = p[j + 1];
                p[j + 1] = aux;
            }
        }
    }

    //Afisare vector sortat
    cout << endl << "Vectorul probabilitatilor sortat in ordine descrescatoare:" << endl;
    for (i = 1; i <= n; i++) {
        cout << "p" << i << "=" << p[i] << " ";
    }
    cout << endl;

    //Etapele 3 si 4
    recursiv(1, n);
    cout << endl << "CODURILE:" << endl;
    for (i = 1; i <= n; i++) { cout << p[i] << " - " << cod[i] << endl; }


    return 0;
}
