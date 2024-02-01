#include "Water.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Water::Water(GameObject* parent)
	:GameObject(parent, "Water"), hModel_(-1)
{
}

//�f�X�g���N�^
Water::~Water()
{
}

//������
void Water::Initialize() {
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets\\WaterPlane.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Water::Update() {

}

//�`��
void Water::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::DrawNMap(hModel_);
}

//�J��
void Water::Release() {

}
