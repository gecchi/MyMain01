#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TransformedActor::GgafDx9TransformedActor(const char* prm_name) : GgafDx9BaseActor(prm_name) {
    _class_name = "GgafDx9TransformedActor";
    _x = _y = _z = 0.0f;
    _paD3DMaterial9 = NULL;
}


void GgafDx9TransformedActor::processDrawPrior() {
    //TODO:óvåüèÿ
    if (_isActiveFlg && !_wasBlindedFlg && _isAliveFlg) {
        GgafDx9World::setDrawDepthLevel(
                        (int)(_z * MAX_DRAW_DEPTH_LEVEL),
                        this
                      );
    }
}
GgafDx9TransformedActor::~GgafDx9TransformedActor() {
}
