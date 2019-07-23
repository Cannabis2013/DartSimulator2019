#ifndef OUTPUTMANAGER_H
#define OUTPUTMANAGER_H

#include <iostream>
#include <qstring.h>

using namespace std;

class OutputManager
{
public:
    enum printMode{Linebreak,NoLinebreak};

    static void print(const QString &output,const printMode &mode = printMode::Linebreak)
    {
        cout << output.toStdString();
        if(mode == printMode::Linebreak)
            cout << endl;
    }

    static void print(const int &output,const printMode &mode = printMode::Linebreak)
    {
        cout << output;
        if(mode == printMode::Linebreak)
            cout << endl;
    }
};

#endif // OUTPUTMANAGER_H
