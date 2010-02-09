#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9SpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_TEX1);
int GgafDx9SpriteSetModel::_draw_set_num_LastDraw = -1;
GgafDx9SpriteSetModel::GgafDx9SpriteSetModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9SpriteSetModel::GgafDx9SpriteSetModel(" << _model_name << ")");

    _fSize_SpriteSetModelWidthPx = 32.0f;
    _fSize_SpriteSetModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pattno_uvflip_Max = 0;
    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paRectUV = NULL;

    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, NULL, 10);
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        _TRACE_("GgafDx9SpriteSetModel("<<prm_model_name<<") �̓����`��Z�b�g���ȗ��B�ő��18�Z�b�g���ݒ肳��܂��B");
        _set_num = 18;
    } else {
        _set_num = num;
        if (_set_num > 18) {
            _TRACE_("GgafDx9SpriteSetModel("<<prm_model_name<<") �̓����`��Z�b�g���I�[�o�[�B_set_num="<<_set_num<<"�B�ő��18�Z�b�g���ݒ肳��܂��B");
            _set_num = 18;
        }
    }


    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDx9ModelManager::restoreSpriteSetModel(GgafDx9SpriteSetModel*)
    //�ōs���Ă���B
}

//�`��
HRESULT GgafDx9SpriteSetModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    TRACE4("GgafDx9SpriteSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
    if (_is_init_model == false) {
        prm_pActor_Target->onCreateModel(); //���f���쐬���̏�������
        _is_init_model = true;
    }
    //�Ώ�Actor
    static GgafDx9SpriteSetActor* pTargetActor;
    pTargetActor = (GgafDx9SpriteSetActor*)prm_pActor_Target;
    //�Ώ�SpriteSetActor�̃G�t�F�N�g���b�p
    static GgafDx9SpriteSetEffect* pSpriteSetEffect;
    pSpriteSetEffect = pTargetActor->_pSpriteSetEffect;
    //�ΏۃG�t�F�N�g
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;
    int draw_set_num = pTargetActor->_draw_set_num;

    static HRESULT hr;
    //���f���������Ȃ�Β��_�o�b�t�@���A�̐ݒ�̓X�L�b�v�ł���
    if (GgafDx9ModelManager::_pModelLastDraw  != this) {
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9SpriteSetModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->view());
        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);
    }

    if (GgafDx9EffectManager::_pEffect_Active != pSpriteSetEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)  {
        if (GgafDx9EffectManager::_pEffect_Active != NULL) {
            TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() EndPass() �Ɏ��s���܂����B");
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() End() �Ɏ��s���܂����B");
        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDx9SpriteSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_hPowerBlink, _fPowerBlink);
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() SetFloat(_hPowerBlink) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_hBlinkThreshold, _fBlinkThreshold);
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() SetFloat(_hBlinkThreshold) �Ɏ��s���܂����B");

        TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() BeginPass(0) �Ɏ��s���܂����B");
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
    GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                    _paIndexParam[draw_set_num - 1].BaseVertexIndex,
                                                    _paIndexParam[draw_set_num - 1].MinIndex,
                                                    _paIndexParam[draw_set_num - 1].NumVertices,
                                                    _paIndexParam[draw_set_num - 1].StartIndex,
                                                    _paIndexParam[draw_set_num - 1].PrimitiveCount);

    //�O��`�惂�f���ێ�
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9SpriteSetModel::_draw_set_num_LastDraw = draw_set_num;
    GgafDx9EffectManager::_pEffect_Active = pSpriteSetEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDx9SpriteSetModel::restore() {
    TRACE3("GgafDx9SpriteSetModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreSpriteSetModel(this);
    TRACE3("GgafDx9SpriteSetModel::restore() " << _model_name << " end");
}

void GgafDx9SpriteSetModel::onDeviceLost() {
    TRACE3("GgafDx9SpriteSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9SpriteSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9SpriteSetModel::release() {
    TRACE3("GgafDx9SpriteSetModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);
    if (_papTextureCon) {
        if (_papTextureCon[0]) {
            _papTextureCon[0]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    TRACE3("GgafDx9SpriteSetModel::release() " << _model_name << " end");
}

GgafDx9SpriteSetModel::~GgafDx9SpriteSetModel() {
    TRACE3("GgafDx9SpriteSetModel::~GgafDx9SpriteSetModel() " << _model_name << " start");
    release();
}

