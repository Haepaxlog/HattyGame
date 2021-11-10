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




const int Widths[] = {100,200,300,400,500,600,700,800,900};
enum rows{ROW_1,ROW_2,ROW_3,ROW_4,ROW_5,ROW_6,ROW_7,ROW_8,ROW_9,ROW_10};
const int speed = 10;
static Vector2 Position = {0};
static Vector2 Playerposition = {0,0};
static Vector2 PlayerSize = {0};
static Texture2D hatty = {0};
static Texture2D letter = {0};
static Texture2D title = {0};
static Letterbox hitbox[10] = {0};
static Rectangle button = {0};
static bool jumped = false;
static int start = 1;
static int point_count = 0;
static int count_number = 0;
static int spawnCounter = 0;
static int framesCounter = 0;
static int duration = 0;

static Rectangle platform1 = {0};
static Rectangle platform2 = {0};

static Rectangle srcRect = {0};

//Jump Height Variables
static int count_notjumped = 0;
static int count_jumped = 0;
static bool up = false;

//Game Loop Variable
static bool gameStart = false;

static void UnloadTextures(void);
static void InitGame(void);


const int screenWidth = 1000;
const int screenHeight = 800;

int main(void){
        
        //Random Seed
        srand(time(NULL));


        InitWindow(screenWidth,screenHeight,"texture tester");
        
        SetTargetFPS(60);

        gameStart = false;
        
        title = LoadTexture("./title.png");
        button = (Rectangle){0,0,64,32};

        while(!WindowShouldClose()){
        
        if(!gameStart){
        
        

        //Title Screen
        if((GetMouseX()  >= (screenWidth/2 + 40) && GetMouseX() <= ((screenWidth/2) + 188)) && 
        (GetMouseY() >= 512 && GetMouseY() <= 500+75) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
               InitGame();

     } else {
        

        //Random Number In Range of 10
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
                if(Position.y == ((screenHeight-platform1.height)-120)){
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
          //Animation,Movement And Wall Behaviour  of Player               
        if(IsKeyDown(KEY_LEFT)){
                if((Position.x - speed) >= (-20)){ 
                Position.x -= speed;
                srcRect = (Rectangle){0,32,32,32};
                }
        }
        if(IsKeyDown(KEY_RIGHT)){
                if((Position.x + speed) <= screenWidth-128){
                Position.x += speed;
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

       
        Playerposition = (Vector2) {Position.x,Position.y};
        
        //Ground Behaviour
        if((Playerposition.x >= (platform1.x+platform1.width)) && 
          (Playerposition.x <= (platform2.x + platform2.width)))
          Playerposition.y += 2; 
        //GameOver Condition
        if((Playerposition.x >= (platform1.x+platform1.width)) && 
          (Playerposition.x <= (platform2.x + platform2.width)) && Playerposition.y == (screenHeight-120)) 
                gameStart == false;

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

        
     } 

        


       
        BeginDrawing();

        if(!gameStart){
       
                ClearBackground(RAYWHITE);
                DrawText("HATTY GAME",screenWidth/2 - 20,50, 30, BLACK);
                DrawTexturePro(title,button,(Rectangle){screenWidth/2,500,256,128},(Vector2){0,0},
                                0.0f,RAYWHITE);
        
        } else{
                        

                

        ClearBackground(GREEN);

              //Drawing Platforms 
              DrawRectangleRec(platform1,BLUE);
              DrawRectangleRec(platform2,BLUE);  
               
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
                

                }

        EndDrawing();

        }


        UnloadTextures();

        CloseWindow();

 
        return 0;
}

//Initializing Game
void InitGame(void){
        
       jumped = false; 
       start = 1; 
       point_count = 0;
       count_number = 0;
       spawnCounter = 0;
       framesCounter = 0;
       duration = 0;
       srcRect = (Rectangle){0};
       
       platform1 = (Rectangle){0,700,400,100};
       platform2 = (Rectangle){600,700,400,100}; 
        
        //Jump Height Variables
        count_notjumped = 0;
        count_jumped = 18;
        up = false;
       

        //Game Loop Variables
        gameStart = true;

        PlayerSize = (Vector2) {64,64};
        Position = (Vector2) {screenWidth/2,(screenHeight-platform1.height)-120};
        hatty = LoadTexture("./hatty_full.png");
        letter = LoadTexture("./letter.png");
        
        for(int i = 0;i < 10; i++){
                hitbox[i].Position = (Vector2){0,0};
                hitbox[i].size = (Vector2){20,20};
                hitbox[i].rotation = 0.0f;
                hitbox[i].speed = 0;
                hitbox[i].row_number = 0;
        }
}


//Unloading Textures
void UnloadTextures(void){
        UnloadTexture(hatty);
        UnloadTexture(letter);
        UnloadTexture(title);
}




