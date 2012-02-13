#include "stdafx.h"
using namespace std;
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
    _offset_frames = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);

//    if (_pMeshModel->_paVtxBuffer_org[0].nx == 0 &&
//        _pMeshModel->_paVtxBuffer_org[0].ny == 0 &&
//        _pMeshModel->_paVtxBuffer_org[0].nz == 0)
//    {
//        strcpy(_technique, "GroundMeshTechnique2");
//    }
}

//void GroundMeshActor::processPreDraw() {
//    _pNext_TheSameDrawDepthLevel = NULL;
//    if (_is_active_flg && _can_live_flg) {
//        //背景なので背面で描画
//        GgafDxUniverse::setDrawDepthMaxLevel(this);
//    }
//}

void GroundMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    GgafDxUtil::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

//    // Zバッファを無効に
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//    // Zバッファ書き込み不可
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリングOFF
    _pMeshModel->draw(this);

//    // Zバッファを有効に
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
//    // Zバッファ書き込み可
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}



void GroundMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

GroundMeshActor::~GroundMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
