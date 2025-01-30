#pragma once
#include <KamataEngine.h>
#include "MapChip.h"
#include "AABB.h"
#include "Box.h"
#include "BrokenBox.h"
#include "Gate.h"
#include"Artillery.h"
#include"Bullet.h"
#include"Electricity.h"
#include"Electricity2.h"

#include "Player.h"
#include "Rope.h"

#include "CameraController.h"
#include "Door1.h"

using namespace KamataEngine;

class Fade;

class GameScene {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kMenu,
		kClear,
		kFadeOut,
	};
	enum class Select {
		kGoStageSelect,
		kGoTitle,
		kGoNextStage,
		kNone,
	};

public:
	// ゲームシーン

	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

	void GenerateBlocks();

	void CheckAllCollision();

    /// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();
	void CheckBulletPlayerCollision();

	bool IsFinished() const { return finished_; }

	void GetStage(const char* number) { stageNum = number; }

	Select GetSelect() const { return select_; }

	// フェーズ切り替え
	void ChangePhase();

	void UpdateCursorSelection(int maxNum, int deadZone);

	void SwitchToNextStage();

	void ClearObject();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* model_ = nullptr;
	//ギミック用
	Model* modelElectricity1_ = nullptr;
	Model* modelElectricity2_ = nullptr;
	Model* modelWall1_ = nullptr;
	Model* modelWall2_ = nullptr;
	Model* modelBom=nullptr;
	Model* modelBom2 = nullptr;
	Model* modelBlock_ = nullptr;
	Model* modelBrokenBox_ = nullptr;
	Model* modelParticle_ = nullptr;
	Model* modelPlayer_ = nullptr;
	Model* modelPlayer1_ = nullptr;
	Model* modelPlayer2_ = nullptr;
	Model* modelCarryRope_ = nullptr;
	Model* modelHopRope_ = nullptr;
	Model* modelSwitch1_ = nullptr;
	Model* modelSwitch2_ = nullptr;

	WorldTransform worldTransform_;
	Camera viewProjection_;
	uint32_t texture = 0;
	uint32_t menuTexture_ = 0;
	uint32_t clearTexture_ = 0;
	uint32_t clearAllTexture_ = 0;
	uint32_t cursorTexture_ = 0;
	uint32_t wallpaperTexture = 0;

	Sprite* menuSprite_ = nullptr;
	Sprite* clearSprite_ = nullptr;
	Sprite* clearAllSirpte_ = nullptr;
	Sprite* cursorSprite_ = nullptr;
	Sprite* wallpaperSprite_ = nullptr;

	std::vector<std::vector<KamataEngine::WorldTransform*>> blocks_;
	std::list<Box*> boxes;
	
	std::list<Gate*> gates;
	std::list<Gate*> gatesList[5];//deleteはいらない
	bool isGate = false;
	uint32_t gateCount = 0u;
	uint32_t maxGate = 5; // とりあえず五個目安
	uint32_t playerNum = 0u;

	const char* stage[5];
	const char* stageNum;
	MapChip* mapchip_ = nullptr;

	bool isPair = false;
	// bool isPairVartical = false;

	std::list<Electricity*> electricity;
	std::list<Electricity2*> electricity2;
	std::list<Electricity*> electricitys[5];
	std::list<Electricity2*> electricitys2[5];
	uint32_t electNum = 0;
	// uint32_t HorizonNum = 0;
	
	std::list<Door1*> doors;
	std::list<Door1*> doorsList[5];
	uint32_t doorCount = 0;
	Artillery* artillery = nullptr;
	bool left[5] = {false};
	bool right[5] = {false};
	bool openFlag = false;

	Player* player1_ = nullptr;
	Player* player2_ = nullptr;

	Vector3 playerPosition[2]{
	    {2.5f, 3.0f, 0.0f},
        {5.0f, 3.0f, 0.0f}
    };
	Vector2 selectCursorPos = {450.0f, 275.0f};

	int selectNum = 1;

	Rope* rope_ = nullptr;
	std::list<BrokenBox*> brokenBoxes;

	CameraController* cameraController = nullptr;
	bool finished_ = false;
	bool clear_ = false;

	Fade* fade_ = nullptr;
	float fadeTime_ = 0.5f;

	Phase phase_ = Phase::kFadeIn;
	Select select_ = Select::kNone;

	XINPUT_STATE state, preState;

};