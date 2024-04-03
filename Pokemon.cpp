/*****************************************
** File:    Pokemon.cpp
** Project: CMSC 202 Project 2, Spring 2024
** Author:  Richard Maliyetu
** Date:    3/11/24
** Section: 33
** E-mail:  r215@gl.umbc.edu 
** E-mail:  r215@umbc.edu 
**
** This file contains the implementation of the class Pokemon
** This program creates an object of pokemon 
** the pokemon objects has several member functions and data to perform certain specific pokemon actions
** for example the Train method. to train the pokemon etc
** more info in the project description.
***********************************************/
 
#include <iostream>
#include "Pokemon.h"
#include <cstdlib>
#include <string>
using namespace std;
  
  // Name: Pokemon (default constructor)
  // Desc: Constructs an empty Pokemon
  // Preconditions - None
  // Postconditions - Pokemon created
  Pokemon::Pokemon(){

  }
  // Name: Pokemon (overloaded constructor)
  // Desc: Constructs a populated Pokemon
  // Preconditions - None
  // Postconditions - Pokemon created with passed num, name, cp, rarity
  Pokemon::Pokemon(int num, string name, int cp, int rarity){
      SetName(name);
      SetCP(cp);
      SetRarity(rarity);
  }
  // Name: GetCP
  // Desc: Returns CP
  // Preconditions - None
  // Postconditions - Returns CP
  int Pokemon::GetCP(){
    return m_CP;
  }
  // Name: GetRarity
  // Desc: Returns rarity
  // Preconditions - None
  // Postconditions - Returns rarity
  int Pokemon::GetRarity(){
    return m_rarity;
  }
  // Name: GetName
  // Desc: Returns name
  // Preconditions - None
  // Postconditions - Returns name
  string Pokemon::GetName(){
    return m_name;
  }
  // Name: GetNum
  // Desc: Returns num
  // Preconditions - None
  // Postconditions - Returns num
  int Pokemon::GetNum(){
    return m_num;
  }
  // Name: SetRarity
  // Desc: Updates the rarity (between 1 and 3)
  // Preconditions - None
  // Postconditions - Updates m_rarity
  void Pokemon::SetRarity(int newRarity){
      m_rarity = newRarity;
  }
  // Name: SetName
  // Desc: Updates the name
  // Preconditions - None
  // Postconditions - Updates m_name
  void Pokemon::SetName(string newName){
      m_name = newName;
  }
  // Name: SetCP
  // Desc: Updates the combat power (CP)
  // Preconditions - None
  // Postconditions - Updates m_CP
  void Pokemon::SetCP(int newCP){
      m_CP = newCP;
  }
  // Name: Train
  // Desc: Increases the CP by TRAIN_POWER up to maxCP
  // Preconditions - maxCP is calculated and passed to this function
  // Postconditions - Updates m_CP by TRAIN_POWER to maxCP
  void Pokemon::Train(int maxCP){

      // temp var to hold CP value
      int tempCP = Pokemon::GetCP(); 

      // train if CP is <= maxCP  
      if(Pokemon::GetCP() <= maxCP) 
      {
        tempCP += TRAIN_VALUE ;  // add train value to tempCP
        Pokemon::SetCP(tempCP);  // update CP in pokemon to tempCP
      }

      // dont train if CP is > maxCP  
      else
      {
        cout << "\n maxCP reached can't train " << Pokemon::GetName() << "anymore" <<endl;
      }
  }