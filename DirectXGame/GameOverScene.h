#include "audio/Audio.h"
#include "base/DirectXCommon.h"
#include "input/Input.h"
#include "3d/Model.h"
#include "2d/Sprite.h"
#include "3d/Camera.h"
#include "3d/WorldTransform.h"
#include "Fade.h"


class GameOverScene {
public:
	enum class Select { kContinue, kGoTitle };

	enum class Phase { kFadeIn, kMain, kFadeOut };

	GameOverScene();
	~GameOverScene();

	void Initialise();
	void Update();
	void Draw();

	Select GetSelect() const { return select_; }
	bool IsFinished() const { return finished_; }
	void SetDeasZone(int deadZone1) {this->deadZone=deadZone1;}

private:
	void UpdateCursorSelection(int maxNum, int deadZone);

	KamataEngine::DirectXCommon* dxCommon_;
	KamataEngine::Input* input_;
	KamataEngine::Audio* audio_;

	Fade* fade_;
	KamataEngine::Sprite* wallpaperSprite_;
	KamataEngine::Sprite* gameOverSprite_;
	KamataEngine::Sprite* cursorSprite_;
	KamataEngine::Vector2 selectCursorPos;
	int wallpaperTexture_;
	int gameOverTexture_;
	int cursorTexture_;

	Phase phase_ = Phase::kFadeIn;
	Select select_;
	bool finished_ = false;

	int selectNum = 1;
	int deadZone;
	XINPUT_STATE state, preState;
};