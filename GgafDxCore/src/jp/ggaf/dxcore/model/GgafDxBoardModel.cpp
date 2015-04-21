#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxBoardModel::FVF = (D3DFVF_XYZ | D3DFVF_TEX1);

GgafDxBoardModel::GgafDxBoardModel(const char* prm_model_name) :
    GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxBoardModel::GgafDxBoardModel(" << _model_name << ")");
    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDxBoardModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreBoardModel(GgafDxBoardModel*)
    //�ōs���Ă���B
}

HRESULT GgafDxBoardModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxBoardModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //�Ώ�Actor
    const GgafDxBoardActor* const pTargetActor = (GgafDxBoardActor*)prm_pActor_target;
    //�Ώ�BoardActor�̃G�t�F�N�g���b�p
    GgafDxBoardEffect* const pBoardEffect = (GgafDxBoardEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pBoardEffect->_pID3DXEffect;
    //����`���UV
    float u,v;
    pTargetActor->_pUvFlipper->getUV(u,v);
    HRESULT hr;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxBoardModel::FVF);
        pDevice->SetTexture(0, _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pBoardEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }
    hr = pID3DXEffect->SetFloat(pBoardEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_offset_u) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pBoardEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_offset_v) �Ɏ��s���܂����B");

    if (GgafDxEffectManager::_pEffect_active != pBoardEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (GgafDxEffectManager::_pEffect_active) {
            _TRACE4_("EndPass("<<GgafDxEffectManager::_pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_active<<")");
            hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() EndPass() �Ɏ��s���܂����B");
            hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (GgafDxEffectManager::_pEffect_active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                GgafDxEffectManager::_pEffect_active->_begin = false;
            }
#endif

        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxBoardModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pBoardEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name<<"("<<pBoardEffect<<")");
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pBoardEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxBoardModel::restore() {
    _TRACE3_("GgafDxBoardModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreBoardModel(this);
    _TRACE3_("GgafDxBoardModel::restore() " << _model_name << " end");
}

void GgafDxBoardModel::release() {
    _TRACE3_("GgafDxBoardModel::release() " << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    if (_papTextureConnection) {
        if (_papTextureConnection[0]) {
            _papTextureConnection[0]->close();
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    _TRACE3_("GgafDxBoardModel::release() " << _model_name << " end");
}

void GgafDxBoardModel::onDeviceLost() {
    _TRACE3_("GgafDxBoardModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxBoardModel::onDeviceLost() " << _model_name << " end");
}

GgafDxBoardModel::~GgafDxBoardModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}
