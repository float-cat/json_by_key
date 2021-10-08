#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <iostream>
#include <fstream>
#include "jsondom.hpp"

using namespace std;

/* Парсер, который разбирает JSON для
    помещения данных в дерево элементов */
class JsonParser
{
 private:
    enum {
        read_key,
        read_value
    };
    void ParseIt(string fname);
    JsonDom jsondom;
 public:
    JsonParser(string fname);
    void PrintByKey(string key);
};

#endif /* JSONPARSER_HPP */
