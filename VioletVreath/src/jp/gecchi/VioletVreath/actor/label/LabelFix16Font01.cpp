#include "LabelFix16Font01.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LabelFix16Font01::LabelFix16Font01(const char* prm_name) :
        FixedFontBoardActor(prm_name, "MSX_16Font")
{
    _class_name = "LabelFix16Font01";
    _pAFader = NEW GgafDxAlphaFader(this);
}

void LabelFix16Font01::onCreateModel() {
}

void LabelFix16Font01::initialize() {
}

void LabelFix16Font01::processBehavior() {
    _pAFader->behave();
}

LabelFix16Font01::~LabelFix16Font01() {
    GGAF_DELETE(_pAFader);
}

