#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGroundStar::BackGroundStar(const char* prm_name) : GgafDx9GeometricActor(prm_name, NULL) {
    _class_name = "BackGroundStar";

    _papBackGroundStar001 = NEW BackGroundStar001*[4];
    _papBackGroundStar001[0] = NEW BackGroundStar001("star01");
    _papBackGroundStar001[1] = NEW BackGroundStar001("star02");
    _papBackGroundStar001[2] = NEW BackGroundStar001("star03");
    _papBackGroundStar001[3] = NEW BackGroundStar001("star04");

    inactivateImmediately();
}

void BackGroundStar::initialize() {
    _TRACE_("BackGroundStar::initialize()");

    for (int i = 0; i < 4; i++) {
        addSubLast(_papBackGroundStar001[i]);
    }

//    _X = 0;
//    _Y = 0;
//    _Z = 0;
//    for (int i = 0; i < 4; i++) {
//        _papBackGroundStar001[i]->setAlpha(0.5);
//    }
}

void BackGroundStar::processBehavior() {
    //フェードイン
//    if (0 < getBehaveingFrame() && getBehaveingFrame() <= 255) {
//        for (int i = 0; i < 4; i++) {
//            _papBackGroundStar001[i]->setAlpha(float(getBehaveingFrame() / 255.0));
//        }
//    }

    if (_X < -800000) {
        _X += 800000;
    } else {
        _X -= 5000;
    }
    _papBackGroundStar001[0]->_X = _X - 800000;
    _papBackGroundStar001[1]->_X = _X ;
    _papBackGroundStar001[2]->_X = _X + 800000;
    _papBackGroundStar001[3]->_X = _X + 1600000;
}

void BackGroundStar::processPreDraw() {
//    //本アクターはGgafDx9DrawableActorではないかつ、
//    //BackGroundStar001がツリーの子ではなくメンバーでないので、
//    //無理やり段階レンダリングに登録
//    for (int i = 0; i < 4; i++) {
//        GgafDx9Universe::setDrawDepthMaxLevel(_papBackGroundStar001[i]);
//    }
}

//void BackGroundStar::processDraw() {
//    for (int i = 0; i < 4; i++) {
//        _papBackGroundStar001[i]->processDraw();
//    }
//}

BackGroundStar::~BackGroundStar() {
    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[0]);
    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[1]);
    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[2]);
    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[3]);
    DELETEARR_IMPOSSIBLE_NULL(_papBackGroundStar001);
}
