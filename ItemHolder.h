#include "TheFrankstonHeader.h"
class ItemHolder : public Object
{
protected:
    vector<Item*> items;
public:
    void addItem(Item* itemToAdd);
    void removeItem(int index);
    Item* getItem(int index);
    int itemsSize();
};


void ItemHolder::addItem(Item* itemToAdd){
    items.push_back(itemToAdd);
}

Item * ItemHolder::getItem(int index){
    return items[index];
}

void ItemHolder::removeItem(int index){
    items.erase(items.begin() + index);
}

int ItemHolder:: itemsSize(){
    return items.size();
}