#ifndef SPACEINVADERSDATASTRUCTURESANDVARIABLES_H_INCLUDED
#define SPACEINVADERSDATASTRUCTURESANDVARIABLES_H_INCLUDED
#include <stdint.h>
#include <stdbool.h>

typedef void (*SpInvData);

SpInvData     spInv_Data_initialization(uint16_t height,uint16_t width);
uint16_t      spInv_Data_getCurrentAmountOfEnemies(SpInvData data);
uint16_t      spInv_Data_getTotalAmountOfEnemies(SpInvData data);
char          spInv_Data_getNormalEnemyToken(SpInvData data);
char          spInv_Data_getShieldEnemyToken(SpInvData data);
char          spInv_Data_getEnemyLaserToken(SpInvData data);
char          spInv_Data_getPlayerToken(SpInvData data);
char          spInv_Data_getPlayerLaser(SpInvData data);
char          spInv_Data_getExplosionToken(SpInvData data);
char          spInv_Data_getEmptySpaceToken(SpInvData data);
void          spInv_Data_changeToExplosionStatus(SpInvData data,uint16_t position_i,uint16_t position_j); //this mean destruction;
char          spInv_Data_getTokenElementFromPosition(SpInvData data,uint16_t position_i,uint16_t position_j);
void          spInv_Data_changeTokenFromPosition(SpInvData data,uint16_t position_i,uint16_t position_j,char token);
void          spInv_Data_changeElementPosition(SpInvData data,uint16_t actual_i,uint16_t actual_j,uint16_t new_i,uint16_t new_j);
void          spInv_Data_traverseSpace(SpInvData data,bool (*doSomething)(char tok,uint16_t posX,uint16_t posY,void* ctx),void* contextVariable);
void          spInv_Data_traverseSpaceReverse(SpInvData data,bool (*doSomething)(char tok,uint16_t posX,uint16_t posY,void* ctx),void* contextVariable);

#include "SpaceInvaders_DataStructuresAndVariables.c"

#endif