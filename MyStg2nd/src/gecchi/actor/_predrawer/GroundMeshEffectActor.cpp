#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundMeshEffectActor::GroundMeshEffectActor(const char* prm_name) :
        GgafDx9MeshActor(prm_name,
                     "GroundMeshEffectTest",
                     "GroundMeshEffect",
                     "GroundMeshEffectTechnique",
                     NULL) {

    _class_name = "GroundMeshEffectActor";
    _frame_offset = 0;
    _pCollisionChecker = NULL;
    _pScaler = NEW GgafDx9Scaler(this);

//    if (_pMeshModel->_paVtxBuffer_org[0].nx == 0 &&
//        _pMeshModel->_paVtxBuffer_org[0].ny == 0 &&
//        _pMeshModel->_paVtxBuffer_org[0].nz == 0)
//    {
//        strcpy(_technique, "GroundMeshEffectTechnique2");
//    }
}

//void GroundMeshEffectActor::processPreDraw() {
//    _pNext_TheSameDrawDepthLevel = NULL;
//    if (_is_active_flg && _can_live_flg) {
//        //�w�i�Ȃ̂Ŕw�ʂŕ`��
//        GgafDx9Universe::setDrawDepthMaxLevel(this);
//    }
//}

void GroundMeshEffectActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matView, &P_CAM->_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9MeshEffectActor::processDraw() SetMatrix(g_matView) �Ɏ��s���܂����B");
    GgafDx9Util::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9MeshEffectActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�J�����OOFF
    _pMeshModel->draw(this);


}



void GroundMeshEffectActor::drawHitArea() {
}

GroundMeshEffectActor::~GroundMeshEffectActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
