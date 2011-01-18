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
    _draw_set_num = 0; //GgafDx9CubeMapMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pCubeMapMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    //基本モデル頂点数
    GgafDx9DrawableActor* pDrawActor = this;
    GgafDx9CubeMapMeshSetActor* pCubeMapMeshSetActor;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pGgafDx9Model == _pCubeMapMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pCubeMapMeshSetActor = (GgafDx9CubeMapMeshSetActor*)pDrawActor;
                hr = pID3DXEffect->SetMatrix(_pCubeMapMeshSetEffect->_ah_matWorld[_draw_set_num], &(pCubeMapMeshSetActor->_matWorld));
                checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
                hr = pID3DXEffect->SetValue(_pCubeMapMeshSetEffect->_ah_materialDiffuse[_draw_set_num], &(pCubeMapMeshSetActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
                checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
                _draw_set_num++;
                if (_draw_set_num >= _pCubeMapMeshSetModel->_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDx9Universe::_pActor_DrawActive = pCubeMapMeshSetActor; //描画セットの最後アクターをセット
    _pCubeMapMeshSetModel->draw(this, _draw_set_num);
}

GgafDx9CubeMapMeshSetActor::~GgafDx9CubeMapMeshSetActor() {
}
