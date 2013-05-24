#include "stdafx.h"
#include "FormationEunomia002a.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia002a::FormationEunomia002a(const char* prm_name) : FormationEunomia002(prm_name) {
    _class_name = "FormationEunomia002a";
}
void FormationEunomia002a::onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_front_, //X•ûŒü”{—¦
//                                        MyShip::lim_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_zleft_  //Z•ûŒü”{—¦
//                                    );
//    pEnemyEunomia->pKurokoLeader_->adjustCoordOffset(0, col*50*1000, col*50*1000);
//    pEnemyEunomia->locate(papSplLineConnection_[col]->peek()->pSp_->_Xbasepoint_[0], 0, 0);
}

FormationEunomia002a::~FormationEunomia002a() {
}
