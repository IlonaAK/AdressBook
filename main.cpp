#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include<vector>
#include<algorithm>

using namespace std;

struct Person
{
    int id;
    string firstname="", lastname="", phoneNumber="", email="", address="";
};

vector<string> splitTextToSingleWord (string text)
{
    vector<string>singleWords;
    string singleWord;
    unsigned char character;

    int length = text.size();

    for( int i = 0; i < length; i++ )
    {
        character = text[ i ];
        if (character != '|')
        {
            singleWord += character;
        }
        else
        {
            singleWords.push_back(singleWord);
            singleWord = "";
        }
    }
    return singleWords;
}

string loadLine()
{
    string entrance = "";
    getline(cin, entrance);
    return entrance;
}

char loadSign()
{
    string entrance = "";
    char sign  = {0};

    while (true)
    {
        getline(cin, entrance );

        if (entrance.length() == 1)
        {
            sign = entrance[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return sign;
}

int loadInteger()
{
    string entrance = "";
    int number = 0;

    while (true)
    {
        getline(cin, entrance);

        stringstream myStream(entrance );
        if (myStream >> number)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return number;
}


vector<Person> addPerson(vector<Person>persons, int allPersonsInAddressBook)
{
Person addressBook;
       if(persons.empty()!=true)
        {
        addressBook.id=persons[persons.size()-1].id +1;
        }
        else if(persons.empty()==true)
        {
            addressBook.id = 1;
        }

    cout << "Podaj imi\251: ";
    addressBook.firstname = loadLine();
    cout << "Podaj nazwisko: ";
    addressBook.lastname = loadLine();
    cout << "Podaj numer telefonu: ";
    addressBook.phoneNumber = loadLine();
    cout << "Podaj email: ";
    addressBook.email = loadLine();
    cout << "Podaj adres: ";
    addressBook.address = loadLine();

    persons.push_back(addressBook);

    fstream file;
    file.open("KsiazkaAdresowa.txt",ios::out | ios::app);

    if (file.good() == true)
    {
        file<<persons[allPersonsInAddressBook].id<<"|";
        file<<persons[allPersonsInAddressBook].firstname<<"|";
        file<<persons[allPersonsInAddressBook].lastname<<"|";
        file<<persons[allPersonsInAddressBook].phoneNumber<<"|";
        file<<persons[allPersonsInAddressBook].email<<"|";
        file<<persons[allPersonsInAddressBook].address<<"|"<<endl;
        file.close();
    }
    else
    {
        cout << "Nie uda\210o si\251 otworzy\206 pliku i zapisa\206 do niego danych." << endl;
        system("pause");
    }
    cout << endl << "Osoba zosta\210a dodana" << endl;
    system("pause");

    return persons;
}

vector <Person> loadPersonsFromFile(vector<Person>persons)
{
    string line;
    int numberOfLine = 1;
    fstream file;
    file.open("KsiazkaAdresowa.txt",ios::in);
    Person addressBook;

    if (file.good() == true)
    {
        while (getline(file,line))
        {
            if (numberOfLine=1)
            {
                addressBook.id=atoi((splitTextToSingleWord(line)[0]).c_str());
                addressBook.firstname =splitTextToSingleWord(line)[1];
                addressBook.lastname=splitTextToSingleWord(line)[2];
                addressBook.phoneNumber=splitTextToSingleWord(line)[3];
                addressBook.email =splitTextToSingleWord(line)[4];
                addressBook.address=splitTextToSingleWord(line)[5];
                persons.push_back(addressBook);

            }
            if (numberOfLine >= 2)
            {

                numberOfLine = 1;
            }
            else
            {
                numberOfLine++;
            }
        }
        file.close();
    }
    return persons;
}

void showAllPersons(vector<Person>persons)
{
    for (int i = 0; i < persons.size(); i++)
    {
        cout << endl;
        cout << "ID: " << persons[i].id << endl;
        cout << persons[i].firstname << " " << persons[i].lastname << endl;
        cout << "Telefon: " << persons[i].phoneNumber << endl;
        cout << "Email: " << persons[i].email << endl;
        cout << "Adres: " << persons[i].address << endl;
        cout << endl;
    }
    system("pause");
}

void searchByFirstname(vector<Person>persons)
{
    string firstname;
    cout << "Podaj imie osoby, kt\242rej dane chcesz wyswietli\206: ";
    firstname = loadLine();
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].firstname == firstname)
        {
            cout << endl;
            cout << "ID: " << persons[i].id << endl;
            cout << persons[i].firstname << " " << persons[i].lastname << endl;
            cout << "Telefon: " << persons[i].phoneNumber << endl;
            cout << "Email: " << persons[i].email << endl;
            cout << "Adres: " << persons[i].address << endl;
            cout << endl;
        }
    }
    system("pause");
}

void searchByLastname(vector<Person>persons)
{
    string lastname;
    cout << "Poda nazwisko osoby, kt\242rej dane chcesz wyswietli\206: ";
    lastname = loadLine();
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].lastname == lastname)
        {
            cout << endl;
            cout << "ID: " << persons[i].id << endl;
            cout << persons[i].firstname << " " << persons[i].lastname << endl;
            cout << "Telefon: " << persons[i].phoneNumber << endl;
            cout << "Email: " << persons[i].email << endl;
            cout << "Adres: " << persons[i].address << endl;
            cout << endl;
        }
    }
    system("pause");
}


