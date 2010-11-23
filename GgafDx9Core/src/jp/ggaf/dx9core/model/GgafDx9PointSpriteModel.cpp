#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9PointSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDx9PointSpriteModel::GgafDx9PointSpriteModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9PointSpriteModel::GgafDx9PointSpriteModel(" << _model_name << ")");
    _pIDirect3DVertexBuffer9 = NULL;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDx9ModelManager::restorePointSpriteModel(GgafDx9PointSpriteModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

//�`��
HRESULT GgafDx9PointSpriteModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    TRACE4("GgafDx9PointSpriteModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

    //�Ώ�Actor
    static GgafDx9PointSpriteActor* pTargetActor;
    pTargetActor = (GgafDx9PointSpriteActor*)prm_pActor_Target;
    //�Ώ�PointSpriteActor�̃G�t�F�N�g���b�p
    static GgafDx9PointSpriteEffect* pPointSpriteEffect;
    pPointSpriteEffect = pTargetActor->_pPointSpriteEffect;
    //�ΏۃG�t�F�N�g
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pPointSpriteEffect->_pID3DXEffect;

    //����`���UV
    static HRESULT hr;
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9PointSpriteModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->refer()->_pIDirect3DTexture9);

        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_power, _fPowerBlink);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_threshold, _fBlinkThreshold);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hTexSize, _fTexSize);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() SetFloat(_hTexSize) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetInt(pPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() SetInt(_hTextureSplitRowcol) �Ɏ��s���܂����B");
    }


    if (GgafDx9EffectManager::_pEffect_Active != pPointSpriteEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)  {
        if (GgafDx9EffectManager::_pEffect_Active != NULL) {
            TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() EndPass() �Ɏ��s���܂����B");
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() End() �Ɏ��s���܂����B");

            ////
            if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDx9EffectManager::_pEffect_Active->_begin = false;
            }
            ////

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDx9PointSpriteActor::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() BeginPass(0) �Ɏ��s���܂����B");

        ////
        if (pPointSpriteEffect->_begin == true) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pPointSpriteEffect->_begin = true;
        }
        ////

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_POINTLIST, 0, _vertices_num);

    //�O��`�惂�f���ێ�
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pPointSpriteEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    //�O��`��UV���W�i�ւ̃|�C���^�j��ۑ�
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDx9PointSpriteModel::restore() {
    TRACE3("GgafDx9PointSpriteModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restorePointSpriteModel(this);
    TRACE3("GgafDx9PointSpriteModel::restore() " << _model_name << " end");
}

void GgafDx9PointSpriteModel::onDeviceLost() {
    TRACE3("GgafDx9PointSpriteModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9PointSpriteModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9PointSpriteModel::release() {
    TRACE3("GgafDx9PointSpriteModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    DELETEARR_IMPOSSIBLE_NULL(_paVtxBuffer_org);
    if (_papTextureCon) {
        if (_papTextureCon[0]) {
            _papTextureCon[0]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    TRACE3("GgafDx9PointSpriteModel::release() " << _model_name << " end");
}

GgafDx9PointSpriteModel::~GgafDx9PointSpriteModel() {
    //release();
    //��GgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) �ŌĂяo�����
}

