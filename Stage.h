#pragma once
#include <d3d11.h>
#include "Engine/GameObject.h"

//Stage���Ǘ�����N���X
class Stage : public GameObject {
private:
	struct CB_STAGE {
		XMFLOAT4	lightPos;
		XMFLOAT4	eyePos;
	};
	XMFLOAT4 light_;
	void InitConstantBuffer();
	void UpdateConstantBuffer();
	ID3D11Buffer* pCBStage_;

public:
	//�R���X�g���N�^
	Stage(GameObject* parent);

	//�f�X�g���N�^
	~Stage();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};