#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>


using namespace std;

struct UsersList
{
    string UserId;
    string UserLogin;
    string UserPassword;
};

struct AddressBook
{
    string ID;
    string UserId;
    string firstName;
    string lastName;
    string phoneNumber;
    string emailAddress;
    string address;
};
void UserWriteToVector (vector <UsersList> &User);
int UserCheckID (vector <UsersList> &User);
void AddingUser (vector <UsersList> &User);

int CheckID ( vector <AddressBook> &addressee);
void AddingAddressee (vector <AddressBook> &addressee);
void WriteToVector( vector <AddressBook> &addressee);
void FindByFirstName (vector <AddressBook> &addressee);
void FindByLastName (vector <AddressBook> &addressee);
void DisplayAllContacts (vector <AddressBook> &addressee);
int DeleteContact (vector <AddressBook> &addressee);
int EditContact (vector <AddressBook> &addressee);
void BookUpdate (vector <AddressBook> &addressee);

int AddresBookMenu (vector <AddressBook> &addressee, vector <UsersList> User, int UserId);
void LoginUser (vector <UsersList> &User, vector <AddressBook> &addressee );


int main()
{

    int choice;
    vector <AddressBook> addressee;
    vector <UsersList> User;

    while (1)
    {
        UserWriteToVector (User);
        system("cls");
        cout << "Panel logowania" << endl;
        cout << "1. Logowanie " << endl;
        cout << "2. Rejestracja " << endl;
        cout << "3. Zakoncz program " << endl;

        cin >> choice ;
        switch(choice)
        {
        case 1:
            LoginUser(User, addressee);
            break;
        case 2:
            AddingUser (User);
            break;
        case 3:
            exit(0);
            break;
        }
    }


    return 0;
}

void UserWriteToVector (vector <UsersList> &User)
{
    User.clear();
    fstream file;
    string line;
    string user;
    string word;
    int lengthOfContact=0;

    int j=-1;
    string variable1, variable2, variable3 ;

    file.open("UsersList.txt", ios::in);
    if (file.good()==false)
    {
        file.open("UsersList.txt", ios::out |ios::app);
    }
    while (getline(file,line))
    {
        user=line;
        lengthOfContact=line.length();
        for (int i=0; i<lengthOfContact; i++)
        {
            if (user[i]!= '|')
            {
                word = word + user[i];
            }
            else if (user[i]=='|')
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
                word="";
            }
        }
        UsersList temp {variable1, variable2, variable3};
        User.push_back(temp);
        j=-1;
    }
}

int UserCheckID (vector <UsersList> &User)
{
    int id=0;
    int sizeOfVector;
    string idOfLastUser;
    sizeOfVector=User.size();
    if (sizeOfVector==0)
    {
        id=0;
    }
    else
    {
        idOfLastUser=User[sizeOfVector-1].UserId;
        id=atoi(idOfLastUser.c_str());
    }
    return id;
}

void LoginUser (vector <UsersList> &User, vector <AddressBook> &addressee)
{
    string login;
    string password;
    bool test;
    int UserId;
    int sizeOfVector;
    sizeOfVector=User.size();
    int k=0;


    while (1)
    {
        cout << "Podaj login: ";
        cin >> login;
        for (int i=0; i<sizeOfVector; i++)
        {
            if (login==User[i].UserLogin)
            {
                k+=1;
            }
        }
        if (k==0)
        {
            cout << "Uzytkownik o takim loginie nie istnieje! Podaj poprawna nazwe uzytkownika " << endl;
        }
        else
        {
            break;
        }
    }

    int i=0;
    while (1)
    {
        if (login==User[i].UserLogin)
        {
            User[i].UserLogin;
            break;
        }
        i++;
    }

    cout << "Podaj haslo: ";
    cin >> password;
    while (1)
    {
        if (password==User[i].UserPassword)
        {
            cout << "Zalogowano " << endl;
            test=1;
            system("pause");
            break;
        }
        else
        {
            cout << "Haslo nieprawidlowe" << endl;
            cout << "Podaj haslo: ";
            cin >> password;
        }
    }
    if(test==1)
    {
        UserId= atoi(User[i].UserId.c_str());
        cout << UserId << endl;
        AddresBookMenu (addressee, User, UserId);
        system ("pause");
    }
}

