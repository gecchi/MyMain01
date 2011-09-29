#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxSpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_TEX1);
int GgafDxSpriteSetModel::_draw_set_num_LastDraw = -1;
GgafDxSpriteSetModel::GgafDxSpriteSetModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxSpriteSetModel::GgafDxSpriteSetModel(" << _model_name << ")");

    _fSize_SpriteSetModelWidthPx = 32.0f;
    _fSize_SpriteSetModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
//    _pattno_uvflip_Max = 0;
    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
//    _paRectUV = NULL;

    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, NULL, 10);
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        _TRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") �̓����`��Z�b�g���ȗ��B�ő��18�Z�b�g���ݒ肳��܂��B");
        _set_num = 18;
    } else {
        _set_num = num;
        if (_set_num > 18) {
            _TRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") �̓����`��Z�b�g���I�[�o�[�B�ő��18�Z�b�g�ł�������ȏ�̃Z�b�g���ł��B�Ӑ}���Ă��܂����H _set_num="<<_set_num<<"�B");
        }
    }


    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreSpriteSetModel(GgafDxSpriteSetModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

//�`��
HRESULT GgafDxSpriteSetModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxSpriteSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

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
        GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->use()->_pIDirect3DBaseTexture9);
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
                throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDxEffectManager::_pEffect_Active->_begin = false;
            }
#endif

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxSpriteSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name<<"("<<pSpriteSetEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pSpriteSetEffect->_begin == true) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pSpriteSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
    GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                    _paIndexParam[prm_draw_set_num - 1].BaseVertexIndex,
                                                    _paIndexParam[prm_draw_set_num - 1].MinIndex,
                                                    _paIndexParam[prm_draw_set_num - 1].NumVertices,
                                                    _paIndexParam[prm_draw_set_num - 1].StartIndex,
                                                    _paIndexParam[prm_draw_set_num - 1].PrimitiveCount);

    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxSpriteSetModel::_draw_set_num_LastDraw = prm_draw_set_num;
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
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);
    if (_papTextureCon) {
        if (_papTextureCon[0]) {
            _papTextureCon[0]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
//    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial_default);
    TRACE3("GgafDxSpriteSetModel::release() " << _model_name << " end");
}

GgafDxSpriteSetModel::~GgafDxSpriteSetModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

