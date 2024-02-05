#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>


#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

using std::vector;

class Texture;

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		Texture* pNormalMap;
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT4 specular;
		float    shininess;
	};

	// �R���X�^���g�o�b�t�@�ɑ�����
	struct CONSTANT_BUFFER
	{
		XMMATRIX matWorld;	// ���[���h�s��
		XMMATRIX matWVP;	// ���[���h�r���[�v���W�F�N�V�����s��
		XMMATRIX matNormal;	// �@���ό`�s��
		XMFLOAT4 diffuse;	// �f�B�t���[�Y
		XMFLOAT4 ambient;	// �A���r�G���g
		XMFLOAT4 specular;	// �X�y�L�����[
		float	 shininess;	// �V���C�j�l�X
		float scroll;
		BOOL isTextured;	// �e�N�X�`�������邩
		BOOL isNormalMap;	// �m�[�}���}�b�v�����邩
	};

	struct VERTEX
	{
		XMVECTOR position;	// �ʒu
		XMVECTOR uv;		// �e�N�X�`�����W
		XMVECTOR normal;	// �@���x�N�g��
		XMVECTOR tangent;	// �ڐ�
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
	vector <int> indexCount_;
	
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);

	void Render3D(Transform& transform);

	Texture* pToon_;
	void RenderToon(Transform& transform);
	void RenderEdge(Transform& transform);

	void RenderNMap(Transform& transform);
	void RenderAlpha(Transform& transform);
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw3D(Transform& transform);
	void	DrawNMap(Transform& transform);
	void    DrawToon(Transform& transform);
	void	DrawAlpha(Transform& transform);
	void    Release();
};