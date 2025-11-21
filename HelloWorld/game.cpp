#include "game.h"
#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "paddle.h"

void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 340 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
}

//Updates ball and checks collisions
void StepFrame(float) {
	
	//Draws the bricks
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int i = 0; i < brickIds.size(); i++) {
		Play::UpdateGameObject(Play::GetGameObject(brickIds[i]));

		Play::DrawObject(Play::GetGameObject(brickIds[i])); //SHOULD ALWAYS BE LAST
	}

	// handles collisions with objects
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++) {
		
		//stores current ball for ease of use
		GameObject& ball = Play::GetGameObject(ballIds[i]);
		

		Play::UpdateGameObject(ball);
		
		//screen edge collision
		//Reverse Horizontal Velocity
		if ((int(ball.pos.x) >= int(DISPLAY_WIDTH) - 8) || int(ball.pos.x) <= 0) {
			ball.velocity.x = ball.velocity.x * -1;
		}
		// Reverse Vertical Velocity
		if ((int(ball.pos.y) >= int(DISPLAY_HEIGHT) - 8) || int(ball.pos.y) <= 0) {
			ball.velocity.y = ball.velocity.y * -1;
		}

		//brick collision
		for (int i2 = 0; i2 < brickIds.size(); i2++) {
			if (Play::IsColliding(ball, Play::GetGameObject(brickIds[i2]))) {
				Play::DestroyGameObject(brickIds[i2]);
				ball.velocity.y = ball.velocity.y * -1;
			}
				
		}

		//paddle collision
		if (IsColliding(*paddle, ball)) {
			ball.velocity.y = ball.velocity.y * -1;
		}

		//draws the balls
		Play::DrawObject(ball); //SHOULD ALWAYS BE LAST
	}
}

//creates all the brick game objects
void SetupScene() { // 35x8 bricks
	for (int i = 0; i < 36; i++) {
		for (int i2 = 0; i2 < 10; i2++) {
			if (i == 0 || i == 35)
				break;
				
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { (DISPLAY_WIDTH - 10) - (i+1) * 17, (DISPLAY_HEIGHT - 20) - (i2+1) * 11}, 6, "brick");
		}
	}
}

