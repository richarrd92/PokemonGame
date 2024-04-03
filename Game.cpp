
#include "Pokemon.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Name: Game Constructor
// Desc - Sets m_filename based on string passed
// Preconditions - Input file passed
// Postconditions - m_filename updated
Game::Game(string filename){
    m_filename = filename; // assigns user input to m_filename
}

// Name: LoadFile
// Desc - Opens file and reads in each Pokemon into m_PokeDex
// Preconditions - Input file passed and populated with Pokemon
// Postconditions - m_pokeDex populated with Pokemon
void Game::LoadFile(){
  fstream myFile;
  myFile.open(m_filename); // opens file 

  string dataArray[TOTAL_POKEMON][4] = {}; // Array to store data from file

       // Load and Store Data from file to dataArray ( dataArray[][] )
       while(myFile.good())
       {
           for(int i = 0;  i < TOTAL_POKEMON; i++ )
           {
               for(int j = 0; j < 4; j++)
               {
                   myFile >> dataArray[i][j];
               }
           }
       }

  myFile.close(); // closes file 

  // Fill up Master list of all Pokemon in the game with data from dataArray
      for(int i = 0;  i < TOTAL_POKEMON; i++ )
      {
          m_pokeDex[i].SetName(dataArray[i][1]); 
          m_pokeDex[i].SetCP(stoi(dataArray[i][2]));    // use of func stoi to convert string into integer
          m_pokeDex[i].SetRarity(stoi(dataArray[i][3]));
      }
}

// Name: DisplayPokeDex
// Desc - Display all Pokemon in the m_pokeDex
// Preconditions - m_pokeDex populated with Pokemon
// Postconditions - None
void Game::DisplayPokeDex(){
    cout <<endl;
    for(int i = 0; i < TOTAL_POKEMON; i++)
    {
      cout << i+1 << "." << setw(NAME_WIDTH) << m_pokeDex[i].GetName() <<endl; // NAME_WIDTH to format pokeDex display of names
    }
}

// Name: MainMenu
// Desc - Displays main menu
// Preconditions - m_pokeDex populated
// Postconditions - Keeps calling until quit chosen
void Game::MainMenu(){

    int userChoice; // User menu choice 
    do
    {
        cout <<endl;
        cout << "What would you like to do?:" <<endl;
        cout << "1. Display Complete PokeDex" <<endl;
        cout << "2. Display your Team" <<endl;
        cout << "3. Search for a new Pokemon" <<endl;
        cout << "4. Battle your Pokemon" <<endl;
        cout << "5. Train your Pokemon" <<endl;
        cout << "6. Exit" <<endl;
        cin >> userChoice;

          switch(userChoice)
          {
              // keeps Displaying menu if userChoice out of bounds (1-6)
              while(userChoice < 1 && userChoice > 6)
              {
                  Game::MainMenu(); // calls main menu
              }

              case 1:   Game::DisplayPokeDex(); break;
              case 2:   Game::DisplayTeam();    break; 
              case 3:   Game::CatchPokemon();   break; 
              case 4:   Game::BattlePokemon();  break;
              case 5:   Game::TrainPokemon();   break;
              case 6:   userChoice = 6;         break; // Sets userChoice -> 6 
          }

      }while(userChoice != 6); // Breaks out of Do-While 

    cout <<endl << "Thanks for playing!" <<endl; 
}

