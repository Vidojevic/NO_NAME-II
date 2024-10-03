#include <SFML/Graphics.hpp>
#include "Components.h"
#include "Entity.h"
#include <iostream>
#include <string>


#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


class EntityManager
{
//variables
public:
    unsigned int              entityID = 0;        //Counter for total entity created.
    Entity                    player1;             //First player.
    Entity                    player2;             //Second player.
    std::vector<Entity>       tilesNonWalkable;    //Storage for non-walkable tiles, tiles that are an obstacle for units (mountains, mines, bases, etc).
    std::vector<Entity>       militaryUnits;       //Storage for all military units (infantry, tanks, artilery..).
    std::vector<sf::Texture*> textureVec;          //Storage for all texture.


//functions
public:
    void createEntity(const std::string entityType, sf::Vector2f position = sf::Vector2f(0,0));      //Creates Entity. Second parameter is default value because of entity Player creation that doesnt
                                                                                                     //require a position value.
    void destroyEntity(Entity entity);                    //When unit is destroyed, flag Enity.ptrMilitaryUnits->destroyed is set to TRUE.
    void healthComponentInitialization(Entity& entity);   //Adding sprites to 5 health cubes (CHealth component).
//    void healthPosition(Entity& entity);                  //**MOVED TO ENTITY CLASS** Used for updating the health bar position relevant to military unit position. Is always above the unit.
    void textureInitialization();                         //Loading texture from file to vector.
    void draw();                                          //Update all entities.

//Constructor/Destructor
public:
    EntityManager()
    {
        //reserving memory for all vectors
        militaryUnits.reserve(50);                    //Reserve memory for 50 entity objects. This way the vector will not be resized when new units are added.
        tilesNonWalkable.reserve(30);
        textureVec.reserve(40);
    };
    virtual ~EntityManager();

};

#endif // ENTITYMANAGER_H
