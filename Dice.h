#pragma once
#include "Engine/GameObject.h"

//Dice���Ǘ�����N���X
class Dice : public GameObject {
private:
	int hModel_;    //���f���ԍ�

public:
	//�R���X�g���N�^
	Dice(GameObject* parent);

	//�f�X�g���N�^
	~Dice();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};