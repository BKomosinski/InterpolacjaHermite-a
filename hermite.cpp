#include<iostream>
#include<iomanip>
#include <cmath>
#include"Interval.h"

using namespace std;

long double oblicz_wartosc_wielomianu(long double* wspolczynniki, int stopien, long double x) {
    long double wynik = wspolczynniki[stopien];

    // obliczanie wartości wielomianu
    for (int i = stopien - 1; i >= 0; i--) {
        wynik = wynik * x + wspolczynniki[i];
    }

    return wynik;
}

void oblicz_wspolczynniki_wielomianu(long double* X, long double* tabFx, int* krotnosci, int laczna_liczba_wezlow,int iloscX)
{
    long double* tabX = new long double[laczna_liczba_wezlow];
    int* tabPochodnych = new int[laczna_liczba_wezlow];
    for (int i = 0; i < laczna_liczba_wezlow; i++)//zerowanie
    {
        tabX[i] = 0;
        tabPochodnych[i] = 0;
    }

    int last = 0; //Wypełnianie tabX
    for (int i = 0; i < iloscX; i++) {
        for (int j = 0; j < krotnosci[i]; j++) {
            tabX[last] = X[i];
            last++;
        }
    }

    for (int i = 1; i < laczna_liczba_wezlow; i++)//zliczanie którą pochodną jest dana wartość
    {
        if (tabX[i] == tabX[i - 1])
        {
            tabPochodnych[i] = tabPochodnych[i - 1] + 1;
        }
        else
            tabPochodnych[i] = 0;
    }

    for (int i = 1; i < laczna_liczba_wezlow; i++)//i = poziom ilorazu róźnicowego
    {
        for (int j = laczna_liczba_wezlow - 1; j >= i; j--)//liczenie dolnego trójkąta tej tabelki
        {
            if (tabPochodnych[j] == 0)
            {
                tabFx[j] = (tabFx[j] - tabFx[j - 1 - tabPochodnych[j - 1]]) / (tabX[j] - tabX[j - i]);
            }
            else
            {
                tabFx[j] /= (long double)i;
                tabPochodnych[j]--;

            }
        }

    }

    for (int j = laczna_liczba_wezlow - 1; j >= 0; j--)
    {
        for (int i = j; i < laczna_liczba_wezlow - 1; i++)
            tabFx[i] = tabFx[i] - tabFx[i + 1] * tabX[j];
    }

}

interval_arithmetic::Interval<long double> oblicz_wartosc_wielomianu2(interval_arithmetic::Interval<long double>* wspolczynniki, int stopien, interval_arithmetic::Interval<long double> x) {
    interval_arithmetic::Interval<long double> wynik = wspolczynniki[stopien];

    // obliczanie wartości wielomianu
    for (int i = stopien - 1; i >= 0; i--) {
        wynik = wynik * x + wspolczynniki[i];
    }

    return wynik;
}

void oblicz_wspolczynniki_wielomianu2(interval_arithmetic::Interval<long double>* X, interval_arithmetic::Interval<long double>* tabFx, int* krotnosci, int laczna_liczba_wezlow, int iloscX)
{
    // ...{
    interval_arithmetic::Interval<long double>* tabX = new interval_arithmetic::Interval<long double>[laczna_liczba_wezlow];
    int* tabPochodnych = new int[laczna_liczba_wezlow];
    for (int i = 0; i < laczna_liczba_wezlow; i++)//zerowanie
    {
        tabX[i] = interval_arithmetic::Interval<long double>(0, 0);
        tabPochodnych[i] = 0;
    }

    int last = 0; //Wypełnianie tabX
    for (int i = 0; i < iloscX; i++) {
        for (int j = 0; j < krotnosci[i]; j++) {
            tabX[last] = X[i];
            last++;
        }
    }

    for (int i = 1; i < laczna_liczba_wezlow; i++)//zliczanie którą pochodną jest dana wartość
    {
        if (tabX[i].a == tabX[i - 1].a && tabX[i].b == tabX[i - 1].b)
        {
            tabPochodnych[i] = tabPochodnych[i - 1] + 1;
        }
        else
            tabPochodnych[i] = 0;
    }

    for (int i = 1; i < laczna_liczba_wezlow; i++)//i = poziom ilorazu róźnicowego
    {
        for (int j = laczna_liczba_wezlow - 1; j >= i; j--)//liczenie dolnego trójkąta tej tabelki
        {
            if (tabPochodnych[j] == 0)
            {
                tabFx[j] = (tabFx[j] - tabFx[j - 1 - tabPochodnych[j - 1]]) / (tabX[j] - tabX[j - i]);
            }
            else
            {
                tabFx[j] = tabFx[j] *( 1 / (long double)i);
                tabPochodnych[j]--;
            }
        }
    }

    for (int j = laczna_liczba_wezlow - 1; j >= 0; j--)
    {
        for (int i = j; i < laczna_liczba_wezlow - 1; i++) {
            tabFx[i] = tabFx[i] - (tabFx[i +1] * tabX[j]);
            
        }
    }
}
