#include "Game.h"

Game::Game()
{
    for (unsigned i=0; i < 6; ++i)   //Magic number 19. Ovde voditi racuna jer broj mora da bude ekvivalentan broju tile-ova koji postoje u folder za ucitavanje, inace nece da ucita sve ili
                                      //ce da se javi greska.
    {
        std::string fileName = ("assets/sound" + std::to_string(i) + ".wav");    // Converting number into string. Svi sprajtovi u folder "assets" nose isto ime,
                                                                                  // pocinju sa "tile" i samo se dodaje broj na kraj zbog lakseg ucitavanje iz fajla.
        soundBuffer.push_back(sf::SoundBuffer());     //creating new object.

        soundBuffer[i].loadFromFile(fileName);         //loading buffer from file to new created object.
    }



    //start screen font
    fontStartWindow.loadFromFile("assets/font2.ttf");
}

Game::~Game()
{
}

///run
void Game::run()
{
    //render window
    const unsigned WINDOW_WIDTH  = 1920;
    const unsigned WINDOW_HEIGHT = 1080;

    sf::RenderWindow window (sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NO_NAME 2" ,sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    //event
    sf::Event event;
    //map
    sf::Texture mapTexture;
    if(!mapTexture.loadFromFile("assets/map_1.jpg"))
    {
        std::cerr << "Error loading tile texture!";
    }
    sf::Sprite mapSprite;
    mapSprite.setTexture(mapTexture);
    mapSprite.setPosition(0,0);
    //sound
    sf::Sound soundDenied;
    soundDenied.setBuffer(soundBuffer[0]);
    sf::Sound soundVictory;
    soundVictory.setBuffer(soundBuffer[3]);
    sf::Sound baseSelection;
    baseSelection.setBuffer(soundBuffer[4]);
    sf::Sound unitSelection;
    unitSelection.setBuffer(soundBuffer[5]);
    //game music
    sf::Sound epicMusic;
    epicMusic.setBuffer(soundBuffer[1]);
    sf::Sound gameMusic;
    gameMusic.setBuffer(soundBuffer[2]);
    gameMusic.setVolume(60);
    //entity manager
    EntityManager entityManager;
    //texture  initialization
    entityManager.textureInitialization();
    //inGame Menu
    inGameMenu.setTexture(*entityManager.textureVec[33]);
    //vicotry windows
    winPlayer1.setTexture(*entityManager.textureVec[34]);
    winPlayer2.setTexture(*entityManager.textureVec[35]);
    //creating entities
    entityManager.createEntity("player1");
    entityManager.createEntity("player2");
    initialization(entityManager);
    //Selection mechanism
    MSelection selection(entityManager);
    //Combat
    MCombat combat;
    //seeding rand() in combat class.
    srand(time(0));
    //Movement
    MMovement movement;


///MAIN LOOP
    while(window.isOpen())
    {
        //start window music- In game music is under option1 start game.
        if(!gameWindow && window.isOpen())
        {
            gameMusic.stop();
            epicMusic.setLoop(true);
            epicMusic.play();
        }
        else if(gameWindow && window.isOpen())
        {
            epicMusic.stop();
        }

///START WINDOW
        while(!gameWindow && window.isOpen())
        {
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
                    window.close();
            }
            //theme
            menuText1.setFont(fontStartWindow);
            menuText1.setFillColor(sf::Color::Green);
            menuText1.setCharacterSize(150);
            menuText1.setString("NO_NAME 2");
            menuText1.setPosition(400,300);
            //new game option
            menuText2.setFont(selection.font);
            menuText2.setFillColor(sf::Color(192,192,192, 255));
            menuText2.setCharacterSize(30);
            menuText2.setString("New Game");
            menuText2.setPosition(850,600);
            //load game option
            menuText3.setFont(selection.font);
            menuText3.setFillColor(sf::Color(192,192,192, 255));
            menuText3.setCharacterSize(30);
            menuText3.setString("Load Game");
            menuText3.setPosition(846,640);
            //quit game option
            menuText4.setFont(selection.font);
            menuText4.setFillColor(sf::Color(192,192,192, 255));
            menuText4.setCharacterSize(30);
            menuText4.setString("Quit Game");
            menuText4.setPosition(850,680);
            //if mouse hovering above menu options, make letters bigger.
            sf::Vector2f mousePos(sf::Mouse::getPosition());
            //option1
            if(menuText2.getGlobalBounds().contains(mousePos))
            {
                menuText2.setCharacterSize(40);
                menuText2.setPosition(827,595);
            }
            else
            {
                menuText2.setCharacterSize(30);
                menuText2.setPosition(850,600);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuText2.getGlobalBounds().contains(mousePos))
            {
                gameWindow = true;
                inGameMenuDisplay = false;
                restartGame(entityManager,selection,movement,combat);
                //In Game music                                               ///INGAME MUSIC
                //gameMusic.setVolume(30);
                gameMusic.setLoop(true);
                gameMusic.play();
            }
            //option2
            if(menuText3.getGlobalBounds().contains(mousePos))
            {
                menuText3.setCharacterSize(40);
                menuText3.setPosition(822,633);
            }
            else
            {
                menuText3.setCharacterSize(30);
                menuText3.setPosition(846,640);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuText3.getGlobalBounds().contains(mousePos))
            {
                gameWindow = true;
                inGameMenuDisplay = false;
                loadGame(entityManager,selection,movement,combat);
                //gameMusic.setVolume(30);
                gameMusic.setLoop(true);
                gameMusic.play();
            }
            //option3
            if(menuText4.getGlobalBounds().contains(mousePos))
            {
                menuText4.setCharacterSize(40);
                menuText4.setPosition(826,675);
            }
            else
            {
                menuText4.setCharacterSize(30);
                menuText4.setPosition(850,680);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuText4.getGlobalBounds().contains(mousePos))
            {
                window.close();
            }

            window.clear(sf::Color::Black);
            window.draw(menuText1);
            window.draw(menuText2);
            window.draw(menuText3);
            window.draw(menuText4);
            window.display();
        }

///GAME WINDOW
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
            {
                window.close();
            }
        }

///InGame Menu
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && (!inGameMenuDisplay))
        {
            selection.selectionActive =  false;
            selection.infoWindowDisplayed = false;
            inGameMenuDisplay = true;
            //sprite menu
            inGameMenu.setOrigin(181,251);
            inGameMenu.setPosition(961,490);
            //text options
            menuText1.setFont(selection.font);
            menuText1.setFillColor(sf::Color::Green);
            menuText1.setCharacterSize(30);
            menuText1.setString("SAVE GAME");
            menuText1.setPosition(inGameMenu.getPosition().x - 83, inGameMenu.getPosition().y - 150);
            menuText2.setFont(selection.font);
            menuText2.setFillColor(sf::Color::Green);
            menuText2.setCharacterSize(30);
            menuText2.setString("LOAD GAME");
            menuText2.setPosition(inGameMenu.getPosition().x - 85, inGameMenu.getPosition().y - 100);
            menuText3.setFont(selection.font);
            menuText3.setFillColor(sf::Color::Green);
            menuText3.setCharacterSize(30);
            menuText3.setString("RESTART");
            menuText3.setPosition(inGameMenu.getPosition().x - 65, inGameMenu.getPosition().y - 50);
            menuText4.setFont(selection.font);
            menuText4.setFillColor(sf::Color::Green);
            menuText4.setCharacterSize(30);
            menuText4.setString("MAIN MENU");
            menuText4.setPosition(inGameMenu.getPosition().x - 81, inGameMenu.getPosition().y + 0);
            menuText5.setFont(selection.font);
            menuText5.setFillColor(sf::Color::Green);
            menuText5.setCharacterSize(30);
            menuText5.setString("QUIT GAME");
            menuText5.setPosition(inGameMenu.getPosition().x - 80, inGameMenu.getPosition().y + 50);
            menuText6.setFont(selection.font);
            menuText6.setFillColor(sf::Color::Green);
            menuText6.setCharacterSize(30);
            menuText6.setString("CLOSE");
            menuText6.setPosition(inGameMenu.getPosition().x - 45, inGameMenu.getPosition().y + 197);
        }
        //if menu open
        else if(inGameMenuDisplay)
        {
            selection.selectionActive = false;
            //if mouse hovering above menu options, make letters bigger.
            sf::Vector2f mousePos(sf::Mouse::getPosition());
            //option1
            if(menuText1.getGlobalBounds().contains(mousePos))
            {
                menuText1.setCharacterSize(40);
                menuText1.setPosition(inGameMenu.getPosition().x - 108, inGameMenu.getPosition().y - 156);
            }
            else
            {
                menuText1.setCharacterSize(30);
                menuText1.setPosition(inGameMenu.getPosition().x - 83, inGameMenu.getPosition().y - 150);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuText1.getGlobalBounds().contains(mousePos))
            {
                inGameMenuDisplay = false;
                selection.selectionActive = true;
                saveGame(entityManager,selection);
            }
            //option2
            if(menuText2.getGlobalBounds().contains(mousePos))
            {
                menuText2.setCharacterSize(40);
                menuText2.setPosition(inGameMenu.getPosition().x - 107, inGameMenu.getPosition().y - 106);
            }
            else
            {
                menuText2.setCharacterSize(30);
                menuText2.setPosition(inGameMenu.getPosition().x - 85, inGameMenu.getPosition().y - 100);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuText2.getGlobalBounds().contains(mousePos))
            {
                inGameMenuDisplay = false;
                selection.selectionActive = true;
                loadGame(entityManager,selection,movement,combat);
            }
            //option3
            if(menuText3.getGlobalBounds().contains(mousePos))
            {
                menuText3.setCharacterSize(40);
                menuText3.setPosition(inGameMenu.getPosition().x - 85, inGameMenu.getPosition().y - 55);
            }
            else
            {
                menuText3.setCharacterSize(30);
                menuText3.setPosition(inGameMenu.getPosition().x - 65, inGameMenu.getPosition().y - 50);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuText3.getGlobalBounds().contains(mousePos))
            {
                inGameMenuDisplay = false;
                selection.selectionActive = true;
                restartGame(entityManager,selection,movement, combat);
            }
            //option4
            if(menuText4.getGlobalBounds().contains(mousePos))
            {
                menuText4.setCharacterSize(40);
                menuText4.setPosition(inGameMenu.getPosition().x - 106, inGameMenu.getPosition().y - 7);
            }
            else
            {
                menuText4.setCharacterSize(30);
                menuText4.setPosition(inGameMenu.getPosition().x - 81, inGameMenu.getPosition().y + 0);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuText4.getGlobalBounds().contains(mousePos))
            {
                gameWindow = false;
                selection.selectionActive = true;
            }
            //option5
            if(menuText5.getGlobalBounds().contains(mousePos))
            {
                menuText5.setCharacterSize(40);
                menuText5.setPosition(inGameMenu.getPosition().x - 102, inGameMenu.getPosition().y + 43);
            }
            else
            {
                menuText5.setCharacterSize(30);
                menuText5.setPosition(inGameMenu.getPosition().x - 80, inGameMenu.getPosition().y + 50);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuText5.getGlobalBounds().contains(mousePos))
            {
                window.close();
            }
            //option6
            if(menuText6.getGlobalBounds().contains(mousePos))
            {
                menuText6.setCharacterSize(40);
                menuText6.setPosition(inGameMenu.getPosition().x - 60, inGameMenu.getPosition().y + 190);
            }
            else
            {
                menuText6.setCharacterSize(30);
                menuText6.setPosition(inGameMenu.getPosition().x - 45, inGameMenu.getPosition().y + 197);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuText6.getGlobalBounds().contains(mousePos))
            {
                inGameMenuDisplay = false;
                menuText1.setPosition(0,0);
                menuText2.setPosition(0,0);
                menuText3.setPosition(0,0);
                menuText4.setPosition(0,0);
                menuText5.setPosition(0,0);
                menuText6.setPosition(0,0);
            }

        }

     selection.actionMenu(entityManager, unitSelection, baseSelection);
     selection.infoWindow(entityManager);

