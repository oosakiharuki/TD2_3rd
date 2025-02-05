#include "GameScene.h"
#include <cassert>
#include "Fade.h"
#include <unordered_set>

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
	delete modelBoxSwitch_;
	delete modelGoal_;

	delete player1_;
	delete player2_;

	for (Artillery* artillery : artilleries) {
		delete artillery;
	}

	delete rope_;

	for (Box* box : boxes) {
		delete box;
	}
	boxes.clear();

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



	for (MapWall* block : blocks_) {
		delete block;		
	}

	blocks_.clear();

	for (BrokenBox* brokenBox_ : brokenBoxes) {
		delete brokenBox_;
	}
	brokenBoxes.clear();

	for (Goal* goal : goals_) {
		delete goal;
	}
	goals_.clear();
	delete goal_;

	for (OnBoxSwitch* onBoxSwitch : onBoxSwitches) {
		delete onBoxSwitch;
	}

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
	stage[0] = "Resources/stageCsv/stage10.csv";
	stage[1] = "Resources/stageCsv/stage02.csv";
	stage[2] = "Resources/stageCsv/stage03.csv";
	stage[3] = "Resources/stageCsv/stage04.csv";
	stage[4] = "Resources/stageCsv/stage05.csv";
	stage[5] = "Resources/stageCsv/stage06.csv";
	
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
	modelBoxSwitch_ = Model::CreateFromOBJ("boxSwitch", true);
	modelGoal_ = Model::CreateFromOBJ("goal", true);

	bgmDataHandle_ = audio_->LoadWave("bgm.wav");
	bgmVoiceHandle_ = audio_->PlayWave(bgmDataHandle_, true, 0.3f);

	buttonDataHande_ = audio_->LoadWave("button.wav");
	selectDataHandle_ = audio_->LoadWave("select.wav");
	menuButtonDataHandle_ = audio_->LoadWave("menuButton.wav");
	clearDataHandle_ = audio_->LoadWave("clear.wav");

	GenerateBlocks();

	//goal_ = new Goal();
	//goal_->Initialize(modelGoal_, &viewProjection_, {5.0f, 5.0f, 0.0f});

	player1_ = new Player();
	player1_->Initialize(modelPlayer1_, 1);
	player1_->SetWorldPosition(playerPosition[0]);
	player1_->SetStarrPosition(playerPosition[0]);

	player2_ = new Player();
	player2_->Initialize(modelPlayer2_, 2);
	player2_->SetWorldPosition(playerPosition[1]);
	player2_->SetStarrPosition(playerPosition[1]);
	
	rope_ = new Rope();
    rope_->Initialize(player1_, player2_, input_, modelCarryRope_, modelHopRope_);
	rope_->SetBoxes(boxes);

	//artillery = new Artillery();
	//artillery->Initialize(modelBom, modelBom2, &viewProjection_);

	//brokenBox_ = new BrokenBox();
	//brokenBox_->Initialize(modelBrokenBox_, &viewProjection_);
	//brokenBox_->SetBoxes(boxes);
	cameraController = new CameraController();
	cameraController->Initialize();
	cameraController->SetTraget(rope_);
	cameraController->Reset();

	cameraController->SetMovebleaArea({27.7f, 30.3f, 15.3f, 42.7f});

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
	
    	for (MapWall* block : blocks_) {	
			block->Update();
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
			if (input_->TriggerKey(DIK_R) || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_Y))) {
				box->RestPosition();
				player1_->ResetPosition();
				player2_->ResetPosition();
			}
		}
	
		for (BrokenBox* brokenBox_ : brokenBoxes) {
			brokenBox_->SetBoxes(boxes);
			brokenBox_->Update();
		}
		//大砲
		for (Artillery* artillery : artilleries) {
			artillery->Update();
		}
    	// プレイヤーの更新
    	player1_->Update();
    	player2_->Update();

    	rope_->Update();
		goal_->Update();
		for (OnBoxSwitch* onBoxSwitch : onBoxSwitches) {
			onBoxSwitch->Update();
		}

    	cameraController->Update();

		/*		if (input_->TriggerKey(DIK_C) || 
			((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_X))) {
			clear_ = true;
		}*/


		break;
	case GameScene::Phase::kFadeIn:
		for (MapWall* block : blocks_) {
			block->Update();
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

		goal_->Update();
		for (Artillery* artillery : artilleries) {
			artillery->Update();
		}
		for (OnBoxSwitch* onBoxSwitch : onBoxSwitches) {
			onBoxSwitch->Update();
		}

		player1_->PlayerUpdateMatrix();
		player2_->PlayerUpdateMatrix();

		rope_->Update();

    	cameraController->Update();
		break;
	default:
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

	for (MapWall* block : blocks_) {
		block->Draw();
	}

	for (BrokenBox* brokenBox_ : brokenBoxes) {
		brokenBox_->Draw();
	}
	goal_->Draw();

	//大砲
	for (Artillery* artillery : artilleries) {
		artillery->Draw();
	}

	for (OnBoxSwitch* onBoxSwitch : onBoxSwitches) {
		onBoxSwitch->Draw();
	}

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
		if (stageNum == stage[maxStage]) {
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
	uint32_t kMapWidth = mapchip_->GetNumHorizontal();

	for (uint32_t i = 0; i < kMapHeight; ++i) {
		for (uint32_t j = 0; j < kMapWidth; ++j) {
			if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kWall) {

				MapWall* block_ = new MapWall();
				block_->Initialize(model_, texture, &viewProjection_, mapchip_->GetMapChipPosition(j, i));

				blocks_.push_back(block_);
			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kBox) {

				Box* box = new Box();
				box->Initialize(modelBlock_, &viewProjection_, mapchip_->GetMapChipPosition(j, i), mapchip_->GetMapChipPosition(j, i));

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
				door->Vartical(); // 向きを変える処理
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
			}else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kPlayerPos) {
				for (uint32_t num = 0; num < 2; num++) {
					if (playerNum == num) {
						playerPosition[num] = mapchip_->GetMapChipPosition(j, i);
					}
				}
				playerNum++;
			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kGoal) {
				goal_ = new Goal();
				goal_->Initialize(modelGoal_, &viewProjection_, mapchip_->GetMapChipPosition(j, i));

			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kArtillery) {
				Artillery* artillery = new Artillery();
				artillery->Initialize(modelBom, modelBom2, &viewProjection_, mapchip_->GetMapChipPosition(j, i));

				artilleries.push_back(artillery);
			} else if (mapchip_->GetMapChipTpeByIndex(j, i) == MapChipType::kBoxSwitch) {
				OnBoxSwitch* onBoxSwitch = new OnBoxSwitch();
				onBoxSwitch->Initialize(modelSwitch1_, &viewProjection_, mapchip_->GetMapChipPosition(j, i));

				onBoxSwitches.push_back(onBoxSwitch);
				onBoxSwitchesList[electNum].push_back(onBoxSwitch);
				electNum++;
			}
		}
	}
}


