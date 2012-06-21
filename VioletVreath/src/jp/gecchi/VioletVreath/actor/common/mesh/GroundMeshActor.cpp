#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GroundMeshActor::GroundMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxMeshActor(prm_name,
                     prm_model,
                     "GroundMeshEffect",
                     "GroundMeshTechnique",
                     prm_pStat,
                     NEW CollisionChecker(this) ) {

    _class_name = "GroundMeshActor";
    offset_frames_ = 0;
    _pColliChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);

//    if (pMeshModel_->paVtxBuffer_org_[0].nx == 0 &&
//        pMeshModel_->paVtxBuffer_org_[0].ny == 0 &&
//        pMeshModel_->paVtxBuffer_org_[0].nz == 0)
//    {
//        strcpy(technique_, "GroundMeshTechnique2");
//    }
}

//void GroundMeshActor::processPreDraw() {
//    pNext_TheSameDrawDepthLevel_ = NULL;
//    if (is_active_flg_ && can_live_flg_) {
//        //背景なので背面で描画
//        GgafDxUniverse::setDrawDepthMaxLevel(this);
//    }
//}

void GroundMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(pMeshEffect_->h_matView_, &P_CAM->matView_ );
//    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    UTIL::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

//    // Zバッファを無効に
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//    // Zバッファ書き込み不可
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリングOFF
    _pMeshModel->draw(this);

//    // Zバッファを有効に
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
//    // Zバッファ書き込み可
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}



void GroundMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

GroundMeshActor::~GroundMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
