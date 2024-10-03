#include "MCombat.h"

MCombat::MCombat()
{
    //combat window textures initialization
    for (unsigned i=0; i < 7; ++i)
    {
        std::string fileName = ("assets/combatWindow" + std::to_string(i) + ".png");    // Converting number into string. Svi sprajtovi u folder "assets" nose isto ime,
                                                                                        // pocinju sa "tile" i samo se dodaje broj na kraj zbog lakseg ucitavanje iz fajla.
        combatWindowTextVec.push_back(new sf::Texture);

        combatWindowTextVec[i]->loadFromFile(fileName);
    }
    //combat window sprites initialization
    for (unsigned i=0; i < 7; ++i)
    {
        combatWindowVec.push_back(sf::Sprite());
        combatWindowVec.back().setTexture(*combatWindowTextVec[i]);
    }
    combatWindowVec[0].setOrigin(300,195);
    combatWindowVec[0].setPosition(958,450);
    combatWindowVec[1].setOrigin(100,32);
    combatWindowVec[1].setPosition(589,380);
    combatWindowVec[2].setOrigin(100,32);
    combatWindowVec[2].setPosition(589,537);
    combatWindowVec[3].setOrigin(125,58);
    combatWindowVec[3].setPosition(1100,390);
    combatWindowVec[4].setOrigin(125,58);
    combatWindowVec[4].setPosition(1100,550);
    combatWindowVec[5].setOrigin(100,32);
    combatWindowVec[5].setPosition(1325,380);
    combatWindowVec[6].setOrigin(75,22);      //promotion window sprite

    //font and text
    font.loadFromFile("assets/font1.ttf");
    win.setFont(font);
    win.setFillColor(sf::Color::Green);
    win.setCharacterSize(40);
   // win.setPosition(552,355);
    loose.setFont(font);
    loose.setFillColor(sf::Color::Green);
    loose.setCharacterSize(40);
    //loose.setPosition(545,512);
    stalemate1.setFont(font);
    stalemate1.setFillColor(sf::Color::Green);
    stalemate1.setCharacterSize(30);
    //stalemate1.setPosition(500,500);
    stalemate2.setFont(font);
    stalemate2.setFillColor(sf::Color::Green);
    stalemate2.setCharacterSize(30);
    //stalemate2.setPosition(500,500);
    exitCombatWindow.setFont(font);
    exitCombatWindow.setFillColor(sf::Color::Green);
    exitCombatWindow.setCharacterSize(35);
    exitCombatWindow.setPosition(1292, 358);
    exitCombatWindow.setString("EXIT");
}

MCombat::~MCombat()
{
}


///White dice throw - 1 dice throw
int MCombat::whiteDiceThrow()
{
    //srand(time(0));          //srand NE MOZE ovde jer uvek kad se pozove ova funcja vreme se resetuje na nula, pa rezultati budu identicni. srand je stavljen u throwingDice funkciju jednom.
    int index = 0;
    int diceArray[6] = {0,1,2,3,4,5};   //index for 6 faces.
    int randNumber   = rand() % 6;

    index = diceArray[randNumber];

    return index;
}


///Red dice throw - 1 dice throw
int MCombat::redDiceThrow()
{
    //srand(time(0));      //srand NE MOZE ovde jer uvek kad se pozove ova funcja vreme se resetuje na nula, pa rezultati budu identicni. srand je stavljen u throwingDice funkciju jednom.
    int index = 0;
    int diceArray[6] = {1,2,3,2,4,5}; //indexes for 6 dice faces without 1. The red dices have two 3, no 1. This values are indexes of vector, not dice numbers.
    int randNumber   = rand() % 6;

    return index = diceArray[randNumber];;
}


