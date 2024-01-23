#include "Dice.h"
#include "Engine/Model.h"

//コンストラクタ
Dice::Dice(GameObject* parent)
	:GameObject(parent, "Dice"), hModel_(-1)
{
}

//デストラクタ
Dice::~Dice()
{
}

//初期化
void Dice::Initialize() {
	//モデルデータのロード
	hModel_ = Model::Load("Assets\\Dice.fbx");
	assert(hModel_ >= 0);

	//transform_.scale_ = { 1.5f, 1.5, 1.5f };
}

//更新
void Dice::Update() {
	transform_.rotate_.y += 0.5f;
	//transform_.rotate_ = { (float)(rand() % 360), (float)(rand() % 360) ,(float)(rand() % 360) };
}

//描画
void Dice::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw3D(hModel_);
}

//開放
void Dice::Release() {

}