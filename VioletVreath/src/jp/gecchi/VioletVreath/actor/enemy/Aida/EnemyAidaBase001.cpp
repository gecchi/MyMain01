#include "stdafx.h"
#include "EnemyAidaBase001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAidaBase001::EnemyAidaBase001(const char* prm_name) :
        EnemyAidaBase(prm_name) {

    pSplManufConnection_ = connectToSplineManufactureManager("EnemyAidaBase001");
    pKurokoLeader_ = pSplManufConnection_->peek()->createKurokoLeader(_pKurokoA);
    useProgress(PROG_MOVE);
}

void EnemyAidaBase001::initialize() {
    EnemyAidaBase::initialize();
    _pKurokoA->relateMvFaceAng(true);
    _pKurokoA->setFaceAngVelo(D_ANG(2), D_ANG(0.4), D0ANG );
}

void EnemyAidaBase001::onActive() {
    EnemyAidaBase::onActive();
    _pProg->reset(PROG_INIT);
}

void EnemyAidaBase001::processBehavior() {
    EnemyAidaBase::processBehavior();

    switch (_pProg->get()) {
        case PROG_INIT: {
            pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_COORD,3);
            _pProg->changeNext();
            break;
        }

        case PROG_MOVE: {
            break;
        }
    }

    pKurokoLeader_->behave();
    _pKurokoA->behave();
}

EnemyAidaBase001::~EnemyAidaBase001() {
    GGAF_DELETE(pKurokoLeader_);
    pSplManufConnection_->close();
}


