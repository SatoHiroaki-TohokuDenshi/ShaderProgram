#include "Stage.h"
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"

#include "Donuts.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), light_(1.0f, 0.0f, 0.0f, 0.0f), pCBStage_(nullptr)
{
}

//デストラクタ
Stage::~Stage() {

}

//初期化
void Stage::Initialize() {
	Instantiate<Donuts>(this);

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

}

//開放
void Stage::Release() {

}
