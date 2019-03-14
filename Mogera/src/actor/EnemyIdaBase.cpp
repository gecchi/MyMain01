#include "EnemyIdaBase.h"

#include "EnemyIda.h"
#include "util/MgrUtil.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

using namespace GgafLib;
using namespace Mogera;

enum {
    PROG_INIT ,
    PROG_MOVE ,
    PROG_END,
};

EnemyIdaBase::EnemyIdaBase(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ida") {
    pConn_pSplManuf_ = connectToSplineManufactureManager("ParallelCurve");
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
    int n = 4;
    coord D = PX_C(20);
    for (int i = 0; i < n; i++) {
        EnemyIda* p1 = NEW EnemyIda("ida");
        appendGroupChildAsFk(p1, 0, D*(i + 1), 0, 0, 0, 0);

        EnemyIda* p2 = NEW EnemyIda("ida");
        appendGroupChildAsFk(p2, 0, -D*(i + 1), 0, 0, 0, 0);
    }
}

void EnemyIdaBase::initialize() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
}

void EnemyIdaBase::onActive() {
    setPosition(0, 0, 0);
    getProgress()->reset(PROG_INIT);
}

void EnemyIdaBase::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_MOVE: {
            if (pProg->hasJustChanged()) {
                pKurokoLeader_->start(RELATIVE_COORD);
                pKuroko->setMvVelo(PX_C(1));
            }
            pKurokoLeader_->behave();

            if (pKurokoLeader_->isFinished()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_END: {
            break;
        }
    }
    pKuroko->behave();
}

void EnemyIdaBase::processJudgement() {
}

void EnemyIdaBase::onInactive() {
}

EnemyIdaBase::~EnemyIdaBase() {
}


