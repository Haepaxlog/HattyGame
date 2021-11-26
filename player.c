#include "raylib.h"
#include "Player.h"


void Jump_Handler(void){
        if(IsKeyPressed(KEY_UP) && !up) up = true;
        if(jumped){
                
                Position.y += count_notjumped;
                count_notjumped++;
                                //2 -20      
                if((hit_detected((Rectangle){Position.x +30,Position.y,PlayerSize.x,PlayerSize.y},platform1) || 
                  (hit_detected((Rectangle){Position.x-20,Position.y,PlayerSize.x,PlayerSize.y},platform2))) && grounded){
                     
                        jumped = false;
                        count_notjumped = 0;
                        up = false;
                        
                        }
                
        }
        if(up && !jumped){
                        
                        Position.y -= count_jumped;
                        count_jumped--;
                        if(count_jumped == 0){
                                jumped = true;
                                count_jumped = 18;
                        }
        }
}


void Mov_Handler(void){
        if(Position.x >= platform1.width-35 && Position.x <= screenWidth-platform2.width-100){
               if(!up)
                jumped = true;
        }
        if(IsKeyDown(KEY_LEFT)){
                if(Position.x - speed+30){
                Position.x -= speed;
                if(hit_detected((Rectangle){Position.x,Position.y,PlayerSize.x,PlayerSize.y},(Rectangle){platform1.width-35,screenHeight+10-platform1.height,1,platform1.y}))
                Position.x += speed;
                srcRect = (Rectangle){0,32,32,32};
                } 
        }
        
        if(IsKeyDown(KEY_RIGHT)){
                if((Position.x + speed) <= screenWidth-128){
                Position.x += speed;
                if(hit_detected((Rectangle){Position.x,Position.y,PlayerSize.x,PlayerSize.y},(Rectangle){screenWidth-platform2.width,screenHeight+10-platform2.height,1,platform2.y}))
                Position.x -= speed;
                srcRect = (Rectangle){32,32,32,32};
                }
        }

        if(!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)){
                if(framesCounter >= (60)){
                        srcRect = (Rectangle){32,0,32,32};
                        duration++;
                        if(duration == 30){
                                framesCounter = 0;
                                duration = 0;
                        }
                        } else{
                       srcRect = (Rectangle){0,0,32,32};
                                }
                        }
      
}

void Draw_Player(void){
     DrawTexturePro(hatty,
                    srcRect, 
                    (Rectangle){Playerposition.x,Playerposition.y,128,128},
                    (Vector2){0,0},
                    0.0f, 
                    RAYWHITE);


    if(!up && activated){    
    if(delay < 40){    
            delay++;
    DrawTexturePro(plus_score,
                    (Rectangle){0,0,32,32},
                    (Rectangle){Playerposition.x+PlayerSize.x,Playerposition.y,96,96},
                    (Vector2){0,0},
                    0.0f,
                    RAYWHITE);
    } else if(delay == 40){
            activated = false;
            delay = 0;
        } 
    }


}

void Collection_Handler(void){
        
        time_left--;
        if(time_left == 0) gameStart = false;


        if(Position.x <= platform1.width-35){
                current_rect = 1;
        }
        if(Position.x >= screenWidth-platform2.width-100){
                current_rect = 2;
        }

        if(recent_rect != current_rect){
                time_left+= 50;
                activated  = true;
        }

        recent_rect = current_rect;

        if(point_count == letter_collect){
                time_left += 200;
                phase_count += 1;
                multiplier++;
                letter_collect += (rand()%50) + multiplier;
        }
}