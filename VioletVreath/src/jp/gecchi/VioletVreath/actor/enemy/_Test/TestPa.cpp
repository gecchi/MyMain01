#include "TestPa.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestPa::TestPa(const char* prm_name)
      : TestEnemy(prm_name, "TestPa", STATUS(TestPa)) {
    _class_name = "TestPa";

    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSe->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestPa::onActive() {
    getStatus()->reset();
}

void TestPa::processBehavior() {
    getKuroko()->behave();
    //getSeTransmitter()->behave();
    dispStamina();
}

void TestPa::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestPa::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

TestPa::~TestPa() {
}
