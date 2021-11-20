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
        return((r1.x + r1.width >= r2.x) && (r1.x <= r2.x + r2.width) && (r1.y + r1.height >= r2.y) && (r1.y <= r2.y + r2.height));
}



//Constants-------------------------------------------------------------
const int Widths[] = {100,200,300,400,500,600,700,800,900};
const int speed = 10;
const Vector2 PlayerSize = {128,128};

//Screen Size
const int screenWidth = 1000;
const int screenHeight = 800;

//Platforms
const Rectangle platform1 = {0,700,400,100};
const Rectangle platform2 = {600,700,400,100}; 
//----------------------------------------------------------------------


//Statics--------------------------------------------------------------

//Player Vectors
static Vector2 Position = {0};
static Vector2 Playerposition = {0,0};

//Textures
static Texture2D hatty = {0};
static Texture2D letter = {0};
static Texture2D title = {0};

//Object Hitboxes
static Letterbox hitbox[10] = {0};
static Rectangle button = {0};

//Logic Integers and Counters
static int start = 1;
static int point_count = 0;
static int count_number = 0;
static int spawnCounter = 0;
static int framesCounter = 0;
static int duration = 0;



static Rectangle srcRect = {0};

//Jump Variables
static bool jumped = false;
static int count_notjumped = 0;
static int count_jumped = 0;
static bool up = false;


static bool grounded = false;
//Game Loop Variable
static bool gameStart = false;

//Global Functions
static void UnloadTextures(void);
static void InitGame(void);
static void Jump_Handler(void);
static void Mov_Handler(void);
static void Letter_Handler(void);
static void Letter_Spawn(int r);
static void Fall_Handler(void);

//-----------------------------------------------------------------------

int main(void){
        
        //Random Seed
        srand(time(NULL));


        InitWindow(screenWidth,screenHeight,"texture tester");
        
        SetTargetFPS(60);

        gameStart = false;
        
        title = LoadTexture("../assets/title.png");
        button = (Rectangle){0,0,64,32};

        while(!WindowShouldClose()){
        
        if(!gameStart){
        
        

        //Title Screen Logic
        if((GetMouseX()  >= (screenWidth/2 + 40) && GetMouseX() <= ((screenWidth/2) + 188)) && 
        (GetMouseY() >= 512 && GetMouseY() <= 500+75) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
               InitGame();

     } else {
        

        //Generate Random Number In Range of 10
        int random_number = rand() % 10;

        framesCounter++;
        
        spawnCounter++;

        if(Position.y + 128 > screenHeight-platform1.height+10){
                grounded = false;
        } else{
                grounded = true;
        }
        
        
        if(Position.x >= platform1.width-35 && Position.x <= screenWidth-platform2.width-80){
               if(!up)
                jumped = true;
        }

        Letter_Spawn(random_number);
        
        
        Jump_Handler();
        Mov_Handler();    
        

       
        Playerposition = (Vector2) {Position.x,Position.y};
        

        
        Letter_Handler();

        if(Playerposition.y >= screenHeight){
                gameStart = false;
                 UnloadTexture(hatty);
                UnloadTexture(letter); 
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

                             
              //Drawing Letters(3.Plane)  
              for(int i = 0;i < 10;i++){
                      if(hitbox[i].Position.y != 0)
                      DrawTexturePro(letter,
                                     (Rectangle){0,0,hitbox[i].size.x+5,hitbox[i].size.y+5},
                                     (Rectangle){hitbox[i].Position.x,hitbox[i].Position.y,64,64},
                                     (Vector2){0,0},
                                     hitbox[i].rotation,
                                     RAYWHITE);

              }
             
              //Drawing Platforms(2.Plane) 
              DrawRectangleRec(platform1,BLUE);
              DrawRectangleRec(platform2,BLUE);

              //Drawing Player(Front Plane)
              DrawTexturePro(hatty,
                             srcRect, 
                            (Rectangle){Playerposition.x,Playerposition.y,128,128},
                            (Vector2){0,0},
                            0.0f, 
                            RAYWHITE);

                //Debug 
                //DrawRectangleRec((Rectangle){platform1.width,platform1.y + 50,platform2.x -400,platform1.y},PINK);
               
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


void InitGame(void){
        
       jumped = false; 
       start = 1; 
       point_count = 0;
       count_number = 0;
       spawnCounter = 0;
       framesCounter = 0;
       duration = 0;
       srcRect = (Rectangle){0};
       
        

        count_notjumped = 0;
        count_jumped = 18;
        up = false;
       
        grounded = true;
  
        gameStart = true;

        Position = (Vector2) {screenWidth/2 + 100,(screenHeight-platform1.height)-120};
        hatty = LoadTexture("../assets/hatty_full.png");
        letter = LoadTexture("../assets/letter.png");
        
        for(int i = 0;i < 10; i++){
                hitbox[i].Position = (Vector2){0,0};
                hitbox[i].size = (Vector2){20,20};
                hitbox[i].rotation = 0.0f;
                hitbox[i].speed = 0;
                hitbox[i].row_number = 0;
        }
}

void Jump_Handler(void){
        if(IsKeyPressed(KEY_UP) && !up) up = true;
        if(jumped){
                
                Position.y += count_notjumped;
                count_notjumped++;
                              
                if((hit_detected((Rectangle){Position.x +60,Position.y,PlayerSize.x,PlayerSize.y},platform1) || 
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
         /*else {
                if(Position.x + PlayerSize.x > screenWidth-platform2.width)
                        Position.x -= speed;
                if(Position.x-10 < platform1.width)
                        Position.x += speed;
                


        }*/
}


void Fall_Handler(void){
        //Ground Behaviour
        if((Position.x >= (platform1.width )) && 
          (Position.x <= platform2.x - 100))
                Position.y += 2;

        //GameOver Condition
        /*if((Position.x >= (platform1.x+platform1.width)) && 
          (Position.x <= (platform2.x + platform2.width)) && Position.y == (screenHeight-120)) 
                gameStart = false;*/
}

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
        


void UnloadTextures(void){
        UnloadTexture(hatty);
        UnloadTexture(letter);
        UnloadTexture(title);
}




