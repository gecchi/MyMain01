#include "VvvMousePointer.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "VvvCaretaker.h"


using namespace GgafLib;
using namespace VVViewer;


VvvMousePointer::VvvMousePointer(const char* prm_name) :
        MousePointerActor(prm_name, "VvvMousePointer") {
    _class_name = "VvvMousePointer";
    pI_ = nullptr;

    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    ViewCollisionChecker* pChecker = getViewCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSquare(0, PX_C(16));
    setHitAble(true);
}

void VvvMousePointer::onCreateModel() {
}

void VvvMousePointer::initialize() {

//    pI_ = desireActor(GgafLib::DefaultMeshActor, "Guruguru", "Guruguru");
//    WorldCollisionChecker* pChecker = pI_->getWorldCollisionChecker();
//    pChecker->createCollisionArea(1);
//    pChecker->setColliSphere(0, PX_C(100));
//    pI_->setHitAble(true);
//    appendGroupChild(KIND_ACTOR, pI_);
}

void VvvMousePointer::onActive() {
}

void VvvMousePointer::processBehavior() {
    getUvFlipper()->behave();

    //D3DXVec3Unproject
//スクリーン座標 = [モデル座標][ワールド行列][ビュー行列][射影行列][ビューポート行列]
//    モデル座標 = [スクリーン座標][ビューポート行列]-1[射影行列]-1[ビュー行列]-1[ワールド行列]-1

    VvvCamera* pCam = pCARETAKER->getSpacetime()->getCamera();

    //モデル座標(0,0,0)
    D3DXMATRIX mat_world = D3DXMATRIX(
        1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    );

    //画面アスペクト：1.77865
    //FovX=1.5708 FovY=1.02436
    //カメラの位置(0,0,-68.3) dxcoord
    //_cameraZ_org=-68.3 dxcoord
    //_dep=15
    //_zn=0.1 dxcoord
    //_zf=(68.3*(15+1.0))=1092.8 dxcoord
    //カメラの表示距離範囲 [0.1 ~ 1092.8] dxcoord
    dxcoord zn = pCam->_zn;
    dxcoord zf = pCam->_zf;
    dxcoord cameraZ_org = pCam->_cameraZ_org;

    //深さデフォルトのZは
    dxcoord Z = RCNV(cameraZ_org, zf, 0.0, 0.0, 1.0);
    //_zf=(68.3*(15+1.0))=1092.8 dxcoord
    D3DXVECTOR3 pos = { (FLOAT)C_PX(_x), (FLOAT)C_PX(_y), Z };
    _TRACE_("befor pos=("<<pos.x<<","<<pos.y<<","<<pos.z<<")");
    D3DXVec3Unproject(
        &pos,         //D3DXVECTOR3 *pOut,              [in, out] 演算結果である D3DXVECTOR3 構造体へのポインタ。
        &pos,         //CONST D3DXVECTOR3 *pV,          [in] 処理の基になる D3DXVECTOR3 構造体へのポインタ。(スクリーン座標)
        &(pCam->_viewport),   //CONST D3DVIEWPORT9 *pViewport,  [in] ビューポートを表す D3DVIEWPORT9 構造体へのポインタ。
        &(pCam->_matProj),    //CONST D3DXMATRIX *pProjection,  [in] 射影行列を表す D3DXMATRIX 構造体へのポインタ。
        &(pCam->_matView),    //CONST D3DXMATRIX *pView,        [in] ビュー行列を表す D3DXMATRIX 構造体へのポインタ。
        &mat_world            //CONST D3DXMATRIX *pWorld        [in] ワールド行列を表す D3DXMATRIX 構造体へのポインタ。
    );
    _TRACE_("after DX_C(pos)=("<<DX_C(pos.x)<<","<<DX_C(pos.y)<<","<<DX_C(pos.z)<<")");
   // pI_->setPosition(DX_C(pos.x),DX_C(pos.y),DX_C(pos.z));
}

void VvvMousePointer::processJudgement() {
}

void VvvMousePointer::onHit(const GgafCore::Actor* prm_pOtherActor) {
    MousePointerActor::onHit(prm_pOtherActor);
}

void VvvMousePointer::onInactive() {
}

VvvMousePointer::~VvvMousePointer() {
}

