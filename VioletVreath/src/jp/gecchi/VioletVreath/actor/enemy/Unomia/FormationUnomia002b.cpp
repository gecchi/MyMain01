#include "FormationUnomia002b.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia002b::FormationUnomia002b(const char* prm_name) : FormationUnomia002(prm_name) {
    _class_name = "FormationUnomia002b";
}

void FormationUnomia002b::onCallUpUnomia(EnemyUnomia* pEnemyUnomia, int col) {
//    pEnemyUnomia->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X�����{��
//                                       -1.0 * MyShip::lim_y_top_,   //Y�����{��
//                                        MyShip::lim_z_left_  //Z�����{��
//                                    );
//    pEnemyUnomia->locate(papSplLineConnection_[col]->peek()->pSp_->_Xbasepoint_[0], 0, 0);
}

FormationUnomia002b::~FormationUnomia002b() {
}
