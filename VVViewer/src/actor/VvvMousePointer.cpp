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

void VvvMousePointer::processBehaviorX2() {
    getUvFlipper()->behave();

    VvvCamera* pCam = pCARETAKER->getSpacetime()->getCamera();

    //モデル座標(0,0,0)
    D3DXMATRIX mat_world = D3DXMATRIX(
        1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    );

    //    画面アスペクト：1.33333
    //    FovX=1.5708 FovY=1.287
    //    カメラの位置(0,0,-40) dxcoord
    //    _cameraZ_org=-40 dxcoord
    //    _dep=15
    //    _zn=0.1 dxcoord
    //    _zf=(40*(15+1.0)-0.1)=639.9 dxcoord
    //    カメラの表示距離範囲 [0.1 ~ 639.9] dxcoord
    //    _viewport.X=0
    //    _viewport.Y=0
    //    _viewport.Width=800
    //    _viewport.Height=600
    //    _viewport.MinZ=0
    //    _viewport.MaxZ=1
    //
    //      inN.z(0.0)                    zt_rate ?                                  inF.z(1.0)
    //   0    _zn(0.1)                    zt                                          _zf(639.9)
    //   |       |                        |     |                                       |
    //---<-------+------------------------O-----+---------------------------------------+- - - - - -
    //   |<-_zn->|                        |     |0                                      |
    //   |<-------------_zf------------------------------------------------------------>|
    //   |<----------target_dep_d-------->|     |                                       |
    //   |<----  -cameraZ_org   --------------->|                                       |
    //   |<------------- -_cameraZ_org + (_dep* - -_cameraZ_org*_dep) -------------- -->|
    dxcoord zn = pCam->_zn;
    dxcoord zf = pCam->_zf;
    dxcoord cameraZ_org = pCam->_cameraZ_org;
    dxcoord dep = pCam->_dep;
    dxcoord target_dep_d = -cameraZ_org; //オブジェクトの距離（ここに実際の測った距離）
    //深さデフォルトのZは
    dxcoord zt_rate = RCNV(zn, zf, target_dep_d, 0.0, 1.0);
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

//    D3DXVECTOR3 in = D3DXVECTOR3( (FLOAT)C_PX(_x), (FLOAT)C_PX(_y), (FLOAT)zt_rate );
//    D3DXVECTOR3 out;
//    D3DXVec3Unproject(
//        &out,         //D3DXVECTOR3 *pOut,              [in, out] 演算結果である D3DXVECTOR3 構造体へのポインタ。
//        &in,         //CONST D3DXVECTOR3 *pV,          [in] 処理の基になる D3DXVECTOR3 構造体へのポインタ。(スクリーン座標)
//        &(pCam->_viewport),   //CONST D3DVIEWPORT9 *pViewport,  [in] ビューポートを表す D3DVIEWPORT9 構造体へのポインタ。
//        &(pCam->_matProj),    //CONST D3DXMATRIX *pProjection,  [in] 射影行列を表す D3DXMATRIX 構造体へのポインタ。
//        &(pCam->_matView),    //CONST D3DXMATRIX *pView,        [in] ビュー行列を表す D3DXMATRIX 構造体へのポインタ。
//        &mat_world            //CONST D3DXMATRIX *pWorld        [in] ワールド行列を表す D3DXMATRIX 構造体へのポインタ。
//    );

    //_TRACE_("after outN=("<<outN.x<<","<<outN.y<<","<<outN.z<<")");
    //_TRACE_("after outF=("<<outF.x<<","<<outF.y<<","<<outF.z<<")");
    dxcoord x = RCNV(0.0, 1.0, zt_rate, outN.x, outF.x);
    dxcoord y = RCNV(0.0, 1.0, zt_rate, outN.y, outF.y);
    dxcoord z = RCNV(0.0, 1.0, zt_rate, outN.z, outF.z);
   pI_->setPosition(DX_C(x),DX_C(y),DX_C(z));

//    pI_->setPosition(DX_C(out.x),DX_C(out.y),DX_C(out.z));
}
void VvvMousePointer::processBehaviorX() {
    VvvCamera* pCam = pCARETAKER->getSpacetime()->getCamera();

    const float MinZ = pCam->_viewport.MinZ;
    const float MaxZ = pCam->_viewport.MaxZ;

    dxcoord zn = pCam->_zn;
    dxcoord zf = pCam->_zf;
    dxcoord cameraZ_org = pCam->_cameraZ_org;
    dxcoord dep = pCam->_dep;
    dxcoord target_dep_d = -cameraZ_org; //オブジェクトの距離（ここに実際の測った距離）
    //深さデフォルトのZは
//    dxcoord zt = RCNV(0, -cameraZ_org * (dep + 1), target_dep_d, zn, zf);
    dxcoord zt_rate = RCNV(zn, zf, target_dep_d, MinZ, MaxZ);

    // _11,  _12,  _13,  _14,
    // _21,  _22,  _23,  _24,
    // _31,  _32,  _33,  _34,
    // _41,  _42,  _43,  _44

    D3DXMATRIX matScreen = D3DXMATRIX(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        C_PX(_x), C_PX(_y), MinZ, 1.0f,  //Near
        C_PX(_x), C_PX(_y), MaxZ, 1.0f   //Far
    );
    D3DXMATRIX matInvView;
    D3DXMatrixInverse(&matInvView, nullptr, &pCam->_matView);
    D3DXMATRIX out = matScreen * pCam->_matInvViewPort * pCam->_matInvProj * matInvView;
    const float near_W = out._34;
    const float far_W = out._44;
    dxcoord x = RCNV(MinZ, MaxZ, zt_rate, out._31 / near_W, out._41 / far_W);
    dxcoord y = RCNV(MinZ, MaxZ, zt_rate, out._32 / near_W, out._42 / far_W);
    dxcoord z = RCNV(MinZ, MaxZ, zt_rate, out._33 / near_W, out._43 / far_W);
    pI_->setPosition(DX_C(x), DX_C(y), DX_C(z));
}

