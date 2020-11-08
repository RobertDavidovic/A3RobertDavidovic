/**************************************************
 Project: RobertDavidovicA1
 Date: Sunday 8th Nov 2020
 Author: Robert Davidovic
 Purpose: To entertain people using a fun text-based
 murder mystery game!
**************************************************/

#include "TheFrankstonHeader.h"
Location * locations[12];
Player player;
vector<Suspect*> suspects;
vector<Item> items;
vector<string> notes;
bool gameEnd = false;


void loadLocations(){
    string locName;
    string locDesc;
    string line;
    ifstream file("Data/locations.txt");
    for (int i = 0; i < 12; i++){
        stringstream lineStream;
        getline(file, line);
        lineStream << line;
        getline(lineStream,locName,'#');
        getline(lineStream,locDesc);
        Location* location = new Location(locName,locDesc);
        locations[i] = location;
    }
    locations[rand() % 12]->setBody();
}

void convertFileToVector(string filename, vector<string>& collection, char newLine = '\n') {
    collection.clear();
    string quote;
    ifstream data(filename);
    while (data.eof() == false) {
        getline(data, quote, newLine);
        collection.push_back(quote);
    }
    data.close();
}

template <typename T>
T retrieveRandomValue(vector<T>& collection){
        int index;
        T value;
        index = rand() % collection.size();
        value = collection[index];
        collection.erase(collection.begin() + index);
        return value;
}

void replaceLine(string& line, string target, string change) {
    size_t start_pos = 0;
    while((start_pos = line.find(target, start_pos)) != string::npos) {
        line.replace(start_pos, target.length(), change);
    }
}

void cleanAlibiLine(stringstream& ssline, int susOne, int susTwo, char endOf /*\n*/){
    string line;
    getline(ssline,line, endOf);
    replaceLine(line,"&&&",suspects[susOne]->getName());
    replaceLine(line,"@@@",suspects[6]->getName());
    suspects[susTwo]->setAlibi(line);
}

void setAlibi(vector<string>& collection, int suspectNumOne, int suspectNumTwo){
    string alibi;
    stringstream ssAlibi;
    alibi = retrieveRandomValue(collection);
    ssAlibi << alibi;
    cleanAlibiLine(ssAlibi,suspectNumOne,suspectNumTwo,'<');
    cleanAlibiLine(ssAlibi,suspectNumTwo,suspectNumOne,'\n');
}

void setAlibis(){
    vector<string> alibis;
    string alibi;
    stringstream ssalibi;
    convertFileToVector("Data/alibi.txt",alibis);
    setAlibi(alibis,1,2);
    setAlibi(alibis,3,4);
    alibi = retrieveRandomValue(alibis);
    ssalibi << alibi;
    if ((rand() % 1) == 0){
        getline(ssalibi,alibi,'<');
    }
    else{
        getline(ssalibi,alibi, '<');
        getline(ssalibi,alibi);
    }
    replaceLine(alibi,"&&&",suspects[rand() % 5+1]->getName());
    replaceLine(alibi,"@@@",suspects[6]->getName());
    suspects[0]->setAlibi(alibi);
    if ((rand() % 573) == 46){
        suspects[0]->setAlibi("I am the Ripper. I was out ripping yesterday and now I'm going to rip you"); /*This is an Easter Egg*/
    }
    convertFileToVector("Data/singleAlibi.txt",alibis);
    alibi = retrieveRandomValue(alibis);
    replaceLine(alibi,"@@@",suspects[6]->getName());
    suspects[5]->setAlibi(alibi);
}


void generateItems(string filename, int itemNum, bool murderWeapon){
    vector<string> itemData;
    convertFileToVector(filename,itemData);
    for (int i = 0; i < itemNum; i++){
        string line;
        stringstream ssline;
        string name;
        string description;
        line = retrieveRandomValue(itemData);
        ssline << line;
        getline(ssline,name,'#');
        getline(ssline,description);
        Item item(name,description,murderWeapon);
        items.push_back(item);
    }
}

void generateAllItems(){
    generateItems("Data/items.txt",3);
    generateItems("Data/murderWeapons.txt",2);
    generateItems("Data/murderWeapons.txt",1,true);
    int roomNum;
    for (int i = 0; i < items.size(); i++){
        roomNum = rand() % 12;
        locations[roomNum]->addItem(&items[i]);
    }
}

void generateSuspects(){
    vector<string> names;
    vector<string> descriptions;
    vector<int> bribables;
    vector<int> wantedItems;
    convertFileToVector("Data/names.txt",names,',');
    convertFileToVector("Data/desc.txt",descriptions);
    Suspect* killer = new Suspect(retrieveRandomValue(names),retrieveRandomValue(descriptions),true);
    suspects.push_back(killer);
    for (int i = 0; i < 6;i++){
        bribables.push_back(i);
        int namesIndex;
        Suspect * sus = new Suspect(retrieveRandomValue(names),retrieveRandomValue(descriptions));
        suspects.push_back(sus);
    }
    for(int i = 0; i < 3; i++){
        wantedItems.push_back(i);
    }
    suspects[retrieveRandomValue(bribables)]->setWantedItem(&items[retrieveRandomValue(wantedItems)]);
    suspects[retrieveRandomValue(bribables)]->setWantedItem(&items[retrieveRandomValue(wantedItems)]);
    setAlibis();
}

