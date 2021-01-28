#pragma once
#include <vector>
#include <iostream>
#include "Pozycja.hpp"
#include <algorithm>

class sklep {
public:
	sklep() {}
	bool sprawdz_czy_istnieje(std::string& s, double r) { //ta funkcja sprawdza czy istnieje w sklepie produkt o podanej nazwie i rozmiarze
		auto result = std::find_if(v_zagli.begin(), v_zagli.end(), [&s, &r](produkt p) { return p.get_Name() == s && p.get_Rozmiar() == r; });
		if (result != v_zagli.end()) {return true;}
		else {return false;}
	}
	void dodaj_do_stalych(std::string &s) { // dodanie imienia klienta do listy stalych klientow
		lista_stalych.emplace_back(s);
	}
	void dodaj_nowy(std::string& s) { // dodanie nazwy nowego produtku ktory wczesniej nie byl dostepny
		wektor_nazw_zagli.emplace_back(s);
	}
	bool sprawdz_klienta(std::string& s) { //sprawdzenie czy klient nalezy do stalych klientow
		auto result0 = std::find_if(lista_stalych.begin(), lista_stalych.end(), [&s](std::string st) {return st == s; });
		if (result0 != lista_stalych.end()) {return true;}
		else {return false;}
	}
	void dodaj(std::string nazwa, double cena, double rozmiar, int ilosc) { //dostawa produktu, sprawdzenie czy istnieje juz taki produkt, jesli tak to zwiekszenie ilosc, jesli nie to dodanie do wektora
			auto result = std::find_if(v_zagli.begin(), v_zagli.end(), [&nazwa, &rozmiar](produkt p) { return p.get_Name() == nazwa && p.get_Rozmiar() == rozmiar; });
			if (result != v_zagli.end()) { result->zwieksz_Ilosc(ilosc);}
			else {v_zagli.push_back(produkt(nazwa, cena, rozmiar, ilosc));}
	}
	bool sprawdz_ilosc(int i, std::string s, double r ){ // sprawdzanie czy zadana ilosc produktu o podanej nazwie jest dostepna
		auto result = std::find_if(v_zagli.begin(), v_zagli.end(), [&s, &r](produkt p) { return p.get_Name() == s && p.get_Rozmiar() == r; });
		if (result->get_Ilosc() >= i) {return true;}
		else {return false;}
	}
	void wyswietl_z() { //wyswietla wszystkie dostepne produktu, posortowane alfabetycznie
		std::cout << " " << std::endl;
		std::cout << "Dostepne zagle: " << std::endl;
		int i = 0;
		std::sort(wektor_nazw_zagli.begin(), wektor_nazw_zagli.end()); 
		for (auto x : wektor_nazw_zagli) {
			++i;
			auto result = std::find_if(v_zagli.begin(), v_zagli.end(), [&x](produkt p) {return p.get_Name() == x; });
			if (result != v_zagli.end()) { std::cout << i <<"." << x << " " << std::endl; }
			else { std::cout << i << "." << x << " wyprzedany" << std::endl; }
		}
	}
	//bool comp(produkt &lhs, produkt &rhs) { return lhs.get_Rozmiar() < rhs.get_Rozmiar(); }
	void wyswietl_z1(std::string n, int i) { //wyswietla wszystkie dostepne rozmiary wraz z cena, posortowane cena lub rozmiarem
		auto result = std::find_if(v_zagli.begin(), v_zagli.end(), [&n](produkt p) { return p.get_Name() == n; });
		std::cout << " " << std::endl;
		std::cout << "Zagiel o nazwie: " << n << " Dostepne warianty: " << std::endl;
		if (i == 1) { std::sort(v_zagli.begin(), v_zagli.end(), [](produkt& p, produkt& s) {return p.get_Rozmiar() < s.get_Rozmiar(); }); std::cout << "Posortowano rozmiarem" << std::endl; }
		if (i == 2){ std::sort(v_zagli.begin(), v_zagli.end(), [](produkt& p, produkt& s) {return p.get_Cena() < s.get_Cena(); }); std::cout << "Posortowano cena" << std::endl; }
		else if (i != 1 && i != 2) { std::cout << "Niepoprawna komenda, posortowano defaultowo" << std::endl; }
		else if (result == v_zagli.end()) { std::cout << "Brak dostepnych ezgemplarzy, poczekaj na dostawe" << std::endl;  }
		for (auto x : v_zagli) {if (x.get_Name() == n) {std::cout << "Rozmiar: " << x.get_Rozmiar() << " Dostepna ilosc: " << x.get_Ilosc() << " sztuk cena: " << x.get_Cena() << " zlotych" << std::endl;}}
		std::cout << " " << std::endl;
		std::cout << "Dodaj do koszyka: wpisz d , Wyjdz do menu klienta: wpisz w" << std::endl;
	}
	std::vector<produkt>& get_v_zagli() { return v_zagli ; }
	std::vector<std::string> get_v_nazwa_z() { return wektor_nazw_zagli; }
	std::vector<std::string> get_lista() { return lista_stalych; }
private:
	std::vector<produkt> v_zagli;
	std::vector<std::string> lista_stalych;
	std::vector<std::string> wektor_nazw_zagli = { "pure" ,"freek", "idol" , "avanti" };
};
