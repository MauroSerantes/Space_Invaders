#ifndef SPACEINVADERSGAMESTATUSCONTROLLER_H_INCLUDED
#define SPACEINVADERSGAMESTATUSCONTROLLER_H_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#define DOWN_TO_EARTH_FLAG bool
#define PLAYER_DESTRUCTION_FLAG bool 


typedef void (*SIGameStatusController);

SIGameStatusController   siController_init(void);
DOWN_TO_EARTH_FLAG       siController_movementOfEnemies(SIGameStatusController si,uint64_t externalClock);
void                     siController_movementOfEnemiesLaser(SIGameStatusController si,uint64_t externalClock);
void                     siController_movementOfPlayer(SIGameStatusController si,char command,uint16_t* externalClockForShoot);
void                     siController_updateBattleField(SIGameStatusController si);
uint16_t                 siController_updateNumberOfEnemies(SIGameStatusController si);    
PLAYER_DESTRUCTION_FLAG  siController_checkPlayerStatus(SIGameStatusController si);  
void                     siController_showCurrentStatusOfBattlefield(SIGameStatusController si);

#include "SpaceInvaders_GameStatusController.c"
#endif