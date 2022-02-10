//
// Created by Tudor on 3/19/2021.
//

#ifndef A67_912_CAMPEAN_TUDOR_ALEXANDRU_COAT_H
#define A67_912_CAMPEAN_TUDOR_ALEXANDRU_COAT_H

#include <string>
#include <vector>
#include <sstream>
#include<iostream>

using namespace std;

class Coat {
public:
    string size;
    string colour;
    int price;
    int quantity;
    string photograph;

public:
    //creates a new coat based on the data given
    Coat(string size,string colour,int price,int quantity,string photo);

    Coat(const Coat& c) = default;

    Coat() = default;

    //returns the size of a coat
    string getSize() const;

    //returns the colour of a coat
    string getColour() const;

    //returns the photo link of a coat
    string getPhoto() const;

    //return the price of a coat
    int getPrice() const;

    //returns the quantity of a coat
    int getQuantity() const;

    //returns the string representation of a coat
    string toString();

    //defines the = operator, passes the data of a coat to another
    Coat& operator=(const Coat& c) = default;

    //compares two coat type variables and returns true if they are equal or false otherwise
    bool operator==(Coat &c) const {
        if(this->size == c.size && this->colour == c.colour)
            return true;
        return false;
    }

    friend std::istream &operator>>(istream &is , Coat &c);

    friend std::ostream &operator<<(ostream &os,const Coat &c);
};


#endif //A67_912_CAMPEAN_TUDOR_ALEXANDRU_COAT_H
