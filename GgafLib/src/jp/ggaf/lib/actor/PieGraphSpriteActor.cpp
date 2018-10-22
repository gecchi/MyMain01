#include "jp/ggaf/lib/actor/PieGraphSpriteActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

PieGraphSpriteActor::PieGraphSpriteActor(const char* prm_name, const char* prm_model, Quantity<int, int>* prm_pFanQty)
      : DefaultRegularPolygonSpriteActor(prm_name, prm_model) {
    _class_name = "PieGraphSpriteActor";
    _pFanQty = prm_pFanQty;
    _is_new_Quantity = false;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

PieGraphSpriteActor::PieGraphSpriteActor(const char* prm_name, const char* prm_model)
      : DefaultRegularPolygonSpriteActor(prm_name, prm_model) {
    _class_name = "PieGraphSpriteActor";
    _pFanQty = NEW Quantity<int, int>();
    _is_new_Quantity = true;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

void PieGraphSpriteActor::linkQty(Quantity<int, int>* prm_pFanQty) {
    if (_pFanQty) {
        if (_is_new_Quantity) {
            GGAF_DELETE(_pFanQty);
        }
    }
    _pFanQty = prm_pFanQty;
    _is_new_Quantity = false;
}

void PieGraphSpriteActor::linkVariable(int* prm_pVariable) {
    _pFanQty->link(prm_pVariable);
}

void PieGraphSpriteActor::processDraw() {
    int fan_num = _pFanQty->getQty();
    if (fan_num == 0) { //I know float ==
        return;
    }
    setDrawFanNum(fan_num);
    DefaultRegularPolygonSpriteActor::processDraw();
}

PieGraphSpriteActor::~PieGraphSpriteActor() {
    if (_is_new_Quantity) {
        GGAF_DELETE(_pFanQty);
    }
}
