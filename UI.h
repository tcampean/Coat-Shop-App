//
// Created by Tudor on 3/20/2021.
//

#ifndef A45_912_CAMPEAN_TUDOR_ALEXANDRU_UI_H
#define A45_912_CAMPEAN_TUDOR_ALEXANDRU_UI_H

#include "Service.h"
#include "WriteRepository.h"

class UI{
public:
    Service serv;
public:
    UI() = default;
    void add_ui();
    void remove_ui();
    void update_ui();
    void list();
    void print_menu_admin();
    void print_menu_client();
    void print_menu();
    void run();
    void run_admin(bool &logged);
    void run_user(bool &logged);
    void test_coats();
    void client_navigation(WriteRepository *shopping_cart);
    void client_navigation_menu();
};


#endif //A45_912_CAMPEAN_TUDOR_ALEXANDRU_UI_H
