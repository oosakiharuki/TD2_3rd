#pragma once
#include "audio/Audio.h"
#include "base/DirectXCommon.h"
#include "input/Input.h"
#include "3d/Model.h"
#include "2d/Sprite.h"
#include "3d/Camera.h"
#include "3d/WorldTransform.h"

class Fade;

/// <summary>
/// タイトルシーン
/// </summry>
class TitleScene {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

public:
	TitleScene();

	~TitleScene();

	void Initialise();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	/// <summary>
	/// タイトルシーン用
	/// </summary>
	XINPUT_STATE state, preState;

	bool finished_ = false;

	Fade* fade_ = nullptr;
	float fadeTime_ = 0.5f;

	Phase phase_ = Phase::kFadeIn;

	uint32_t wallpaperTexture_ = 0;
	KamataEngine::Sprite* wallpaperSprite_ = nullptr;

	uint32_t titleTexture_ = 0;
	KamataEngine::Sprite* titleSprite_ = nullptr;

	uint32_t bgmDataHandle_ = 0;
	uint32_t buttonDataHande_ = 0;

	uint32_t bgmVoiceHandle_ = 0;
	uint32_t buttonVoiceHandle_ = 0;
};