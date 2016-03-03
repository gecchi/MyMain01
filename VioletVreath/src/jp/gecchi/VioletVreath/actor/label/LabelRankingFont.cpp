#include "LabelRankingFont.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LabelRankingFont::LabelRankingFont(const char* prm_name) :
        FontBoardActor(prm_name, "Ranking_16Font")
{
    _class_name = "LabelRankingFont";
    pAFader_ = NEW GgafDxAlphaFader(this);
}

void LabelRankingFont::onCreateModel() {
}

void LabelRankingFont::initialize() {
}

void LabelRankingFont::processBehavior() {
}

LabelRankingFont::~LabelRankingFont() {
    GGAF_DELETE(pAFader_);
}

