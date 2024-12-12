#include "Rope.h"
#include "Player.h"
#include <cassert>

void Rope::Initialize(Player* p1, Player* p2) { 
	assert(p1); 
	player1_ = p1;
	assert(p2);
	player2_ = p2;
}

void Rope::Update() {}

void Rope::Draw(KamataEngine::Camera* camera) {}
