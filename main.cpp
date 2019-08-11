#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <limits>
#include <conio.h>

using namespace std;

struct Uzytkownik
{
    int id = 0;
    string nazwa = "";
    string haslo = "";
};

struct Adresat
{
    int id = 0;
    int idUzytkownika = 0;
    string imie = "";
    string nazwisko = "";
    string numerTelefonu = "";
    string email = "";
    string adres = "";
};

int odczytBazyDanychUzytkownikowZPliku(vector <Uzytkownik> *w_uzytkownicy)
{
    int liczbaUzytkownikow = 0;

    fstream bazaDanychUzytkownikow;

    string pobranaLiniaTekstuZBazyDanych = "";

    vector <int> pozycjeZnakuRozdzielajacego;

    Uzytkownik uzytkownik;

    //Odczyt z pliku
    bazaDanychUzytkownikow.open("bazaDanychUzytkownikow.txt", ios::in);

    if(bazaDanychUzytkownikow.good() == true)
    {
        while(getline(bazaDanychUzytkownikow, pobranaLiniaTekstuZBazyDanych))
        {
            for(int i=0; i<pobranaLiniaTekstuZBazyDanych.length(); i++)
            {
                if(pobranaLiniaTekstuZBazyDanych[i] == '|')
                {
                    pozycjeZnakuRozdzielajacego.push_back(i);
                }
            }

            uzytkownik.id = atoi(pobranaLiniaTekstuZBazyDanych.substr(0, pozycjeZnakuRozdzielajacego[0]).c_str());
            uzytkownik.nazwa = pobranaLiniaTekstuZBazyDanych.substr(pozycjeZnakuRozdzielajacego[0]+1, pozycjeZnakuRozdzielajacego[1]-pozycjeZnakuRozdzielajacego[0]-1);
            uzytkownik.haslo = pobranaLiniaTekstuZBazyDanych.substr(pozycjeZnakuRozdzielajacego[1]+1, pozycjeZnakuRozdzielajacego[2]-pozycjeZnakuRozdzielajacego[1]-1);

            (*w_uzytkownicy).push_back(uzytkownik);

            pozycjeZnakuRozdzielajacego.clear();
        }
    }

    bazaDanychUzytkownikow.close();
    //Koniec odczytu pliku

    return liczbaUzytkownikow = (*w_uzytkownicy).size();
}

int logowanieUzytkownika(vector <Uzytkownik> *w_uzytkownicy)
{
    string nazwaUzytkownika = "";
    string hasloUzytkownika = "";

    cout << "LOGOWANIE UZYTKOWNIKA" << endl;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;

    vector<Uzytkownik>::iterator koniecWektora = (*w_uzytkownicy).end();
    for(vector<Uzytkownik>::iterator itr = (*w_uzytkownicy).begin(); itr !=koniecWektora; ++itr)
    {
        if(itr->nazwa == nazwaUzytkownika)
        {
            for(int liczbaProb=1; liczbaProb<4; liczbaProb++)
            {
                cout << "Podaj haslo (" << liczbaProb << "-a proba): ";
                cin >> hasloUzytkownika;

                if(itr->haslo == hasloUzytkownika)
                {
                    system( "cls" );
                    cout << "Poprawnie zalogowano!" << endl;
                    Sleep(1500);
                    system( "cls" );
                    return itr->id;
                }

                cout << "Niepoprawne haslo!" << endl;
                Sleep(1500);
                system( "cls" );
                cout << "LOGOWANIE UZYTKOWNIKA" << endl;
                cout << "Podaj nazwe uzytkownika: " << nazwaUzytkownika << endl;
            }

            system( "cls" );
            cout << "Wykorzystano maksymalna liczbe prob!" << endl;
            Sleep(1500);
            system( "cls" );
            return 0;
        }
    }

    system( "cls" );
    cout << "Uzytkownik nie istnieje!" << endl;
    Sleep(1500);
    system( "cls" );

    return 0;
}

