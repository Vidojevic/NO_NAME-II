#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "EntityManager.h"
#include <iostream>
#include <string>

#ifndef MSELECTION_H
#define MSELECTION_H


class MSelection
{
//data members
public:
    bool               actionMenuDisplayed     = false;   //The unit action menu displayed.
    bool               infoWindowDisplayed     = false;   //Military unit Info window displayed.

    bool               infoBaseWindowDisplayed = false;   //Base info window displayed.
    bool               baseActionMenuDisplayed = false;   //Action menu for player base displayed (Build Units, End Turn).

    bool             ironMineOwnerColorDisplay = false;   //Displays color of the player who owns a iron mine in the mine info window.
    bool             goldMineOwnerColorDisplay = false;   //Displays color of the player who owns a gold mine in the mine info window.


    bool               baseActionMenuBuild     = false;   //Action menu for player base, build options (Infantry, Artilery, Tank).

    bool               selectionActive         = true;    //Used to disable selection when combat window active. Used in Game class.

    bool               rank1Active             = false;   //When rank1 is active. Used for the draw function.
    bool               rank2Active             = false;   //When rank2 is active. Used for the draw function.
    bool               rank3Active             = false;   //When rank3 is active. Used for the draw function.
    bool               rank4Active             = false;   //When rank4 is active. Used for the draw function.

    unsigned short int selectedUnitID;                 //Storing the ID of current selected entity(unit).

    std::vector<sf::Sprite> baseActionMenu;            //Build Units, End Turn buttons for players Base action menu.

public:
    //info window text strings
    sf::Font font;               //Text font.
private:
    sf::Text text1;              //Lines of text in the info window.
    sf::Text text2;              //
    sf::Text text3;              //
    sf::Text text4;              //
    sf::Text text5;              //
    sf::Text text6;              //base info window lines
    sf::Text text7;              //
    sf::Text text8;              //
public:
    //action menu sprites
    sf::Sprite moveIcon;         //Action menu move icon.
    sf::Sprite attackIcon;       //Action menu attack icon.
    sf::Sprite fortifyIcon;      //Action menu fortify icon.
private:
    //info window sprite
    sf::Sprite infoWndw;
    //Rank sprites for info window
    sf::Sprite rank1;
    sf::Sprite rank2;
    sf::Sprite rank3;
    sf::Sprite rank4;
    //rect representing the colors of player who ownes the iron mine amd gold mine: green-player1 , red-player2
    sf::RectangleShape ironMineOwnerColor;
    sf::RectangleShape goldMineOwnerColor;

//functions
public:
    void actionMenu(EntityManager& entityManager, sf::Sound& unitSelection, sf::Sound& baseSelection);    //Opening the action menu when clicking on military units.
    void infoWindow(EntityManager& entityManager);    //Opening an info window when hovering above military units.

    void deselectBaseActionMenyDisplayed();           //Closing the base action menu + repositioning the button sprites outside of the map when closed. The reason for repositioning is because there
                                                      //is a conflict between button sprites and unit sptites when they occupy the same tile. (BUG)
    void deselectActionMenuDisplayed();               //Same as for function above, but for unit action menu. Closing and repositioning outside the map. Same problem as function above this one.

    void draw(sf::RenderWindow& renderWndw);

//Konstruktor/Destruktor
public:
    MSelection(EntityManager& entityMng);
    virtual ~MSelection();

};

#endif // MSELECTION_H
