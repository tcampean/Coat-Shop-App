//
// Created by Tudor on 3/20/2021.
//

#ifndef A45_912_CAMPEAN_TUDOR_ALEXANDRU_SERVICE_H
#define A45_912_CAMPEAN_TUDOR_ALEXANDRU_SERVICE_H

#endif //A45_912_CAMPEAN_TUDOR_ALEXANDRU_SERVICE_H

#include "Repository.h"

class Service{
public:
    Repository repo;
public:
    //creates a service
    Service() = default;

    //adds a new coat to the repo through the service, returns 1 if successful or 0 otherwise
    int servAdd(Coat c);

    //removes a coat from the repo through the service, returns 1 if successful or 0 otherwise
    int servRemove(string size, string color);

    //updates a coat from the repo through the service, returns 1 if successful or 0 otherwise
    int updateCoat(string size,string colour,string new_size,string new_color, int price, int quantity, string photo );


};