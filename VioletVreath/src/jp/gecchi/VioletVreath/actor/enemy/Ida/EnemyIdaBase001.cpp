#include "EnemyIdaBase001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
    useProgress(PROG_BANPEI);
}

void EnemyIdaBase001::initialize() {
    EnemyIdaBase::initialize();
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollPitchYawFaceAngVelo(D_ANG(2), D0ANG, D_ANG(0.4));
}

void EnemyIdaBase001::onActive() {
    EnemyIdaBase::onActive();
    getProgress()->reset(PROG_INIT);
}

void EnemyIdaBase001::processBehavior() {
    EnemyIdaBase::processBehavior();
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pKurokoLeader_->start(RELATIVE_COORD, 3);
            pProg->changeNext();
            break;
        }
        case PROG_MOVE: {
            pKurokoLeader_->behave();
            break;
        }
    }

    pKuroko->behave();
}

EnemyIdaBase001::~EnemyIdaBase001() {
    GGAF_DELETE(pKurokoLeader_);
    pConn_pSplManuf_->close();
}