///Throwing dice
void MCombat::throwingDices(Entity& player)
{
//dice throw by unit type and its rank for player 1
    //rank1 - 3 whites
    if(player1ThrowedDice.empty())
    {
        if(player.ptrCSpecial->whiteDice1 && player.ptrCSpecial->whiteDice2 && player.ptrCSpecial->whiteDice3)
        {
            for(unsigned i=0; i < 3; ++i)
            {
                int index = whiteDiceThrow();
                player1ThrowedDice.push_back(player1Dice.whiteDiceVec[index]);  //copiying into vector for raw unsorted diplay in combat window.
                player1SortedDice.push_back(player1Dice.whiteDiceVec[index]);   //copying into vector wich will be bubble sorted for sorted dice combat window.
                player1BubbleSort[i] = index;                                   //storing index of the dice as number, then bubble sort the numbers.
            }
            return;
        }
        //rank2 - 1 red, 2 whites
        if(!player.ptrCSpecial->whiteDice1 && player.ptrCSpecial->whiteDice2 && player.ptrCSpecial->whiteDice3)
        {
            int x = 0;
            int index1 = redDiceThrow();
            int index2 = whiteDiceThrow();
            int index3 = whiteDiceThrow();
            player1ThrowedDice.push_back(player1Dice.redDiceVec[index1]);
            player1SortedDice.push_back(player1Dice.redDiceVec[index1]);
            player1BubbleSort[x] = index1;
            player1ThrowedDice.push_back(player1Dice.whiteDiceVec[index2]);
            player1SortedDice.push_back(player1Dice.whiteDiceVec[index2]);
            player1BubbleSort[x+1] = index2;
            player1ThrowedDice.push_back(player1Dice.whiteDiceVec[index3]);
            player1SortedDice.push_back(player1Dice.whiteDiceVec[index3]);
            player1BubbleSort[x+2] = index3;

            return;
        }
        //rank 3 - 2 red, 1 white
        if(!player.ptrCSpecial->whiteDice1 && !player.ptrCSpecial->whiteDice2 && player.ptrCSpecial->whiteDice3)
        {
            int x = 0;
            int index1 = redDiceThrow();
            int index2 = redDiceThrow();
            int index3 = whiteDiceThrow();
            player1ThrowedDice.push_back(player1Dice.redDiceVec[index1]);
            player1SortedDice.push_back(player1Dice.redDiceVec[index1]);
            player1BubbleSort[x] = index1;
            player1ThrowedDice.push_back(player1Dice.redDiceVec[index2]);
            player1SortedDice.push_back(player1Dice.redDiceVec[index2]);
            player1BubbleSort[x+1] = index2;
            player1ThrowedDice.push_back(player1Dice.whiteDiceVec[index3]);
            player1SortedDice.push_back(player1Dice.whiteDiceVec[index3]);
            player1BubbleSort[x+2] = index3;

            return;
        }
        //rank 4 - 3 red
        if(!player.ptrCSpecial->whiteDice1 && !player.ptrCSpecial->whiteDice2 && !player.ptrCSpecial->whiteDice3)
        {
            int x = 0;
            int index1 = redDiceThrow();
            int index2 = redDiceThrow();
            int index3 = redDiceThrow();
            player1ThrowedDice.push_back(player1Dice.redDiceVec[index1]);
            player1SortedDice.push_back(player1Dice.redDiceVec[index1]);
            player1BubbleSort[x] = index1;
            player1ThrowedDice.push_back(player1Dice.redDiceVec[index2]);
            player1SortedDice.push_back(player1Dice.redDiceVec[index2]);
            player1BubbleSort[x+1] = index2;
            player1ThrowedDice.push_back(player1Dice.redDiceVec[index3]);
            player1SortedDice.push_back(player1Dice.redDiceVec[index3]);
            player1BubbleSort[x+2] = index3;

            return;
        }
    }
//dice throw by unit type and its rank for player 2
    else
    {
        if(player.ptrCSpecial->whiteDice1 && player.ptrCSpecial->whiteDice2 && player.ptrCSpecial->whiteDice3)
        {
            for(unsigned i=0; i < 3; ++i)
            {
            int index = whiteDiceThrow();
            player2ThrowedDice.push_back(player2Dice.whiteDiceVec[index]);
            player2SortedDice.push_back(player2Dice.whiteDiceVec[index]);
            player2BubbleSort[i] = index;
            }
            return;
        }
        if(!player.ptrCSpecial->whiteDice1 && player.ptrCSpecial->whiteDice2 && player.ptrCSpecial->whiteDice3)
        {
            int x = 0;
            int index1 = redDiceThrow();
            int index2 = whiteDiceThrow();
            int index3 = whiteDiceThrow();
            player2ThrowedDice.push_back(player2Dice.redDiceVec[index1]);
            player2SortedDice.push_back(player2Dice.redDiceVec[index1]);
            player2BubbleSort[x] = index1;
            player2ThrowedDice.push_back(player2Dice.whiteDiceVec[index2]);
            player2SortedDice.push_back(player2Dice.whiteDiceVec[index2]);
            player2BubbleSort[x+1] = index2;
            player2ThrowedDice.push_back(player2Dice.whiteDiceVec[index3]);
            player2SortedDice.push_back(player2Dice.whiteDiceVec[index3]);
            player2BubbleSort[x+2] = index3;

            return;
        }
        if(!player.ptrCSpecial->whiteDice1 && !player.ptrCSpecial->whiteDice2 && player.ptrCSpecial->whiteDice3)
        {
            int x = 0;
            int index1 = redDiceThrow();
            int index2 = redDiceThrow();
            int index3 = whiteDiceThrow();
            player2ThrowedDice.push_back(player2Dice.redDiceVec[index1]);
            player2SortedDice.push_back(player2Dice.redDiceVec[index1]);
            player2BubbleSort[x] = index1;
            player2ThrowedDice.push_back(player2Dice.redDiceVec[index2]);
            player2SortedDice.push_back(player2Dice.redDiceVec[index2]);
            player2BubbleSort[x+1] = index2;
            player2ThrowedDice.push_back(player2Dice.whiteDiceVec[index3]);
            player2SortedDice.push_back(player2Dice.whiteDiceVec[index3]);
            player2BubbleSort[x+2] = index3;

            return;
        }
        if(!player.ptrCSpecial->whiteDice1 && !player.ptrCSpecial->whiteDice2 && !player.ptrCSpecial->whiteDice3)
        {
            int x = 0;
            int index1 = redDiceThrow();
            int index2 = redDiceThrow();
            int index3 = redDiceThrow();
            player2ThrowedDice.push_back(player2Dice.redDiceVec[index1]);
            player2SortedDice.push_back(player2Dice.redDiceVec[index1]);
            player2BubbleSort[x] = index1;
            player2ThrowedDice.push_back(player2Dice.redDiceVec[index2]);
            player2SortedDice.push_back(player2Dice.redDiceVec[index2]);
            player2BubbleSort[x+1] = index2;
            player2ThrowedDice.push_back(player2Dice.redDiceVec[index3]);
            player2SortedDice.push_back(player2Dice.redDiceVec[index3]);
            player2BubbleSort[x+2] = index3;

            return;
        }
    }
}


