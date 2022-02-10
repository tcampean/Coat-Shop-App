//
// Created by Tudor on 4/17/2021.
//

#ifndef A89_912_CAMPEAN_TUDOR_ALEXANDRU_HTMLREPOSITORY_H
#define A89_912_CAMPEAN_TUDOR_ALEXANDRU_HTMLREPOSITORY_H

#include <WriteRepository.h>
#include <fstream>
#include <windows.h>


class HTMLRepository : public WriteRepository
{
public:
    void write() override
    {
        ofstream f("D:\\GitHub\\a89-912-Campean-Tudor-Alexandru\\example.html",ios::trunc);
        f.close();
        f.open("D:\\GitHub\\a89-912-Campean-Tudor-Alexandru\\example.html",ios::app);
        if(!f.is_open())
            return;
        f<<"<!DOCTYPE html>"<<endl;
        f<<"<html>"<<endl;
        f<<"<head>\n"<<"<title>Shopping cart</title>\n"<<"</head>\n"<<endl;
        f<<"<body>"<<endl;
        string str = "<table border=\"1\">";
        f<<str<<endl;
        f<<"<tr>"<<endl;
        f<<"<td>Size</td>"<<endl;
        f<<"<td>Colour</td>"<<endl;
        f<<"<td>Price</td>"<<endl;
        f<<"<td>Quantity</td>"<<endl;
        f<<"<td>Link</td>"<<endl;
        f<<"</tr>"<<endl;
        for(auto c:this->coats) {
            f << "<tr>" << endl;
            f << "<td>" << c.getSize() << "</td>" << endl;
            f << "<td>" << c.getColour() << "</td>" << endl;
            f << "<td>" << c.getPrice() << "</td>" << endl;
            f << "<td>" << c.getQuantity() << "</td>" << endl;
            f << "<td><a href=\"" << c.getPhoto() << "\">Link</a></td>" << endl;
            f << "</tr>" << endl;
        }

        f<<"</table>"<<endl;
        f<<"</body>"<<endl;
        f<<"</html>"<<endl;
        f.close();
    }

    void open() override
    {
        ShellExecuteA(nullptr, "open", "example.html", nullptr, "D:\\GitHub\\a89-912-Campean-Tudor-Alexandru",
                      SW_SHOWNORMAL);
    }
};

#endif //A89_912_CAMPEAN_TUDOR_ALEXANDRU_HTMLREPOSITORY_H
