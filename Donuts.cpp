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

	transform_.scale_ = { 0.7f, 0.7f, 0.7f };
}

//�X�V
void Donuts::Update() {
	transform_.rotate_.y += 0.5f;
}

//�`��
void Donuts::Draw(){
	Model::SetTransform(hModel_, transform_);
	Model::DrawToon(hModel_);
}

//�J��
void Donuts::Release() {

}