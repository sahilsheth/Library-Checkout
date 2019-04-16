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
void bookReturn(vector<Book *> & myBooks);
void update(vector<Book *> myBooks, vector<Person *> myCardholders);
void availableBooks(vector<Book *> myBooks);
void viewOutStandingRentals(vector<Book *> myBooks);
void closeCard(vector<Person *> &myCardholders);
bool checkCard(vector<Person *> &myCardholders, int cardNumbers);
bool checkBook(vector<Book *> &myBooks, int bookNumbers);
int findBooks(vector<Book *> &myBooks, int bookNumber);
int findCard(vector<Person *> &myCardholders, int cardIdNum);
void cardRentals(vector<Book *> &myBooks, vector<Person *> &myCardholders);



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
    //return;

}

void bookCheckingout(vector<Book *> & myBooks, vector<Person *> myCardholders)
{
    Person *peoplePtr = nullptr;
    int cardId, findCards, findBook, bookId, cardNumber=0;
    cout << "Please enter the card ID: ";
    cin >> cardId;
    if(checkCard(myCardholders, cardId))
    {
        for(int i =0; i <myCardholders.size(); i++)
        {
            //is this needed
            //if(cardId == myCardholders[i]-getId() && myCardholders[i]->isActive())
            if(cardId == myCardholders[i]->getId())
            {
                   cout << "Cardholder: " << myCardholders[i]->fullName()<<endl;
            }
            
        }
    }
    else
    {
        cout << "Card not found " << endl;
    }
    
    cout << "Please enter the book ID: ";
    cin >> bookId;
    if(checkBook(myBooks, bookId))
    {
        
        for(int i = 0; i< myBooks.size(); i++)
        {
            if(bookId == myBooks[i]->getId())
            {
                cout << "Title: " << myBooks[i]->getTitle()<<endl;
                cout << "Rental completed " << endl;
                findCards = findCard(myCardholders, cardId);
                findBook = findBooks(myBooks, cardId);
                peoplePtr = myCardholders[findCards];
                myBooks[findBook]->setPersonPtr(peoplePtr);
            }
        }
        
        
        
        for(int j = 0; j<myBooks.size(); j++)
        {
            if(bookId == myBooks[j]->getId() && myBooks[j]->getPersonPtr() != nullptr)
            {
                cout << "Book already checked out " << endl;
                //return; check if return is necessary
            }
        }
    }
       
    else
    {
        cout << "Book not found " << endl;
    }
    
}

bool checkCard(vector<Person *> &myCardholders, int cardNumbers)
{
    int cardCheck = 0;
    ;//int cardCheckNum = cardNumbers;
    for(int i = 0; i< myCardholders.size(); i++)
    {
        //check if isActive is needed
        if(cardNumbers == myCardholders[i]->getId()) //&& myCardholders[i]->isActive() == 1)
        {
            return true;
        }
        else{
            cardCheck++;
        }
    }
    if(cardCheck == myCardholders.size())
    {
        return false;
    }
    
    return false;
}

bool checkBook(vector<Book *> &myBooks, int bookNumbers)
{
    
    int bookCheck = 0;
    for(int i = 0; i< myBooks.size(); i++)
    {
        if(bookNumbers == myBooks[i]->getId())
        {
            return true;
        }
        else{
            bookCheck++;
        }
    }
    
    if(bookCheck == myBooks.size())
    {
        return false;
    }
    
    return false;
    
}
       
int findBooks(vector<Book *> &myBooks, int bookNumber)
{
    for(int i = 0; myBooks.size(); i++)
    {
        if(bookNumber == myBooks[i]->getId())
        {
            return i;
        }
    }
    return 0;
}
       
int findCard(vector<Person *> &myCardholders, int cardIdNum)
{
    for(int i = 0; i<myCardholders.size(); i++)
    {
        if(cardIdNum == myCardholders[i]->getId())
        {
            return i;
        }
    }
    return 0;
}

