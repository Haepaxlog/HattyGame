#include "raylib.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Letterbox{
        Vector2 Position;
        Vector2 size;
        float rotation;
        int speed;
        int row_number;
}Letterbox;

bool hit_detected(Rectangle r1,Rectangle r2){
        bool truth = (r1.x + r1.width >= r2.x) && (r1.x <= r2.x + r2.width) && (r1.y + r1.height >= r2.y) && (r1.y <= r2.y + r2.height);
        return truth;
}



static void UnloadTextures(void);

const int Widths[] = {100,200,300,400,500,600,700,800,900};
enum rows{ROW_1,ROW_2,ROW_3,ROW_4,ROW_5,ROW_6,ROW_7,ROW_8,ROW_9,ROW_10};
const int speed = 10;
static Vector2 Position = {0,0};
static Vector2 Playerposition = {0,0};
static Texture2D hatty = {0};
static Texture2D letter = {0};
static Letterbox hitbox[10] = {0};

int main(void){
        
        //Random Seed
        srand(time(NULL));

        const int screenWidth = 1000;
        const int screenHeight = 800;

        InitWindow(screenWidth,screenHeight,"texture tester");
        
        bool jumped = false; 
        int start = 1; 
        int point_count = 0;
        int count_number = 0;
        int spawnCounter = 0;
        int framesCounter = 0;
        int duration = 0;
        Rectangle srcRect = {0};
        SetTargetFPS(60);
        
        //Jump Height Variables
        int count_notjumped = 0;
        int count_jumped = 18;
        bool up = false;
       
        Vector2 PlayerSize = {64,64};
        Vector2 Position = {screenWidth/2,screenHeight-128};
        Texture2D hatty = LoadTexture("./hatty_full.png");
        Texture2D letter = LoadTexture("./letter.png");
        
        for(int i = 0;i < 10; i++){
                hitbox[i].Position = (Vector2){0,0};
                hitbox[i].size = (Vector2){20,20};
                hitbox[i].rotation = 0.0f;
                hitbox[i].speed = 0;
                hitbox[i].row_number = 0;
        }


        while(!WindowShouldClose()){
        
        //Random Number of Screen Width
        int random_number = rand() % 10;

        framesCounter++;
        
        spawnCounter++;
        

        //Hitbox Spawning of Letters
        if(start == 1 || spawnCounter % 60){
                for(int i = 0;i < 10; i++){
                        if(hitbox[i].Position.x == 0 && hitbox[i].Position.y == 0){
                                hitbox[i].Position = (Vector2){Widths[random_number],0};
                                hitbox[i].row_number = random_number;
                                int random_speed = rand() % 10 + 5;
                                hitbox[i].speed = random_speed;
                                break;
                        }
                }
                start = 0;
        }
        
       
        

        //Jumping Handler
        if(IsKeyPressed(KEY_UP) && !up) up = true;
        if(jumped){
                
                Position.y += count_notjumped;
                count_notjumped++;
                if(Position.y == (screenHeight-128)){
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
          //Animation and Movement of Player               
        if(IsKeyDown(KEY_LEFT)){
                Position.x -= speed;
                srcRect = (Rectangle){0,32,32,32};
        }
        if(IsKeyDown(KEY_RIGHT)){
                Position.x += speed;
                srcRect = (Rectangle){32,32,32,32};
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

        Vector2 Playerposition = {Position.x,Position.y};


        //Movement, Hit-Detection, Destruction of Letters
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

        
        


       
        BeginDrawing();
        ClearBackground(GREEN);

               
              //Drawing Letters(Back Plane)  
              for(int i = 0;i < 10;i++){
                      if(hitbox[i].Position.y != 0)
                      DrawTexturePro(letter,
                                     (Rectangle){0,0,hitbox[i].size.x+5,hitbox[i].size.y+5},
                                     (Rectangle){hitbox[i].Position.x,hitbox[i].Position.y,64,64},
                                     (Vector2){0,0},
                                     hitbox[i].rotation,
                                     RAYWHITE);

              }
              
              //Drawing Player(Front Plane)
              DrawTexturePro(hatty,
                             srcRect, 
                            (Rectangle){Playerposition.x,Playerposition.y,128,128},
                            (Vector2){0,0},
                            0.0f, 
                            RAYWHITE);  
               
              char str[20];
              sprintf(str,"%i",point_count);
              DrawText(str,20,20,40,BLACK);
                

        EndDrawing();

        }

        UnloadTextures();

        CloseWindow();

 
        return 0;
}

//Unloading Textures
void UnloadTextures(void){
        UnloadTexture(hatty);
        UnloadTexture(letter);
}




