#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultUniverse::DefaultUniverse(const char* prm_name) : GgafDx9Universe(prm_name) {
    _class_name = "DefaultUniverse";
    _pLinearOctree = NEW LinearOctreeForActor(6);
    _pLinearOctree->setRootSpace(-8000000 ,-8000000 ,-8000000 ,8000000 ,8000000 ,8000000);
//
//
//    GgafLinearOctree<GgafDx9GeometricActor>* pLinearOctree =
//            NEW GgafLinearOctree<GgafDx9GeometricActor>
//                (
//                    5,
//                    -8000000 ,-8000000 ,-8000000 ,8000000 ,8000000 ,8000000
//                );
//    GgafLinearOctree<GgafDx9GeometricActor>::Elem* pElem = NEW GgafLinearOctree<GgafDx9GeometricActor>::Elem(this);
//    pLinearOctree->registElem(pElem, 1000,1000,1000,1500,1500,1500);
//
//    _TRACE_("----------------------------------------------------------------八分木")
//    pLinearOctree->putTree();
}

void DefaultUniverse::nextFrame() {
    GgafDx9Core::GgafDx9Universe::nextFrame();
}


void DefaultUniverse::processFinal() {
    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
        _pLinearOctree->putTree();
    }
    _pLinearOctree->clearElem();


    //ルートシーンを更新
    float x1,y1,z1,x2,y2,z2;
    x1 = y1 = z1 = x2 = y2 = z2 = 0.0f;
    D3DXVECTOR3* pVecNear;
    D3DXVECTOR3* pVecFar;

    for (int i = 0; i < 4; i++) {
        pVecNear =  &(pCAM->_vecNear[i]);
        pVecFar  =  &(pCAM->_vecFar[i]);


        if (x1 > pVecNear->x) {
            x1 = pVecNear->x;
        }
        if (y1 > pVecNear->y) {
            y1 = pVecNear->y;
        }
        if (z1 > pVecNear->z) {
            z1 = pVecNear->z;
        }

        if (x2 < pVecNear->x) {
            x2 = pVecNear->x;
        }
        if (y2 < pVecNear->y) {
            y2 = pVecNear->y;
        }
        if (z2 < pVecNear->z) {
            z2 = pVecNear->z;
        }

        if (x1 > pVecFar->x) {
            x1 = pVecFar->x;
        }
        if (y1 > pVecFar->y) {
            y1 = pVecFar->y;
        }
        if (z1 > pVecFar->z) {
            z1 = pVecFar->z;
        }

        if (x2 < pVecFar->x) {
            x2 = pVecFar->x;
        }
        if (y2 < pVecFar->y) {
            y2 = pVecFar->y;
        }
        if (z2 < pVecFar->z) {
            z2 = pVecFar->z;
        }
    }


    _pLinearOctree->setRootSpace(x1 * PX_UNIT * LEN_UNIT,
                                 y1 * PX_UNIT * LEN_UNIT,
                                 z1 * PX_UNIT * LEN_UNIT,
                                 x2 * PX_UNIT * LEN_UNIT,
                                 y2 * PX_UNIT * LEN_UNIT,
                                 z2 * PX_UNIT * LEN_UNIT);
    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
        _TRACE_("(x1,y1,z1,x2,y2,z2)=("<<(x1 * PX_UNIT * LEN_UNIT)<<","<<
                                         (y1 * PX_UNIT * LEN_UNIT)<<","<<
                                         (z1 * PX_UNIT * LEN_UNIT)<<","<<
                                         (x2 * PX_UNIT * LEN_UNIT)<<","<<
                                         (y2 * PX_UNIT * LEN_UNIT)<<","<<
                                         (z2 * PX_UNIT * LEN_UNIT)<<")");
    }


}

DefaultUniverse::~DefaultUniverse() {
    _pLinearOctree->putTree();
    DELETE_IMPOSSIBLE_NULL(_pLinearOctree);

}
