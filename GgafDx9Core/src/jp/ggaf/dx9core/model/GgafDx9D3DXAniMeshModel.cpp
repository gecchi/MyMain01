#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXAniMeshModel::GgafDx9D3DXAniMeshModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9D3DXAniMeshModel::GgafDx9D3DXAniMeshModel(" << prm_model_name << ")");
    _pFR = NULL;
    _pAC = NULL;
    _dwNumMaterials = 0L;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDx9ModelManager::restoreD3DXAniMeshModel(GgafDx9D3DXAniMeshModel*)
    //で行っている。

    _Ang = 0.0f;
}

HRESULT GgafDx9D3DXAniMeshModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE4("GgafDx9D3DXAniMeshModel::draw("<<prm_pActor_Target->getName()<<")");
    GgafDx9D3DXAniMeshActor* pTargetActor;
    //対象アクター
    pTargetActor = (GgafDx9D3DXAniMeshActor*)prm_pActor_Target;
    //対象MeshActorのエフェクトラッパ
    GgafDx9D3DXAniMeshEffect* pD3DXAniMeshEffect;
    pD3DXAniMeshEffect = pTargetActor->_pD3DXAniMeshEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pD3DXAniMeshEffect->_pID3DXEffect;
    GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9D3DXAniMeshActor::FVF);
    static HRESULT hr;



    //_Ang += 0.004f;





    //ワールド変換行列スタックによるワールド変換行列の計算
    //D3DXMATRIX WorldMat;
    //D3DXMatrixIdentity(&WorldMat);
    //D3DXMatrixRotationYawPitchRoll(&Rot, _Ang, _Ang / 2.37f, 0);
    //D3DXMatrixMultiply(&WorldMat, &WorldMat, &Rot);
    //&(pTargetActor->_matWorld)
    // アニメーションをフレーム分進める
    _pAC->AdvanceTime( 6.0f, NULL );

    WTMStack.SetWorldMatrix(&(pTargetActor->_matWorld));
    // フレームのワールド変換行列を計算
    WTMStack.UpdateFrame(_pFR);

    pDrawList = WTMStack.GetDrawList(); // 描画リストを取得

    list<D3DXFRAME_WORLD*>::iterator it = pDrawList->begin();
    int materialnum;

    for (int i = 0; it != pDrawList->end(); i++, it++) {
        //描画
        if (GgafDx9EffectManager::_pEffect_Active != pD3DXAniMeshEffect && i == 0) {
            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
                TRACE4("["<<i<<"],EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                mightDx9Exception(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() EndPass() に失敗しました。");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                mightDx9Exception(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() End() に失敗しました。");
            }

            TRACE4("["<<i<<"],SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            mightDx9Exception(hr, S_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");
            TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            mightDx9Exception(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            mightDx9Exception(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() BeginPass(0) に失敗しました。");
        } else {
            hr = pID3DXEffect->CommitChanges();
            mightDx9Exception(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() CommitChanges() に失敗しました。");
        }


        //hr = pID3DXEffect->SetMatrix(_pD3DXAniMeshEffect->_hMatWorld, &_matWorld );
            //mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");


        //GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &(*it)->WorldTransMatrix); // ワールド変換行列を設定
        TRACE4("["<<i<<"],SetMatrix");
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_hMatWorld, &(*it)->WorldTransMatrix );
        mightDx9Exception(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

        materialnum = (*it)->pMeshContainer->NumMaterials;
        for (int j = 0; j < materialnum; j++) {
            TRACE4("["<<i<<"]["<<j<<"],SetMaterial");
            GgafDx9God::_pID3DDevice9->SetMaterial(&(*it)->pMeshContainer->pMaterials[j].MatD3D);
            TRACE4("["<<i<<"]["<<j<<"],DrawSubset");
            (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(j);
        }
    }

//
//
//
//    for (DWORD i = 0; i < _dwNumMaterials; i++) {
//        if (GgafDx9ModelManager::_pModelLastDraw != this || _dwNumMaterials != 1) {
//            if (_papTextureCon[i] != NULL) {
//                //テクスチャのセット
//                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[i]->view());
//            } else {
//                _TRACE_("GgafDx9D3DXAniMeshModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
//                //無ければテクスチャ無し
//                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
//            }
//            //マテリアルのセット
//            //GgafDx9God::_pID3DDevice9->SetMaterial(&(pTargetActor->_paD3DMaterial9[i]));
//            hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_hMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[i].Diffuse), sizeof(D3DCOLORVALUE) );
//            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetValue(g_MaterialDiffuse) に失敗しました。");
//        }
//
//        //描画
//        if (GgafDx9EffectManager::_pEffect_Active != pD3DXAniMeshEffect && i == 0) {
//            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
//                TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
//                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
//                mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() EndPass() に失敗しました。");
//                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
//                mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() End() に失敗しました。");
//            }
//
//            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
//            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
//            mightDx9Exception(hr, S_OK, "GgafDx9D3DXAniMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");
//            TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
//            UINT numPass;
//            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
//            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() Begin() に失敗しました。");
//            hr = pID3DXEffect->BeginPass(0);
//            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() BeginPass(0) に失敗しました。");
//        } else {
//            hr = pID3DXEffect->CommitChanges();
//            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() CommitChanges() に失敗しました。");
//        }
//        TRACE4("DrawSubset: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
//        hr = _pID3DXAniMesh->DrawSubset(i);
//
//    }
    //前回描画モデル名反映
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pD3DXAniMeshEffect;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

//シェーダー実装前
//        if (pTargetActor->_SX == LEN_UNIT &&
//            pTargetActor->_SY == LEN_UNIT &&
//            pTargetActor->_SZ == LEN_UNIT)
//        {
//            hr = _pID3DXAniMesh->DrawSubset(i); //なんて便利なメソッド！
//        } else {
//            //拡大縮小がなされているため、カメラ空間にトランスフォームされた後で頂点法線の正規化するように設定（負荷高）
//            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//            hr = _pID3DXAniMesh->DrawSubset(i); //なんて便利なメソッド！
//            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
//        }


void GgafDx9D3DXAniMeshModel::restore() {
    TRACE3("GgafDx9D3DXAniMeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreD3DXAniMeshModel(this);
    TRACE3("GgafDx9D3DXAniMeshModel::restore() " << _model_name << " end");
}

void GgafDx9D3DXAniMeshModel::onDeviceLost() {
    TRACE3("GgafDx9D3DXAniMeshModel::onDeviceLost() " << _model_name << " start");
    //デバイスロスト時は解放します。
    release();
    TRACE3("GgafDx9D3DXAniMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9D3DXAniMeshModel::release() {
    TRACE3("GgafDx9D3DXAniMeshModel::release() " << _model_name << " start");
//    if (_pID3DXAniMesh == NULL) {
//        throwGgafCriticalException("[GgafDx9D3DXAniMeshModel::release] Error! _pID3DXAniMeshが オブジェクトになっていないため release できません！");
//    }
    //テクスチャを解放
    for (DWORD i = 0; i < _dwNumMaterials; i++) {
        if (_papTextureCon[i] != NULL) {
            _papTextureCon[i]->close();
        }
    }

    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //テクスチャの配列
//    RELEASE_IMPOSSIBLE_NULL(_pID3DXAniMesh);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);

    TRACE3("GgafDx9D3DXAniMeshModel::release() " << _model_name << " end");
}

GgafDx9D3DXAniMeshModel::~GgafDx9D3DXAniMeshModel() {
    TRACE3("GgafDx9D3DXAniMeshModel::~GgafDx9D3DXAniMeshModel() " << _model_name << " start");
    release();
}
