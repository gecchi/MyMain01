#include "stdafx.h"
#include "GraphBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/lib/util/AmountGraph.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/GraphBar.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GraphBar::GraphBar(const char* prm_name, const char* prm_model, AmountGraph* prm_pAmount)
      : DefaultBoardActor(prm_name, prm_model) {
    _class_name = "GraphBar";
    pAmount_ = prm_pAmount;
    org_width_ = _pBoardModel->_fSize_BoardModelWidthPx;
    rate_org_width_ = 1.0 / org_width_;
}


GraphBar::~GraphBar() {
}
