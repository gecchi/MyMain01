#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXAniMeshModel::GgafDx9D3DXAniMeshModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9D3DXAniMeshModel::GgafDx9D3DXAniMeshModel(" << prm_model_name << ")");
    _pFR = NULL;
    _pAcBase = NULL;
    _dwNumMaterials = 0L;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDx9ModelManager::restoreD3DXAniMeshModel(GgafDx9D3DXAniMeshModel*)
    //で行うようにした。要参照。

    _Ang = 0.0f;
}

HRESULT GgafDx9D3DXAniMeshModel::draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDx9D3DXAniMeshModel::draw("<<prm_pActor_Target->getName()<<")");
    //対象アクター
    GgafDx9D3DXAniMeshActor* pTargetActor = (GgafDx9D3DXAniMeshActor*)prm_pActor_Target;
    //対象MeshActorのエフェクトラッパ
    GgafDx9D3DXAniMeshEffect* pD3DXAniMeshEffect = (GgafDx9D3DXAniMeshEffect*)prm_pActor_Target->_pGgafDx9Effect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pD3DXAniMeshEffect->_pID3DXEffect;

//
//
//    if (GgafDx9ModelManager::_pModelLastDraw != this) {
//        //頂点バッファとインデックスバッファを設定
//        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertex_unit);
//        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9MeshModel::FVF);
//        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);
//
//        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _fPowerBlink);
//        checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
//        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _fBlinkThreshold);
//        checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
//    }
//















    GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9D3DXAniMeshActor::FVF);
    HRESULT hr;

    //checkDxException(hr, S_OK, "GgafDx9D3DXAniMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");
    hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_power, _fPowerBlink);
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_threshold, _fBlinkThreshold);
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    //_Ang += 0.004f;


//    // アニメーションをフレーム分進める
//    _pAcBase->AdvanceTime(_advanceTimePerFrame, NULL );


    //ワールド変換行列スタックによるワールド変換行列の計算
    D3DXMATRIX WorldMat;
    D3DXMatrixIdentity(&WorldMat);
    //D3DXMatrixRotationYawPitchRoll(&Rot, _Ang, _Ang / 2.37f, 0);
    //D3DXMatrixMultiply(&WorldMat, &WorldMat, &Rot);
    //&(pTargetActor->_matWorld)


    WTMStack.SetWorldMatrix(&WorldMat);
    // フレームのワールド変換行列を計算
    WTMStack.UpdateFrame(_pFR);

    list< D3DXFRAME_WORLD* > *pDrawList;
    pDrawList = WTMStack.GetDrawList(); // 描画リストを取得

    list<D3DXFRAME_WORLD*>::iterator it = pDrawList->begin();
    int materialnum;


    for (int i = 0; it != pDrawList->end(); i++, it++) {
        //描画
        if ((GgafDx9EffectManager::_pEffect_Active != pD3DXAniMeshEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDx9EffectManager::_pEffect_Active) {
                TRACE4("["<<i<<"],EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() EndPass() に失敗しました。");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() End() に失敗しました。");

#ifdef MY_DEBUG
                if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDx9EffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name<<"("<<pD3DXAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pD3DXAniMeshEffect->_begin == true) {
                throwGgafCriticalException("End していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pD3DXAniMeshEffect->_begin = true;
            }
#endif

        }

        //GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &(*it)->WorldTransMatrix); // ワールド変換行列を設定
        //_TRACE_("["<<i<<"]○SetMatrix FrameName="<<((*it)->Name)<<" 描画！");

        D3DXMatrixMultiply(&WorldMat, &((*it)->WorldTransMatrix), &(pTargetActor->_matWorld));

//        _TRACE_("(*it)->WorldTransMatrix=");
//        putMat(&((*it)->WorldTransMatrix));
//        _TRACE_("pTargetActor->_matWorld=");
//        putMat(&(pTargetActor->_matWorld));
//        _TRACE_("WorldMat=");
//        putMat(&WorldMat);
        //hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &((*it)->WorldTransMatrix));
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &WorldMat);
        checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");




        //hr = pID3DXEffect->SetMatrix(_pD3DXAniMeshEffect->_h_matWorld, &_matWorld );
            //checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        if ((*it)->pMeshContainer == NULL) {
            TRACE4("["<<i<<"]×SetMatrix FrameName="<<((*it)->Name)<<" 飛ばし！");
            continue;
        } else {

            materialnum = (*it)->pMeshContainer->NumMaterials;
            for (int j = 0; j < materialnum; j++) {
                TRACE4("["<<i<<"]["<<j<<"],SetMaterial");
                //GgafDx9God::_pID3DDevice9->SetMaterial(&(*it)->pMeshContainer->pMaterials[j].MatD3D);

                hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &((*it)->pMeshContainer->pMaterials[j].MatD3D.Diffuse), sizeof(D3DCOLORVALUE) );
                checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");

                hr = pID3DXEffect->CommitChanges();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() CommitChanges() に失敗しました。");

                (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(j);
            }
        }
    }

//
//
//
//    for (DWORD i = 0; i < _dwNumMaterials; i++) {
//        if (GgafDx9ModelManager::_pModelLastDraw != this || _dwNumMaterials != 1) {
//            if (_papTextureCon[i]) {
//                //テクスチャのセット
//                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[i]->refer()->_pIDirect3DBaseTexture9);
//            } else {
//                _TRACE_("GgafDx9D3DXAniMeshModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
//                //無ければテクスチャ無し
//                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
//            }
//            //マテリアルのセット
//            //GgafDx9God::_pID3DDevice9->SetMaterial(&(pTargetActor->_paD3DMaterial9[i]));
//            hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[i].Diffuse), sizeof(D3DCOLORVALUE) );
//            checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
//        }
//
//        //描画
//        if (GgafDx9EffectManager::_pEffect_Active != pD3DXAniMeshEffect && i == 0) {
//            if (GgafDx9EffectManager::_pEffect_Active) {
//                TRACE4("EndPass("<<GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name<<"("<<GgafDx9EffectManager::_pEffect_Active<<")");
//                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
//                checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() EndPass() に失敗しました。");
//                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
//                checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() End() に失敗しました。");
//            }
//
//            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
//            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
//            checkDxException(hr, S_OK, "GgafDx9D3DXAniMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");
//            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
//            UINT numPass;
//            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
//            checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() Begin() に失敗しました。");
//            hr = pID3DXEffect->BeginPass(0);
//            checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() BeginPass(0) に失敗しました。");
//        } else {
//            hr = pID3DXEffect->CommitChanges();
//            checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() CommitChanges() に失敗しました。");
//        }
//        TRACE4("DrawSubset: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
//        hr = _pID3DXAniMesh->DrawSubset(i);
//
//    }
    //前回描画モデル名反映
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pD3DXAniMeshEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
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
    if (_papTextureCon) {
        for (int i = 0; i < (int)_dwNumMaterials; i++) {
            if (_papTextureCon[i]) {
                TRACE3("close() _papTextureCon["<<i<<"]->"<<(_papTextureCon[i]->getIdStr()));
                _papTextureCon[i]->close();
            }
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //テクスチャの配列
//    RELEASE_IMPOSSIBLE_NULL(_pID3DXAniMesh);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    RELEASE_IMPOSSIBLE_NULL(_pAcBase);
    DELETE_IMPOSSIBLE_NULL(_pAH);
    //TODO:いつ消すの？
    TRACE3("GgafDx9D3DXAniMeshModel::release() " << _model_name << " end");
}

GgafDx9D3DXAniMeshModel::~GgafDx9D3DXAniMeshModel() {
    //release();
    //はGgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) で呼び出される
}
