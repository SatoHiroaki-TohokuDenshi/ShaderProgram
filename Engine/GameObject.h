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
	list<GameObject *>	childList_;		// �q���̃��X�g
	Transform			transform_;		// ���W���
	GameObject*			pParent_;		// �e�I�u�W�F�N�g
	string				objectName_;	// �I�u�W�F�N�g�̖��O�̕�����
	SphereCollider*		pCollider_;		// �R���C�_�[

public:
	// �R���X�g���N�^
	GameObject();
	GameObject(GameObject* parent, const string& name);

	// �f�X�g���N�^
	~GameObject();

	// �������z�֐�
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	// �ċA�I�ɌĂяo���֐�
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	// ����
	void KillMe();

	// �ʒu�Z�b�g
	void SetPosition(XMFLOAT3 position);
	void SetPosition(float x, float y, float z);

	// ����
	GameObject* FindChildObject(string _objName);
	GameObject* GetRootJob();
	GameObject* FindObject(string _objName);

	// �����蔻��
	void AddCollider(SphereCollider* pCollider);
	void Collision(GameObject* pTarget);
	void RoundRobin(GameObject* pTarget);

public:
	//�e���v���[�g�̒�`
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