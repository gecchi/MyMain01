#include "stdafx.h"
#include "FormationAntiope001.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Antiope/EnemyAntiopeP.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Antiope/EnemyAntiopeN.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

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
    pDepoConnection_AntiopeP_ = connect_DepositoryManager("AntiopeP");
    pDepoConnection_AntiopeN_ = connect_DepositoryManager("AntiopeN");

}
void FormationAntiope001::initialize() {
}

void FormationAntiope001::onActive() {
    num_Antiope_ = RF_FormationAntiope001_Num(G_RANK);    //ï“ë‡êî
    cnt_Antiope_ = 0;
    interval_frames_ = RF_FormationAntiope001_LaunchInterval(G_RANK);  //ÉAÉâÉXÇÃä‘äu(frame)
}

void FormationAntiope001::processBehavior() {
    if (cnt_Antiope_ < num_Antiope_) {
        if (getActiveFrame() % interval_frames_ == 0) {
            MyShip* pMyShip = P_MYSHIP;
            coord renge = PX_C(1200);
            GgafDxCore::GgafDxGeoElem entry_pos(RND(pMyShip->_x - (renge*0.5), pMyShip->_x + (renge*1.5)),
                                                RND(pMyShip->_y - renge, pMyShip->_y + renge),
                                                RND(pMyShip->_z - renge, pMyShip->_z + renge) );

            GgafDxCore::GgafDxGeoElem twd_pos_p(RND(entry_pos.x - renge, entry_pos.x + renge),
                                                RND(entry_pos.y - renge, entry_pos.y + renge),
                                                RND(entry_pos.z - renge, entry_pos.z + renge) );

            float vX, vY, vZ;
            UTIL::getNormalizeVector(RND(entry_pos.x - renge, entry_pos.x + renge),
                                     RND(entry_pos.y - renge, entry_pos.y + renge),
                                     RND(entry_pos.z - renge, entry_pos.z + renge),
                                     vX, vY, vZ);
            coord veloMv = 4000;

            EnemyAntiopeP* pP = (EnemyAntiopeP*)pDepoConnection_AntiopeP_->peek()->dispatch();
            if (pP) {
                pP->positionAs(&entry_pos);
                pP->getKuroko()->setMvAngTwd(&twd_pos_p);
                pP->setRzFaceAng(pP->getKuroko()->_angRzMv);
                pP->setRyFaceAng(pP->getKuroko()->_angRyMv);
                pP->getKuroko()->stopMv();
                pP->mv_velo_twd_.set(vX*veloMv, vY*veloMv, vZ*veloMv);
            }

            EnemyAntiopeN* pN = (EnemyAntiopeN*)pDepoConnection_AntiopeN_->peek()->dispatch();
            if (pN) {
                pN->positionAs(&entry_pos);
                pN->getKuroko()->setMvAngTwd(&twd_pos_p);
                pN->getKuroko()->reverseMvAng(); //îΩì]
                pN->setRzFaceAng(pN->getKuroko()->_angRzMv);
                pN->setRyFaceAng(pN->getKuroko()->_angRyMv);
                pN->getKuroko()->stopMv();
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
