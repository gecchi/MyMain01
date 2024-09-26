#include "Zako.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "actor/Zakoko.h"



using namespace GgafLib;
using namespace Mogera;

enum {
    PHASE_INIT   ,
    PHASE_CURVE ,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};

Zako::Zako(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Zako") {
    _class_name = "Zako";
    pVehicleLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    pOs_ = nullptr;

    int n = 6;
    for (int t = 0; t < n; t++) {
        double rad_pos = ((PI*2.0)*t) / n;
        double z = cos(rad_pos);
        double y = sin(rad_pos);
        static coord r = PX_C(50);
        std::string name = "Zakoko("+XTOS(t)+")";
        Zakoko* pZakoko = NEW Zakoko(name.c_str());
        appendChildAsFk(pZakoko, 0,  z*r,  y*r, 0, 0, 0);
        pZakoko->setMaterialColor(RCNV(0, n-1, t, 5, 1.0),
                                  RCNV(0, n-1, t, 1.0, 5),
                                  0.5);
    }
}

void Zako::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void Zako::initialize() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setRollFaceAngVelo(D_ANG(2));
    pLocusVehicle->setMvVelo(PX_C(1));

    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(128));
}

void Zako::onActive() {
    getPhase()->reset(PHASE_INIT);
    if (isFirst()) {
        std::string filename = XTOS(getName()) + ".dat";
        pOs_ = NEW std::ofstream(filename.c_str());
    }
}

void Zako::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
//    GgafCore::Phase* pPhase = getPhase();
//    switch (pPhase->getCurrent()) {
//        case PHASE_INIT: {
//            pPhase->changeNext();
//            break;
//        }
//
//        case PHASE_CURVE: {
//            if (pPhase->hasJustChanged()) {
//                getLocusVehicle()->setMvAcce(0); //加速度がある場合は切っておく
//                pVehicleLeader_->start(RELATIVE_COORD_DIRECTION, 1);
//            }
//            pVehicleLeader_->behave(); //カーブ移動するようにDriverを操作
//
//            if (pVehicleLeader_->isFinished()) {
//                pPhase->changeNext();
//            }
//            break;
//        }
//
//        case PHASE_LEAVE: {
//            if (pPhase->hasJustChanged()) {
//                sayonara();
//            }
//            break;
//        }
//        default :
//            break;
//    }
//
    pLocusVehicle->behave();
}

void Zako::processJudgement() {
//    if (pOs_) {
//        (*pOs_) << _x << "  " << _y << "  " << _z << std::endl;
//    }
}

void Zako::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

void Zako::onInactive() {
}

Zako::~Zako() {
    if (pOs_) {
        (*pOs_).close();
    }
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
