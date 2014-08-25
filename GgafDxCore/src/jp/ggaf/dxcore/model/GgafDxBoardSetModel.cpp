#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardSetActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"


using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxBoardSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
GgafDxBoardSetModel::GgafDxBoardSetModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxBoardSetModel::GgafDxBoardSetModel(" << _model_name << ")");

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;
    _obj_model |= Obj_GgafDxBoardSetModel;

    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, nullptr, 10);
    pT = strtok(nullptr, "/");
    if (pT == nullptr) {
        _TRACE_("GgafDxBoardSetModel("<<prm_model_name<<") �̓����`��Z�b�g���ȗ��̂��߁A�ő��28���Z�b�g����܂��B");
        _set_num = 28;
    } else {
        _set_num = num;
        if (_set_num > 28) {
            _TRACE_("GgafDxBoardSetModel("<<prm_model_name<<") �̓����`��Z�b�g���I�[�o�[�B�ő��28���Z�b�g�ł����A����ȏ�̃Z�b�g���ł��B�Ӑ}���Ă��܂����H_set_num="<<_set_num);
        }
    }
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreBoardSetModel(GgafDxBoardSetModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

//�`��
HRESULT GgafDxBoardSetModel::draw(GgafDxDrawableActor* prm_pActor_target, int prm_draw_set_num) {
    TRACE4("GgafDxBoardSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_("GgafDxBoardSetModel::draw() "<<_model_name<<" �̕`��Z�b�g���I�[�o�[�B_set_num="<<_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //�Ώ�Actor
    GgafDxBoardSetActor* pTargetActor = (GgafDxBoardSetActor*)prm_pActor_target;
    //�Ώ�BoardSetActor�̃G�t�F�N�g���b�p
    GgafDxBoardSetEffect* pBoardSetEffect = (GgafDxBoardSetEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pBoardSetEffect->_pID3DXEffect;

    HRESULT hr;
    //���f���������Ȃ�Β��_�o�b�t�@���A�̐ݒ�̓X�L�b�v�ł���
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxBoardSetModel::FVF);
        pDevice->SetTexture(0, _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }

    if (GgafDxEffectManager::_pEffect_active != pBoardSetEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (GgafDxEffectManager::_pEffect_active) {
           TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_active<<")");
            hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() EndPass() �Ɏ��s���܂����B");
            hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (GgafDxEffectManager::_pEffect_active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                GgafDxEffectManager::_pEffect_active->_begin = false;
            }
#endif

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxBoardSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name<<"("<<pBoardSetEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pBoardSetEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pBoardSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
    INDEXPARAM& idxparam = _paIndexParam[prm_draw_set_num-1];
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  idxparam.BaseVertexIndex,
                                  idxparam.MinIndex,
                                  idxparam.NumVertices,
                                  idxparam.StartIndex,
                                  idxparam.PrimitiveCount);

    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pBoardSetEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxBoardSetModel::restore() {
    TRACE3("GgafDxBoardSetModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreBoardSetModel(this);
    TRACE3("GgafDxBoardSetModel::restore() " << _model_name << " end");
}

void GgafDxBoardSetModel::onDeviceLost() {
    TRACE3("GgafDxBoardSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxBoardSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxBoardSetModel::release() {
    TRACE3("GgafDxBoardSetModel::release() " << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    if (_papTextureConnection) {
        if (_papTextureConnection[0]) {
            _papTextureConnection[0]->close();
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_DELETEARR(_paIndexParam);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    TRACE3("GgafDxBoardSetModel::release() " << _model_name << " end");
}

GgafDxBoardSetModel::~GgafDxBoardSetModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

