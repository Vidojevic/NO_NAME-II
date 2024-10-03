#include "EntityManager.h"

/*EntityManager::EntityManager()    //Constructor is defined in the header!!!
{
}
*/
EntityManager::~EntityManager()
{
    //freeing pointers to texture
    for(sf::Texture* i: textureVec)
    {
        delete i;
        i = nullptr;
        //std::cout << "texture pointer deleted.\n";
    }

}



///createEntity
void EntityManager::createEntity(const std::string entityType, sf::Vector2f position)  // second argument is default value,player has no position therefore this arg is default.
{
    entityID += 1;                 //Total number of Entity created. Used for Entity id.

    //player 1
    if(entityType == "player1")
    {
        player1.tag           = entityType;
        player1.id            = entityID;
        //adding components
        player1.ptrCplayer    = new CPlayer;
        player1.ptrCResources = new CResources;
    }
    //player 2
    else if(entityType == "player2")
    {
        player2.tag           = entityType;
        player2.id            = entityID;
        //adding components
        player2.ptrCplayer    = new CPlayer();
        player2.ptrCResources = new CResources();
        //initializing components data members
        player2.ptrCplayer->isPlaying = false;
    }
    //infantry green
    else if(entityType == "infantryGreen")
    {
        militaryUnits.push_back(Entity());
        //militaryUnits.emplace_back();       //Without passing a type it creates an object in place. If there are arguments in objetcs constructor, they should be passed in the paranteses.
                                              //If we pass a type of an object in the parantese, it copies it into vector, the same what push_back does.
        militaryUnits.back().tag = entityType;
        militaryUnits.back().id  = entityID;
        //adding components
        militaryUnits.back().ptrCTransform    = new CTransform(sf::Vector2f(80,60));
        militaryUnits.back().ptrCMilitaryUnit = new CMilitaryUnit();
        militaryUnits.back().ptrCHealth       = new CHealth();
        militaryUnits.back().ptrCSpecial      = new CSpecial();
        //initializing component data members
        militaryUnits.back().ptrCTransform->position         = position;
        militaryUnits.back().ptrCMilitaryUnit->health        = 5;
        militaryUnits.back().ptrCMilitaryUnit->movementRange = 1;
        militaryUnits.back().ptrCMilitaryUnit->movementRangeDefault = 1;
        militaryUnits.back().ptrCMilitaryUnit->shootingRange = 1;
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setTexture(*textureVec[0]);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setOrigin(militaryUnits.back().ptrCTransform->spriteHalfSize);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setPosition(militaryUnits.back().ptrCTransform->position);

        healthComponentInitialization(militaryUnits.back());
    }
    //tank green
    else if(entityType == "tankGreen")
    {
        militaryUnits.push_back(Entity());

        militaryUnits.back().tag = entityType;
        militaryUnits.back().id  = entityID;
        //adding components
        militaryUnits.back().ptrCTransform    = new CTransform(sf::Vector2f(80,56));
        militaryUnits.back().ptrCMilitaryUnit = new CMilitaryUnit();
        militaryUnits.back().ptrCHealth       = new CHealth();
        militaryUnits.back().ptrCSpecial      = new CSpecial();
        //initializing component data members
        militaryUnits.back().ptrCTransform->position = position;
        militaryUnits.back().ptrCMilitaryUnit->health        = 5;
        militaryUnits.back().ptrCMilitaryUnit->movementRange = 2;
        militaryUnits.back().ptrCMilitaryUnit->movementRangeDefault = 2;
        militaryUnits.back().ptrCMilitaryUnit->shootingRange = 1;
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setTexture(*textureVec[1]);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setOrigin(militaryUnits.back().ptrCTransform->spriteHalfSize);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setPosition(militaryUnits.back().ptrCTransform->position);

        healthComponentInitialization(militaryUnits.back());
    }
    //artilery green
    else if(entityType == "artileryGreen")
    {
        militaryUnits.push_back(Entity());

        militaryUnits.back().tag = entityType;
        militaryUnits.back().id  = entityID;
        //adding components
        militaryUnits.back().ptrCTransform    = new CTransform(sf::Vector2f(80,72));
        militaryUnits.back().ptrCMilitaryUnit = new CMilitaryUnit();
        militaryUnits.back().ptrCHealth       = new CHealth();
        militaryUnits.back().ptrCSpecial      = new CSpecial();
        //initializing component data members
        militaryUnits.back().ptrCTransform->position = position;
        militaryUnits.back().ptrCMilitaryUnit->health        = 5;
        militaryUnits.back().ptrCMilitaryUnit->movementRange = 1;
        militaryUnits.back().ptrCMilitaryUnit->movementRangeDefault = 1;
        militaryUnits.back().ptrCMilitaryUnit->shootingRange = 2;
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setTexture(*textureVec[2]);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setOrigin(militaryUnits.back().ptrCTransform->spriteHalfSize);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setPosition(militaryUnits.back().ptrCTransform->position);

        healthComponentInitialization(militaryUnits.back());
    }
    //infantry yellow
    else if(entityType == "infantryYellow")
    {
        militaryUnits.push_back(Entity());
        //militaryUnits.emplace_back();       //Without passing a type it creates an object in place. If there are arguments in objetcs constructor, they should be passed in the paranteses.
                                              //If we pass a type of an object in the parantese, it copies it into vector, the same what push_back does.
        militaryUnits.back().tag = entityType;
        militaryUnits.back().id  = entityID;
        //adding components
        militaryUnits.back().ptrCTransform    = new CTransform(sf::Vector2f(80,62));
        militaryUnits.back().ptrCMilitaryUnit = new CMilitaryUnit();
        militaryUnits.back().ptrCHealth       = new CHealth();
        militaryUnits.back().ptrCSpecial      = new CSpecial();
        //initializing component data members
        militaryUnits.back().ptrCTransform->position = position;
        militaryUnits.back().ptrCMilitaryUnit->health        = 5;
        militaryUnits.back().ptrCMilitaryUnit->movementRange = 1;
        militaryUnits.back().ptrCMilitaryUnit->movementRangeDefault = 1;
        militaryUnits.back().ptrCMilitaryUnit->shootingRange = 1;
        militaryUnits.back().isActive                        = false;               //Is set to false because this are the yellow player units and the don't play at the start of the game.
                                                                                    //After the green player finishes his turn, yellow units are all set isActive=true, and green's to false.
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setTexture(*textureVec[3]);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setOrigin(militaryUnits.back().ptrCTransform->spriteHalfSize);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setPosition(militaryUnits.back().ptrCTransform->position);

        healthComponentInitialization(militaryUnits.back());
    }
    //tank yellow
    else if(entityType == "tankYellow")
    {
        militaryUnits.push_back(Entity());

        militaryUnits.back().tag = entityType;
        militaryUnits.back().id  = entityID;
        //adding components
        militaryUnits.back().ptrCTransform    = new CTransform(sf::Vector2f(80,52));
        militaryUnits.back().ptrCMilitaryUnit = new CMilitaryUnit();
        militaryUnits.back().ptrCHealth       = new CHealth();
        militaryUnits.back().ptrCSpecial      = new CSpecial();
        //initializing component data members
        militaryUnits.back().ptrCTransform->position = position;
        militaryUnits.back().ptrCMilitaryUnit->health        = 5;
        militaryUnits.back().ptrCMilitaryUnit->movementRange = 2;
        militaryUnits.back().ptrCMilitaryUnit->movementRangeDefault = 2;
        militaryUnits.back().ptrCMilitaryUnit->shootingRange = 1;
        militaryUnits.back().isActive                        = false;               //Is set to false because this are the yellow player units and the don't play at the start of the game.
                                                                                    //After the green player finishes his turn, yellow units are all set isActive=true, and green's to false.
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setTexture(*textureVec[4]);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setOrigin(militaryUnits.back().ptrCTransform->spriteHalfSize);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setPosition(militaryUnits.back().ptrCTransform->position);

        healthComponentInitialization(militaryUnits.back());
    }
    //artilery yellow
    else if(entityType == "artileryYellow")
    {
        militaryUnits.push_back(Entity());

        militaryUnits.back().tag  = entityType;
        militaryUnits.back().id   = entityID;
        //adding components
        militaryUnits.back().ptrCTransform    = new CTransform(sf::Vector2f(80,70));
        militaryUnits.back().ptrCMilitaryUnit = new CMilitaryUnit();
        militaryUnits.back().ptrCHealth       = new CHealth();
        militaryUnits.back().ptrCSpecial      = new CSpecial();
        //initialize component data members
        militaryUnits.back().ptrCTransform->position = position;
        militaryUnits.back().ptrCMilitaryUnit->health        = 5;
        militaryUnits.back().ptrCMilitaryUnit->movementRange = 1;
        militaryUnits.back().ptrCMilitaryUnit->movementRangeDefault = 1;
        militaryUnits.back().ptrCMilitaryUnit->shootingRange = 2;
        militaryUnits.back().isActive                        = false;               //Is set to false because this are the yellow player units and the don't play at the start of the game.
                                                                                    //After the green player finishes his turn, yellow units are all set isActive=true, and green's to false.
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setTexture(*textureVec[5]);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setOrigin(militaryUnits.back().ptrCTransform->spriteHalfSize);
        militaryUnits.back().ptrCMilitaryUnit->spriteMilitaryUnit.setPosition(militaryUnits.back().ptrCTransform->position);

        healthComponentInitialization(militaryUnits.back());
    }
    //base green
    else if(entityType == "baseGreen")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(81,90));
        tilesNonWalkable.back().ptrCTile      = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[6]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
        tilesNonWalkable.back().ptrCTile->baseActive = true;
        tilesNonWalkable.back().ptrCTile->isWalkable = true;

    }
    //base yellow
    else if(entityType == "baseYellow")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(81,90));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[7]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
        tilesNonWalkable.back().ptrCTile->baseActive = false;
        tilesNonWalkable.back().ptrCTile->isWalkable = true;
    }
    //volcano 1
    else if(entityType == "volcano1")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(90,72));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[11]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
    }
    //volcano 2
    else if(entityType == "volcano2")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(90,78));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[12]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
    }
    //gold mine
    else if(entityType == "goldMine")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(90,75));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[9]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
        tilesNonWalkable.back().ptrCTile->isWalkable = true;
    }
    //iron mine
    else if(entityType == "ironMine")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(90,81));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[8]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
        tilesNonWalkable.back().ptrCTile->isWalkable = true;
    }
    //mountain
    else if(entityType == "mountain")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(190,111));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[10]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
    }
    //still unknown use for this tile
    else if(entityType == "unknown")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(90,82));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[13]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
        tilesNonWalkable.back().ptrCTile->isWalkable = true;
    }
    //volcano (2x2 tile) tile 1
    else if(entityType == "greatVolcano1")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(95,91));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[28]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
    }
    //volcano (2x2 tile) tile 2
    else if(entityType == "greatVolcano2")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(95,91));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[29]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
    }
    //volcano  (2x2 tile) tile 3
    else if(entityType == "greatVolcano3")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(95,91));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[30]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
    }
    //volcano  (2x2 tile) tile 4
    else if(entityType == "greatVolcano4")
    {
        tilesNonWalkable.push_back(Entity());

        tilesNonWalkable.back().tag = entityType;
        tilesNonWalkable.back().id  = entityID;
        //adding components
        tilesNonWalkable.back().ptrCTransform = new CTransform(sf::Vector2f(95,91));
        tilesNonWalkable.back().ptrCTile = new CTile();
        //initializing component data members
        tilesNonWalkable.back().ptrCTransform->position = position;
        tilesNonWalkable.back().ptrCTile->spriteTile.setTexture(*textureVec[31]);
        tilesNonWalkable.back().ptrCTile->spriteTile.setOrigin(tilesNonWalkable.back().ptrCTransform->spriteHalfSize);
        tilesNonWalkable.back().ptrCTile->spriteTile.setPosition(tilesNonWalkable.back().ptrCTransform->position);
    }

}


