#include "EnemyIdaBase001.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
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
    pVehicleLeader_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
}

void EnemyIdaBase001::initialize() {
    EnemyIdaBase::initialize();
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    pVecVehicle->linkFaceAngByMvAng(true);
    pVecVehicle->setRollPitchYawFaceAngVelo(D_ANG(2), D0ANG, D_ANG(0.4));
}

void EnemyIdaBase001::onActive() {
    EnemyIdaBase::onActive();
    getProgress()->reset(PROG_INIT);
}

void EnemyIdaBase001::processBehavior() {
    EnemyIdaBase::processBehavior();
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pVehicleLeader_->start(RELATIVE_COORD, 3);
            pProg->changeNext();
            break;
        }
        case PROG_MOVE: {
            pVehicleLeader_->behave();
            break;
        }
    }

    pVecVehicle->behave();
}

EnemyIdaBase001::~EnemyIdaBase001() {
    GGAF_DELETE(pVehicleLeader_);
    pConn_pCurveManuf_->close();
}

