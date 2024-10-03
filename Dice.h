#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef DICE_H
#define DICE_H


class Dice
{
private:
    std::vector<sf::Texture*> diceTexture;        //dice texture vector.

public:
    std::vector<sf::Sprite> whiteDiceVec;        //6 face of white dice.
    std::vector<sf::Sprite> redDiceVec;          //6 face of red dice.

//Functions



//Constructor-Destructor
public:
    Dice();
    virtual ~Dice();
};

#endif // DICE_H
