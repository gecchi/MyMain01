#include "InnerTitleBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/Quantity.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

InnerTitleBar::InnerTitleBar(const char* prm_name)
      : CappedGraphBarActor(prm_name, "InnerTitleBar") {
    _class_name = "InnerTitleBar";
}

void InnerTitleBar::initialize() {
    setSpecialRenderDepthIndex(1); //•`‰æ‡˜‚ğÅ‘O–Ê•`‰æ‚É‹­§B
}
void InnerTitleBar::processBehavior() {
}
InnerTitleBar::~InnerTitleBar() {
}

