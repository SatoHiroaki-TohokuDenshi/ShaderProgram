#include "Ball.h"
#include "Engine/Model.h"

//コンストラクタ
Ball::Ball(GameObject* parent)
	:GameObject(parent, "Ball"), hModel_(-1)
{
}

//デストラクタ
Ball::~Ball()
{
}

//初期化
void Ball::Initialize() {
	//モデルデータのロード
	hModel_ = Model::Load("Assets\\Ball_new.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = { 1.5f, 1.5, 1.5f };
	transform_.position_.z = 3.0f;
}

//更新
void Ball::Update() {
	transform_.rotate_.y += 0.5f;
	//transform_.rotate_ = { (float)(rand() % 360), (float)(rand() % 360) ,(float)(rand() % 360) };
}

//描画
void Ball::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::DrawNMap(hModel_);
}

//開放
void Ball::Release() {

}