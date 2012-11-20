#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxWorldBoundModel::GgafDxWorldBoundModel(char* prm_model_name) : GgafDxMorphMeshModel(prm_model_name) {
    TRACE3("GgafDxWorldBoundModel::GgafDxWorldBoundModel(" << _model_name << ")");
    _obj_model |= Obj_GgafDxWorldBoundModel;
}


HRESULT GgafDxWorldBoundModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxWorldBoundModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

    //対象アクター
    GgafDxWorldBoundActor* pTargetActor = (GgafDxWorldBoundActor*)prm_pActor_Target;
    //対象アクターのエフェクトラッパ
    GgafDxWorldBoundEffect* pWorldBoundEffect = (GgafDxWorldBoundEffect*)prm_pActor_Target->_pEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pWorldBoundEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //頂点バッファ設定
    if (GgafDxModelManager::_pModelLastDraw != this) {
        GgafDxGod::_pID3DDevice9->SetVertexDeclaration( _pIDirect3DVertexDeclaration9); //頂点フォーマット
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            GgafDxGod::_pID3DDevice9->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //インデックスバッファ設定
        GgafDxGod::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        hr = pID3DXEffect->SetValue(pWorldBoundEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw()SetValue(g_colMaterialDiffuse) に失敗しました。");

        if ((GgafDxEffectManager::_pEffect_Active != pWorldBoundEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) &&
                i == 0) {
            if (GgafDxEffectManager::_pEffect_Active) {
               TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() EndPass() に失敗しました。"<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() End() に失敗しました。");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pWorldBoundEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxWorldBoundModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");


            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pWorldBoundEffect->_effect_name<<"("<<pWorldBoundEffect<<")");
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
            if (pWorldBoundEffect->_begin == true) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pWorldBoundEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw()CommitChanges() に失敗しました。");
        }

        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pWorldBoundEffect->_effect_name);
        GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pWorldBoundEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;

    return D3D_OK;
}


GgafDxWorldBoundModel::~GgafDxWorldBoundModel() {
}

