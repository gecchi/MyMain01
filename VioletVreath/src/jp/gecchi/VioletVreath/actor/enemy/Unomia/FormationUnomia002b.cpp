#include "FormationUnomia002b.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia002b::FormationUnomia002b(const char* prm_name) : FormationUnomia002(prm_name) {
    _class_name = "FormationUnomia002b";
}

void FormationUnomia002b::onSummonUnomia(EnemyUnomia* pEnemyUnomia, int col) {
//    pEnemyUnomia->pVehicleLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X•ûŒü”{—¦
//                                       -1.0 * MyShip::lim_y_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_z_left_  //Z•ûŒü”{—¦
//                                    );
//    pEnemyUnomia->setPosition(papCurveSrcConnection_[col]->peek()->pSp_->_Xbasepoint_[0], 0, 0);
}

FormationUnomia002b::~FormationUnomia002b() {
}
