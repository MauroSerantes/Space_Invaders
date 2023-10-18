#include "SpaceInvaders_GameStatusController.h"
#include "SpaceInvaders_DataStructuresAndVariables.h"
#include <math.h>
#define ENEMIES_MOVES_RIGHT (uint8_t) 1
#define ENEMIES_MOVES_LEFT (uint8_t) 2


// main structure
typedef struct _spinvController{
    SpInvData data_game;
    uint16_t  speed_of_enemies;
    uint8_t  direction_of_enemies; // true = right  false = left
    uint16_t  battle_field_width;
    uint16_t  battle_field_height;
    uint16_t  ratio_of_enemies_shoot;
}SPINVController;



SIGameStatusController siController_init(void){
    SPINVController* new_controller = (SPINVController*) malloc(sizeof(SPINVController));
    
    if(new_controller != NULL){
        new_controller->battle_field_width = 44;
        new_controller->battle_field_height = 25;
        new_controller->data_game = spInv_Data_initialization(new_controller->battle_field_height,new_controller->battle_field_width);
        new_controller->direction_of_enemies = ENEMIES_MOVES_RIGHT;
        new_controller->ratio_of_enemies_shoot = 5;
    }
    
    return (SIGameStatusController) new_controller;
}

DOWN_TO_EARTH_FLAG  siController_movementOfEnemies(SIGameStatusController si,uint64_t externalClock){
    
    ((SPINVController*)si)->speed_of_enemies = 1 + 10 * (spInv_Data_getCurrentAmountOfEnemies(((SPINVController*)si)->data_game)
    /spInv_Data_getTotalAmountOfEnemies(((SPINVController*)si)->data_game));

    bool goDown = false;
    uint16_t i = 0;

    while(i < ((SPINVController*)si)->battle_field_height && 
          spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,0) != spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game) &&
          spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,0) != spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game)){
        i++;
    }
    
    if(i< ((SPINVController*)si)->battle_field_height){
        ((SPINVController*)si)->direction_of_enemies = ENEMIES_MOVES_RIGHT;
        goDown = true;
    }
    
    i=0; 
    
    while(i < ((SPINVController*)si)->battle_field_height && 
          spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,((SPINVController*)si)->battle_field_width-1) != spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game) &&
          spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,((SPINVController*)si)->battle_field_width-1) != spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game)){
        i++;
    }

    if(i < ((SPINVController*)si)->battle_field_height){
        ((SPINVController*)si)->direction_of_enemies = ENEMIES_MOVES_LEFT;
        goDown = true;
    }

    if(externalClock % ((SPINVController*)si)->speed_of_enemies == 0){
        
        if(((SPINVController*)si)->direction_of_enemies == ENEMIES_MOVES_RIGHT){
            
            for(uint16_t j=((SPINVController*)si)->battle_field_width;j>0;j--){
                for(uint16_t i=((SPINVController*)si)->battle_field_height-1;i>0;i--){
                    
                    if(goDown && (spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i-1,j-1) == spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)
                    || spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i-1,j-1) == spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game))){
                        
                        spInv_Data_changeElementPosition(((SPINVController*)si)->data_game,i-1,j-1,i,j); 
                    }
                    
                    if(!goDown && (spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j-1) == spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)
                    || spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j-1) == spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game))){
                            
                        spInv_Data_changeElementPosition(((SPINVController*)si)->data_game,i,j-1,i,j);

                    }

                }
            }
        }    
        if(((SPINVController*)si)->direction_of_enemies == ENEMIES_MOVES_LEFT){

             for (uint16_t j=0;j<((SPINVController*)si)->battle_field_width-1;j++) {
                for (uint16_t i=1;i<((SPINVController*)si)->battle_field_height;i++) {
                   
                    if (goDown && (spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i-1,j+1) == spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)
                    || spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i-1,j+1) == spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game))){
                       
                       spInv_Data_changeElementPosition(((SPINVController*)si)->data_game,i-1,j+1,i,j);
                    }
                    
                    if (!goDown && (spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j+1) == spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)
                    || spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j+1) == spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game))) {

                        spInv_Data_changeElementPosition(((SPINVController*)si)->data_game,i,j+1,i,j);
                    }

                }
            }
        }

        for (int j=0; j<((SPINVController*)si)->battle_field_width; j++) {
            
            if (spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-1,j) == spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)
                || spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-1,j) == spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game)){
                
                return  true;

            }

        }
    }
    return false; 
}

void siController_movementOfEnemiesLaser(SIGameStatusController si,uint64_t externalClock){
     bool enemies_ready_to_shoot = false;
  
     for(uint16_t j=0;j<((SPINVController*)si)->battle_field_width;j++){
        
        for(uint16_t i=((SPINVController*)si)->battle_field_height;i>0;i--){
            
          if(externalClock % 2 ==0  && spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getEnemyLaserToken(((SPINVController*)si)->data_game)
            && (spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i+1,j) != spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)
            && spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i+1,j) != spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game))){
    
                spInv_Data_changeElementPosition(((SPINVController*)si)->data_game,i,j,i+1,j);
        
          }
          
          if(externalClock % 2 ==0 && spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getEnemyLaserToken(((SPINVController*)si)->data_game)
            && (spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i+1,j) == spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)
            || spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i+1,j) == spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game))){

                spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,i,j,spInv_Data_getEmptySpaceToken(((SPINVController*)si)->data_game));
          }

          if((externalClock+1)%2==0 && i==((SPINVController*)si)->battle_field_height-1  && spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getEnemyLaserToken(((SPINVController*)si)->data_game)){
                spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,i,j,spInv_Data_getEmptySpaceToken(((SPINVController*)si)->data_game));
          }
        }
    }   
    
    for(uint16_t j=0;j<((SPINVController*)si)->battle_field_width;j++){
        
        for(uint16_t i=0;i<((SPINVController*)si)->battle_field_height;i++){
            
            if((externalClock % ((SPINVController*)si)->ratio_of_enemies_shoot)==0 && (spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)
            || spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game)) && (rand()%15)>13 &&
            spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i+1,j) != spInv_Data_getPlayerLaser(((SPINVController*)si)->data_game)){
                
                uint16_t k = i+1;

                while(k < ((SPINVController*)si)->battle_field_height && (spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,k,j) != spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)
                && spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,k,j) != spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game))){
                    k++;
                }
                if(k == ((SPINVController*)si)->battle_field_height){
                    enemies_ready_to_shoot = true;
                }
                if(enemies_ready_to_shoot){
                     spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,i+1,j,spInv_Data_getEnemyLaserToken(((SPINVController*)si)->data_game));         
                }
            }

        }
    }
}


