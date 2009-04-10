#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TransformedActor::GgafDx9TransformedActor(const char* prm_name) : GgafDx9BaseActor(prm_name) {
    _class_name = "GgafDx9TransformedActor";
    _x = _y = _z = 0.0f;
    _paD3DMaterial9 = NULL;
    _fAlpha = 1.0;
}

void GgafDx9TransformedActor::processDrawPrior() {
    //TODO:—vŒŸ“¢
    if (_is_active_flg && !_was_hidden_flg && _can_live_flg) {
        if (getAlpha() < 1.0) {
            GgafDx9World::setDrawDepthLevel(
                            (int)(_z * MAX_DRAW_DEPTH_LEVEL),
                            this
                          );
        } else {
            GgafDx9World::setDrawDepthMaxLevel(this);
        }
    }
}

GgafDx9TransformedActor::~GgafDx9TransformedActor() {
}
