#include "EnemyIdaBase001.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT ,
    PHASE_MOVE ,
    PHASE_BANPEI,
};

EnemyIdaBase001::EnemyIdaBase001(const char* prm_name) :
        EnemyIdaBase(prm_name) {

    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyIdaBase001");
    pVehicleLeader_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
}

void EnemyIdaBase001::initialize() {
    EnemyIdaBase::initialize();
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->linkFaceAngByMvAng(true);
    pLocoVehicle->setRollPitchYawFaceAngVelo(D_ANG(2), D0ANG, D_ANG(0.4));
}

void EnemyIdaBase001::onActive() {
    EnemyIdaBase::onActive();
    getPhase()->reset(PHASE_INIT);
}

void EnemyIdaBase001::processBehavior() {
    EnemyIdaBase::processBehavior();
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pVehicleLeader_->start(RELATIVE_COORD, 3);
            pPhase->changeNext();
            break;
        }
        case PHASE_MOVE: {
            pVehicleLeader_->behave();
            break;
        }
    }

    pLocoVehicle->behave();
}

EnemyIdaBase001::~EnemyIdaBase001() {
    GGAF_DELETE(pVehicleLeader_);
    pConn_pCurveManuf_->close();
}

