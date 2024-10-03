#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Entity.h"
#include <cstdlib>
#include <ctime>
#include "Dice.h"
#include <iostream>

#ifndef MCOMBAT_H
#define MCOMBAT_H


class MCombat
{
public:
    bool                      combatWindowActive = false;   //Showing combat window.
    bool                      attackActive       = false;   //Showing red tiles for attack.
    bool                      attackerWin        = false;   //If attacker wins in battle, the unit gets promotion. Used in combatResult and unitPromotion functions.
    bool                      defenderWin        = false;   //If defender wins in battle, the unit gets promotion.
    bool                      stalemateWin       = false;   //If stalemate battle, used in unitPromotion function.
    bool                      promotionWindow    = false;   //Display promotion window for 2-3 second when promotion earned.

private:
    std::vector<sf::Texture*> combatWindowTextVec;  //Combat window 3 parts texture.
public:
    std::vector<sf::Sprite>   combatWindowVec;      //Combat window 3 parts sprites.
private:
    std::vector<sf::Sprite>   player1ThrowedDice;   //Vector for storing throwed dice for player 1.
    std::vector<sf::Sprite>   player2ThrowedDice;   //Vector for storing throwed dice for player 2.

    std::vector<sf::Sprite>   player1SortedDice;    //Vector for storing throwed dice for player 1.
    std::vector<sf::Sprite>   player2SortedDice;    //Vector for storing throwed dice for player 2.

    std::vector<sf::RectangleShape> rectVec;        //Storing tile rectangles for attackShow mechanics.

    int player1BubbleSort[3];                       //After throwing dice, values are copied in this array and bubble sort algorythm is aplied. Then the values are compared with the player 2 array.
    int player2BubbleSort[3];                       //Values are stored as numbers, not sprites.

    Dice player1Dice;                               //Dice for player 1.
    Dice player2Dice;                               //Dice for player 2.

    sf::Font font;                                  //Text font.
    sf::Text win;                                   //Text strings
    sf::Text loose;                                 //
    sf::Text stalemate1;                            //
    sf::Text stalemate2;                            //
    sf::Text exitCombatWindow;                      //

//Functions
private:
    int  whiteDiceThrow();              //Throwing 1 white dice algorythm. Returns a value between 0-5.
    int  redDiceThrow();                //Throwing 1 red dice algorythm. Returns a value between 0-5, without 1 but with two 2.
    void throwingDices(Entity& player); //Throw dices according to unit's rank. Each player needs to use this function.
    void bubbleSort();                  //Bubble sort dice throw in array as numbers not sprites.
    void dicePositionCombatWindow();    //Sets the position of dices on combat window.
public:
    void attackShow(EntityManager& manager, Entity& entity);  //When Attack button clicked. Displays tiles that can be used for attack. The same function as showMove, changed slightly.
                                                              //Occupied tiles showed in contrast to moveSHow where not occupied tiles showed.
    void attack(EntityManager& manager, Entity& entity);      //Attack start.
private:
    void unitPromotion(Entity& attacker, Entity& defender);   //Unit promoted if wins. Used in attack function.
    void combatResult(Entity& player1, Entity& player2);      //Results of the combat.
public:
    void combatWindowClose();                                 //Closing combat window.

    void draw(sf::RenderWindow& window);

//Constructor/Destructor
public:
    MCombat();
    virtual ~MCombat();

};

#endif // MCOMBAT_H
