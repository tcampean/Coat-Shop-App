//
// Created by Tudor on 5/6/2021.
//

#include "Coat.h"

#include "Coat.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


Coat::Coat(string size1,string colour1,int price1,int quantity1,string photo){

    this->size = size1;
    this->colour = colour1;
    this->price = price1;
    this->quantity = quantity1;
    this->photograph = photo;

}

string Coat::getSize() const {
    return this->size;
}

string Coat::getColour()const {
    return this->colour;
}

string Coat::getPhoto() const{
    return this->photograph;
}

int Coat::getPrice() const {
    return this->price;
}

int Coat::getQuantity() const {
    return this->quantity;
}

string Coat::toString() {
    return "Size: " + this->getSize() + " Colour: "+ this->getColour() + " Price: " + to_string(this->getPrice()) + " Quantity: " + to_string(this->getQuantity()) +" Photo: "+ this->getPhoto();
}


vector<string> tokenize(string str, char delimiter)
{
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while(getline(ss,token,delimiter)){
        tokens.push_back(token);
    }
    return tokens;

}


std::istream &operator>>(istream &is , Coat &c){
    string line;
    getline(is,line);
    vector<string> tokens = tokenize(line,',');
    if(tokens.size() != 5)
        return is;
    c.size = tokens[0];
    c.colour = tokens[1];
    c.price = stoi(tokens[2]);
    c.quantity = stoi(tokens[3]);
    c.photograph = tokens[4];

    return is;

}

std::ostream &operator<<(ostream &os,const Coat &c) {
    os<<c.size<<","<<c.colour<<","<<c.price<<","<<c.quantity<<","<<c.photograph<<"\n";
    return os;

}