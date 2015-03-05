#include "TrialAndErrScene.h"

#include "scene/MgrUniverse/MgrWorld.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "actor/Zako.h"
#include "jp/ggaf/core/GgafFactory.h"
#include <actor/FormationZako001.h>

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";
    orderActorToFactory(999, FormationZako001, "FormationZako001");
}

void TrialAndErrScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //�}�E�X���W�̑��΍��W��0�ɂ��邽�߂Q��Ăяo��
}

void TrialAndErrScene::processBehavior() {
    if (getActiveFrame() == 120) {
        FormationZako001* p = (FormationZako001*)obtainActorFromFactory(999);
        bringDirector()->addSubGroup(p);
        p->position(0,0,0);
    }
}

TrialAndErrScene::~TrialAndErrScene() {
}
