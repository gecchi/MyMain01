#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundMeshActor::GroundMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9MeshActor(prm_name,
                     prm_model,
                     "GroundMeshEffect",
                     "GroundMeshTechnique",
                     NEW CollisionChecker(this) ) {

    _class_name = "GroundMeshActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometricScaler(this);

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
//        GgafDx9Universe::setDrawDepthMaxLevel(this);
//    }
//}

void GroundMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matView, &P_CAM->_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    GgafDx9Util::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

//    // Zバッファを無効に
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//    // Zバッファ書き込み不可
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリングOFF
    _pMeshModel->draw(this);

//    // Zバッファを有効に
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
//    // Zバッファ書き込み可
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}



void GroundMeshActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

GroundMeshActor::~GroundMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
