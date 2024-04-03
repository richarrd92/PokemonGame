/*****************************************
** File:    Pokemon.h
** Project: CMSC 202 Project 2, Spring 2024
** Author:  Richard Maliyetu
** Date:    3/11/24
** Section: 33
** E-mail:  r215@gl.umbc.edu 
** E-mail:  r215@umbc.edu 
**
** This file contains the declaration of the class Pokemon
** This program creates an object of pokemon 
** the pokemon objects has several member functions and data to perform certain specific pokemon actions
** for example the Train method. to train the pokemon etc
** more info in the project description.
***********************************************/

#ifndef POKEMON_H //Header Guards
#define POKEMON_H //Header Guards

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//Constants
const int TRAIN_VALUE = 10; //CP increase when Train is completed

class Pokemon{
 public:
  // Name: Pokemon (default constructor)
  // Desc: Constructs an empty Pokemon
  // Preconditions - None
  // Postconditions - Pokemon created
  Pokemon();
  // Name: Pokemon (overloaded constructor)
  // Desc: Constructs a populated Pokemon
  // Preconditions - None
  // Postconditions - Pokemon created with passed num, name, cp, rarity
  Pokemon(int num, string name, int cp, int rarity);
  // Name: GetCP
  // Desc: Returns CP
  // Preconditions - None
  // Postconditions - Returns CP
  int GetCP();
  // Name: GetRarity
  // Desc: Returns rarity
  // Preconditions - None
  // Postconditions - Returns rarity
  int GetRarity();
  // Name: GetName
  // Desc: Returns name
  // Preconditions - None
  // Postconditions - Returns name
  string GetName();
  // Name: GetNum
  // Desc: Returns num
  // Preconditions - None
  // Postconditions - Returns num
  int GetNum();
  // Name: SetRarity
  // Desc: Updates the rarity (between 1 and 3)
  // Preconditions - None
  // Postconditions - Updates m_rarity
  void SetRarity(int newRarity);
  // Name: SetName
  // Desc: Updates the name
  // Preconditions - None
  // Postconditions - Updates m_name
  void SetName(string newName);
  // Name: SetCP
  // Desc: Updates the combat power (CP)
  // Preconditions - None
  // Postconditions - Updates m_CP
  void SetCP(int newCP);
  // Name: Train
  // Desc: Increases the CP by TRAIN_POWER up to maxCP
  // Preconditions - maxCP is calculated and passed to this function
  // Postconditions - Updates m_CP by TRAIN_POWER to maxCP
  void Train(int maxCP);
private:
  int m_num; //Number of the Pokemon
  string m_name; //Name of the Pokemon
  int m_CP; //Combat power of the Pokemon
  int m_rarity; //Rarity of the Pokemon
};

#endif