void GameScene::CheckAllCollision() { 
	#pragma region
	//左側
	AABB aabb1, aabb2;
	aabb1 = player1_->GetAABB();
	aabb2 = player2_->GetAABB();

	for (uint32_t i = 0; i < maxGate; i++) {
		// 左側
		for (Electricity* elect : electricitys[i]) {
			AABB ElectAABB = elect->GetAABB();
			if (AABB::IsCollision(aabb1, ElectAABB)) {
				player1_->OnCollision(elect);
				elect->OnCollision(player1_);
				left[i] = true;
			} else {
				left[i] = false;
			}
		}

		for (Electricity2* elect : electricitys2[i]) {
			// 右側
			AABB ElectAABB = elect->GetAABB();
			if (AABB::IsCollision(aabb2, ElectAABB)) {
				player2_->OnCollision2(elect);
				elect->OnCollision(player2_);
				right[i] = true;
			} else {
				right[i] = false;
			}
		}


		for (OnBoxSwitch* onBoxSwitch : onBoxSwitchesList[i]) {
			AABB switchAABB = onBoxSwitch->GetAABB();
		
			for (Box* box : boxes) {
				AABB boxAABB= box->GetAABB();

				if (AABB::IsCollision(boxAABB, switchAABB)) {
					onBoxSwitch->OnCollision();
					OnBox[i] = true;
					break;
				} else {
					OnBox[i] = false;
				}
			}	
		}
		for (Door1* door : doorsList[i]) {
			for (Box* box : boxes) {
				door->OnCollisionBox(box);
				door->SetCorrectionPos(player1_);
				door->SetCorrectionPos(player2_);
				door->Resetcorrection();
			}
			door->SetFlag(left[i], right[i]);
			door->SetFlagSwitch(OnBox[i]);
		}
	}

	for (MapWall* block : blocks_) {
		AABB wallAABB = block->GetAABB();
		if (AABB::IsCollision(aabb1, wallAABB)) {
			block->OnCollisionPlayer(player1_, wallAABB);
		}
		if (AABB::IsCollision(aabb2, wallAABB)) {
			block->OnCollisionPlayer(player2_, wallAABB);
		}

		for (Box* box : boxes) {
			AABB boxAABB = box->GetAABB();
			if (AABB::IsCollision(boxAABB, wallAABB)) {
				block->OnCollisionBox(box, wallAABB);

				block->SetCorrectionPos(player1_);
				block->SetCorrectionPos(player2_);
				block->Resetcorrection();
			}
		}
	}


	for (BrokenBox* brokenBox_ : brokenBoxes) {
		AABB brokenBoxAABB = brokenBox_->GetAABB();
		if (!brokenBox_->IsBreak()) {
			if (AABB::IsCollision(aabb1, brokenBoxAABB)) {
				brokenBox_->OnCollisionPlayer(player1_, brokenBoxAABB);
			}
			if (AABB::IsCollision(aabb2, brokenBoxAABB)) {
				brokenBox_->OnCollisionPlayer(player2_, brokenBoxAABB);
			}
			for (Box* box : boxes) {
				AABB boxAABB = box->GetAABB();
				if (AABB::IsCollision(boxAABB, brokenBoxAABB) && box->GetNowMode() == Box::Mode::Normal) {
					brokenBox_->OnCollisionBox(box, brokenBoxAABB);

					brokenBox_->SetCorrectionPos(player1_);
					brokenBox_->SetCorrectionPos(player2_);
					brokenBox_->Resetcorrection();
				}
			}
		}
	}

   #pragma endregion
}

