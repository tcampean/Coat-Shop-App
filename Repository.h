//
// Created by Tudor on 3/19/2021.
//

#ifndef A45_912_CAMPEAN_TUDOR_ALEXANDRU_REPOSITORY_H
#define A45_912_CAMPEAN_TUDOR_ALEXANDRU_REPOSITORY_H

#include "Coat.h"
#include <vector>
#include <sstream>

class Repository{
public:
    vector<Coat> coats;

public:

    Repository() = default;

    //destroys the repository

    //adds a new coat to the repo , returns 1 if successful or 0 otherwise
    int addCoat(Coat c);

    //removes a coat from the repo, returns 1 if successful or 0 otherwise
    int removeCoat(string size, string color);

    //updates a coat from the repo with new data , returns 1 if successful or 0 otherwise
    int updateCoat(string size,string colour,string new_size,string new_color, int price, int quantity, string photo );

    //returns the amount of elements in the repo
    int length();

    //returns the value of all coats in the repository
    int getSum();

    //builds and returns a new repository containing all coats of a given size
    Repository fetch_coats(string size,Repository &repo);

    //adds a coat, if the coat already exists it's quantity will be increased
    //if the coat doesn't exist it will be added to the repo with quantity 1
    void addCoats(Coat c);

    //decreases the quantity of an existing coat in the repo
    //if the quantity reaches 0 the coat will be deleted from the repo
    void removeSingleCoat(Coat c);

    void readCoats(string file_name);

    void writeCoats();

    void clear();


};

#endif //A45_912_CAMPEAN_TUDOR_ALEXANDRU_REPOSITORY_H
