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
	enum class Stage {
		stage1 = 1,
		stage2,
		stage3,
		stage4,
		stage5,
	};
	enum class Ctrl {
		kKey,
		kPad,
		kNone,
	};

public:
	SelectScene();
	~SelectScene();
	void Initialize();
	void Update();
	void Draw();
	bool IsFinished() const { return finished_; }
	const char* SetStageNum() { return nowStage; }
	Stage GetStageNum() const { return stage_; }

	void CheckControl(int deadZone);

	void UpdateCursorSelection(int maxNum, int deadZone);

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	XINPUT_STATE state, preState;
	// 左スティックの入力デッドゾーンの設定


	bool finished_ = false;
	int number = 1;
	int MaxStage = 6;
	const char* stage[20];//MaxStageと合わせて変えてね

	const char* nowStage;
	KamataEngine::Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0u;
	KamataEngine::Vector2 texLT = {0, 0};
	KamataEngine::Vector2 texSize = {368, 256};

	uint32_t wallpaperTexture_ = 0;
	uint32_t selectTexture_ = 0;
	uint32_t keyCtrlTexture_ = 0;
	uint32_t padCtrlTexture_ = 0;
	uint32_t menuTexture_ = 0;
	uint32_t cursorTexture_ = 0;

	KamataEngine::Sprite* wallpaperSprite_ = nullptr;
	KamataEngine::Sprite* selectSprite_ = nullptr;
	KamataEngine::Sprite* keyCtrlSprite_ = nullptr;
	KamataEngine::Sprite* padCtrlSprite_ = nullptr;
	KamataEngine::Sprite* menuSprite_ = nullptr;
	KamataEngine::Sprite* cursorSprite_ = nullptr;

	KamataEngine::Vector2 selectCursorPos = {450.0f, 275.0f};

	Fade* fade_ = nullptr;
	float fadeTime_ = 0.5f;

	bool menuON = false;
	bool ctrlOpen = false;
	int selectNum = 1;

	Phase phase_ = Phase::kFadeIn;
	Stage stage_ = Stage::stage1;
	Ctrl ctrl_ = Ctrl::kNone;

    bool menuClosedRecently = false; // メニュー閉じた直後かどうか
	int menuCloseTimer = 0;          // メニュー閉じた後のカウントダウン
	const int menuCloseDelay = 10;   // 10フレームの遅延を設定

	uint32_t bgmDataHandle_ = 0;
	uint32_t buttonDataHande_ = 0;
	uint32_t selectDataHandle_ = 0;
	uint32_t menuButtonDataHandle_ = 0;

	uint32_t bgmVoiceHandle_ = 0;
	uint32_t buttonVoiceHandle_ = 0;
	uint32_t selectVoiceHandle_ = 0;
	uint32_t menuButtonVoiceHandle_ = 0;
};