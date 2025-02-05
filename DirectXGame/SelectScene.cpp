#include "SelectScene.h"
#include "Fade.h"

using namespace KamataEngine;

SelectScene::SelectScene() {}
SelectScene::~SelectScene() { 
	delete sprite_; 
	delete wallpaperSprite_;
	delete selectSprite_;
	delete keyCtrlSprite_;
	delete padCtrlSprite_;
	delete menuSprite_;
	delete cursorSprite_;
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
	stage[5] = "Resources/stageCsv/stage06.csv";
	stage[6] = "Resources/stageCsv/stage07.csv";
	stage[7] = "Resources/stageCsv/stage08.csv";
	stage[8] = "Resources/stageCsv/stage09.csv";
	stage[9] = "Resources/stageCsv/stage10.csv";
	stage[10] = "Resources/stageCsv/stage11.csv";
	stage[11] = "Resources/stageCsv/stage12.csv";
	stage[12] = "Resources/stageCsv/stage13.csv";
	stage[13] = "Resources/stageCsv/stage14.csv";
	stage[14] = "Resources/stageCsv/stage15.csv";

	textureHandle_ = TextureManager::Load("numbersSheet.png");
	sprite_ = Sprite::Create(textureHandle_, Vector2(450, 230));
	sprite_->SetSize(Vector2{368, 256});
	sprite_->SetTextureRect(texLT, texSize);

	wallpaperTexture_ = KamataEngine::TextureManager::Load("wallpaper.jpg");
	selectTexture_ = KamataEngine::TextureManager::Load("select.png");
	keyCtrlTexture_ = KamataEngine::TextureManager::Load("keyCtrl.png");
	padCtrlTexture_ = KamataEngine::TextureManager::Load("padCtrl.png");
	menuTexture_ = KamataEngine::TextureManager::Load("ctrlMenu.png");
	cursorTexture_ = KamataEngine::TextureManager::Load("cursor.png");

	wallpaperSprite_ = KamataEngine::Sprite::Create(wallpaperTexture_, {0.0f, 0.0f});
	selectSprite_ = KamataEngine::Sprite::Create(selectTexture_, {0.0f, 0.0f});
	keyCtrlSprite_ = KamataEngine::Sprite::Create(keyCtrlTexture_, {0.0f, 0.0f});
	padCtrlSprite_ = KamataEngine::Sprite::Create(padCtrlTexture_, {0.0f, 0.0f});
	menuSprite_ = KamataEngine::Sprite::Create(menuTexture_ , {0.0f, 0.0f});
	cursorSprite_ = KamataEngine::Sprite::Create(cursorTexture_, selectCursorPos);

	bgmDataHandle_ = audio_->LoadWave("bgm.wav");
	bgmVoiceHandle_ = audio_->PlayWave(bgmDataHandle_, true, 0.3f);

	buttonDataHande_ = audio_->LoadWave("button.wav");
	selectDataHandle_ = audio_->LoadWave("select.wav");
	menuButtonDataHandle_ = audio_->LoadWave("menuButton.wav");

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, fadeTime_);
}

void SelectScene::Update() {
	input_->GetJoystickState(0, state);
	input_->GetJoystickStatePrevious(0, preState);
	const int deadZone = 8000;

	CheckControl(deadZone);

    // メニューを閉じた直後の誤入力防止（一定時間だけキー入力を無視する）
	if (menuClosedRecently) {
		menuCloseTimer--;
		if (menuCloseTimer <= 0) {
			menuClosedRecently = false;
		}
		return; // ここで return することで一時的に入力を無視
	}

	if (!menuON) {
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
					selectVoiceHandle_ = audio_->PlayWave(selectDataHandle_, false, 0.5f);
    				number++;
     				texLT.x += 368;
    			}
    		}

    		// ステージ選択 (左)
    		if (number > 1) {
    			if (input_->TriggerKey(DIK_A) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ||
    			    (state.Gamepad.sThumbLX < -deadZone && preState.Gamepad.sThumbLX >= -deadZone)) {
					selectVoiceHandle_ = audio_->PlayWave(selectDataHandle_, false);
    				number--;
    				texLT.x -= 368;
    			}
    		}

    		sprite_->SetTextureRect(texLT, texSize);

    		// 決定ボタン
    		if (input_->TriggerKey(DIK_SPACE) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
    			nowStage = stage[number - 1]; // 配列に合わせるため
				audio_->StopWave(bgmVoiceHandle_);
				buttonVoiceHandle_ = audio_->PlayWave(buttonDataHande_, false );
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

}


