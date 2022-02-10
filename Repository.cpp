//
// Created by Tudor on 3/19/2021.
//

#include "Repository.h"
#include "Validators.h"
#include <iostream>
#include <fstream>

using namespace std;


int Repository::addCoat(Coat c) {
    for(auto i: this->coats)
        if(i.getSize() == c.getSize() && i.getColour() == c.getColour())
            throw RepositoryException();
    this->coats.push_back(c);
    return 1;

}

int Repository::removeCoat(string size , string color) {
    int previous_length = this->coats.size();
    int index = 0;
    for(auto i: this->coats) {
        if (i.getSize() == size && i.getColour() == color)
            this->coats.erase(this->coats.begin()+index);
        index++;
    }
    if(previous_length != this->coats.size()) {
        return 1;
    }
    else
        throw RepositoryException();
}

int Repository::updateCoat(string size,string colour,string new_size,string new_color, int price, int quantity, string photo ) {
    int index = 0,ok=0;
    for(auto i:this->coats) {
        if (i.getSize() == size && i.getColour() == colour) {
            ok = 1;
            break;
        }
        index++;
    }

    if(ok == 0)
        throw RepositoryException("ersfffd");
    if(size == new_size)
        new_size = "";
    if(colour == new_color)
        new_color = "";
    for(auto i :this->coats)
        if(i.getSize() == new_size && i.getColour() == new_color ||
           i.getSize() == size && i.getColour() == new_color ||
           i.getSize() == new_size && i.getColour() == colour)
            throw RepositoryException();
    if(new_size == "")
        new_size = this->coats[index].getSize();
    if(new_color=="")
        new_color = this->coats[index].getColour();
    if(price == -1)
        price = this->coats[index].getPrice();
    if(quantity == -1)
        quantity = this->coats[index].getQuantity();
    if(photo=="")
        photo = this->coats[index].getPhoto();

    Coat c(new_size,new_color,price,quantity,photo);
    CoatValidator validator;
    validator.validate(c);
    this->coats[index]=c;
    return 1;

}

int Repository::getSum()
{
    if(this->length() == 0)
        return 0;
    int sum = 0;
    for(auto i:this->coats)
        sum+=i.getPrice()*i.getQuantity();
    return sum;
}

int Repository::length(){
    return this->coats.size();
}

Repository Repository::fetch_coats(string size,Repository &repo)
{
    for(auto i:this->coats)
        if(!size.empty()) {
            if (i.getSize() == size)
                repo.addCoat(i);
        }
        else
            repo.addCoat(i);
    return repo;
}

void Repository::addCoats(Coat c)
{
    int index = 0;
    bool found = false;
    for(auto i :this->coats) {
        if (i == c) {
            this->coats[index].quantity++;
            found = true;
        }
        index++;
    }
    if(!found)
    {
        c.quantity = 1;
        this->addCoat(c);
    }
}

void Repository::removeSingleCoat(Coat c) {
    int index = 0;
    for(auto i: this->coats) {
        if (i == c) {
            this->coats[index].quantity--;
            if (this->coats[index].quantity == 0) {
                this->removeCoat(i.getSize(), i.getColour());

            }

        }
        index++;
    }

}

void Repository::readCoats(string file_name)
{
    ifstream f;
    f.open("D:\\GitHub\\a10-912-Campean-Tudor-Alexandru-1\\yea.txt");
    if(!f.is_open())
        return;
    Coat c{};
    while(f>>c)
    {
        this->addCoat(c);
    }
    f.close();
}

void Repository::writeCoats() {
    ofstream f("D:\\GitHub\\a10-912-Campean-Tudor-Alexandru-1\\yea.txt",ios::trunc);
    f.close();
    f.open("D:\\GitHub\\a10-912-Campean-Tudor-Alexandru-1\\yea.txt",ios::app);

    if(!f.is_open())
        throw exception();
    for(auto c:this->coats)
    {
        f<<c;
    }
    f.close();
}

void Repository::clear()
{
    this->coats.clear();
}