#include "jp/ggaf/dx/actor/AniMeshActor.h"

#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/model/AniMeshModel.h"
#include "jp/ggaf/dx/effect/AniMeshEffect.h"
#include "jp/ggaf/dx/util/FrameWorldMatrix.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

DWORD AniMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
AniMeshActor::AniMeshActor(const char* prm_name,
                           const char* prm_model_id,
                           const char* prm_effect_id,
                           const char* prm_technique,
                           Checker* prm_pChecker) :

                               FigureActor(prm_name,
                                           prm_model_id,
                                           TYPE_ANIMESH_MODEL,
                                           prm_effect_id,
                                           TYPE_ANIMESH_EFFECT,
                                           prm_technique,
                                           prm_pChecker) ,
_stackWorldMat() {

    _obj_class |= Obj_GgafDx_AniMeshActor;
    _class_name = "AniMeshActor";
    _papAnimationSet = nullptr;
    _pAniMeshModel = (AniMeshModel*)_pModel;
    _pAniMeshEffect = (AniMeshEffect*)_pEffect;
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列

    ID3DXAnimationController* pAc_cloned = _pAniMeshModel->getCloneAnimationController();
    _pPuppeteer = NEW Puppeteer(pAc_cloned);
    //Frame
    _stackWorldMat._pModel_MapBornFrame_AnimationSetList = &(_pAniMeshModel->_mapBornFrame_AnimationSetList);

    FrameWorldMatrix* pFrameRoot = _pAniMeshModel->_pFrameRoot;
    _stackWorldMat.registerFrameTransformationMatrix(pFrameRoot);



}

void AniMeshActor::processDraw() {
    _pAniMeshModel->draw(this);
}

AniMeshActor::~AniMeshActor() {
    GGAF_DELETE(_pPuppeteer);
}
