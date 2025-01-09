#include "GameScene.h"

#include <cassert>

GameScene::GameScene(){};
GameScene::~GameScene() {
	delete model_;
	delete mapchip_;
	// delete box_;
	for (Box* box : boxes) {
		delete box;
	}

	for (Gate* gate : gates) {
		delete gate;
	}

	for (std::vector<WorldTransform*> blockLine : blocks_) {
		for (WorldTransform* block : blockLine) {
			delete block;
		}
	}
	blocks_.clear();
};

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	texture = TextureManager::Load("white1x1.png");
	
	viewProjection_.Initialize();
	worldTransform_.Initialize();
	
	mapchip_ = new MapChip();
	mapchip_->LordCSV("Resources/stage.csv");

	model_ = Model::Create();


	uint32_t kMapHeight = mapchip_->GetNumVirtical();
	uint32_t kMapWight = mapchip_->GetNumHorizontal();

	blocks_.resize(kMapHeight);
	for (uint32_t i = 0; i < kMapWight; i++) {
		blocks_[i].resize(kMapWight);
	}

	for (uint32_t i = 0; i < kMapHeight; ++i) {
		for (uint32_t j = 0; j < kMapWight; ++j) {
			if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kWall) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				blocks_[i][j] = worldTransform;		
				blocks_[i][j]->translation_ = mapchip_->GetMapChipPosition(j, i);
				if (isGate) {
					isGate = false;
					isA = true;
				}
			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kBox) {
				
				Box* box = new Box();
				box->Initialize(model_,&viewProjection_,mapchip_->GetMapChipPosition(j, i));
				boxes.push_back(box);
			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kGate) {
				Gate* gate = new Gate();
				gate->Initialize(model_, &viewProjection_, mapchip_->GetMapChipPosition(j, i));
				gates.push_back(gate);

				if (!isGate) {
					isGate = true;
				}
				if(isA){
					gatesList[1].push_back(gate);
				} else  {
					gatesList[0].push_back(gate);
				}
			}
		}
	}
			

}

void GameScene::Update() { 
	//box_->Update();

	for (std::vector<WorldTransform*> blockLine : blocks_) {
		for (WorldTransform* block : blockLine) {
			if (!block) {
				continue;
			} else {
				block->UpdateMatrix();
			}
		}
	}

	for (Box* box : boxes) {
		box->Update();
	}


	for (Gate* gate : gatesList[0]) {
		gate->Update();
		if (input_->PushKey(DIK_1)) {
			gate->OpenGate();
		} else {
			gate->CloseGate();
		}
	}

	for (Gate* gate : gatesList[1]) {
		gate->Update();
		if (input_->PushKey(DIK_2)) {
			gate->OpenGate();
		} else {
			gate->CloseGate();
		}
	}
};

void GameScene::Draw() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///
	
	//box_->Draw();
	for (Box* box : boxes) {
		box->Draw();
	}

	for (Gate* gate : gates) {
		gate->Draw();
	}

	for (std::vector<WorldTransform*> blockLine : blocks_) {
		for (WorldTransform* block : blockLine) {
			if (!block) {
				continue;
			} else {
				model_->Draw(*block, viewProjection_,texture);
			}
		}
	}

	/// </summary>

	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}