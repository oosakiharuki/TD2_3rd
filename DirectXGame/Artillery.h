#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
#include <list>
class Bullet;
class Artillery {
public:
	~Artillery();
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Camera* camera, KamataEngine::Vector3 position);

	// 更新
	void Update();

	// 描画
	void Draw();

	void Fire();
	void OnCollision();
	KamataEngine::Vector3 GetWorldPostion() { return worldTransform_.translation_; }
	float GetRadius() { return radius_; }
	std::list<Bullet*> GetBullets() { return bullets_; }
	// 発射間隔
	static const int kFireInterval = 100;

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::WorldTransform worldTransform2_;
	KamataEngine::ObjectColor objColor = {};
	int Timer_;
	// bool Flag = false;
	float radius_ = 1.0f;
	std::list<Bullet*> bullets_;
	bool isDead=false;
};