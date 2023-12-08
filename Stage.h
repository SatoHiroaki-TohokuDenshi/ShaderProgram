#pragma once
#include <d3d11.h>
#include "Engine/GameObject.h"

//Stageを管理するクラス
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
	//コンストラクタ
	Stage(GameObject* parent);

	//デストラクタ
	~Stage();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};