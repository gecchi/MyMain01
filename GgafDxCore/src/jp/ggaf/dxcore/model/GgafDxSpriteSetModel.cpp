#include "jp/ggaf/dxcore/model/GgafDxSpriteSetModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteSetEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxSpriteSetActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxSpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_TEX1);
GgafDxSpriteSetModel::GgafDxSpriteSetModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    _DTRACE3_("GgafDxSpriteSetModel::GgafDxSpriteSetModel(" << _model_name << ")");

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;

    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, nullptr, 10);
    pT = strtok(nullptr, "/");
    if (pT == nullptr) {
        _DTRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") の同時描画セット数省略。最大の18セットが設定されます。");
        _set_num = 18;
    } else {
        _set_num = num;
        if (_set_num > 18) {
            _DTRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大の18セットですがそれ以上のセット数です。意図していますか？ _set_num="<<_set_num<<"。");
        }
    }
    _obj_model |= Obj_GgafDxSpriteSetModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreSpriteSetModel(GgafDxSpriteSetModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDxSpriteSetModel::draw(GgafDxDrawableActor* prm_pActor_target, int prm_draw_set_num) {
    _DTRACE4_("GgafDxSpriteSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwGgafCriticalException("GgafDxSpriteSetModel::draw() "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //対象Actor
    GgafDxSpriteSetActor* pTargetActor = (GgafDxSpriteSetActor*)prm_pActor_target;
    //対象SpriteSetActorのエフェクトラッパ
    GgafDxSpriteSetEffect* pSpriteSetEffect = (GgafDxSpriteSetEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;

    static HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    if (GgafDxModelManager::_pModelLastDraw  != this) {
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxSpriteSetModel::FVF);
        pDevice->SetTexture(0, _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }

    if (GgafDxEffectManager::_pEffect_active != pSpriteSetEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (GgafDxEffectManager::_pEffect_active) {
            _DTRACE4_("EndPass("<<GgafDxEffectManager::_pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_active<<")");
            hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() EndPass() に失敗しました。");
            hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() End() に失敗しました。");

#ifdef MY_DEBUG
            if (GgafDxEffectManager::_pEffect_active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                GgafDxEffectManager::_pEffect_active->_begin = false;
            }
#endif

        }
        _DTRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxSpriteSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _DTRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name<<"("<<pSpriteSetEffect<<")");
        hr = pID3DXEffect->Begin( &_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pSpriteSetEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pSpriteSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() CommitChanges() に失敗しました。");
    }
    _DTRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
    INDEXPARAM& idxparam = _paIndexParam[prm_draw_set_num - 1];
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  idxparam.BaseVertexIndex,
                                  idxparam.MinIndex,
                                  idxparam.NumVertices,
                                  idxparam.StartIndex,
                                  idxparam.PrimitiveCount);
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() １パス目 EndPass() に失敗しました。");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() "<<pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
            pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                          idxparam.BaseVertexIndex,
                                          idxparam.MinIndex,
                                          idxparam.NumVertices,
                                          idxparam.StartIndex,
                                          idxparam.PrimitiveCount);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() "<<pass+1<<"パス目 EndPass() に失敗しました。");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() １パス目 BeginPass(0) に失敗しました。");
    }

    //前回描画モデル保持
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pSpriteSetEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxSpriteSetModel::restore() {
    _DTRACE3_("GgafDxSpriteSetModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreSpriteSetModel(this);
    _DTRACE3_("GgafDxSpriteSetModel::restore() " << _model_name << " end");
}

void GgafDxSpriteSetModel::onDeviceLost() {
    _DTRACE3_("GgafDxSpriteSetModel::onDeviceLost() " << _model_name << " start");
    release();
    _DTRACE3_("GgafDxSpriteSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxSpriteSetModel::release() {
    _DTRACE3_("GgafDxSpriteSetModel::release() " << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    if (_papTextureConnection) {
        if (_papTextureConnection[0]) {
            _papTextureConnection[0]->close();
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_DELETEARR(_paIndexParam);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    _DTRACE3_("GgafDxSpriteSetModel::release() " << _model_name << " end");
}

GgafDxSpriteSetModel::~GgafDxSpriteSetModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