vector <Person> editPerson (vector<Person>persons)
{
    char choice;
    int id;
    string firstname, lastname, email, address, phoneNumber;
    cout<<"Podaj ID osoby, kt\242rej dane chcesz edytowa\206: ";
    id= loadInteger();

    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].id ==id)
        {
            cout << "ID: " << persons[i].id << endl;
            cout << "1. Imi\251: "<<persons[i].firstname<<endl;
            cout << "2. Nazwisko: " << persons[i].lastname << endl;
            cout << "3. Telefon: " << persons[i].phoneNumber << endl;
            cout << "4. Email: " << persons[i].email << endl;
            cout << "5. Adres: " << persons[i].address << endl;
            cout<<"Podaj numer pozycji, kt\242r\245 chcesz edytowa\206: ";
            choice=loadSign();
            if (choice == '1')
            {
                cout<<"Podaj nowe imi\251: ";
                firstname=loadLine();

                vector<Person>::iterator itr=persons.begin()+i;
                Person addressBook;
                addressBook.id=id;
                addressBook.firstname=firstname;
                addressBook.lastname=persons[i].lastname;
                addressBook.phoneNumber=persons[i].phoneNumber;
                addressBook.email=persons[i].email;
                addressBook.address=persons[i].address;
                persons.insert(itr,addressBook);
                auto it=persons.begin()+i+1;
                persons.erase(it);

                break;
            }
            else if (choice == '2')
            {
                cout<<"Podaj nowe nazwisko: ";
                lastname=loadLine();
                vector<Person>::iterator itr=persons.begin()+i;
                Person addressBook;
                addressBook.id=id;
                addressBook.firstname=persons[i].firstname;
                addressBook.lastname=lastname;
                addressBook.phoneNumber=persons[i].phoneNumber;
                addressBook.email=persons[i].email;
                addressBook.address=persons[i].address;
                persons.insert(itr,addressBook);
                auto it=persons.begin()+i+1;
                persons.erase(it);
            }
            else if (choice == '3')
            {

                cout<<"Podaj nowy nr telefonu: ";
                phoneNumber=loadLine();
                vector<Person>::iterator itr=persons.begin()+i;
                Person addressBook;
                addressBook.id=id;
                addressBook.firstname=persons[i].firstname;
                addressBook.lastname=persons[i].lastname;
                addressBook.phoneNumber=phoneNumber;
                addressBook.email=persons[i].email;
                addressBook.address=persons[i].address;
                persons.insert(itr,addressBook);
                auto it=persons.begin()+i+1;
                persons.erase(it);
            }
            else if (choice == '4')
            {
                cout<<"Podaj nowy email: ";
                email=loadLine();
                vector<Person>::iterator itr=persons.begin()+i;
                Person addressBook;
                addressBook.id=id;
                addressBook.firstname=persons[i].firstname;
                addressBook.lastname=persons[i].lastname;
                addressBook.phoneNumber=persons[i].phoneNumber;
                addressBook.email=email;
                addressBook.address=persons[i].address;
                persons.insert(itr,addressBook);
                auto it=persons.begin()+i+1;
                persons.erase(it);
            }
            else if (choice == '5')
            {
                cout<<"Podaj nowy adres: ";
                address=loadLine();
                vector<Person>::iterator itr=persons.begin()+i;
                Person addressBook;
                addressBook.id=id;
                addressBook.firstname=persons[i].firstname;
                addressBook.lastname=persons[i].lastname;
                addressBook.phoneNumber=persons[i].phoneNumber;
                addressBook.email=persons[i].email;
                addressBook.address=address;
                persons.insert(itr,addressBook);
                auto it=persons.begin()+i+1;
                persons.erase(it);
            }
        }
    }

    return persons;
}
vector <Person> removePerson (vector<Person>persons)
{
    char choice;
    int id;
    string firstname, lastname, email, address, phoneNumber;
    cout<<"Podaj ID osoby, kt\242rej dane chcesz usun\245\206: ";
    id= loadInteger();

    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].id ==id)
        {
            cout << "ID: " << persons[i].id << endl;
            cout << "Imi\251: "<<persons[i].firstname<<endl;
            cout << "Nazwisko: " << persons[i].lastname << endl;
            cout << "Telefon: " << persons[i].phoneNumber << endl;
            cout << "Email: " << persons[i].email << endl;
            cout << "Adres: " << persons[i].address << endl;
            cout<<"Czy napewno chcesz usun\245\206 t\251 osob\251?<t/n> ";
            choice=loadSign();
            if (choice=='t')
            {
                auto it=persons.begin()+i;
                persons.erase(it);
                break;
            }
        }
    }
    return persons;
}

