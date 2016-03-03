#include "jp/ggaf/dxcore/model/ex/GgafDxWorldBoundModel.h"

using namespace GgafCore;
using namespace GgafDxCore;

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxWorldBoundEffect.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxWorldBoundActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

GgafDxWorldBoundModel::GgafDxWorldBoundModel(const char* prm_model_name) : GgafDxMorphMeshModel(prm_model_name) {
    _TRACE3_("GgafDxWorldBoundModel::GgafDxWorldBoundModel(" << _model_name << ")");
    _obj_model |= Obj_GgafDxWorldBoundModel;
}


HRESULT GgafDxWorldBoundModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxWorldBoundModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    GgafDxWorldBoundActor* pTargetActor = (GgafDxWorldBoundActor*)prm_pActor_target;
    //対象アクターのエフェクトラッパ
    GgafDxWorldBoundEffect* pWorldBoundEffect = (GgafDxWorldBoundEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pWorldBoundEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //頂点バッファ設定
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //頂点フォーマット
        pDevice->SetStreamSource(0, _pVertexBuffer_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            pDevice->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //インデックスバッファ設定
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        hr = pID3DXEffect->SetValue(pWorldBoundEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw()SetValue(g_colMaterialDiffuse) に失敗しました。");
        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if ((pEffect_active != pWorldBoundEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) &&
                i == 0) {
            if (pEffect_active) {
               _TRACE4_("GgafDxWorldBoundModel::draw() EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() EndPass() に失敗しました。"<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() End() に失敗しました。");
                if (pEffect_active->_obj_effect & Obj_GgafDxMassEffect) {
                    pDevice->SetStreamSourceFreq( 0, 1 );
                    pDevice->SetStreamSourceFreq( 1, 1 );
                }
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("GgafDxWorldBoundModel::draw() SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pWorldBoundEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxWorldBoundModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            _TRACE4_("GgafDxWorldBoundModel::draw() BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pWorldBoundEffect->_effect_name<<"("<<pWorldBoundEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() Begin() に失敗しました。");
            //モーフターゲットの数により pass を切り替えている
            //プリマリメッシュのみ                             = pass0
            //プライマリメッシュ＋モーフターゲットメッシュ１つ = pass1
            //プライマリメッシュ＋モーフターゲットメッシュ２つ = pass2
            //以下最大９まで
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() BeginPass("<<_morph_target_num<<") に失敗しました。");

#ifdef MY_DEBUG
            if (pWorldBoundEffect->_begin) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pWorldBoundEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() CommitChanges() に失敗しました。");
        }

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pWorldBoundEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      _paIndexParam[i].BaseVertexIndex,
                                      _paIndexParam[i].MinIndex,
                                      _paIndexParam[i].NumVertices,
                                      _paIndexParam[i].StartIndex,
                                      _paIndexParam[i].PrimitiveCount);
        GgafGod::_num_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pWorldBoundEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}


GgafDxWorldBoundModel::~GgafDxWorldBoundModel() {
}

