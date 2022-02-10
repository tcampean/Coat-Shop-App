//
// Created by Tudor on 4/16/2021.
//

#ifndef A67_912_CAMPEAN_TUDOR_ALEXANDRU_WRITEREPOSITORY_H
#define A67_912_CAMPEAN_TUDOR_ALEXANDRU_WRITEREPOSITORY_H

#include "Repository.h"

class WriteRepository : public Repository
{
public:
    virtual void write() {}
    virtual void open() {}

};

#endif //A67_912_CAMPEAN_TUDOR_ALEXANDRU_WRITEREPOSITORY_H