void SelectScene::Draw() { 
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
	sprite_->Draw();
	selectSprite_->Draw();

	if (menuON) {
		menuSprite_->Draw();
		cursorSprite_->Draw();
	}
	if (ctrlOpen) {
    	switch (ctrl_) {
    	case SelectScene::Ctrl::kKey:
			keyCtrlSprite_->Draw();
    		break;
    	case SelectScene::Ctrl::kPad:
			padCtrlSprite_->Draw();
    		break;
    	}
	}


	fade_->Draw(commandList);
	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
}

void SelectScene::CheckControl(int deadZone) {
	if (input_->TriggerKey(DIK_ESCAPE) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_START)) {
		menuButtonVoiceHandle_ = audio_->PlayWave(menuButtonDataHandle_, false);
		if (!menuON) {
    		menuON = true;
		} else {
			ctrlOpen = false;
			ctrl_ = Ctrl::kNone;
			menuON = false;
			phase_ = Phase::kMain;
			selectNum = 1;
		}
	}

	if (menuON && ctrl_ == Ctrl::kNone) {
		// 通常ステージの選択
		std::vector<float> cursorPositions = {275.0f, 360.0f, 450.0f};
		// カーソル移動処理を関数でまとめて呼び出し
		UpdateCursorSelection(3, deadZone);

		// カーソル位置の更新
		selectCursorPos.y = cursorPositions[selectNum - 1];
		cursorSprite_->SetPosition(selectCursorPos);

		if (input_->TriggerKey(DIK_SPACE) || 
			((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A))) {
			buttonVoiceHandle_ = audio_->PlayWave(buttonDataHande_, false, 0.5f);
			switch (selectNum) {
			case 1:
				ctrl_ = Ctrl::kKey;
    			ctrlOpen = true;
				break;
			case 2:
				ctrl_ = Ctrl::kPad;
				ctrlOpen = true;
				break;
			case 3:
				menuON = false;
				phase_ = Phase::kMain;

                // メニュー閉じた直後は入力を受け付けない
				menuClosedRecently = true;
				menuCloseTimer = menuCloseDelay; // 10フレーム無視
				break;
			}

		}
	} else if (ctrlOpen && ctrl_ != Ctrl::kNone) {
		if (input_->TriggerKey(DIK_SPACE) || 
			((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A))) {
			menuButtonVoiceHandle_ = audio_->PlayWave(menuButtonDataHandle_, false);
			ctrlOpen = false;
			ctrl_ = Ctrl::kNone;
			menuON = false;
			phase_ = Phase::kMain;
			selectNum = 1;

            // メニュー閉じた直後は入力を受け付けない
			menuClosedRecently = true;
			menuCloseTimer = menuCloseDelay; // 10フレーム無視
		}
	}
}

// カーソル移動を処理する関数
void SelectScene::UpdateCursorSelection(int maxNum, int deadZone) {
	// 下方向への入力処理
	if (input_->TriggerKey(DIK_S) || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) ||
	    (state.Gamepad.sThumbLY < -deadZone && preState.Gamepad.sThumbLY >= -deadZone)) {
		selectVoiceHandle_ = audio_->PlayWave(selectDataHandle_, false);
		selectNum++;
	}

	// 上方向への入力処理
	if (input_->TriggerKey(DIK_W) || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) ||
	    (state.Gamepad.sThumbLY > deadZone && preState.Gamepad.sThumbLY <= deadZone)) {
		selectVoiceHandle_ = audio_->PlayWave(selectDataHandle_, false);
		selectNum--;
	}

	// 範囲制限（ループするように設定）
	if (selectNum < 1) {
		selectNum = maxNum;
	} else if (selectNum > maxNum) {
		selectNum = 1;
	}
}

