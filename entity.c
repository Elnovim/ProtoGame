#include "entity.h"

entity LoadBanditYoshi()
{
	entity banditYoshi;

	Image walkingI = LoadImage("Data/BanditYoshiWalking.png");
	banditYoshi.walkingRight = LoadTextureFromImage(walkingI);
	ImageFlipHorizontal(&walkingI);
	banditYoshi.walkingLeft  = LoadTextureFromImage(walkingI);
	banditYoshi.walking = banditYoshi.walkingRight;
	UnloadImage(walkingI);
	banditYoshi.currentWalkingFrame = 0;
	banditYoshi.frameWalkingCounter = 0;
	banditYoshi.frameWalkingSpeed = 8;
	banditYoshi.frameRectWalking.x = 0.0f;
	banditYoshi.frameRectWalking.y = 0.0f;
	banditYoshi.frameRectWalking.width = (float)banditYoshi.walking.width/5.0f;
	banditYoshi.frameRectWalking.height = (float)banditYoshi.walking.height;

	Image idleI = LoadImage("Data/BanditYoshiIdle.png");
	banditYoshi.idleRight = LoadTextureFromImage(idleI);
	ImageFlipHorizontal(&idleI);
	banditYoshi.idleLeft = LoadTextureFromImage(idleI);
	banditYoshi.idle = banditYoshi.idleRight;
	UnloadImage(idleI);
	banditYoshi.frameRectIdle.x = 0.0f;
	banditYoshi.frameRectIdle.y = 0.0f;
	banditYoshi.frameRectIdle.width = (float)banditYoshi.idle.width;
	banditYoshi.frameRectIdle.height = (float)banditYoshi.idle.height;

	Image jumpingI = LoadImage("Data/BanditYoshiJumping.png");
	banditYoshi.jumpingRight = LoadTextureFromImage(jumpingI);
	ImageFlipHorizontal(&jumpingI);
	banditYoshi.jumpingLeft = LoadTextureFromImage(jumpingI);
	banditYoshi.jumping = banditYoshi.jumpingRight;
	UnloadImage(jumpingI);
	banditYoshi.frameRectJumping.x = 0.0f;
	banditYoshi.frameRectJumping.y = 0.0f;
	banditYoshi.frameRectJumping.width = (float)banditYoshi.jumping.width/3.0f;
	banditYoshi.frameRectJumping.height = (float)banditYoshi.jumping.height;

	banditYoshi.position.x = 50.0f;
	banditYoshi.position.y = 50.0f;
	banditYoshi.speed = 30.0f;
	banditYoshi.direction = 1;
	banditYoshi.isWalking = false;

	return banditYoshi;
}

void UpdateEntityPlayer(entity *e, float delta)
{
	if(IsKeyDown(KEY_RIGHT))
	{
		e->position.x += e->speed*delta;
		e->isWalking = true;
		e->walking = e->walkingRight;
		e->idle = e->idleRight;
		e->direction = 1;
	}
	else if(IsKeyDown(KEY_LEFT))
	{
		e->position.x -= e->speed*delta;
		e->isWalking = true;
		e->walking = e->walkingLeft;
		e->idle = e->idleLeft;
		e->direction = -1;
	}
	else
	{
		e->isWalking = false;
	}

	if(e->isWalking)
	{
		++e->frameWalkingCounter;

		if(e->frameWalkingCounter >= (60/e->frameWalkingSpeed))
		{
			e->frameWalkingCounter = 0;
			e->currentWalkingFrame = ((e->currentWalkingFrame + e->direction) + 5) % 5;

			e->frameRectWalking.x = (float)e->currentWalkingFrame*(float)e->walking.width/5.0f;
		}
	}

	else
	{
		e->frameWalkingCounter = 0;
		e->currentWalkingFrame = 0;
		e->frameRectWalking.x = 0.0f;
	}
}

void DrawEntity(entity *e)
{
	if(e->isWalking)
	{
		DrawTextureRec(e->walking, e->frameRectWalking, e->position, WHITE);
	}
	else
	{
		DrawTextureRec(e->idle, e->frameRectIdle, e->position, WHITE);
	}
}

void UnloadEntityTextures(entity *e)
{
	UnloadTexture(e->walkingRight);
	UnloadTexture(e->walkingLeft);
	UnloadTexture(e->idleRight);
	UnloadTexture(e->idleLeft);
	UnloadTexture(e->jumpingRight);
	UnloadTexture(e->jumpingLeft);
}