///Move, selection and attack
     for(Entity& i: entityManager.militaryUnits)
     {
         if(i.id == selection.selectedUnitID)   //Comparing the current entity ID in vector with selected unit id(variable in Selection class actionMenu function).
         {
             sf::Vector2f mousePos(sf::Mouse::getPosition());
             //Move button pressed.
             if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && selection.moveIcon.getGlobalBounds().contains(mousePos))
             {
                    i.ptrCMilitaryUnit->movePressed   = true;
                    selection.actionMenuDisplayed     = false;
                    //selection.deselectActionMenuDisplayed();  //deselecting and repositioning action menu sprites
                    i.ptrCMilitaryUnit->attackPressed = false;

                    //sound if unit moved and move button pressed again.
                    if(i.ptrCMilitaryUnit->unitMoved)
                    {
                        soundDenied.play();
                        continue;
                    }

                     continue;
             }
             //Attack button pressed.
             if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && selection.attackIcon.getGlobalBounds().contains(mousePos))
             {
                   selection.baseActionMenuDisplayed = false;
                   selection.baseActionMenuBuild     = false;

                   i.ptrCMilitaryUnit->movePressed   = false;  //If Move selected, reseting bool.
                   movement.pathActive               = false;

                   i.ptrCMilitaryUnit->attackPressed = true;
                   selection.actionMenuDisplayed    = false;
                  // selection.deselectActionMenuDisplayed();

                   //sound if unit moved and move button pressed again.
                   if(i.ptrCMilitaryUnit->unitAttacked)
                   {
                        soundDenied.play();
                        continue;
                   }

                   continue;
              }
              //Repair button pressed
              if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && selection.fortifyIcon.getGlobalBounds().contains(mousePos))
              {
                  //player 1
                  if(entityManager.player1.ptrCplayer->isPlaying && entityManager.player1.ptrCplayer->goldTotal >= 40
                     && !i.ptrCMilitaryUnit->unitMoved && !i.ptrCMilitaryUnit->unitAttacked && i.ptrCMilitaryUnit->health < 5)
                  {
                      selection.actionMenuDisplayed     = false;
                      i.ptrCMilitaryUnit->unitMoved     = true;
                      i.ptrCMilitaryUnit->unitAttacked  = true;

                      entityManager.player1.ptrCplayer->goldTotal = entityManager.player1.ptrCplayer->goldTotal - 40;
                      i.ptrCMilitaryUnit->health = 5;

                      break;
                  }
                  else if(i.ptrCMilitaryUnit->unitMoved || i.ptrCMilitaryUnit->unitAttacked
                          || entityManager.player1.ptrCplayer->goldTotal < 40 || i.ptrCMilitaryUnit->health == 5)
                  {
                      soundDenied.play();
                      continue;
                  }
                  //player 2
                  if(entityManager.player2.ptrCplayer->isPlaying && entityManager.player2.ptrCplayer->goldTotal >= 40
                     && !i.ptrCMilitaryUnit->unitMoved && !i.ptrCMilitaryUnit->unitAttacked && i.ptrCMilitaryUnit->health < 5)
                  {
                      selection.actionMenuDisplayed    = false;
                      i.ptrCMilitaryUnit->unitMoved    = true;
                      i.ptrCMilitaryUnit->unitAttacked = true;

                      entityManager.player2.ptrCplayer->goldTotal = entityManager.player2.ptrCplayer->goldTotal - 40;
                      i.ptrCMilitaryUnit->health = 5;

                      break;
                  }
                  else if(i.ptrCMilitaryUnit->unitMoved || i.ptrCMilitaryUnit->unitAttacked
                          || entityManager.player1.ptrCplayer->goldTotal < 40 || i.ptrCMilitaryUnit->health == 5)
                  {
                      soundDenied.play();
                      continue;
                  }

                  continue;
              }
         }
         if(i.id != selection.selectedUnitID)    //If not choosing any option and clicking on another unit, reset the previous unit bool's.
         {
             i.ptrCMilitaryUnit->movePressed   = false;
             movement.pathActive = false;
             i.ptrCMilitaryUnit->attackPressed = false;
             combat.attackActive = false;
         }
         //Move.
         if(i.ptrCMilitaryUnit->movePressed && !i.ptrCMilitaryUnit->unitMoved)  //Move.
         {
             selection.baseActionMenuDisplayed = false;
             selection.baseActionMenuBuild     = false;

             movement.moveShow(entityManager, i);
             movement.moveUnit(i);

             break;
         }
         //Attack.
         if(i.ptrCMilitaryUnit->attackPressed && !i.ptrCMilitaryUnit->unitAttacked)
         {
             combat.attackShow(entityManager, i);

             combat.attack(entityManager, i);

             break;
         }
         //If unit attacks before moving, no more movement.
         if(i.ptrCMilitaryUnit->unitAttacked)
         {
             i.ptrCMilitaryUnit->unitMoved = true;
         }
     }


