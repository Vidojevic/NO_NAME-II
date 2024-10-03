#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <cstdlib>
#include "EntityManager.h"
#include "MSelection.h"
#include "MMovement.h"
#include "MCombat.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>

#ifndef GAME_H
#define GAME_H


class Game
{
private:
//data members
    bool baseGreenOccupied               = false;    //Counting turns if base is occupied. If the value is 3, game over.
    bool baseYellowOccupied              = false;    //
    bool inGameMenuDisplay               = false;    //Show menu in game by pressing ESC.
    bool gameWindow                      = false;    //Gaming window.
public:
    unsigned short int baseGreenCounter  = 0;        //Counts turns when base occupied=true. If value 3, game over.
    unsigned short int baseYellowCounter = 0;        //
private:
    unsigned short int unitYellowID      = 0;        //Stores the id of unit thta curently occupies enemy base. If the unit is moved or destroyed, counter and bool are reseted.
    unsigned short int unitGreenID       = 0;        //

    sf::Sprite inGameMenu;                           //Menu in the game. Opens by pressing ESC.
    sf::Sprite winPlayer1;                           //Victory window for player1.
    sf::Sprite winPlayer2;                           //Victory window for player2.

    sf::Font fontStartWindow;                        //Font used in the start window.
    sf::Text menuText1;                              //In game menu options. Save game.
    sf::Text menuText2;                              //Load game.
    sf::Text menuText3;                              //Restart.
    sf::Text menuText4;                              //Main Menu.
    sf::Text menuText5;                              //Quit Game.
    sf::Text menuText6;                              //Close menu window.

    std::vector<sf::SoundBuffer> soundBuffer;

//funtions
public:
    void run();
private:
    void initialization(EntityManager& manager);      //Drawing tiles, units, structures at their start positions

    void endTurn(EntityManager& manager);             //End turn function. isPlaying = false; All units = inactive, baseActive = false, and more..

    void saveGame(EntityManager& manager, const MSelection& selection)const;                                 //Save game.
    void loadGame(EntityManager& manager, MSelection& selection, MMovement& movement, MCombat& combat);      //Load game.
    void restartGame(EntityManager& manager, MSelection& selection, MMovement& movement, MCombat& combat);   //Restart game.



//Constructor-Destructor
public:
    Game();
    virtual ~Game();
};

#endif // GAME_H
