#include "AniTest.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/util/Input.h"

using namespace GgafLib;
using namespace Mogera;


AniTest::AniTest(const char* prm_name) :
        DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton") {
    _class_name = "AniTest";
}

void AniTest::onCreateModel() {
}

void AniTest::initialize() {
}

void AniTest::onActive() {
}

void AniTest::processBehavior() {
    if (GgafDx::Input::isPushedDownKey(DIK_0)) {
        _pPuppeteer->play(LEFT_HAND,
                            0,          //UINT   prm_performance_no,
                            -1,         //double prm_loopnum,
                            1.0,        //double prm_target_speed,
                            0,          //frame  prm_shift_speed_frames,
                            1.0,        //double prm_target_weight,
                            0    );     //frame  prm_shift_weight_frames

    }
    _pPuppeteer->behave();
}

void AniTest::processJudgement() {
}

void AniTest::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

void AniTest::onInactive() {
}

void AniTest::scatter() {
}

AniTest::~AniTest() {
}
