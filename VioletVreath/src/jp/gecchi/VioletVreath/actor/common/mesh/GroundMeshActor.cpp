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
//        //�w�i�Ȃ̂Ŕw�ʂŕ`��
//        GgafDxUniverse::setDrawDepthMaxLevel(this);
//    }
//}

void GroundMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(pMeshEffect_->h_matView_, &P_CAM->matView_ );
//    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matView) �Ɏ��s���܂����B");
    UTIL::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

//    // Z�o�b�t�@�𖳌���
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//    // Z�o�b�t�@�������ݕs��
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�J�����OOFF
    _pMeshModel->draw(this);

//    // Z�o�b�t�@��L����
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
//    // Z�o�b�t�@�������݉�
//    GgafDxGod::pID3DDevice9_->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}



void GroundMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

GroundMeshActor::~GroundMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
