#include "GameScene.h"
#include <cassert>
#include "Fade.h"

GameScene::GameScene(){};
GameScene::~GameScene() {
	delete model_;

	delete modelElectricity1_;
	delete modelElectricity2_;
	delete modelWall1_;
	delete modelWall2_;
	delete modelBlock_;
	delete modelBrokenBox_;
	delete modelParticle_;
	

	delete modelPlayer_;
	delete modelPlayer1_;
	delete modelPlayer2_;
	delete modelCarryRope_;
	delete modelHopRope_;
	delete modelBom;
	delete modelBom2;
	delete mapchip_;
	delete modelSwitch1_;
	delete modelSwitch2_;

	delete player1_;
	delete player2_;

	delete artillery;

	delete rope_;
	for (Box* box : boxes) {
		delete box;
	}
	boxes.clear();

	for (Gate* gate : gates) {
		delete gate;
	}
	gates.clear();

	for (Electricity* electrical : electricity) {
		delete electrical;
	}
	electricity.clear();
	for (Electricity2* electrical : electricity2) {
		delete electrical;
	}
	electricity2.clear();

	for (Door1* door : doors) {
		delete door;
	}
	doors.clear();


	for (std::vector<WorldTransform*> blockLine : blocks_) {
		for (WorldTransform* block : blockLine) {
			delete block;
		}
	}
	blocks_.clear();

	for (BrokenBox* brokenBox_ : brokenBoxes) {
		delete brokenBox_;
	}
	brokenBoxes.clear();

	delete cameraController;

	delete fade_;

	delete menuSprite_;
	delete clearSprite_;
	delete clearAllSirpte_;
	delete cursorSprite_;
	delete wallpaperSprite_;
	delete menuAttendSprite_;
};

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	texture = TextureManager::Load("white1x1.png");
	menuTexture_ = TextureManager::Load("nemu.png");
	clearTexture_ = TextureManager::Load("clear.png");
	clearAllTexture_ = TextureManager::Load("clearAll.png");
	cursorTexture_ = TextureManager::Load("cursor.png");
	wallpaperTexture = TextureManager::Load("wallpaper.jpg");
	menuAttendTexture_ = TextureManager::Load("menuAttend.png");

	menuSprite_ = Sprite::Create(menuTexture_, {0.0f, 0.0f});
	clearSprite_ = Sprite::Create(clearTexture_, {0.0f, 0.0f});
	clearAllSirpte_ = Sprite::Create(clearAllTexture_, {0.0f, 0.0f});
	cursorSprite_ = Sprite::Create(cursorTexture_, selectCursorPos);
	wallpaperSprite_ = Sprite::Create(wallpaperTexture, {0.0f, 0.0f});
	menuAttendSprite_ = Sprite::Create(menuAttendTexture_, {0.0f, 0.0f});
	
	viewProjection_.Initialize();
	worldTransform_.Initialize();

	// ステージ名
	stage[0] = "Resources/stageCsv/stage01.csv";
	stage[1] = "Resources/stageCsv/stage02.csv";
	stage[2] = "Resources/stageCsv/stage03.csv";
	stage[3] = "Resources/stageCsv/stage04.csv";
	stage[4] = "Resources/stageCsv/stage05.csv";
	
	mapchip_ = new MapChip();
	mapchip_->LordCSV(stageNum);

	model_ = Model::Create();

	modelElectricity1_ = Model::Create();
	modelElectricity2_ = Model::Create();
	modelWall1_ = Model::CreateFromOBJ("gate", true);
	modelWall2_ = Model::Create();
	modelBlock_ = Model::CreateFromOBJ("block", true);
	modelBrokenBox_ = Model::CreateFromOBJ("brokenBlock", true);
	modelParticle_ = Model::CreateFromOBJ("debris", true);
	modelPlayer_ = Model::CreateFromOBJ("Player", true);
	modelPlayer1_ = Model::CreateFromOBJ("player1", true);
	modelPlayer2_ = Model::CreateFromOBJ("player2", true);
	modelCarryRope_ = Model::CreateFromOBJ("carryRope", true);
	modelHopRope_ = Model::CreateFromOBJ("hopRope", true);
	modelBom = Model::CreateFromOBJ("Artillery", true);
	modelBom2 = Model::CreateFromOBJ("bom",true);
	modelSwitch1_ = Model::CreateFromOBJ("electroSwitch1", true);
	modelSwitch2_ = Model::CreateFromOBJ("electroSwitch2", true);

	GenerateBlocks();



	player1_ = new Player();
	player1_->Initialize(playerPosition[0], modelPlayer1_, 1);

	player2_ = new Player();
	player2_->Initialize(playerPosition[1], modelPlayer2_, 2);
	
	rope_ = new Rope();
    rope_->Initialize(player1_, player2_, input_, modelCarryRope_, modelHopRope_);
	rope_->SetBoxes(boxes);

	artillery = new Artillery();
	artillery->Initialize(modelBom, modelBom2, &viewProjection_);

	//brokenBox_ = new BrokenBox();
	//brokenBox_->Initialize(modelBrokenBox_, &viewProjection_);
	//brokenBox_->SetBoxes(boxes);
	cameraController = new CameraController();
	cameraController->Initialize();
	cameraController->SetTraget(rope_);
	cameraController->Reset();

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, fadeTime_);

}

