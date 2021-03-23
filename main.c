#include "raylib.h"
#include <stdio.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Display mario sprite");
    int width = GetMonitorWidth(0);
    int height = GetMonitorHeight(0);
    SetWindowSize(width, height);
    ToggleFullscreen();

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Image banditYoshiWalkingI = LoadImage("Data/BanditYoshiWalking.png");
    Texture2D banditYoshiWalkingRight = LoadTextureFromImage(banditYoshiWalkingI);        // Texture loading
    ImageFlipHorizontal(&banditYoshiWalkingI);
    Texture2D banditYoshiWalkingLeft  = LoadTextureFromImage(banditYoshiWalkingI);
    Texture2D banditYoshiWalking = banditYoshiWalkingRight;
    UnloadImage(banditYoshiWalkingI);

    Image banditYoshiIdleI = LoadImage("Data/BanditYoshiIdle.png");
    Texture2D banditYoshiIdleRight = LoadTextureFromImage(banditYoshiIdleI);
    ImageFlipHorizontal(&banditYoshiIdleI);
    Texture2D banditYoshiIdleLeft = LoadTextureFromImage(banditYoshiIdleI);
    Texture2D banditYoshiIdle = banditYoshiIdleRight;
    UnloadImage(banditYoshiIdleI);
 
    Vector2 position = {0.0f, 0.0f};
    Rectangle frameRectWalking = {0.0f, 0.0f, (float)banditYoshiWalking.width/5.0f, (float)banditYoshiWalking.height};
    Rectangle frameRectIdle = {0.0f, 0.0f, (float)banditYoshiIdle.width, (float)banditYoshiIdle.height};
    float banditSpeed = 30.0f;
    int currentFrame = 0;
    int frameCounter = 0;
    int frameSpeed = 8;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        float deltaTime = GetFrameTime();

        bool isWalking = false;

        // 1 for moving to the right, -1 for moving to the left (animation should be reverse)
        int frameUpdate = 1;

        if(IsKeyDown(KEY_RIGHT))
        {
            position.x += banditSpeed*deltaTime;
            isWalking = true;
            banditYoshiWalking = banditYoshiWalkingRight;
            banditYoshiIdle = banditYoshiIdleRight;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            position.x -= banditSpeed*deltaTime;
            isWalking = true;
            banditYoshiWalking = banditYoshiWalkingLeft;
            banditYoshiIdle = banditYoshiIdleLeft;
            frameUpdate = -1;
        }

        if(isWalking)
        {
            ++frameCounter;

            if(frameCounter >= (60/frameSpeed))
            {
                frameCounter = 0;
                currentFrame = ((currentFrame + frameUpdate) + 5) % 5;

                frameRectWalking.x = (float)currentFrame*(float)banditYoshiWalking.width/5.0f;
            }
        }

        else
        {
            frameCounter = 0;
            currentFrame = 0;
            frameRectWalking.x = 0.0f;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BEIGE);
            if(isWalking)
            {
                DrawTextureRec(banditYoshiWalking, frameRectWalking, position, WHITE);
            }
            else
            {
                DrawTextureRec(banditYoshiIdle, frameRectIdle, position, WHITE);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(banditYoshiWalkingRight);       // Texture unloading
    UnloadTexture(banditYoshiWalkingLeft);
    UnloadTexture(banditYoshiIdleRight);
    UnloadTexture(banditYoshiIdleLeft);

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}