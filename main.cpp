#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>


using namespace std;

struct AddressBook
{
    string ID;
    string firstName;
    string lastName;
    string phoneNumber;
    string emailAddress;
    string address;
};

int CheckID ( vector <AddressBook> &addressee);
void AddingAddressee (vector <AddressBook> &addressee);
void WriteToVector( vector <AddressBook> &addressee);
void FindByFirstName (vector <AddressBook> &addressee);
void FindByLastName (vector <AddressBook> &addressee);
void DisplayAllContacts (vector <AddressBook> &addressee);
void DeleteContact (vector <AddressBook> &addressee);
void EditContact (vector <AddressBook> &addressee);
void BookUpdate (vector <AddressBook> &addressee);

int main()
{
    int wybor;
    vector <AddressBook> addressee;
    while (1)
    {
        WriteToVector (addressee);
        system("cls");
        cout << " KSIAZKA ADRESOWA " << endl;
        cout << "1. Dodaj adresata " << endl;
        cout << "2. Wyszukaj po imieniu " << endl;
        cout << "3. Wyszukaj po nazwisku " << endl;
        cout << "4. Wyswietl wszystkich adresatow " << endl;
        cout << "5. Usun adresata " << endl;
        cout << "6. Edytuj adresata " << endl;
        cout << "9. Zakoncz program " << endl;
        cout << "Twoj wybor: " << endl;
        cin >> wybor;

        switch(wybor)
        {
        case 1:
            AddingAddressee (addressee);
            break;
        case 2:
            FindByFirstName (addressee);
            break;
        case 3:
            FindByLastName (addressee);
            break;
        case 4:
            DisplayAllContacts (addressee);
            break;
        case 5:
            DeleteContact (addressee);
            BookUpdate (addressee);
            break;
        case 6:
            EditContact (addressee);
            BookUpdate (addressee);
            break;
        case 9:
            exit(0);
            break;
        }
    }
    return 0;
}

int CheckID ( vector <AddressBook> &addressee)
{
    int id=0;
    int sizeOfVector;
    string idOfLastConntact;
    sizeOfVector=addressee.size();
    if (sizeOfVector==0){
        id=0;
    }
    else{
        idOfLastConntact=addressee[sizeOfVector-1].ID;
        id=atoi(idOfLastConntact.c_str());
    }
    return id;
}

void AddingAddressee (vector <AddressBook> &addressee)
{
    int ID=CheckID(addressee)+1;
    string name, surname, auxiliary, phone, email, address;
    cout << "Podaj Imie: ";
    getline(cin,auxiliary);
    getline(cin,name);
    cout << "Podaj nazwisko: ";
    getline(cin,surname);
    cout << "Podaj numer telefonu: ";
    getline(cin,phone);
    cout << "Podaj adres email: ";
    getline (cin, email);
    cout << "Podaj adres: ";
    getline (cin, address);

    fstream file;
    file.open("book.txt", ios::out |ios::app);
    file<<ID <<"|";
    file<<name<<"|";;
    file<<surname<<"|";
    file<<phone<<"|";
    file<<email<<"|";
    file<<address<<"|";
    file<<endl;
    file.close();
    system("pause");
}

void WriteToVector( vector <AddressBook> &addressee)
{
    addressee.clear();
    fstream file;
    string line;
    string contact;
    string word;
    int lengthOfContact=0;

    int j=-1;
    string variable1, variable2, variable3, variable4, variable5, variable6 ;

    file.open("book.txt", ios::in);
    if (file.good()==false)
    {
        file.open("book.txt", ios::out |ios::app);
    }
    while (getline(file,line))
    {
        contact=line;
        lengthOfContact=line.length();
        for (int i=0; i<lengthOfContact; i++)
        {
            if (contact[i]!= '|')
            {
                word = word + contact[i];
            }
            else if (contact[i]=='|')
            {
                ++j;
                if (j==0)
                {
                    variable1=word;
                }
                if (j==1)
                {
                    variable2=word;
                }
                if (j==2)
                {
                    variable3=word;
                }
                if (j==3)
                {
                    variable4=word;
                }
                if (j==4)
                {
                    variable5=word;
                }
                if (j==5)
                {
                    variable6=word;
                }
                word="";
            }
        }
        AddressBook temp {variable1, variable2, variable3, variable4, variable5, variable6};
        addressee.push_back(temp);
        j=-1;
    }
}

void FindByFirstName (vector <AddressBook> &addressee)
{
    int sizeOfVector, k=0;
    sizeOfVector=addressee.size();
    string surname;

    cout <<"Podaj imie kontaktu, ktory ma zostac wyswietlony: ";
    cin >> surname;

    for(int i=0; i<sizeOfVector; i++)
    {
        if (addressee[i].firstName==surname)
        {
            cout << addressee[i].ID << endl;
            cout << addressee[i].firstName << endl;
            cout << addressee[i].lastName << endl;
            cout << addressee[i].phoneNumber << endl;
            cout << addressee[i].emailAddress << endl;
            cout << addressee[i].address << endl;
            ++k;
        }
    }
    if (k==0)
    {
        cout << "Kontakt nie istnieje " << endl;
    }
    k=0;

    cout << endl;
    system("pause");
}

