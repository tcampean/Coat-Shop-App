//
// Created by Tudor on 4/9/2021.
//

#ifndef A67_912_CAMPEAN_TUDOR_ALEXANDRU_VALIDATORS_H
#define A67_912_CAMPEAN_TUDOR_ALEXANDRU_VALIDATORS_H

#include <string>
#include <Coat.h>

class ValidationException{

private:
    std::string error;

public:
    ValidationException(std::string error);
    std::string getError();
};



class CoatValidator {

public:
    void validate(const Coat &c);

};

class inputValidator {
public:
    void validateInput(const string s,const string q);

};

class RepositoryException : public exception{
private:
    string message;
public:
    RepositoryException() = default;

    RepositoryException(string s){
        this->message = s;
    }

};

#endif //A67_912_CAMPEAN_TUDOR_ALEXANDRU_VALIDATORS_H
