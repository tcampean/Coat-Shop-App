//
// Created by Tudor on 4/16/2021.
//

#ifndef A67_912_CAMPEAN_TUDOR_ALEXANDRU_CSVREPOSITORY_H
#define A67_912_CAMPEAN_TUDOR_ALEXANDRU_CSVREPOSITORY_H

#include "WriteRepository.h"
#include <fstream>
#include <windows.h>
#include <shellapi.h>

class CSVRepository : public WriteRepository
{
public:
    void write() override
    {
        ofstream f("D:\\GitHub\\a10-912-Campean-Tudor-Alexandru-1\\example.csv",ios::trunc);
        f.close();
        f.open("D:\\GitHub\\a10-912-Campean-Tudor-Alexandru-1\\example.csv",ios::app);

        if(!f.is_open())
            return;
        for(auto c:this->coats)
        {
            f<<c;
        }
        f.close();
    }

    void open() override
    {
        ShellExecuteA(nullptr,"open","C:\\Windows\\system32\\notepad.exe","D:\\GitHub\\a89-912-Campean-Tudor-Alexandru\\example.csv",nullptr,SW_SHOWNORMAL);
    }
};

#endif //A67_912_CAMPEAN_TUDOR_ALEXANDRU_CSVREPOSITORY_H
