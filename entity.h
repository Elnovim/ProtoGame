#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

typedef struct
{
	Texture2D walkingRight;
	Texture2D walkingLeft;
	Texture2D walking;
	Rectangle frameRectWalking;
	int currentWalkingFrame;
	int frameWalkingCounter;
	int frameWalkingSpeed;

	Texture2D idleRight;
	Texture2D idleLeft;
	Texture2D idle;
	Rectangle frameRectIdle;

	Texture2D jumpingRight;
	Texture2D jumpingLeft;
	Texture2D jumping;
	Rectangle frameRectJumping;

	Vector2 position;
	float speed;
	int direction;
	bool isWalking;
} entity;

entity LoadBanditYoshi();

// TODO : Sûrement faudra-t-il mieux passer aussi les inputs pour ne pas tester tous les mêmes inputs à chque update ?
void UpdateEntityPlayer(entity *e, float delta);
void DrawEntity(entity *e);

void UnloadEntityTextures(entity *e);

#endif