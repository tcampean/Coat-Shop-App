//
// Created by Tudor on 5/6/2021.
//
#include "HTMLRepository.h"
#include "CSVRepository.h"
#include <QFileDialog>
#include <QMessageBox>
#include "GUI.h"
#include <QStandardPaths>
#include "Validators.h"
#include "HTMLRepository.h"
#include <QDebug>

GUI::GUI(QWidget *parent)
{
    this->initMain();
    this->connector();

}

void GUI::initMain() {
    QHBoxLayout* layout = new QHBoxLayout{ this };
    QWidget* rightSide = new QWidget{};
    QVBoxLayout* vLayout = new QVBoxLayout{ rightSide };
    QFont f("Verdana",15);
    QWidget* buttonsWidget = new QWidget{};
    QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
    this->adminButton = new QPushButton("Admin Mode");
    this->adminButton->setFont(f);
    this->userButton = new QPushButton("User Mode");
    this->userButton->setFont(f);
    hLayout->addWidget(this->userButton);
    hLayout->addWidget(this->adminButton);

    vLayout->addWidget(buttonsWidget);

    layout->addWidget(rightSide);


}

void GUI::connector() {
    QObject::connect(this->adminButton,&QPushButton::clicked,this,&GUI::AdminMode);
    QObject::connect(this->userButton,&QPushButton::clicked,this,&GUI::UserMode);

}

void GUI::AdminMode() {
    this->adminMode.show();
    this->userMode.hide();
}

void GUI::UserMode()
{
    this->userMode.show();
    this->adminMode.hide();

}

Admin::Admin(QWidget *parent) {
    this->initAdmin();
    this->adminConnector();


}

Admin::~Admin(){

}

void Admin::initAdmin() {

    this->undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"),this);
    this->redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"),this);
    QVBoxLayout* layout = new QVBoxLayout{this};
    QWidget* file = new QWidget{};
    QGridLayout* fileLayout = new QGridLayout{file};
    QLabel* fileLabel = new QLabel{"&File Name:"};
    this->Open = new QPushButton{"Open file"};
    fileLayout->addWidget(fileLabel,0,0);
    fileLayout->addWidget(this->Open,1,0);
    layout->addWidget(file);


    this->coatList = new QListWidget{};
    this->coatList->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(this->coatList);
    QWidget* data = new QWidget{};
    QFormLayout* dataForm = new QFormLayout{data};

    this->coatSize = new QLineEdit{};
    QLabel* sizeLabel = new QLabel{ "&Size:" };
    sizeLabel->setBuddy(this->coatSize);
    this->coatColour = new QLineEdit{};
    QLabel* colourLabel = new QLabel{ "&Colour:" };
    colourLabel->setBuddy(this->coatColour);
    this->coatPrice = new QLineEdit{};
    QLabel* priceLabel = new QLabel{ "&Price:" };
    priceLabel->setBuddy(this->coatPrice);
    this->coatQuantity = new QLineEdit{};
    QLabel* qLabel = new QLabel{ "&Quantity:" };
    qLabel->setBuddy(this->coatQuantity);
    this->coatPhoto = new QLineEdit{};
    QLabel* photoLabel = new QLabel{ "&Photo:" };
    photoLabel->setBuddy(this->coatPhoto);
    dataForm->addRow(sizeLabel,this->coatSize);
    dataForm->addRow(colourLabel,this->coatColour);
    dataForm->addRow(priceLabel,this->coatPrice);
    dataForm->addRow(qLabel,this->coatQuantity);
    dataForm->addRow(photoLabel,this->coatPhoto);
    layout->addWidget(data);
    QWidget* buttons = new QWidget{};
    QGridLayout* buttonLayout = new QGridLayout{buttons};
    this->addCoat = new QPushButton("Add Coat");
    this->removeCoat = new QPushButton("Remove Coat");
    this->updateCoat = new QPushButton("Update coat");
    this->Undo = new QPushButton("Undo");
    this->Redo = new QPushButton("Redo");
    buttonLayout->addWidget(this->addCoat,0,0);
    buttonLayout->addWidget(this->removeCoat,0,1);
    buttonLayout->addWidget(this->updateCoat,0,2);
    buttonLayout->addWidget(this->Undo,1,0);
    buttonLayout->addWidget(this->Redo,1,2);
    layout->addWidget(buttons);

}
void Admin::adminConnector() {
    QObject::connect(this->Open,&QPushButton::clicked,this,&Admin::ReadData);
    QObject::connect(this->addCoat,&QPushButton::clicked,this,&Admin::addCoatButton);
    QObject::connect(this,SIGNAL(addCoatSignal(const std::string&,const std::string&,const int&,const int&,const std::string&)),this,SLOT(addCoatFunction(const std::string&,const std::string&,const int&,const int&,const std::string&)));
    QObject::connect(this->removeCoat,&QPushButton::clicked,this,&Admin::deleteCoatButton);
    QObject::connect(this->updateCoat,&QPushButton::clicked,this,&Admin::updateCoatButton);
    QObject::connect(this,&Admin::listUpdateSignal,this,&Admin::populateCoatList);
    QObject::connect(this->coatList,&QListWidget::itemSelectionChanged,this,[this]() {this->itemSelection();});
    QObject::connect(this->Undo,&QPushButton::clicked,this,&Admin::undo);
    QObject::connect(this->Redo,&QPushButton::clicked,this,&Admin::redo);
    QObject::connect(this->undoShortcut,SIGNAL(activated()),this,SLOT(undo()));
    QObject::connect(this->redoShortcut,SIGNAL(activated()),this,SLOT(redo()));



}