int rejestracjaUzytkownika(vector <Uzytkownik> *w_uzytkownicy, int *w_liczbaUzytkownikow)
{
    fstream bazaDanychUzytkownikow;
    Uzytkownik uzytkownik;

    string nazwaUzytkownika = "";
    string hasloUzytkownika = "";

    cout << "REJESTRACJA UZYTKOWNIKA" << endl;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;

    vector<Uzytkownik>::iterator koniecWektora = (*w_uzytkownicy).end();
    for(vector<Uzytkownik>::iterator itr = (*w_uzytkownicy).begin(); itr !=koniecWektora; ++itr)
    {
        if(itr->nazwa == nazwaUzytkownika)
        {
            system( "cls" );
            cout << "Podany uzytkownik istnieje juz w bazie danych!";
            Sleep(1500);
            system( "cls" );
            return *w_liczbaUzytkownikow;
        }
    }

    cout << "Podaj haslo uzytkownika: ";
    cin >> hasloUzytkownika;

    uzytkownik.id = (*w_uzytkownicy).size()+1;
    uzytkownik.nazwa = nazwaUzytkownika;
    uzytkownik.haslo = hasloUzytkownika;

    (*w_uzytkownicy).push_back(uzytkownik);

    //Zapis do pliku
    bazaDanychUzytkownikow.open("bazaDanychUzytkownikow.txt", ios::out | ios::app);

    bazaDanychUzytkownikow << uzytkownik.id << '|';
    bazaDanychUzytkownikow << uzytkownik.nazwa << '|';
    bazaDanychUzytkownikow << uzytkownik.haslo << '|' << endl;

    bazaDanychUzytkownikow.close();
    //Koniec zapisu do pliku

    cout << "Uzytkownik zostal dodany do bazy danych!";
    Sleep(1500);
    system( "cls" );

    return (*w_uzytkownicy).size();
}

int menuUzytkownika(vector <Uzytkownik> *w_uzytkownicy, int *w_liczbaUzytkownikow)
{
    while(1)
    {
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;

        string opcjaMenu = "";

        do
        {
            cout << "Twoj wybor:";
            cin >> opcjaMenu;
        }
        while (opcjaMenu != "1" && opcjaMenu != "2" && opcjaMenu != "3");

        if(opcjaMenu == "1")
        {
            if(*w_liczbaUzytkownikow == 0)
            {
                system( "cls" );
                cout << "Baza danych nie zawiera Uzytkownikow! Zarejestruj sie!";
                Sleep(1500);
                system( "cls" );
            }
            else
            {
                system( "cls" );
                int idZalogowanegoUzytkownika = logowanieUzytkownika(w_uzytkownicy);

                if(idZalogowanegoUzytkownika != 0)
                {
                    return idZalogowanegoUzytkownika;
                }
            }
        }
        else if(opcjaMenu == "2")
        {
            system( "cls" );
            *w_liczbaUzytkownikow = rejestracjaUzytkownika(w_uzytkownicy, w_liczbaUzytkownikow);
        }
        else if(opcjaMenu == "3")
        {
            system( "cls" );
            cout << "Dziekujemy za skorzystanie z aplikacji!" << endl;
            exit(0);
        }
    }
}

void zapiszBazeDanychAdresatow(vector <Adresat> *w_adresaci)
{
    fstream bazaDanychAdresatow;

    //Zapis do pliku
    bazaDanychAdresatow.open("bazaDanychAdresatow.txt", ios::out);

    for(int indeksAdresata=0; indeksAdresata<(*w_adresaci).size(); indeksAdresata++)
    {
        bazaDanychAdresatow << (*w_adresaci)[indeksAdresata].id << '|';
        bazaDanychAdresatow << (*w_adresaci)[indeksAdresata].imie << '|';
        bazaDanychAdresatow << (*w_adresaci)[indeksAdresata].nazwisko << '|';
        bazaDanychAdresatow << (*w_adresaci)[indeksAdresata].numerTelefonu << '|';
        bazaDanychAdresatow << (*w_adresaci)[indeksAdresata].email << '|';
        bazaDanychAdresatow << (*w_adresaci)[indeksAdresata].adres << '|' << endl;
    }

    bazaDanychAdresatow.close();
    //Koniec zapisu do pliku
}

