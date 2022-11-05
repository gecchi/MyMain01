#include "jp/ggaf/dx/actor/BoneAniMeshActor.h"

#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/model/BoneAniMeshModel.h"
#include "jp/ggaf/dx/effect/BoneAniMeshEffect.h"
#include "jp/ggaf/dx/util/BoneAniMeshFrame.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

DWORD BoneAniMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
BoneAniMeshActor::BoneAniMeshActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   CollisionChecker* prm_pChecker) :

                                       FigureActor(prm_name,
                                                   prm_model,
                                                   TYPE_BONEANIMESH_MODEL,
                                                   prm_effect_id,
                                                   TYPE_BONEANIMESH_EFFECT,
                                                   prm_technique,
                                                   prm_pChecker) ,
_stackWorldMat() {

    _obj_class |= Obj_GgafDx_BoneAniMeshActor;
    _class_name = "BoneAniMeshActor";
    _papAnimationSet = nullptr;
    _pBoneAniMeshModel = (BoneAniMeshModel*)_pModel;
    _pBoneAniMeshEffect = (BoneAniMeshEffect*)_pEffect;
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列

    ID3DXAnimationController* pAc_cloned = _pBoneAniMeshModel->getCloneAnimationController();
    _pPuppeteer = NEW Puppeteer(pAc_cloned);
    BoneAniMeshFrame* pFrameRoot = _pBoneAniMeshModel->_pFrameRoot;
    _stackWorldMat.registerFrameTransformationMatrix(pFrameRoot);
}

void BoneAniMeshActor::processDraw() {
    _pBoneAniMeshModel->draw(this);
}

BoneAniMeshActor::~BoneAniMeshActor() {
    GGAF_DELETE(_pPuppeteer);
}
