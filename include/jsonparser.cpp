#ifndef JSONPARSER_CPP
#define JSONPARSER_CPP

#include "jsonparser.hpp"

void JsonParser::ParseIt(string fname)
{
    /* Проверка открывались ли ковычки */
    bool valueinq = false;
    bool inq = false;
    unsigned int state = read_key;
    /* Приемник для символов */
    char tmp;
    ifstream in;
    in.open(fname);
    string buffer;
    if(!in.is_open())
        throw "Open file error!";
    while(in.get(tmp))
    {
        /* Разбираем документ JSON по следующей логике */
        switch(tmp)
        {
            /* Удаляем переносы, табуляцию и запятые */
            case 13: break;
            case 10: break;
            case 9: break;
            case ',':
                if(state == read_value)
                {
                    jsondom.CurSetValue(buffer, valueinq);
                    jsondom.LevelUp();
                    buffer.clear();
                    state = read_key;
                    valueinq = false;
                }
                break;
            /* Пробелы */
            case 32:
                /* Если между ковычек - пробелы
                    тоже сохраняем */
                if(inq)
                    buffer.push_back(tmp);
                break;
            /* Признак конца ключа */
            case ':':
                if(state == read_key)
                {
                    jsondom.AddChildToCur();
                    jsondom.CurSetKey(buffer);
                    buffer.clear();
                    state = read_value;
                    valueinq = false;
                }
                break;
            /* Спускаемся вниз по дереву элементов */
            case '{':
                state = read_key;
                buffer.clear();
                break;
            /* Поднимаемся вверх по дереву элементов */
            case '}':
                if(state == read_value)
                {
                    jsondom.CurSetValue(buffer, valueinq);
                    jsondom.LevelUp();
                    buffer.clear();
                    state = read_key;
                    valueinq = false;
                }
                jsondom.LevelUp();
                break;
            /* Двойные ковычки */
            case '"':
                /* Помечаем, что были ковычки у значения */
                if(!valueinq)
                    valueinq = true;
                /* Интертируем флаг открытых ковычек */
                inq = !inq;
                break;
            default:
                buffer.push_back(tmp);
        }
    }
}

JsonParser::JsonParser(string fname)
{
    ParseIt(fname);
}

void JsonParser::PrintByKey(string key)
{
    jsondom.PrintByKey(key);
}

#endif /* JSONPARSER_CPP */