///Base Action Menus--
    if(selection.baseActionMenuDisplayed)
    {
        sf::Vector2f mousePos(sf::Mouse::getPosition());
    //End Turn option
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && selection.baseActionMenu[0].getGlobalBounds().contains(mousePos))
        {
            //unit action menu off, repositioning Button sprites outside the map(conflict with sprites that occupy the same space and mouse click, bug)
            selection.deselectActionMenuDisplayed();
            //base action menu off, repositioning Button sprites outside the map(conflict with sprites that occupy the same space and mouse click, bug)
            selection.deselectBaseActionMenyDisplayed();
            //reseting all units
            endTurn(entityManager);
        }
    //Build Units option
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && selection.baseActionMenu[1].getGlobalBounds().contains(mousePos))
        {
            for(Entity& i: entityManager.tilesNonWalkable)
            {
                if(i.tag == "baseGreen" && entityManager.player1.ptrCplayer->isPlaying)
                {
                    selection.baseActionMenuBuild = true;  //displaying 3 new buttons (Infatntry, Artilery, Tank).

                    selection.baseActionMenu[2].setPosition(i.ptrCTransform->position.x + 150, i.ptrCTransform->position.y - 20);
                    selection.baseActionMenu[3].setPosition(i.ptrCTransform->position.x + 150, i.ptrCTransform->position.y + 30);
                    selection.baseActionMenu[4].setPosition(i.ptrCTransform->position.x + 150, i.ptrCTransform->position.y + 80);

                    break;

                }
                else if(i.tag == "baseYellow" && entityManager.player2.ptrCplayer->isPlaying)
                {
                    selection.baseActionMenuBuild = true;  //displaying 3 new buttons (Infatntry, Artilery, Tank).

                    selection.baseActionMenu[2].setPosition(i.ptrCTransform->position.x - 150, i.ptrCTransform->position.y - 230);
                    selection.baseActionMenu[3].setPosition(i.ptrCTransform->position.x - 150, i.ptrCTransform->position.y - 180);
                    selection.baseActionMenu[4].setPosition(i.ptrCTransform->position.x - 150, i.ptrCTransform->position.y - 130);

                    break;

                }
          }
        }
    }

