#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


DWORD GgafDx9PlateModel::FVF =  (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);

GgafDx9PlateModel::GgafDx9PlateModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE("GgafDx9PlateModel::GgafDx9PlateModel(" <<  _model_name << ")");
	_fSize_PlateModelWidth  = 32.0f;
	_fSize_PlateModelHeight = 32.0f;
	_iRowNum_TextureSplit    = 1;
	_iColNum_TextureSplit    = 1;
	_iPatternNo_Max = 1;
	_pTexture = NULL;
	_paRectUV = NULL;
	_pRectUV_drawlast = NULL;
}



//�`��

HRESULT GgafDx9PlateModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
	TRACE("GgafDx9PlateModel::draw("<<prm_pActor_Target->getName()<<")");
	//GgafDx9God::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0x000000, 1.0, 0);
	GgafDx9PlateActor* pPlateActor_Target = (GgafDx9PlateActor*)prm_pActor_Target;


	//���ݒ�i�����Ȃ��̂ŃR�����g�j
//	_pD3DMaterial9->Diffuse.a = pPlateActor_Target->_fAlpha;
//	_pD3DMaterial9->Ambient.a = pPlateActor_Target->_fAlpha;
//	GgafDx9God::_pID3DDevice9->SetMaterial(_pD3DMaterial9);

	if (GgafDx9God::_pModelManager->_id_lastdraw != _id) {
		GgafDx9God::_pID3DDevice9->SetTexture( 0, _pTexture->getResource() );
		//������ւ�Ł@this �� 0x0h �ɂȂ�
		GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9PlateModel::FVF);

	} else {
		//������Ƃ��������̂�I
	}
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE); //���C�g�I�t
	GgafDx9God::_pID3DDevice9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pPlateActor_Target->_paVertex, pPlateActor_Target->_iSize_Vertec_unit);
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);

	//����2008/10/24 �̔]�݂���
	//GgafDx9God::_pID3DDevice9->SetMaterial �ŐF���}�e���A���ŕύX�ł���Ǝv���Ă����B
	//�����������A���낢�����Ă��ł��Ȃ������B �g�����X�t�H�[���ς݁iFVF �� D3DFVF_XYZRHW �t�j�̓}�e���A�����K�p����Ȃ��i�����ł��Ȃ��j�E�E�E
	//�Ƃ������A�}�e���A���K�p�͌Œ�p�C�v���C���̍H�����Ƃ������ƂȂ̂��A�悭�킩��Ȃ��B
	//���������_�J���[�͓K�p�����A����͂ǂ��ōs����̂��B�����_�̍Ō��ւ�Œ��_�J���[�͓K�p�����Ƃ������ƂȂ̂��H
	//
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_MATERIAL); //�}�e���A����񌳂��}�e���A���ɂ���
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1); //�}�e���A����񌳂𒸓_�J���[�ɂ���
	//
	//�Ƃ�����̂ŁA�}�e���A�������_�J���[���Ō�̃����_�����O���ɐݒ�ł�����̂Ǝv���Ă��B�Ⴄ�̂��A�������̂��A�ݒ肪����Ȃ��̂�����B
	//TODO:�Ƃ肠�������i�}�e���A���j�͌�񂵁B

	GgafDx9God::_pModelManager->_id_lastdraw = _id; //�O��`�惂�f�����ۑ�
	//GgafGod::_iNumPlayingActor++;
	return D3D_OK;
}


void GgafDx9PlateModel::restore() {
	_TRACE_("GgafDx9PlateModel::restore() " <<  _model_name << " start");
	GgafDx9God::_pModelManager->restorePlateModel(this);
	_TRACE_("GgafDx9PlateModel::restore() " <<  _model_name << " end");
}

void GgafDx9PlateModel::release() {
	_TRACE_("GgafDx9PlateModel::release() " <<  _model_name << " start");
	//GgafDx9ModelManager::_pTextureManager->releaseResourceLead(_pTexture);
	RELEASE_SAFETY(_pTexture);
	DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
	_TRACE_("GgafDx9PlateModel::release() " <<  _model_name << " end");


}

void GgafDx9PlateModel::onDeviceLost() {
	_TRACE_("GgafDx9PlateModel::onDeviceLost() " <<  _model_name << " start");
	release();
	_TRACE_("GgafDx9PlateModel::onDeviceLost() " <<  _model_name << " end");
}

GgafDx9PlateModel::~GgafDx9PlateModel() {
    _TRACE_("GgafDx9PlateModel::~GgafDx9PlateModel() " <<  _model_name << " start");
    release();
    _TRACE_("GgafDx9PlateModel::~GgafDx9PlateModel() " <<  _model_name << " end");
}
