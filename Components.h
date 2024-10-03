#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef COMPONENTS_H
#define COMPONENTS_H


class Components
{
public:
    Components();
    virtual ~Components();
protected:
private:
};



///Player Components
class CPlayer
{
public:
    bool                 isPlaying    = true;      //Player1 true and player2 false at the start of the game.It will be used for turns- false when the other player is playing.
                                                   //It will be used together with military units flag isActive. When player isPlaying=true also all of his units are set to active=true.
    bool                 baseOccupied = false;     //If players base is occupied,flag is set to true. If players base is occupied for 2 turns, game is over.
    unsigned short int   unitsTotal   = 3;         //Total units.The game starts with 3 units.
    unsigned short int   ironTotal    = 0;         //Iron resource total.
    unsigned short int   goldTotal    = 0;         //Gold resource total.
    unsigned short int   minesTotal   = 0;         //Total amount of mines concquered.
};



///Military Unit Components
class CTransform
{
public:
    sf::Vector2f position;           //Entity position
    sf::Vector2f velocity;           //Entity velocity
    sf::Vector2f spriteSize;         //Sprite size
    sf::Vector2f spriteHalfSize;     //Sprite half size. Used set sprite setOrigin in the  middle od the sprite.

    sf::Vector2f startingPosition;   //Entity position at the start of the game. It's used for restarting level.

    //Constructor-Destructor
    CTransform(sf::Vector2f sizeSprt)
               : spriteSize(sizeSprt),
                 spriteHalfSize(sizeSprt.x / 2, sizeSprt.y / 2) {}
    virtual ~CTransform() {};
};


class CMilitaryUnit
{
public:
//data members
    bool               movePressed   = false;  //Move button pressed.
    bool               unitMoved     = false;  //Unit moved.

    bool               attackPressed = false;  //Attack button pressed.
    bool               unitAttacked  = false;  //Unit attacked.

    int                health        = 0;      //Number of soldiers in a unit. By default there are 5. Every soldier in a units has 1 dice to throw.
    unsigned short int movementRange = 0;      //Tank 2 tiles, artilery 1 tile, infantry 1 tile.
    unsigned short int shootingRange = 0;      //Tank 1 tile, artilery 2 tiles, infantry 1 tile.

    unsigned short int movementRangeDefault = 0;   //Initialized in Entity Manager with movement range of the unit. Used in endTurn Game to reset the values if units moved.

    sf::Sprite spriteMilitaryUnit;

};


class CSpecial
{
public:
    unsigned short int rankLevel = 1;   //Military unit rank. Every rank changes the unit white dice into red dice.

    bool               whiteDice1 = true;
    bool               whiteDice2 = true;
    bool               whiteDice3 = true;

};


///Unit health cubes
class CHealth
{
//data members
public:
    std::vector<sf::Sprite> healthBar;

};



///Tile Compnents
class CTile
{
public:
    bool isWalkable         = false;     //Non-walkable tiles: mountains, obstacles, mines, bases, military units.
    bool baseActive         = false;     //Green base is active when green player is playing and yellow player base is inactive, and vice versa.
    bool mineOwnedByPlayer1 = false;     //When player1 one ownes the mine. Used in Selection infoWindow.
    bool mineOwnedByPlayer2 = false;     //When player2 one ownes the mine. Used in Selection infoWindow.

    sf::Sprite spriteTile;

};



///Resource Components  (also for player component)
class CResources
{
public:
    bool ironMine = false;                  //When player conquers a mine1, bool == true, starts accumulating ironIncome.
    bool goldMine = false;                  //When player conquers a mine, boll == true, starts accumulating ironIncome

    unsigned short int ironIncome = 20;          //If flag for iron mine true, start income.
    unsigned short int goldIncome = 15;          //If flag for gold mine true, start income.
};




#endif // COMPONENTS_H
