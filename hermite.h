#ifndef HERMITE_H
#define HERMITE_H
#include"Interval.h"

long double oblicz_wartosc_wielomianu(long double* wspolczynniki, int stopien, long double x);
void oblicz_wspolczynniki_wielomianu(long double* X, long double* tabFx, int* krotnosci, int laczna_liczba_wezlow, int iloscX);
void oblicz_wspolczynniki_wielomianu2(interval_arithmetic::Interval<long double>* X, interval_arithmetic::Interval<long double>* tabFx, int* krotnosci, int laczna_liczba_wezlow, int iloscX);
interval_arithmetic::Interval<long double> oblicz_wartosc_wielomianu2(interval_arithmetic::Interval<long double>* wspolczynniki, int stopien, interval_arithmetic::Interval<long double> x) ;

#endif // HERMITE_H
