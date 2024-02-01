#pragma once
#include "Engine/GameObject.h"

//Waterを管理するクラス
class Water : public GameObject {
private:
	int hModel_;    //モデル番号

public:
	//コンストラクタ
	Water(GameObject* parent);

	//デストラクタ
	~Water();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
