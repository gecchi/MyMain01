#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundMeshTestActor::GroundMeshTestActor(const char* prm_name) :
        GgafDx9MeshActor(prm_name,
                         "_chk_GroundMeshEffectTest",
                         "GroundMeshEffect",
                         "GroundMeshEffectTechnique",
                         NULL,
                         NULL) {

    _class_name = "GroundMeshTestActor";
    _offset_frames = 0;
    _pCollisionChecker = NULL;
    _pScaler = NEW GgafDx9Scaler(this);

//    if (_pMeshModel->_paVtxBuffer_org[0].nx == 0 &&
//        _pMeshModel->_paVtxBuffer_org[0].ny == 0 &&
//        _pMeshModel->_paVtxBuffer_org[0].nz == 0)
//    {
//        strcpy(_technique, "GroundMeshEffectTechnique2");
//    }
}

//void GroundMeshTestActor::processPreDraw() {
//    _pNext_TheSameDrawDepthLevel = NULL;
//    if (_is_active_flg && _can_live_flg) {
//        //背景なので背面で描画
//        GgafDx9Universe::setDrawDepthMaxLevel(this);
//    }
//}

void GroundMeshTestActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDx9MeshTestActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    GgafDx9Util::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9MeshTestActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリングOFF
    _pMeshModel->draw(this);


}



void GroundMeshTestActor::drawHitArea() {
}

GroundMeshTestActor::~GroundMeshTestActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