void AddingUser (vector <UsersList> &User)
{
    int ID=UserCheckID(User)+1;
    string login, password, auxiliary;
    int sizeOfVector;
    sizeOfVector=User.size();

    cout << "Podaj Login: ";
    getline(cin,auxiliary);

    getline(cin,login);
    for (int i=0; i<sizeOfVector; i++)
    {
        if (User[i].UserLogin==login)
        {
            cout << "Uzytkownik o takim nicku istnieje, wpisz ponownie inna nazwe " << endl;
            cout << "Podaj Login: ";
            getline(cin,login);
            i=0;
        }
    }

    cout << "Podaj haslo: ";
    getline(cin,password);

    fstream file;
    file.open("UsersList.txt", ios::out |ios::app);
    file<<ID <<"|";
    file<<login<<"|";;
    file<<password<<"|";
    file<<endl;
    file.close();
    system("pause");
}

int CheckID ( vector <AddressBook> &addressee)
{
    string line;
    string contact, word, variable;
    int lengthOfContact;
    int j=0;
    int id;
    int numberOfLines=0;

    fstream file;

    file.open("book.txt", ios::in);
    while (getline(file,line))
    {
        numberOfLines=numberOfLines+1;
    }
    file.close();

    file.open("book.txt", ios::in);
    while (getline(file,line))
    {
        lengthOfContact=line.length();
        contact=line;

        for (int i=0; i<lengthOfContact; i++)
        {
            if (numberOfLines==1)
            {
                word = word + contact[i];

                if (contact[i+1]=='|')
                {
                    variable=word;
                    break;
                }
            }
            if (contact[i]!= '|')
            {
                word = word + contact[i];
            }
            else if (contact[i]=='|')
            {
                ++j;
                if (j==0)
                {
                    variable=word;
                }
                word="";
            }
        }
        j=-1;
    }
    file.close();
    id=atoi(variable.c_str());
    return id;
}

void AddingAddressee (vector <AddressBook> &addressee, vector <UsersList> &User, int UserId)
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
    file<<UserId << "|";
    file<<name<<"|";;
    file<<surname<<"|";
    file<<phone<<"|";
    file<<email<<"|";
    file<<address<<"|";
    file<<endl;
    file.close();
    system("pause");
}

void WriteToVector( vector <AddressBook> &addressee, int UserId)
{
    ostringstream ss;
    ss << UserId;
    string UserIdString = ss.str();

    addressee.clear();
    fstream file;
    string line;
    string contact;
    string word;
    int lengthOfContact=0;

    int j=-1;
    string variable1, variable2, variable3, variable4, variable5, variable6, variable7 ;

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
                if (j==6)
                {
                    variable7=word;
                }
                word="";
            }
        }
        if (variable2==UserIdString)
        {
            AddressBook temp {variable1, variable2, variable3, variable4, variable5, variable6, variable7};
            addressee.push_back(temp);
        }
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

int DeleteContact (vector <AddressBook> &addressee)
{
    string ID;
    int IdDeletedContact=0;
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
            cout << "Kontakt zostal usuniety. " << endl;
            system("pause");
        }
        else
        {
            cout << "Kontakt nie zostal usuniety. " << endl;
            return 0;
            system("pause");
        }
    }

    else if (k==0)
    {
        cout << "Kontakt nie istnieje " << endl;
        system("pause");
        return 0;
    }
    k=0;
    cout << endl;
    return IdDeletedContact=atoi(ID.c_str());

}

int EditContact (vector <AddressBook> &addressee)
{
    int choice;
    string name, surname, phone, email, address, auxiliary;
    string ID;
    int IDToReturn=0;
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
        system("pause");
        return 0;
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
    IDToReturn=atoi(ID.c_str());
    return IDToReturn;
}

