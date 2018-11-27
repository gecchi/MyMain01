#include "jp/ggaf/lib/actor/FramedHorizontalBarActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FramedHorizontalBarActor::FramedHorizontalBarActor(const char* prm_name, const char* prm_model, Quantity<int, pixcoord>* prm_pPxQty)
      : DefaultFramedBoardActor(prm_name, prm_model)
{
    _class_name = "FramedHorizontalBarActor";
    _pPxQty = prm_pPxQty;
    _is_new_Quantity = false;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

FramedHorizontalBarActor::FramedHorizontalBarActor(const char* prm_name, const char* prm_model)
      : DefaultFramedBoardActor(prm_name, prm_model)
{
    _class_name = "FramedHorizontalBarActor";
    _pPxQty = NEW Quantity<int, pixcoord>();
    _is_new_Quantity = true;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

void FramedHorizontalBarActor::linkQty(Quantity<int, pixcoord>* prm_pPxQty) {
    if (_pPxQty) {
        if (_is_new_Quantity) {
            GGAF_DELETE(_pPxQty);
        }
    }
    _pPxQty = prm_pPxQty;
    _is_new_Quantity = false;
}

void FramedHorizontalBarActor::linkVariable(int* prm_pVariable) {
    _pPxQty->link(prm_pVariable);
}

void FramedHorizontalBarActor::processPreDraw() {
    pixcoord bar_width = getPix();
    setWidth(PX_C(bar_width));
    DefaultFramedBoardActor::processPreDraw();
}

FramedHorizontalBarActor::~FramedHorizontalBarActor() {
    if (_is_new_Quantity) {
        GGAF_DELETE(_pPxQty);
    }
}
