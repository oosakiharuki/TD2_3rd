#include "GameOverScene.h"

#include "base/TextureManager.h"

GameOverScene::GameOverScene() {}

GameOverScene::~GameOverScene() {
	delete fade_;
	delete wallpaperSprite_;
	delete gameOverSprite_;
	delete cursorSprite_;
}

void GameOverScene::Initialise() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	audio_ = KamataEngine::Audio::GetInstance();

	wallpaperTexture_ = KamataEngine::TextureManager::Load("wallpaper.jpg");
	wallpaperSprite_ = KamataEngine::Sprite::Create(wallpaperTexture_, {0.0f, 0.0f});

	gameOverTexture_ = KamataEngine::TextureManager::Load("clear.png");
	gameOverSprite_ = KamataEngine::Sprite::Create(gameOverTexture_, {200.0f, 100.0f});

	cursorTexture_ = KamataEngine::TextureManager::Load("cursor.png");
	cursorSprite_ = KamataEngine::Sprite::Create(cursorTexture_, {150.0f, 275.0f});

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 30);
}

void GameOverScene::Update() {
	input_->GetJoystickState(0, state);
	input_->GetJoystickStatePrevious(0, preState);

	switch (phase_) {
	case Phase::kFadeIn:
		fade_->Update();
		if (fade_->IsFinished()) {
			fade_->Stop();
			phase_ = Phase::kMain;
		}
		break;

	case Phase::kMain:
		// カーソルの選択肢を更新
		UpdateCursorSelection(2, deadZone);
		

		// 決定ボタン（Space / Aボタン）で次のフェーズへ進む
		if (input_->TriggerKey(DIK_SPACE) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			fade_->Start(Fade::Status::FadeOut, 30);
			phase_ = Phase::kFadeOut; // フェードアウトに進む
		}
		break;

	case Phase::kFadeOut:
		fade_->Update();
		if (fade_->IsFinished()) {
			fade_->Stop();
			finished_ = true;
		}
		break;
	}
}

void GameOverScene::UpdateCursorSelection(int maxNum, int deadZone2) {
	// 下方向への入力処理
	if (input_->TriggerKey(DIK_S) || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) ||
	    (state.Gamepad.sThumbLY < -deadZone2 && preState.Gamepad.sThumbLY >= -deadZone2)) {
		selectNum++;
	}

	// 上方向への入力処理
	if (input_->TriggerKey(DIK_W) || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) ||
	    (state.Gamepad.sThumbLY > deadZone2 && preState.Gamepad.sThumbLY <= deadZone2)) {
		selectNum--;
	}

	// 範囲制限（ループするように設定）
	if (selectNum < 1) {
		selectNum = maxNum;
	} else if (selectNum > maxNum) {
		selectNum = 1;
	}
	// カーソルの位置を更新（選択されている項目に合わせて移動）
	cursorSprite_->SetPosition({150.0f, 275.0f + 100.0f * (selectNum - 1)});
}
void GameOverScene::Draw() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	KamataEngine::Sprite::PreDraw(commandList);
	wallpaperSprite_->Draw();
	KamataEngine::Sprite::PostDraw();
	dxCommon_->ClearDepthBuffer();

	KamataEngine::Sprite::PreDraw(commandList);
	gameOverSprite_->Draw();
	cursorSprite_->Draw();
	fade_->Draw(commandList);
	KamataEngine::Sprite::PostDraw();
}