///Bubble Sort dice throw - sorting dice throw by numbers
void MCombat::bubbleSort()
{
    //bubble sort player 1 throw
    int* p1 = player1BubbleSort;
    int* p2 = player1BubbleSort;

    //bubble sort player 1 throw
    for (int i = 0; i < 2; ++i)
    {
        for(int y=i+1; y < 3; ++y)
        {
            if(p1[i] > p2[y])
            {
                std::swap(p1[i], p2[y]);
                std::swap(player1SortedDice[i], player1SortedDice[y]);
            }
        }
    }
    //bubble sort player 2 throw
    int* p3 = player2BubbleSort;
    int* p4 = player2BubbleSort;

    for (int i = 0; i < 2; ++i)
    {
        for(int y=i+1; y < 3; ++y)
        {
            if(p3[i] > p4[y])
            {
                std::swap(p3[i], p4[y]);
                std::swap(player2SortedDice[i], player2SortedDice[y]);
            }
        }
    }
}


///Attack Show  -- Displays tiles that can be attacked, if the enemy units are in range. Same as moveSHow, slightly changed. See MCombat.h
void MCombat::attackShow(EntityManager& manager, Entity& entity)
{
    attackActive =  true;

    rectVec.clear();    //clearing previous elements

    for(unsigned i=0; i < entity.ptrCMilitaryUnit->shootingRange; ++i)
    {
        //horizontal, vertical tiles
        bool tileXPlusOccupied  = false;
        bool tileXMinusOccupied = false;
        bool tileYPlusOccupied  = false;
        bool tileYMinusOccupied = false;
        //angle tiles
        bool tileXPlusYMinusOccupied  = false;
        bool tileXPlusYPlusOccupied   = false;
        bool tileXMinusYMinusOccupied = false;
        bool tileXMinusYPlusOccupied  = false;

        sf::RectangleShape rectProbe;           //rectagle that tests if the tile is occupied by enemy unit.
        rectProbe.setSize(sf::Vector2f(80,80));
        rectProbe.setOrigin(45,45);
        rectProbe.setFillColor(sf::Color::Transparent);
        rectProbe.setOutlineColor(sf::Color::Red);
        rectProbe.setOutlineThickness(5);

        float a = 105 + (i*100);
        float b = 105 + (i*100);

        //test for military units if they are an obsticle on the path, if no- draw rectangle
        for(Entity& y: manager.militaryUnits)
        {
            //x+ axis test
            rectProbe.setPosition(entity.ptrCTransform->position.x + a,  entity.ptrCTransform->position.y + 5);
            if(rectProbe.getPosition().x > 1900)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXPlusOccupied = false;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXPlusOccupied == false && !y.isActive && !y.destroyed)
            {
                tileXPlusOccupied = true;
                continue;
            }
            //x- axis test
            rectProbe.setPosition(entity.ptrCTransform->position.x - a,  entity.ptrCTransform->position.y - 5);
            if(rectProbe.getPosition().x < 30)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXMinusOccupied = false;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXMinusOccupied == false && !y.isActive && !y.destroyed)
            {
                tileXMinusOccupied = true;
                continue;
            }
            //y+ axis test
            rectProbe.setPosition(entity.ptrCTransform->position.x + 5,  entity.ptrCTransform->position.y + b);
            if(rectProbe.getPosition().y > 1020)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileYPlusOccupied = false;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileYPlusOccupied == false && !y.isActive && !y.destroyed)
            {
                tileYPlusOccupied = true;
                continue;
            }
            //y- axis test
            rectProbe.setPosition(entity.ptrCTransform->position.x - 5,  entity.ptrCTransform->position.y - b);
            if(rectProbe.getPosition().y < 50)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileYMinusOccupied = false;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileYMinusOccupied == false && !y.isActive && !y.destroyed)
            {
                tileYMinusOccupied = true;
                continue;
            }

            //angle axis x+,y-
            rectProbe.setPosition(entity.ptrCTransform->position.x + a,  entity.ptrCTransform->position.y - 105);
            if(rectProbe.getPosition().x > 1900 || rectProbe.getPosition().y < 50)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXPlusYMinusOccupied = false;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXPlusYMinusOccupied == false && !y.isActive && !y.destroyed)
            {
                tileXPlusYMinusOccupied = true;
                continue;
            }
            //angle axis x+,y+
            rectProbe.setPosition(entity.ptrCTransform->position.x + a,  entity.ptrCTransform->position.y + 105);
            if(rectProbe.getPosition().x > 1900 || rectProbe.getPosition().y > 1000)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXPlusYPlusOccupied = false;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXPlusYPlusOccupied == false && !y.isActive && !y.destroyed)
            {
                tileXPlusYPlusOccupied = true;
                continue;
            }
            //angle axis x-,y-
            rectProbe.setPosition(entity.ptrCTransform->position.x - a,  entity.ptrCTransform->position.y - 105);
            if(rectProbe.getPosition().x < 30 || rectProbe.getPosition().y < 50)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXMinusYMinusOccupied = false;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXMinusYMinusOccupied == false && !y.isActive && !y.destroyed)
            {
                tileXMinusYMinusOccupied = true;
                continue;
            }
            //angle axis x-,y+
            rectProbe.setPosition(entity.ptrCTransform->position.x - a,  entity.ptrCTransform->position.y + 105);
            if(rectProbe.getPosition().x < 30 || rectProbe.getPosition().y > 1000)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXMinusYPlusOccupied = false;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXMinusYPlusOccupied == false && !y.isActive && !y.destroyed)
            {
                tileXMinusYPlusOccupied = true;
                continue;
            }
        }

        //show possible unit path
        if(tileXPlusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Red);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + (a - 0.1),  entity.ptrCTransform->position.y + 5);
            }

        if(tileXMinusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Red);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x - (a-10),  entity.ptrCTransform->position.y + 5);
            }
        if(tileYPlusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Red);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + 5,  entity.ptrCTransform->position.y + b);
            }
        if(tileYMinusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Red);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + 5,  entity.ptrCTransform->position.y - (b-10));
            }
            if(tileXPlusYMinusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Red);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + (a - 0.1),  entity.ptrCTransform->position.y - 95);
            }
            if(tileXPlusYPlusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Red);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + (a - 0.1),  entity.ptrCTransform->position.y + 105);
            }
            if(tileXMinusYMinusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Red);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x - (a - 10),  entity.ptrCTransform->position.y - 95);
            }
            if(tileXMinusYPlusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Red);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x - (a - 10),  entity.ptrCTransform->position.y + 105);
            }
            else
            {
                continue;
            }
    }
}


