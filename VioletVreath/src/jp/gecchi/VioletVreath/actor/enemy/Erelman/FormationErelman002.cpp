#include "FormationErelman002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/EnemyErelman.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/core/util/GgafXpm.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationErelman002::FormationErelman002(const char* prm_name, EnemyErelmanController* prm_pController) :
        FormationErelman(prm_name, "FormationErelman002_Xpm", 7, prm_pController) {
    _class_name = "FormationErelman002";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationColNum()];
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col] = connectToSplineManufactureManager(("FormationErelman002/"+XTOS(col)).c_str());
    }
}

void FormationErelman002::processBehavior() {
    FormationErelman::processBehavior();
//    int col_num = getFormationColNum();
//    for (int col = 0; col < col_num; col++) {
//        SplineLine* sp = papSplManufConn_[col]->peek()->_sp;
//        sp->rotation(geo_.rx, geo_.rz, geo_.ry);
//    }
}

void FormationErelman002::onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyErelman* pErelman = (EnemyErelman*)prm_pActor;
    if (pErelman->pKurokoLeader_) {
        throwGgafCriticalException("pErelman->pKurokoLeader_が設定されてます。pErelman="<<pErelman<<"("<<pErelman->getName()<<")");
    } else {
        pErelman->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createKurokoLeader(pErelman->getKuroko());
    }
//    double rate_z = pErelman->pKurokoLeader_->_pManufacture->_rate_z; //MAG_Z=100000
//
//    //Z = (prm_col*0.4)*rate_z //0.4は隣の列との間隔
//    //(0, 0, Z) を Rz > Ry 回転移動させると
//    //(Z*sinRy, 0, Z*cosRy)
//    float sinRy = ANG_SIN(geo_.ry);
//    float cosRy = ANG_COS(geo_.ry);
//    double d_col = -1.0 * papSplManufConn_[prm_col]->peek()->_sp->_rotmat._43;
//    dxcoord Z = d_col*rate_z; //rate_zを掛けることにより、ここで Z はcoordの単位となる。(ようにMAG_X,MAG_Y,MAG_Zを設定してある）
//    coord dx = Z*sinRy;
//    coord dy = 0;
//    coord dz = Z*cosRy;
//    pErelman->pKurokoLeader_->setStartPosition(geo_.x + dx,
//                                              geo_.y + dy,
//                                              geo_.z + dz);
    pErelman->pKurokoLeader_->setStartPosition(geo_.x, geo_.y, geo_.z);
    pErelman->pKurokoLeader_->setStartAngle(geo_.rx, geo_.ry, geo_.rz);
    pErelman->setPositionAround(geo_.x, geo_.y, geo_.z, PX_C(700));
    pErelman->setFaceAngTwd(geo_.x,
                           geo_.y,
                           geo_.z);
    pErelman->getKuroko()->setMvAngByFaceAng();
    pErelman->getKuroko()->setMvVelo(0);
    pErelman->getKuroko()->setMvAcce(80);

    //色を設定
    GgafXpm* pXpM = pXpmConnection_->peek();
    pErelman->setMaterialColor(pXpM->getColor(prm_row, prm_col));
}

void FormationErelman002::onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) {

}

FormationErelman002::~FormationErelman002() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

