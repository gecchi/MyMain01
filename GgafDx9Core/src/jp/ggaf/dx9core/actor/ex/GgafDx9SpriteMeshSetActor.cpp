#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteMeshSetActor::GgafDx9SpriteMeshSetActor(const char* prm_name,
                                       const char* prm_model,
                                       GgafDx9Checker* prm_pChecker) :

                                        GgafDx9MeshSetActor(prm_name,
                                                           prm_model,
                                                           "SpriteMeshSetEffect",
                                                           "SpriteMeshSetTechnique",
                                                           prm_pChecker) {

    _class_name = "GgafDx9SpriteMeshSetActor";
    _pUvFliper = NEW GgafDx9UvFliper(this);
    _pUvFliper->forceUvFlipPtnRange(0, 1);
    _pUvFliper->setUvFlipPtnNo(0);
    _pUvFliper->setUvFlipMethod(NOT_ANIMATED, 1);
}


void GgafDx9SpriteMeshSetActor::processDraw() {

    _draw_set_num = 1; //GgafDx9MeshSetActorの同じモデルが連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > _pMeshSetModel->_set_num) {
                    _draw_set_num = _pMeshSetModel->_set_num;
                    break;
                }
                _pNextDrawActor = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_hMatView) に失敗しました。");
    //基本モデル頂点数
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetInt(_h_nVertexs) に失敗しました。2");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    GgafDx9SpriteMeshSetActor* pA;
    float u = 0;
    float v = 0;
    for (int i = 0; i < _draw_set_num; i++) {
        (*_pFunc_calcWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ahMaterialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_MaterialDiffuse) に失敗しました。");

        pA = (GgafDx9SpriteMeshSetActor*)pDrawActor; //このキャストは危険である。
        //[MEMO]
        //GgafDx9SpriteMeshSetActor は、GgafDx9MeshSetActor から派生しており、モデルクラスは同じである。
        //GgafDx9SpriteMeshSetActorが使用するモデル名("x/10/Flora"等)と、GgafDx9MeshSetActorが使用するモデル名が
        //同じものが存在する場合、pDrawActor は、GgafDx9MeshSetActor の可能性もある。
        //これは、_draw_set_num を求めるロジックは同一深度で連続の同一(アドレス)モデルである。という判定しか行っていないため。
        //したがって、本来は GgafDx9SpriteMeshSetActor と GgafDx9MeshSetActor で同一モデル名を使用することは禁止にしたい。
        //したいけども、そうそう起こる事でも無いので、とりあえず注意して重複させないように意識することにする。
        //TODO:重複しないようにする仕組みを組み込もう

        //UVオフセット設定
        pA->_pUvFliper->getUV(u, v);
        hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetU[i], u);
        checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_u) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetV[i], v);
        checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_v) に失敗しました。");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}


GgafDx9SpriteMeshSetActor::~GgafDx9SpriteMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFliper);
}
