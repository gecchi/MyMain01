#include "stdafx.h"
#include "EnemyIdaBase001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyIdaBase001::EnemyIdaBase001(const char* prm_name) :
        EnemyIdaBase(prm_name) {

    pSplManufConnection_ = connect_SplineManufactureManager("EnemyIdaBase001");
    pKurokoLeader_ = pSplManufConnection_->peek()->createKurokoLeader(getKuroko());
    useProgress(PROG_BANPEI);
}

void EnemyIdaBase001::initialize() {
    EnemyIdaBase::initialize();
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceWithMvAng(true);
    pKuroko->setFaceAngVelo(D_ANG(2), D_ANG(0.4), D0ANG );
}

void EnemyIdaBase001::onActive() {
    EnemyIdaBase::onActive();
    getProgress()->reset(PROG_INIT);
}

void EnemyIdaBase001::processBehavior() {
    EnemyIdaBase::processBehavior();
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_COORD, 3);
            pProg->changeNext();
            break;
        }
        case PROG_MOVE: {
            break;
        }
    }

    pKurokoLeader_->behave();
    pKuroko->behave();
}

EnemyIdaBase001::~EnemyIdaBase001() {
    GGAF_DELETE(pKurokoLeader_);
    pSplManufConnection_->close();
}

