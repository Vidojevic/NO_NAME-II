#include <SFML/Graphics.hpp>
#include "Components.h"
#include <string>
#include <iostream>

#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:
    friend class EntityManager;          //Friend with EntityManager class. All entity's are built in EntityManager class.

//variables
public:
    bool          isActive      = true;         //Military units active when Player is playing, false when ends turn. Used also for icons(move, attack, fortify).
    bool          destroyed     = false;        //When military unit is destroyed, this flag is set to TRUE.
    int           id            = 0;
    std::string   tag           = "Default";    //The name of the Entity (tile, tank, soldier, artilery, mine, base, etc  *********OVO IDE U ENTITY MANAGER

//pointers to components
    CPlayer*        ptrCplayer       = nullptr;
    CTransform*     ptrCTransform    = nullptr;
    CMilitaryUnit*  ptrCMilitaryUnit = nullptr;
    CHealth*        ptrCHealth       = nullptr;
    CSpecial*       ptrCSpecial      = nullptr;
    CTile*          ptrCTile         = nullptr;
    CResources*     ptrCResources    = nullptr;

//functions
public:
    void                 healthPosition(Entity& entity);    //Used for updating the health bar position relevant to military unit position. Is always above the unit.

    const int            getID()       const;       //Getter
    const std::string&   getTag()      const;       //Getter

private:
    void freePointersToComponentsMilitaryUnit();      //Freeing pointers to components for Military Units entities. Used in Destructor.
    void freePointersToComponentsTilesNonWalkable();  //Freeing pointers to components for Non-Walkable Tiles entities. Used in Destructor.



//Constructor-Destructor
private:
    Entity();                    //Constructor is private. This class is only used by EntityManager class via Friend command. Only EntityManager can create Entity's.
public:
    virtual ~Entity();
};

#endif // ENTITY_H
