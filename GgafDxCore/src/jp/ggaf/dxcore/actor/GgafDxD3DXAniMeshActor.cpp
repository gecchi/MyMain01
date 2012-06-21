#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxD3DXAniMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
GgafDxD3DXAniMeshActor::GgafDxD3DXAniMeshActor(const char* prm_name,
                                               const char* prm_model_id,
                                               const char* prm_effect_id,
                                               const char* prm_technique,
                                               GgafStatus* prm_pStat,
                                               GgafDxChecker* prm_pChecker) :

                                                   GgafDxDrawableActor(prm_name,
                                                                       prm_model_id,
                                                                       "A",
                                                                       prm_effect_id,
                                                                       "A",
                                                                       prm_technique,
                                                                       prm_pStat,
                                                                       prm_pChecker) {
    _obj_class |= Obj_GgafDxD3DXAniMeshActor;
    _class_name = "GgafDxD3DXAniMeshActor";
    _pD3DXAniMeshModel = (GgafDxD3DXAniMeshModel*)_pModel;
    _pD3DXAniMeshEffect = (GgafDxD3DXAniMeshEffect*)_pEffect;
    _pFunc_calcRotMvWorldMatrix = UTIL::setWorldMatrix_RxRzRyMv;
    _pPuppeteer = NEW GgafDxPuppeteer(this);
}

void GgafDxD3DXAniMeshActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //GgafDxD3DXAniMeshActorはメッシュαも設定（シェーダーで参照するため）
//    for (DWORD i = 0; i < _pD3DXAniMeshModel->_num_materials; i++) {
//        _paMaterial[i].Ambient.a = _alpha;
//        _paMaterial[i].Diffuse.a = _alpha;
//    }
}

void GgafDxD3DXAniMeshActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //GgafDxD3DXAniMeshActorはメッシュαも設定（シェーダーで参照するため）
//    for (DWORD i = 0; i < _pD3DXAniMeshModel->_num_materials; i++) {
//        _paMaterial[i].Ambient.a = _alpha;
//        _paMaterial[i].Diffuse.a = _alpha;
//    }
}

void GgafDxD3DXAniMeshActor::processDraw() {
    _pD3DXAniMeshModel->draw(this);
}

GgafDxD3DXAniMeshActor::~GgafDxD3DXAniMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pPuppeteer);
}