void Admin::ReadData() {
    QString file = QFileDialog::getOpenFileName(this, "Open File", "D:\\GitHub\\a10-912-Campean-Tudor-Alexandru-1", "Text Files (*.txt);;C++ Files (*.cpp *.h)");
    if (file != "") {
        this->fileName = file.toStdString();

        std::ifstream f{this->fileName};
        if (!f.is_open()) {
            QMessageBox::critical(0, "Error", "File could not be opened!");
            return;
        }
        Coat c{};
        while(f>>c)
        {
            this->serv.servAdd(c);
        }
        f.close();
    }
    this->populateCoatList();
}
void Admin::populateCoatList() {
    if (this->serv.repo.length() > 0) {
        if (this->coatList->count() > 0)
            this->coatList->clear();
        for (auto c: this->serv.repo.coats) {
            QString coat = QString::fromStdString(c.toString());
            QListWidgetItem *item = new QListWidgetItem{coat};
            this->coatList->addItem(item);
        }
        this->coatList->setCurrentRow(0);

    }
    else
        this->coatList->clear();
}

void Admin::addCoatButton() {
    QString size = this->coatSize->text();
    QString colour = this->coatColour->text();
    QString price = this->coatPrice->text();
    QString quantity = this->coatQuantity->text();
    QString photo = this->coatPhoto->text();
    int intQuantity = stoi(quantity.toStdString());
    int intPrice = stoi(price.toStdString());
    emit addCoatSignal(size.toStdString(),colour.toStdString(),intPrice,intQuantity,photo.toStdString());
}

void Admin::deleteCoatButton() {
    int index = this->getSelected();
    if(index <0 || index >= this->serv.repo.length())
        return;
    RemoveOperation *operation = new RemoveOperation{this->serv.repo.coats[index]};
    this->UndoOperations.push(operation);


    this->serv.repo.coats.erase(this->serv.repo.coats.begin()+index);

    emit listUpdateSignal();
    this->serv.repo.writeCoats();

}

void Admin::addCoatFunction(const std::string& size, const std::string& colour, const int& price, const int& quantity, const std::string& photo) {
    try{
        this->serv.servAdd(Coat{size,colour,price,quantity,photo});
        AddOperation *operation = new AddOperation{Coat{size,colour,price,quantity,photo}};
        this->UndoOperations.push(operation);
        emit listUpdateSignal();
        this->serv.repo.writeCoats();
    } catch(ValidationException& v) {
        QMessageBox::critical(0, "Error", "Adding failed!");
    } catch(RepositoryException& r)
    {
        QMessageBox::critical(0, "Error", "Adding failed!");
    }


}

void Admin::updateCoatButton() {
    int index = this->getSelected();
    if(index == -1 || index >= this->serv.repo.length())
        return;
    Coat c = this->serv.repo.coats[index];
    QString size = this->coatSize->text();
    QString colour = this->coatColour->text();
    QString price = this->coatPrice->text();
    QString quantity = this->coatQuantity->text();
    QString photo = this->coatPhoto->text();
    int intQuantity = stoi(quantity.toStdString());
    int intPrice = stoi(price.toStdString());
    try {
        this->serv.updateCoat(c.getSize(), c.getColour(), size.toStdString(), colour.toStdString(), intPrice,
                              intQuantity, photo.toStdString());
        UpdateOperation *operation = new UpdateOperation{c,Coat{size.toStdString(), colour.toStdString(), intPrice,
                                                                intQuantity, photo.toStdString()}};
        this->UndoOperations.push(operation);
        emit listUpdateSignal();
        this->serv.repo.writeCoats();
    }catch(RepositoryException& v)
    {
        QMessageBox::critical(0, "Error", "Updating failed!");
    }catch(ValidationException* r)
    {
        QMessageBox::critical(0, "Error", "Updating failed!");
    }

}

