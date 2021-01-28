#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Klient.hpp"
#include "Sklep.hpp"
//ten plik zawiera klase ktora odpowiedzialna jest za kupno, przyjmujemy koszyk klienta, sprawdzamy czy ma wystarczajace srodki i dokonujemy zakupu
class Handel {
public:
	void zakup(klient &k, sklep& s) {
		if (zsumuj_koszyk(k) <= k.get_portfel()) { // warunek czy klient ma wystarczajaco srodkow na koncie
			for (auto x : k.get_koszyk()) {
				std::string new_Name = x.get_Name();
				double new_Rozmiar = x.get_Rozmiar();
				auto result = std::find_if(s.get_v_zagli().begin(), s.get_v_zagli().end(), [&new_Name, &new_Rozmiar](produkt p) { return p.get_Name() == new_Name && p.get_Rozmiar() == new_Rozmiar; });
				result->zmniejsz_Ilosc(x.get_Ilosc());
				std::remove_if(s.get_v_zagli().begin(), s.get_v_zagli().end(), [](produkt p) {return p.get_Ilosc() == 0; }); // usuniecie produktu jesli jego ilosc spadnie do zera
			}
			k.dodaj_do_portfela( - zsumuj_koszyk(k)*(k.get_rabat())); // modyfikacja portfela klienta z uwzglednieniem rabatu
			k.get_koszyk().clear();
			k.set_Ilosc(0);
			std::cout << " Dokonano zakupu " << std::endl;
		} else {std::cout << "Nie wystarczajace srodki w portfelu, dodaj srodki" << std::endl;}
	}
	double zsumuj_koszyk(klient k) { // ta funkcja odpowiedzialna jest za obliczenie jaki jest koszt calego koszyka
		double suma = 0;
		for (auto x : k.get_koszyk()) { suma = x.get_Cena() * x.get_Ilosc() + suma; }
		return suma;
	}
};