#include "stdafx.h"
#include "FormationEunomia002b.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia002b::FormationEunomia002b(const char* prm_name) : FormationEunomia002(prm_name) {
    _class_name = "FormationEunomia002b";
}

void FormationEunomia002b::onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_front_, //X�����{��
//                                       -1.0 * MyShip::lim_top_,   //Y�����{��
//                                        MyShip::lim_zleft_  //Z�����{��
//                                    );
//    pEnemyEunomia->locate(papSplLineConnection_[col]->peek()->pSp_->_Xbasepoint_[0], 0, 0);
}

FormationEunomia002b::~FormationEunomia002b() {
}
