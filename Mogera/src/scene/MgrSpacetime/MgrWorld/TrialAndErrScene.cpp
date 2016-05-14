#include "TrialAndErrScene.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "actor/PointSpriteTest.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";
    pTest_ = nullptr;
    orderActorToFactory(999, PointSpriteTest, "PointSpriteTest");
}

void TrialAndErrScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //�}�E�X���W�̑��΍��W��0�ɂ��邽�߂Q��Ăяo��
}

void TrialAndErrScene::processBehavior() {

    if (getActiveFrame() == 120) {
        pTest_ = (PointSpriteTest*)obtainActorFromFactory(999);
        bringDirector()->addSubGroup(pTest_);
        pTest_->position(0,0,0);
    }

}

TrialAndErrScene::~TrialAndErrScene() {
}
