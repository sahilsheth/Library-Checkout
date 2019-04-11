#include "person.h"

Person::Person(int cardNo, bool act, string fName, string lName) {
    // complete constructor
    cardID = cardNo;
    firstName = fName;
    lastName = lName;
    setActive(act);

}

string Person::getFirstName() {
    return firstName; // complete
}

string Person::getLastName() {
    return lastName; // complete
}

int Person::getId() {
    return cardID; // complete
}

void Person::setActive(bool act) {
    active = act;
} 


bool Person::isActive() {
    if(active == 1)
    {
        return true;
        
    }
    else
    {
        return false;
        
    }
}

string Person::fullName() {
    return firstName + " " + lastName; // complete
}