// Name: CatchPokemon
// Desc - Main function for catching pokemon. Does the following:
//        1. Calls CatchMenu and stores rarity chosen
//        2. Randomly chooses a number between 0 - 99
//        3. If random number is less than rarity, calls FoundPokemon
//        4. If random number is greater than rarity, indicates none found
//        5. Call AddPokemon if new Pokemon is caught
// Preconditions - m_pokeDex has maximum CP for Pokemon
// Postconditions - After random Pokemon of that rarity is chosen,
//                  this function reduces the CP of between 30-50%
//                  and adds to m_team
  void Game::CatchPokemon(){
    cout <<endl;

    int rarity = Game::CatchMenu(); // stores return value from catchMenu into rarity
    int percentProb; // stores rarity in percentage form
    int randNumb = rand() % 98 +1; // Randomly chooses a number between 0 - 99

          // sets common rarity from integer to percentage
          if(rarity == 1)
          {
            percentProb = COMMON; // 45% chance
          }

          // sets uncommon rarity from integer to percentage
          else if (rarity == 2)
          {
            percentProb = UNCOMMON; // 25% chance
          } 
          
          else if (rarity == 3)
          {
            percentProb = ULTRA; // 1% chance
          } 


    // If random number is less than percentProb, calls FoundPokemon
    if(randNumb < percentProb)
    {

        // passes rarity into FoundPokemon function
        // passses foundPokemon into AddPokemon function
        Game::AddPokemon(Game::FoundPokemon(rarity));

    } 
      
    // If random number is greater than rarity, indicates none found
    else
    {
        cout << "No pokemon found! search again! " <<endl;
    }

  }

// Name: CatchMenu
// Desc - User chooses which rarity of Pokemon to try and catch
// Preconditions - m_pokeDex has rarities of 1-3
// Postconditions - Returns choice of 1-3
  int Game::CatchMenu(){
    int rarity; // stores rarity choice from the user
    cout <<endl;
    cout << "What rarity of Pokemon would you like catch?: " <<endl;
    cout << "1. Common (High Probability)" <<endl;
    cout << "2. Uncommon (Normal Probability)" <<endl;
    cout << "3. Ultra Rare (Extremely Low Probability)" <<endl;
    cin >> rarity;

    // keeps prompting if value rarity value entered is out of bounds 
    while (!((rarity > 0) && (rarity < 4)))
    {
    cout <<endl;
    cout << "What rarity of Pokemon would you like catch?: " <<endl;
    cout << "1. Common (High Probability)" <<endl;
    cout << "2. Uncommon (Normal Probability)" <<endl;
    cout << "3. Ultra Rare (Extremely Low Probability)" <<endl;
    cin >> rarity;
    }

    if(rarity == 1)
    {
      cout << "\nYou start to search..." <<endl;
      return 1; // 45% chance
    }

    else if (rarity == 2)
    {
      cout << "\nYou start to search..." <<endl;
      return 2; // 25% chance
    } 

    cout << "\nYou start to search..." <<endl;
    return 3; // 1% chance
  }

// Name: FoundPokemon
// Desc - Based on rarity passed in, randomly chooses one Pokemon
//        from the m_pokeDex, updates the CP, and adds to m_team
// Preconditions - m_pokeDex has maximum CP for Pokemon
// Postconditions - After random Pokemon of that rarity is chosen,
//                  this function reduces the CP of between 30-50%
//                  and adds to m_team
  Pokemon Game::FoundPokemon(int rarity){

    int randNumb = rand() % TOTAL_POKEMON; // random number between (0-150) -> all the pokemon in the game
    
    // keeps trying random numbers until pokemon with similar rarity found
    while(m_pokeDex[randNumb].GetRarity() != rarity)
    {
      randNumb = rand() % TOTAL_POKEMON; 
    }

    cout << "You found a " << m_pokeDex[randNumb].GetName() <<endl;

    return m_pokeDex[randNumb]; // returns found pokemon
  }

