#ifndef __COMMON_H__
#define __COMMON_H__
using namespace std;
#include <sstream>      
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Item.h"
#include "Suspect.h"
#include "ItemHolder.h"
#include "Location.h"
#include "Player.h"


template <typename T>
T retrieveRandomValue(vector<T>& collection);
void generateSuspects();
void setAlibi(vector<string>& collection, int suspectNumOne, int suspectNumTwo);
void setAlibis(Suspect& first, Suspect& second);
void inputCommand();
void loadLocations();
void displayFileText(string filename);
void fillLocations();
void cleanAlibiLine(stringstream& ssline, int susOne, int susTwo, char endOf);
void generateItems(string filename, int itemNum, bool murderWeapon = false);
void displayAndWait(string filename, string exit);
void goToLocation(string locName);
void questionMode(Suspect sus);
void question(string susName);
void generateAllItems();
void get(string ItemName);
void drop(string ItemName);
void examine(string itemName);
void give(string item, string suspect);
void bag();
void intro();
void search();
#endif