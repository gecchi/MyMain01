#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMeshSetActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMeshSetEffect.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshSetModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMeshSetActor::GgafDxCubeMapMeshSetActor(const char* prm_name,
                                                     const char* prm_model_id,
                                                     const char* prm_effect_id,
                                                     const char* prm_technique,
                                                     GgafStatus* prm_pStat,
                                                     GgafDxChecker* prm_pChecker) :
                                              GgafDxMeshSetActor(prm_name,
                                                                 prm_model_id,
                                                                 "g",
                                                                 prm_effect_id,
                                                                 "g",
                                                                 prm_technique,
                                                                 prm_pStat,
                                                                 prm_pChecker) ,
                                              GgafDxICubeMapActor() {
    _obj_class |= Obj_GgafDxCubeMapMeshSetActor;
    _class_name = "GgafDxCubeMapMeshSetActor";
    _pCubeMapMeshSetModel = (GgafDxCubeMapMeshSetModel*)_pModel;
    _pCubeMapMeshSetEffect = (GgafDxCubeMapMeshSetEffect*)_pEffect;
}

void GgafDxCubeMapMeshSetActor::processDraw() {
    int draw_set_num = 0; //GgafDxCubeMapMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = _pCubeMapMeshSetEffect->_pID3DXEffect;
    HRESULT hr;

    hr = pID3DXEffect->SetFloat(_pCubeMapMeshSetEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "GgafDxCubeMapMeshActor::processDraw() SetFloat(_h_reflectances) に失敗しました。");
    GgafDxGod::_pID3DDevice9->SetTexture(1, getCubeMapTexture());

    //基本モデル頂点数
    GgafDxFigureActor* pDrawActor = this;
    GgafDxCubeMapMeshSetActor* pCubeMapMeshSetActor = nullptr;
    int model_set_num = _pCubeMapMeshSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pCubeMapMeshSetModel && pDrawActor->_hash_technique == _hash_technique ) {
            pCubeMapMeshSetActor = (GgafDxCubeMapMeshSetActor*)pDrawActor;
            if (getCubeMapTexture() == pCubeMapMeshSetActor->getCubeMapTexture() &&
                  (_reflectance-0.00001f < pCubeMapMeshSetActor->_reflectance && pCubeMapMeshSetActor->_reflectance < _reflectance+0.00001f)) {
                hr = pID3DXEffect->SetMatrix(_pCubeMapMeshSetEffect->_ah_matWorld[draw_set_num], &(pCubeMapMeshSetActor->_matWorld));
                checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
                hr = pID3DXEffect->SetValue(_pCubeMapMeshSetEffect->_ah_materialDiffuse[draw_set_num], &(pCubeMapMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNextRenderActor;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pCubeMapMeshSetActor; //描画セットの最後アクターをセット
    ((GgafDxMeshSetModel*)_pCubeMapMeshSetModel)->GgafDxMeshSetModel::draw(this, draw_set_num);
}

GgafDxCubeMapMeshSetActor::~GgafDxCubeMapMeshSetActor() {
}
