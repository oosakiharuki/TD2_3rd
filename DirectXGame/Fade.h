#pragma once
#include "2d/Sprite.h"
#include "base/DirectXCommon.h"

/// <summary>
/// フェード
/// <summary>
class Fade {
public:
	enum class Status {
		None,
		FadeIn,
		FadeOut,
	};

public:
	void Initialize();

	void Update();

	void Draw(ID3D12GraphicsCommandList* commandlist);

	// フェード開始
	void Start(Status status, float duration);

	// フェード停止
	void Stop();

	// フェード終了判定
	bool IsFinished() const;

private:
	uint32_t textureHandle_ = 0;
	KamataEngine::Sprite* sprite_ = nullptr;
	// 現在のフェードの状態
	Status status_ = Status::None;
	// フェードの持続時間
	float duration_ = 0.0f;
	// 経過時間カウンター
	float counter_ = 0.0f;
};