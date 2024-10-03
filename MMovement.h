#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>       //time
#include <thread>       //for delaying a moveUnit function, thread
#include "Entity.h"
#include "EntityManager.h"
#include "MSelection.h"

#ifndef MMOVEMENT_H
#define MMOVEMENT_H


class MMovement
{
//data members
public:
    bool pathActive = false;    //Path displayed.

private:
    std::vector<sf::RectangleShape> rectVec;    //Storing tile rectangles for unit movement

//functions
public:
    void moveShow(EntityManager& manager, Entity& entity);    //When Move button clicked. Displays tiles that can be used for unit movement.

    void moveUnit(Entity& entity);                            //Move unit.

    void draw(sf::RenderWindow& window);


//Constructor/Destructor
public:
    MMovement();
    virtual ~MMovement();
};

#endif // MMOVEMENT_H
