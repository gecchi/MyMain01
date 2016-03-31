#include "BoardTest.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "actor/BoardTest.h"

#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;


BoardTest::BoardTest(const char* prm_name) :
        FontSpriteActor(prm_name, "BoardTest") {
    _class_name = "BoardTest";

    pAFader_ = NEW GgafDxAlphaFader(this);
}

void BoardTest::onCreateModel() {
}

void BoardTest::initialize() {
}

void BoardTest::onActive() {
}

void BoardTest::processBehavior() {
    addRzFaceAng(1000);
    pAFader_->behave();
}

void BoardTest::processJudgement() {
}

void BoardTest::onHit(const GgafActor* prm_pOtherActor) {
}

void BoardTest::onInactive() {
}

BoardTest::~BoardTest() {
    GGAF_DELETE(pAFader_);
}
