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

    pI_ = desireActor(GgafLib::DefaultMeshActor, "Guruguru", "Guruguru");
    WorldCollisionChecker* pChecker = pI_->getWorldCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(100));
    pI_->setScaleR(3.0);
    pI_->setHitAble(true);
    appendGroupChild(KIND_ACTOR, pI_);
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
    dxcoord dep = pCam->_dep;

    //   0 _zn(0.1)                                                              _zf(1.0)
    //   | |                                                                      |
    //---<-+------------------------o---------------------------------------------+- - - - - -
    //   |                          |                                             |
    //  cameraZ_org                 |                                  -_cameraZ_org*_dep
    //   |<----------target_dep_d-->|

    dxcoord target_dep_d = -cameraZ_org; //オブジェクトの距離（ここに実際の測った距離）
    //深さデフォルトのZは
    dxcoord zt = RCNV(0, -cameraZ_org*(dep+1), target_dep_d, zn, zf);
    dxcoord zt_rate = RCNV(zn, zf, zt, 0.0, 1.0);
    D3DXVECTOR3 inN = D3DXVECTOR3( (FLOAT)C_PX(_x), (FLOAT)C_PX(_y), (FLOAT)0 );
    D3DXVECTOR3 inF = D3DXVECTOR3( (FLOAT)C_PX(_x), (FLOAT)C_PX(_y), (FLOAT)1 );
    D3DXVECTOR3 outN,  outF;
    //_TRACE_("befor inN=("<<inN.x<<","<<inN.y<<","<<inN.z<<")");
    //_TRACE_("befor inF=("<<inF.x<<","<<inF.y<<","<<inF.z<<")");
    D3DXVec3Unproject(
        &outN,         //D3DXVECTOR3 *pOut,              [in, out] 演算結果である D3DXVECTOR3 構造体へのポインタ。
        &inN,         //CONST D3DXVECTOR3 *pV,          [in] 処理の基になる D3DXVECTOR3 構造体へのポインタ。(スクリーン座標)
        &(pCam->_viewport),   //CONST D3DVIEWPORT9 *pViewport,  [in] ビューポートを表す D3DVIEWPORT9 構造体へのポインタ。
        &(pCam->_matProj),    //CONST D3DXMATRIX *pProjection,  [in] 射影行列を表す D3DXMATRIX 構造体へのポインタ。
        &(pCam->_matView),    //CONST D3DXMATRIX *pView,        [in] ビュー行列を表す D3DXMATRIX 構造体へのポインタ。
        &mat_world            //CONST D3DXMATRIX *pWorld        [in] ワールド行列を表す D3DXMATRIX 構造体へのポインタ。
    );
    D3DXVec3Unproject(
        &outF,         //D3DXVECTOR3 *pOut,              [in, out] 演算結果である D3DXVECTOR3 構造体へのポインタ。
        &inF,         //CONST D3DXVECTOR3 *pV,          [in] 処理の基になる D3DXVECTOR3 構造体へのポインタ。(スクリーン座標)
        &(pCam->_viewport),   //CONST D3DVIEWPORT9 *pViewport,  [in] ビューポートを表す D3DVIEWPORT9 構造体へのポインタ。
        &(pCam->_matProj),    //CONST D3DXMATRIX *pProjection,  [in] 射影行列を表す D3DXMATRIX 構造体へのポインタ。
        &(pCam->_matView),    //CONST D3DXMATRIX *pView,        [in] ビュー行列を表す D3DXMATRIX 構造体へのポインタ。
        &mat_world            //CONST D3DXMATRIX *pWorld        [in] ワールド行列を表す D3DXMATRIX 構造体へのポインタ。
    );
    //_TRACE_("after outN=("<<outN.x<<","<<outN.y<<","<<outN.z<<")");
    //_TRACE_("after outF=("<<outF.x<<","<<outF.y<<","<<outF.z<<")");
    dxcoord x = RCNV(0.0, 1.0, zt_rate, outN.x, outF.x);
    dxcoord y = RCNV(0.0, 1.0, zt_rate, outN.y, outF.y);
    dxcoord z = RCNV(0.0, 1.0, zt_rate, outN.z, outF.z);
   pI_->setPosition(DX_C(x),DX_C(y),DX_C(z));
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

