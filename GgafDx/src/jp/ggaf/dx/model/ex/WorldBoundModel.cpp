#include "jp/ggaf/dx/model/ex/WorldBoundModel.h"

#include "jp/ggaf/dx/model/MassModel.h"

using namespace GgafDx;

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/effect/ex/WorldBoundEffect.h"
#include "jp/ggaf/dx/actor/ex/WorldBoundActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/Config.h"

WorldBoundModel::WorldBoundModel(const char* prm_model_id) : MorphMeshModel(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_WorldBoundModel;
}


HRESULT WorldBoundModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("WorldBoundModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* pDevice = pCARETAKER->_pID3DDevice9;
    //対象アクター
    WorldBoundActor* pTargetActor = (WorldBoundActor*)prm_pActor_target;
    //対象アクターのエフェクトラッパ
    WorldBoundEffect* pWorldBoundEffect = (WorldBoundEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pWorldBoundEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //頂点バッファ設定
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //頂点フォーマット
        pDevice->SetStreamSource(0, _paVertexBuffer_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            pDevice->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //インデックスバッファ設定
        pDevice->SetIndices(_paIndexBuffer);

        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        hr = pID3DXEffect->SetValue(pWorldBoundEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) &&
                i == 0) {
            if (pEffect_active) {
               _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() に失敗しました。"<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "End() に失敗しました。");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pWorldBoundEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pWorldBoundEffect->_effect_name<<"("<<pWorldBoundEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
            //モーフターゲットの数により pass を切り替えている
            //プリマリメッシュのみ                             = pass0
            //プライマリメッシュ＋モーフターゲットメッシュ１つ = pass1
            //プライマリメッシュ＋モーフターゲットメッシュ２つ = pass2
            //以下最大９まで
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "BeginPass("<<_morph_target_num<<") に失敗しました。");

#ifdef MY_DEBUG
            if (pWorldBoundEffect->_begin) {
                throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pWorldBoundEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
        }

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pWorldBoundEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      _paIndexParam[i].BaseVertexIndex,
                                      _paIndexParam[i].MinIndex,
                                      _paIndexParam[i].NumVertices,
                                      _paIndexParam[i].StartIndex,
                                      _paIndexParam[i].PrimitiveCount);
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_draw++;
#endif
    }
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pWorldBoundEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}


WorldBoundModel::~WorldBoundModel() {
}

