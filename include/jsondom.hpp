#ifndef JSONDOM_HPP
#define JSONDOM_HPP

#include <iostream>
#include <fstream>
#include <list>

using namespace std;

/* Класс для узлов дерева элементов */
class JsonDomItem
{
    private:
        JsonDomItem *parent;
        string key;
        string value;
        /* В ковычках значение или нет */
        bool valueinq;
        list<JsonDomItem> childs;
    public:
        JsonDomItem(void);
        JsonDomItem(JsonDomItem *p);
        JsonDomItem* GetParent(void);
        /* Создает потомка, возвращает адрес
            на него */
        JsonDomItem* CreateChild(void);
        void SetKey(string k);
        void SetValue(string v, bool inq);
        string GetPart(void);
        void Print(void);
        void Print(unsigned int tabnum, bool separator);
        void PrintByKey(string k);
};

/* Класс обертка для операций над деревом из
    JsonDomItem'ов */
class JsonDom
{
 private:
    JsonDomItem root;
    /* Текущий элемент построения дерева,
        используется для навигации по дереву,
        но не для выделения памяти! */
    JsonDomItem *cur;
 public:
    JsonDom(void);
    void CurSetKey(string key);
    void CurSetValue(string value, bool inq);
    void AddChildToCur();
    void LevelUp();
    void PrintByKey(string key);
};

#endif /* JSONDOM_HPP */
