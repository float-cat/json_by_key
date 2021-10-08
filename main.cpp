#include <cstdlib>
#include <iostream>

#include "include/jsonparser.hpp"

using namespace std;

int main(int argc, char **argv)
{
    try
    {
        /* Проверяем ключики */
        if(argc == 5 && string(argv[1]) == "-f" &&
            string(argv[3]) == "-k")
        {
            JsonParser parser(argv[2]);
            parser.PrintByKey(argv[4]);
        }
        /* Все остальные варианты, включая атрибут -h */
        else
        {
            cout << "USING: -f <file_name> -k <key>" << endl;
            return EXIT_SUCCESS;
        }
    }
    catch (const char &e)
    {
        cerr << e << endl;
        return -1;
    }
    return EXIT_SUCCESS;
}
