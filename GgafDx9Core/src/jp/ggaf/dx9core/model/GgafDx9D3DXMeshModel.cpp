#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXMeshModel::GgafDx9D3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9D3DXMeshModel::GgafDx9D3DXMeshModel(" << prm_model_name << ")");
    _pID3DXMesh = NULL;
    _dwNumMaterials = 0L;
    _dwOptions = prm_dwOptions;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDx9ModelManager::restoreD3DXMeshModel(GgafDx9D3DXMeshModel*)
    //で行っている。
}

HRESULT GgafDx9D3DXMeshModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    TRACE4("GgafDx9D3DXMeshModel::draw("<<prm_pActor_Target->getName()<<")");
    GgafDx9D3DXMeshActor* pTargetActor;
    //対象アクター
    pTargetActor = (GgafDx9D3DXMeshActor*)prm_pActor_Target;
    //対象MeshActorのエフェクトラッパ
    GgafDx9MeshEffect* pMeshEffect;
    pMeshEffect = pTargetActor->_pMeshEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pMeshEffect->_pID3DXEffect;
    GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9D3DXMeshActor::FVF);
    static HRESULT hr;

    for (DWORD i = 0; i < _dwNumMaterials; i++) {
        if (GgafDx9ModelManager::_pModelLastDraw != this || _dwNumMaterials != 1) {
            if (_papTextureCon[i] != NULL) {
                //テクスチャのセット
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[i]->view());
            } else {
                _TRACE_("GgafDx9D3DXMeshModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            //マテリアルのセット
            //GgafDx9God::_pID3DDevice9->SetMaterial(&(pTargetActor->_paD3DMaterial9[i]));
            hr = pID3DXEffect->SetValue(pMeshEffect->_hMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[i].Diffuse), sizeof(D3DCOLORVALUE) );
            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() SetValue(g_MaterialDiffuse) に失敗しました。");
        }

        //描画
        if ((GgafDx9EffectManager::_pEffect_Active != pMeshEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
                TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() EndPass() に失敗しました。");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() End() に失敗しました。");
            }

            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            mightDx9Exception(hr, S_OK, "GgafDx9D3DXMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");
            TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() BeginPass(0) に失敗しました。");
        } else {
            hr = pID3DXEffect->CommitChanges();
            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() CommitChanges() に失敗しました。");
        }
        TRACE4("DrawSubset: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        hr = _pID3DXMesh->DrawSubset(i);
    }
    //前回描画モデル名反映
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pMeshEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

//シェーダー実装前
//        if (pTargetActor->_SX == LEN_UNIT &&
//            pTargetActor->_SY == LEN_UNIT &&
//            pTargetActor->_SZ == LEN_UNIT)
//        {
//            hr = _pID3DXMesh->DrawSubset(i); //なんて便利なメソッド！
//        } else {
//            //拡大縮小がなされているため、カメラ空間にトランスフォームされた後で頂点法線の正規化するように設定（負荷高）
//            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//            hr = _pID3DXMesh->DrawSubset(i); //なんて便利なメソッド！
//            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
//        }


void GgafDx9D3DXMeshModel::restore() {
    TRACE3("GgafDx9D3DXMeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreD3DXMeshModel(this);
    TRACE3("GgafDx9D3DXMeshModel::restore() " << _model_name << " end");
}

void GgafDx9D3DXMeshModel::onDeviceLost() {
    TRACE3("GgafDx9D3DXMeshModel::onDeviceLost() " << _model_name << " start");
    //デバイスロスト時は解放します。
    release();
    TRACE3("GgafDx9D3DXMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9D3DXMeshModel::release() {
    TRACE3("GgafDx9D3DXMeshModel::release() " << _model_name << " start");
    if (_pID3DXMesh == NULL) {
        throwGgafCriticalException("[GgafDx9D3DXMeshModel::release] Error! _pID3DXMeshが オブジェクトになっていないため release できません！");
    }
    //テクスチャを解放
	if (_papTextureCon) {
		for (DWORD i = 0; i < _dwNumMaterials; i++) {
			if (_papTextureCon[i] != NULL) {
				_papTextureCon[i]->close();
			}
		}
	}
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //テクスチャの配列
    RELEASE_IMPOSSIBLE_NULL(_pID3DXMesh);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);

    TRACE3("GgafDx9D3DXMeshModel::release() " << _model_name << " end");
}

GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() {
    TRACE3("GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() " << _model_name << " start");
    release();
}