int Admin::getSelected() {
    if(this->coatList->count()==0)
        return -1;
    QModelIndexList index = this->coatList->selectionModel()->selectedIndexes();
    if(index.size()==0)
    {
        this->coatSize->clear();
        this->coatQuantity->clear();
        this->coatColour->clear();
        this->coatPhoto->clear();
        this->coatPrice->clear();
        return -1;

    }
    int position = index.at(0).row();
    return position;

}

void Admin::itemSelection() {
    int index = this->getSelected();
    if(index == -1)
        return;
    if(index >= this->serv.repo.length())
        return;
    Coat c = this->serv.repo.coats[index];
    this->coatSize->setText(QString::fromStdString(c.getSize()));
    this->coatColour->setText(QString::fromStdString(c.getColour()));
    this->coatPhoto->setText(QString::fromStdString(c.getPhoto()));
    this->coatPrice->setText(QString::fromStdString(to_string(c.getPrice())));
    this->coatQuantity->setText(QString::fromStdString(to_string(c.getQuantity())));
}

void Admin::undo() {
    if(this->UndoOperations.size() <= 0)
        QMessageBox::critical(0, "Error", "There is nothing to undo!");
    else {
        this->UndoOperations.top()->undo(this->serv.repo);
        this->RedoOperations.push(this->UndoOperations.top());
        this->UndoOperations.pop();
        emit listUpdateSignal();
        this->serv.repo.writeCoats();
    }
}

void Admin::redo() {
    if(this->RedoOperations.size() <= 0)
        QMessageBox::critical(0, "Error", "There is nothing to redo!");
    else {
        this->RedoOperations.top()->redo(this->serv.repo);
        this->UndoOperations.push(this->RedoOperations.top());
        this->RedoOperations.pop();
        emit listUpdateSignal();
        this->serv.repo.writeCoats();
    }


}



User::User(QWidget *parent) {
    this->initUser();
    this->shopping = false;
    this->index = 0;
    this->userConnector();
    this->serv.repo.readCoats("yea.txt");
    this->table = new CoatTableModel{this->shoppingCart};



}

User::~User(){

}

void User::initUser() {
    QVBoxLayout* layout = new QVBoxLayout{this};
    this->coatList = new QListWidget{};
    QWidget* upper = new QWidget{};
    QHBoxLayout* list = new QHBoxLayout{upper};
    list->addWidget(this->coatList);
    QWidget* upperButton = new QWidget{};
    QGridLayout* upperButtons = new QGridLayout{upperButton};
    this->buy = new QPushButton("Buy");
    this->next = new QPushButton("Next coat");
    this->finishShopping = new QPushButton("Finish shopping");
    upperButtons->addWidget(this->buy,0,0);
    upperButtons->addWidget(this->next,1,0);
    upperButtons->addWidget(this->finishShopping,2,0);
    list->addWidget(upperButton);
    layout->addWidget(upper);
    this->table = new CoatTableModel(this->shoppingCart);
    this->cart = new QTableView();
    this->cart->setModel(this->table);
    layout->addWidget(this->cart);

    QWidget* data = new QWidget{};
    QFormLayout* dataForm = new QFormLayout{data};


    this->coatSize = new QLineEdit{};
    QLabel* sizeLabel = new QLabel{ "&Size:" };
    sizeLabel->setBuddy(this->coatSize);
    dataForm->addRow(sizeLabel,this->coatSize);
    layout->addWidget(data);
    QWidget* buttons = new QWidget{};
    QGridLayout* buttonLayout = new QGridLayout{buttons};
    this->startShopping = new QPushButton("Start Shopping!");
    this->showCart = new QPushButton("Display shopping cart");
    buttonLayout->addWidget(this->startShopping,0,0);
    buttonLayout->addWidget(this->showCart,0,1);
    layout->addWidget(buttons);
    QWidget* radio = new QWidget{};
    this->radiobutton = new QButtonGroup{0};
    this->HTML = new QRadioButton("HTML");
    this->CSV = new QRadioButton("CSV");
    radiobutton->addButton(this->HTML);
    radiobutton->addButton(this->CSV);
    layout->addWidget(this->HTML);
    layout->addWidget(this->CSV);
    this->HTML->setChecked(true);


}


