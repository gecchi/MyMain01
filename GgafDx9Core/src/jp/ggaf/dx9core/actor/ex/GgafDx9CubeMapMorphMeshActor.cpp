#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeMapMorphMeshActor::GgafDx9CubeMapMorphMeshActor(const char* prm_name,
                                             const char* prm_model_id,
                                             const char* prm_effect_id,
                                             const char* prm_technique,
                                             GgafDx9Checker* prm_pChecker) :

                                                 GgafDx9MorphMeshActor(prm_name,
                                                                       prm_model_id,
                                                                       "H",
                                                                       prm_effect_id,
                                                                       "H",
                                                                       prm_technique,
                                                                       prm_pChecker) {
    _obj_class |= Obj_GgafDx9CubeMapMorphMeshActor;
    _class_name = "GgafDx9CubeMapMorphMeshActor";
    _pCubeMapMorphMeshModel = (GgafDx9CubeMapMorphMeshModel*)_pGgafDx9Model;
    _pCubeMapMorphMeshEffect = (GgafDx9CubeMapMorphMeshEffect*)_pGgafDx9Effect;
    _pCubeMapTextureCon = (GgafDx9TextureConnection*)(P_UNIVERSE->_pCubeMapTextureManager->getConnection("uffizi_cross_cubemap.dds"));
}

void GgafDx9CubeMapMorphMeshActor::setCubeMapTexture(const char* prm_cubemap_tex) {
    _pCubeMapTextureCon->close();
    _pCubeMapTextureCon = (GgafDx9TextureConnection*)(P_UNIVERSE->_pCubeMapTextureManager->getConnection(prm_cubemap_tex));
}
void GgafDx9CubeMapMorphMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pCubeMapMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pCubeMapMorphMeshEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetInt(_pCubeMapMorphMeshEffect->_h_morph_target_num, _pCubeMapMorphMeshModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshActor::processDraw() SetInt(_h_morph_target_num) に失敗しました。");
    for (int pattern = 1; pattern <= _pCubeMapMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pCubeMapMorphMeshEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshActor::processDraw() SetFloat(_ah_weight["<<pattern<<"]) に失敗しました。");
    }
    hr = pID3DXEffect->SetMatrix(_pCubeMapMorphMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

    if (_pCubeMapTextureCon) {
        GgafDx9God::_pID3DDevice9->SetTexture(1, _pCubeMapTextureCon->refer()->_pIDirect3DBaseTexture9);
    } else {
        throwGgafCriticalException("GgafDx9CubeMapMorphMeshActor::processDraw() 環境マップテクスチャがありません this="<<getName());
    }

    _pCubeMapMorphMeshModel->draw(this);
}

GgafDx9CubeMapMorphMeshActor::~GgafDx9CubeMapMorphMeshActor() {
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
}
