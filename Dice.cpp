#include "Dice.h"

Dice::Dice()
{
    //REGULAR dice texture vector initialization
    for (unsigned i=0; i < 12; ++i)
    {
        std::string fileName = ("assets/dice" + std::to_string(i) + ".png");    // Converting number into string. Svi sprajtovi u folder "assets" nose isto ime,
                                                                                // pocinju sa "tile" i samo se dodaje broj na kraj zbog lakseg ucitavanje iz fajla.
        diceTexture.push_back(new sf::Texture);

        diceTexture[i]->loadFromFile(fileName);
    }
    //white dice vector initialization
    for (unsigned i=0; i < 6; ++i)
    {
        redDiceVec.push_back(sf::Sprite());
        redDiceVec.back().setTexture(*diceTexture[i]);
        redDiceVec.back().setOrigin(35,35);

    }
    //red dice vector initialization
    for (unsigned i=6; i < 12; ++i)
    {
        whiteDiceVec.push_back(sf::Sprite());
        whiteDiceVec.back().setTexture(*diceTexture[i]);
        whiteDiceVec.back().setOrigin(35,35);
    }
}

Dice::~Dice()
{
}




