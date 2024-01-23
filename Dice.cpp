#include "Dice.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Dice::Dice(GameObject* parent)
	:GameObject(parent, "Dice"), hModel_(-1)
{
}

//�f�X�g���N�^
Dice::~Dice()
{
}

//������
void Dice::Initialize() {
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets\\Dice.fbx");
	assert(hModel_ >= 0);

	//transform_.scale_ = { 1.5f, 1.5, 1.5f };
}

//�X�V
void Dice::Update() {
	transform_.rotate_.y += 0.5f;
	//transform_.rotate_ = { (float)(rand() % 360), (float)(rand() % 360) ,(float)(rand() % 360) };
}

//�`��
void Dice::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw3D(hModel_);
}

//�J��
void Dice::Release() {

}