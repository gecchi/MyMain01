#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAntiope001::FormationAntiope001(const char* prm_name) :
        DefaultGeometricActor(prm_name, nullptr) {
    _class_name = "FormationAntiope001";
    num_Antiope_ = 0;
    cnt_Antiope_ = 0;
    interval_frames_ = 0;
    pDepoConnection_AntiopeP_ = connectToDepositoryManager("AntiopeP");
    pDepoConnection_AntiopeN_ = connectToDepositoryManager("AntiopeN");

}
void FormationAntiope001::initialize() {
}

void FormationAntiope001::onActive() {
    num_Antiope_ = RR_FormationAntiope001_Num(_RANK_);    //ï“ë‡êî
    cnt_Antiope_ = 0;
    interval_frames_ = RR_FormationAntiope001_LaunchInterval(_RANK_);  //ÉpÉâÉXÇÃä‘äu(frame)
}

void FormationAntiope001::processBehavior() {
    if (cnt_Antiope_ < num_Antiope_) {
        if (getActiveFrame() % interval_frames_ == 0) {
            MyShip* pMyShip = P_MYSHIP;
            coord renge = PX_C(1000);
            GgafDxCore::GgafDxGeoElem entry_pos(RND(pMyShip->_X - renge ,pMyShip->_X + renge),
                                                RND(pMyShip->_Y - renge ,pMyShip->_Y + renge),
                                                RND(pMyShip->_Z - renge ,pMyShip->_Z + renge) );

            GgafDxCore::GgafDxGeoElem twd_pos_p(RND(pMyShip->_X - renge ,pMyShip->_X + renge),
                                                RND(pMyShip->_Y - renge ,pMyShip->_Y + renge),
                                                RND(pMyShip->_Z - renge ,pMyShip->_Z + renge) );

            float vX, vY, vZ;
            UTIL::getNormalizeVector(RND(pMyShip->_X - renge ,pMyShip->_X + renge),
                                     RND(pMyShip->_Y - renge ,pMyShip->_Y + renge),
                                     RND(pMyShip->_Z - renge ,pMyShip->_Z + renge),
                                     vX, vY, vZ);
            coord veloMv = 3000;

            EnemyAntiopeP* pP = (EnemyAntiopeP*)pDepoConnection_AntiopeP_->peek()->dispatch();
            if (pP) {
                pP->locateAs(&entry_pos);
                pP->_pKurokoA->setMvAngTwd(&twd_pos_p);
                pP->_pKurokoA->setFaceAngByMvAng();
                pP->_pKurokoA->setMvVelo(0);
                pP->_pKurokoA->setMvAcce(0);
                pP->mv_velo_twd_.set(vX*veloMv, vY*veloMv, vZ*veloMv);
            }

            EnemyAntiopeN* pN = (EnemyAntiopeN*)pDepoConnection_AntiopeN_->peek()->dispatch();
            if (pN) {
                pN->locateAs(&entry_pos);
                pN->_pKurokoA->setMvAngTwd(&twd_pos_p);
                pN->_pKurokoA->reverseMvAng();
                pP->_pKurokoA->setFaceAngByMvAng();
                pN->_pKurokoA->setMvVelo(0);
                pN->_pKurokoA->setMvAcce(0);
                pN->mv_velo_twd_.set(vX*veloMv, vY*veloMv, vZ*veloMv);
            }
            cnt_Antiope_++;
        }
    } else {
        if (!wasDeclaredEnd()) {
            sayonara(1000);
        }
    }
}


FormationAntiope001::~FormationAntiope001() {
    pDepoConnection_AntiopeP_->close();
    pDepoConnection_AntiopeN_->close();
}
