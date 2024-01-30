#include "Model.h"
#include "SafeMacro.h"

namespace Model {

	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	std::vector<ModelData*> modelList;
}

int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//�t�@�C���l�[����������������A�ǂ܂�I
	for (auto& e : modelList)
	{
		if (e->filename_ == fileName) {
			pData->pfbx_ = e->pfbx_;
			break;
		}
	}

	if (pData->pfbx_ == nullptr)
	{
		pData->pfbx_ = new Fbx;
		pData->pfbx_->Load(fileName);
	}

	modelList.push_back(pData);
	return( modelList.size() - 1 );
}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
}

void Model::Draw3D(int hModel) {
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
	modelList[hModel]->pfbx_->Draw3D(modelList[hModel]->transform_);
}

void Model::DrawNMap(int hModel) {
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
	modelList[hModel]->pfbx_->DrawNMap(modelList[hModel]->transform_);
}

void Model::DrawToon(int hModel) {
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
	modelList[hModel]->pfbx_->DrawToon(modelList[hModel]->transform_);
}

void Model::DrawAlpha(int hModel)
{
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
	modelList[hModel]->pfbx_->DrawAlpha(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false; //�Q�Ƃ���Ă�H
	for (int i=0; i < modelList.size(); i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pfbx_ == modelList[j]->pfbx_)
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)
		{
			SAFE_DELETE(modelList[i]->pfbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}
