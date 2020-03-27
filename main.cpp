#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <vector>
using namespace std;

struct InformationAboutSingleContact
{
    string firstName, lastName, phoneNumber, email, address;
    int id;
};

vector<InformationAboutSingleContact> loadContactList(int totalAmountOfContacts, InformationAboutSingleContact acquaintance)
{
    string line;
    fstream file;
    vector<InformationAboutSingleContact> acquaintances;
    char searchedSign='|';

    file.open("ksiazka.txt", ios::in);

    if(file.good()==true)
    {
        while (!file.eof())
        {
            for (int i=0; i<totalAmountOfContacts; i++)
            {
                getline(file,line);

                size_t position1 = line.find(searchedSign);
                acquaintance.id = atoi((line.substr(0,position1)).c_str());

                size_t position2 = line.find( searchedSign, position1 + 1 );
                acquaintance.firstName = line.substr(position1+1,(position2-position1-1));

                size_t position3 = line.find( searchedSign, position2 + 1 );
                acquaintance.lastName = line.substr(position2+1,(position3-position2-1));

                size_t position4 = line.find( searchedSign, position3 + 1 );
                acquaintance.phoneNumber = line.substr(position3+1,(position4-position3-1));

                size_t position5 = line.find( searchedSign, position4 + 1 );
                acquaintance.email = line.substr(position4+1,(position5-position4-1));

                size_t position6 = line.find( searchedSign, position5 + 1 );
                acquaintance.address = line.substr(position5+1,(position6-position5-1));

                acquaintances.push_back(acquaintance);
            }
        }
    }
    file.close();

    return acquaintances;
}

int checkTotalAmountOfContacts ()
{
    int totalAmountOfContacts;
    int LineNumber=0;

    fstream file;
    file.open("ksiazka.txt", ios::in);

    if(file.good()==false)
        totalAmountOfContacts=0;

    else
    {
        string line;
        while (getline(file, line))
        {
            LineNumber++;
        }
        totalAmountOfContacts=LineNumber;
    }

    file.close();
    return totalAmountOfContacts;
}

void saveNewContact(InformationAboutSingleContact acquaintance, vector<InformationAboutSingleContact>acquaintances, int totalAmountOfContacts)
{
    string firstName, lastName, phoneNumber, email, address;
    int id;

    cout<<"Podaj imie: ";
    cin >> firstName;
    cout<<"Podaj nazwisko: ";
    cin >> lastName;
    cout<<"Podaj numer telefonu: ";
    cin >> phoneNumber;
    cout<<"Podaj e-mail: ";
    cin >> email;
    cout<<"Podaj adres: ";
    cin.sync();
    getline(cin, address);

    fstream file;
    file.open("ksiazka.txt", ios::in);

    if(file.good()==false)
        id = 1;
    else
        id = acquaintances[totalAmountOfContacts-1].id + 1;

    file.close();

    file.open("ksiazka.txt", ios::out | ios::app);
    file << id << '|' << firstName << '|' << lastName << '|' << phoneNumber << '|' << email << '|' << address << '|' << endl;
    file.close();

    cout << "Kontakt dodano do ksiazki adresowej: " << firstName << " " << lastName << endl;
    Sleep(2000);
}

