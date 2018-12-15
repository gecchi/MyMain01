#include "MpBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MpBar::MpBar(const char* prm_name)
      : FramedHorizontalBarActor(prm_name, "MpBar") {
    _class_name = "MpBar";
    getUvFlipper()->setActivePtn(5);
    getFrameUvFlipper()->remapPatternNoUv(8,
                                          0 , 1 , 2 ,
                                          4 ,     6 ,
                                          8 , 9 , 10  );
    setHeight(PX_C(16));
}

void MpBar::initialize() {

}

MpBar::~MpBar() {
}
