#include "EnemyIdaBase.h"

#include "EnemyIda.h"
#include "util/MgrUtil.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "scene/MgrSpacetime/MgrWorld/ParallelCurveTestScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace Mogera;

enum {
    PROG_INIT ,
    PROG_MOVE ,
    PROG_END,
};

EnemyIdaBase::EnemyIdaBase(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ida") {
    pConn_pCurveManuf_ = connectToCurveManufactureManager("FormationZako001_STEP");
    pVehicleLeader_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
    pVehicleLeader_->_turn_smooth = true;
    std::string filename = XTOS(getName()) + ".dat";
    pOs_ = NEW std::ofstream(filename.c_str());
    setScaleR(0.5);
    int n = 3; //���s�Ȑ��̐�(base + n * 2)
    coord D = PX_C(20); //���s�Ȑ��̊Ԋu
    for (int i = 0; i < n; i++) {
        std::string name1 = "ParallelCurve_"+XTOS(i)+"_1";
        EnemyIda* p1 = NEW EnemyIda(name1.c_str());
        appendGroupChildAsFk(p1, 0, D*(i + 1), 0, 0, 0, 0);
        _list_child.addLast(p1, false);
        std::string name2 = "ParallelCurve_"+XTOS(i)+"_2";
        EnemyIda* p2 = NEW EnemyIda(name2.c_str());
        appendGroupChildAsFk(p2, 0, -D*(i + 1), 0, 0, 0, 0);
        _list_child.addLast(p2, false);
    }
    _list_child.createIndex();
}

void EnemyIdaBase::initialize() {
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    pVecVehicle->linkFaceAngByMvAng(true);
}

void EnemyIdaBase::onActive() {
    getProgress()->reset(PROG_INIT);
}

void EnemyIdaBase::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Progress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            //�C�x���g�҂�
            break;
        }
        case PROG_MOVE: {
            if (pProg->hasJustChanged()) {
                pVehicleLeader_->start(RELATIVE_COORD);
                getVecVehicle()->setMvVelo(PX_C(2));
            }
            pVehicleLeader_->behave();
            if (pVehicleLeader_->isFinished()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_END: {
            getVecVehicle()->stop();
            getVecVehicle()->stopTurningMvAng();
            break;
        }
    }
    pVecVehicle->behave();
}

void EnemyIdaBase::processJudgement() {
}


void EnemyIdaBase::onInactive() {
}

void EnemyIdaBase::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_START_MOVING) {
        _TRACE_(FUNC_NAME<<" EVENT_START_PLOT !!");
        GgafCore::Progress* pProg = getProgress();
        pProg->change(PROG_MOVE);
    }
}

EnemyIdaBase::~EnemyIdaBase() {
    pConn_pCurveManuf_->close();
    if (pOs_) {
        (*pOs_).close();
    }
}

