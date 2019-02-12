#include "Zako.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "actor/Zakoko.h"



using namespace GgafLib;
using namespace Mogera;

enum {
    PROG_INIT   ,
    PROG_SPLINE ,
    PROG_LEAVE ,
    PROG_BANPEI,
};

Zako::Zako(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Zako") {
    _class_name = "Zako";
    useProgress(PROG_BANPEI);
    pKurokoLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    pOs_ = nullptr;

    int n = 6;
    for (int t = 0; t < n; t++) {
        double rad_pos = ((PI*2.0)*t) / n;
        double z = cos(rad_pos);
        double y = sin(rad_pos);
        static coord r = PX_C(50);
        std::string name = "Zakoko("+XTOS(t)+")";
        Zakoko* pZakoko = NEW Zakoko(name.c_str());
        appendGroupChildAsFk(pZakoko, 0,  z*r,  y*r, 0, 0, 0);
        pZakoko->setMaterialColor(RCNV(0, n-1, t, 5, 1.0),
                                  RCNV(0, n-1, t, 1.0, 5),
                                  0.5);
    }
}

void Zako::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void Zako::initialize() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollFaceAngVelo(D_ANG(2));
    pKuroko->setMvVelo(PX_C(1));

    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(128));
}

void Zako::onActive() {
    getProgress()->reset(PROG_INIT);
    if (isFirst()) {
        std::string filename = XTOS(getName()) + ".dat";
        pOs_ = NEW std::ofstream(filename.c_str());
    }
}

void Zako::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
//    GgafCore::Progress* const pProg = getProgress();
//    switch (pProg->get()) {
//        case PROG_INIT: {
//            pProg->changeNext();
//            break;
//        }
//
//        case PROG_SPLINE: {
//            if (pProg->hasJustChanged()) {
//                getKuroko()->setMvAcce(0); //加速度がある場合は切っておく
//                pKurokoLeader_->start(RELATIVE_COORD_DIRECTION, 1);
//            }
//            pKurokoLeader_->behave(); //スプライン移動を振る舞い
//
//            if (pKurokoLeader_->isFinished()) {
//                pProg->changeNext();
//            }
//            break;
//        }
//
//        case PROG_LEAVE: {
//            if (pProg->hasJustChanged()) {
//                sayonara();
//            }
//            break;
//        }
//        default :
//            break;
//    }
//
    pKuroko->behave();
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
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