void displayFileText(string filename){
    string line;
    ifstream file(filename);
    while (getline(file, line)) {
    cout << line << '\n';
  }
  file.close();
}

void displayAndWait(string filename, string exit){
    string command;
    displayFileText(filename);
    do{
    getline(cin, command);
    }while(command != exit);
}

void goToLocation(string locName){
    bool locationFound;
    for(int i = 0; i < 12; i++){
        if(locName == locations[i]->getName()){
            player.setLocation(locations[i]);
            locationFound = true;
            break;
        }
    }
    if (!locationFound){
        cout << "Location was not found\n";
        return;
    }
    cout << "------"<< player.getlocation()->getName() << "------\n" << player.getlocation()->getDescription() <<'\n';
}

void fillLocations(){
    vector<int> locationIndex;
    for(int i = 0; i < 12; i++){
        locationIndex.push_back(i);
    }
    for(int i = 0; i < suspects.size()-1; i++){
        int randIndex = retrieveRandomValue(locationIndex);
        locations[randIndex]->setSuspect(suspects[i]);
    }
}

void search(){
    bool nothingFound = true;
    cout << "You search the area. ";
    if (player.getlocation()->getSuspect()){
        cout << "You find a person called " << player.getlocation()->getSuspect()->getName() << ". "; 
        nothingFound = false;
    }
    if(player.getlocation()->itemsSize() == 1){
        cout << "You find a " << player.getlocation()->getItem(0)->getName() << ". ";
        nothingFound = false;
    }
    if(player.getlocation()->itemsSize() > 1){
        cout << "You find these items here;\n";
        for (int i = 0; i < player.getlocation()->itemsSize(); i++){
            cout << player.getlocation()->getItem(i)->getName() << '\n';
        }
        nothingFound = false;
    }
    if(player.getlocation()->isMurderLocation()){
        cout << "This is where the murder took place. \n";
        nothingFound = false;
    }
    if(nothingFound){
        cout << "You find nothing of note\n";
    }

}


void question(string susName){
    bool quit = false;
    string command;
    if (player.getlocation()->getSuspect()->getName() == susName){
        if (player.getlocation()->getSuspect()->getWantedItem()){
            if (player.getlocation()->getSuspect()->getWantedItem()->getName() == "vegemite-sandwich"){
                cout << "\nDo you speak my language? \n"; /*This is an Easter Egg*/
                return;
            }
            cout << "\nDon't talk to me until you find me " << player.getlocation()->getSuspect()->getWantedItem()->getName() << '\n';
            return;
        }
        cout << "Ask the player 'who' too see who they are and 'what' to see what they were doing yesterday. Say 'bye' to leave\n";
        while(!quit){
            getline(cin,command);
            if (command == "who"){
                cout << susName << " says " << '"' << player.getlocation()->getSuspect()->getDescription() << '\n';
            }
            else if(command == "what"){
                cout << susName << " says " << '"' << player.getlocation()->getSuspect()->getAlibi() << '\n';
            }
            else if (command == "bye"){
                cout << "You walk away from " << susName <<'\n';
                quit = true;
            }
            else{
                cout << "Invalid command\n";
            }
        }
    }
    else{
        cout << "\nThat person could not be found here\n";
    }
}

void swapItem(ItemHolder& holder, ItemHolder& taker, string itemName, string message){
        for (int i = 0; i < holder.itemsSize();i++){
        if (holder.getItem(i)->getName() == itemName){
            taker.addItem(holder.getItem(i));
            replaceLine(message,"{item}",holder.getItem(i)->getName());
            cout << message;
            holder.removeItem(i);
            return;
        }
    }
    cout << "That item could not be found\n";
}

void bag(){
    if (player.itemsSize() == 0){
        cout << "You have no items in your bag \n";
    }
    else if(player.itemsSize() == 1){
        cout << "You have a " << player.getItem(0)->getName() << " in your bag.\n";
    }
    else{
        cout << "You have these items in your bag;\n";
        for (int i = 0; i < player.itemsSize(); i++){
            cout << player.getItem(i)->getName() << '\n';
        }
    }
}

void examine(string itemName){
    for (int i = 0; i < player.itemsSize(); i++){
        if (player.getItem(i)->getName() == itemName){
            cout << player.getItem(i)->getDescription() << '\n';
            if (player.getItem(i)->isMurderWeapon()){
                cout << " This is the murder weapon.\n";
            }
            return;
        }
    }
    cout << "You don't have this item";
}

