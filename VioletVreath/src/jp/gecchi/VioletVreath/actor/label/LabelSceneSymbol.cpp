#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LabelSceneSymbol::LabelSceneSymbol(const char* prm_name) :
        StringBoardActor(prm_name, "SceneSymbol")
{
    _class_name = "LabelSceneSymbol";
    setAlign(ALIGN_CENTER, VALIGN_TOP);
    update(PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2), 0, "Q");
}

void LabelSceneSymbol::onCreateModel() {
}

void LabelSceneSymbol::initialize() {
}

void LabelSceneSymbol::processBehavior() {
}

LabelSceneSymbol::~LabelSceneSymbol() {
}

