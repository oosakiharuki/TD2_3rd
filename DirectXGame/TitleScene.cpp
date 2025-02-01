#include "TitleScene.h"
#include "Fade.h"
#include "base/TextureManager.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() { 
	delete fade_; 
	delete wallpaperSprite_;
	delete titleSprite_;
}

void TitleScene::Initialise() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	audio_ = KamataEngine::Audio::GetInstance();

	wallpaperTexture_ = KamataEngine::TextureManager::Load("wallpaper.jpg");
	wallpaperSprite_ = KamataEngine::Sprite::Create(wallpaperTexture_, {0.0f, 0.0f});

	titleTexture_ = KamataEngine::TextureManager::Load("title.png");
	titleSprite_ = KamataEngine::Sprite::Create(titleTexture_, {0.0f, 0.0f});

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, fadeTime_);
}

void TitleScene::Update() {
	input_->GetJoystickState(0, state);
	input_->GetJoystickStatePrevious(0, preState);

	switch (phase_) {
	case TitleScene::Phase::kFadeIn:
		fade_->Update();
		if (fade_->IsFinished()) {
			fade_->Stop();
			phase_ = Phase::kMain;
		}
		break;
	case TitleScene::Phase::kMain:
		if (input_->TriggerKey(DIK_SPACE) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			fade_->Start(Fade::Status::FadeOut, fadeTime_);
			phase_ = Phase::kFadeOut;
		}
		break;
	case TitleScene::Phase::kFadeOut:
		fade_->Update();
		if (fade_->IsFinished()) {
			fade_->Stop();
			finished_ = true;
		}
		break;
	}
}

void TitleScene::Draw() { 
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList(); 

	#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	wallpaperSprite_->Draw();
	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	titleSprite_->Draw(); 
	fade_->Draw(commandList);
	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
}