void bribe(Suspect& sus, Item *item){
    if(sus.getWantedItem() == item){
        cout << "You give " << sus.getName() << " the " << item->getName() << '\n';
        sus.setWantedItem(nullptr);
        for (int i = 0; i < player.itemsSize(); i++){
            if (player.getItem(i)->getName() == item->getName()){
                player.removeItem(i);
            }
        }
    }
    else{
        cout << """I don't want this.\n""";
    }
}

void give(string item, string suspect){
    if (player.getlocation()->getSuspect()->getName() != suspect){
        cout << "That person is not here\n";
        return;
    }
    for (int i = 0; i < player.itemsSize(); i++){
        if (player.getItem(i)->getName() == item){
            bribe(*player.getlocation()->getSuspect(), player.getItem(i));
            return;
        }
    }
    cout << "You do not have this item.\n";
}

void note(){
    string line;
    cout << "Type exit as a line to leave";
    cout << "\n------------NOTE PAD------------\n";
    for (int i = 0; i < notes.size();i++)
    {
        cout << notes[i] << '\n';
    }
    do
    {
        getline(cin,line);
        if (line != "exit"){
            notes.push_back(line);
        }
    } while (line != "exit");
    
}


void inputCommand(){
    string command;
    string parameter;
    stringstream input;
    getline(cin, command);
    input << command;
    getline(input,command,' ');
    getline(input,parameter);
    cout << '\n';
    if(command == "help"){
        displayAndWait("Data/instructions.txt","ok");
        return;
    }
    else if(command == "map"){
        cout << "MAP\n";
        for (int i = 0; i < 12; i++){
            cout << locations[i]->getName() << '\n';
        }
        return;
    }
    else if(command == "go"){
        goToLocation(parameter);
        return;
    }
    else if(command == "question"){
        question(parameter);
    }
    else if(command == "search"){
        search();
    }
    else if (command == "get"){
        swapItem(*player.getlocation(),player,parameter,"You pick up the {item} and put it in your bag\n");
    }
    else if (command == "bag")
    {
        bag();
    }
    else if (command == "drop"){
        swapItem(player,*player.getlocation(),parameter,"You drop the {item} here\n");
    }
    else if(command == "examine"){
        examine(parameter);
    }
    else if (command == "give"){
        string itemName;
        string susName;
        stringstream parameters;
        parameters << parameter;
        getline(parameters,itemName,' ');
        getline(parameters,susName);
        give(itemName,susName);
    }
    else if(command == "eat"){  /*This is an Easter Egg*/
        for (int i = 0; i < player.itemsSize();i++){
            if (player.getItem(i)->getName() == "fish"){
                if (parameter == "fish"){
                    cout << "You turn into a fish. The worldy concerns of mere land-walkers no longer affects you. You have beaten this game with the true ending.";
                    gameEnd = true;
                    return;
                }
            }
        }
        cout << "Invalid Command";
    }
    else if (command == "accuse"){
        cout << "You call all the suspects to this location.";
        string response;
        if(player.getlocation()->isMurderLocation()){
            cout << " You're in the right spot but do you have the murder weapon?\n";
            bag();
            cout << "\nName the murder weapon: ";
            getline(cin,response);
            for (int i =0; i < player.itemsSize();i++){
                if(player.getItem(i)->getName() == response){
                    if(player.getItem(i)->isMurderWeapon()){
                        cout << "That's the murder weapon. Now who is the murderer.\nThese are the possible suspects;\n";
                        for (int i = 0; i < 6; i ++){
                            cout << suspects[i]->getName() << '\n';
                        }
                        getline(cin,response);
                        for (int i = 0; i < suspects.size();i++){
                            if(suspects[i]->getName() == response){
                                if (suspects[i]->isRipper()){
                                    cout << "\nCongratulations! You have called out the Ripper and they are beaten by the crowd around them. You win the game!!!\n";
                                    getline(cin,response);
                                    gameEnd = true;
                                    return;
                                }
                            }
                        }
                        cout << "\nYou accuse the wrong person and they go to jail. You lose your job and the game.\n";
                        getline(cin,response);
                    }
                }
            }
            cout << "\nNope you're wrong and fired as detective. You lose.\n";
            getline(cin,response);
            gameEnd = true;
        }
        else{
            cout << " However this isn't where the murder took place. You are fired as detective.\n";
            getline(cin,response);
            gameEnd = true;
        }
    }
    else if(command == "quit"){
        string response;
        cout << "You quit because you are lazy\n";
        getline(cin,response);
    }
    else if(command == "notes"){
        note();
    }
    else{
        cout << "Invalid Command";
    }
    cout<<"\nEnter a command\n";
}


void intro(){
    srand((unsigned int)time(NULL));
    loadLocations();
    generateAllItems();
    generateSuspects();
    fillLocations();
    displayAndWait("Data/intro.txt","play");
    displayAndWait("Data/instructions.txt","ready");
    player.setLocation(locations[rand() % 12]);
    cout << "\n------" << player.getlocation()->getName() << "------\n" << player.getlocation()->getDescription() << '\n' << "Enter a command" << '\n';
}

int main(){
    intro();
    do
    {
        inputCommand();
    } while (!gameEnd);
     
    return 0;
}