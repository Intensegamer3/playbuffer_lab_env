#pragma once
namespace Play { struct GameObject; }

struct Paddle {
	
	const int paddleSize = 50;
	int x = 50;
	const int y = 10;
} ;

void DrawPaddle(Paddle);
void UpdatePaddle();
bool IsColliding(const Paddle&,const Play::GameObject&);
float Max(float onef, float twof);
float Min(float onef, float twof);

//external reference for paddle for game.cpp
extern Paddle* paddle;