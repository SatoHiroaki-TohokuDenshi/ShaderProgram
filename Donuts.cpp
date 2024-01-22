#include "Donuts.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Donuts::Donuts(GameObject* parent)
	:GameObject(parent, "Donuts"), hModel_(-1)
{
}

//�f�X�g���N�^
Donuts::~Donuts()
{
}

//������
void Donuts::Initialize() {
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets\\Donuts.fbx");
	assert(hModel_ >= 0);

	//transform_.scale_ = { 1.5f, 1.5, 1.5f };
}

//�X�V
void Donuts::Update() {
	//transform_.rotate_.y += 0.5f;
	//transform_.rotate_ = { (float)(rand() % 360), (float)(rand() % 360) ,(float)(rand() % 360) };
}

//�`��
void Donuts::Draw(){
	Model::SetTransform(hModel_, transform_);
	Model::DrawNMap(hModel_);
}

//�J��
void Donuts::Release() {

}