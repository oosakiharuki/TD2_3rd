#pragma once
#include "AABB.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
class Player;
class Box;
class Door1 {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position, KamataEngine::Vector3 speed);
	

	void Update();

	void Draw();

	void OnCollision(Player*player);
	void OnCollisionBox(Box* box);
	void SetCorrectionPos(Player* player);
	void Resetcorrection() { correctionPos = {0, 0, 0}; }
	void SetFlag(bool Flag1, bool Flag2);
	void SetFlagSwitch(bool Flag);
	void Vartical();

	void ReSetClose();

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	

	KamataEngine::WorldTransform worldTransform_;
	

	KamataEngine::ObjectColor objColor = {};
	bool Flag;
	bool FlagSwitch;
	KamataEngine::Vector3 kSpeed;
	KamataEngine::Vector3 kReturnSpeed;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;

	//当たり判定用のサイズ
	float sizeX = 0;
	float sizeY = 0;

	// 当たり判定用のサイズ
	float sizeXswitch = 0;
	float sizeYswitch = 0;
	
	Rect rect;
	KamataEngine::Vector3 correctionPos;

	bool isVartical = false;
	bool CloseFlag = false;
	//一瞬で押してドアが止まらないようにするFlag
	bool doorMove = false;

	KamataEngine::Vector3 ResetPosition;
	KamataEngine::Vector3 ResetSpeed;
};
