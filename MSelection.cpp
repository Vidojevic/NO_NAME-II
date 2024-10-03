#include "MSelection.h"

MSelection::MSelection(EntityManager& entityMng)
{
    int index = 19;
    //initializing Base action menu for Green player (Build Unit, EndTurn, Infantry, Artilery, Tank build options)
    for(unsigned i=0; i < 5; ++i)
    {
        baseActionMenu.push_back(sf::Sprite());
        baseActionMenu.back().setTexture(*entityMng.textureVec[index]);
        baseActionMenu.back().setOrigin(70,23);
        index = index + 1;
    }

    //initializing Unit action menu sprites
    moveIcon.setTexture(*entityMng.textureVec[14]);
    moveIcon.setOrigin(moveIcon.getGlobalBounds().width / 2, moveIcon.getGlobalBounds().height / 2);
    attackIcon.setTexture(*entityMng.textureVec[15]);
    attackIcon.setOrigin(moveIcon.getGlobalBounds().width / 2, moveIcon.getGlobalBounds().height / 2);
    fortifyIcon.setTexture(*entityMng.textureVec[32]); //changed to repair icon sprite
    fortifyIcon.setOrigin(moveIcon.getGlobalBounds().width / 2, moveIcon.getGlobalBounds().height / 2);

    //initializing info window (sprite)
    infoWndw.setTexture(*entityMng.textureVec[18]);
    infoWndw.setOrigin(infoWndw.getGlobalBounds().width / 2, infoWndw.getGlobalBounds().height / 2);

    //initializing rank sprites
    rank1.setTexture(*entityMng.textureVec[24]);
    rank2.setTexture(*entityMng.textureVec[25]);
    rank3.setTexture(*entityMng.textureVec[26]);
    rank4.setTexture(*entityMng.textureVec[27]);

    //initializing font and text
    font.loadFromFile("assets/font1.ttf");

    text1.setFont(font);
    text1.setFillColor(sf::Color::Green);
    text1.setCharacterSize(13);

    text2.setFont(font);
    text2.setFillColor(sf::Color::Green);
    text2.setCharacterSize(13);

    text3.setFont(font);
    text3.setFillColor(sf::Color::Green);
    text3.setCharacterSize(13);

    text4.setFont(font);
    text4.setFillColor(sf::Color::Green);
    text4.setCharacterSize(13);

    text5.setFont(font);
    text5.setFillColor(sf::Color::Green);
    text5.setCharacterSize(13);

    text6.setFont(font);
    text6.setFillColor(sf::Color::Green);
    text6.setCharacterSize(13);

    text7.setFont(font);
    text7.setFillColor(sf::Color::Green);
    text7.setCharacterSize(13);

    text8.setFont(font);
    text8.setFillColor(sf::Color::Green);
    text8.setCharacterSize(13);
}

MSelection::~MSelection()
{
}

///Action menu
void MSelection::actionMenu(EntityManager& entityManager, sf::Sound& unitSelection, sf::Sound& baseSelection)
{
//military units
    for(Entity& i: entityManager.militaryUnits)
    {
        if(i.isActive && !i.destroyed)
        {
            sf::Vector2f mousePos(sf::Mouse::getPosition());

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && i.ptrCMilitaryUnit->spriteMilitaryUnit.getGlobalBounds().contains(mousePos) && selectionActive)  //Only for the player that has the turn, only his units are active.
            {
                //sound
                unitSelection.play();
                actionMenuDisplayed     = true;
                deselectBaseActionMenyDisplayed();  //closing base action menu and repositioning button sprites outside the map. Bug, read header file.
                selectedUnitID = i.getID();         //Storing the selected unit ID.

                attackIcon.setPosition(i.ptrCTransform->position.x, i.ptrCTransform->position.y - 40);
                moveIcon.setPosition(i.ptrCTransform->position.x - 28, i.ptrCTransform->position.y - 40);
                fortifyIcon.setPosition(i.ptrCTransform->position.x + 28, i.ptrCTransform->position.y - 40);

                break;       //Breaks the loop because unit is selected. No need for more iterations.
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !(i.ptrCMilitaryUnit->spriteMilitaryUnit.getGlobalBounds().contains(mousePos)))
            {
                actionMenuDisplayed = false;
            }
        }
    }
