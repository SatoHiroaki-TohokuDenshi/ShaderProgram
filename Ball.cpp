#include "Ball.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
	:GameObject(parent, "Ball"), hModel_(-1)
{
}

//�f�X�g���N�^
Ball::~Ball()
{
}

//������
void Ball::Initialize() {
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets\\Ball_new.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = { 1.5f, 1.5, 1.5f };
	transform_.position_.z = 3.0f;
}

//�X�V
void Ball::Update() {
	transform_.rotate_.y += 0.5f;
	//transform_.rotate_ = { (float)(rand() % 360), (float)(rand() % 360) ,(float)(rand() % 360) };
}

//�`��
void Ball::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::DrawNMap(hModel_);
}

//�J��
void Ball::Release() {

}