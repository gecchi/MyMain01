#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGroundStar001::BackGroundStar001(const char* prm_name) :
    GgafDx9MeshActor(prm_name,
                     "hoshiboshi2",
                     "BackGroundStarEffect",
                     "BackGroundStarTechnique",
                     NULL ) {

    _class_name = "BackGroundStar001";
    _X = 0; //ŠJŽnÀ•W
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

void BackGroundStar001::processDraw() {
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
    GgafDx9Core::GgafDx9MeshActor::processDraw();
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
}

BackGroundStar001::~BackGroundStar001() {
}
