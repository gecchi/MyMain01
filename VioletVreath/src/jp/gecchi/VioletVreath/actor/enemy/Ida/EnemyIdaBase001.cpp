#include "EnemyIdaBase001.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"



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
    pRikishaLeader_ = pConn_pSplManuf_->peek()->createRikishaLeader(callRikisha());
}

void EnemyIdaBase001::initialize() {
    EnemyIdaBase::initialize();
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->linkFaceAngByMvAng(true);
    pRikisha->setRollPitchYawFaceAngVelo(D_ANG(2), D0ANG, D_ANG(0.4));
}

void EnemyIdaBase001::onActive() {
    EnemyIdaBase::onActive();
    getProgress()->reset(PROG_INIT);
}

void EnemyIdaBase001::processBehavior() {
    EnemyIdaBase::processBehavior();
    GgafDx::Rikisha* const pRikisha = callRikisha();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pRikishaLeader_->start(RELATIVE_COORD, 3);
            pProg->changeNext();
            break;
        }
        case PROG_MOVE: {
            pRikishaLeader_->behave();
            break;
        }
    }

    pRikisha->behave();
}

EnemyIdaBase001::~EnemyIdaBase001() {
    GGAF_DELETE(pRikishaLeader_);
    pConn_pSplManuf_->close();
}