///Choosing unit to build
    if(selection.baseActionMenuBuild)
    {
        //Infantry
        sf::Vector2f mousePos1(sf::Mouse::getPosition());
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && selection.baseActionMenu[2].getGlobalBounds().contains(mousePos1))
        {
            //checking if the active base tile is occupied by another unit
            bool isBaseTileOccupied = false;
            for(Entity& i: entityManager.tilesNonWalkable)
            {
                if(i.ptrCTile->baseActive)
                {
                    for(Entity& j: entityManager.militaryUnits)
                    {
                        sf::Vector2f unitPos(j.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition());
                        if(i.ptrCTile->spriteTile.getGlobalBounds().contains(unitPos))
                        {
                            isBaseTileOccupied = true;
                            soundDenied.play();
                            break;
                        }
                    }

                    if(!isBaseTileOccupied && entityManager.player1.ptrCplayer->isPlaying && entityManager.player1.ptrCplayer->ironTotal >= 40)
                    {
                        entityManager.createEntity("infantryGreen", sf::Vector2f(i.ptrCTransform->position));
                        entityManager.player1.ptrCplayer->unitsTotal = entityManager.player1.ptrCplayer->unitsTotal + 1;
                        entityManager.player1.ptrCplayer->ironTotal  = entityManager.player1.ptrCplayer->ironTotal - 40;
                        selection.deselectBaseActionMenyDisplayed();
                        break;
                    }
                    else if(!isBaseTileOccupied && entityManager.player1.ptrCplayer->isPlaying && entityManager.player1.ptrCplayer->ironTotal < 40)
                    {
                        soundDenied.play();
                        break;
                    }

                    if(!isBaseTileOccupied && entityManager.player2.ptrCplayer->isPlaying && entityManager.player2.ptrCplayer->ironTotal >= 40)
                    {
                        entityManager.createEntity("infantryYellow", sf::Vector2f(i.ptrCTransform->position));
                        entityManager.militaryUnits.back().isActive = true;
                        entityManager.player2.ptrCplayer->unitsTotal = entityManager.player2.ptrCplayer->unitsTotal + 1;
                        entityManager.player2.ptrCplayer->ironTotal  = entityManager.player2.ptrCplayer->ironTotal - 40;
                        selection.deselectBaseActionMenyDisplayed();
                        break;
                    }
                    else if(!isBaseTileOccupied && entityManager.player2.ptrCplayer->isPlaying && entityManager.player2.ptrCplayer->ironTotal < 40)
                    {
                        soundDenied.play();
                        break;
                    }
                }
            }
          }
          //Artilery
          sf::Vector2f mousePos2(sf::Mouse::getPosition());
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && selection.baseActionMenu[3].getGlobalBounds().contains(mousePos2))
        {
            //checking if the active base tile is occupied by another unit
            bool isBaseTileOccupied = false;
            for(Entity& i: entityManager.tilesNonWalkable)
            {
                if(i.ptrCTile->baseActive)
                {
                    for(Entity& j: entityManager.militaryUnits)
                    {
                        sf::Vector2f unitPos(j.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition());
                        if(i.ptrCTile->spriteTile.getGlobalBounds().contains(unitPos))
                        {
                            isBaseTileOccupied = true;
                            soundDenied.play();
                            break;
                        }
                    }

                    if(!isBaseTileOccupied && entityManager.player1.ptrCplayer->isPlaying && entityManager.player1.ptrCplayer->ironTotal >= 60)
                    {
                        entityManager.createEntity("artileryGreen", sf::Vector2f(i.ptrCTransform->position));
                        entityManager.player1.ptrCplayer->unitsTotal = entityManager.player1.ptrCplayer->unitsTotal + 1;
                        entityManager.player1.ptrCplayer->ironTotal  = entityManager.player1.ptrCplayer->ironTotal - 60;
                        selection.deselectBaseActionMenyDisplayed();
                        break;
                    }
                    else if(!isBaseTileOccupied && entityManager.player1.ptrCplayer->isPlaying && entityManager.player1.ptrCplayer->ironTotal < 60)
                    {
                        soundDenied.play();
                        break;
                    }

                    if(!isBaseTileOccupied && entityManager.player2.ptrCplayer->isPlaying && entityManager.player2.ptrCplayer->ironTotal >= 60)
                    {
                        entityManager.createEntity("artileryYellow", sf::Vector2f(i.ptrCTransform->position));
                        entityManager.militaryUnits.back().isActive = true;
                        entityManager.player2.ptrCplayer->unitsTotal = entityManager.player2.ptrCplayer->unitsTotal + 1;
                        entityManager.player2.ptrCplayer->ironTotal  = entityManager.player2.ptrCplayer->ironTotal - 60;
                        selection.deselectBaseActionMenyDisplayed();
                        break;
                    }
                    else if(!isBaseTileOccupied && entityManager.player2.ptrCplayer->isPlaying && entityManager.player2.ptrCplayer->ironTotal < 60)
                    {
                        soundDenied.play();
                        break;
                    }
                }
            }
          }
        //Tank
        sf::Vector2f mousePos3(sf::Mouse::getPosition());
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && selection.baseActionMenu[4].getGlobalBounds().contains(mousePos3))
        {
            //checking if the active base tile is occupied by another unit
            bool isBaseTileOccupied = false;
            for(Entity& i: entityManager.tilesNonWalkable)
            {
                if(i.ptrCTile->baseActive)
                {
                    for(Entity& j: entityManager.militaryUnits)
                    {
                        sf::Vector2f unitPos(j.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition());
                        if(i.ptrCTile->spriteTile.getGlobalBounds().contains(unitPos))
                        {
                            isBaseTileOccupied = true;
                            soundDenied.play();
                            break;
                        }
                    }

                    if(!isBaseTileOccupied && entityManager.player1.ptrCplayer->isPlaying && entityManager.player1.ptrCplayer->ironTotal >= 80)
                    {
                        entityManager.createEntity("tankGreen", sf::Vector2f(i.ptrCTransform->position));
                        entityManager.player1.ptrCplayer->unitsTotal = entityManager.player1.ptrCplayer->unitsTotal + 1;
                        entityManager.player1.ptrCplayer->ironTotal  = entityManager.player1.ptrCplayer->ironTotal - 80;
                        selection.deselectBaseActionMenyDisplayed();
                        break;
                    }
                    else if(!isBaseTileOccupied && entityManager.player1.ptrCplayer->isPlaying && entityManager.player1.ptrCplayer->ironTotal < 80)
                    {
                        soundDenied.play();
                        break;
                    }

                    if(!isBaseTileOccupied && entityManager.player2.ptrCplayer->isPlaying && entityManager.player2.ptrCplayer->ironTotal >= 80)
                    {
                        entityManager.createEntity("tankYellow", sf::Vector2f(i.ptrCTransform->position));
                        entityManager.militaryUnits.back().isActive = true;
                        entityManager.player2.ptrCplayer->unitsTotal = entityManager.player2.ptrCplayer->unitsTotal + 1;
                        entityManager.player2.ptrCplayer->ironTotal  = entityManager.player2.ptrCplayer->ironTotal - 80;
                        selection.deselectBaseActionMenyDisplayed();
                        break;
                    }
                    else if(!isBaseTileOccupied && entityManager.player2.ptrCplayer->isPlaying && entityManager.player2.ptrCplayer->ironTotal < 80)
                    {
                        soundDenied.play();
                        break;
                    }
                }
            }
          }
    }

