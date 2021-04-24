#include "EnemyIdaBase001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT ,
    PROG_MOVE ,
    PROG_BANPEI,
};

EnemyIdaBase001::EnemyIdaBase001(const char* prm_name) :
        EnemyIdaBase(prm_name) {

    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyIdaBase001");
    pDriverLeader_ = pConn_pCurveManuf_->peek()->createVecDriverLeader(getVecDriver());
}

void EnemyIdaBase001::initialize() {
    EnemyIdaBase::initialize();
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->linkFaceAngByMvAng(true);
    pVecDriver->setRollPitchYawFaceAngVelo(D_ANG(2), D0ANG, D_ANG(0.4));
}

void EnemyIdaBase001::onActive() {
    EnemyIdaBase::onActive();
    getProgress()->reset(PROG_INIT);
}

void EnemyIdaBase001::processBehavior() {
    EnemyIdaBase::processBehavior();
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pDriverLeader_->start(RELATIVE_COORD, 3);
            pProg->changeNext();
            break;
        }
        case PROG_MOVE: {
            pDriverLeader_->behave();
            break;
        }
    }

    pVecDriver->behave();
}

EnemyIdaBase001::~EnemyIdaBase001() {
    GGAF_DELETE(pDriverLeader_);
    pConn_pCurveManuf_->close();
}

