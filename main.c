#include "raylib.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Player.h"
#include "Letter.h"




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

//Player Vectors
Vector2 Position = {0};
Vector2 Playerposition = {0,0};

//Object Hitboxes
Letterbox hitbox[10] = {0};

Rectangle srcRect = {0};

//Textures
Texture2D hatty = {0};
Texture2D letter = {0};
Texture2D plus_score = {0};

//Icon
Image WindowIcon = {0};

//Statics--------------------------------------------------------------

//Textures
static Texture2D title = {0};

static Rectangle button = {0};

//Game Loop Variable
bool gameStart = false;

//Global Functions
static void UnloadTextures(void);
static void InitGame(void);
static void Draw_Title(void);
static void Draw_Score(void);
static void Draw(void);

//-----------------------------------------------------------------------

//Logic Integers and Counters
int start = 1;
int point_count = 0;
int count_number = 0;
int spawnCounter = 0;
int framesCounter = 0;
int duration = 0;

//Jump Variables
bool jumped = false;
int count_notjumped = 0;
int count_jumped = 0;
bool up = false;
bool grounded = false;

//Timer and Collector
int second_counter = 0;
int time_left = 0;
int letter_collect = 0;
int phase_count = 0;
int multiplier = 0;


int current_rect = 0;
int recent_rect = 0;

int delay = 0;

bool activated = false;



int main(void){
        
        //Random Seed
        srand(time(NULL));

        InitWindow(screenWidth,screenHeight,"HattyGame");        
        SetTargetFPS(60);

        WindowIcon = LoadImage("../assets/hatty_icon.png");
        SetWindowIcon(WindowIcon);

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

        if(framesCounter%60) second_counter++;
        
        spawnCounter++;

        if(Position.y + 128 > screenHeight-platform1.height+10){
                grounded = false;
        } else{
                grounded = true;
        }
        
        
        Letter_Spawn(random_number);
        
        Collection_Handler();
        
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
       
        Draw_Title();
                
        } else{
                        
        Draw();

        ClearBackground(GREEN);

              
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
      
       multiplier = 0;

       delay = 0;

       activated = false;

        current_rect = 0;
        recent_rect = 2;

       second_counter = 0;
       time_left = 400;
       letter_collect = (rand()%50) + multiplier;
       phase_count = 0;

       

        count_notjumped = 0;
        count_jumped = 18;
        up = false;
       
        grounded = true;
  
        gameStart = true;

        Position = (Vector2) {screenWidth/2 + 100,(screenHeight-platform1.height)-120};
        hatty = LoadTexture("../assets/hatty_full.png");
        letter = LoadTexture("../assets/letter.png");
        plus_score = LoadTexture("../assets/plus_score.png");
        
        for(int i = 0;i < 10; i++){
                hitbox[i].Position = (Vector2){0,0};
                hitbox[i].size = (Vector2){20,20};
                hitbox[i].rotation = 0.0f;
                hitbox[i].speed = 0;
                hitbox[i].row_number = 0;
        }
}

void Draw_Title(void){
        ClearBackground(RAYWHITE);
        DrawText("HATTY GAME",screenWidth/2 - 20,50, 30, BLACK);
        DrawTexturePro(title,button,(Rectangle){screenWidth/2,500,256,128},(Vector2){0,0},0.0f,RAYWHITE);
}       

void Draw_Score(void){
        char str_point_count[20];
        sprintf(str_point_count,"Letters:%i",point_count);
        DrawText(str_point_count,20,20,40,BLACK);
        char str_time_left[20];
        sprintf(str_time_left,"Time:%i",time_left);
        DrawText(str_time_left,screenWidth-180,20,40,BLACK);
        char str_letter_collect[20];
        sprintf(str_letter_collect,"Goal:%i",letter_collect);
        DrawText(str_letter_collect,screenWidth-180,60,40,BLACK);
}

void Draw(void){
                
        //Drawing Letters(3.Plane)
        Draw_Letters();  
              
        //Drawing Platforms(2.Plane) 
        DrawRectangleRec(platform1,BLUE);
        DrawRectangleRec(platform2,BLUE);

        //Drawing Player(Front Plane)
        Draw_Player();

        //Debug 
        //DrawRectangleRec((Rectangle){platform1.width,platform1.y + 50,platform2.x -400,platform1.y},PINK);

        Draw_Score(); 
}

void UnloadTextures(void){
        UnloadTexture(hatty);
        UnloadTexture(letter);
        UnloadTexture(title);
        UnloadTexture(plus_score);
        UnloadImage(WindowIcon);
}
