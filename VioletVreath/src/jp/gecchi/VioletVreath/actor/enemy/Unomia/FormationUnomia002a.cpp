#include "FormationUnomia002a.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia002a::FormationUnomia002a(const char* prm_name) : FormationUnomia002(prm_name) {
    _class_name = "FormationUnomia002a";
}
void FormationUnomia002a::onSummonUnomia(EnemyUnomia* pEnemyUnomia, int col) {
//    pEnemyUnomia->pVehicleLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X•ûŒü”{—¦
//                                        MyShip::lim_y_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_z_left_  //Z•ûŒü”{—¦
//                                    );
//    pEnemyUnomia->pVehicleLeader_->adjustCoordOffset(0, col*50*1000, col*50*1000);
//    pEnemyUnomia->setPosition(papCurveSrcConnection_[col]->peek()->pSp_->_Xbasepoint_[0], 0, 0);
}

FormationUnomia002a::~FormationUnomia002a() {
}