void FindByLastName (vector <AddressBook> &addressee)
{
    int sizeOfVector, k=0;
    sizeOfVector=addressee.size();
    string name;

    cout <<"Podaj nazwisko kontaktu, ktory ma zostac wyswietlony: ";
    cin >> name;

    for(int i=0; i<sizeOfVector; i++)
    {
        if (addressee[i].lastName==name)
        {
            cout << addressee[i].ID << endl;
            cout << addressee[i].firstName << endl;
            cout << addressee[i].lastName << endl;
            cout << addressee[i].phoneNumber << endl;
            cout << addressee[i].emailAddress << endl;
            cout << addressee[i].address << endl;
            ++k;
        }
    }
    if (k==0)
    {
        cout << "Kontakt nie istnieje " << endl;
    }
    k=0;
    cout << endl;
    system("pause");
}

void DisplayAllContacts (vector <AddressBook> &addressee)
{
    int sizeOfVector;
    sizeOfVector=addressee.size();
    string name;

    for(int i=0; i<sizeOfVector; i++)
    {
        cout << addressee[i].ID << endl;
        cout << addressee[i].firstName << endl;
        cout << addressee[i].lastName << endl;
        cout << addressee[i].phoneNumber << endl;
        cout << addressee[i].emailAddress << endl;
        cout << addressee[i].address << endl;
    }
    cout << endl;
    system("pause");
}

void DeleteContact (vector <AddressBook> &addressee)
{
    string ID;
    int sizeOfVector, k=0;
    char choice;
    sizeOfVector=addressee.size();
    cout <<"Podaj numer ID kontaktu, ktory ma zostac usuniety: ";
    cin >> ID;
    for(int i=0; i<sizeOfVector; i++)
    {
        if (addressee[i].ID==ID)
        {
            cout << addressee[i].ID << endl;
            cout << addressee[i].firstName << endl;
            cout << addressee[i].lastName << endl;
            cout << addressee[i].phoneNumber << endl;
            cout << addressee[i].emailAddress << endl;
            cout << addressee[i].address << endl;
            ++k;
        }
    }
    cout << endl;
    if (k!=0)
    {
        cout << "Aby potwierdzic usuniecie powyzeszgo kontaktu wcisnij 't': " << endl;
        cin >> choice;
        if(choice=='t')
        {
            for (int i=0; i<sizeOfVector; i++)
            {
                if (addressee[i].ID==ID)
                {
                    addressee.erase(addressee.begin()+i);
                }
            }
            cout << "Kontakt zostal usuniety. ";
        }
        else
        {
            cout << "Kontakt nie zostal usuniety. " << endl;
        }
    }

    else if (k==0)
    {
        cout << "Kontakt nie istnieje " << endl;
    }
    k=0;
    cout << endl;
    system("pause");
}

void EditContact (vector <AddressBook> &addressee)
{
    int choice;
    string name, surname, phone, email, address, auxiliary;
    string ID;
    int lengthOfVector;
    int k=-1;
    lengthOfVector=addressee.size();

    cout << "1 - imie " << endl;
    cout << "2 - nazwisko " << endl;
    cout << "3 - numer telefonu " << endl;
    cout << "4 - email " << endl;
    cout << "5 - adres " << endl;
    cout << "6 - powrot do menu " << endl;

    cout << "Wpisz numer ID uzytkownika ktory ma byc zmieniony:  ";
    cin >> ID;

    for(int i=0; i<lengthOfVector; i++)
    {
        if (addressee[i].ID==ID)
        {
            k=i;
            break;
        }
    }
    if (k<0)
    {
        cout << "Kontakt o wybranym ID nie istnieje. " << endl;
    }
    else
    {
        cout << endl;
        cout << "Dane wybranego kontaktu: " << endl;
        cout << addressee[k].ID << endl;
        cout << addressee[k].firstName << endl;
        cout << addressee[k].lastName << endl;
        cout << addressee[k].phoneNumber << endl;
        cout << addressee[k].emailAddress << endl;
        cout << addressee[k].address << endl;

        cout << endl;
        cout << "Co ma zostac zmienione?: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            cout << "Wpisz zmienione imie: " ;
            getline(cin,auxiliary);
            getline(cin,name);
            addressee[k].firstName = name;
            cout << "Imie zostalo zmienione " << endl;
            break;
        case 2:
            cout << "Wpisz zmienione nazwisko: " ;
            getline(cin,auxiliary);
            getline(cin,surname);
            addressee[k].lastName = surname;
            cout << "Nazwisko zostalo zmienione " << endl;
            break;
        case 3:
            cout << "Wpisz zmieniony numer telefonu: " ;
            getline(cin,auxiliary);
            getline(cin,phone);
            addressee[k].phoneNumber = phone;
            cout << "Numer telefonu zostal zmieniony " << endl ;
            break;
        case 4:
            cout << "Wpisz zmieniony email: " ;
            getline(cin,auxiliary);
            getline(cin,email);
            addressee[k].emailAddress = email;
            cout << "Adres email zostal zmieniony " << endl;
            break;
        case 5:
            cout << "Wpisz zmieniony adres: ";
            getline(cin,auxiliary);
            getline(cin,address);
            addressee[k].address = address;
            cout << "Adres zostaly zmieniony " << endl;
            break;
        case 6:
            break;
        }
    }
    k=0;
    system("pause");
}

void BookUpdate (vector <AddressBook> &addressee)
{
    int sizeOfVector;
    sizeOfVector=addressee.size();
    fstream file;
    file.open("book.txt", ios::out);

    for(int i=0; i<sizeOfVector; i++)
    {
        file << addressee[i].ID << "|";
        file << addressee[i].firstName << "|";
        file << addressee[i].lastName << "|";
        file << addressee[i].phoneNumber << "|";
        file << addressee[i].emailAddress << "|";
        file << addressee[i].address << "|";
        file << endl;
    }
}