//FIX DOES NOT WORK
void viewOutStandingRentals(vector<Book *> myBooks)
{
  int countRent = 0;
  for(int i =0; i < myBooks.size(); i++)
  {
    if(myBooks[i]->getPersonPtr())
    {
      cout << "Book ID: " << myBooks[i]->getId()<<endl;
      cout << "Title: " << myBooks[i]->getTitle()<<endl;
      cout << "Author: " << myBooks[i]->getAuthor()<<endl;
      cout << "Cardholder: " << myBooks[i]->getPersonPtr()->fullName() <<endl;
      cout << "Card ID: " << myBooks[i]->getPersonPtr()->getId() << endl;
      countRent++;
    }
  }

  if(countRent == 0)
  {
    cout << "No outstanding rentals" << endl;
  }

}


void cardRentals(vector<Book *> &myBooks, vector<Person *> &myCardholders)
{
    int cardIds, cardNum1;
    int counting;
    cout << "Please enter the card ID: " << endl;
    cin >> cardIds;
    cardNum1 = findCard(myCardholders, cardIds);
    if(!checkCard(myCardholders, cardIds))
    {
        cout << "Card ID not found " << endl;
    }
    else
    {
        cout << "Cardholder: " << myCardholders[cardNum1]->fullName()<<endl;
        for(int i = 0; i < myBooks.size(); i++)
        {
            if(cardNum1 == myBooks[i]->getPersonPtr()->getId())
            {
                cout << "Book ID: " << myBooks[i]->getId()<<endl;
                cout << "Title: " << myBooks[i]->getTitle()<<endl;
                cout << "Author: " << myBooks[i]->getAuthor() << endl;
                counting++;
            }
        }
    }
    
    if(counting == 0)
    {
        cout << "No outstanding rentals " << endl;
    }
    
    
    
    
}

void bookReturn(vector<Book *> & myBooks)
{
    int bookNums, bookIds;
    Person * pPtr = nullptr;
    cout << "Please enter the book ID to return: " << endl;
    cin >> bookIds;
    if(!checkBook(myBooks, bookIds))
    {
        cout << "Book ID not found. " << endl;
    }
    else //if(checkBook(myBooks, bookIds))
    {
        bookNums = findBooks(myBooks, bookIds);
        //check this again
        if(myBooks[bookNums]->getPersonPtr())
        {
            myBooks[bookNums]->setPersonPtr(pPtr);
            cout << "Return completed " <<endl;
            return;
        }
    }
}



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
       
       
void closeCard(vector<Person *> &myCardholders)
{
    char choice;
    int myCardID, findBookID;
    bool active = 0;
    cout << "Pease enter the card ID: " << endl;
    cin >> myCardID;
    if(checkCard(myCardholders, myCardID))
    {
        findBookID = findCard(myCardholders, myCardID);
        cout << myCardholders[findBookID]->fullName() << endl;
        if(myCardholders[findBookID]->isActive())
        {
            cout << "Are you sure you want to deactive card (y/n)?" <<endl;
            cin >> choice;
            if(choice=='y')
            {
                myCardholders[findBookID]->setActive(active);
                cout<<"Card ID deactivated. "<<endl;
            }
            else if(choice=='n')
            {
                return;
            }
        }
        else
        {
            cout<<"Card ID is already inactive. " << endl;
        }
    }
    
    else
    {
        cout<<"Card ID not found. " <<endl;
    }
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
                bookCheckingout(books, cardholders);
                break;

            case 2:
                // Book return
                bookReturn(books);
                break;

            case 3:
                // View all available books
                availableBooks(books);
                break;

            case 4:
                // View all outstanding rentals
                viewOutStandingRentals(books);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                cardRentals(books, cardholders);
                break;

            case 6:
                // Open new library card
                openCard(cardholders, idNum);

                break;

            case 7:
                // Close library card
                closeCard(cardholders);
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
