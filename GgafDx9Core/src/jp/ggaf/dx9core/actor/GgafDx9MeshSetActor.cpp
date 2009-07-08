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

    int cnt = 1; //同一描画深度に、GgafDx9MeshSetActorの同じモデルが連続しているカウント数
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = dynamic_cast<GgafDx9DrawableActor*>(_pNext_TheSameDrawDepthLevel);

_TRACE_(" GgafDx9MeshSetActor::processDrawMain()  ちぇーん");
    while (true) {
        if (_pNextDrawActor != NULL)  {
            GgafDx9Model* pGgafDx9Model =  _pNextDrawActor->_pGgafDx9Model;
            if (pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                cnt++;
                if (cnt > 8) {
                    break;
                }
                GgafActor* pA = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;

                _pNextDrawActor = dynamic_cast<GgafDx9DrawableActor*>(pA);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    int _set_index = 0;
    int _draw_object_num = 1;
    //index   0 1 2 3 4
    //object  1 2 4 8 16
//    if (cnt >= 16) {
//        _set_index = 4;
//        _draw_object_num = 16;
//    } else

    if (cnt >= 8) {
        _set_index = 3;
        _draw_object_num = 8;
    } else if (4 <= cnt &&  cnt <= 7) {
        _set_index = 2;
        _draw_object_num = 4;
    } else if (2 <= cnt &&  cnt <= 3) {
        _set_index = 1;
        _draw_object_num = 2;
    } else {
        _set_index = 0;
        _draw_object_num = 1;
    }


    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetActor::GgafDx9MeshSetEffect SetMatrix(g_matView) に失敗しました。");
    GgafDx9GeometricActor *pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_object_num; i++) {
        GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(pDrawActor, _aMatWorld[i]);
        pDrawActor = (GgafDx9GeometricActor*)(pDrawActor -> _pNext_TheSameDrawDepthLevel);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &_aMatWorld[i]);
        mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetActor::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");
    }

    _pMeshSetModel->draw(this);
}

GgafDx9MeshSetActor::~GgafDx9MeshSetActor() {
}
