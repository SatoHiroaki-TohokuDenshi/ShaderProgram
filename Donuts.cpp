#include "Donuts.h"
#include "Engine/Model.h"

//コンストラクタ
Donuts::Donuts(GameObject* parent)
	:GameObject(parent, "Donuts"), hModel_(-1)
{
}

//デストラクタ
Donuts::~Donuts()
{
}

//初期化
void Donuts::Initialize() {
	//モデルデータのロード
	hModel_ = Model::Load("Assets\\Donuts.fbx");
	assert(hModel_ >= 0);

	//transform_.scale_ = { 1.5f, 1.5, 1.5f };
}

//更新
void Donuts::Update() {
	//transform_.rotate_.y += 0.5f;
	//transform_.rotate_ = { (float)(rand() % 360), (float)(rand() % 360) ,(float)(rand() % 360) };
}

//描画
void Donuts::Draw(){
	Model::SetTransform(hModel_, transform_);
	Model::DrawNMap(hModel_);
}

//開放
void Donuts::Release() {

}