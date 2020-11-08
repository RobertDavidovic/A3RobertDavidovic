#include "TheFrankstonHeader.h"
class Suspect : public Object
{
private:
    string alibi;
    bool murderer;
    Item * wantedItem = nullptr;
public:
    Suspect(string susName, string susDesc, bool killer = false);
    string getAlibi();
    void setAlibi(string susAlibi);
    Suspect();
    Item * getWantedItem();
    void setWantedItem(Item* item);
    bool isRipper();
};

Suspect::Suspect(string susName, string susDesc, bool killer)
{
    name = susName;
    description = susDesc;
    murderer = killer;
}

string Suspect::getAlibi(){
    return alibi;
}

void Suspect::setAlibi(string susAlibi){
    alibi = susAlibi;
}

Item * Suspect::getWantedItem(){
    return wantedItem;
}

void Suspect::setWantedItem(Item* item){
    wantedItem = item;
}

bool Suspect::isRipper(){
    return murderer;
}