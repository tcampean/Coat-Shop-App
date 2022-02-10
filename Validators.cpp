//
// Created by Tudor on 4/9/2021.
//

#include "Validators.h"

ValidationException::ValidationException(std::string _error) : error{_error}{
}

std::string ValidationException::getError() {
    return this->error;
}

void CoatValidator::validate(const Coat &c) {
    string errors;
    if(c.getSize().length()<1)
        errors+=string("The size can't be empty!\n");
    for(auto i:c.getSize())
        if(!isalpha(i) && !isdigit(i)) {
            errors += string("The size can contain only letters or numbers!\n");
            break;
        }
    if(c.getColour().length() < 1)
        errors+=string("The colour can't be empty!\n");
    for(auto i:c.getColour())
        if(!isalpha(i) && !isspace(i)) {
            errors += string("The colour must contain only letters!\n");
            break;
        }
    if(c.getPrice()<1)
        errors+=string("The price can't be negative!\n");
    if(c.getQuantity()<1)
        errors+=string("The quantity can't be negative!\n");
    if(c.getPhoto().empty())
        errors+=string("The coat must have a link!\n");

    if(!errors.empty())
        throw ValidationException(errors);

}

void inputValidator::validateInput(const string price, const string quantity) {
    string errors;
    for(auto i :price)
        if (!isdigit(i)){
            errors+="Invalid price!\n";
            break;
        }
    for (auto i:quantity)
        if (!isdigit(i))
        {
            errors +="Invalid quantity";
            break;
        }
    if(!errors.empty())
        throw ValidationException(errors);
}