// Name: AddPokemon
// Desc - Figures out where to insert newly found Pokemon
//        If m_team has opening, inserts into first open slot
//        If m_team is full, inserts into first slot with lower CP
//        If m_team is full, and new Pokemon has lower CP, does not insert
//        Tells user if not inserted
// Preconditions - None
// Postconditions - New Pokemon is added to m_team if possible
//                  or user is notified that there is no room
  void Game::AddPokemon(Pokemon newPokemon){
      
      Pokemon temp = newPokemon; // temporay pokemon Object

      // m_team is has an opening/ open slot
      if(Game::TeamSize() < NUM_TEAM)
      {
            int reduction = (rand() % ((MAX_FIND-1) - (MIN_FIND+1) +1)) + (MIN_FIND+1); // assigns rand numb btn (50-30) to reduction
            double reductionPercent = reduction/(double)100; // converts reduction to percentage
            int reduced_CP = temp.GetCP() - (temp.GetCP() * reductionPercent); // gets amount of CP reduced

            // m_pokeDex[randNumb].SetCP(reduced_CP); // set CP to reduce_CP
            temp.SetCP(reduced_CP); // set temp pokemon CP to reduce_CP

            m_team[Game::TeamSize()] = temp; // adds temp pokemon to m_team then increments

            cout << temp.GetName() << " added to your team!" <<endl;
      }

      // m_team is full
      else 
      {   
            int lowestCP = 0; //  sets lowest CP to zero
            int min = 5000; // number to replicate minimum 

            // iterates through m_team to find the lowest CP
            for(int i = 0; i < NUM_TEAM; i++)
            {
                if(m_team[i].GetCP() < min)
                {
                    min = m_team[i].GetCP(); // stores the lowest CP in m_team into min 
                    lowestCP = min; // store min into lowest CP
                }
            }

            // if new pokemon CP has higher CP compared to all pokemon in m_team
            if(lowestCP < temp.GetCP()) 
            {
              // iterates through m_team
              for(int i = 0; i < NUM_TEAM; i++)
              {
                  if(m_team[i].GetCP() == lowestCP) // if CP in m_team < CP in newPokemon
                  {
                    m_team[i] = temp; // adds new pokemon at index pokemon with the lowest CP is found

                    int reduction = (rand() % ((MAX_FIND-1) - (MIN_FIND+1) +1)) + (MIN_FIND+1); // assigns rand numb btn (50-30) to reduction
                    double reductionPercent = reduction/(double)100; // converts to percentage
                    int reduced_CP = temp.GetCP() - (temp.GetCP() * reductionPercent); // gets amount of CP reduced

                    m_team[i].SetCP(reduced_CP); // set CP to reduce_CP

                    cout << temp.GetName() << " added to your team!" <<endl;
                    break;
                  }
              } 
            }
            
            // if new found pokemon CP is less than all CP in m_team          
            else
            {   
              cout << temp.GetName() << " has lower CP, hence not Added to team" <<endl;
            }
      }
  }


// Name: TeamSize
// Desc - Iterates through m_team to see how many team members exist
// Preconditions - m_team exists
// Postconditions - Returns 0 if empty otherwise up to 4
  int Game::TeamSize(){
    int emptySlots = NUM_TEAM; // m_team by default has 4

    for(int i = 0; i < NUM_TEAM; i++)
    {
      if(m_team[i].GetName().empty())
      { 
        // -1 for every empty slot found
        emptySlots--;
      }
    }

    // returns 0 if team is empty
    return emptySlots; // returns value stored in size
  }

// Name: DisplayTeam
// Desc - Iterates through m_team to display information about team
// Preconditions - m_team exists
// Postconditions - None
  void Game::DisplayTeam(){
    cout <<endl;

      // if team is empty
      if(Game::TeamSize() == 0)
      {
        cout << "You have no team yet. Maybe search for a Pokemon?!" <<endl;
      }

      else
      {
        // iterate through m_team
        for(int i = 0;  i < Game::TeamSize(); i++ )
        {
            cout << i+1 << "." << setw(NAME_WIDTH) << m_team[i].GetName() << setw(NUM_WIDTH) << m_team[i].GetCP() <<endl;
        }
      }

  }

// Name: FindPokemon
// Desc - Iterates through m_pokeDex to see if matching name exists
//        Returns index if found else -1
// Preconditions - m_pokeDex exists
// Postconditions - Returns index of match, else -1
  int Game::FindPokemon(string name){

    // iterates through all pokemon in the game
    for(int i = 0; i < TOTAL_POKEMON; i++)
    {
        if(name ==  m_pokeDex[i].GetName())
        {
          return i; // returns index i if match case found
        }
    }

    return -1; // returns -1 if no match found
  }