void GameScene::Update() { 


	ChangePhase();
	switch (phase_) {
	case GameScene::Phase::kMain:
    	CheckAllCollision();
	
    	CheckAllCollisions();
		CheckBulletPlayerCollision();
	
    	for (std::vector<WorldTransform*> blockLine : blocks_) {
    		for (WorldTransform* block : blockLine) {
    			if (!block) {
    				continue;
    			} else {
    				block->UpdateMatrix();
    			}
    		}
    	}

		for (Electricity* electrical : electricity) {
			electrical->Update();
		}
		for (Electricity2* electrical : electricity2) {
			electrical->Update();
		}
		for (Door1* door : doors) {
			door->Update();
			door->OnCollision(player1_);
			door->OnCollision(player2_);
		}

		for (Box* box : boxes) {
			box->Update();
		}
	
		for (BrokenBox* brokenBox_ : brokenBoxes) {
			brokenBox_->SetBoxes(boxes);
			brokenBox_->Update();
		}
		//大砲
		artillery->Update();
    	// プレイヤーの更新
    	player1_->Update();
    	player2_->Update();

    	rope_->Update();

    	cameraController->Update();

		if (input_->TriggerKey(DIK_C) || 
			((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_Y))) {
			clear_ = true;
		}
		break;
	default:
		for (std::vector<WorldTransform*> blockLine : blocks_) {
			for (WorldTransform* block : blockLine) {
				if (!block) {
					continue;
				} else {
					block->UpdateMatrix();
				}
			}
		}

		for (Electricity* electrical : electricity) {
			electrical->Update();
		}

		for (Electricity2* electrical : electricity2) {
			electrical->Update();
		}

		for (Door1* door : doors) {
			door->Update();
			door->OnCollision(player1_);
			door->OnCollision(player2_);
		}

		for (Box* box : boxes) {
			box->Update();
		}

		for (BrokenBox* brokenBox_ : brokenBoxes) {
			brokenBox_->SetBoxes(boxes);
			brokenBox_->Update();
		}
		artillery->Update();
		player1_->PlayerUpdateMatrix();
		player2_->PlayerUpdateMatrix();

		rope_->Update();

    	cameraController->Update();
		break;
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
	wallpaperSprite_->Draw();
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
	

	
	rope_->Draw(&viewProjection_);
	// プレイヤーの描画
	player1_->Draw(&viewProjection_);
	player2_->Draw(&viewProjection_);



	//mapchip_->Draw();

	//box_->Draw();

	for (Box* box : boxes) {
		box->Draw();
	}

	for (Electricity* electrical : electricity) {
		electrical->Draw();
	}
	for (Electricity2* electrical : electricity2) {
		electrical->Draw();
	}
	for (Door1* door : doors) {
		door->Draw();
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

	for (BrokenBox* brokenBox_ : brokenBoxes) {
		brokenBox_->Draw();
	}
	//大砲
	artillery->Draw();
	viewProjection_.matView = cameraController->GetViewProjection().matView;
	viewProjection_.matProjection = cameraController->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();

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
	switch (phase_) {
	case GameScene::Phase::kMain:
		menuAttendSprite_->Draw();
		break;
	case GameScene::Phase::kMenu:
		menuSprite_->Draw();
		cursorSprite_->Draw();
		break;
	case GameScene::Phase::kClear:
		if (stageNum == stage[4]) {
			clearAllSirpte_->Draw();
		} else {
    		clearSprite_->Draw();
		}
		cursorSprite_->Draw();
		break;
	}

	fade_->Draw(commandList);
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateBlocks() {
	uint32_t kMapHeight = mapchip_->GetNumVirtical();
	uint32_t kMapWight = mapchip_->GetNumHorizontal();

    blocks_.resize(kMapHeight);
	for (uint32_t i = 0; i < kMapHeight; i++) {
		blocks_[i].resize(kMapWight);
	}


	for (uint32_t i = 0; i < kMapHeight; ++i) {
		for (uint32_t j = 0; j < kMapWight; ++j) {
			if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kWall) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				blocks_[i][j] = worldTransform;
				blocks_[i][j]->translation_ = mapchip_->GetMapChipPosition(j, i);
			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kBox) {

				Box* box = new Box();
				box->Initialize(modelBlock_, &viewProjection_, mapchip_->GetMapChipPosition(j, i));

				boxes.push_back(box);
			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kBrokenBox) {
				BrokenBox* brokenBox_ = new BrokenBox();
				brokenBox_->Initialize(modelBrokenBox_, modelParticle_, &viewProjection_, mapchip_->GetMapChipPosition(j, i));
				brokenBoxes.push_back(brokenBox_);

			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kPlug) {

				if (!isPair) {
					// 左側
					Electricity* elect = new Electricity;
					elect->Initialize(modelSwitch1_, model_, &viewProjection_);
					elect->SetPosition(mapchip_->GetMapChipPosition(j, i));
					electricity.push_back(elect);

					// electricitys の配列要素の範囲チェックと初期化
					if (electNum < 5) {
						if (electricitys[electNum].empty()) {
							electricitys[electNum] = std::list<Electricity*>();
						}
						electricitys[electNum].push_back(elect);
					}
					isPair = true;
				} else {
					// 右側
					Electricity2* elect = new Electricity2;
					elect->Initialize(modelSwitch2_, model_, &viewProjection_);
					elect->SetPosition(mapchip_->GetMapChipPosition(j, i));
					electricity2.push_back(elect);

					// electricitys2 の配列要素の範囲チェックと初期化
					if (electNum < 5) {
						if (electricitys2[electNum].empty()) {
							electricitys2[electNum] = std::list<Electricity2*>();
						}
						electricitys2[electNum].push_back(elect);
						electNum++;
					}
					isPair = false;
				}
			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kDoor) {
				Door1* door = new Door1();
				Vector3 kSpeed = {1.0f, 0.0f, 0.0f};

				door->Initialize(modelWall1_, &viewProjection_, mapchip_->GetMapChipPosition(j, i), kSpeed);
				doors.push_back(door);

				// doorCount の範囲チェック
				if (doorCount < 5) {
					// doorsList に要素を確保してから push_back する
					if (doorsList[doorCount].empty()) {
						doorsList[doorCount] = std::list<Door1*>();
					}
					doorsList[doorCount].push_back(door);
					doorCount++;
				} 
			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kDoorVertical) {
				Door1* door = new Door1();
				Vector3 kSpeed = {0.0f, 1.0f, 0.0f};
				
				door->Initialize(modelWall1_, &viewProjection_, mapchip_->GetMapChipPosition(j, i), kSpeed);
				door->Vartical();//向きを変える処理
				doors.push_back(door);
				doorsList[doorCount].push_back(door);
				doorCount++;
			}else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kPlayerPos) {
				for (uint32_t num = 0; num < 2; num++) {
					if (playerNum == num) {
						playerPosition[num] = mapchip_->GetMapChipPosition(j, i);
					}
				}
				playerNum++;
			}
		}
	}
}

