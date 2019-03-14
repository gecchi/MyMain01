#include "ParallelCurveTestScene.h"

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "actor/EnemyIda.h"
#include "actor/EnemyIdaBase.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"

using namespace GgafLib;
using namespace Mogera;

enum {
    PROG_INIT ,
    PROG_CALM ,
    PROG_WAIT ,
    PROG_BANPEI,
};

ParallelCurveTestScene::ParallelCurveTestScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "ParallelCurveTestScene";
    pTest_ = nullptr;
    requestActor(1234, EnemyIdaBase, "EnemyIdaBase");
}


void ParallelCurveTestScene::initialize() {
    GgafDx::Input::updateMouseState();
    GgafDx::Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void ParallelCurveTestScene::processBehavior() {

    if (getActiveFrame() == 100) {
        EnemyIdaBase* p = (EnemyIdaBase*)receiveActor(1234);
        bringSceneMediator()->appendGroupChild(p);
        p->setPosition(0, 0, 0);
    }
}


ParallelCurveTestScene::~ParallelCurveTestScene() {
}
