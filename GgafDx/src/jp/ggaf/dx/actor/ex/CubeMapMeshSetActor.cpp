#include "jp/ggaf/dx/actor/ex/CubeMapMeshSetActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/ex/CubeMapMeshSetEffect.h"
#include "jp/ggaf/dx/model/ex/CubeMapMeshSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

CubeMapMeshSetActor::CubeMapMeshSetActor(const char* prm_name,
                                         const char* prm_model,
                                         const char* prm_effect_id,
                                         const char* prm_technique,
                                         CollisionChecker* prm_pChecker) :
                                              MeshSetActor(prm_name,
                                                           prm_model,
                                                           TYPE_CUBEMAPMESHSET_MODEL,
                                                           prm_effect_id,
                                                           TYPE_CUBEMAPMESHSET_EFFECT,
                                                           prm_technique,
                                                           prm_pChecker) ,
                                              ICubeMapActor() {
    _obj_class |= Obj_GgafDx_CubeMapMeshSetActor;
    _class_name = "CubeMapMeshSetActor";
    _pCubeMapMeshSetModel = (CubeMapMeshSetModel*)_pModel;
    _pCubeMapMeshSetEffect = (CubeMapMeshSetEffect*)_pEffect;
}

void CubeMapMeshSetActor::processDraw() {
    int draw_set_num = 0; //CubeMapMeshSetActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = _pCubeMapMeshSetEffect->_pID3DXEffect;
    HRESULT hr;

    hr = pID3DXEffect->SetFloat(_pCubeMapMeshSetEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "SetFloat(_h_reflectances) に失敗しました。");
    pCARETAKER->_pID3DDevice9->SetTexture(1, getCubeMapTexture());

    //基本モデル頂点数
    FigureActor* pDrawActor = this;
    CubeMapMeshSetActor* pCubeMapMeshSetActor = nullptr;
    int model_draw_set_num = _pCubeMapMeshSetModel->_draw_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pCubeMapMeshSetModel && pDrawActor->_hash_technique == _hash_technique ) {
            pCubeMapMeshSetActor = (CubeMapMeshSetActor*)pDrawActor;
            if (getCubeMapTexture() == pCubeMapMeshSetActor->getCubeMapTexture() &&
                  (_reflectance-0.00001f < pCubeMapMeshSetActor->_reflectance && pCubeMapMeshSetActor->_reflectance < _reflectance+0.00001f)) {
                hr = pID3DXEffect->SetMatrix(_pCubeMapMeshSetEffect->_ah_matWorld[draw_set_num], &(pCubeMapMeshSetActor->_matWorld));
                checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
                hr = pID3DXEffect->SetValue(_pCubeMapMeshSetEffect->_ah_materialDiffuse[draw_set_num], &(pCubeMapMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
                checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");

                pDrawActor = pDrawActor->_pNextRenderActor;
                draw_set_num++;
                if (draw_set_num >= model_draw_set_num) {
                    break;
                }
            } else {
                break;
            }
        } else {
            break;
        }
    }
    ((MeshSetModel*)_pCubeMapMeshSetModel)->MeshSetModel::draw(this, draw_set_num);
    _pNextRenderActor = pDrawActor;
}

void CubeMapMeshSetActor::changeModelByIndex(int prm_model_index) {
    MeshSetActor::changeModelByIndex(prm_model_index);
    _pCubeMapMeshSetModel = (CubeMapMeshSetModel*)_pModel;
}

CubeMapMeshSetActor::~CubeMapMeshSetActor() {
}
