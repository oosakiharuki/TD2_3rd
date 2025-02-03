#include "3d/Camera.h"

class Rope;

class CameraController {
public:

	struct Rect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};

	void Initialize();
	void Update();
	void SetTraget(Rope* target) { target_ = target; }
	void Reset();
	const KamataEngine::Camera& GetViewProjection() const { return viewProjection_; }

	void SetMovebleaArea(Rect area) { movableArea_ = area; };

private:
	KamataEngine::Camera viewProjection_;
	Rope* target_ = nullptr;
	KamataEngine::Vector3 targetOffset_ = {0.0f, 0.0f, -40.0f};

	Rect movableArea_ = {0, 100, 0, 100};
	// 追従対象の各方向へのカメラ移動範囲
	static inline const Rect kMargin = {-0.5f, 0.5f, -4.0f, 4.0f};
};