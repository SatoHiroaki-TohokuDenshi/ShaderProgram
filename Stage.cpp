#include "Stage.h"
#include "Donuts.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
}

//デストラクタ
Stage::~Stage() {

}

//初期化
void Stage::Initialize() {
	Instantiate<Donuts>(this);
}

//更新
void Stage::Update() {

}

//描画
void Stage::Draw() {

}

//開放
void Stage::Release() {

}
