#include "LabelSceneSymbol.h"

#include "jp/gecchi/VioletVreath/Config.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LabelSceneSymbol::LabelSceneSymbol(const char* prm_name) :
        FontBoardActor(prm_name, "SceneSymbol")
{
    _class_name = "LabelSceneSymbol";
    setAlign(ALIGN_CENTER, VALIGN_TOP);
    update(PX_C(CONFIG::GAME_BUFFER_WIDTH/2), 0, "Q");
}

void LabelSceneSymbol::onCreateModel() {
}

void LabelSceneSymbol::initialize() {
}

void LabelSceneSymbol::processBehavior() {
}

LabelSceneSymbol::~LabelSceneSymbol() {
}