void siController_movementOfPlayer(SIGameStatusController si,char command,uint16_t* externalClockForShoot){
     if(command == '4'){
        for(uint16_t j=0;j<((SPINVController*)si)->battle_field_width-1;j++){
            if(spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-1,j+1) == spInv_Data_getPlayerToken(((SPINVController*)si)->data_game)){
                spInv_Data_changeElementPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-1,j+1,((SPINVController*)si)->battle_field_height-1,j);
            }
        }
    }
    if(command == '6'){
        for(uint16_t j = ((SPINVController*)si)->battle_field_width-1;j>0;j--){
            if(spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-1,j-1) == spInv_Data_getPlayerToken(((SPINVController*)si)->data_game)){
                spInv_Data_changeElementPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-1,j-1,((SPINVController*)si)->battle_field_height-1,j);
            }
        }
    }
    if(command == 's' && *externalClockForShoot>=3){
        for(uint16_t j=0;j<((SPINVController*)si)->battle_field_width;j++){
            if(spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-1,j-1) == spInv_Data_getPlayerToken(((SPINVController*)si)->data_game)){
                spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-2,j,spInv_Data_getPlayerLaser(((SPINVController*)si)->data_game));
                *externalClockForShoot = 0;
            }
        }                                
    }
}


void siController_updateBattleField(SIGameStatusController si){
    for(int j=0;j<((SPINVController*)si)->battle_field_width;j++){
       for(int i=0;i<((SPINVController*)si)->battle_field_height;i++){
            
            if (i>0 && spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getPlayerLaser(((SPINVController*)si)->data_game) && 
            spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i-1,j) == spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game)){
            
                spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,i,j,spInv_Data_getEmptySpaceToken(((SPINVController*)si)->data_game));
                spInv_Data_changeToExplosionStatus(((SPINVController*)si)->data_game,i-1,j);
            
            }
            
            if(i>0 && spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getPlayerLaser(((SPINVController*)si)->data_game) && 
            spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i-1,j) == spInv_Data_getShieldEnemyToken(((SPINVController*)si)->data_game)) {
            
                spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,i,j,spInv_Data_getEmptySpaceToken(((SPINVController*)si)->data_game));
                spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,i-1,j,spInv_Data_getNormalEnemyToken(((SPINVController*)si)->data_game));
            
            }
            
            else if(spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getPlayerLaser(((SPINVController*)si)->data_game) && 
            spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i-1,j) == spInv_Data_getEnemyLaserToken(((SPINVController*)si)->data_game)) {
                
                spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,i,j,spInv_Data_getEmptySpaceToken(((SPINVController*)si)->data_game));

            }
            
            else if(spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getExplosionToken(((SPINVController*)si)->data_game)) {
                
                spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,i,j,spInv_Data_getEmptySpaceToken(((SPINVController*)si)->data_game));

            }
            
            else if(spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j) == spInv_Data_getPlayerLaser(((SPINVController*)si)->data_game) && 
            spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i-1,j) != spInv_Data_getEnemyLaserToken(((SPINVController*)si)->data_game)) {
                 
                spInv_Data_changeElementPosition(((SPINVController*)si)->data_game,i,j,i-1,j); 
            }                
        }
    }

    for(uint16_t j=0;j<((SPINVController*)si)->battle_field_width;j++){
        
        if(spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,0,j) == spInv_Data_getPlayerLaser(((SPINVController*)si)->data_game)){
              
              spInv_Data_changeTokenFromPosition(((SPINVController*)si)->data_game,0,j,spInv_Data_getEmptySpaceToken(((SPINVController*)si)->data_game));
        }

    } 
}

uint16_t siController_updateNumberOfEnemies(SIGameStatusController si){
    return (spInv_Data_getCurrentAmountOfEnemies(((SPINVController*)si)->data_game));
}    

PLAYER_DESTRUCTION_FLAG  siController_checkPlayerStatus(SIGameStatusController si){
    for(int j=0;j<((SPINVController*)si)->battle_field_width;j++){
        
        if(spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-2,j) == spInv_Data_getEnemyLaserToken(((SPINVController*)si)->data_game)
        && spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,((SPINVController*)si)->battle_field_height-1,j) == spInv_Data_getPlayerToken(((SPINVController*)si)->data_game)){
            return true;
        }

    }
    return false;
}  

void siController_showCurrentStatusOfBattlefield(SIGameStatusController si){
     
     for(uint16_t i=0;i<((SPINVController*)si)->battle_field_height;i++){
          
          printf("|");

          for(uint16_t j=0;j<((SPINVController*)si)->battle_field_width;j++){
              
              printf("%c",spInv_Data_getTokenElementFromPosition(((SPINVController*)si)->data_game,i,j));
               
          }

          printf("|\n");

     }

}