void VvvMousePointer::processBehavior() {
    VvvCamera* pCam = pCARETAKER->getSpacetime()->getCamera();
    dxcoord target_dep_d = -(pCam->_cameraZ_org); //オブジェクトの距離（ここに実際の測った距離
    dxcoord zt_rate = RCNV_to_0_1(pCam->_zn, pCam->_zf, target_dep_d);
    D3DXMATRIX matScreen = D3DXMATRIX(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        C_PX(_x), C_PX(_y), 0, 1.0f,  //Near Z=0
        C_PX(_x), C_PX(_y), 1, 1.0f   //Far  Z=1
    );
//    D3DXMATRIX matInvView;
//    D3DXMatrixInverse(&matInvView, nullptr, &pCam->_matView);
//    D3DXMATRIX matWorldCoords = matScreen * pCam->_matInvViewPort * pCam->_matInvProj * matInvView;
    D3DXMATRIX matWorldCoords = matScreen * pCam->_matInvViewPort_Proj_View;

    //下記を計算最適化
    //    const float near_W = out._34;
    //    const float far_W = out._44;
    //    const float MinZ = pCam->_viewport.MinZ; // = 0
    //    const float MaxZ = pCam->_viewport.MaxZ; // = 1
    //    dxcoord x = RCNV(MinZ, MaxZ, zt_rate, out._31 / near_W, out._41 / far_W);
    //    dxcoord y = RCNV(MinZ, MaxZ, zt_rate, out._32 / near_W, out._42 / far_W);
    //    dxcoord z = RCNV(MinZ, MaxZ, zt_rate, out._33 / near_W, out._43 / far_W);

    const float near_W = matWorldCoords._34;
    const float far_W = matWorldCoords._44;
    const float W = (far_W*near_W);
    const float near_W_zt_rate = (near_W * zt_rate);
    dxcoord x = (near_W_zt_rate*matWorldCoords._41 - ((zt_rate - 1) * (far_W*matWorldCoords._31))) / W;
    dxcoord y = (near_W_zt_rate*matWorldCoords._42 - ((zt_rate - 1) * (far_W*matWorldCoords._32))) / W;
    dxcoord z = (near_W_zt_rate*matWorldCoords._43 - ((zt_rate - 1) * (far_W*matWorldCoords._33))) / W;
    pI_->setPosition(DX_C(x), DX_C(y), DX_C(z));
//    _TRACE_("pI=("<<DX_PX(x)<<","<<DX_PX(y)<<","<<DX_PX(z));
}

void VvvMousePointer::processJudgement() {
//    _TRACE_("dtop,dbottom="<<DX_PX(pI_->_dest_from_vppln_top)<<","<<DX_PX(pI_->_dest_from_vppln_bottom));
//    _TRACE_("dleft,dright="<<DX_PX(pI_->_dest_from_vppln_left)<<","<<DX_PX(pI_->_dest_from_vppln_right));
}

void VvvMousePointer::onHit(const GgafCore::Actor* prm_pOtherActor) {
    MousePointerActor::onHit(prm_pOtherActor);
}

void VvvMousePointer::onInactive() {
}

VvvMousePointer::~VvvMousePointer() {
}

