#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxMeshActor::GgafDxMeshActor(const char* prm_name,
                                 const char* prm_model_id,
                                 const char* prm_effect_id,
                                 const char* prm_technique,
                                 GgafStatus* prm_pStat,
                                 GgafDxChecker* prm_pChecker) :

                                     GgafDxDrawableActor(prm_name,
                                                         prm_model_id,
                                                         "X",
                                                         prm_effect_id,
                                                         "X",
                                                         prm_technique,
                                                         prm_pStat,
                                                         prm_pChecker) {
    _obj_class |= Obj_GgafDxMeshActor;
    _class_name = "GgafDxMeshActor";
    _pMeshModel = (GgafDxMeshModel*)_pModel;
    _pMeshEffect = (GgafDxMeshEffect*)_pEffect;
    _far_rate = -1.0f;
    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
}

GgafDxMeshActor::GgafDxMeshActor(const char* prm_name,
                                 const char* prm_model_id,
                                 const char* prm_model_type,
                                 const char* prm_effect_id,
                                 const char* prm_effect_type,
                                 const char* prm_technique,
                                 GgafStatus* prm_pStat,
                                 GgafDxChecker* prm_pChecker) :

                                   GgafDxDrawableActor(prm_name,
                                                       prm_model_id,
                                                       prm_model_type,
                                                       prm_effect_id,
                                                       prm_effect_type,
                                                       prm_technique,
                                                       prm_pStat,
                                                       prm_pChecker) {
    _obj_class |= Obj_GgafDxMeshActor;
    _class_name = "GgafDxMeshActor";
    _pMeshModel = (GgafDxMeshModel*)_pModel;
    _pMeshEffect = (GgafDxMeshEffect*)_pEffect;
    _far_rate = -1.0f;
    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
}

void GgafDxMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDxMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.a = _fAlpha;
        _paMaterial[i].Diffuse.a = _fAlpha;
    }
}

void GgafDxMeshActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDxMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.a = _fAlpha;
        _paMaterial[i].Diffuse.a = _fAlpha;
    }
}


void GgafDxMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_far_rate, _far_rate );

    _pMeshModel->draw(this);
}

GgafDxMeshActor::~GgafDxMeshActor() {
}
