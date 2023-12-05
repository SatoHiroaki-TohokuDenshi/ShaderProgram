#pragma once

#include <list>
#include <string>
#include "Transform.h"

using std::string;
using std::list;

class SphereCollider;

class GameObject {
private:
	bool isDead_;

protected:
	list<GameObject *>	childList_;		// 子供のリスト
	Transform			transform_;		// 座標情報
	GameObject*			pParent_;		// 親オブジェクト
	string				objectName_;	// オブジェクトの名前の文字列
	SphereCollider*		pCollider_;		// コライダー

public:
	// コンストラクタ
	GameObject();
	GameObject(GameObject* parent, const string& name);

	// デストラクタ
	~GameObject();

	// 純粋仮想関数
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	// 再帰的に呼び出す関数
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	// 消去
	void KillMe();

	// 位置セット
	void SetPosition(XMFLOAT3 position);
	void SetPosition(float x, float y, float z);

	// 検索
	GameObject* FindChildObject(string _objName);
	GameObject* GetRootJob();
	GameObject* FindObject(string _objName);

	// 当たり判定
	void AddCollider(SphereCollider* pCollider);
	void Collision(GameObject* pTarget);
	void RoundRobin(GameObject* pTarget);

public:
	//テンプレートの定義
	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return(pObject);
	}
};