void GameScene::CheckAllCollisions() { 
	KamataEngine::Vector3 posA, posB; 

	#pragma region 壊れる箱と箱の当たり判定

	// 壊れる箱と箱全ての当たり判定
	for (Box* box : boxes) {
			// 箱の座標
			posB = box->GetWorldPosition();
		for (BrokenBox* brokenBox_ : brokenBoxes) {
			// 壊れる箱の座標
			posA = brokenBox_->GetWorldPosition();

			KamataEngine::Vector3 diff = {posB.x - posA.x, posB.y - posA.y, posB.z - posA.z};
			float distanceSquared = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

			float radiusSum = brokenBox_->GetRadius() + box->GetRadius();

			// 球と球の交差判定
			if (distanceSquared <= (radiusSum * radiusSum)) {
				if (box->GetNowMode() == Box::Mode::Hop)
				brokenBox_->OnCollision();
			}
		}
	}
	#pragma endregion

	#pragma region ゴールと箱の当たり判定
	// ゴールと箱の当たり判定
	for (Box* box : boxes) {
		// 箱の座標
		posB = box->GetWorldPosition();

		// Goalの座標
		posA = goal_->GetWorldPosition();

		KamataEngine::Vector3 diff = {posB.x - posA.x, posB.y - posA.y, posB.z - posA.z};
		float distanceSquared = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

		float radiusSum = goal_->GetRadius() + box->GetRadius();

		// 球と球の交差判定
		if (distanceSquared <= (radiusSum * radiusSum)) {
			clear_ = true;
		}

	}
	#pragma endregion
}

