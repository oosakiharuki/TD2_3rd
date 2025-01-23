#pragma once
#include "KamataEngine.h"
//#include "2d/Sprite.h"

class Fade;

class SelectScene {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

public:
	SelectScene();
	~SelectScene();
	void Initialize();
	void Update();
	void Draw();
	bool IsFinished() const { return finished_; }
	const char* SetStageNum() { return nowStage; }

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	XINPUT_STATE state, preState;
	bool finished_ = false;
	int number = 1;
	int MaxStage = 5;
	const char* stage[5];//MaxStageと合わせて変えてね

	const char* nowStage;
	KamataEngine::Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0u;
	KamataEngine::Vector2 texLT = {0, 0};
	KamataEngine::Vector2 texSize = {64, 64};

	Fade* fade_ = nullptr;
	float fadeTime_ = 0.5f;

	Phase phase_ = Phase::kFadeIn;
};