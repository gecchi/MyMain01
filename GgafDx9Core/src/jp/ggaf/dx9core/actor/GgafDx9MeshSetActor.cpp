#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshSetActor::GgafDx9MeshSetActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect,
                                   const char* prm_technique,
                                   GgafDx9Checker* prm_pChecker) :
                                       GgafDx9DrawableActor(prm_name,
                                                                         prm_model,
                                                                         prm_effect,
                                                                         prm_technique,
                                                                         prm_pChecker) {
    _class_name = "GgafDx9MeshSetActor";
    _pMeshSetModel = (GgafDx9MeshSetModel*)_pGgafDx9Model;
    _pMeshSetEffect = (GgafDx9MeshSetEffect*)_pGgafDx9Effect;
}


void GgafDx9MeshSetActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableActor::setAlpha(prm_fAlpha);
    //GgafDx9MeshSetActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMeshSetModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}


void GgafDx9MeshSetActor::processDrawMain() {
    _draw_set_num = 1; //同一描画深度に、GgafDx9MeshSetActorの同じモデルが連続しているカウント数
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            GgafDx9Model* pGgafDx9Model = _pNextDrawActor->_pGgafDx9Model;
            if (pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > 8) {
                    _draw_set_num = 8;
                    break;
                }
                _pNextDrawActor= _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
//    _draw_set_index = 0;
//    _draw_object_num = 1;
//
//    //index   0 1 2 3 4
//    //object  1 2 4 8 16
//    if (cnt >= 8 && _pMeshSetModel->_setnum >= 4) {
//        _draw_set_index = 3;
//        _draw_object_num = 8;
//    } else if (4 <= cnt && _pMeshSetModel->_setnum >= 3) {
//        _draw_set_index = 2;
//        _draw_object_num = 4;
//    } else if (2 <= cnt && _pMeshSetModel->_setnum >= 2) {
//        _draw_set_index = 1;
//        _draw_object_num = 2;
//    } else {
//        _draw_set_index = 0;
//        _draw_object_num = 1;
//    }
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView);
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetActor::processDrawMain() SetMatrix(_hMatView) に失敗しました。");
    //基本モデル頂点数
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetActor::processDrawMain() SetInt(_h_nVertexs) に失敗しました。2");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawActor->_matWorld));
        mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetActor::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }

    _pMeshSetModel->draw(this);
}

GgafDx9MeshSetActor::~GgafDx9MeshSetActor() {
}