//non-walkable tiles
    for(Entity& i: entityManager.tilesNonWalkable)
    {
        sf::Vector2f mousePos(sf::Mouse::getPosition());
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && i.ptrCTile->spriteTile.getGlobalBounds().contains(mousePos) && selectionActive)
        {
            //if base selected, show action menu (Build Units and End turn)
            if(i.tag == "baseGreen" && entityManager.player1.ptrCplayer->isPlaying)
            {
                //sound
                baseSelection.play();
                baseActionMenuDisplayed = true;

                baseActionMenu[0].setPosition(i.ptrCTransform->position.x + 10, i.ptrCTransform->position.y + 130);
                baseActionMenu[1].setPosition(i.ptrCTransform->position.x + 10, i.ptrCTransform->position.y + 80);

                break;

            }
            else if(i.tag == "baseYellow" && entityManager.player2.ptrCplayer->isPlaying)
            {
                //sound
                baseSelection.play();
                baseActionMenuDisplayed = true;

                baseActionMenu[0].setPosition(i.ptrCTransform->position.x - 10, i.ptrCTransform->position.y - 80);
                baseActionMenu[1].setPosition(i.ptrCTransform->position.x - 10, i.ptrCTransform->position.y - 130);

                break;

            }
        }

    }
              /*  else if(i.tag == "volcano2")
                    std::cout << "Volcano2.\n";
                if(i.tag == "goldMine")
                    std::cout << "Gold Mine.\n";
                else if(i.tag == "ironMine")
                    std::cout << "Iron Mine.\n";
                if(i.tag == "mountain")
                    std::cout << "Mountain.\n";
                else if(i.tag == "unknown")
                    std::cout << "Unknown.\n";
                if(i.tag == "baseGreen")
                    std::cout << "Base Green.\n";
                else if(i.tag == "baseYellow")
                    std::cout << "Base Yellow.\n";*/
}




