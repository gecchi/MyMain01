#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMorphMeshActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMorphMeshEffect.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMorphMeshModel.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMorphMeshActor::GgafDxCubeMapMorphMeshActor(const char* prm_name,
                                                         const char* prm_model_id,
                                                         const char* prm_effect_id,
                                                         const char* prm_technique,
                                                         GgafStatus* prm_pStat,
                                                         GgafDxChecker* prm_pChecker) :

                                                 GgafDxMorphMeshActor(prm_name,
                                                                      prm_model_id,
                                                                      "H",
                                                                      prm_effect_id,
                                                                      "H",
                                                                      prm_technique,
                                                                      prm_pStat,
                                                                      prm_pChecker) ,
                                                 GgafDxICubeMapActor() {
    _obj_class |= Obj_GgafDxCubeMapMorphMeshActor;
    _class_name = "GgafDxCubeMapMorphMeshActor";
    _pCubeMapMorphMeshModel = (GgafDxCubeMapMorphMeshModel*)_pModel;
    _pCubeMapMorphMeshEffect = (GgafDxCubeMapMorphMeshEffect*)_pEffect;
}

void GgafDxCubeMapMorphMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pCubeMapMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetInt(_pCubeMapMorphMeshEffect->_h_morph_target_num, _pCubeMapMorphMeshModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "SetInt(_h_morph_target_num) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    for (int pattern = 1; pattern <= _pCubeMapMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pCubeMapMorphMeshEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "SetFloat(_ah_weight["<<pattern<<"]) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    }
    hr = pID3DXEffect->SetMatrix(_pCubeMapMorphMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    hr = pID3DXEffect->SetFloat(_pCubeMapMorphMeshEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "SetFloat(_h_reflectances) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    GgafDxGod::_pID3DDevice9->SetTexture(1, getCubeMapTexture());

    _pCubeMapMorphMeshModel->draw(this);
}


GgafDxCubeMapMorphMeshActor::~GgafDxCubeMapMorphMeshActor() {
}
