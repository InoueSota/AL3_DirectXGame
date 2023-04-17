#pragma once
#include "Model.h"
#include "WorldTransform.h"



class Player {

public:
	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};

