#ifndef JSONDOM_CPP
#define JSONDOM_CPP

#include "jsondom.hpp"

JsonDomItem::JsonDomItem(void)
{
    parent = NULL;
    valueinq = false;
}

JsonDomItem::JsonDomItem(JsonDomItem *p)
{
    parent = p;
    valueinq = false;
}

JsonDomItem* JsonDomItem::GetParent(void)
{
    return parent;
}

JsonDomItem* JsonDomItem::CreateChild(void)
{
    JsonDomItem item(this);
    childs.push_back(item);
    /* Получаем указатель на новый элемент
        в конце списка детей */
    return &(*(childs.rbegin()));
}

void JsonDomItem::SetKey(string k)
{
    key = k;
}

void JsonDomItem::SetValue(string v, bool inq)
{
    value = v;
    valueinq = inq;
}

/* Получаем строку адреса */
string JsonDomItem::GetPart(void)
{
    string result("/");
    JsonDomItem *p = parent;
    while(p->parent!=NULL)
    {
        result = "/" + p->key + result;
        p = p->parent;
    }
    return result;
}

/* Метод обертка для рекурсивной распечатки */
void JsonDomItem::Print(void)
{
    cout << GetPart();
    Print(0, false);
}

void JsonDomItem::Print(unsigned int tabnum, bool separator)
{
    unsigned int t = tabnum;
    /* Выставляем табуляцию */
    while(t-- > 0)
        cout << static_cast<char>(9);
    if(key.length()>0)
    {
        /* Корректируем кавычки */
        if(tabnum == 0)
            cout << key << ": ";
        else
            cout << "\"" << key << "\": ";
    }
    t = 0;
    if(value.length()>0)
    {
        if(valueinq)
            cout << "\"" << value << "\"";
        else
            cout << value;
        if(separator)
            cout << ",";
        cout << endl;
    }
    else
    {
        cout << "{" << endl;
        /* Печать потомков, последний потом обрабатывается
            отдельно, чтобы учесть отсутствие запятой */
        auto last = --childs.end();
        for(auto it = childs.begin(); it != last; it++)
            (*it).Print(tabnum+1, true);
        (*last).Print(tabnum+1, false);
        /* Выставляем табуляцию */
        t = tabnum;
        while(t-- > 0)
            cout << static_cast<char>(9);
        cout << "}";
        if(separator)
            cout << ",";
        cout << endl;
    }
}

void JsonDomItem::PrintByKey(string k)
{
    for(auto it = childs.begin(); it != childs.end(); it++)
    {
        if((*it).key == k)
            (*it).Print();
        (*it).PrintByKey(k);
    }
}

/* Класс обертка для операций над деревом из
    JsonDomItem'ов */

JsonDom::JsonDom(void)
{
    cur = &root;
}

void JsonDom::CurSetKey(string key)
{
    cur->SetKey(key);
}

void JsonDom::CurSetValue(string value, bool inq)
{
    cur->SetValue(value, inq);
}

void JsonDom::AddChildToCur()
{
    cur = cur->CreateChild();
}

void JsonDom::LevelUp()
{
    cur = cur->GetParent();
}

void JsonDom::PrintByKey(string key)
{
    root.PrintByKey(key);
}


#endif /* JSONDOM_CPP */
