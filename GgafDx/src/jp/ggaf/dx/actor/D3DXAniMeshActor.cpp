#include "jp/ggaf/dx/actor/D3DXAniMeshActor.h"

#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/model/D3DXAniMeshModel.h"
#include "jp/ggaf/dx/effect/D3DXAniMeshEffect.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

DWORD D3DXAniMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
D3DXAniMeshActor::D3DXAniMeshActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   CollisionChecker* prm_pChecker) :

                                       FigureActor(prm_name,
                                                   prm_model,
                                                   TYPE_D3DXANIMESH_MODEL,
                                                   prm_effect_id,
                                                   TYPE_D3DXANIMESH_EFFECT,
                                                   prm_technique,
                                                   prm_pChecker),
_stackWorldMat() {
    _obj_class |= Obj_GgafDx_D3DXAniMeshActor;
    _class_name = "D3DXAniMeshActor";
    _pD3DXAniMeshModel = (D3DXAniMeshModel*)_pModel;
    _pD3DXAniMeshEffect = (D3DXAniMeshEffect*)_pEffect;
    _papAnimationSet = nullptr;
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    ID3DXAnimationController* pAc_cloned = _pD3DXAniMeshModel->getCloneAnimationController();
    _pPuppeteer = NEW Puppeteer(pAc_cloned);
    BoneAniMeshFrame* pFrameRoot = _pD3DXAniMeshModel->_pFrameRoot;
    _stackWorldMat.registerFrameTransformationMatrix(pFrameRoot);
}

void D3DXAniMeshActor::processDraw() {
    _pD3DXAniMeshModel->draw(this);
}

void D3DXAniMeshActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pD3DXAniMeshModel = (D3DXAniMeshModel*)_pModel;
}

D3DXAniMeshActor::~D3DXAniMeshActor() {
    GGAF_DELETE(_pPuppeteer);
}
