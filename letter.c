#include "Letter.h"


void Letter_Spawn(int r){
        if(start == 1 || spawnCounter % 60){
                for(int i = 0;i < 10; i++){
                        if(hitbox[i].Position.x == 0 && hitbox[i].Position.y == 0){
                                hitbox[i].Position = (Vector2){Widths[r],0};
                                hitbox[i].row_number = r;
                                int random_speed = rand() % 10 + 5;
                                hitbox[i].speed = random_speed;
                                break;
                        }
                }
                start = 0;
        }
}

void Letter_Handler(void){
        if((spawnCounter%60)){
                for(int i = 0;i < 10;i++){
                        if(hitbox[i].Position.x != 0){
                        hitbox[i].Position.y +=  hitbox[i].speed;
                        //Hit-Detection Algorithm
                        if(hit_detected((Rectangle){hitbox[i].Position.x,hitbox[i].Position.y,hitbox[i].size.x,hitbox[i].size.y},
                                                (Rectangle){Playerposition.x,Playerposition.y,PlayerSize.x,PlayerSize.y})){
                                point_count++;
                                hitbox[i].Position = (Vector2){0,0};
                               

                        } else if(hitbox[i].Position.y >= screenHeight){
                                hitbox[i].Position = (Vector2){0,0};
                                        }
                                 }
                         
                        }
            }

        
    }

void Draw_Letters(void){
    for(int i = 0;i < 10;i++){
                      if(hitbox[i].Position.x != 0)
                      DrawTexturePro(letter,
                                     (Rectangle){0,0,hitbox[i].size.x+5,hitbox[i].size.y+5},
                                     (Rectangle){hitbox[i].Position.x,hitbox[i].Position.y,64,64},
                                     (Vector2){0,0},
                                     hitbox[i].rotation,
                                     RAYWHITE);

            }
}
