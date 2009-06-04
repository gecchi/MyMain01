#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGroundStar001::BackGroundStar001(const char* prm_name) :
    GgafDx9MeshActor(prm_name,
                     "X/hosiboshi2",
                     "X/BackGroundStarEffect",
                     "BackGroundStarTechnique",
                     NULL ) {

    _class_name = "BackGroundStar001";
    _X = 0; //äJénç¿ïW
    _Y = 0;
    _Z = 0;
}

void BackGroundStar001::initialize() {
    setBumpable(false);
}

void BackGroundStar001::processBehavior() {
}

void BackGroundStar001::processJudgement() {
}


BackGroundStar001::~BackGroundStar001() {
}