int odczytBazyDanychAdresatowZPliku(vector <Adresat> *w_adresaci, int idZalogowanegoUzytkownika, int *w_liczbaAdresatowGlobalna)
{
    int liczbaAdresatow = 0;

    fstream bazaDanychAdresatow;

    string pobranaLiniaTekstuZBazyDanych = "";

    vector <int> pozycjeZnakuRozdzielajacego;

    Adresat adresat;

    //Odczyt z pliku
    bazaDanychAdresatow.open("bazaDanychAdresatow.txt", ios::in);

    if(bazaDanychAdresatow.good() == true)
    {
        while(getline(bazaDanychAdresatow, pobranaLiniaTekstuZBazyDanych))
        {
            for(int i=0; i<pobranaLiniaTekstuZBazyDanych.length(); i++)
            {
                if(pobranaLiniaTekstuZBazyDanych[i] == '|')
                {
                    pozycjeZnakuRozdzielajacego.push_back(i);
                }
            }

            if(atoi(pobranaLiniaTekstuZBazyDanych.substr(pozycjeZnakuRozdzielajacego[0]+1, pozycjeZnakuRozdzielajacego[1]-pozycjeZnakuRozdzielajacego[0]-1).c_str()) == idZalogowanegoUzytkownika)
            {
                adresat.id = atoi(pobranaLiniaTekstuZBazyDanych.substr(0, pozycjeZnakuRozdzielajacego[0]).c_str());
                adresat.idUzytkownika = atoi(pobranaLiniaTekstuZBazyDanych.substr(pozycjeZnakuRozdzielajacego[0]+1, pozycjeZnakuRozdzielajacego[1]-pozycjeZnakuRozdzielajacego[0]-1).c_str());
                adresat.imie = pobranaLiniaTekstuZBazyDanych.substr(pozycjeZnakuRozdzielajacego[1]+1, pozycjeZnakuRozdzielajacego[2]-pozycjeZnakuRozdzielajacego[1]-1);
                adresat.nazwisko = pobranaLiniaTekstuZBazyDanych.substr(pozycjeZnakuRozdzielajacego[2]+1, pozycjeZnakuRozdzielajacego[3]-pozycjeZnakuRozdzielajacego[2]-1);
                adresat.numerTelefonu = pobranaLiniaTekstuZBazyDanych.substr(pozycjeZnakuRozdzielajacego[3]+1, pozycjeZnakuRozdzielajacego[4]-pozycjeZnakuRozdzielajacego[3]-1);
                adresat.email = pobranaLiniaTekstuZBazyDanych.substr(pozycjeZnakuRozdzielajacego[4]+1, pozycjeZnakuRozdzielajacego[5]-pozycjeZnakuRozdzielajacego[4]-1);
                adresat.adres = pobranaLiniaTekstuZBazyDanych.substr(pozycjeZnakuRozdzielajacego[5]+1, pozycjeZnakuRozdzielajacego[6]-pozycjeZnakuRozdzielajacego[5]-1);

                (*w_adresaci).push_back(adresat);
            }

            *w_liczbaAdresatowGlobalna = *w_liczbaAdresatowGlobalna +1;

            pozycjeZnakuRozdzielajacego.clear();
        }
    }

    bazaDanychAdresatow.close();
    //Koniec odczytu pliku

    return liczbaAdresatow = (*w_adresaci).size();
}

int dodajAdresata(vector <Adresat> *w_adresaci)
{
    fstream bazaDanychAdresatow;

    Adresat adresat;

    string imie = "";
    string nazwisko = "";
    string numerTelefonu = "";
    string email = "";
    string adres = "";

    cout << "DODAJ ADRESATA" << endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;

    cin.ignore(numeric_limits < streamsize >::max(), '\n' );

    cout << "Podaj numer telefonu: ";
    getline(cin, numerTelefonu);
    cout << "Podaj adres e-mail: ";
    getline(cin, email);
    cout << "Podaj adres: ";
    getline(cin, adres);

    for(int i=0; i<(*w_adresaci).size(); i++)
    {
        if((*w_adresaci)[i].imie == imie && (*w_adresaci)[i].nazwisko == nazwisko)
        {
            cout << "Adresat istnieje juz w bazie danych!";
            Sleep(1500);
            system( "cls" );
            return (*w_adresaci).size();
        }
    }

    if((*w_adresaci).size() == 0)
    {
        adresat.id = 1;
    }
    else
    {
        adresat.id = (*w_adresaci)[(*w_adresaci).size()-1].id + 1;
    }
    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.numerTelefonu = numerTelefonu;
    adresat.email = email;
    adresat.adres = adres;

    (*w_adresaci).push_back(adresat);

    //Zapis do pliku
    bazaDanychAdresatow.open("bazaDanychAdresatow.txt", ios::out | ios::app);

    bazaDanychAdresatow << adresat.id << '|';
    bazaDanychAdresatow << adresat.imie << '|';
    bazaDanychAdresatow << adresat.nazwisko << '|';
    bazaDanychAdresatow << adresat.numerTelefonu << '|';
    bazaDanychAdresatow << adresat.email << '|';
    bazaDanychAdresatow << adresat.adres << '|' << endl;

    bazaDanychAdresatow.close();
    //Koniec zapisu do pliku

    cout << "Adresat zostal dodany do bazy danych!";
    Sleep(1500);
    system( "cls" );

    return (*w_adresaci).size();
}