///Attack -- this function is used in Game class to activate combat window
void MCombat::attack(EntityManager& manager, Entity& entity)
{
    Entity* entity2;

    for(sf::RectangleShape& i: rectVec)
    {
        sf::Vector2f mousePos(sf::Mouse::getPosition());
        if(i.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            for(unsigned j=0; j < manager.militaryUnits.size(); ++j)
            {
                if(i.getGlobalBounds().contains(manager.militaryUnits[j].ptrCTransform->position) && (!manager.militaryUnits[j].destroyed))  //if the rectangle contains enemy unit.
                {
                    entity2 = &manager.militaryUnits[j];  //getting the address of the ememy unit that is clicked on.
                }
            }

            combatWindowActive = true;
            combatResult(entity, *entity2);   //Combat window.
            unitPromotion(entity, *entity2);   //Unit promotion depending on the combat result.

            attackActive = false;
            entity.ptrCMilitaryUnit->unitAttacked  = true;
            entity.ptrCMilitaryUnit->attackPressed = false;

            break;
        }
    }
}


///Unit Promotion
void MCombat::unitPromotion(Entity& attacker, Entity& defender)
{
    //Attacker win
    if(attackerWin && (attacker.ptrCSpecial->rankLevel < 4))
    {
        if(attacker.ptrCSpecial->rankLevel == 1 && !(attacker.destroyed))
        {
            attacker.ptrCSpecial->rankLevel = attacker.ptrCSpecial->rankLevel + 1;
            attacker.ptrCSpecial->whiteDice1 = false;  //+1 red dice (total 1)
            //promotion window display
            promotionWindow = true;
            combatWindowVec[6].setPosition(combatWindowVec[1].getPosition().x - 25, combatWindowVec[1].getPosition().y -40);
        }
        else if(attacker.ptrCSpecial->rankLevel == 2 && !(attacker.destroyed))
        {
            attacker.ptrCSpecial->rankLevel = attacker.ptrCSpecial->rankLevel + 1;
            attacker.ptrCSpecial->whiteDice2 = false;  //+1 red dice (total 2)
            //promotion window display
            promotionWindow = true;
            combatWindowVec[6].setPosition(combatWindowVec[1].getPosition().x - 25, combatWindowVec[1].getPosition().y -40);
        }
        else if(attacker.ptrCSpecial->rankLevel == 3 && !(attacker.destroyed))
        {
            attacker.ptrCSpecial->rankLevel = attacker.ptrCSpecial->rankLevel + 1;
            attacker.ptrCSpecial->whiteDice3 = false;   //+1 red dice (total 3)
            //promotion window display
            promotionWindow = true;
            combatWindowVec[6].setPosition(combatWindowVec[1].getPosition().x - 25, combatWindowVec[1].getPosition().y -40);
        }
    }
    //Defender win
    else if(defenderWin && (defender.ptrCSpecial->rankLevel < 4))
    {
        if(defender.ptrCSpecial->rankLevel == 1 && !(defender.destroyed))
        {
            defender.ptrCSpecial->rankLevel = defender.ptrCSpecial->rankLevel + 1;
            defender.ptrCSpecial->whiteDice1 = false;   //+1 red dice (total 1)
            //promotion window display
            promotionWindow = true;
            combatWindowVec[6].setPosition(combatWindowVec[2].getPosition().x - 25, combatWindowVec[2].getPosition().y -40);
        }
        else if(defender.ptrCSpecial->rankLevel == 2 && !(defender.destroyed))
        {
            defender.ptrCSpecial->rankLevel = defender.ptrCSpecial->rankLevel + 1;
            defender.ptrCSpecial->whiteDice2 = false;   //+1 red dice (total 2)
            //promotion window display
            promotionWindow = true;
            combatWindowVec[6].setPosition(combatWindowVec[2].getPosition().x - 25, combatWindowVec[2].getPosition().y -40);
        }
        else if(defender.ptrCSpecial->rankLevel == 3 && !(defender.destroyed))
        {
            defender.ptrCSpecial->rankLevel = defender.ptrCSpecial->rankLevel + 1;
            defender.ptrCSpecial->whiteDice3 = false;   //+1 red dice (total 3)
            //promotion window display
            promotionWindow = true;
            combatWindowVec[6].setPosition(combatWindowVec[2].getPosition().x - 25, combatWindowVec[2].getPosition().y -40);
        }
    }
    else if(stalemateWin)
    {
        promotionWindow = false;
    }
}



