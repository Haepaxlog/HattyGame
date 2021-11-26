#include "raylib.h"
#include <stdlib.h>

extern Texture2D hatty;
extern Texture2D plus_score;

extern Vector2 Position;
extern Vector2 Playerposition;

extern const Vector2 PlayerSize;
extern const Rectangle platform1;
extern const Rectangle platform2;

extern const int screenWidth;
extern const int screenHeight;

extern bool jumped;
extern bool up;
extern const int speed;

extern bool hit_detected(Rectangle r1,Rectangle r2);
extern Rectangle srcRect;
extern int framesCounter;
extern int duration;

extern int count_jumped;
extern int count_notjumped;
extern bool grounded;

extern int point_count;

extern int second_counter;
extern int time_left;
extern int letter_collect;
extern int phase_count;

extern int multiplier;

extern bool gameStart;


extern bool position_change;
extern int current_rect;
extern int recent_rect;

extern int delay;

extern bool activated;


void Jump_Handler(void);
void Mov_Handler(void);
void Draw_Player(void);
void Collection_Handler(void);