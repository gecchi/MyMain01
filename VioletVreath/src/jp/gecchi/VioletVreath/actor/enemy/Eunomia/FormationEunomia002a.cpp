#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia002a::FormationEunomia002a(const char* prm_name) : FormationEunomia002(prm_name) {
    _class_name = "FormationEunomia002a";
}
void FormationEunomia002a::processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->pSplSeq_->adjustAxisRate(
//                                        MyShip::lim_front_, //X�����{��
//                                        MyShip::lim_top_,   //Y�����{��
//                                        MyShip::lim_zleft_  //Z�����{��
//                                    );
//    pEnemyEunomia->pSplSeq_->adjustCoodOffset(0, col*50*1000, col*50*1000);
//    pEnemyEunomia->locate(papSplLineCon_[col]->use()->pSp_->_Xbasepoint_[0], 0, 0);
}

FormationEunomia002a::~FormationEunomia002a() {
}