///When the combat window is open, selection of units is disabled.
     if(combat.combatWindowActive)
         {
             selection.selectionActive = false;
             combat.combatWindowClose();
         }
         else if(!combat.combatWindowActive)
         {
             selection.selectionActive = true;
         }

///Conquering mines
     for(Entity& i: entityManager.tilesNonWalkable)
     {
         //iron mine1
         if(i.tag == "ironMine")
         {
             for(Entity& y: entityManager.militaryUnits)
             {
                 if(y.tag == "infantryGreen" || y.tag == "artileryGreen" || y.tag == "tankGreen")
                 {
                     if(i.ptrCTile->spriteTile.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && !i.ptrCTile->mineOwnedByPlayer1 )
                     {
                         i.ptrCTile->mineOwnedByPlayer1 = true;

                         entityManager.player1.ptrCplayer->minesTotal = entityManager.player1.ptrCplayer->minesTotal + 1;
                         if(i.ptrCTile->mineOwnedByPlayer2)
                         {
                             entityManager.player2.ptrCplayer->minesTotal = entityManager.player2.ptrCplayer->minesTotal - 1;
                             i.ptrCTile->mineOwnedByPlayer2 = false;
                         }
                         else
                         {
                             continue;
                         }
                     }
                 }
                else if(y.tag == "infantryYellow" || y.tag == "artileryYellow" || y.tag == "tankYellow")
                {
                     if(i.ptrCTile->spriteTile.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()) && !i.ptrCTile->mineOwnedByPlayer2)
                     {
                         i.ptrCTile->mineOwnedByPlayer2 = true;

                         entityManager.player2.ptrCplayer->minesTotal = entityManager.player2.ptrCplayer->minesTotal + 1;
                         if(i.ptrCTile->mineOwnedByPlayer1)
                         {
                             entityManager.player1.ptrCplayer->minesTotal = entityManager.player1.ptrCplayer->minesTotal - 1;
                             i.ptrCTile->mineOwnedByPlayer1 = false;
                         }
                         else
                         {
                             continue;
                         }
                     }
                }
             }
          }
         //gold mine
         if(i.tag == "goldMine")
         {
             for(Entity& y: entityManager.militaryUnits)
             {
                 if(y.destroyed)
                 {
                     continue;
                 }
                 else if(y.tag == "infantryGreen" || y.tag == "artileryGreen" || y.tag == "tankGreen")
                 {
                     if(i.ptrCTile->spriteTile.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()))
                     {
                         entityManager.player2.ptrCResources->goldMine = false;
                         entityManager.player1.ptrCResources->goldMine = true;
                     }
                 }
                else if(y.tag == "infantryYellow" || y.tag == "artileryYellow" || y.tag == "tankYellow")
                {
                     if(i.ptrCTile->spriteTile.getGlobalBounds().contains(y.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()))
                     {
                         entityManager.player1.ptrCResources->goldMine = false;
                         entityManager.player2.ptrCResources->goldMine = true;
                     }
                }

             }
          }
     }


///Victory- Enemy Base conquered. Unit needs to be 2 turns on the tile of the enemy base to win
     for(Entity& i: entityManager.tilesNonWalkable)
     {
         if(i.tag == "baseGreen")
         {
             for(Entity& j: entityManager.militaryUnits)
             {
                 if(j.tag == "infantryYellow" || j.tag == "artileryYellow" || j.tag == "tankYellow")
                 {
                     if(i.ptrCTile->spriteTile.getGlobalBounds().contains(j.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()))
                     {
                         baseGreenOccupied = true;
                         unitYellowID      = j.id;
                         break;
                     }
                     else if((j.id == unitYellowID && !i.ptrCTile->spriteTile.getGlobalBounds().contains(j.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()))
                             || j.destroyed) //If unit no more on base tile or destroyed, reset all values.
                     {
                         baseGreenOccupied  = false;
                         baseGreenCounter   = 0;
                     }
                 }
             }
         }
         else if(i.tag == "baseYellow")
         {
             for(Entity& j: entityManager.militaryUnits)
             {
                 if(j.tag == "infantryGreen" || j.tag == "artileryGreen" || j.tag == "tankGreen")
                 {
                     if(i.ptrCTile->spriteTile.getGlobalBounds().contains(j.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()))
                     {
                         baseYellowOccupied = true;
                         unitGreenID       = j.id;
                         break;
                     }
                     else if((j.id == unitGreenID && !i.ptrCTile->spriteTile.getGlobalBounds().contains(j.ptrCMilitaryUnit->spriteMilitaryUnit.getPosition()))
                             || j.destroyed) //If unit no more on base tile or destroyed, reset all values.
                     {
                         baseYellowOccupied  = false;
                         baseYellowCounter   = 0;
                     }
                 }
             }
         }
     }



///RENDERING

       window.clear(sf::Color::Black);
       window.draw(mapSprite);

       for(Entity& i: entityManager.tilesNonWalkable)  //Non-walkable tiles.
       {
           window.draw(i.ptrCTile->spriteTile);
       }

       for(Entity& i: entityManager.militaryUnits)   //Military units + health bar.
       {
           if(!i.destroyed)
           {
               window.draw(i.ptrCMilitaryUnit->spriteMilitaryUnit);
               for(unsigned short int y=0; y < i.ptrCMilitaryUnit->health; ++y)
               {
                   window.draw(i.ptrCHealth->healthBar[y]);
               }
           }
       }

       movement.draw(window);         //Movement mechanics

       selection.draw(window);        //Action menu and Info Window update.

       combat.draw(window);           //Combat window update.

       //Victory Window   -- introducing a bool winPlayer1Display will solve the problem of this being here
     if(baseGreenCounter == 3)
     {
          selection.selectionActive = false;
          soundVictory.play();
          winPlayer2.setPosition(610,300);
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
         {
             gameWindow = false;
         }
          window.draw(winPlayer2);

         //ubaci takodje neki sound
     }
     else if(baseYellowCounter == 3)
     {
         selection.selectionActive = false;
         soundVictory.play();
         winPlayer1.setPosition(610,300);
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
         {
             gameWindow = false;
         }
         window.draw(winPlayer1);

         //ubaci takodje neki sound
     }
     //In game menu
     if(inGameMenuDisplay)
       {
           window.draw(inGameMenu);
           window.draw(menuText1);
           window.draw(menuText2);
           window.draw(menuText3);
           window.draw(menuText4);
           window.draw(menuText5);
           window.draw(menuText6);
       }


       window.display();
     }

}