///destroyEntity
void EntityManager::destroyEntity(Entity entity)
{
    entity.destroyed = true;
}


///Health Component Initialization - It is used only once during the entity creation
void EntityManager::healthComponentInitialization(Entity& entity)
{
    for(unsigned i=0; i < 5; ++i)
    {
        entity.ptrCHealth->healthBar.push_back(sf::Sprite());
        entity.ptrCHealth->healthBar.back().setTexture(*textureVec[17]);
        entity.ptrCHealth->healthBar.back().setOrigin(5,5);
    }

    entity.healthPosition(entity);   //Setting position for the health sprites (health bar) above the military unit
}


/*///Health Position       ***MOVED TO ENTITY CLASS***
void EntityManager::healthPosition(Entity& entity)
{
    entity.ptrCHealth->healthBar[0].setPosition(entity.ptrCTransform->position.x - 20, entity.ptrCTransform->position.y - 35);
    entity.ptrCHealth->healthBar[1].setPosition(entity.ptrCTransform->position.x - 10, entity.ptrCTransform->position.y - 35);
    entity.ptrCHealth->healthBar[2].setPosition(entity.ptrCTransform->position.x - 0, entity.ptrCTransform->position.y - 35);
    entity.ptrCHealth->healthBar[3].setPosition(entity.ptrCTransform->position.x + 10, entity.ptrCTransform->position.y - 35);
    entity.ptrCHealth->healthBar[4].setPosition(entity.ptrCTransform->position.x + 20, entity.ptrCTransform->position.y - 35);
}
*/

///textureInitialization
void EntityManager::textureInitialization()
{
    for (unsigned i=0; i < 36; ++i)   //Magic number 19. Ovde voditi racuna jer broj mora da bude ekvivalentan broju tile-ova koji postoje u folder za ucitavanje, inace nece da ucita sve ili
                                      //ce da se javi greska.
    {
        std::string fileName = ("assets/sprite" + std::to_string(i) + ".png");    // Converting number into string. Svi sprajtovi u folder "assets" nose isto ime,
                                                                                  // pocinju sa "tile" i samo se dodaje broj na kraj zbog lakseg ucitavanje iz fajla.
        textureVec.push_back(new sf::Texture);

        textureVec[i]->loadFromFile(fileName);
    }

}







