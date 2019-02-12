#include "jp/ggaf/lib/actor/FramedHorizontalBarActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/BoardEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/BoardModel.h"
#include "jp/ggaf/dx/util/Util.h"



using namespace GgafLib;

FramedHorizontalBarActor::FramedHorizontalBarActor(const char* prm_name, const char* prm_model, Quantity<int, coord>* prm_pQty)
      : DefaultFramedBoardActor(prm_name, prm_model)
{
    _class_name = "FramedHorizontalBarActor";
    _pQty = prm_pQty;
    _is_new_Quantity = false;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

FramedHorizontalBarActor::FramedHorizontalBarActor(const char* prm_name, const char* prm_model)
      : DefaultFramedBoardActor(prm_name, prm_model)
{
    _class_name = "FramedHorizontalBarActor";
    _pQty = NEW Quantity<int, coord>();
    _is_new_Quantity = true;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

void FramedHorizontalBarActor::processPreDraw() {
    coord bar_width = getCoordWidth();
    setWidth(bar_width);
    DefaultFramedBoardActor::processPreDraw();
}

FramedHorizontalBarActor::~FramedHorizontalBarActor() {
    if (_is_new_Quantity) {
        GGAF_DELETE(_pQty);
    }
}
