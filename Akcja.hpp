#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Klient.hpp"
#include "Sklep.hpp"
#include "Handel.hpp"

// ten plik zawiera klase ktora jest odpowiedzialna za akcje ktore podejmuje uzytkownik sklepu
class akcja {
public:
	int liczba_klientow = 0;
	akcja() : h{ new Handel }, s{ new sklep }, state{ true } { // domysle sklep zostaje wypelniony jakas iloscia zagli
		s->dodaj( "freek", 1100, 4.4, 5);
		s->dodaj( "freek", 1200, 4.0, 5);
		s->dodaj( "idol", 1250, 4.8, 5);
		s->dodaj( "pure", 900, 4.8, 5);
		s->dodaj( "pure", 850, 4.0, 5);
		s->dodaj( "freek", 1115, 5.2, 5);
		s->dodaj( "freek", 1000, 4.8, 5);
		s->dodaj( "idol", 1000, 4.0, 5);
	}
	~akcja() { delete h; delete s; }
	bool get_state() { return state; }
	void akcja_u() { // glowne menu
		std::string odp;
		std::cout << "Witaj w sklepie" << std::endl;
		std::cout << "Zaloguj jako: " << std::endl;
		std::cout << "Klient: wcisnij k" << std::endl;
		std::cout << "Admin: wcisnij a" << std::endl;
		std::cout << "Wyjdz ze sklepu: wcisnij w" << std::endl;
		std::cin >> odp;
		if (odp == "a") {
			bool state3 = true;
			while (state3 == true) {//menu admina
				std::cout << "Opcje: " << std::endl;
				std::cout << "Dodaj produkt: wcisnij d" << std::endl;
				std::cout << "Dodaj klienta do listy stalych klientow: wcisnij k" << std::endl;
				std::cout << "Wyjdz do glownego menu: wcisnij w" << std::endl;
				std::string odp1;
				std::cin >> odp1;
				if (odp1 == "d") {
					std::string  nazwa;
					double rozmiar, cena;
					int wybor;
					int ilosc;
					std::cout << "Wybierz z istniejacych nazw poprzez wpisanie odpowiedniego numeru " << std::endl;
					int i = 0;
					for (auto x : s->get_v_nazwa_z()) { ++i;   std::cout << i << "." << x << std::endl; }
					std::cout << "Lub dodaj zupelnie nowy produkt do listy instniejacych porduktow: wpisz 11" << std::endl;
					std::cout << " " << std::endl;
					std::cin >> wybor;
					std::cout << nazwa;
					for (int i = 0; i < s->get_v_nazwa_z().size(); ++i) {
						if (wybor == i + 1) {
							nazwa = s->get_v_nazwa_z()[wybor-1];
							std::cout << "Podaj cene: ";
							std::cin >> cena;
							std::cout << "Podaj rozmiar: ";
							std::cin >> rozmiar;
							std::cout << "Podaj ilosc: ";
							std::cin >> ilosc;
							s->dodaj(nazwa, cena, rozmiar, ilosc);
						} else {}
					}
					if (wybor == 11) {
						std::string odp3;
						std::cout << "Podaj nazwe produktu: " << std::endl;
						std::cin >> odp3;
						s->dodaj_nowy(odp3);
					}	
				}
				else if (odp1 == "w") { state3 = false; }
				else if (odp1 == "k") {
					std::string imie;
					std::cout << " " << std::endl;
					std::cout << "Podaj imie stalego klienta: " << std::endl;
					std::cin >> imie;
					s->dodaj_do_stalych(imie);
				} else { std::cout << "Niepoprawna komenda" << std::endl;}
			}
		} //koniec menu admina
		else if (odp == "k") { //menu klienta
				std::string imie, odp2;
				std::cout << "Podaj imie: " << std::endl;
				std::cin >> imie;
				bool state1 = true;
				while (state1 == true) {
					std::cout << " " << std::endl;
					std::cout << "Witaj! kliencie o imieniu: " << imie << " Mozliwe opcje: " << std::endl;
					std::cout << "Wyswietl dostepne produkty: wpisz w" << std::endl;
					std::cout << "Wyswietl swoj koszyk: wpisz k" << std::endl;
					std::cout << "Wyswietl swoj portfel: wpisz p" << std::endl;
					std::cout << "Dodaj srodki do portfela: wpisz c" << std::endl;
					std::cout << "Sfinalizuj swoje zakupy: wpisz s" << std::endl;
					std::cout << "Jesli chcesz wyjsc do menu logowania: wpisz e" << std::endl;
					std::cout << " " << std::endl;
					auto result = std::find_if(wektor_klientow.begin(), wektor_klientow.end(), [&imie](klient* k) { return k->get_imie() == imie; });
					if (result != wektor_klientow.end()) {	//poczatek petli odpowiedzialnej za istniejacego juz klienta
						std::cout << "Witamy ponownie " << imie << std::endl;
						std::cout << " " << std::endl;
						std::cin >> odp2;
						if (odp2 == "w") {
							s->wyswietl_z();
							int odp5;
							std::cout << "Jesli chcesz wybrac ktorys z produktow wpisz numer " << std::endl;
							std::cout << "Jesli chcesz wyjsc do menu klienta: wpisz 10" << std::endl;
							std::cout << " " << std::endl;
							std::cin >> odp5;
							if (odp5 == 10) {}
							else if (odp5 > s->get_v_nazwa_z().size()) {std::cout << "niepoprawny numer" << std::endl;}
							else {
								std::string odp3;
								int odp6;
								std::cout << "Posortuj rozmiarem: wpisz 1, posortuj cena: wpisz 2" << std::endl;
								std::cin >> odp6;
								for (int i = 1; i < s->get_v_nazwa_z().size()+1; ++i) {
									if (odp5 == i) {
										odp3 = s->get_v_nazwa_z()[odp5-1];
										break;
									} else {}
								}
								s->wyswietl_z1(odp3, odp6);
								std::string odp4;
								std::cin >> odp4;
								if (odp4 == "d") {
									double rozmiar1;
									int ilosc1;
									std::cout << "Podaj rozmiar: " << std::endl;
									std::cin >> rozmiar1;
									std::cout << "Podaj ilosc: " << std::endl;
									std::cin >> ilosc1;
									if (s->sprawdz_czy_istnieje(odp3, rozmiar1) == true) {
										auto result1 = std::find_if(s->get_v_zagli().begin(), s->get_v_zagli().end(), [&odp3, &rozmiar1](produkt p) { return p.get_Name() == odp3 && p.get_Rozmiar() == rozmiar1; });
										double new_cena = result1->get_Cena();
										(*result)->dodaj_do_koszyka(odp3, new_cena, rozmiar1, ilosc1, *s);}
									else {std::cout << "Nie ma takiego rozmiaru" << std::endl;}
								}
								else if (odp4 == "w") {}
								else {std::cout << "Niepoprawna komenda" << std::endl;}
							}
						}
						else if (odp2 == "k") { (*result)->wyswietl_koszyk();  std::cout << " " << std::endl;  }
						else if (odp2 == "p") { (*result)->id(); }
						else if (odp2 == "c") {
							double suma;
							std::cout << "Podaj sume ktora chcesz dodac: " << std::endl;
							std::cin >> suma;
							(*result)->dodaj_do_portfela(suma);
						}
						else if (odp2 == "s") { (*result)->wyswietl_koszyk(); h->zakup( *(*result) , *s); }
						else if (odp2 == "e") { state1 = false; }
					}       //koniec petli odpowiedzialnej za przyjecie istniejacego juz klienta
					else {	//poczatek petli odpowiedzzialnej za przyjecie nowego klienta
						bool staly = s->sprawdz_klienta(imie);
						klient* kli = new klient(imie, staly);
						wektor_klientow.emplace_back(kli);
						++liczba_klientow;
						std::cin >> odp2;
						if (odp2 == "w") {
							s->wyswietl_z();
							std::string odp3;
							int odp5;
							std::cout << "Jesli chcesz wybrac ktorys z produktow wpisz numer: " << std::endl;
							std::cout << "Jesli chcesz wyjsc do menu klienta: wpisz 10" << std::endl;
							std::cout << " " << std::endl;
							std::cin >> odp5;
							for (int i = 1; i < s->get_v_nazwa_z().size() + 1; ++i) {
								if (odp5 == i) {
									odp3 = s->get_v_nazwa_z()[odp5 - 1];
									break;
								} else {}
							}
							if (odp5 == 10) { }
							else if (odp5 > s->get_v_nazwa_z().size()) {std::cout << "niepoprawny numer" << std::endl;}
							else {
								int odp6;
								std::cout << "Posortuj rozmiarem: wpisz 1, posortuj cena: wpisz 2" << std::endl;
								std::cin >> odp6;
								s->wyswietl_z1(odp3, odp6);
								std::string odp4;
								std::cin >> odp4;
								if (odp4 == "d") {
									double rozmiar1;
									int ilosc1;
									std::cout << "Podaj rozmiar: " << std::endl;
									std::cin >> rozmiar1;
									std::cout << "Podaj ilosc: " << std::endl;
									std::cin >> ilosc1;
									if (s->sprawdz_czy_istnieje(odp3, rozmiar1) == true) {
										auto result1 = std::find_if(s->get_v_zagli().begin(), s->get_v_zagli().end(), [&odp3, &rozmiar1](produkt p) { return p.get_Name() == odp3 && p.get_Rozmiar() == rozmiar1; });
										wektor_klientow[liczba_klientow - 1]->dodaj_do_koszyka(odp3, result1->get_Cena(), rozmiar1, ilosc1, *s);
										wektor_klientow[liczba_klientow - 1]->wyswietl_koszyk();
									} else {std::cout << "Nie ma takiego rozmiaru" << std::endl;}
								} else if (odp4 == "w") {} 
								else {std::cout << "Niepoprawna komenda" << std::endl;}
							}
						}
						else if (odp2 == "k") {wektor_klientow[liczba_klientow - 1]->wyswietl_koszyk();std::cout << " " << std::endl;}
						else if (odp2 == "p") {wektor_klientow[liczba_klientow - 1]->id();}
						else if (odp2 == "e") {state1 = false;}
						else if (odp2 == "c") {
							double suma;
							std::cout << "Podaj sume ktora chcesz dodac: " << std::endl;
							std::cin >> suma;
							wektor_klientow[liczba_klientow - 1]->dodaj_do_portfela(suma);
						}
					}//koniec petli gdzie nie bylo wczesniej klienta
				}
		} //koniec menu klienta
		else if (odp == "w") { state = false; }
		else { std::cout << "Niepoprawna komenda" << std::endl;}
	}//koniec glownego menu
private:
	bool state;
	Handel* h;
	sklep* s;
	std::vector<klient*> wektor_klientow;
};