void CheckEditedContact (vector <AddressBook> &addressee, string variable, int IdOfEditedContact, string contact)
{
    int vectorLength=addressee.size();
    int ordinalNumberOfVector;

    int IdNumberOfCheckedAdressee;

    for (int i=0;i<vectorLength;i++)
    {
        IdNumberOfCheckedAdressee=atoi(addressee[i].ID.c_str());
        if (IdNumberOfCheckedAdressee==IdOfEditedContact)
        {
            ordinalNumberOfVector=i;
        }
    }
    int IdInAddressBook=atoi(variable.c_str());

    fstream file;

    file.open("bookTemp.txt", ios::out | ios::app);

    if(IdInAddressBook==IdOfEditedContact)
    {
        file << addressee[ordinalNumberOfVector].ID << "|";
        file << addressee[ordinalNumberOfVector].UserId << "|";
        file << addressee[ordinalNumberOfVector].firstName << "|";
        file << addressee[ordinalNumberOfVector].lastName << "|";
        file << addressee[ordinalNumberOfVector].phoneNumber << "|";
        file << addressee[ordinalNumberOfVector].emailAddress << "|";
        file << addressee[ordinalNumberOfVector].address << "|";
        file << endl;
    }
    else
    {
        file << contact << endl;
    }
    file.close();
}

void CheckDeletedContact (vector <AddressBook> &addressee, string variable, int IdOfEditedContact, string contact)
{
    int IdInAddressBook=atoi(variable.c_str());
    fstream file;

    file.open("bookTemp.txt", ios::out | ios::app);

    if(IdInAddressBook==IdOfEditedContact)
    {
        file <<"";
    }
    else
    {
        file << contact << endl;
    }
    file.close();
}

void BookUpdate (vector <AddressBook> &addressee, int IdOfEditedContact, int IdDeletedContact)
{
    string line;
    string contact;
    string variable1;
    int j=-1;
    int lengthOfContact;
    int sizeOfVector;
    string word;
    sizeOfVector=addressee.size();
    fstream file;

    file.open("book.txt", ios::in);
    while (getline(file,line))
    {
        lengthOfContact=line.length();
        contact=line;
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
                word="";
            }
        }
        if (IdOfEditedContact==0 && IdDeletedContact==0)
        {
            break;
        }
        else if (IdOfEditedContact!=0)
        {
            CheckEditedContact (addressee, variable1, IdOfEditedContact, contact);
        }
        else
        {
            CheckDeletedContact (addressee, variable1, IdDeletedContact, contact);
        }
        j=-1;
    }
    file.close();

    if (IdOfEditedContact!=0 || IdDeletedContact!=0)
    {
        remove ("book.txt");
        rename ("bookTemp.txt", "book.txt" );
    }
}

int AddresBookMenu (vector <AddressBook> &addressee, vector <UsersList> User, int UserId)
{
    int choice;
    int IdOfEditedContact=0;
    int IdDeletedContact=0;
    while (1)
    {
        WriteToVector (addressee, UserId);
        system("cls");
        cout << "Zalogowany uzytkownik: " << User[UserId-1].UserLogin << "   Numer Id uzytkownika: " << User[UserId-1].UserId << endl << endl;
        cout << " KSIAZKA ADRESOWA " << endl;
        cout << "1. Dodaj adresata " << endl;
        cout << "2. Wyszukaj po imieniu " << endl;
        cout << "3. Wyszukaj po nazwisku " << endl;
        cout << "4. Wyswietl wszystkich adresatow " << endl;
        cout << "5. Usun adresata " << endl;
        cout << "6. Edytuj adresata " << endl;
        cout << "8. Powrot do poprzedniego menu " << endl;
        cout << "9. Zakoncz program " <<endl;
        cout << "Twoj wybor: " << endl;
        cin >> choice;

        switch(choice)
        {
        case 1:
            AddingAddressee (addressee, User, UserId);
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
            IdDeletedContact=DeleteContact (addressee);
            BookUpdate (addressee, IdOfEditedContact, IdDeletedContact);
            IdDeletedContact=0;
            break;
        case 6:
            IdOfEditedContact=EditContact(addressee);
            BookUpdate (addressee, IdOfEditedContact, IdDeletedContact);
            IdOfEditedContact=0;
            break;
        case 8:
            return 0;
            break;
        case 9:
            exit(0);
            break;
        }
    }
}
