#include "Stage.h"
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Donuts.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), light_(1.0f, 0.0f, 0.0f, 0.0f), pCBStage_(nullptr)
{
}

//�f�X�g���N�^
Stage::~Stage() {

}

//������
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

	// �R���X�^���g�o�b�t�@�̍쐬
	HRESULT hr;
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStage_);
	if (FAILED(hr)) {
		MessageBox(NULL, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
	}
}

//�X�V
void Stage::Update() {
	UpdateConstantBuffer();
}

void Stage::UpdateConstantBuffer() {
	XMFLOAT4 eye;
	XMStoreFloat4(&eye, Camera::GetCameraPos());

	CB_STAGE cb{
		light_,		//����
		eye			//���_
	};

	//Direct3D::pContext_->UpdateSubresource(pCBStage_, 0, NULL, &cb, 0, 0);
	
	//Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStage_);
	//Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStage_);
}

//�`��
void Stage::Draw() {
	
}

//�J��
void Stage::Release() {

}
