#include "FormationAntiope001.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
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
    pConn_depo_pAntiopeP_ = connectToDepositoryManager("AntiopeP");
    pConn_depo_pAntiopeN_ = connectToDepositoryManager("AntiopeN");
}

void FormationAntiope001::initialize() {
}

void FormationAntiope001::onActive() {
    num_Antiope_ = RF_FormationAntiope001_Num(G_RANK);    //�ґ���
    cnt_Antiope_ = 0;
    interval_frames_ = RF_FormationAntiope001_LaunchInterval(G_RANK);  //�o���Ԋu(frame)
}

void FormationAntiope001::processBehavior() {
    if (cnt_Antiope_ < num_Antiope_) {
        if (getActiveFrame() % interval_frames_ == 0) {
            MyShip* pMyShip = P_MYSHIP;
            coord renge = PX_C(1200);
            GgafDxCore::GgafDxGeoElem entry_pos(RND(pMyShip->_x - (renge*0.5), pMyShip->_x + (renge*1.5)),
                                                RND_ABOUT(pMyShip->_y, renge),
                                                RND_ABOUT(pMyShip->_z, renge) );

            GgafDxCore::GgafDxGeoElem twd_pos_p(RND_ABOUT(entry_pos.x, renge),
                                                RND_ABOUT(entry_pos.y, renge),
                                                RND_ABOUT(entry_pos.z, renge) );

            float vX, vY, vZ;
            UTIL::getNormalizedVector(RND_ABOUT(entry_pos.x, renge),
                                     RND_ABOUT(entry_pos.y, renge),
                                     RND_ABOUT(entry_pos.z, renge),
                                     vX, vY, vZ);
            coord veloMv = 4000;

            EnemyAntiopeP* pP = (EnemyAntiopeP*)pConn_depo_pAntiopeP_->peek()->dispatch();
            EnemyAntiopeN* pN = nullptr;
            if (pP) {
                pN = (EnemyAntiopeN*)pConn_depo_pAntiopeN_->peek()->dispatch();
            }

            if (pP && pN) {
                pP->placeAs(&entry_pos);
                pP->getKuroko()->setMvAngTwd(&twd_pos_p);
                pP->setRzFaceAng(pP->getKuroko()->_rz_mv);
                pP->setRyFaceAng(pP->getKuroko()->_ry_mv);
                pP->getKuroko()->stopMv();
                pP->mv_velo_twd_.set(vX*veloMv, vY*veloMv, vZ*veloMv);

                pN->placeAs(&entry_pos);
                pN->getKuroko()->setMvAngTwd(&twd_pos_p);
                pN->getKuroko()->reverseMvAng(); //���]
                pN->setRzFaceAng(pN->getKuroko()->_rz_mv);
                pN->setRyFaceAng(pN->getKuroko()->_ry_mv);
                pN->getKuroko()->stopMv();
                pN->mv_velo_twd_.set(vX*veloMv, vY*veloMv, vZ*veloMv);

                //�y�A�����O
                pP->pP_ = pN;
                pN->pP_ = pP;
                cnt_Antiope_++;
            } else {
                if (pP) {
                    pP->pP_ = nullptr;
                    pP->sayonara();
                }
                if (pN) {
                    pN->pP_ = nullptr;
                    pN->sayonara();
                }
            }


        }
    } else {
        if (!wasDeclaredEnd()) {
            sayonara(1000);
        }
    }
}

FormationAntiope001::~FormationAntiope001() {
    pConn_depo_pAntiopeP_->close();
    pConn_depo_pAntiopeN_->close();
}