void searchByFirstName(int totalAmountOfContacts, vector<InformationAboutSingleContact>acquaintances)
{
    string firstName;
    string correctData = "";

    cout << "Podaj imie szukanego kontaktu ";
    cin >> firstName;

    for(int i=0; i<totalAmountOfContacts; i++)
    {
        if(acquaintances[i].firstName==firstName)
        {
            correctData = "OK";
            cout<<endl;
            cout<<"Imie i nazwisko: "<< acquaintances[i].firstName << " "<< acquaintances[i].lastName << endl;
            cout<<"Numer telefonu: " << acquaintances[i].phoneNumber << endl;
            cout<<"E-mail: " << acquaintances[i].email << endl;
            cout<<"Adres: " << acquaintances[i].address << endl ;
        }
    }
    cout<<endl;

    if(correctData == "OK")
    {
        cout << "Wyswietlono wszystkie kontakty o takim imieniu." << endl;
    }
    else
    {
        cout << "Brak kontaktow o wskazanym imieniu." << endl;
    }

    cout<<"Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void searchByLastName(int totalAmountOfContacts, vector<InformationAboutSingleContact>acquaintances)
{
    string lastName;
    string correctData = "";

    cout << "Podaj nazwisko szukanego kontaktu ";
    cin >> lastName;
    for(int i=0; i<totalAmountOfContacts; i++)
    {
        if(acquaintances[i].lastName == lastName)
        {
            correctData = "OK";
            cout<<endl;
            cout<<"Imie i nazwisko: "<< acquaintances[i].firstName << " "<< acquaintances[i].lastName << endl;
            cout<<"Numer telefonu: " << acquaintances[i].phoneNumber << endl;
            cout<<"E-mail: " << acquaintances[i].email << endl;
            cout<<"Adres: " << acquaintances[i].address << endl ;
        }
    }
    cout<<endl;

    if(correctData == "OK")
    {
        cout << "Wyswietlono wszystkie kontakty o takim nazwisku." << endl;
    }
    else
    {
        cout << "Brak kontaktow o wskazanym nazwisku." << endl;
    }

    cout<<"Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void displayAllContacts(int totalAmountOfContacts, vector<InformationAboutSingleContact> acquaintances)
{
    fstream file;
    file.open("ksiazka.txt", ios::in);

    if(file.good()==false)
    {
        cout<<"Twoja ksiazka adresowa jest pusta." << endl;
    }

    else
    {
        for(int i=0; i<totalAmountOfContacts; i++)
        {
            cout<<endl;
            cout << acquaintances[i].id << ". " << acquaintances[i].firstName <<" "<< acquaintances[i].lastName << endl;
            cout<<"Nr tel.: " << acquaintances[i].phoneNumber <<", e-mail: " << acquaintances[i].email << endl;
            cout <<"Adres: " << acquaintances[i].address << endl ;
        }
    }
    file.close();

    cout<<endl;
    cout<<"Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();

}

void deleteContact (int totalAmountOfContacts, vector<InformationAboutSingleContact> acquaintances)
{
    fstream file;
    int id;
    char userChoiceSideMenu;
    cout << "Podaj numer ID kontaktu ktory zamierzasz usunac ";
    cin >> id;
    cout << "Usunac kontakt o numerze ID " << id << "? (potwierdz klawiszem t/n) ";
    cin >> userChoiceSideMenu;
    cout << endl;

    if (userChoiceSideMenu == 't')
    {
        for(int i = 0; i < totalAmountOfContacts; i++)
        {
            if(acquaintances[i].id == id)
            {
                acquaintances.erase(acquaintances.begin() + i);
            }
        }

        if ((acquaintances.size())/2 == totalAmountOfContacts)
        {
            cout << "Kontakt o wskazanym numerze ID nie istnieje." << endl;
        }

        else
        {
            file.open("ksiazka.txt", ios::out);
            for(int i = 0; i < totalAmountOfContacts-1; i++)
            {
                file << acquaintances[i].id << '|' << acquaintances[i].firstName << '|' << acquaintances[i].lastName << '|' << acquaintances[i].phoneNumber << '|' << acquaintances[i].email << '|' << acquaintances[i].address << '|' << endl;
            }
            file.close();
            cout << "Adresat zostal usuniety. ";
        }
    }

    cout << endl;
    cout << "Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void editContact (int totalAmountOfContacts, vector<InformationAboutSingleContact> acquaintances)
{
    fstream file;
    int id;
    char userChoiceSideMenu;
    string changedData;
    string correctID="";

    cout << "Podaj numer ID kontaktu ktory chcesz edytowac ";
    cin >> id;

    for(int i = 0; i < totalAmountOfContacts; i++)
    {
        if(acquaintances[i].id == id)
        {
            correctID = "ID poprawne";
        }
    }

    if (correctID == "ID poprawne")
    {
        cout << "Ktore dane chcesz edytowac? " << endl;
        cout << "1. Imie" << endl;
        cout << "2. Nazwisko" << endl;
        cout << "3. Numer telefonu" << endl;
        cout << "4. E-mail" << endl;
        cout << "5. Adres" << endl;
        cout << "6. Powrot do menu glownego" << endl;
        cout << "Twoj wybor: ";
        cin >> userChoiceSideMenu;
        cout << endl;

        if (userChoiceSideMenu == '1')
        {
            for(int i = 0; i < totalAmountOfContacts; i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualne imie: " << acquaintances[i].firstName <<endl;
                    cout << "Zmiana na : " ;
                    cin >> changedData;
                    acquaintances[i].firstName = changedData;
                    cout << endl << "Imie zostalo zmienione."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu == '2')
        {
            for(int i = 0; i < totalAmountOfContacts; i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualne nazwisko: " << acquaintances[i].lastName <<endl;
                    cout << "Zmiana na : " ;
                    cin >> changedData;
                    acquaintances[i].lastName = changedData;
                    cout << endl << "Nazwisko zostalo zmienione."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu == '3')
        {
            for(int i = 0; i < totalAmountOfContacts; i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualny nr. telefonu : " << acquaintances[i].phoneNumber <<endl;
                    cout << "Zmiana na : " ;
                    cin >> changedData;
                    acquaintances[i].phoneNumber = changedData;
                    cout << endl << "Nr. telefonu zostal zmieniony."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu == '4')
        {
            for(int i = 0; i < totalAmountOfContacts; i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualny email: " << acquaintances[i].email <<endl;
                    cout << "Zmiana na : " ;
                    cin >> changedData;
                    acquaintances[i].email = changedData;
                    cout << endl << "Email zostal zmieniony."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu == '5')
        {
            for(int i = 0; i < totalAmountOfContacts; i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualny adres: " << acquaintances[i].address <<endl;
                    cout << "Zmiana na : " ;
                    cin.sync();
                    getline(cin, changedData);
                    acquaintances[i].address = changedData;
                    cout << endl << "Adres zostal zmieniony."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu=='6')
        {
            exit(0);
        }

        file.open("ksiazka.txt", ios::out);
        for(int i = 0; i < totalAmountOfContacts; i++)
        {
            file << acquaintances[i].id << '|' << acquaintances[i].firstName << '|' << acquaintances[i].lastName << '|' << acquaintances[i].phoneNumber << '|' << acquaintances[i].email << '|' << acquaintances[i].address << '|' << endl;
        }
        file.close();


    }
    else
    {
        cout << "Kontakt o wskazanym numerze ID nie istnieje." << endl;
    }

    cout << endl;
    cout << "Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

int main()
{
    InformationAboutSingleContact acquaintance;
    int totalAmountOfContacts = checkTotalAmountOfContacts();
    vector<InformationAboutSingleContact> acquaintances = loadContactList(totalAmountOfContacts, acquaintance);

    char userChoiceMainMenu;
    while(1)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresta" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        cin >> userChoiceMainMenu;
        cout << endl;

        if (userChoiceMainMenu=='1')
        {
            saveNewContact(acquaintance, acquaintances, totalAmountOfContacts);
        }

        else if (userChoiceMainMenu=='2')
        {
            searchByFirstName(totalAmountOfContacts, acquaintances);
        }

        else if (userChoiceMainMenu=='3')
        {
            searchByLastName(totalAmountOfContacts, acquaintances);
        }

        else if (userChoiceMainMenu=='4')
        {
            displayAllContacts(totalAmountOfContacts, acquaintances);
        }

        else if (userChoiceMainMenu=='5')
        {
            deleteContact(totalAmountOfContacts, acquaintances);
            totalAmountOfContacts = checkTotalAmountOfContacts();
        }

        else if (userChoiceMainMenu=='6')
        {
            editContact(totalAmountOfContacts, acquaintances);
        }

        else if (userChoiceMainMenu=='9')
        {
            exit(0);
        }

        totalAmountOfContacts = checkTotalAmountOfContacts();
        acquaintances = loadContactList(totalAmountOfContacts, acquaintance);
    }
    return 0;
}
