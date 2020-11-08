#include "TheFrankstonHeader.h"
class Player : public ItemHolder
{
private:
    Location *location;
    vector<Item*> items;
public:
    Player();
    Location * getlocation();
    void setLocation(Location *setLocation);
};

Player::Player(){

}


Location * Player::getlocation(){
    return location;
}

void Player::setLocation(Location *setLocation){
    location = setLocation;
}
