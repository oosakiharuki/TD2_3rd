#include "GameScene.h"

#include <cassert>

GameScene::GameScene(){};
GameScene::~GameScene() {
	delete model_;

	delete modelElectricity1_;
	delete modelElectricity2_;
	delete modelWall1_;
	delete modelWall2_;
	delete modelBrokenBox_;
	
	delete electricityGimmick_;

	delete modelPlayer_;
	delete modelCarryRope_;
	delete modelHopRope_;
	delete mapchip_;

	delete player1_;
	delete player2_;

	delete rope_;
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

	delete brokenBox_;

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

	modelElectricity1_ = Model::Create();
	modelElectricity2_ = Model::Create();
	modelWall1_ = Model::Create();
	modelWall2_ = Model::Create();
	modelBrokenBox_ = Model::Create();
	modelPlayer_ = Model::CreateFromOBJ("Player", true);
	modelCarryRope_ = Model::CreateFromOBJ("Rope", true);
	modelHopRope_ = Model::CreateFromOBJ("hopRope", true);

	//電気ギミック
	electricityGimmick_ = new Electricity;
	electricityGimmick_->Initialize(modelElectricity1_, modelElectricity2_, modelWall1_, modelWall2_, &viewProjection_);

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



	player1_ = new Player();
	player1_->Initialize(playerPosition[0], modelPlayer_, 1);

	player2_ = new Player();
	player2_->Initialize(playerPosition[1], modelPlayer_, 2);
	
	rope_ = new Rope();
    rope_->Initialize(player1_, player2_, input_, modelCarryRope_, modelHopRope_);
	rope_->SetBoxes(boxes);


	brokenBox_ = new BrokenBox();
	brokenBox_->Initialize(modelBrokenBox_, &viewProjection_);
	brokenBox_->SetBoxes(boxes);
}

void GameScene::Update() { 
	//box_->Update();

	CheckAllCollisions();
	
	electricityGimmick_->Update();
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


	brokenBox_->Update();

	// プレイヤーの更新
	player1_->Update();
	player2_->Update();

	rope_->Update();

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
	

	
	electricityGimmick_->Draw();

	// プレイヤーの描画
	player1_->Draw(&viewProjection_);
	player2_->Draw(&viewProjection_);

	rope_->Draw(&viewProjection_);

	//mapchip_->Draw();

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

	brokenBox_->Draw();


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

void GameScene::CheckAllCollisions() { 
	KamataEngine::Vector3 posA, posB; 

	float boxRadius = 1.0f;
	float brokenBoxRadius = 1.0f;

	#pragma region 壊れる箱と箱の当たり判定
	// 壊れる箱の座標
	posA = brokenBox_->GetWorldPosition();
	
	// 壊れる箱と箱全ての当たり判定
	for (Box* box : boxes) {
		// 箱の座標
		posB = box->GetWorldPosition();
    	KamataEngine::Vector3 diff = {posB.x - posA.x, posB.y - posA.y, posB.z - posA.z};
    	float distanceSquared = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

    	float radiusSum = brokenBoxRadius + boxRadius;

    	// 球と球の交差判定
    	if (distanceSquared <= (radiusSum * radiusSum)) {
			brokenBox_->OnCollision();
    	}
	}
	#pragma endregion

}
