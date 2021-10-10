#ifndef JSONPARSER_CPP
#define JSONPARSER_CPP

#include "jsonparser.hpp"

void JsonParser::ParseIt(string fname)
{
    /* Проверка на массив */
    bool isarray = false;
    /* Проверка открывались ли кавычки */
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
        /* Игнорируем логику разбора, если массив */
        if(isarray)
        {
            if(tmp == ']')
                isarray = false;
            else if(tmp == '"' || tmp == ',')
            {
                buffer.push_back(tmp);
                continue;
            }
        }
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
            /* Двойные кавычки */
            case '"':
                /* Помечаем, что были кавычки у значения */
                if(!valueinq)
                    valueinq = true;
                /* Интертируем флаг открытых кавычек */
                inq = !inq;
                break;
            /* Начался массив */
            case '[':
                /* Помечаем, что у нас открылся массив */
                if(!isarray)
                    isarray = true;
                buffer.push_back(tmp);
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
