#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeMapMeshSetActor::GgafDx9CubeMapMeshSetActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique,
                                         GgafDx9Checker* prm_pChecker) :
                                              GgafDx9MeshSetActor(prm_name,
                                                                  prm_model_id,
                                                                  "g",
                                                                  prm_effect_id,
                                                                  "g",
                                                                  prm_technique,
                                                                  prm_pChecker) {
    _obj_class |= Obj_GgafDx9CubeMapMeshSetActor;
    _class_name = "GgafDx9CubeMapMeshSetActor";
    _pCubeMapMeshSetModel = (GgafDx9CubeMapMeshSetModel*)_pGgafDx9Model;
    _pCubeMapMeshSetEffect = (GgafDx9CubeMapMeshSetEffect*)_pGgafDx9Effect;
//    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
}



void GgafDx9CubeMapMeshSetActor::processDraw() {
    _draw_set_num = 1; //GgafDx9CubeMapMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx9DrawableActor* _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pCubeMapMeshSetModel &&
                _pNextDrawActor->_hash_technique == _hash_technique
            ) {
                _draw_set_num++;
                if (_draw_set_num > _pCubeMapMeshSetModel->_set_num) {
                    _draw_set_num = _pCubeMapMeshSetModel->_set_num;
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

    ID3DXEffect* pID3DXEffect = _pCubeMapMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //基本モデル頂点数
    hr = pID3DXEffect->SetInt(_pCubeMapMeshSetEffect->_h_vertexs_num, _pCubeMapMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMeshSetActor::processDraw() SetInt(_h_vertexs_num) に失敗しました。2");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        hr = pID3DXEffect->SetMatrix(_pCubeMapMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GgafDx9CubeMapMeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        hr = pID3DXEffect->SetValue(_pCubeMapMeshSetEffect->_ah_materialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDx9CubeMapMeshSetModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pCubeMapMeshSetModel->draw(this, _draw_set_num);
}

GgafDx9CubeMapMeshSetActor::~GgafDx9CubeMapMeshSetActor() {
}
