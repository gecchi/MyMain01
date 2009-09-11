#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9BoardSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
int GgafDx9BoardSetModel::_draw_set_num_LastDraw = -1;
GgafDx9BoardSetModel::GgafDx9BoardSetModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9BoardSetModel::GgafDx9BoardSetModel(" << _model_name << ")");

    _fSize_BoardSetModelWidthPx = 32.0f;
    _fSize_BoardSetModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pattno_max = 1;

    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paRectUV = NULL;
    _set_num = 8;
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDx9ModelManager::restoreBoardSetModel(GgafDx9BoardSetModel*)
    //�ōs���Ă���B
}

//�`��
HRESULT GgafDx9BoardSetModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE4("GgafDx9BoardSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
    //�Ώ�Actor
    static GgafDx9BoardSetActor* pTargetActor;
    pTargetActor = (GgafDx9BoardSetActor*)prm_pActor_Target;
    //�Ώ�BoardSetActor�̃G�t�F�N�g���b�p
    static GgafDx9BoardSetEffect* pBoardSetEffect;
    pBoardSetEffect = pTargetActor->_pBoardSetEffect;
    //�ΏۃG�t�F�N�g
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pBoardSetEffect->_pID3DXEffect;
    int draw_set_num = pTargetActor->_draw_set_num;

    static HRESULT hr;
    //���f���������Ȃ�Β��_�o�b�t�@���A�̐ݒ�̓X�L�b�v�ł���
    if (GgafDx9ModelManager::_pModelLastDraw  != this) {
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9BoardSetModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->view());
        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);
    }

    if (GgafDx9EffectManager::_pEffect_Active != pBoardSetEffect)  {
        if (GgafDx9EffectManager::_pEffect_Active != NULL) {
            TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            mightDx9Exception(hr, D3D_OK, "GgafDx9BoardSetActor::draw() EndPass() �Ɏ��s���܂����B");
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
            mightDx9Exception(hr, D3D_OK, "GgafDx9BoardSetActor::draw() End() �Ɏ��s���܂����B");
        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        mightDx9Exception(hr, S_OK, "GgafDx9BoardSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");
        TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        mightDx9Exception(hr, D3D_OK, "GgafDx9BoardSetActor::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        mightDx9Exception(hr, D3D_OK, "GgafDx9BoardSetActor::draw() BeginPass(0) �Ɏ��s���܂����B");
    } else {
        hr = pID3DXEffect->CommitChanges();
        mightDx9Exception(hr, D3D_OK, "GgafDx9BoardSetModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
    GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                    _paIndexParam[draw_set_num-1].BaseVertexIndex,
                                                    _paIndexParam[draw_set_num-1].MinIndex,
                                                    _paIndexParam[draw_set_num-1].NumVertices,
                                                    _paIndexParam[draw_set_num-1].StartIndex,
                                                    _paIndexParam[draw_set_num-1].PrimitiveCount);

    //�O��`�惂�f���ێ�
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9BoardSetModel::_draw_set_num_LastDraw = draw_set_num;
    GgafDx9EffectManager::_pEffect_Active = pBoardSetEffect;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDx9BoardSetModel::restore() {
    TRACE3("GgafDx9BoardSetModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreBoardSetModel(this);
    TRACE3("GgafDx9BoardSetModel::restore() " << _model_name << " end");
}

void GgafDx9BoardSetModel::onDeviceLost() {
    TRACE3("GgafDx9BoardSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9BoardSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9BoardSetModel::release() {
    TRACE3("GgafDx9BoardSetModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);
    _papTextureCon[0]->close();
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);
    TRACE3("GgafDx9BoardSetModel::release() " << _model_name << " end");
}

GgafDx9BoardSetModel::~GgafDx9BoardSetModel() {
    TRACE3("GgafDx9BoardSetModel::~GgafDx9BoardSetModel() " << _model_name << " start");
    release();
}

