#include "Water.h"
#include "Engine/Model.h"

//コンストラクタ
Water::Water(GameObject* parent)
	:GameObject(parent, "Water"), hModel_(-1)
{
}

//デストラクタ
Water::~Water()
{
}

//初期化
void Water::Initialize() {
	//モデルデータのロード
	hModel_ = Model::Load("Assets\\WaterPlane.fbx");
	assert(hModel_ >= 0);
}

//更新
void Water::Update() {

}

//描画
void Water::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::DrawNMap(hModel_);
}

//開放
void Water::Release() {

}
