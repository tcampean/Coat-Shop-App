//
// Created by Tudor on 3/20/2021.
//

#include "UI.h"
#include <iostream>
#include <string.h>
#include <Validators.h>
#include "CSVRepository.h"
#include "HTMLRepository.h"




void UI::print_menu() {
    cout<<"1: Administrator"<<endl;
    cout<<"2: User"<<endl;
}

void UI::print_menu_admin() {
    cout<<"1: Add a coat"<<endl;
    cout<<"2: Remove a coat"<<endl;
    cout<<"3: Update a coat"<<endl;
    cout<<"4: List all coats"<<endl;
    cout<<"5: Log out"<<endl;
    cout<<"0: Exit"<<endl;
}

void UI::print_menu_client() {
    cout<<"1: Look through coats"<<endl;
    cout<<"2: Open Shopping Cart file"<<endl;
    cout<<"3: Log out"<<endl;
    cout<<"0: Exit "<<endl;
}

void UI::add_ui() {
    string size,colour,price,quantity,photo;
    cout<<"Enter a size:";
    cin>>size;
    cout<<"Enter a colour:";
    cin>>colour;
    cout<<"Enter a price:";
    cin>>price;
    cout<<"Enter a quantity:";
    cin>>quantity;
    cout<<"Enter a link:";
    cin>>photo;
    inputValidator input;
    input.validateInput(price,quantity);
    int int_price = stoi(price);
    int int_quantity = stoi(quantity);
    Coat c(size,colour,int_price,int_quantity,photo);
    this->serv.servAdd(c);
}

void UI::remove_ui() {
    string size,color;
    cout<<"Enter a size:";
    cin>>size;
    cout<<"Enter a colour:";
    cin>>color;
    int result = this->serv.servRemove(size,color);
    if(result == 1)
        cout<<"Coat removed successfully!" <<endl;
    else
        cout<<"The coat does not exist!"<<endl;



}

void UI::update_ui() {
    string size,colour,new_size,new_colour,price,quantity,photo;
    string buffer;
    getline(cin,buffer);
    cout<<"Enter the size:";
    getline(cin,size);
    cout<<"Enter the colour:";
    getline(cin,colour);
    cout<<"Enter the new size:";
    getline(cin,new_size);
    cout<<"Enter the new colour:";
    getline(cin,new_colour);
    cout<<"Enter the new price:";
    getline(cin,price);
    cout<<"Enter the new quantity:";
    getline(cin,quantity);
    cout<<"Enter the new link:";
    getline(cin,photo);
    inputValidator input;
    input.validateInput(price,quantity);

    int int_price;
    int int_quantity;
    if(price.empty())
        int_price = -1;
    else
        int_price = stoi(price);
    if(quantity.empty())
        int_quantity = -1;
    else
        int_quantity = stoi(quantity);
    int result = this->serv.updateCoat(size,colour,new_size,new_colour,int_price,int_quantity,photo);
    if(result == 1)
        cout<<"Coat updated successfully!"<<endl;


}

void UI::test_coats() {
    Coat c("XL","Red",500,3,"Yes");
    this->serv.servAdd(c);
    Coat a("XXL","Red",5600,2,"Yes2");
    this->serv.servAdd(a);
    Coat b("L","Blue",520,6,"No");
    this->serv.servAdd(b);
    Coat x("M","Yellow",2500,1,"Yes22");
    this->serv.servAdd(x);
    Coat d("M","Green",5200,7,"Yes11");
    this->serv.servAdd(d);
    Coat f("XL","Green",500,2,"Yes11");
    this->serv.servAdd(f);
    Coat z("XXL","Green",200,6,"Yes22");
    this->serv.servAdd(z);
    Coat g("L","Red",500,3,"Myabe");
    this->serv.servAdd(g);
    Coat h("M","Black",5200,4,"Yes111");
    this->serv.servAdd(h);
    Coat i("L","Black",500,1,"Yes22");
    this->serv.servAdd(i);
}

void UI::list() {
    for(auto i : this->serv.repo.coats)
        cout<<i.toString()<<endl;
}

void UI::client_navigation_menu()
{
    cout<<"1: Buy"<<endl;
    cout<<"2: Next"<<endl;
    cout<<"3: Show shopping cart"<<endl;
    cout<<"4: Exit shopping spree"<<endl;

}

