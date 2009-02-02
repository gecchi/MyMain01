#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


DWORD GgafDx9SquareModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE);


GgafDx9SquareModel::GgafDx9SquareModel(string prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
	TRACE("GgafDx9SquareModel::GgafDx9SquareModel(" <<  _model_name << ")");
	_pD3DMaterial9 = NULL;
	_pIDirect3DVertexBuffer9 = NULL;
	//_pModel_Next = NULL;
	_iSize_Vertecs = 0;
	_iSize_Vertec_unit = 0;
	//�f�o�C�C�X���X�g�Ή��̂��߁A�e�N�X�`���A���_�A�}�e���A���̏�������
	//GgafDx9God::_pModelManager->restoreSquareModel �ōs���Ă���B
}


//�`��
HRESULT GgafDx9SquareModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
	TRACE("GgafDx9SquareModel::draw("<<prm_pActor_Target->getName()<<")");
	//GgafDx9SquareActor* pSquareActor_Target = (GgafDx9SquareActor*)prm_pActor_Target;
	//HRESULT	hr;
	if (GgafDx9God::_pModelManager->_id_lastdraw != _id) { //�O��ƕ`�惂�f�����Ⴄ
		GgafDx9God::_pID3DDevice9 -> SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _iSize_Vertec_unit);
		GgafDx9God::_pID3DDevice9 -> SetMaterial(_pD3DMaterial9);
		GgafDx9God::_pID3DDevice9 -> SetFVF(GgafDx9SquareModel::FVF);
		GgafDx9God::_pID3DDevice9 -> SetTexture(0, NULL);
	} else { //�O��ƕ`�惂�f��������
		// �� ��������ł悢�B�����͂₢�ł����`�I(���Ԃ�)
	}

	//2D�̕`�悵�āA���C�g�܂����Ƃ�
	GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, FALSE); //���C�g�I�t
	GgafDx9God::_pID3DDevice9 -> DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, TRUE);

	//�O��`�惂�f�����ۑ�
	GgafDx9God::_pModelManager->_id_lastdraw = _id;
	GgafGod::_iNumPlayingActor++;
	return D3D_OK;
}

void GgafDx9SquareModel::restore() {
	_TRACE_("GgafDx9SquareModel::restore() " <<  _model_name << " start");
	GgafDx9God::_pModelManager->restoreSquareModel(this);
	_TRACE_("GgafDx9SquareModel::restore() " <<  _model_name << " end");
}

void GgafDx9SquareModel::onDeviceLost() {
	_TRACE_("GgafDx9SquareModel::onDeviceLost() " <<  _model_name << " start");
	release();
	_TRACE_("GgafDx9SquareModel::onDeviceLost() " <<  _model_name << " end");
}

void GgafDx9SquareModel::release() {
	_TRACE_("GgafDx9SquareModel::release() " <<  _model_name << " start");

	RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
	DELETE_IMPOSSIBLE_NULL(_pD3DMaterial9);

	_TRACE_("GgafDx9SquareModel::release() " <<  _model_name << " end");
}


GgafDx9SquareModel::~GgafDx9SquareModel() {
	_TRACE_("GgafDx9SquareModel::~GgafDx9SquareModel() " <<  _model_name << " start");
	release();
	_TRACE_("GgafDx9SquareModel::~GgafDx9SquareModel() " <<  _model_name << " end");
}
