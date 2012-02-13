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
//        //�w�i�Ȃ̂Ŕw�ʂŕ`��
//        GgafDxUniverse::setDrawDepthMaxLevel(this);
//    }
//}

void GroundMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matView) �Ɏ��s���܂����B");
    GgafDxUtil::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

//    // Z�o�b�t�@�𖳌���
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//    // Z�o�b�t�@�������ݕs��
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�J�����OOFF
    _pMeshModel->draw(this);

//    // Z�o�b�t�@��L����
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
//    // Z�o�b�t�@�������݉�
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}



void GroundMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

GroundMeshActor::~GroundMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