///Initialization- Start New Game
void Game::initialization(EntityManager& manager)
{

    //manager.createEntity("player1"); ----Pleyeri se kreiraju samo jednom u Game, i posle se samo njihove vrenosti resetuju na default kad treba, ne prave se ponovo. Sve ostalo se kreira ponovo.
    //manager.createEntity("player2");
    manager.createEntity("infantryGreen",  sf::Vector2f(162,190));
    manager.createEntity("tankYellow",     sf::Vector2f(1860,890));
    manager.createEntity("tankGreen",      sf::Vector2f(62,190));
    manager.createEntity("infantryYellow", sf::Vector2f(1760,890));
    manager.createEntity("artileryGreen",  sf::Vector2f(162,90));
    manager.createEntity("artileryYellow", sf::Vector2f(1760,990));
    manager.createEntity("baseGreen",      sf::Vector2f(62,90));
    manager.createEntity("baseYellow",     sf::Vector2f(1862,990));
    manager.createEntity("volcano1",       sf::Vector2f(1262,590));
    manager.createEntity("volcano2",       sf::Vector2f(762,890));
    manager.createEntity("volcano2",       sf::Vector2f(662,390));
    manager.createEntity("goldMine",       sf::Vector2f(962,390));
    manager.createEntity("ironMine",       sf::Vector2f(362,790));
    manager.createEntity("ironMine",       sf::Vector2f(1562,290));
//    manager.createEntity("mountain",       sf::Vector2f((962+50),590));
//    manager.createEntity("unknown",        sf::Vector2f(862,90));
    manager.createEntity("greatVolcano1",  sf::Vector2f(865,490));
    manager.createEntity("greatVolcano2",  sf::Vector2f(960,490));
    manager.createEntity("greatVolcano3",  sf::Vector2f(960,581));
    manager.createEntity("greatVolcano4",  sf::Vector2f(865,581));
}



///End Turn
void Game::endTurn(EntityManager& manager)
{
//reseting player status from playing to not playing and vice versa.
    if(manager.player1.ptrCplayer->isPlaying)
        manager.player1.ptrCplayer->isPlaying = false;
    else if(!manager.player1.ptrCplayer->isPlaying)
        manager.player1.ptrCplayer->isPlaying = true;
    if(manager.player2.ptrCplayer->isPlaying)
        manager.player2.ptrCplayer->isPlaying = false;
    else if(!manager.player2.ptrCplayer->isPlaying)
        manager.player2.ptrCplayer->isPlaying = true;
//if player owns a mine, add income
    //iron mine
    if( manager.player1.ptrCplayer->isPlaying)
        manager.player1.ptrCplayer->ironTotal = manager.player1.ptrCplayer->ironTotal + (manager.player1.ptrCResources->ironIncome * manager.player1.ptrCplayer->minesTotal);
    if( manager.player2.ptrCplayer->isPlaying)
        manager.player2.ptrCplayer->ironTotal = manager.player2.ptrCplayer->ironTotal + (manager.player2.ptrCResources->ironIncome * manager.player2.ptrCplayer->minesTotal);
    //gold mine
    if(manager.player1.ptrCResources->goldMine && manager.player1.ptrCplayer->isPlaying)
        manager.player1.ptrCplayer->goldTotal = manager.player1.ptrCplayer->goldTotal + manager.player1.ptrCResources->goldIncome;
    else if(manager.player2.ptrCResources->goldMine && manager.player2.ptrCplayer->isPlaying)
        manager.player2.ptrCplayer->goldTotal = manager.player2.ptrCplayer->goldTotal + manager.player2.ptrCResources->goldIncome;
//If base is conquered, start turn counter
    if(baseGreenOccupied && manager.player2.ptrCplayer->isPlaying)
    {
        baseGreenCounter = baseGreenCounter + 1;
    }
    if(baseYellowOccupied && manager.player1.ptrCplayer->isPlaying)
    {
        baseYellowCounter = baseYellowCounter + 1;
    }
//reseting military units
    for(Entity& i: manager.militaryUnits)
    {
        //If unit was active then false, if not then active.
        if(i.isActive)
            i.isActive = false;
        else if(!i.isActive)
            i.isActive = true;
        //if move pressed
        if(i.ptrCMilitaryUnit->movePressed)
            i.ptrCMilitaryUnit->movePressed = false;
        //if unit moved, reset the movement posibility
        if(i.ptrCMilitaryUnit->unitMoved)
            i.ptrCMilitaryUnit->unitMoved = false;
        if(i.ptrCMilitaryUnit->attackPressed)
            i.ptrCMilitaryUnit->attackPressed = false;
        if(i.ptrCMilitaryUnit->unitAttacked)
            i.ptrCMilitaryUnit->unitAttacked = false;
        //reseting the movement value to default value if the unit has been moved during turn.
        i.ptrCMilitaryUnit->movementRange = i.ptrCMilitaryUnit->movementRangeDefault;
    }
    for(Entity& j: manager.tilesNonWalkable)
    {
        //if base was active then inactive, and vice versa
        if(j.tag == "baseGreen" || j.tag == "baseYellow")
        {
            if(j.ptrCTile->baseActive)
                j.ptrCTile->baseActive = false;
            else if(!j.ptrCTile->baseActive)
                j.ptrCTile->baseActive = true;
        }
    }
}


