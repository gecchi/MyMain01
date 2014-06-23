#include "stdafx.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMorphMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMorphMeshEffect.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMorphMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMorphMeshModel::GgafDxCubeMapMorphMeshModel(char* prm_model_name) : GgafDxMorphMeshModel(prm_model_name) {
    TRACE3("GgafDxCubeMapMorphMeshModel::GgafDxCubeMapMorphMeshModel(" << _model_name << ")");
    _obj_model |= Obj_GgafDxCubeMapMorphMeshModel;
}


HRESULT GgafDxCubeMapMorphMeshModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxCubeMapMorphMeshModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    GgafDxCubeMapMorphMeshActor* pTargetActor = (GgafDxCubeMapMorphMeshActor*)prm_pActor_Target;
    //対象アクターのエフェクトラッパ
    GgafDxCubeMapMorphMeshEffect* pCubeMapMorphMeshEffect = (GgafDxCubeMapMorphMeshEffect*)(prm_pActor_Target->getEffect());
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pCubeMapMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //頂点バッファ設定
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetVertexDeclaration( _pIDirect3DVertexDeclaration9); //頂点フォーマット
        pDevice->SetStreamSource(0, _pIDirect3DVertexBuffer9_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            pDevice->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //インデックスバッファ設定
        pDevice->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw() SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw() SetFloat(_h_specular_power) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (GgafDxModelManager::_pModelLastDraw != this || _nMaterialListGrp != 1) {
            if (_papTextureConnection[material_no]) {
                //テクスチャをs0レジスタにセット
                pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDxCubeMapMorphMeshModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pCubeMapMorphMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw()SetValue(g_colMaterialDiffuse) に失敗しました。");

        if ((GgafDxEffectManager::_pEffect_Active != pCubeMapMorphMeshEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) &&
                i == 0) {
            if (GgafDxEffectManager::_pEffect_Active) {
               TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw() EndPass() に失敗しました。"<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw() End() に失敗しました。");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pCubeMapMorphMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxCubeMapMorphMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");


            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pCubeMapMorphMeshEffect->_effect_name<<"("<<pCubeMapMorphMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw() Begin() に失敗しました。");
            //モーフターゲットの数により pass を切り替えている
            //プリマリメッシュのみ                             = pass0
            //プライマリメッシュ＋モーフターゲットメッシュ１つ = pass1
            //プライマリメッシュ＋モーフターゲットメッシュ２つ = pass2
            //以下最大９まで
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw() BeginPass("<<_morph_target_num<<") に失敗しました。");
#ifdef MY_DEBUG
            if (pCubeMapMorphMeshEffect->_begin) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pCubeMapMorphMeshEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxCubeMapMorphMeshModel::draw()CommitChanges() に失敗しました。");
        }

        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pCubeMapMorphMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      _paIndexParam[i].BaseVertexIndex,
                                      _paIndexParam[i].MinIndex,
                                      _paIndexParam[i].NumVertices,
                                      _paIndexParam[i].StartIndex,
                                      _paIndexParam[i].PrimitiveCount);
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pCubeMapMorphMeshEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;

    return D3D_OK;
}


GgafDxCubeMapMorphMeshModel::~GgafDxCubeMapMorphMeshModel() {
}

