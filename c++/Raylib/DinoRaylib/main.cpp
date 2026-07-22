#include "raylib.h"

#define RAYBLACK CLITERAL(Color){ 10, 10, 10, 255 }

 class Dino {
    private:
        Vector2 startPosition;
        float startJumpForce;
        float startGravity;

        Vector2 position;
        bool isAlive;
        bool isGrounded;
        float jumpForce;
        float gravity;
        float velocityY;
        
    public:
        Dino(Vector2 p, bool iA,bool iG, float jF, float g, float vY);
        void Jump(float jumpF);
        void Dead();
        void Reset();
        void ApplyGravity();
        void UpdatePos();
        Vector2 GetPos();
        int GetJumpForce();
        float GetGravity();
        float GetVelocityY();
 };

Dino::Dino(Vector2 p, bool iA,bool iG, float jF, float g, float vY){

    startPosition = p;
    startJumpForce = jF;
    startGravity = g;

    position = p;
    isAlive = iA;
    isGrounded= iG;
    jumpForce = jF;
    gravity = g;
    velocityY = vY;
}

void Dino::Jump(float jumpF)
{
    if (!isGrounded) return;
    velocityY = -jumpF;

}

void Dino::Dead()
{

}

void Dino::Reset()
{
    position = startPosition;
    isAlive = true;
    isGrounded= true;
    jumpForce = startJumpForce;
    gravity = startGravity;
    velocityY = 0;
}

void Dino::ApplyGravity()
{
    if (!isGrounded)
        velocityY += gravity * GetFrameTime();

}

void Dino::UpdatePos()
{
    position.y += velocityY * GetFrameTime();

    if (position.y >= 550){
        position.y = 550;
        isGrounded = true;
    }
    else
        isGrounded = false;
}

Vector2 Dino::GetPos(){
    return position;   
}

int Dino::GetJumpForce()
{
    return jumpForce;
}

float Dino::GetGravity()
{
    return gravity;
}

class Obstacle {
    
    private:
    Vector2 startPos;
    
    Vector2 position;
    int velocity;
    int randomSpawn = 50;

    public:

    Obstacle(Vector2 p, int v);

    void Move(int velocity);
    void Reset();
    Vector2 GetPos();
    int GetSpeed();
};

Obstacle::Obstacle(Vector2 p, int v)
{
    startPos = p;
    position = p;
    velocity = v;
}

void Obstacle::Move(int velocity){
    position.x -= velocity * GetFrameTime();
   
    if (position.x <= -randomSpawn) {
        position.x = 1000;
        randomSpawn = GetRandomValue(50, 500);
    }   
}

void Obstacle::Reset()
{
    position = startPos;
}
Vector2 Obstacle::GetPos()
{
    return position;
}

int Obstacle::GetSpeed()
{
    return velocity;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;
    float ballRadius = 25.0f;
    Vector2 startPos = { 100, 550 };
    Vector2 right = {1000, 525};
    Dino Dinosaur(startPos, true, true, 600.0f, 1000.0f, 0.0f);
    Obstacle Cactus(right, 600);

    InitWindow(screenWidth, screenHeight, "Er fucking juego del fucking dinosaurio de fokin gugle");

    

    SetTargetFPS(100);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        Dinosaur.ApplyGravity();
        Dinosaur.UpdatePos();
        Cactus.Move(Cactus.GetSpeed());

        if (IsKeyPressed(KEY_SPACE)){
            Dinosaur.Jump(Dinosaur.GetJumpForce());
        }

        if (IsKeyPressed(KEY_R)){
            Dinosaur.Reset();
            Cactus.Reset();
        }
        
        Rectangle dinoBox = {
            Dinosaur.GetPos().x,
            Dinosaur.GetPos().y,
            50,
            50
        };

        Rectangle cactusBox = {
            Cactus.GetPos().x,
            Cactus.GetPos().y,
            50,
            50
        };

        if (CheckCollisionRecs(dinoBox, cactusBox))
        {
            Dinosaur.Reset();
            Cactus.Reset();
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            
            ClearBackground(RAYWHITE);

            DrawLine(0, 550, 800, 550, GRAY );

            DrawCircleV(Dinosaur.GetPos(), ballRadius, RAYBLACK);
            DrawRectangleV(Cactus.GetPos(), {50, 50}, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}