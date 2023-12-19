#include "Stage.h"
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Donuts.h"

namespace {
	const float velocity = 0.1f;
}

//コンストラクタ
Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), light_(1.0f, 0.0f, 0.0f, 0.0f), pCBStage_(nullptr),
	 hModel_(-1), ballT_()
{
}

//デストラクタ
Stage::~Stage() {

}

//初期化
void Stage::Initialize() {
	Instantiate<Donuts>(this);
	hModel_ = Model::Load("Assets\\Ball.fbx");
	assert(hModel_ >= 0);

	ballT_.position_ = { light_.x, light_.y, light_.z };
	ballT_.scale_ = { 0.2f, 0.2f, 0.2f };

	InitConstantBuffer();
}

void Stage::InitConstantBuffer() {
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CB_STAGE);
	cb.Usage = D3D11_USAGE_DEFAULT;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = 0;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	HRESULT hr;
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStage_);
	if (FAILED(hr)) {
		MessageBox(NULL, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
	}
}

//更新
void Stage::Update() {
	if (Input::IsKey(DIK_D))	ballT_.position_.x += velocity;
	if (Input::IsKey(DIK_A))	ballT_.position_.x -= velocity;
	if (Input::IsKey(DIK_W))	ballT_.position_.z += velocity;
	if (Input::IsKey(DIK_S))	ballT_.position_.z-= velocity;
	if (Input::IsKey(DIK_Q))	ballT_.position_.y += velocity;
	if (Input::IsKey(DIK_E))	ballT_.position_.y -= velocity;

	SetLightPos(ballT_.position_);

	UpdateConstantBuffer();
}

void Stage::UpdateConstantBuffer() {
	CB_STAGE cb;
	XMStoreFloat4(&cb.eyePos, Camera::GetCameraPos());
	cb.lightPos = light_;

	Direct3D::pContext_->UpdateSubresource(pCBStage_, 0, NULL, &cb, 0, 0);

	Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStage_);
	Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStage_);
}

//描画
void Stage::Draw() {
	Model::SetTransform(hModel_, ballT_);
	Model::Draw3D(hModel_);
}

//開放
void Stage::Release() {

}

void Stage::SetLightPos(XMFLOAT3 f) {
	light_ = XMFLOAT4(f.x, f.y, f.z, 0.0f);
}