#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

/*
void Menu::saveGame(EntityManager& manager, const Game game) const
{
    std::ofstream saving;
    saving.open("assetSaveGame/save.txt");

    //Player1 components
    saving << manager.player1.ptrCplayer->isPlaying << " " << manager.player1.ptrCplayer->unitsTotal << " " << manager.player1.ptrCplayer->ironTotal
           << " " << manager.player1.ptrCplayer->goldTotal << " " << manager.player1.ptrCplayer->baseOccupied
           << " " << manager.player1.ptrCResources->ironMine << " " << manager.player1.ptrCResources->goldMine << " "
           << game.baseGreenOccupied << " " << game.baseGreenCounter << " " << manager.player1.tag << " " << manager.player1.id << "\n";
    //Player2 components
    saving << manager.player2.ptrCplayer->isPlaying << " " << manager.player2.ptrCplayer->unitsTotal << " " << manager.player2.ptrCplayer->ironTotal
           << " " << manager.player2.ptrCplayer->goldTotal << " " << manager.player2.ptrCplayer->baseOccupied
           << " " << manager.player1.ptrCResources->ironMine << " " << manager.player1.ptrCResources->goldMine << " "
           << game.baseYellowOccupied << " " << game.baseYellowCounter << " " << manager.player1.tag << " " << manager.player1.id << "\n";
    //Military unit components
    for(Entity& i: manager.militaryUnits)
    {
        saving << i.tag << " " << i.id << " " << i.ptrCTransform->position.x << " " << i.ptrCTransform->position.y << " "
               << i.ptrCTransform->spriteSize.x << " " << i.ptrCTransform->spriteSize.y << " "
               << i.ptrCTransform->spriteHalfSize.x << " " << i.ptrCTransform->spriteHalfSize.y << " "
               << i.ptrCMilitaryUnit->movePressed << " " << i.ptrCMilitaryUnit->unitMoved << " " << i.ptrCMilitaryUnit->attackPressed << " " << i.ptrCMilitaryUnit->unitAttacked << " "
               << i.ptrCMilitaryUnit->health << " " << i.ptrCMilitaryUnit->movementRange << " " << i.ptrCMilitaryUnit->shootingRange << " "
               << i.ptrCSpecial->rankLevel << "\n";
    }
    //Bases, mines, volcanos
    for(Entity& j: manager.tilesNonWalkable)
    {
        saving << j.tag << " " << j.id << " " << j.ptrCTransform->position.x << " " << j.ptrCTransform->position.y << " "
               << j.ptrCTransform->spriteSize.x << " " << j.ptrCTransform->spriteSize.y << " " << j.ptrCTransform->spriteHalfSize.x << " " << j.ptrCTransform->spriteHalfSize.y << " "
               << j.ptrCTile->baseActive << " " << j.ptrCTile->isWalkable << "\n";
    }
}*/