// Name: TrainPokemon
// Desc - If m_team size is 0. If 0, tells user and returns to main menu
//        If m_team size > 0, displays team (DisplayTeam)
//        Asks user to chose one team member
//        Calls Train on chosen team member and passes corresponding CP
//             value from m_pokeDex (m_pokeDex holds max CP for all)
// Preconditions - m_team and m_pokeDex exists
// Postconditions - Calls Train on chosen team member
  void Game::TrainPokemon(){
    cout <<endl;

    // m_team is empty
    if(Game::TeamSize() == 0)
    {
        cout << "You have no Pokemon yet. Maybe search for a Pokemon?!" <<endl;
    }

    // m_team contains pokemon(s)
    else
    {
        int userChoice; // number selected by user
        cout << "Which of your pokemon would you like to use?:"<<endl;
        Game::DisplayTeam(); // displays team
        cin >> userChoice;

          // keeps prompting if value entered is out of bounds 
          while ((userChoice > Game::TeamSize()) || (userChoice <= 0))
          {
            cout <<endl;
            cout << "Which of your pokemon would you like to use?:"<<endl;
            Game::DisplayTeam(); // displays team
            cin >> userChoice;
          }

            // stores value returned from FindPokemon into index
            int index = Game::FindPokemon(m_team[userChoice-1].GetName()); // -1 to get appropriate index in array
            
            //Calls Train on chosen team member and passes corresponding CP value from m_pokeDex (m_pokeDex holds max CP for all)
            m_team[userChoice-1].Train(m_pokeDex[index].GetCP());

            cout <<endl << "Your " << m_team[userChoice-1].GetName() << " CP goes up!" <<endl;
      }
  }

// Name: BattlePokemon
// Desc - If m_team size is 0. If 0, tells user and returns to main menu
//        If m_team size > 0, randomly chooses Pokemon to fight from
//        m_pokeDex. Asks which team member to use in battle.
//        Random enemy has a CP of 0 - max CP + 200.
//        Compares CP for random enemy and team member.
//        If team member wins, indicates and returns to main menu
//        If team member loses, indicates, sets CP to 0, returns to menu
// Preconditions - m_team exists
// Postconditions - Either the player wins or team member's CP is set to 0
  void Game::BattlePokemon(){
    cout <<endl;

    // m_team is empty
    if(Game::TeamSize() == 0)
    {
        cout << "You have no team yet. Maybe search for a Pokemon?!" <<endl;
    } 

    else
    {        
        int randNumb = rand() % TOTAL_POKEMON; // random number between (0-150) -> all the pokemon in the game

        Pokemon temp = m_pokeDex[randNumb]; // creates temporay pokemon Object = pokemon found 
        
        int randCP = (rand() % (m_pokeDex[randNumb].GetCP() -1)) +1; // randNumb btn (0- maxCP)            
        
        temp.SetCP(randCP+200);

        cout << "You are going to fight a " << temp.GetName() <<endl;
        cout << "The enemy has a CP of " << temp.GetCP() <<endl<<endl;

        int userChoice; // number selected by user
        cout << "Which of your pokemon would you like to use?:"<<endl;
        Game::DisplayTeam(); // displays team
        cin >> userChoice;

          // keeps prompting if value entered is out of bounds 
          while ((userChoice > Game::TeamSize()) || (userChoice <= 0))
          {
            cout <<endl;
            cout << "Which of your pokemon would you like to use?:"<<endl;
            Game::DisplayTeam(); // displays team
            cin >> userChoice;
          }

          // team member has lower CP
          if(m_team[userChoice-1].GetCP() < temp.GetCP())
          {
              m_team[userChoice-1].SetCP(0);
              cout << "\nYou lost." <<endl;
              cout << "Your " << m_team[userChoice-1].GetName() << " can't lift its head." <<endl;
              cout << "You should replace it." <<endl;
          }

          else
          {
            cout << "\nYou won!!" <<endl;
          }
    }
  }

// Name: Start
// Desc - Calls LoadFile then MainMenu
// Preconditions - m_fileName is populated
// Postconditions - Exits game when done running
  void Game::Start(){
    Game::LoadFile();
    Game::MainMenu();
  }        
 
