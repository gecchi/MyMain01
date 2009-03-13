#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9SquareModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE);

GgafDx9SquareModel::GgafDx9SquareModel(char* prm_platemodel_name) :
    GgafDx9Model(prm_platemodel_name) {
    TRACE3("GgafDx9SquareModel::GgafDx9SquareModel(" << _model_name << ")");
    _pD3DMaterial9 = NULL;
    _pIDirect3DVertexBuffer9 = NULL;
    //_pModel_Next = NULL;
    _size_vertecs = 0;
    _size_vertec_unit = 0;
    //�f�o�C�C�X���X�g�Ή��̂��߁A�e�N�X�`���A���_�A�}�e���A���̏�������
    //GgafDx9God::_pModelManager->restoreSquareModel �ōs���Ă���B
}

//�`��
HRESULT GgafDx9SquareModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE3("GgafDx9SquareModel::draw("<<prm_pActor_Target->getName()<<")");
    //GgafDx9SquareActor* pSquareActor_Target = (GgafDx9SquareActor*)prm_pActor_Target;
    //HRESULT	hr;
    if (GgafDx9ModelManager::_id_lastdraw != _id) { //�O��ƕ`�惂�f�����Ⴄ
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertec_unit);
        GgafDx9God::_pID3DDevice9->SetMaterial(_pD3DMaterial9);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9SquareModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
    } else { //�O��ƕ`�惂�f��������
        // �� ��������ł悢�B�����͂₢�ł����`�I(���Ԃ�)
    }

    //2D�̕`�悵�āA���C�g�܂����Ƃ�
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE); //���C�g�I�t
    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);

    //�O��`�惂�f�����ۑ�
    GgafDx9ModelManager::_id_lastdraw = _id;
    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9SquareModel::restore() {
    TRACE3("GgafDx9SquareModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreSquareModel(this);
    TRACE3("GgafDx9SquareModel::restore() " << _model_name << " end");
}

void GgafDx9SquareModel::onDeviceLost() {
    TRACE3("GgafDx9SquareModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9SquareModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9SquareModel::release() {
    TRACE3("GgafDx9SquareModel::release() " << _model_name << " start");

    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    DELETE_IMPOSSIBLE_NULL(_pD3DMaterial9);

    TRACE3("GgafDx9SquareModel::release() " << _model_name << " end");
}

GgafDx9SquareModel::~GgafDx9SquareModel() {
    TRACE3("GgafDx9SquareModel::~GgafDx9SquareModel() " << _model_name << " start");
    release();
    TRACE3("GgafDx9SquareModel::~GgafDx9SquareModel() " << _model_name << " end");
}
