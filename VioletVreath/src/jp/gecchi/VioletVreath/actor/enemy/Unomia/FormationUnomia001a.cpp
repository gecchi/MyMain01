#include "FormationUnomia001a.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/EnemyUnomia.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia001a::FormationUnomia001a(const char* prm_name) : FormationUnomia001(prm_name) {
    _class_name = "FormationUnomia001a";
}
void FormationUnomia001a::onCallUpUnomia(EnemyUnomia* pEnemyUnomia, int col) {
//    pEnemyUnomia->pDriverLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X�����{��
//                                        MyShip::lim_y_top_,   //Y�����{��
//                                        MyShip::lim_z_left_  //Z�����{��
//                                    );
    pEnemyUnomia->pDriverLeader_->adjustCoordOffset(PX_C(0), PX_C(col*50), PX_C(col*50));
    pEnemyUnomia->pDriverLeader_->setAbsoluteBeginCoord();
}

FormationUnomia001a::~FormationUnomia001a() {
}