///Info window
void MSelection::infoWindow(EntityManager& entityManager)
{
//Military Units
    for(Entity& i: entityManager.militaryUnits)
    {
        sf::Vector2f mousePos1(sf::Mouse::getPosition());
        if(!i.destroyed)
        {
            if(i.ptrCMilitaryUnit->spriteMilitaryUnit.getGlobalBounds().contains(mousePos1) && !(actionMenuDisplayed) && !(baseActionMenuDisplayed) && !(baseActionMenuBuild))
            {
                infoBaseWindowDisplayed = false;
                infoWindowDisplayed     = true;

                //Showing info window on the right side of military unit.
                if(i.ptrCTransform->position.x < 1720)
                {
                    infoWndw.setPosition(i.ptrCTransform->position.x + 120, i.ptrCTransform->position.y);  //Positioning the info window relative to military unit.

                //positioning text inside info window (information about the unit)
                    std::string line;
                    line = "Unit Health:   " + std::to_string(i.ptrCMilitaryUnit->health);
                    text1.setString(line);
                    text1.setPosition(i.ptrCTransform->position.x + 55, i.ptrCTransform->position.y -70);
                    line = "Movement Range:  " + std::to_string(i.ptrCMilitaryUnit->movementRange);
                    text2.setString(line);
                    text2.setPosition(i.ptrCTransform->position.x + 55, i.ptrCTransform->position.y -40);
                    line = "Shooting Range:   " + std::to_string(i.ptrCMilitaryUnit->shootingRange);
                    text3.setString(line);
                    text3.setPosition(i.ptrCTransform->position.x + 55, i.ptrCTransform->position.y -20);
                    line = "Defense: ";
                    text4.setString(line);
                    text4.setPosition(i.ptrCTransform->position.x + 55, i.ptrCTransform->position.y -0);
                    line = "\nRank: ";
                    text5.setString(line);
                    text5.setPosition(i.ptrCTransform->position.x + 55, i.ptrCTransform->position.y +20);
                //positioning rank sprite
                    if(i.ptrCSpecial->rankLevel == 1)
                    {
                        rank1Active = true;
                        rank1.setPosition(i.ptrCTransform->position.x + 100, i.ptrCTransform->position.y + 30);
                    }
                    else if(i.ptrCSpecial->rankLevel == 2)
                    {
                        rank2Active = true;
                        rank2.setPosition(i.ptrCTransform->position.x + 100, i.ptrCTransform->position.y + 30);
                    }
                    else if(i.ptrCSpecial->rankLevel == 3)
                    {
                        rank3Active = true;
                        rank3.setPosition(i.ptrCTransform->position.x + 100, i.ptrCTransform->position.y + 30);
                    }
                    else if(i.ptrCSpecial->rankLevel == 4)
                    {
                        rank4Active = true;
                        rank4.setPosition(i.ptrCTransform->position.x + 100, i.ptrCTransform->position.y + 30);
                    }

                }
                //Showing info window on the left side of military unit
                else
                {
                    infoWndw.setPosition(i.ptrCTransform->position.x - 120, i.ptrCTransform->position.y);

                    //positioning text inside info window (information about the unit)
                    std::string line;
                    line = "Unit Health:   " + std::to_string(i.ptrCMilitaryUnit->health);
                    text1.setString(line);
                    text1.setPosition(i.ptrCTransform->position.x -185, i.ptrCTransform->position.y -70);
                    line = "Movement Range:  " + std::to_string(i.ptrCMilitaryUnit->movementRange);
                    text2.setString(line);
                    text2.setPosition(i.ptrCTransform->position.x -185, i.ptrCTransform->position.y -40);
                    line = "Shooting Range:   " + std::to_string(i.ptrCMilitaryUnit->shootingRange);
                    text3.setString(line);
                    text3.setPosition(i.ptrCTransform->position.x -185, i.ptrCTransform->position.y -20);
                    line = "Defense: ";
                    text4.setString(line);
                    text4.setPosition(i.ptrCTransform->position.x -185, i.ptrCTransform->position.y -0);
                    line = "\nRank: ";
                    text5.setString(line);
                    text5.setPosition(i.ptrCTransform->position.x -185, i.ptrCTransform->position.y +20);

                    if(i.ptrCSpecial->rankLevel == 1)
                    {
                        rank1Active = true;
                        rank1.setPosition(i.ptrCTransform->position.x - 140, i.ptrCTransform->position.y + 30);
                    }
                    else if(i.ptrCSpecial->rankLevel == 2)
                    {
                        rank2Active = true;
                        rank2.setPosition(i.ptrCTransform->position.x - 140, i.ptrCTransform->position.y + 30);
                    }
                    else if(i.ptrCSpecial->rankLevel == 3)
                    {
                        rank3Active = true;
                        rank3.setPosition(i.ptrCTransform->position.x - 140, i.ptrCTransform->position.y + 30);
                    }
                    else if(i.ptrCSpecial->rankLevel == 4)
                    {
                        rank4Active = true;
                        rank4.setPosition(i.ptrCTransform->position.x - 140, i.ptrCTransform->position.y + 30);
                    }

                }

                break;
            }
            else
            {
                if(infoWindowDisplayed)
                {
                    infoWindowDisplayed = false;
                    rank1Active         = false;
                    rank2Active         = false;
                    rank3Active         = false;
                    rank4Active         = false;
                }
            }
        }
    }
//Non Walkable tiles - Bases and mines Info
    for(Entity& j: entityManager.tilesNonWalkable)
    {
        sf::Vector2f mousePos2(sf::Mouse::getPosition());
        if(j.ptrCTile->spriteTile.getGlobalBounds().contains(mousePos2) && !(actionMenuDisplayed) && !(baseActionMenuDisplayed) && !(baseActionMenuBuild))
        {
            if(j.ptrCTile->baseActive && j.tag == "baseGreen")
            {
                infoWindowDisplayed     = false;
                infoBaseWindowDisplayed = true;
                infoWndw.setPosition(j.ptrCTransform->position.x + 120, j.ptrCTransform->position.y);  //Positioning the info window relative to base position.

                    //positioning text inside info window (information about the green base)
                    std::string line;
                    line = "Iron Total:   " + std::to_string(entityManager.player1.ptrCplayer->ironTotal);
                    text6.setString(line);
                    text6.setScale(1,1);
                    text6.setPosition(j.ptrCTransform->position.x + 55, j.ptrCTransform->position.y -45);
                    line = "Gold Total:  " + std::to_string(entityManager.player1.ptrCplayer->goldTotal);
                    text7.setString(line);
                    text7.setPosition(j.ptrCTransform->position.x + 55, j.ptrCTransform->position.y -15);
                    line = "Units Total:   " + std::to_string(entityManager.player1.ptrCplayer->unitsTotal);
                    text8.setString(line);
                    text8.setPosition(j.ptrCTransform->position.x + 55, j.ptrCTransform->position.y + 15);

            }
            else if(j.ptrCTile->baseActive && j.tag == "baseYellow")
            {
                infoWindowDisplayed     = false;
                infoBaseWindowDisplayed = true;
                infoWndw.setPosition(j.ptrCTransform->position.x - 120, j.ptrCTransform->position.y);  //Positioning the info window relative to base position.

                    //positioning text inside info window (information about the green base)
                    std::string line;
                    line = "Iron Total:   " + std::to_string(entityManager.player2.ptrCplayer->ironTotal);
                    text6.setString(line);
                    text6.setScale(1,1);
                    text6.setPosition(j.ptrCTransform->position.x - 185, j.ptrCTransform->position.y -35);
                    line = "Gold Total:  " + std::to_string(entityManager.player2.ptrCplayer->goldTotal);
                    text7.setString(line);
                    text7.setPosition(j.ptrCTransform->position.x - 185, j.ptrCTransform->position.y -5);
                    line = "Units Total:   " + std::to_string(entityManager.player2.ptrCplayer->unitsTotal);
                    text8.setString(line);
                    text8.setPosition(j.ptrCTransform->position.x - 185, j.ptrCTransform->position.y +25);

            }
            else if(j.tag == "ironMine")
            {
                //positioning text inside info window (information about the green base)else if(j.tag == "ironMine1")
                infoWindowDisplayed     = false;
                infoBaseWindowDisplayed = true;
                infoWndw.setPosition(j.ptrCTransform->position.x + 120, j.ptrCTransform->position.y);  //Positioning the info window.

                //positioning text inside info window (information about the green base)
                std::string line;
                line = "Iron Mine";
                text6.setString(line);
                text6.setScale(1.2,1.2);
                text6.setPosition(j.ptrCTransform->position.x + 84, j.ptrCTransform->position.y -75);
                line = "Income: 20 per turn";
                text7.setString(line);
                text7.setPosition(j.ptrCTransform->position.x + 55, j.ptrCTransform->position.y -25);
                line = "Owned:  ";
                text8.setString(line);
                text8.setPosition(j.ptrCTransform->position.x + 55, j.ptrCTransform->position.y + 15);
                //owned by player
                if(j.ptrCTile->mineOwnedByPlayer1)
                {
                    ironMineOwnerColorDisplay = true;
                    ironMineOwnerColor.setSize(sf::Vector2f(30,20));
                    ironMineOwnerColor.setFillColor(sf::Color::Green);
                    ironMineOwnerColor.setPosition(j.ptrCTransform->position.x + 120, j.ptrCTransform->position.y + 10);
                }
                else if(j.ptrCTile->mineOwnedByPlayer2)
                {
                    ironMineOwnerColorDisplay = true;
                    ironMineOwnerColor.setSize(sf::Vector2f(30,20));
                    ironMineOwnerColor.setFillColor(sf::Color::Red);
                    ironMineOwnerColor.setPosition(j.ptrCTransform->position.x + 120, j.ptrCTransform->position.y + 10);
                }
            }
            else if(j.tag == "goldMine")
            {
                infoWindowDisplayed     = false;
                infoBaseWindowDisplayed = true;
                infoWndw.setPosition(j.ptrCTransform->position.x + 120, j.ptrCTransform->position.y);  //Positioning the info window.

                //positioning text inside info window (information about the green base)
                std::string line;
                line = "Gold Mine";
                text6.setString(line);
                text6.setScale(1.2,1.2);
                text6.setPosition(j.ptrCTransform->position.x + 83, j.ptrCTransform->position.y -75);
                line = "Income: 15 per turn";
                text7.setString(line);
                text7.setPosition(j.ptrCTransform->position.x + 55, j.ptrCTransform->position.y -25);
                line = "Owned:  ";
                text8.setString(line);
                text8.setPosition(j.ptrCTransform->position.x + 55, j.ptrCTransform->position.y + 15);
                //owned by player
                if(entityManager.player1.ptrCResources->goldMine)
                {
                    goldMineOwnerColorDisplay = true;
                    goldMineOwnerColor.setSize(sf::Vector2f(30,20));
                    goldMineOwnerColor.setFillColor(sf::Color::Green);
                    goldMineOwnerColor.setPosition(j.ptrCTransform->position.x + 120, j.ptrCTransform->position.y + 10);
                }
                else if(entityManager.player2.ptrCResources->goldMine)
                {
                    goldMineOwnerColorDisplay = true;
                    goldMineOwnerColor.setSize(sf::Vector2f(30,20));
                    goldMineOwnerColor.setFillColor(sf::Color::Red);
                    goldMineOwnerColor.setPosition(j.ptrCTransform->position.x + 120, j.ptrCTransform->position.y + 10);
                }
            }
            break;
        }
        else if(infoBaseWindowDisplayed)
        {
            infoBaseWindowDisplayed   = false;
            ironMineOwnerColorDisplay = false;
            goldMineOwnerColorDisplay = false;
        }
    }
}


