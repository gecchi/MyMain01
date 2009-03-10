#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9BoardModel::FVF = (D3DFVF_XYZ | D3DFVF_TEX1);

GgafDx9BoardModel::GgafDx9BoardModel(char* prm_platemodel_name) :
    GgafDx9Model(prm_platemodel_name) {
    TRACE("GgafDx9BoardModel::GgafDx9BoardModel(" << _model_name << ")");
    _fSize_BoardModelWidth = 32.0f;
    _fSize_BoardModelHeight = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pattno_max = 1;
    _pTextureCon = NULL;
    _paRectUV = NULL;
    _pRectUV_drawlast = NULL;
}

//�`��

HRESULT GgafDx9BoardModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE("GgafDx9BoardModel::draw("<<prm_pActor_Target->getName()<<")");
    //GgafDx9God::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0x000000, 1.0, 0);
    static GgafDx9BoardActor* pBoardActor_Target;
    pBoardActor_Target = (GgafDx9BoardActor*)prm_pActor_Target;

    //���ݒ�i�����Ȃ��̂ŃR�����g�j
    //	_pD3DMaterial9->Diffuse.a = pBoardActor_Target->_fAlpha;
    //	_pD3DMaterial9->Ambient.a = pBoardActor_Target->_fAlpha;
    //	GgafDx9God::_pID3DDevice9->SetMaterial(_pD3DMaterial9);

    if (GgafDx9ModelManager::_id_lastdraw != _id) {
        GgafDx9God::_pID3DDevice9->SetTexture(0, _pTextureCon->view());
        //������ւ�Ł@this �� 0x0h �ɂȂ�
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9BoardModel::FVF);

    } else {
        //������Ƃ��������̂��ǂ���
    }
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE); //���C�g�I�t
    GgafDx9God::_pID3DDevice9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pBoardActor_Target->_paVertex,
                                               pBoardActor_Target->_size_vertec_unit);
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

    GgafDx9ModelManager::_id_lastdraw = _id; //�O��`�惂�f�����ۑ�
    //GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9BoardModel::restore() {
    _TRACE_("GgafDx9BoardModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreBoardModel(this);
    _TRACE_("GgafDx9BoardModel::restore() " << _model_name << " end");
}

void GgafDx9BoardModel::release() {
    _TRACE_("GgafDx9BoardModel::release() " << _model_name << " start");
    //GgafDx9ModelManager::_pTextureManager->releaseResourceConnection(_pTextureCon);
    if (_pTextureCon != NULL) {
        _pTextureCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    _TRACE_("GgafDx9BoardModel::release() " << _model_name << " end");

}

void GgafDx9BoardModel::onDeviceLost() {
    _TRACE_("GgafDx9BoardModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9BoardModel::onDeviceLost() " << _model_name << " end");
}

GgafDx9BoardModel::~GgafDx9BoardModel() {
    _TRACE_("GgafDx9BoardModel::~GgafDx9BoardModel() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9BoardModel::~GgafDx9BoardModel() " << _model_name << " end");
}