void User::userConnector() {
    QObject::connect(this->startShopping,&QPushButton::clicked,this,&User::startShoppingFunction);
    QObject::connect(this->buy,&QPushButton::clicked,this,&User::buyFunction);
    QObject::connect(this->next,&QPushButton::clicked,this,&User::nextFunction);
    QObject::connect(this->finishShopping,&QPushButton::clicked,this,&User::finishShoppingFunction);
    QObject::connect(this->showCart,&QPushButton::clicked,this,&User::displayCart);

}

void User::populate()
{
    this->coatList->clear();
    string message = "Current coat: ";
    message += this->availableCoat.coats[index].toString();
    message += "\n";
    message += "\n";
    message += "\n";
    message += "Your total is: ";
    message += to_string(this->shoppingCart.getSum());
    message += "\n";
    message += "Your cart contains:";
    for(auto i: this->shoppingCart.coats)
    {
        message += i.toString();
        message += "\n";
    }
    QString print = QString::fromStdString(message);
    QListWidgetItem *item = new QListWidgetItem{print};
    this->coatList->addItem(item);

}


void User::startShoppingFunction() {
    if(!shopping) {
        this->shoppingCart.coats.clear();
        this->shopping = true;
        QString size = this->coatSize->text();
        this->serv.repo.fetch_coats(size.toStdString(), this->availableCoat);
        if (this->availableCoat.length() == 0) {
            this->coatList->clear();
            this->shopping = false;
            QString message = QString::fromStdString("There are no coats matching given size!");
            QListWidgetItem *item = new QListWidgetItem{message};
            this->coatList->addItem(item);

        } else
            this->populate();
    }
    else
        QMessageBox::critical(0, "Error", "You are already in a shopping spree!");


}

void User::buyFunction() {
    if(shopping) {
        this->shoppingCart.addCoats(availableCoat.coats[index]);
        this->serv.repo.removeSingleCoat(availableCoat.coats[index]);
        this->availableCoat.removeSingleCoat(this->availableCoat.coats[index]);
        if (this->availableCoat.length() == 0) {
            this->coatList->clear();
            string message = "There are no more coats of this size!\n";
            message += "Your total is: ";
            message += to_string(this->shoppingCart.getSum());
            message += "\n";
            message += "Your cart contains:";
            message += "\n";
            for (auto i: this->shoppingCart.coats) {
                message += i.toString();
                message += "\n";
            }
            QString print = QString::fromStdString(message);
            QListWidgetItem *item = new QListWidgetItem{print};
            this->coatList->addItem(item);
            this->shopping = false;
            this->table = new CoatTableModel(this->shoppingCart);
            this->cart->setModel(this->table);
            this->serv.repo.writeCoats();
        } else{
            this->nextFunction();
        }
    }
    else{
        QMessageBox::critical(0, "Error", "You are not in a shopping spree!");
    }
}

void User::nextFunction() {
    if (shopping){
        index++;
        if (index >= this->availableCoat.length())
            index = 0;
        this->populate();
    }
    else
        QMessageBox::critical(0, "Error", "You are not in a shopping spree!");
}
void User::finishShoppingFunction() {
    if (shopping){
        this->shopping = false;
        string message = "Your total is ";
        message += to_string(this->shoppingCart.getSum());
        QMessageBox::information(this,"Thank you for shopping with us!",QString::fromStdString(message));
        availableCoat.coats.clear();
        this->serv.repo.writeCoats();
        this->table = new CoatTableModel(this->shoppingCart);
        this->cart->setModel(this->table);


    }
    else
        QMessageBox::critical(0, "Error", "You are not in a shopping spree!");


}

void User::displayCart() {
    if(shopping)
        QMessageBox::critical(0, "Error", "You can't do that during shopping spree!");
    else
    {
        if(this->HTML->isChecked())
            this->HTMLCart();
        else
            this->CSVCart();
    }

}

void User::HTMLCart()
{
    HTMLRepository HTML;
    for(auto i : this->shoppingCart.coats)
    {
        HTML.addCoat(i);
    }
    HTML.write();
    HTML.open();

}

void User::CSVCart() {
    CSVRepository CSV;
    for(auto i : this->shoppingCart.coats)
    {
        CSV.addCoat(i);
    }
    CSV.write();
    CSV.open();

}