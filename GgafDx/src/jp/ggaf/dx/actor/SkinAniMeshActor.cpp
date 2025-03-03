#include "jp/ggaf/dx/actor/SkinAniMeshActor.h"

#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/model/SkinAniMeshModel.h"
#include "jp/ggaf/dx/effect/SkinAniMeshEffect.h"
#include "jp/ggaf/dx/util/SkinAniMeshFrame.h"
#include "jp/ggaf/dx/util/Util.h"

using namespace GgafDx;

DWORD SkinAniMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
SkinAniMeshActor::SkinAniMeshActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect_id,
                                   const char* prm_technique) :

                                       FigureActor(prm_name,
                                                   prm_model,
                                                   TYPE_SKINANIMESH_MODEL,
                                                   prm_effect_id,
                                                   TYPE_SKINANIMESH_EFFECT,
                                                   prm_technique),
_stackWorldMat() {

    _obj_class |= Obj_GgafDx_SkinAniMeshActor;
    _class_name = "SkinAniMeshActor";
    _papAnimationSet = nullptr;
    _pSkinAniMeshModel = (SkinAniMeshModel*)_pModel;
    _pSkinAniMeshEffect = (SkinAniMeshEffect*)_pEffect;
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列

    ID3DXAnimationController* pAc_cloned = _pSkinAniMeshModel->getCloneAnimationController();
    _pPuppeteer = NEW Puppeteer(pAc_cloned, _pSkinAniMeshModel->_anim_ticks_per_second);
    SkinAniMeshFrame* pFrameRoot = _pSkinAniMeshModel->_pFrameRoot;
    _stackWorldMat.registerFrameTransformationMatrix(pFrameRoot);
}

void SkinAniMeshActor::processDraw() {
    _pSkinAniMeshModel->draw(this);
}


void SkinAniMeshActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pSkinAniMeshModel = (SkinAniMeshModel*)_pModel;
}


SkinAniMeshActor::~SkinAniMeshActor() {
    GGAF_DELETE(_pPuppeteer);
}
