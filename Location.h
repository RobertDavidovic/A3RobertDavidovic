#include "TheFrankstonHeader.h"
class Location : public ItemHolder
{
private:
    bool murder_location = false;
    Suspect* suspect = nullptr;
public:
    Location();
    Location(string location_name, string location_description);
    Suspect * getSuspect();
    bool isMurderLocation();
    void setSuspect(Suspect *sus);
    void setBody();
};
Location::Location(){
    
}
Location::Location(string location_name, string location_description)
{
    name = location_name;
    description = location_description;
}

Suspect * Location::getSuspect(){
    return suspect;
}

bool Location::isMurderLocation(){
    return murder_location;
}

void Location::setSuspect(Suspect *sus){
    suspect =  sus;
}
void Location::setBody(){
    murder_location = true;
}