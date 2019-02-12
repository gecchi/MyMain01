#include "VreathBar.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;

VreathBar::VreathBar(const char* prm_name)
      : FramedHorizontalBarActor(prm_name, "VreathBar") {
    _class_name = "VreathBar";
    getUvFlipper()->setActivePtn(5);
    getFrameUvFlipper()->remapPatternNoUv(8,
                                          0 , 1 , 2 ,
                                          4 ,     6 ,
                                          8 , 9 , 10  );
    setHeight(PX_C(16));
}

void VreathBar::initialize() {
}

VreathBar::~VreathBar() {
}

