#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxPointSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDxPointSpriteModel::GgafDxPointSpriteModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxPointSpriteModel::GgafDxPointSpriteModel(" << _model_name << ")");
    _pIDirect3DVertexBuffer9 = NULL;
    _paVtxBuffer_org = NULL;
    _vertices_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _fSquareSize = 0.0f;
    _fTexSize = 0.0f;
    _texture_split_rowcol = 1;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restorePointSpriteModel(GgafDxPointSpriteModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

//�`��
HRESULT GgafDxPointSpriteModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxPointSpriteModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

    //�Ώ�Actor
    GgafDxPointSpriteActor* pTargetActor = (GgafDxPointSpriteActor*)prm_pActor_Target;
    //�Ώ�PointSpriteActor�̃G�t�F�N�g���b�p
    GgafDxPointSpriteEffect* pPointSpriteEffect = (GgafDxPointSpriteEffect*)prm_pActor_Target->_pEffect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pPointSpriteEffect->_pID3DXEffect;

    //����`���UV
    HRESULT hr;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDxGod::_pID3DDevice9->SetFVF(GgafDxPointSpriteModel::FVF);
        GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->use()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hTexSize, _fTexSize);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetFloat(_hTexSize) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetInt(pPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetInt(_hTextureSplitRowcol) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetValue(pPointSpriteEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
    }


    if (GgafDxEffectManager::_pEffect_Active != pPointSpriteEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)  {
        if (GgafDxEffectManager::_pEffect_Active) {
            TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() EndPass() �Ɏ��s���܂����B");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDxEffectManager::_pEffect_Active->_begin = false;
            }
#endif

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxPointSpriteActor::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name<<"("<<pPointSpriteEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pPointSpriteEffect->_begin == true) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pPointSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
    GgafDxGod::_pID3DDevice9->DrawPrimitive(D3DPT_POINTLIST, 0, _vertices_num);

    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pPointSpriteEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    //�O��`��UV���W�i�ւ̃|�C���^�j��ۑ�
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxPointSpriteModel::restore() {
    TRACE3("GgafDxPointSpriteModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restorePointSpriteModel(this);
    TRACE3("GgafDxPointSpriteModel::restore() " << _model_name << " end");
}

void GgafDxPointSpriteModel::onDeviceLost() {
    TRACE3("GgafDxPointSpriteModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxPointSpriteModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxPointSpriteModel::release() {
    TRACE3("GgafDxPointSpriteModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    DELETEARR_IMPOSSIBLE_NULL(_paVtxBuffer_org);
    if (_papTextureCon) {
        if (_papTextureCon[0]) {
            _papTextureCon[0]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial_default);
    TRACE3("GgafDxPointSpriteModel::release() " << _model_name << " end");
}

GgafDxPointSpriteModel::~GgafDxPointSpriteModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