///Combat result
void MCombat::combatResult(Entity& player1, Entity& player2)
{
    attackerWin  = false;
    defenderWin  = false;
    stalemateWin = false;

    player1ThrowedDice.clear();
    player2ThrowedDice.clear();
    player1SortedDice.clear();
    player2SortedDice.clear();

    throwingDices(player1);        //player 1 throwing dices.
    throwingDices(player2);        //player 2 throwing dices.
    bubbleSort();                  //sorting dice values.
    dicePositionCombatWindow();    //Sets the position of dices on combat window.

    int* p1 = player1BubbleSort;
    int* p2 = player2BubbleSort;

    int  player1Lose = 0;
    int  player2Lose = 0;
    int  stalemate   = 0;
//comparing dice values
    for(unsigned i=0; i < 3; ++i)
    {
        if(p1[i] > p2[i])
        {
            player2Lose = player2Lose + 1;
            continue;;
        }
        else if(p1[i] < p2[i])
        {
            player1Lose = player1Lose + 1;
            continue;
        }
        if(p1[i] == p2[i])
        {
            stalemate = stalemate + 1;
            continue;
        }
    }
//Health update according to result, artilery doesnt take damage when attacking
    if(player1.tag == "artileryGreen" || player1.tag == "artileryYellow")
    {
        player2.ptrCMilitaryUnit->health -= player2Lose;
    }
    else
    {
        player1.ptrCMilitaryUnit->health -= player1Lose;
        player2.ptrCMilitaryUnit->health -= player2Lose;
    }

//If player is destroyed + if no unit was destroyed(stalemate)
    if(player1.ptrCMilitaryUnit->health <= 0)
    {
        player1.destroyed = true;
    }
    if(player2.ptrCMilitaryUnit->health <= 0)
    {
        player2.destroyed = true;
    }

    win.setString("    ");      //clear the previous string
    loose.setString("    ");
    stalemate1.setString("    ");
    stalemate2.setString("    ");

    if(player1Lose < player2Lose)
    {
        attackerWin = true;
        win.setString("WIN");       //set new string
        win.setPosition(552,355);
        loose.setString("LOST");
        loose.setPosition(545,512);
    }
    else if(player1Lose > player2Lose)
    {
        defenderWin = true;
        loose.setString("LOST");
        loose.setPosition(545,354);
        win.setString("WIN");
        win.setPosition(552,512);
    }
    else if(player1Lose == player2Lose)
    {
        stalemateWin = true;
        stalemate1.setString("STALEMATE");
        stalemate1.setPosition(506,361);
        stalemate2.setString("STALEMATE");
        stalemate2.setPosition(506,518);
    }
}


