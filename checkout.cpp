// Name
// Section #
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;


void printMenu();
void readBooks(vector<Book *> & myBooks);
int readPersons(vector<Person *> & myCardholders);
void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders);
void openCard(vector<Person *> & myCardholders, int &nextID);
//Book * searchBook(vector<Book *> myBooks, int id);
void bookCheckingout(vector<Book *> & myBooks, vector<Person *> myCardholders);
void update(vector<Book *> myBooks, vector<Person *> myCardholders);
void availableBooks(vector<Book *> myBooks);


void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

/* You are not obligated to use these function declarations - they're just given as examples
void readBooks(vector<Book *> & myBooks) {
    return;
}

int readPersons(vector<Person *> & myCardholders) {
    return 0;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    return;
}

void openCard(vector<Person *> & myCardholders, int nextID) {
    return;
}

Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}
*/

void readBooks(vector<Book *> & myBooks)
{
    Book *bPtr = nullptr;
    string writer, categories, title;
    string line;
    //string remove;
    int idNum;
    ifstream data;
    data.open("books.txt");
    while(data >> idNum)
    {
        getline(data, line);
        getline(data, title);
        getline(data, writer);
        getline(data, categories);
        bPtr = new Book(idNum, title, writer, categories);
        myBooks.push_back(bPtr);
        //myBooks.emplace_back(idNum, title, writer, categories);
    }

    data.close();

}

int readPersons(vector<Person *> & myCardholders) {

    Person *people = nullptr;
    string first, last;
    int cardNum;
    bool activation;
    ifstream personData;
    personData.open("persons.txt");
    /*while(personData >> cardNum >> activation >> first >> last)
    {
        myCardholders.emplace_back(cardNum, activation, first, last);
    }*/
    while(personData >> cardNum)
    {
        personData >> activation >> first >> last;
        people = new Person(cardNum, activation, first, last);
        myCardholders.push_back(people);
    }

    personData.close();
    return cardNum+1;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {

    vector<int> rentBooks;
    vector<int> rentCard;
    Person *rentPerson = nullptr;
    int idBook, idCard;
    //store id nums for card and book into vector
    ifstream rentFile;
    rentFile.open("rentals.txt");
    while(rentFile >> idBook)
    {
        rentFile >> idCard;
        rentBooks.push_back(idBook);
        rentCard.push_back(idCard);

    }
    rentFile.close();

    //check if person checked out the book or not
    for(int i=0; i< rentBooks.size(); i++)
    {
        idCard = rentCard[i];
        idBook = rentBooks[i];
        for(int i = 0; i < myBooks.size(); i++)
        {
            if(idBook == myBooks[i]->getId())
            {
                myBooks[i]->setPersonPtr(rentPerson);
            }
        }

        for(int i = 0; i < myCardholders.size(); i++)
        {
            if(idCard == myBooks[i]->getId())
            {
                rentPerson = myCardholders[i];
            }
        }
    }
    return;

}

/*void bookCheckingout(vector<Book *> & myBooks, vector<Person *> myCardholders)
{








}*/








///////////////////////////////////////////////////////////// may want to check openCard and see if for loop is necessary and also check to see if id needs to be incremented
void openCard(vector<Person *> & myCardholders, int &nextID) {

    string fName, lName;
    cout << "Please enter the first name: ";
    cin >> fName;
    cout << "Please enter the last name: ";
    cin >> lName;

    bool activation = 1;
    Person *p = nullptr;

    /*for(int i = 0; i < myCardholders.size(); i++)
    {
        myCardholders[i]->setActive(activation);
        cout << "Card ID " << myCardholders[i]->getId() << " active" << endl;
        cout << "Cardholder: " << myCardholders[i]->fullName() << endl;
    }*/
    p = new Person(nextID, activation, fName, lName);
    myCardholders.push_back(p);
    cout << "Card ID " << nextID << " active" << endl;
    cout << "Cardholder: " << p->fullName() << endl;
    nextID++;



}

/*Book * searchBook(vector<Book *> myBooks, int id) {

}*/

//may need to check if count should be in the if statement or in the else
void availableBooks(vector<Book *> myBooks)
{
    int count = 0;
    for(int i = 0; i < myBooks.size(); i++)
    {
        if(myBooks[i]->getPersonPtr() == nullptr)
        {
            cout << "Book ID: " << myBooks[i]->getId() << endl;
            cout << "Title: " << myBooks[i]->getTitle() << endl;
            cout << "Author: " << myBooks[i]->getAuthor() << endl;
            cout << "Category: " << myBooks[i]->getCategory() << endl;
            count ++;
        }
    }

    if(count == 0)
    {
        cout << "No available books" << endl;
    }
}

void update(vector<Book *> myBooks, vector<Person *> myCardholders)
{
    bool active;
    int cardNum, bookNum;
    string fName, lName;
    ofstream writeOut;
    writeOut.open("persons.txt");
    for(int i = 0; i < myCardholders.size(); i++)
    {
        active = myCardholders[i]->isActive();
        fName = myCardholders[i]->getFirstName();
        lName = myCardholders[i]->getLastName();
        cardNum = myCardholders[i]->getId();
        writeOut << cardNum <<  "  " << active << " " << fName << " " << lName << endl;
    }
    writeOut.close();

    writeOut.open("rentals.txt");

    for(int i = 0; i < myBooks.size(); i++)
    {
        if(myBooks[i]->getPersonPtr())
        {
            writeOut << bookNum << " " << cardNum << endl;
        }

    }

    writeOut.close();

}




int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int idNum = 0;
    readBooks(books);
    idNum = readPersons(cardholders);
    readRentals(books, cardholders);
    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
                break;

            case 2:
                // Book return
                break;

            case 3:
                // View all available books
                availableBooks(books);
                break;

            case 4:
                // View all outstanding rentals
                break;

            case 5:
                // View outstanding rentals for a cardholder
                break;

            case 6:
                // Open new library card
                openCard(cardholders, idNum);

                break;

            case 7:
                // Close library card
                break;

            case 8:
                // Must update records in files here before exiting the program
                update(books, cardholders);
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
