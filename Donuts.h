#pragma once
#include "Engine/GameObject.h"

//Donutsを管理するクラス
class Donuts : public GameObject {
private:
	int hModel_;    //モデル番号

public:
	//コンストラクタ
	Donuts(GameObject* parent);

	//デストラクタ
	~Donuts();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};