#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGroundStar001::BackGroundStar001(const char* prm_name) :
    GgafDx9MeshActor(prm_name,
                     "hoshiboshi3",
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
    setAlpha(0.9);
}

void BackGroundStar001::processBehavior() {
}
void BackGroundStar001::processPreJudgement() {
        _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
        _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
        _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
}

void BackGroundStar001::processJudgement() {
}
void BackGroundStar001::processPreDraw() {
    GgafDx9Universe::setDrawDepthLevel(1,this);
}
void BackGroundStar001::processDraw() {
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    GgafDx9Core::GgafDx9MeshActor::processDraw();
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
}

BackGroundStar001::~BackGroundStar001() {
}
