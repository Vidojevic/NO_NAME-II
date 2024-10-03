#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
    //freeing pointers to components for different Entity types
    //military units:
    if(tag == "infantryGreen" || tag == "tankGreen" || tag == "artileryGreen" || tag == "infantryYellow" || tag == "tankYellow" || tag == "artileryYellow")
    {
        freePointersToComponentsMilitaryUnit();
    }
    //non-walkable tiles
    else if(tag == "baseGreen" || tag == "baseYellow" || tag == "volcano1" || tag == "volcano2" || tag == "goldMine" || tag == "ironMine" || tag == "mountain" || tag == "unknown")
    {
        freePointersToComponentsTilesNonWalkable();
    }
}


///Healt positioning
void Entity::healthPosition(Entity& entity)
{
    entity.ptrCHealth->healthBar[0].setPosition(entity.ptrCTransform->position.x - 20, entity.ptrCTransform->position.y - 35);
    entity.ptrCHealth->healthBar[1].setPosition(entity.ptrCTransform->position.x - 10, entity.ptrCTransform->position.y - 35);
    entity.ptrCHealth->healthBar[2].setPosition(entity.ptrCTransform->position.x - 0, entity.ptrCTransform->position.y - 35);
    entity.ptrCHealth->healthBar[3].setPosition(entity.ptrCTransform->position.x + 10, entity.ptrCTransform->position.y - 35);
    entity.ptrCHealth->healthBar[4].setPosition(entity.ptrCTransform->position.x + 20, entity.ptrCTransform->position.y - 35);
}


///getId
const int Entity::getID() const
{
    return id;
}


///getTag
const std::string& Entity::getTag() const
{
    return tag;
}


///freeing pointers to components for Military Units entities
void Entity::freePointersToComponentsMilitaryUnit()
{
    delete ptrCTransform;
    ptrCTransform = nullptr;
    //std::cout << "Entity ptrCTransform deleted\n";
    delete ptrCMilitaryUnit;
    ptrCMilitaryUnit = nullptr;
    //std::cout << "Entity ptrCMilitaryUnit deleted\n";
    delete ptrCHealth;
    ptrCHealth = nullptr;
    //std::cout << "Entity ptrCHealth deleted\n";
    delete ptrCSpecial;
    ptrCSpecial = nullptr;
    //std::cout << "Entity ptrCSpecial deleted\n";
}


///freeing pointers to components for Non-Walkable Tiles
void Entity::freePointersToComponentsTilesNonWalkable()
{
    delete ptrCTransform;
    ptrCTransform = nullptr;
    //std::cout << "Entity ptrCTransform deleted.\n";
    delete ptrCTile;
    ptrCTile = nullptr;
    //std::cout << "Entity ptrCTile deleted.\n";
}









