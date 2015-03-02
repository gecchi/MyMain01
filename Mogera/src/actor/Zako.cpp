#include "Zako.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "actor/Zakoko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;


Zako::Zako(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Zako") {
    _class_name = "Zako";
    pAFader_ = NEW GgafDxAlphaFader(this);
    useProgress(PROG_BANPEI);
    pKurokoLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    scatter_flg_ = false;
    delay_ = 0;
    pOs_ = nullptr;

    int n = 6;
    for (int t = 0; t < n; t++) {
        double rad_pos = PI*2.0*n / t;
        double z = cos(rad_pos);
        double y = sin(rad_pos);
        static coord r = PX_C(50);
        Zakoko* pZakoko = NEW Zakoko("Zakoko");
        addSubGroupAsFk(pZakoko, 0,  z*r,  y*r, 0, 0, 0);
        pZakoko->setMaterialColor(RCNV(0, n-1, t, 5, 1.0),
                                   RCNV(0, n-1, t, 1.0, 5),
                                  0.5);
    }
    is_head_ = false;
}

void Zako::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void Zako::initialize() {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
    pKuroko->setSpinAngVelo(D_ANG(2));
}

void Zako::onActive() {
    getProgress()->reset(PROG_INIT);
    if (is_head_) {
        std::string filename = XTOS(getName()) + ".dat";
        pOs_ = NEW std::ofstream(filename.c_str());
    }
}

void Zako::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }

        case PROG_SPLINE: {
            if (pProg->isJustChanged()) {
                getKuroko()->setMvAcce(0); //加速度がある場合は切っておく
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION, 1);
            }
            pKurokoLeader_->behave(); //スプライン移動を振る舞い

            if (scatter_flg_) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
                sayonara();
            }
            break;
        }
        default :
            break;
    }

    pAFader_->behave();
    getKuroko()->behave();
}

void Zako::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }

    if (pOs_) {
        (*pOs_) << _x <<"  "<< _y <<"   " <<_z<< std::endl;
    }
}

void Zako::onHit(GgafActor* prm_pOtherActor) {
}

void Zako::onInactive() {
    if (getBehaveingFrame() > 10) {
        //ZakoCoreに管理されている。初めはInactive()であるため。
        sayonara();
    }
}
void Zako::scatter() {
    //Formationから指示がある。
    scatter_flg_ = true;
}

Zako::~Zako() {

    if (pOs_) {
        (*pOs_).close();
    }

    GGAF_DELETE(pAFader_);
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
