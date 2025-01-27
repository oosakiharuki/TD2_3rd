#include "SelectScene.h"
#include "Fade.h"

using namespace KamataEngine;

SelectScene::SelectScene() {}
SelectScene::~SelectScene() { 
	delete sprite_; 
	delete fade_;
}

void SelectScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ステージ名
	stage[0] = "Resources/stageCsv/stage01.csv";
	stage[1] = "Resources/stageCsv/stage02.csv";
	stage[2] = "Resources/stageCsv/stage03.csv";
	stage[3] = "Resources/stageCsv/stage04.csv";
	stage[4] = "Resources/stageCsv/stage05.csv";

	textureHandle_ = TextureManager::Load("Numbers.png");
	sprite_ = Sprite::Create(textureHandle_, Vector2(0, 0));
	sprite_->SetSize(Vector2{64, 64});
	sprite_->SetTextureRect(texLT, texSize);

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, fadeTime_);
}

void SelectScene::Update() {
	input_->GetJoystickState(0, state);
	input_->GetJoystickStatePrevious(0, preState);

	// 左スティックの入力デッドゾーンの設定
	const int deadZone = 8000;

	switch (phase_) {
	case SelectScene::Phase::kFadeIn:
		fade_->Update();
		if (fade_->IsFinished()) {
			fade_->Stop();
			phase_ = Phase::kMain;
		}
		break;
	case SelectScene::Phase::kMain:
		// ステージ選択 (右)
		if (number < MaxStage) {
			if (input_->TriggerKey(DIK_D) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ||
			    (state.Gamepad.sThumbLX > deadZone && preState.Gamepad.sThumbLX <= deadZone)) {
				number++;
				texLT.x += 64;
			}
		}

		// ステージ選択 (左)
		if (number > 1) {
			if (input_->TriggerKey(DIK_A) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ||
			    (state.Gamepad.sThumbLX < -deadZone && preState.Gamepad.sThumbLX >= -deadZone)) {
				number--;
				texLT.x -= 64;
			}
		}

		sprite_->SetTextureRect(texLT, texSize);

		// 決定ボタン
		if (input_->TriggerKey(DIK_SPACE) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			nowStage = stage[number - 1]; // 配列に合わせるため
			fade_->Start(Fade::Status::FadeOut, fadeTime_);
			phase_ = Phase::kFadeOut;
		}
		break;
	case SelectScene::Phase::kFadeOut:
		fade_->Update();
		if (fade_->IsFinished()) {
			fade_->Stop();
			finished_ = true;
		}
		break;
	}
}


void SelectScene::Draw() { 
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList(); 

	sprite_->PreDraw(commandList); 
	sprite_->Draw();
	sprite_->PostDraw();

	fade_->Draw(commandList);
}