void GameScene::CheckBulletPlayerCollision() {
	// 判定対象AとBの座標
	Vector3 posA, posB;
	for (Artillery* artillery : artilleries) {
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

		//壁と弾
		for (MapWall* block : blocks_) {
			posA = block->GetWorldPosition();

			for (Bullet* bullet : Bullets) {
				posB = bullet->GetWorldPosition();

				// posAとposBの距離
				float posC = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);

				// 半径の差
				float L = (1.0f + bullet->GetRadius()) * (1.0f + bullet->GetRadius());
				// 球と壁の交差判定
				if (posC <= L) {
					// 敵弾の衝突時コールバックを呼び出す
					bullet->OnCollision();
				}
			}
		}
		
		//壊れる壁と弾
		for (BrokenBox* brokenBox_ : brokenBoxes) {
			posA = brokenBox_->GetWorldPosition();
			
			for (Bullet* bullet : Bullets) {
				posB = bullet->GetWorldPosition();

				// posAとposBの距離
				float posC = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);

				// 半径の差
				float L = (1.0f + bullet->GetRadius()) * (1.0f + bullet->GetRadius());
				// 球と壁の交差判定
				if (posC <= L && !brokenBox_->IsBreak()) {
					// 敵弾の衝突時コールバックを呼び出す
					bullet->OnCollision();
					brokenBox_->OnCollision();
				}
			}
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
			menuButtonVoiceHandle_ = audio_->PlayWave(menuButtonDataHandle_, false);
			phase_ = Phase::kMenu;
            selectNum = 1;

		} else if (clear_) {
			audio_->StopWave(bgmVoiceHandle_);
			clearVoiceHandle_ = audio_->PlayWave(clearDataHandle_, false, 0.5f);
			phase_ = Phase::kClear;
		}
		break;
	case GameScene::Phase::kMenu: {
		if (input_->TriggerKey(DIK_ESCAPE) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_START)) {
			menuButtonVoiceHandle_ = audio_->PlayWave(menuButtonDataHandle_, false);
			phase_ = Phase::kMain;
		}
		// カーソル位置をテーブルで管理
		constexpr float cursorPositions[] = {275.0f, 360.0f, 450.0f};

		// カーソル移動処理を関数でまとめて呼び出し
		UpdateCursorSelection(3, deadZone);

		// カーソル位置の更新
		selectCursorPos.y = cursorPositions[selectNum - 1];
		cursorSprite_->SetPosition(selectCursorPos);

		if (input_->TriggerKey(DIK_SPACE) 
			|| ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A))) {
			buttonVoiceHandle_ = audio_->PlayWave(buttonDataHande_, false);
			switch (selectNum) {
			case 1:
				select_ = Select::kGoStageSelect;
				audio_->StopWave(bgmVoiceHandle_);
				fade_->Start(Fade::Status::FadeOut, fadeTime_);
				phase_ = Phase::kFadeOut;
				break;
			case 2:
				select_ = Select::kGoTitle;
				audio_->StopWave(bgmVoiceHandle_);
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
		if (stageNum == stage[maxStage]) {
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
			buttonVoiceHandle_ = audio_->PlayWave(buttonDataHande_, false);
			if (stageNum == stage[maxStage]) {
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
			    player1_->SetWorldPosition(playerPosition[0]);
				player1_->SetStarrPosition(playerPosition[0]);
			    player2_->SetWorldPosition(playerPosition[1]);
				player2_->SetStarrPosition(playerPosition[1]);
				rope_->SetBoxes(boxes);

				clear_ = false;
				phase_ = Phase::kFadeIn;
				fade_->Start(Fade::Status::FadeIn, fadeTime_);
				select_ = Select::kNone;
				bgmVoiceHandle_ = audio_->PlayWave(bgmDataHandle_, true, 0.3f);
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


void GameScene::SwitchToNextStage() {
	for (uint32_t i = 0; i < maxStage; i++) {
		if (stageNum == stage[i]) {
			stageNum = stage[i + 1];
			break;
		}
	}
}

void GameScene::ClearObject() {
	// Boxの解放
	for (Box*& box : boxes) {
		delete box;
		box = nullptr;
	}
	boxes.clear();

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
	electNum = 0;

	// Doorの解放
	for (Door1*& door : doors) {
		delete door;
		door = nullptr;
	}
	doors.clear();
	doorCount = 0;

  
	for (OnBoxSwitch* onBoxSwitch : onBoxSwitches) {
		delete onBoxSwitch;
		onBoxSwitch = nullptr;
	}
	onBoxSwitches.clear();

	for (uint32_t i = 0; i < maxGate; i++) {
		electricitys[i].clear();
		electricitys2[i].clear();
		doorsList[i].clear();
		onBoxSwitchesList[i].clear();
		onBoxSwitchesList[i].clear();
		OnBox[i] = false;
	}

	// Blocksの解放
	for (MapWall* block : blocks_) {
		delete block;
	}
	blocks_.clear();

	// BrokenBoxの解放
	for (BrokenBox*& brokenBox_ : brokenBoxes) {
		delete brokenBox_;
		brokenBox_ = nullptr;
	}
	brokenBoxes.clear();

	delete goal_;

	for (Artillery* artillery : artilleries) {
		delete artillery;
	}
	artilleries.clear();

	playerNum = 0;
}