///Save Game
void Game::saveGame(EntityManager& manager, const MSelection& selection) const
{
    std::ofstream saving;
    saving.open("assetSaveGame/save.txt");

    //Player1 components
    saving << manager.player1.tag << " " << manager.player1.id << " "
           << manager.player1.ptrCplayer->isPlaying << " " << manager.player1.ptrCplayer->unitsTotal << " " << manager.player1.ptrCplayer->ironTotal
           << " " << manager.player1.ptrCplayer->goldTotal << " " << manager.player1.ptrCplayer->baseOccupied
           << " " << manager.player1.ptrCResources->ironMine << " " << manager.player1.ptrCResources->goldMine << " "
           << baseGreenOccupied << " " << baseGreenCounter << " "
           << manager.player1.isActive << " " << manager.player1.destroyed << " "
           << manager.player1.ptrCplayer->minesTotal << "\n";
    //Player2 components
    saving << manager.player2.tag << " " << manager.player2.id << " "
           << manager.player2.ptrCplayer->isPlaying << " " << manager.player2.ptrCplayer->unitsTotal << " " << manager.player2.ptrCplayer->ironTotal
           << " " << manager.player2.ptrCplayer->goldTotal << " " << manager.player2.ptrCplayer->baseOccupied
           << " " << manager.player2.ptrCResources->ironMine << " " << manager.player2.ptrCResources->goldMine << " "
           << baseYellowOccupied << " " << baseYellowCounter << " "
           << manager.player2.isActive << " " << manager.player2.destroyed << " "
           << manager.player2.ptrCplayer->minesTotal << "\n";
    //Selection- if mine occupied, show player color
    saving << selection.ironMineOwnerColorDisplay << " " << selection.goldMineOwnerColorDisplay << "\n";
    //Military unit components
    for(Entity& i: manager.militaryUnits)
    {
        saving << i.tag << " " << i.ptrCTransform->position.x << " " << i.ptrCTransform->position.y << " "
               << i.id << " " << i.isActive << " " << i.destroyed << " "
               << i.ptrCTransform->spriteSize.x << " " << i.ptrCTransform->spriteSize.y << " "
               << i.ptrCTransform->spriteHalfSize.x << " " << i.ptrCTransform->spriteHalfSize.y << " "
               << i.ptrCMilitaryUnit->movePressed << " " << i.ptrCMilitaryUnit->unitMoved << " " << i.ptrCMilitaryUnit->attackPressed << " " << i.ptrCMilitaryUnit->unitAttacked << " "
               << i.ptrCMilitaryUnit->health << " " << i.ptrCMilitaryUnit->movementRange << " " << i.ptrCMilitaryUnit->shootingRange << " "
               << i.ptrCSpecial->rankLevel << "\n";
    }
    //Bases, mines, volcanos
    for(Entity& j: manager.tilesNonWalkable)
    {
        saving << j.tag << " " << j.ptrCTransform->position.x << " " << j.ptrCTransform->position.y << " "
               << j.id << " "
               << j.ptrCTransform->spriteSize.x << " " << j.ptrCTransform->spriteSize.y << " " << j.ptrCTransform->spriteHalfSize.x << " " << j.ptrCTransform->spriteHalfSize.y << " "
               << j.ptrCTile->baseActive << " " << j.ptrCTile->isWalkable << " "
               << j.ptrCTile->mineOwnedByPlayer1 << " " << j.ptrCTile->mineOwnedByPlayer2 << "\n";
    }

    saving.close();
}


