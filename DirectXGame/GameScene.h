#pragma once
#include <KamataEngine.h>
#include "MapChip.h"
#include "AABB.h"
#include "Box.h"
#include "BrokenBox.h"
#include "Gate.h"

#include"Electricity.h"
#include"Electricity2.h"

#include "Player.h"
#include "Rope.h"

#include "CameraController.h"

using namespace KamataEngine;

class Fade;

class GameScene {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
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

	void CheckAllCollision();

    /// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	bool IsFinished() const { return finished_; }


	void GetStage(const char* number) { stageNum = number; }

	// フェーズ切り替え
	void ChangePhase();

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
	Model* modelBrokenBox_ = nullptr;
	Model* modelPlayer_ = nullptr;
	Model* modelCarryRope_ = nullptr;
	Model* modelHopRope_ = nullptr;

	WorldTransform worldTransform_;
	Camera viewProjection_;
	uint32_t texture = 0;

	std::vector<std::vector<KamataEngine::WorldTransform*>> blocks_;
	std::list<Box*> boxes;
	
	std::list<Gate*> gates;
	std::list<Gate*> gatesList[2];//deleteはいらない
	bool isGate = false;
	bool isA = false;


	const char* stageNum;
	MapChip* mapchip_ = nullptr;

	Electricity* electricityGimmick_;
	Electricity2* electricityGimmick2_;

	Player* player1_ = nullptr;
	Player* player2_ = nullptr;

	Vector3 playerPosition[2]{
	    {2.5f, 3.0f, 0.0f},
        {5.0f, 3.0f, 0.0f}
    };

	Rope* rope_ = nullptr;
	BrokenBox* brokenBox_ = nullptr;

	CameraController* cameraController = nullptr;
	bool finished_ = false;

	Fade* fade_ = nullptr;
	float fadeTime_ = 0.5f;

	Phase phase_ = Phase::kFadeIn;

	XINPUT_STATE state, preState;
};