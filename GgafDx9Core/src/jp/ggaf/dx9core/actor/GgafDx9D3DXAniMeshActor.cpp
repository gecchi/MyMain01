#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9D3DXAniMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
GgafDx9D3DXAniMeshActor::GgafDx9D3DXAniMeshActor(const char* prm_name,
                                                 const char* prm_model_id,
                                                 const char* prm_effect_id,
                                                 const char* prm_technique,
                                                 GgafDx9Checker* prm_pChecker) :

                                           GgafDx9DrawableActor(prm_name,
                                                                prm_model_id,
                                                                "A",
                                                                prm_effect_id,
                                                                "A",
                                                                prm_technique,
                                                                prm_pChecker) {
    _obj_class |= Obj_GgafDx9D3DXAniMeshActor;
    _class_name = "GgafDx9D3DXAniMeshActor";
    _pD3DXAniMeshModel = (GgafDx9D3DXAniMeshModel*)_pModel;
    _pD3DXAniMeshEffect = (GgafDx9D3DXAniMeshEffect*)_pEffect;
    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
    _pPuppeteer = NEW GgafDx9Puppeteer(this);
}

void GgafDx9D3DXAniMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDx9D3DXAniMeshActorはメッシュαも設定（シェーダーで参照するため）
//    for (DWORD i = 0; i < _pD3DXAniMeshModel->_dwNumMaterials; i++) {
//        _paMaterial[i].Ambient.a = _fAlpha;
//        _paMaterial[i].Diffuse.a = _fAlpha;
//    }
}

void GgafDx9D3DXAniMeshActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDx9D3DXAniMeshActorはメッシュαも設定（シェーダーで参照するため）
//    for (DWORD i = 0; i < _pD3DXAniMeshModel->_dwNumMaterials; i++) {
//        _paMaterial[i].Ambient.a = _fAlpha;
//        _paMaterial[i].Diffuse.a = _fAlpha;
//    }
}

void GgafDx9D3DXAniMeshActor::processDraw() {
    _pD3DXAniMeshModel->draw(this);
}

GgafDx9D3DXAniMeshActor::~GgafDx9D3DXAniMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pPuppeteer);
}