void GameScene::CheckAllCollision() { 
	#pragma region
	//左側
	AABB aabb1, aabb2;
	aabb1 = player1_->GetAABB();

	AABB aabb3, aabb4;
	aabb3 = player2_->GetAABB();

	for (uint32_t i = 0; i < maxGate; i++) {
		//左側
		for (Electricity* elect : electricitys[i]) {
			aabb2 = elect->GetAABB();
			 if (AABB::IsCollision(aabb1, aabb2)) {
				player1_->OnCollision(elect);
				elect->OnCollision(player1_);
				left[i] = true;
			}
		}

		for (Electricity2* elect : electricitys2[i]) {
			//右側
			aabb4 = elect->GetAABB();
			if (AABB::IsCollision(aabb3, aabb4)) {
				player2_->OnCollision2(elect);
				elect->OnCollision(player2_);
				right[i] = true;
			}
		}

		for (Door1* door : doorsList[i]) {
			door->SetFlag(left[i], right[i]);
		}

	}

   #pragma endregion
}

void GameScene::CheckAllCollisions() { 
	KamataEngine::Vector3 posA, posB; 

	float boxRadius = 1.0f;
	float brokenBoxRadius = 1.0f;

	#pragma region 壊れる箱と箱の当たり判定

	// 壊れる箱と箱全ての当たり判定
	for (Box* box : boxes) {
		for (BrokenBox* brokenBox_ : brokenBoxes) {
			// 壊れる箱の座標
			posA = brokenBox_->GetWorldPosition();
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
	}
	#pragma endregion

}

void GameScene::CheckBulletPlayerCollision() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	const std::list<Bullet*>& Bullets = artillery->GetBullets();
	// 自キャラの座標
	posA = player1_->GetWorldPosition();

	for (Bullet* bullet : Bullets) {
		posB = bullet->GetWorldPosition();
		// posAとposBの距離
		float posC = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);

		// 半径の差
		float L = (player1_->GetRadius() + bullet->GetRadius()) * (player1_->GetRadius() + bullet->GetRadius());
		// 球と球の交差判定
		if (posC <= L) {
			// 自キャラの衝突時コールバックを呼び出す
			player1_->OnCollisionBullet();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}

	// 自キャラの座標
	posA = player2_->GetWorldPosition();

	for (Bullet* bullet : Bullets) {
		posB = bullet->GetWorldPosition();
		// posAとposBの距離
		float posC = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);

		// 半径の差
		float L = (player2_->GetRadius() + bullet->GetRadius()) * (player2_->GetRadius() + bullet->GetRadius());
		// 球と球の交差判定
		if (posC <= L) {
			// 自キャラの衝突時コールバックを呼び出す
			player2_->OnCollisionBullet();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}

	// 自キャラの座標
	posA = rope_->GetWorldTransform().translation_;

	for (Bullet* bullet : Bullets) {
		posB = bullet->GetWorldPosition();
		// posAとposBの距離
		float posC = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);

		// 半径の差
		float L = (rope_->GetRadius() + bullet->GetRadius()) * (rope_->GetRadius() + bullet->GetRadius());
		// 球と球の交差判定
		if (posC <= L) {
			// 自キャラの衝突時コールバックを呼び出す
			rope_->OnCollisionBullet();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision2();
		}
	}
	// 自キャラの座標
	posA = artillery->GetWorldPostion();

	for (Bullet* bullet : Bullets) {
		posB = bullet->GetWorldPosition();
		// posAとposBの距離
		float posC = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);

		// 半径の差
		float L = (artillery->GetRadius() + bullet->GetRadius()) * (artillery->GetRadius() + bullet->GetRadius());
		// 球と球の交差判定
		if (posC <= L) {
			// 自キャラの衝突時コールバックを呼び出す
			artillery->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
}

