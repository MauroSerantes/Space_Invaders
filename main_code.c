#include "SpaceInvaders_GameStatusController.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(void){
    
   SIGameStatusController var =  siController_init();
   
   uint16_t counterToShoot = 0;
   uint64_t counter = 1;
   
   system("cls");
   
   bool finish = false;

   while(!finish && siController_updateNumberOfEnemies(var)>0){
       system("cls");
       siController_showCurrentStatusOfBattlefield(var);
       siController_movementOfEnemiesLaser(var,counter);
       siController_updateBattleField(var);
       finish = siController_movementOfEnemies(var,counter);
       if(kbhit()){
         siController_movementOfPlayer(var,getch(),&counterToShoot);
       }
       
       finish = (!finish)?siController_checkPlayerStatus(var):finish;
       counter++;
       counterToShoot++;
       Sleep(50);
   }

   return 0;
}