vector <Person> loadVectorToFile(vector<Person>persons)
{
    fstream file;
    file.open("KsiazkaAdresowa.txt",ios::out);

    if (file.good() == true)
    {
        for(int i=0; i<persons.size(); i++)
        {
            file<<persons[i].id<<"|";
            file<<persons[i].firstname<<"|";
            file<<persons[i].lastname<<"|";
            file<<persons[i].phoneNumber<<"|";
            file<<persons[i].email<<"|";
            file<<persons[i].address<<"|"<<endl;
        }
        file.close();
    }
    else
    {
        cout << "Nie uda\210o si\251 otworzy\206 pliku i zapisa\206 do niego danych." << endl;
        system("pause");
    }
    return persons;
}


int main()
{
    vector <Person>persons;
    int allPersonsInAddressBook = 0;
    char choice;

      persons = loadPersonsFromFile(persons);

    while (true)
    {

        allPersonsInAddressBook=persons.size();

        system("cls");
        cout<<"    KSI\244\275KA ADRESOWA"<<endl;
        cout<<"**********MENU***************"<<endl;
        cout << "1. Dodaj adresata"<<endl;
        cout << "2. Wyszukaj po imieniu"<<endl;
        cout << "3. Wyszukaj po nazwisku"<<endl;
        cout << "4. Wy\230wietl wszystkich adresat\242w"<<endl;
        cout << "5. Usu\344 adresata" <<endl;
        cout << "6. Edytuj adresata" <<endl;
        cout << "9. Zako\344cz program" <<endl;
        cout << "Tw\242j wyb\242r: ";
       choice = loadSign();

        if (choice == '1')
        {

          persons=addPerson(persons, allPersonsInAddressBook);

        }
        else if (choice == '2')
        {

            searchByFirstname(persons);
        }
        else if (choice == '3')
        {

            searchByLastname(persons);
        }
        else if (choice == '4')
        {
            showAllPersons(persons);
        }
        else if (choice == '5')
        {
            persons=removePerson(persons);
            loadVectorToFile(persons);
            loadPersonsFromFile(persons);
                     }
        else if (choice == '6')
        {
            persons=editPerson(persons);
            loadVectorToFile(persons);
        }
        else if (choice == '9')
        {
            exit(0);
        }
    }
    return 0;
}
