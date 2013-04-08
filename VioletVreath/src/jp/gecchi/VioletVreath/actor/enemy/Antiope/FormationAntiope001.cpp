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

            coord renge = PX_C(1000);
            GgafDxCore::GgafDxGeoElem entry_pos(RND(P_MYSHIP->_X - renge ,P_MYSHIP->_X + renge),
                                                RND(P_MYSHIP->_Y - renge ,P_MYSHIP->_Y + renge),
                                                RND(P_MYSHIP->_Z - renge ,P_MYSHIP->_Z + renge) );

            GgafDxCore::GgafDxGeoElem twd_pos_p(RND(P_MYSHIP->_X - renge ,P_MYSHIP->_X + renge),
                                                RND(P_MYSHIP->_Y - renge ,P_MYSHIP->_Y + renge),
                                                RND(P_MYSHIP->_Z - renge ,P_MYSHIP->_Z + renge) );

            GgafDxCore::GgafDxGeoElem twd_pos_n(entry_pos._X - twd_pos_p._X,
                                                entry_pos._Y - twd_pos_p._Y,
                                                entry_pos._Z - twd_pos_p._Z );

            EnemyAntiopeP* pP = (EnemyAntiopeP*)pDepoConnection_AntiopeP_->peek()->dispatch();
            if (pP) {
                pP->locateWith(&entry_pos);
                pP->_pKurokoA->setMvAngTwd(&twd_pos_p);
                pP->_pKurokoA->setMvVelo(0);
                pP->_pKurokoA->setMvAcce(0);
            }

            EnemyAntiopeN* pN = (EnemyAntiopeN*)pDepoConnection_AntiopeN_->peek()->dispatch();
            if (pN) {
                pN->locateWith(&entry_pos);
                pN->_pKurokoA->setMvAngTwd(&twd_pos_n);
                pN->_pKurokoA->setMvVelo(0);
                pN->_pKurokoA->setMvAcce(0);
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