void UI::client_navigation(WriteRepository *shopping_cart)
{
    bool shopping_spree = true;
    Repository available_coats;
    string size,buffer;
    cout<<"Enter a size:";
    getline(cin,buffer);
    getline(cin,size);
    this->serv.repo.fetch_coats(size,available_coats);
    if(available_coats.length()==0) {
        cout << "There are no coats matching this size!" << endl;
        return;
    }
    int index = 0;
    while(shopping_spree)
    {
        int command;
        cout<<endl;
        cout<<"Current coat: "<<available_coats.coats[index].toString()<<endl;
        this->client_navigation_menu();
        cout<<"Enter command:";
        cin>>command;
        if(command == 1) {
            shopping_cart->addCoats(available_coats.coats[index]);
            shopping_cart->write();
            cout << "The coat was added to the shopping cart!" << endl;
            cout << "Your total is " << shopping_cart->getSum() << endl;
            this->serv.repo.removeSingleCoat(available_coats.coats[index]);
            available_coats.removeSingleCoat(available_coats.coats[index]);
            index++;
            if(available_coats.length()==0) {
                cout << "There are no more coats!" << endl;
                cout<<"Your cart contains: "<<endl;
                for(auto i:shopping_cart->coats)
                    cout<<i.toString()<<endl;
                cout<<"Your total is "<<shopping_cart->getSum()<<endl;
                shopping_spree = false;
            }
            if(index >= available_coats.length())
                index = 0;

        }
        else if(command == 2) {
            index++;
            if (index >= available_coats.length())
                index = 0;
        }
        else if(command == 3)
        {   cout << "Your cart contains: " << endl;
            for(auto i:shopping_cart->coats)
                cout<<i.toString()<<endl;
            cout << "Your total is " << shopping_cart->getSum() << endl;
        }

        else if(command == 4)
        {
            cout << "Your cart contains: " << endl;
            for(auto i:shopping_cart->coats)
                cout<<i.toString()<<endl;
            cout << "Your total is " << shopping_cart->getSum() << endl;
            cout<<"Thank you for shopping with us!"<<endl;
            shopping_spree = false;
        }

    }
}

void UI::run(){
    bool selected = false;
    string user_type;
    this->serv.repo.readCoats("yes.txt");
    while(!selected)
    {
        this->print_menu();
        cout<<"Enter type of user:";
        cin>>user_type;
        if(user_type == "1" || user_type == "2")
            selected = true;
        bool logged = true;
        if(user_type == "1")
            this->run_admin(logged);
        else
            this->run_user(logged);
        if(!logged)
            selected = false;

    }

}

void UI::run_admin(bool &logged)
{
    bool done = false;
    while(!done){
        int command;

        this->print_menu_admin();
        cout<<"Enter a command:";
        cin>>command;
        if(command == 1) {
            try{
                this->add_ui();
                this->serv.repo.writeCoats();
            }catch(ValidationException& v)
            {
                cout<<v.getError()<<endl;
            }catch (RepositoryException& r) {
                cout << "The coat already exists!" << endl;
            }
        }
        else if (command == 2)
            try {

                this->remove_ui();
                this->serv.repo.writeCoats();
            }catch(RepositoryException& r)
            {
                cout<<"The coat doesn't exist!"<<endl;
            }
        else if(command == 3)
            try{
                this->update_ui();
                this->serv.repo.writeCoats();
            }catch(ValidationException& v)
            {
                cout<<v.getError()<<endl;
            }catch(RepositoryException& r)
            {
                cout<<"The coat to be modified doesn't exist or the modifications interfere with other coats"<<endl;

            }
        else if(command == 4)
            this->list();
        else if(command == 5)
        {
            logged = false;
            done = true;
        }
        else if(command == 0)
            done = true;
    }

}

void UI::run_user(bool &logged)
{
    bool done = false;
    HTMLRepository HTML;
    CSVRepository CSV;
    cout<<"1: HTML file"<<endl;
    cout<<"2: CSV file"<<endl;
    int filetype;
    cout<<"Enter a command:";
    cin>>filetype;
    while(!done)
    {
        int command;
        this->print_menu_client();
        cout<<"Enter a command:";
        cin>>command;
        if(command == 1) {
            WriteRepository *shopping_cart;
            if(filetype == 1)
            {
                shopping_cart = &HTML;
            }
            else{
                shopping_cart = &CSV;
            }
            this->client_navigation(shopping_cart);
            this->serv.repo.writeCoats();
            HTML.clear();
            CSV.clear();
        }
        else if (command == 2)
        {
            if(filetype == 1)
                HTML.open();
            else
                CSV.open();
        }
        else if(command == 3)
        {
            logged = false;
            done = true;

        }
        else {
            done = true;
        }

    }

}