///Load Game
void Game::loadGame(EntityManager& manager, MSelection& selection, MMovement& movement, MCombat& combat)
{
    manager.militaryUnits.clear();    //deleting all units from map.
    manager.tilesNonWalkable.clear();  //deleting all non-walkables.

    selection.actionMenuDisplayed     = false;
    selection.infoWindowDisplayed     = false;
    selection.infoBaseWindowDisplayed = false;
    selection.baseActionMenuDisplayed = false;
    selection.baseActionMenuBuild     = false;
    movement.pathActive               = false;
    combat.attackActive               = false;

    std::string inputLine;
    unsigned short totalNumberOfUnits = 0;   //Counts all the units that exist in the save file. Used to start reading non-walkable tiles from the point where units end.
    std::string tag;
    int id, health;
    bool /*isPlaying, baseOccupied,*/ baseActive, mineOwnedByPlayer1, mineOwnedByPlayer2, isActive, destroyed, movePressed, unitMoved, attackPressed, unitAttacked, isWalkable;
    unsigned short int /*unitsTotal, ironTotal, goldTotal,*/ movementRange, shootingRange, rankLevel;
    sf::Vector2f position;
    sf::Vector2f spriteSize;
    sf::Vector2f spriteHalfSize;

    std::ifstream load;
    load.open("assetSaveGame/save.txt");

//player1 loading
    std::getline(load, inputLine);
    std::istringstream stringByString1(inputLine);

    while(stringByString1 >> manager.player1.tag >> manager.player1.id >> manager.player1.ptrCplayer->isPlaying >> manager.player1.ptrCplayer->unitsTotal >> manager.player1.ptrCplayer->ironTotal
                          >> manager.player1.ptrCplayer->goldTotal >> manager.player1.ptrCplayer->baseOccupied
                          >> manager.player1.ptrCResources->ironMine >> manager.player1.ptrCResources->goldMine >> baseGreenOccupied >> baseGreenCounter
                          >> manager.player1.isActive >> manager.player1.destroyed
                          >> manager.player1.ptrCplayer->minesTotal)
    {
        break;
    }
//player2 loading
    std::getline(load, inputLine);
    std::istringstream stringByString2(inputLine);

    while(stringByString2 >> manager.player2.tag >> manager.player2.id >> manager.player2.ptrCplayer->isPlaying >> manager.player2.ptrCplayer->unitsTotal >> manager.player2.ptrCplayer->ironTotal
                          >> manager.player2.ptrCplayer->goldTotal >> manager.player2.ptrCplayer->baseOccupied
                          >> manager.player2.ptrCResources->ironMine >> manager.player2.ptrCResources->goldMine >> baseGreenOccupied >> baseGreenCounter
                          >> manager.player2.isActive >> manager.player2.destroyed
                          >> manager.player2.ptrCplayer->minesTotal)
    {
        break;
    }
//Selection- if mine occupied, show player color
    std::getline(load, inputLine);
    std::istringstream stringByString3(inputLine);

    while(stringByString3 >> selection.ironMineOwnerColorDisplay >> selection.goldMineOwnerColorDisplay )
    {
        break;
    }
//military units loading
    if(load)
    {
        while(std::getline(load, inputLine))
        {
            std::istringstream stringByString4(inputLine);
            while(stringByString4 >> tag >> position.x >> position.y >> id >> isActive >> destroyed >> spriteSize.x >> spriteSize.y >> spriteHalfSize.x >> spriteHalfSize.y
                                  >> movePressed >> unitMoved >> attackPressed >> unitAttacked >> health >> movementRange >> shootingRange >> rankLevel)
            {
                if(tag == "infantryGreen" || tag == "artileryGreen" || tag == "tankGreen" || tag == "infantryYellow" || tag == "artileryYellow" || tag == "tankYellow")
                {
                    totalNumberOfUnits = totalNumberOfUnits + 1;
                    manager.createEntity(tag, position);
                    manager.militaryUnits.back().tag = tag;
                    manager.militaryUnits.back().ptrCTransform->position = position;
                    manager.militaryUnits.back().id = id;
                    manager.militaryUnits.back().isActive = isActive;
                    manager.militaryUnits.back().destroyed = destroyed;
                    manager.militaryUnits.back().ptrCTransform->spriteSize = spriteSize;
                    manager.militaryUnits.back().ptrCTransform->spriteHalfSize = spriteHalfSize;
                    manager.militaryUnits.back().ptrCMilitaryUnit->movePressed = movePressed;
                    manager.militaryUnits.back().ptrCMilitaryUnit->unitMoved = unitMoved;
                    manager.militaryUnits.back().ptrCMilitaryUnit->attackPressed = attackPressed;
                    manager.militaryUnits.back().ptrCMilitaryUnit->unitAttacked = unitAttacked;
                    manager.militaryUnits.back().ptrCMilitaryUnit->health = health;
                    manager.militaryUnits.back().ptrCMilitaryUnit->movementRange = movementRange;
                    manager.militaryUnits.back().ptrCMilitaryUnit->shootingRange = shootingRange;
                    manager.militaryUnits.back().ptrCSpecial->rankLevel = rankLevel;

                    //manualy addapting dices to units rank
                    if(rankLevel == 2 && !destroyed)
                    {
                        manager.militaryUnits.back().ptrCSpecial->whiteDice1 = false;  //+1 red dice (total 1)

                        combat.combatWindowVec[6].setPosition(combat.combatWindowVec[1].getPosition().x - 25, combat.combatWindowVec[1].getPosition().y -40);
                    }
                    else if(rankLevel == 3 && !destroyed)
                    {
                        manager.militaryUnits.back().ptrCSpecial->whiteDice1 = false;  //+1 red dice (total 1)
                        manager.militaryUnits.back().ptrCSpecial->whiteDice2 = false;  //+1 red dice (total 2)

                        combat.combatWindowVec[6].setPosition(combat.combatWindowVec[1].getPosition().x - 25, combat.combatWindowVec[1].getPosition().y -40);
                    }
                    else if(rankLevel == 4 && !destroyed)
                    {
                        manager.militaryUnits.back().ptrCSpecial->whiteDice1 = false;  //+1 red dice (total 1)
                        manager.militaryUnits.back().ptrCSpecial->whiteDice2 = false;  //+1 red dice (total 2)
                        manager.militaryUnits.back().ptrCSpecial->whiteDice3 = false;   //+1 red dice (total 3)

                        combat.combatWindowVec[6].setPosition(combat.combatWindowVec[1].getPosition().x - 25, combat.combatWindowVec[1].getPosition().y -40);
                    }
                }
                else
                {
                    break;
                }

            }
        }
    }
//Non-walkable tiles- bases, mines, volcanos
    load.clear();                  //clearing the EOF flag.
    load.seekg(0, std::ios::beg);  //returning to the beggining of the file.
    for(unsigned short i=0; i < (totalNumberOfUnits +3); ++i)   //skipping all the military units and start reading the non-walkable entities that come after.
    {
        load.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(load)
    {
        while(std::getline(load, inputLine))
        {
            std::istringstream stringByString5(inputLine);
            while(stringByString5 >> tag >> position.x >> position.y >> id >> spriteSize.x >> spriteSize.y >> spriteHalfSize.x >> spriteHalfSize.y
                                  >> baseActive >> isWalkable >> mineOwnedByPlayer1 >> mineOwnedByPlayer2)
            {
                manager.createEntity(tag, position);
                manager.tilesNonWalkable.back().id = id;
                manager.tilesNonWalkable.back().ptrCTransform->spriteSize = spriteSize;
                manager.tilesNonWalkable.back().ptrCTransform->spriteHalfSize = spriteHalfSize;
                manager.tilesNonWalkable.back().ptrCTile->baseActive = baseActive;
                manager.tilesNonWalkable.back().ptrCTile->isWalkable = isWalkable;
                manager.tilesNonWalkable.back().ptrCTile->mineOwnedByPlayer1 = mineOwnedByPlayer1;
                manager.tilesNonWalkable.back().ptrCTile->mineOwnedByPlayer2 = mineOwnedByPlayer2;
            }
        }
    }

    load.close();
}


///Restart Game
void Game::restartGame(EntityManager& manager, MSelection& selection, MMovement& movement, MCombat& combat)
{
    //deleting all existing entities
    manager.militaryUnits.clear();
    manager.tilesNonWalkable.clear();
    //creating new entities
    initialization(manager);
    ///NAPRAVI SAMO INICIJALIZATION FILE I OVDE GA UCITAJ KAKO BI POSTAVIO SVE JEDINICE i NON-WALKABLES NA SVOJE MESTO.
    ///POSTAVI SVE MOGUCE BOOLOVE NA DEFAULT VREDNOSTI.
    //player1 restart
    manager.player1.isActive = true;
    manager.player1.ptrCplayer->baseOccupied = false;
    manager.player1.ptrCplayer->goldTotal    = 0;
    manager.player1.ptrCplayer->ironTotal    = 0;
    manager.player1.ptrCplayer->isPlaying    = true;
    manager.player1.ptrCplayer->unitsTotal   = 3;
    manager.player1.ptrCResources->goldMine  = false;
    manager.player1.ptrCResources->ironMine  = false;
    manager.player1.ptrCplayer->minesTotal   = 0;
    //player2 restart
    manager.player2.isActive = false;
    manager.player2.ptrCplayer->baseOccupied = false;
    manager.player2.ptrCplayer->goldTotal = 0;
    manager.player2.ptrCplayer->ironTotal = 0;
    manager.player2.ptrCplayer->isPlaying = false;
    manager.player2.ptrCplayer->unitsTotal = 3;
    manager.player2.ptrCResources->goldMine = false;
    manager.player2.ptrCResources->ironMine = false;
    manager.player2.ptrCplayer->minesTotal  = 0;
    //base occupied restart
    baseGreenOccupied  = false;
    baseGreenCounter   = 0;
    baseYellowOccupied = false;
    baseYellowCounter  = 0;
    //Selection- if mine occupied, show player color
    selection.actionMenuDisplayed       = false;
    selection.baseActionMenuBuild       = false;
    selection.baseActionMenuDisplayed   = false;
    selection.goldMineOwnerColorDisplay = false;
    selection.ironMineOwnerColorDisplay = false;
    selection.selectionActive           = true;
    //combat restart
    combat.attackActive = false;
    combat.combatWindowActive = false;
    combat.promotionWindow    = false;
    //movement restart
    movement.pathActive = false;
}













