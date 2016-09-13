#include <iostream>
#include <fstream>
#include <string>

#include "lexanalyzer.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 1) // make sure the user executed
    {             // the program correctly

        cout << "ERROR:  NO FILE SPECIFIED, PLEASE TRY AGAIN." << endl;
        return 1;
    }

    lexanalyzer analyzer(argv);  // create and run the
    analyzer.charReader();       // analyer

    return 0;
}