void GameScene::ChangePhase() {
	input_->GetJoystickState(0, state);
	input_->GetJoystickStatePrevious(0, preState);
	const int deadZone = 8000;

	switch (phase_) {
	case GameScene::Phase::kFadeIn:
		fade_->Update();
		if (fade_->IsFinished()) {
			fade_->Stop();
			phase_ = Phase::kMain;
		}
		break;
	case GameScene::Phase::kMain:
		if (input_->TriggerKey(DIK_ESCAPE) || 
			(state.Gamepad.wButtons & XINPUT_GAMEPAD_START) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_START)) {
			phase_ = Phase::kMenu;
		} else if (clear_) {
			phase_ = Phase::kClear;
		}
		break;
	case GameScene::Phase::kMenu: {
		// カーソル位置をテーブルで管理
		constexpr float cursorPositions[] = {275.0f, 360.0f, 450.0f};

		// カーソル移動処理を関数でまとめて呼び出し
		UpdateCursorSelection(3, deadZone);

		// カーソル位置の更新
		selectCursorPos.y = cursorPositions[selectNum - 1];
		cursorSprite_->SetPosition(selectCursorPos);

		if (input_->TriggerKey(DIK_SPACE) 
			|| ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A))) {
			switch (selectNum) {
			case 1:
				select_ = Select::kGoStageSelect;
				fade_->Start(Fade::Status::FadeOut, fadeTime_);
				phase_ = Phase::kFadeOut;
				break;
			case 2:
				select_ = Select::kGoTitle;
				fade_->Start(Fade::Status::FadeOut, fadeTime_);
				phase_ = Phase::kFadeOut;
				break;
			case 3:
				phase_ = Phase::kMain;
				break;
			}
		}
		break;
	}
	case GameScene::Phase::kClear:
		if (stageNum == stage[4]) {
			// 最終ステージ後の選択
			std::vector<float> cursorPositions = {275.0f, 360.0f};
			// カーソル移動処理を関数でまとめて呼び出し
			UpdateCursorSelection(2, deadZone);

			// カーソル位置の更新
			selectCursorPos.y = cursorPositions[selectNum - 1];
			cursorSprite_->SetPosition(selectCursorPos);
		} else {
			// 通常ステージの選択
			std::vector<float> cursorPositions = {275.0f, 360.0f, 450.0f};
			// カーソル移動処理を関数でまとめて呼び出し
			UpdateCursorSelection(3, deadZone);

			// カーソル位置の更新
			selectCursorPos.y = cursorPositions[selectNum - 1];
			cursorSprite_->SetPosition(selectCursorPos);
		}

		if (input_->TriggerKey(DIK_SPACE) || 
			((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A))) {
			if (stageNum == stage[4]) {
				switch (selectNum) {
				case 1:
					select_ = Select::kGoStageSelect;
					fade_->Start(Fade::Status::FadeOut, fadeTime_);
					phase_ = Phase::kFadeOut;
					break;
				case 2:
					select_ = Select::kGoTitle;
					fade_->Start(Fade::Status::FadeOut, fadeTime_);
					phase_ = Phase::kFadeOut;
					break;
				}
			} else {
				switch (selectNum) {
				case 1:
					select_ = Select::kGoNextStage;
					SwitchToNextStage();
					fade_->Start(Fade::Status::FadeOut, fadeTime_);
					phase_ = Phase::kFadeOut;
					break;
				case 2:
					select_ = Select::kGoStageSelect;
					fade_->Start(Fade::Status::FadeOut, fadeTime_);
					phase_ = Phase::kFadeOut;
					break;
				case 3:
					select_ = Select::kGoTitle;
					fade_->Start(Fade::Status::FadeOut, fadeTime_);
					phase_ = Phase::kFadeOut;
					break;
				}
			}
		}
		break;
	case GameScene::Phase::kFadeOut:
		fade_->Update();
		if (fade_->IsFinished()) {
			fade_->Stop();
			switch (select_) {
			case GameScene::Select::kGoNextStage:

				mapchip_->ResetMapChipData();
				ClearObject();
				mapchip_->LordCSV(stageNum);
				GenerateBlocks();
				rope_->SetBoxes(boxes);
				clear_ = false;
				phase_ = Phase::kFadeIn;
				fade_->Start(Fade::Status::FadeIn, fadeTime_);
				select_ = Select::kNone;
				break;
			default:
    			finished_ = true;
				break;
			}
		}
		break;
	}
}

