#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxSpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_TEX1);
GgafDxSpriteSetModel::GgafDxSpriteSetModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxSpriteSetModel::GgafDxSpriteSetModel(" << _model_name << ")");

    _fSize_SpriteSetModelWidthPx = 32.0f;
    _fSize_SpriteSetModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pIDirect3DVertexBuffer9 = nullptr;
    _pIDirect3DIndexBuffer9 = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;

    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, nullptr, 10);
    pT = strtok(nullptr, "/");
    if (pT == nullptr) {
        _TRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") �̓����`��Z�b�g���ȗ��B�ő��18�Z�b�g���ݒ肳��܂��B");
        _set_num = 18;
    } else {
        _set_num = num;
        if (_set_num > 18) {
            _TRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") �̓����`��Z�b�g���I�[�o�[�B�ő��18�Z�b�g�ł�������ȏ�̃Z�b�g���ł��B�Ӑ}���Ă��܂����H _set_num="<<_set_num<<"�B");
        }
    }
    _obj_model |= Obj_GgafDxSpriteSetModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreSpriteSetModel(GgafDxSpriteSetModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

//�`��
HRESULT GgafDxSpriteSetModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxSpriteSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwGgafCriticalException("GgafDxSpriteSetModel::draw() "<<_model_name<<" �̕`��Z�b�g���I�[�o�[�B_set_num="<<_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    //�Ώ�Actor
    GgafDxSpriteSetActor* pTargetActor = (GgafDxSpriteSetActor*)prm_pActor_Target;
    //�Ώ�SpriteSetActor�̃G�t�F�N�g���b�p
    GgafDxSpriteSetEffect* pSpriteSetEffect = (GgafDxSpriteSetEffect*)prm_pActor_Target->_pEffect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;

    static HRESULT hr;
    //���f���������Ȃ�Β��_�o�b�t�@���A�̐ݒ�̓X�L�b�v�ł���
    if (GgafDxModelManager::_pModelLastDraw  != this) {
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDxGod::_pID3DDevice9->SetFVF(GgafDxSpriteSetModel::FVF);
        GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9);
        GgafDxGod::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }

    if (GgafDxEffectManager::_pEffect_Active != pSpriteSetEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)  {
        if (GgafDxEffectManager::_pEffect_Active) {
            TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() EndPass() �Ɏ��s���܂����B");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDxEffectManager::_pEffect_Active->_begin = false;
            }
#endif

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxSpriteSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name<<"("<<pSpriteSetEffect<<")");
        hr = pID3DXEffect->Begin( &_numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pSpriteSetEffect->_begin == true) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pSpriteSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
    INDEXPARAM& idxparam = _paIndexParam[prm_draw_set_num - 1];
    GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                   idxparam.BaseVertexIndex,
                                                   idxparam.MinIndex,
                                                   idxparam.NumVertices,
                                                   idxparam.StartIndex,
                                                   idxparam.PrimitiveCount);
    if (_numPass >= 2) { //�Q�p�X�ڈȍ~������
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() �P�p�X�� EndPass() �Ɏ��s���܂����B");

        for (UINT pass = 1; pass < _numPass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() "<<pass+1<<"�p�X�� BeginPass("<<pass<<") �Ɏ��s���܂����B");
            GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                           idxparam.BaseVertexIndex,
                                                           idxparam.MinIndex,
                                                           idxparam.NumVertices,
                                                           idxparam.StartIndex,
                                                           idxparam.PrimitiveCount);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() "<<pass+1<<"�p�X�� EndPass() �Ɏ��s���܂����B");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() �P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
    }

    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pSpriteSetEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxSpriteSetModel::restore() {
    TRACE3("GgafDxSpriteSetModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreSpriteSetModel(this);
    TRACE3("GgafDxSpriteSetModel::restore() " << _model_name << " end");
}

void GgafDxSpriteSetModel::onDeviceLost() {
    TRACE3("GgafDxSpriteSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxSpriteSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxSpriteSetModel::release() {
    TRACE3("GgafDxSpriteSetModel::release() " << _model_name << " start");
    GGAF_RELEASE(_pIDirect3DVertexBuffer9);
    GGAF_RELEASE(_pIDirect3DIndexBuffer9);
    if (_papTextureConnection) {
        if (_papTextureConnection[0]) {
            _papTextureConnection[0]->close();
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_DELETEARR(_paIndexParam);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    TRACE3("GgafDxSpriteSetModel::release() " << _model_name << " end");
}

GgafDxSpriteSetModel::~GgafDxSpriteSetModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

