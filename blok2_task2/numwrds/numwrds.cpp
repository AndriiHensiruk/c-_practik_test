//one more nice code block
#include <iostream>
#include <fstream>
#include <string>

void readfail(std::string path)
{
   
    std::ifstream fil;
    fil.open(path);

    if (!fil.is_open())
    {
        printf("Fail not open");

    }
    else
    {
        printf("Fail is open");
        std::string ch;
        while (!fil.eof())
            ch = "";
        getline(fil, ch);
        std::cout << ch;
    }

    fil.close();
}

int main(int argc, char* argv[])
{
           
    int i;
 
    for (i = 0; i < argc; i++)
    {

        if ((std::strcmp(argv[i], "-f") == 0) && (std::strcmp(argv[i], "-c") == 0))
        {
            printf("An error occurred while typing");;
            // break;
        }
        if (std::strcmp(argv[i], "-h")==0)
        {
            std::cout << argv[0] << "\n";
           // break;
        }
        if (std::strcmp(argv[i], "-c")==0)
        {
            printf("%d\n", argc);
            //break;
        }
        if (std::strcmp(argv[i], "-v")==0)
        {
            printf( "version 2.1");
           // break;
        }
        if (std::strcmp(argv[i], "-f") == 0)
        {
            std::string arg = argv[i];
            readfail(arg);
            // break;
        }

    }
    
   

    system("pause");

    return 0;
}