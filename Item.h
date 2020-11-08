#include "TheFrankstonHeader.h"
class Item : public Object
{
private:
    bool murderWeapon;
public:
    Item();
    Item(string itemName, string itemDesc,bool makeMurder = false);
    bool isMurderWeapon();
};

Item::Item()
{
}

Item::Item(string itemName, string itemDesc, bool makeMurder){
    name = itemName;
    description = itemDesc;
    murderWeapon = makeMurder;
}

bool Item::isMurderWeapon(){
    return murderWeapon;
}