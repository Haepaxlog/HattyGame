#include "raylib.h"
#include <stdlib.h>

typedef struct Letterbox{
        Vector2 Position;
        Vector2 size;
        float rotation;
        int speed;
        int row_number;
}Letterbox;

extern Texture2D letter;

extern int start;
extern int spawnCounter;
extern const int Widths[];
extern Letterbox hitbox[10];
extern int point_count;

extern const int screenHeight;
extern const int screenWidth;

extern Vector2 Playerposition;
extern const Vector2 PlayerSize;

extern bool hit_detected(Rectangle r1,Rectangle r2);


void Letter_Spawn(int r);
void Letter_Handler(void);
void Draw_Letters(void);