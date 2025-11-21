#pragma once
#include "paddle.h"
#include "game.h"


Paddle* paddle = new Paddle();


void DrawPaddle(Paddle paddle) {
	Play::Vector2f tr(paddle.x + paddle.paddleSize, paddle.y + 2);
	Play::Vector2f bl(paddle.x - paddle.paddleSize, paddle.y - 2);
	Play::DrawRect(bl, tr, Play::Colour(Play::cWhite));
}

//paddle movement
void UpdatePaddle() {
	if (Play::KeyDown(Play::KEY_LEFT)) {
		paddle->x -= 3;
	}
	else if (Play::KeyDown(Play::KEY_RIGHT)) {
		paddle->x += 3;
	}
}

//checks collision between paddle and the ball
bool IsColliding(const Paddle& paddle, const Play::GameObject& ball) {
	
	Play::Vector2f tr(paddle.x + paddle.paddleSize, paddle.y + 2);
	Play::Vector2f bl(paddle.x - paddle.paddleSize, paddle.y - 2);

	const float dx = ball.pos.x - Min(tr.x, Max(ball.pos.x, bl.x));
	const float dy = ball.pos.y - Min(tr.y, Max(ball.pos.y, bl.y));
	return (dx * dx + dy * dy) < (ball.radius * ball.radius);
}

//returns highest number
float Max(float onef, float twof) {
	return (onef < twof ? twof : onef);
}

//returns lowest number
float Min(float onef, float twof) {
	return (onef > twof ? twof : onef);
}