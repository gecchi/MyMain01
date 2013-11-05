#include "stdafx.h"
#include "EnemyIdaBase001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
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
    pKurokoLeader_ = pSplManufConnection_->peek()->createKurokoLeader(_pKurokoA);
    useProgress(PROG_BANPEI-1);
}

void EnemyIdaBase001::initialize() {
    EnemyIdaBase::initialize();
    _pKurokoA->relateFaceWithMvAng(true);
    _pKurokoA->setFaceAngVelo(D_ANG(2), D_ANG(0.4), D0ANG );
}

void EnemyIdaBase001::onActive() {
    EnemyIdaBase::onActive();
    _pProg->reset(PROG_INIT);
}

void EnemyIdaBase001::processBehavior() {
    EnemyIdaBase::processBehavior();

    switch (_pProg->get()) {
        case PROG_INIT: {
            pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_COORD, 3);
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

EnemyIdaBase001::~EnemyIdaBase001() {
    GGAF_DELETE(pKurokoLeader_);
    pSplManufConnection_->close();
}

