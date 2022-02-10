//
// Created by Tudor on 3/20/2021.
//

#include "Service.h"
#include "Validators.h"


int Service::servAdd(Coat c) {
    CoatValidator validator;
    validator.validate(c);
    return this->repo.addCoat(c);
}

int Service::servRemove(string size, string color) {
    return this->repo.removeCoat(size,color);
}

int Service::updateCoat(string size, string colour, string new_size, string new_color, int price, int quantity,
                        string photo) {
    return this->repo.updateCoat(size,colour,new_size,new_color,price,quantity,photo);
}
