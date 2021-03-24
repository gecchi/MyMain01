#include "EnemyIdaBase001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"
#include "jp/ggaf/dx/manager/SplineManufactureConnection.h"
#include "jp/ggaf/dx/util/spline/SplineManufacture.h"

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

    pConn_pSplManuf_ = connectToSplineManufactureManager("EnemyIdaBase001");
    pVecDriverLeader_ = pConn_pSplManuf_->peek()->createVecDriverLeader(callVecDriver());
}

void EnemyIdaBase001::initialize() {
    EnemyIdaBase::initialize();
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    pVecDriver->linkFaceAngByMvAng(true);
    pVecDriver->setRollPitchYawFaceAngVelo(D_ANG(2), D0ANG, D_ANG(0.4));
}

void EnemyIdaBase001::onActive() {
    EnemyIdaBase::onActive();
    getProgress()->reset(PROG_INIT);
}

void EnemyIdaBase001::processBehavior() {
    EnemyIdaBase::processBehavior();
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pVecDriverLeader_->start(RELATIVE_COORD, 3);
            pProg->changeNext();
            break;
        }
        case PROG_MOVE: {
            pVecDriverLeader_->behave();
            break;
        }
    }

    pVecDriver->behave();
}

EnemyIdaBase001::~EnemyIdaBase001() {
    GGAF_DELETE(pVecDriverLeader_);
    pConn_pSplManuf_->close();
}