// カーソル移動を処理する関数
void GameScene::UpdateCursorSelection(int maxNum, int deadZone) {
	// 下方向への入力処理
	if (input_->TriggerKey(DIK_S) || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) ||
	    (state.Gamepad.sThumbLY < -deadZone && preState.Gamepad.sThumbLY >= -deadZone)) {
		selectNum++;
	}

	// 上方向への入力処理
	if (input_->TriggerKey(DIK_W) || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) ||
	    (state.Gamepad.sThumbLY > deadZone && preState.Gamepad.sThumbLY <= deadZone)) {
		selectNum--;
	}

	// 範囲制限（ループするように設定）
	if (selectNum < 1) {
		selectNum = maxNum;
	} else if (selectNum > maxNum) {
		selectNum = 1;
	}
}


void GameScene::SwitchToNextStage() {

	if (stageNum == stage[0]) {
		stageNum = stage[1];
	} else if (stageNum == stage[1]) {
		stageNum = stage[2];
	} else if (stageNum == stage[2]) {
		stageNum = stage[3];
	} else if (stageNum == stage[3]) {
		stageNum = stage[4];
	}
}

void GameScene::ClearObject() {
	// Boxの解放
	for (Box*& box : boxes) {
		delete box;
		box = nullptr;
	}
	boxes.clear();

	// Gateの解放
	for (Gate*& gate : gates) {
		delete gate;
		gate = nullptr;
	}
	gates.clear();

	// Electricityの解放
	for (Electricity*& electrical : electricity) {
		delete electrical;
		electrical = nullptr;
	}
	electricity.clear();

	for (Electricity2*& electrical2 : electricity2) {
		delete electrical2;
		electrical2 = nullptr;
	}
	electricity2.clear();

	// Doorの解放
	for (Door1*& door : doors) {
		delete door;
		door = nullptr;
	}
	doors.clear();

	// Gateリストの解放
	for (auto& list : gatesList) {
		for (Gate*& gate : list) {
			delete gate;
			gate = nullptr;
		}
		list.clear();
	}

	// Blocksの解放
	for (auto& blockLine : blocks_) {
		for (WorldTransform*& block : blockLine) {
			delete block;
			block = nullptr;
		}
		blockLine.clear();
	}
	blocks_.clear();

	// BrokenBoxの解放
	for (BrokenBox*& brokenBox_ : brokenBoxes) {
		delete brokenBox_;
		brokenBox_ = nullptr;
	}
	brokenBoxes.clear();
}
