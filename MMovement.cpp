#include "MMovement.h"

MMovement::MMovement()
{
    rectVec.reserve(12);
}

MMovement::~MMovement()
{
}


///Move Show
void MMovement::moveShow(EntityManager& manager, Entity& entity)
{
    pathActive =  true;

    rectVec.clear();    //clearing previous elements

    for(unsigned i=0; i < entity.ptrCMilitaryUnit->movementRange; ++i)
    {
        //horizontal, vertical tiles test (units)
        bool tileXPlusOccupied  = false;
        bool tileXMinusOccupied = false;
        bool tileYPlusOccupied  = false;
        bool tileYMinusOccupied = false;

        //angle tile, units
        bool tileXPlusYMinusOccupied  = false;
        bool tileXPlusYPlusOccupied   = false;
        bool tileXMinusYMinusOccupied = false;
        bool tileXMinusYPlusOccupied  = false;

        sf::RectangleShape rectProbe;           //rectagle that tests if the tile is occupied by enemy unit.
        rectProbe.setSize(sf::Vector2f(80,80));
        rectProbe.setOrigin(45,45);
        rectProbe.setFillColor(sf::Color::Transparent);
        rectProbe.setOutlineColor(sf::Color::Green);
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
                tileXPlusOccupied = true;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXPlusOccupied == false && !y.destroyed)
            {
                tileXPlusOccupied = true;
                continue;
            }
            else if(tileXPlusOccupied == false)  //non-walkable tiles test
            {
                for(Entity& x: manager.tilesNonWalkable)
                {
                    if(rectProbe.getGlobalBounds().contains(x.ptrCTile->spriteTile.getPosition()) && !x.ptrCTile->isWalkable)
                       {
                           tileXPlusOccupied = true;
                           continue;
                       }
                }
            }
            //x- axis test
            rectProbe.setPosition(entity.ptrCTransform->position.x - a,  entity.ptrCTransform->position.y - 5);
            if(rectProbe.getPosition().x < 30)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXMinusOccupied = true;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXMinusOccupied == false && !y.destroyed)
            {
                tileXMinusOccupied = true;
                continue;
            }
            else if(tileXMinusOccupied == false)
            {
                for(Entity& x: manager.tilesNonWalkable)
                {
                    if(rectProbe.getGlobalBounds().contains(x.ptrCTile->spriteTile.getPosition()) && !x.ptrCTile->isWalkable)
                       {
                           tileXMinusOccupied = true;
                           continue;
                       }
                }
            }
            //y+ axis test
            rectProbe.setPosition(entity.ptrCTransform->position.x + 5,  entity.ptrCTransform->position.y + b);
            if(rectProbe.getPosition().y > 1020)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileYPlusOccupied = true;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileYPlusOccupied == false && !y.destroyed)
            {
                tileYPlusOccupied = true;
                continue;
            }
            else if(tileYPlusOccupied == false)
            {
                for(Entity& x: manager.tilesNonWalkable)
                {
                    if(rectProbe.getGlobalBounds().contains(x.ptrCTile->spriteTile.getPosition()) && !x.ptrCTile->isWalkable)
                       {
                           tileYPlusOccupied = true;
                           continue;
                       }
                }
            }
            //y- axis test
            rectProbe.setPosition(entity.ptrCTransform->position.x - 5,  entity.ptrCTransform->position.y - b);
            if(rectProbe.getPosition().y < 50)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileYMinusOccupied = true;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileYMinusOccupied == false && !y.destroyed)
            {
                tileYMinusOccupied = true;
                continue;
            }
            else if(tileYMinusOccupied == false)
            {
                for(Entity& x: manager.tilesNonWalkable)
                {
                    if(rectProbe.getGlobalBounds().contains(x.ptrCTile->spriteTile.getPosition()) && !x.ptrCTile->isWalkable)
                       {
                           tileYMinusOccupied = true;
                           continue;
                       }
                }
            }

            //angle axis x+,y-
            rectProbe.setPosition(entity.ptrCTransform->position.x + a,  entity.ptrCTransform->position.y - 105);
            if(rectProbe.getPosition().x > 1900 || rectProbe.getPosition().y < 50)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXPlusYMinusOccupied = true;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXPlusYMinusOccupied == false && !y.destroyed)
            {
                tileXPlusYMinusOccupied = true;
                continue;
            }
            else if(tileXPlusYMinusOccupied == false)
            {
                for(Entity& x: manager.tilesNonWalkable)
                {
                    if(rectProbe.getGlobalBounds().contains(x.ptrCTile->spriteTile.getPosition()) && !x.ptrCTile->isWalkable)
                       {
                           tileXPlusYMinusOccupied = true;
                           continue;
                       }
                }
            }
            //angle axis x+,y+
            rectProbe.setPosition(entity.ptrCTransform->position.x + a,  entity.ptrCTransform->position.y + 105);
            if(rectProbe.getPosition().x > 1900 || rectProbe.getPosition().y > 1000)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXPlusYPlusOccupied = true;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXPlusYPlusOccupied == false && !y.destroyed)
            {
                tileXPlusYPlusOccupied = true;
                continue;
            }
            else if(tileXPlusYPlusOccupied == false)
            {
                for(Entity& x: manager.tilesNonWalkable)
                {
                    if(rectProbe.getGlobalBounds().contains(x.ptrCTile->spriteTile.getPosition()) && !x.ptrCTile->isWalkable)
                       {
                           tileXPlusYPlusOccupied = true;
                           continue;
                       }
                }
            }
            //angle axis x-,y-
            rectProbe.setPosition(entity.ptrCTransform->position.x - a,  entity.ptrCTransform->position.y - 105);
            if(rectProbe.getPosition().x < 30 || rectProbe.getPosition().y < 50)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXMinusYMinusOccupied = true;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXMinusYMinusOccupied == false && !y.destroyed)
            {
                tileXMinusYMinusOccupied = true;
                continue;
            }
            else if(tileXMinusYMinusOccupied == false)
            {
                for(Entity& x: manager.tilesNonWalkable)
                {
                    if(rectProbe.getGlobalBounds().contains(x.ptrCTile->spriteTile.getPosition()) && !x.ptrCTile->isWalkable)
                       {
                           tileXMinusYMinusOccupied = true;
                           continue;
                       }
                }
            }
            //angle axis x-,y+
            rectProbe.setPosition(entity.ptrCTransform->position.x - a,  entity.ptrCTransform->position.y + 105);
            if(rectProbe.getPosition().x < 30 || rectProbe.getPosition().y > 1000)   // Checking the map borders and marking the tile as occupied if it is outside map.
            {
                tileXMinusYPlusOccupied = true;
                //continue;
            }
            if(rectProbe.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && tileXMinusYPlusOccupied == false && !y.destroyed)
            {
                tileXMinusYPlusOccupied = true;
                continue;
            }
            else if(tileXMinusYPlusOccupied == false)
            {
                for(Entity& x: manager.tilesNonWalkable)
                {
                    if(rectProbe.getGlobalBounds().contains(x.ptrCTile->spriteTile.getPosition()) && !x.ptrCTile->isWalkable)
                       {
                           tileXMinusYPlusOccupied = true;
                           continue;
                       }
                }
            }
        }

        //show possible unit path
        if(!tileXPlusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Green);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + (a - 0.1),  entity.ptrCTransform->position.y + 5);
            }

        if(!tileXMinusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Green);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x - (a-10),  entity.ptrCTransform->position.y + 5);
            }
        if(!tileYPlusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Green);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + 5,  entity.ptrCTransform->position.y + b);
            }
        if(!tileYMinusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Green);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + 5,  entity.ptrCTransform->position.y - (b-10));
            }
            if(!tileXPlusYMinusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Green);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + (a - 0.1),  entity.ptrCTransform->position.y - 95);
            }
            if(!tileXPlusYPlusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Green);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x + (a - 0.1),  entity.ptrCTransform->position.y + 105);
            }
            if(!tileXMinusYMinusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Green);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x - (a - 10),  entity.ptrCTransform->position.y - 95);
            }
            if(!tileXMinusYPlusOccupied)
            {
                rectVec.push_back(sf::RectangleShape());
                rectVec.back().setSize(sf::Vector2f(80,80));
                rectVec.back().setOrigin(45,45);
                rectVec.back().setFillColor(sf::Color::Transparent);
                rectVec.back().setOutlineColor(sf::Color::Green);
                rectVec.back().setOutlineThickness(5);
                rectVec.back().setPosition(entity.ptrCTransform->position.x - (a - 10),  entity.ptrCTransform->position.y + 105);
            }
            else
            {
                continue;
            }
    }
}



///Move unit
void MMovement::moveUnit(Entity& entity)
{
    for(sf::RectangleShape& i: rectVec)
    {
        sf::Vector2f mousePos(sf::Mouse::getPosition());
        if(i.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));      //delaying function execution for given time.

            entity.ptrCMilitaryUnit->spriteMilitaryUnit.setPosition(i.getPosition());
            entity.ptrCTransform->position.x = i.getPosition().x - 5;
            entity.ptrCTransform->position.y = i.getPosition().y - 5;

            entity.healthPosition(entity);

            pathActive = false;
            entity.ptrCMilitaryUnit->unitMoved   = true;
            entity.ptrCMilitaryUnit->movePressed = false;

            entity.ptrCMilitaryUnit->movementRange = 0;

            break;
        }
    }
}


void MMovement::draw(sf::RenderWindow& window)
{
    if(pathActive)
    {
        for(sf::RectangleShape& i: rectVec)
        {
            window.draw(i);
        }
    }
}