void wyszukajPoImieniu(vector <Adresat> *w_adresaci)
{
    string imie = "";
    int liczbaWyszukanychAdresatow = 0;

    cout << "WYSZUKAJ PO IMIENIU" << endl;
    cout << "Podaj imie: ";
    cin >> imie;

    for(int i=0; i<(*w_adresaci).size(); i++)
    {
        if(imie == (*w_adresaci)[i].imie)
        {
            if(liczbaWyszukanychAdresatow == 0)
            {
                cout << endl;
                cout << "Id." << '\t';
                cout << "Imie" << '\t';
                cout << "Nazw." << '\t';
                cout << "Telefon" << '\t' << '\t';
                cout << "Email" << '\t' << '\t' << '\t';
                cout << "Adres" << '\t';
                cout << endl;
            }

            cout << (*w_adresaci)[i].id << '\t';
            cout << (*w_adresaci)[i].imie << '\t';
            cout << (*w_adresaci)[i].nazwisko << '\t';
            cout << (*w_adresaci)[i].numerTelefonu << '\t';
            cout << (*w_adresaci)[i].email << '\t';
            cout << (*w_adresaci)[i].adres << endl;
            liczbaWyszukanychAdresatow++;
        }
    }

    if(liczbaWyszukanychAdresatow == 0)
    {
        system( "cls" );
        cout << "Nie znaleziono Adresatow!";
        Sleep(1500);
        system( "cls" );
        return;
    }
    else
    {
        cout << endl << "Nacisnij dowolny klawisz, aby powrocic do menu glownego...";
        getch();
        system( "cls" );
    }
}

void wyszukajPoNazwisku(vector <Adresat> *w_adresaci)
{
    string nazwisko = "";
    int liczbaWyszukanychAdresatow = 0;

    cout << "WYSZUKAJ PO NAZWISKU" << endl;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;

    for(int i=0; i<(*w_adresaci).size(); i++)
    {
        if(nazwisko == (*w_adresaci)[i].nazwisko)
        {
            if(liczbaWyszukanychAdresatow == 0)
            {
                cout << endl;
                cout << "Id." << '\t';
                cout << "Imie" << '\t';
                cout << "Nazw." << '\t';
                cout << "Telefon" << '\t' << '\t';
                cout << "Email" << '\t' << '\t' << '\t';
                cout << "Adres" << '\t';
                cout << endl;
            }

            cout << (*w_adresaci)[i].id << '\t';
            cout << (*w_adresaci)[i].imie << '\t';
            cout << (*w_adresaci)[i].nazwisko << '\t';
            cout << (*w_adresaci)[i].numerTelefonu << '\t';
            cout << (*w_adresaci)[i].email << '\t';
            cout << (*w_adresaci)[i].adres << endl;
            liczbaWyszukanychAdresatow++;
        }
    }

    if(liczbaWyszukanychAdresatow == 0)
    {
        system( "cls" );
        cout << "Nie znaleziono Adresatow!";
        Sleep(1500);
        system( "cls" );
        return;
    }
    else
    {
        cout << endl << "Nacisnij dowolny klawisz, aby powrocic do menu glownego...";
        getch();
        system( "cls" );
    }
}