///Deselecting baseActionMenuDisplayed - Read function desription in header file to see why this function is neceseary
void MSelection::deselectBaseActionMenyDisplayed()
{
    baseActionMenuDisplayed = false;
    baseActionMenuBuild     = false;

    for(sf::Sprite& i: baseActionMenu)
    {
        i.setPosition(0,0);
    }
}


///Deselecting unit action menu - Read function desription in header file to see why this function is neceseary
void MSelection::deselectActionMenuDisplayed()
{
    actionMenuDisplayed = false;

    attackIcon.setPosition(0,0);
    moveIcon.setPosition(0,0);
    fortifyIcon.setPosition(0,0);

}



///draw
void MSelection::draw(sf::RenderWindow& renderWndw)
{
    //unit action buttons
    if(actionMenuDisplayed)
    {
        renderWndw.draw(moveIcon);
        renderWndw.draw(attackIcon);
        renderWndw.draw(fortifyIcon);
    }
    //unit info window
    if(infoWindowDisplayed)
    {
        renderWndw.draw(infoWndw);
        renderWndw.draw(text1);
        renderWndw.draw(text2);
        renderWndw.draw(text3);
        renderWndw.draw(text4);
        renderWndw.draw(text5);
        if(rank1Active)
            renderWndw.draw(rank1);
        else if(rank2Active)
            renderWndw.draw(rank2);
        else if(rank3Active)
            renderWndw.draw(rank3);
        else if(rank4Active)
            renderWndw.draw(rank4);
    }
    //info: base
    if(infoBaseWindowDisplayed)
    {
        renderWndw.draw(infoWndw);
        renderWndw.draw(text6);
        renderWndw.draw(text7);
        renderWndw.draw(text8);
    }
    //info: mine owner color
    if(ironMineOwnerColorDisplay)
    {
        renderWndw.draw(ironMineOwnerColor);
    }
    if(goldMineOwnerColorDisplay)
    {
        renderWndw.draw(goldMineOwnerColor);
    }
    //base menu
    if(baseActionMenuDisplayed)
    {
        renderWndw.draw(baseActionMenu[0]);
        renderWndw.draw(baseActionMenu[1]);
    }
    if(baseActionMenuBuild)
    {
        renderWndw.draw(baseActionMenu[2]);
        renderWndw.draw(baseActionMenu[3]);
        renderWndw.draw(baseActionMenu[4]);
    }
}




