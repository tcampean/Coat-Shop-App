//
// Created by Tudor on 5/29/2021.
//

#ifndef A10_912_CAMPEAN_TUDOR_ALEXANDRU_1_UNDOREDO_H
#define A10_912_CAMPEAN_TUDOR_ALEXANDRU_1_UNDOREDO_H
#include <vector>
#include "Repository.h"

class UndoRedo{
public:
public:
    UndoRedo() = default;
    ~UndoRedo() = default;
    virtual void undo(Repository &repo) = 0;
    virtual void redo(Repository &repo) = 0;
};

class AddOperation : public UndoRedo{
public:
    Coat c;
public:
    AddOperation() = default;
    AddOperation(Coat a)
    {
        this->c = a;
    }
    ~AddOperation() = default;
    void undo(Repository &repo) override
    {
        repo.removeCoat(c.getSize(),c.getColour());
    }

    void redo(Repository &repo) override
    {
        repo.addCoat(c);
    }


};

class RemoveOperation : public UndoRedo
{
public:
    Coat c;
public:
    RemoveOperation() = default;
    RemoveOperation(Coat a)
    {
        this->c = a;
    }
    ~RemoveOperation() = default;
    void undo(Repository &repo) override
    {
        repo.addCoat(c);
    }
    void redo(Repository &repo) override
    {
        repo.removeCoat(c.getSize(),c.getColour());
    }
};

class UpdateOperation : public UndoRedo
{
public:
    Coat initialCoat;
    Coat afterCoat;
public:
    UpdateOperation() = default;
    UpdateOperation(Coat a , Coat b)
    {
     this->initialCoat = a;
     this->afterCoat = b;
    }
    void undo(Repository &repo) override
    {
        int position = 0;
        for(auto i : repo.coats) {

            if (i.getSize() == afterCoat.getSize() && i.getColour() == afterCoat.getColour())
                break;
            position++;
        }
        repo.coats[position] = initialCoat;

    }

    void redo(Repository &repo) override
    {
        int position = 0;
        for(auto i : repo.coats) {

            if (i.getSize() == initialCoat.getSize() && i.getColour() == initialCoat.getColour())
                break;
            position++;
        }
        repo.coats[position] = afterCoat;
    }
};

#endif //A10_912_CAMPEAN_TUDOR_ALEXANDRU_1_UNDOREDO_H
