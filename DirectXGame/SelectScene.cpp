#include "SelectScene.h"

using namespace KamataEngine;

SelectScene::SelectScene() {}
SelectScene::~SelectScene() { delete sprite_; }

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
}

void SelectScene::Update() {

	if (number < MaxStage) {
		if (input_->TriggerKey(DIK_D) || 
		(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {		
			number++;
			texLT.x += 64;
		}
	}

	if (number > 1) {
		if (input_->TriggerKey(DIK_A) || 
			(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			number--;
			texLT.x -= 64;
		}
	}
	sprite_->SetTextureRect(texLT, texSize);

	

	if (input_->TriggerKey(DIK_SPACE) || 
		(state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
		nowStage = stage[number - 1];//配列に合わせるため
		finished_ = true;
	}
}

void SelectScene::Draw() { 
	sprite_->PreDraw(dxCommon_->GetCommandList()); 
	sprite_->Draw();
	sprite_->PostDraw();

}
