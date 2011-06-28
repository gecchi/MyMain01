#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultUniverse::DefaultUniverse(const char* prm_name, GgafDx9Camera* prm_pCamera) : GgafDx9Universe(prm_name, prm_pCamera) {
    _class_name = "DefaultUniverse";
    //８分木作成
    _pLinearOctree = NEW LinearOctreeForActor(6);
    _pLinearOctree->setRootSpace(_X_goneLeft  ,_Y_goneBottom, _Z_goneNear ,
                                 _X_goneRight ,_Y_goneTop   , _Z_goneFar   );
    //画面左の領域は少ない
}


void DefaultUniverse::processFinal() {
//    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//        _TRACE_(" DefaultUniverse::processFinal() befor");
//        _pLinearOctree->putTree();
//    }

    _pLinearOctree->clearElem();

//    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//        _TRACE_(" DefaultUniverse::processFinal() _pLinearOctree->clearElem(); after");
//        _pLinearOctree->putTree();
//    }

//    //ルートシーンを更新
//    float x1,y1,z1,x2,y2,z2;
//    x1 = y1 = z1 = x2 = y2 = z2 = 0.0f;
//    D3DXVECTOR3* pVecNear;
//    D3DXVECTOR3* pVecFar;
//
//    for (int i = 0; i < 4; i++) {
//        pVecNear =  &(P_CAM->_vecNear[i]);
//        pVecFar  =  &(P_CAM->_vecFar[i]);
//
//
//        if (x1 > pVecNear->x) {
//            x1 = pVecNear->x;
//        }
//        if (y1 > pVecNear->y) {
//            y1 = pVecNear->y;
//        }
//        if (z1 > pVecNear->z) {
//            z1 = pVecNear->z;
//        }
//
//        if (x2 < pVecNear->x) {
//            x2 = pVecNear->x;
//        }
//        if (y2 < pVecNear->y) {
//            y2 = pVecNear->y;
//        }
//        if (z2 < pVecNear->z) {
//            z2 = pVecNear->z;
//        }
//
//        if (x1 > pVecFar->x) {
//            x1 = pVecFar->x;
//        }
//        if (y1 > pVecFar->y) {
//            y1 = pVecFar->y;
//        }
//        if (z1 > pVecFar->z) {
//            z1 = pVecFar->z;
//        }
//
//        if (x2 < pVecFar->x) {
//            x2 = pVecFar->x;
//        }
//        if (y2 < pVecFar->y) {
//            y2 = pVecFar->y;
//        }
//        if (z2 < pVecFar->z) {
//            z2 = pVecFar->z;
//        }
//    }
//
//
//    _pLinearOctree->setRootSpace(x1*1.3 * PX_UNIT * LEN_UNIT,
//                                 y1*1.3 * PX_UNIT * LEN_UNIT,
//                                 z1*1.3 * PX_UNIT * LEN_UNIT,
//                                 x2*1.3 * PX_UNIT * LEN_UNIT,
//                                 y2*1.3 * PX_UNIT * LEN_UNIT,
//                                 z2*1.3 * PX_UNIT * LEN_UNIT);
//    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//        _TRACE_("ROOT(x1,y1,z1,x2,y2,z2)=("<<(_pLinearOctree->_root_X1)<<","<<
//                                             (_pLinearOctree->_root_Y2)<<","<<
//                                             (_pLinearOctree->_root_Z2)<<","<<
//                                             (_pLinearOctree->_root_X2)<<","<<
//                                             (_pLinearOctree->_root_Y2)<<","<<
//                                             (_pLinearOctree->_root_Z2)<<")");
//    }


}

DefaultUniverse::~DefaultUniverse() {
#ifdef MY_DEBUG
    _pLinearOctree->putTree();
    ColliAABActor::release();
    ColliAAPrismActor::release();
    ColliSphereActor::release();
#endif
    DELETE_IMPOSSIBLE_NULL(_pLinearOctree);
}
