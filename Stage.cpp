#include "Stage.h"
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
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
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
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
	XMFLOAT4 eye;
	XMStoreFloat4(&eye, Camera::GetCameraPos());

	CB_STAGE cb{
		light_,		//光源
		eye			//視点
	};

	//Direct3D::pContext_->UpdateSubresource(pCBStage_, 0, NULL, &cb, 0, 0);
	
	//Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStage_);
	//Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStage_);
}

//描画
void Stage::Draw() {
	
}

//開放
void Stage::Release() {

}
