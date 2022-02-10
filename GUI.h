//
// Created by Tudor on 5/6/2021.
//

#ifndef A89_912_CAMPEAN_TUDOR_ALEXANDRU_GUI_H
#define A89_912_CAMPEAN_TUDOR_ALEXANDRU_GUI_H
#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include <Service.h>
#include <QRadioButton>
#include "WriteRepository.h"
#include <QButtonGroup>
#include <CoatTableModel.h>
#include <QTableView>
#include "UndoRedo.h"
#include "QShortcut"
#include <stack>

class Admin: public QWidget
{
    Q_OBJECT
private:
    stack<UndoRedo*> UndoOperations;
    stack<UndoRedo*> RedoOperations;

public:
    Admin(QWidget* parent = 0);
    ~Admin();
    void initAdmin();
    QListWidget* coatList;
    QLineEdit* coatSize;
    QLineEdit* coatColour;
    QLineEdit* coatPrice;
    QLineEdit* coatQuantity;
    QLineEdit* coatPhoto;
    string fileName;
    QPushButton* addCoat;
    QPushButton* removeCoat;
    QPushButton* updateCoat;
    QPushButton* logOut;
    QPushButton* Open;
    QPushButton* Undo;
    QPushButton* Redo;
    void adminConnector();
    Service serv;
    void ReadData();
    void addCoatButton();
    void populateCoatList();
    int getSelected();
    void itemSelection();
    void deleteCoatButton();
    void updateCoatButton();
    QShortcut* undoShortcut;
    QShortcut* redoShortcut;

    signals:
            void addCoatSignal(const std::string&,const std::string&,const int&,const int&,const std::string&);
    void listUpdateSignal();

public slots:
            void addCoatFunction(const std::string&,const std::string&,const int&,const int&,const std::string&);
            void undo();
            void redo();

};

class User: public QWidget
{
    Q_OBJECT
private:
    bool shopping;
    WriteRepository shoppingCart;
    Repository availableCoat;
    int index;

public:
    User(QWidget* parent = 0);
    ~User();
    void initUser();
    Service serv;
    CoatTableModel* table;
    QListWidget* coatList;
    QTableView* cart;
    QLineEdit* coatSize;
    QPushButton* startShopping;
    QPushButton* showCart;
    QPushButton* buy;
    QPushButton* next;
    QPushButton* finishShopping;
    QRadioButton* HTML;
    QRadioButton* CSV;
    QButtonGroup* radiobutton;
    void userConnector();
    void startShoppingFunction();
    void populate();
    void buyFunction();
    void nextFunction();
    void finishShoppingFunction();
    void HTMLCart();
    void CSVCart();
    void displayCart();


};

class GUI: public QWidget
{
    Q_OBJECT
public:
    GUI(QWidget* parent = 0);

private:
    void initMain();
    void connector();
    QPushButton* userButton;
    void UserMode();
    QPushButton* adminButton;
    void AdminMode();
    Admin adminMode;
    User userMode;


private slots:

};

#endif //A89_912_CAMPEAN_TUDOR_ALEXANDRU_GUI_H
