#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXMeshModel::GgafDx9D3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9D3DXMeshModel::GgafDx9D3DXMeshModel(" << prm_model_name << ")");
    _pID3DXMesh = NULL;
    _paD3DMaterial9_default = NULL;
    _papTextureCon = NULL;
    _dwNumMaterials = 0L;
    //_pModel_Next     = NULL;
    //上記のプロパティは、GgafDx9God::_pModelManager->restoreD3DXMeshModel() から設定されることになる。
    _dwOptions = prm_dwOptions;
}

HRESULT GgafDx9D3DXMeshModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    static GgafDx9UntransformedActor* pActor_Target;
    //ここをどうやって振り分けるGgafDx9D3DXMeshActor と GgafDx9DynaD3DXMeshActor
    pActor_Target = (GgafDx9UntransformedActor*)prm_pActor_Target;
    static HRESULT hr;


        for (DWORD i = 0; i < _dwNumMaterials; i++) {
            //マテリアルのセット
            GgafDx9God::_pID3DDevice9->SetMaterial(&(pActor_Target->_paD3DMaterial9[i]));
            if (_papTextureCon[i] != NULL) {
                //テクスチャのセット
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[i]->view());
            } else {
                //無ければテクスチャ無し
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            //描画
            if (pActor_Target->_SX == LEN_UNIT &&
                pActor_Target->_SY == LEN_UNIT &&
                pActor_Target->_SZ == LEN_UNIT)
            {
                hr = _pID3DXMesh->DrawSubset(i); //なんて便利なメソッド！
            } else {
                //拡大縮小がなされているため、カメラ空間にトランスフォームされた後で頂点法線の正規化するように設定（負荷高）
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
                hr = _pID3DXMesh->DrawSubset(i); //なんて便利なメソッド！
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
            }
        }

//    }

    //前回描画モデル名反映
    GgafDx9ModelManager::_id_lastdraw = _id;
    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9D3DXMeshModel::restore() {
    _TRACE_("GgafDx9D3DXMeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreD3DXMeshModel(this);
    _TRACE_("GgafDx9D3DXMeshModel::restore() " << _model_name << " end");
}

void GgafDx9D3DXMeshModel::onDeviceLost() {
    _TRACE_("GgafDx9D3DXMeshModel::onDeviceLost() " << _model_name << " start");
    //デバイスロスト時は解放します。
    release();
    _TRACE_("GgafDx9D3DXMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9D3DXMeshModel::release() {
    _TRACE_("GgafDx9D3DXMeshModel::release() " << _model_name << " start");
    if (_pID3DXMesh == NULL) {
        throwGgafCriticalException("[GgafDx9D3DXMeshModel::release] Error! _pID3DXMeshが オブジェクトになっていないため release できません！");
    }
    //テクスチャを解放
    for (DWORD i = 0; i < _dwNumMaterials; i++) {
        if (_papTextureCon[i] != NULL) {
            _papTextureCon[i]->close();
        }
    }

    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //テクスチャの配列
    RELEASE_IMPOSSIBLE_NULL(_pID3DXMesh);
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    _TRACE_("GgafDx9D3DXMeshModel::release() " << _model_name << " end");
}

GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() {
    _TRACE_("GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() " << _model_name << " end");
}
