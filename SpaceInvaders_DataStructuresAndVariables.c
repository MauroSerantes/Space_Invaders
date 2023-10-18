#include <stdlib.h>
#include <stdio.h>
#include "SpaceInvaders_DataStructuresAndVariables.h"

typedef struct _sp_inv_data{
    // battlefield;
    char** battleSpace;
    uint16_t width;
    uint16_t height;

    // enemies variables.
    char normalEnemyToken;
    char shieldEnemyToken;
    char enemyLaserToken;
    uint16_t currentAmountOfEnemies;
    uint16_t totalAmoutOfEnemies;

    //player variables.
    char playerToken;
    char playerLaser;

    //generic variable
    char explosionToken;
}SpInv_data;


SpInvData spInv_Data_initialization(uint16_t height,uint16_t width){
    SpInv_data*  data = (SpInv_data*) malloc (sizeof(SpInv_data));
    
    if(data != NULL){
         //init variables.
         data->width = width;
         data->height = height;
         data->battleSpace = (char**) malloc(height*sizeof(char*));
         
         for(uint16_t i=0;i<height;i++){
            data->battleSpace[i] = (char*) malloc (width*sizeof(char));
         }
         
         data->normalEnemyToken = 'M';
         data->shieldEnemyToken = 'W';
         data->enemyLaserToken = 'v';
         data->playerToken = 'A';
         data->playerLaser = '^';
         data->explosionToken = 'X';
         data->currentAmountOfEnemies = 0; 
         data->totalAmoutOfEnemies = 0;

         //init the board by default.This board of chars is not resizable.
         
        for(int i=0;i<height;i++){
           for(int j=0;j<width;j++){
            
             if(i%2!=0 && j%2==0 && i<7 && j>=5 && j<=width-5){
                data->battleSpace[i][j] = data->normalEnemyToken;
                data->currentAmountOfEnemies++;
                data->totalAmoutOfEnemies++;
             }
             else{
                if(i%2!=0 && j%2==0 && i>=7 && i<9 && j>=5 && j<=width-5){
                    data->battleSpace[i][j] = data->shieldEnemyToken;
                    data->currentAmountOfEnemies++;
                    data->totalAmoutOfEnemies++;
                }
                else{
                    data->battleSpace[i][j] = ' ';
                }
             }
           
           }
        }
        
        data->battleSpace[height-1][width/2] = data->playerToken;
    }
    return (SpInvData) data;
}

char spInv_Data_getNormalEnemyToken(SpInvData data){
    return ((SpInv_data*)data)->normalEnemyToken;
}

char spInv_Data_getShieldEnemyToken(SpInvData data){
    return ((SpInv_data*)data)->shieldEnemyToken;
}

char spInv_Data_getEnemyLaserToken(SpInvData data){
    return ((SpInv_data*)data)->enemyLaserToken;
}

char spInv_Data_getPlayerToken(SpInvData data){
    return ((SpInv_data*)data)->playerToken;
}

char spInv_Data_getPlayerLaser(SpInvData data){
    return ((SpInv_data*)data)->playerLaser;
}

char spInv_Data_getExplosionToken(SpInvData data){
    return ((SpInv_data*)data)->explosionToken;
}

char spInv_Data_getEmptySpaceToken(SpInvData data){
    return ' ';
}

uint16_t  spInv_Data_getCurrentAmountOfEnemies(SpInvData data){
   return  ((SpInv_data*)data)->currentAmountOfEnemies;
}

uint16_t  spInv_Data_getTotalAmountOfEnemies(SpInvData data){
    return  ((SpInv_data*)data)->totalAmoutOfEnemies;
}

void  spInv_Data_changeToExplosionStatus(SpInvData data,uint16_t position_i,uint16_t position_j){
    if(position_i<((SpInv_data*)data)->height  && position_j<((SpInv_data*)data)->width){
         char token = ((SpInv_data*)data)->battleSpace[position_i][position_j];

         if(token == ((SpInv_data*)data)->normalEnemyToken){
            ((SpInv_data*)data)->currentAmountOfEnemies  -= 1;  
         } 

         ((SpInv_data*)data)->battleSpace[position_i][position_j] = ((SpInv_data*)data)->explosionToken;
    }
}

char spInv_Data_getTokenElementFromPosition(SpInvData data,uint16_t position_i,uint16_t position_j){
    char token = ' ';
    if(position_i<((SpInv_data*)data)->height  && position_j<((SpInv_data*)data)->width){
        token = ((SpInv_data*)data)->battleSpace[position_i][position_j]; 
    }
    return token;
}

void spInv_Data_changeTokenFromPosition(SpInvData data,uint16_t position_i,uint16_t position_j,char token){
    if(position_i<((SpInv_data*)data)->height  && position_j<((SpInv_data*)data)->width){
        ((SpInv_data*)data)->battleSpace[position_i][position_j] = token; 
    }
}

void spInv_Data_changeElementPosition(SpInvData data,uint16_t actual_i,uint16_t actual_j,uint16_t new_i,uint16_t new_j){
    if(actual_i<((SpInv_data*)data)->height  && actual_j<((SpInv_data*)data)->width
    && new_i<((SpInv_data*)data)->height  && new_j<((SpInv_data*)data)->width){
         
         ((SpInv_data*)data)->battleSpace[new_i][new_j] = ((SpInv_data*)data)->battleSpace[actual_i][actual_j];
         ((SpInv_data*)data)->battleSpace[actual_i][actual_j] = ' ';

    }
}

void spInv_Data_traverseSpace(SpInvData data,bool (*doSomething)(char,uint16_t,uint16_t,void*),void* contextVariable){
    uint16_t i = 0;
    uint16_t j = 0;

    while(i<((SpInv_data*)data)->width){
         
         j = 0;

         while(j<((SpInv_data*)data)->height && doSomething(((SpInv_data*)data)->battleSpace[i][j],j,i,contextVariable)){
            j++;
         }

         i = (j == ((SpInv_data*)data)->height)? (i+1):((SpInv_data*)data)->width;

    }
}

void spInv_Data_traverseSpaceReverse(SpInvData data,bool (*doSomething)(char tok,uint16_t posX,uint16_t posY,void* ctx),void* contextVariable){
   uint16_t i = ((SpInv_data*)data)->height-1;
   uint16_t j = 0;
   
   while(i>=0){
         
         j = ((SpInv_data*)data)->width - 1;

         while(j >= 0 && doSomething(((SpInv_data*)data)->battleSpace[i][j],j,i,contextVariable)){
            j--;
         }

         i = (j == -1)? (i-1):-1;

    }
}