void wyswietlWszystkichAdresatow(vector <Adresat> *w_adresaci)
{
    cout << "WYSWIETL WSZYSTKICH ADRESATOW" << endl;

    cout << endl;
    cout << "Id." << '\t';
    cout << "Imie" << '\t';
    cout << "Nazw." << '\t';
    cout << "Telefon" << '\t' << '\t';
    cout << "Email" << '\t' << '\t' << '\t';
    cout << "Adres" << '\t';
    cout << endl;

    for(int i=0; i<(*w_adresaci).size(); i++)
    {
        cout << (*w_adresaci)[i].id << '\t';
        cout << (*w_adresaci)[i].imie << '\t';
        cout << (*w_adresaci)[i].nazwisko << '\t';
        cout << (*w_adresaci)[i].numerTelefonu << '\t';
        cout << (*w_adresaci)[i].email << '\t';
        cout << (*w_adresaci)[i].adres << endl;
    }

    cout << endl << "Nacisnij dowolny klawisz, aby powrocic do menu glownego...";
    getch();
    system( "cls" );
}

void edytujAdresata(vector <Adresat> *w_adresaci)
{
    int id, indeksAdresata = 0;
    string opcjaMenu = "";

    cout << "EDYTUJ ADRESATA" << endl;
    cout << "Podaj id: ";
    cin >> id;

    for(indeksAdresata=0; indeksAdresata<(*w_adresaci).size(); indeksAdresata++)
    {
        if((*w_adresaci)[indeksAdresata].id == id)
        {
            break;
        }
    }

    if(indeksAdresata == (*w_adresaci).size())
    {
        system( "cls" );
        cout << "Adresat o podanym ID nie istnieje!";
        Sleep(1500);
        system( "cls" );
        return;
    }

    system( "cls" );
    cout << "EDYTUJ ADRESATA O ID: " << id << endl;
    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - numer telefonu" << endl;
    cout << "4 - email" << endl;
    cout << "5 - adres" << endl;
    cout << "6 - powrot do menu" << endl;

    do
    {
        cout << "Twoj wybor:";
        cin >> opcjaMenu;
    }
    while (opcjaMenu != "1" && opcjaMenu != "2" && opcjaMenu != "3" && opcjaMenu != "4" && opcjaMenu != "5" && opcjaMenu != "6");

    if(opcjaMenu == "1")
    {
        string imie = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj imie: ";
        cin >> imie;

        (*w_adresaci)[indeksAdresata].imie = imie;

        zapiszBazeDanychAdresatow(w_adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else if(opcjaMenu == "2")
    {
        string nazwisko = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj nazwisko: ";
        cin >> nazwisko;

        (*w_adresaci)[indeksAdresata].nazwisko = nazwisko;

        zapiszBazeDanychAdresatow(w_adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else if(opcjaMenu == "3")
    {
        string numerTelefonu = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj numer telefonu: ";
        cin.ignore(numeric_limits < streamsize >::max(), '\n' );
        getline(cin, numerTelefonu);

        (*w_adresaci)[indeksAdresata].numerTelefonu = numerTelefonu;

        zapiszBazeDanychAdresatow(w_adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else if(opcjaMenu == "4")
    {
        string email = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj email: ";
        cin >> email;

        (*w_adresaci)[indeksAdresata].email = email;

        zapiszBazeDanychAdresatow(w_adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else if(opcjaMenu == "5")
    {
        string adres = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj adres: ";
        cin.ignore(numeric_limits < streamsize >::max(), '\n' );
        getline(cin, adres);

        (*w_adresaci)[indeksAdresata].adres = adres;

        zapiszBazeDanychAdresatow(w_adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else
    {
        system( "cls" );
        return;
    }
}

int usunAdresata(vector <Adresat> *w_adresaci)
{
    int id, indeksAdresata = 0;
    string potwierdzenieUsunieciaAdresata = "";

    cout << "USUN ADRESATA" << endl;
    cout << "Podaj id: ";
    cin >> id;

    for(indeksAdresata=0; indeksAdresata<(*w_adresaci).size(); indeksAdresata++)
    {
        if((*w_adresaci)[indeksAdresata].id == id)
        {
            break;
        }
    }

    if(indeksAdresata == (*w_adresaci).size())
    {
        system( "cls" );
        cout << "Adresat o podanym ID nie istnieje!";
        Sleep(1500);
        system( "cls" );
        return (*w_adresaci).size();
    }

    cout << "Potwierdz usuniecie adresata klawiszem 't': ";
    cin >> potwierdzenieUsunieciaAdresata;

    if(potwierdzenieUsunieciaAdresata == "t")
    {
        (*w_adresaci).erase((*w_adresaci).begin()+indeksAdresata);

        zapiszBazeDanychAdresatow(w_adresaci);

        cout << endl << "Adresat zostal usuniety z bazy danych!";
        Sleep(1500);
        system( "cls" );
    }
    else
    {
        cout << endl << "Nie usunieto adresata!";
        Sleep(1500);
        system( "cls" );
    }

    return (*w_adresaci).size();
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Uzytkownik> *w_uzytkownicy;
    w_uzytkownicy = &uzytkownicy;

    vector <Adresat> adresaci;
    vector <Adresat> *w_adresaci;
    w_adresaci = &adresaci;

    int liczbaAdresatowGlobalna = 0;
    int *w_liczbaAdresatowGlobalna = &liczbaAdresatowGlobalna;

    int liczbaUzytkownikow = odczytBazyDanychUzytkownikowZPliku(w_uzytkownicy);
    int *w_liczbaUzytkownikow = &liczbaUzytkownikow;

    int idZalogowanegoUzytkownika = menuUzytkownika(w_uzytkownicy, w_liczbaUzytkownikow);

    int liczbaAdresatowUzytkownika = odczytBazyDanychAdresatowZPliku(w_adresaci, idZalogowanegoUzytkownika, w_liczbaAdresatowGlobalna);

    while(1)
    {
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;

        string opcjaMenu = "";

        do
        {
            cout << "Twoj wybor:";
            cin >> opcjaMenu;
        }
        while (opcjaMenu != "1" && opcjaMenu != "2" && opcjaMenu != "3" && opcjaMenu != "4" && opcjaMenu != "5" && opcjaMenu != "6" && opcjaMenu != "9");

        if(opcjaMenu == "1")
        {
            system( "cls" );
            liczbaAdresatowUzytkownika = dodajAdresata(w_adresaci);
        }
        else if(opcjaMenu == "2")
        {
            if(liczbaAdresatowUzytkownika == 0)
            {
                system( "cls" );
                cout << "Baza danych nie zawiera Adresatow!";
                Sleep(1500);
                system( "cls" );
            }
            else
            {
                system( "cls" );
                wyszukajPoImieniu(w_adresaci);
            }
        }
        else if(opcjaMenu == "3")
        {
            if(liczbaAdresatowUzytkownika == 0)
            {
                system( "cls" );
                cout << "Baza danych nie zawiera Adresatow!";
                Sleep(1500);
                system( "cls" );
            }
            else
            {
                system( "cls" );
                wyszukajPoNazwisku(w_adresaci);
            }
        }
        else if(opcjaMenu == "4")
        {
            if(liczbaAdresatowUzytkownika == 0)
            {
                system( "cls" );
                cout << "Baza danych nie zawiera Adresatow!";
                Sleep(1500);
                system( "cls" );
            }
            else
            {
                system( "cls" );
                wyswietlWszystkichAdresatow(w_adresaci);
            }
        }
        else if(opcjaMenu == "5")
        {
            if(liczbaAdresatowUzytkownika == 0)
            {
                system( "cls" );
                cout << "Baza danych nie zawiera Adresatow!";
                Sleep(1500);
                system( "cls" );
            }
            else
            {
                system( "cls" );
                liczbaAdresatowUzytkownika = usunAdresata(w_adresaci);
            }
        }
        else if(opcjaMenu == "6")
        {
            if(liczbaAdresatowUzytkownika == 0)
            {
                system( "cls" );
                cout << "Baza danych nie zawiera Adresatow!";
                Sleep(1500);
                system( "cls" );
            }
            else
            {
                system( "cls" );
                edytujAdresata(w_adresaci);
            }
        }
        else if(opcjaMenu == "9")
        {
            system( "cls" );
            cout << "Dziekujemy za skorzystanie z aplikacji!" << endl;
            exit(0);
        }
    }

    return 0;
}