///Dice position on Combat Window
void MCombat::dicePositionCombatWindow()
{
    //positioning throwed dice on combat window
    unsigned short int x = 780;
    unsigned short int y = 380;
    for(sf::Sprite& i: player1ThrowedDice)
    {
        i.setPosition(x,y);

        x = x + 75;
    }
    unsigned short int q = 780;
    unsigned short int z = 540;
    for(sf::Sprite& i: player2ThrowedDice)
    {
        i.setPosition(q,z);

        q = q + 75;
    }

    //positioning sorted dice on combat window
    unsigned short int a = 1022;
    unsigned short int b = 380;
    for(sf::Sprite& i: player1SortedDice)
    {
        i.setPosition(a,b);
        i.setScale(0.8,0.8);

        a = a + 60;
    }
    unsigned short int c = 1022;
    unsigned short int d = 540;
    for(sf::Sprite& i: player2SortedDice)
    {
        i.setPosition(c,d);
        i.setScale(0.8,0.8);

        c = c + 60;
    }
}


///Combat Window Close
void MCombat::combatWindowClose()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f mousePos(sf::Mouse::getPosition());
        if(combatWindowVec[5].getGlobalBounds().contains(mousePos))
        {
            combatWindowActive = false;
            promotionWindow    = false;
        }
    }
}


///Draw
void MCombat::draw(sf::RenderWindow& window)
{
    if(attackActive)                            //Attack tiles display.
    {
        for(sf::RectangleShape& i: rectVec)
        {
            window.draw(i);
        }
    }

    if(combatWindowActive)
    {
        for(sf::Sprite& i: combatWindowVec)      //Combat window display.
        {
            window.draw(i);
        }
        for(sf::Sprite& i: player1ThrowedDice)   //Player 1 throwed dice display.
        {
            window.draw(i);
        }
        for(sf::Sprite& i: player2ThrowedDice)   //Player 2 throwed dice display.
        {
            window.draw(i);
        }
        for(sf::Sprite& i: player1SortedDice)   //Player 1 sorted dice display.
        {
            window.draw(i);
        }
        for(sf::Sprite& i: player2SortedDice)   //Player 2 sorted dice display.
        {
            window.draw(i);
        }
        window.draw(win);                       //Text
        window.draw(loose);                     //
        window.draw(stalemate1);                //
        window.draw(stalemate2);                //
        window.draw(exitCombatWindow);          //
    }

    //promotion window
    if(promotionWindow)
    {
        window.draw(combatWindowVec[6]);
    }
}








