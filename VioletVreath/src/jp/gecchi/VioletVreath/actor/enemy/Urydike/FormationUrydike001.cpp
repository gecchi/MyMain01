#include "FormationUrydike001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/EnemyUrydike.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUrydike001::FormationUrydike001(const char* prm_name) :
        FormationUrydike(prm_name, 9, 256, 8) {
    _class_name = "FormationUrydike001";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationColNum()];
    papSplManufConn_[0] = getConnection_SplineManufactureManager("FormationUrydike001");
    papSplManufConn_[1] = getConnection_SplineManufactureManager("FormationUrydike001_0_1");
    papSplManufConn_[2] = getConnection_SplineManufactureManager("FormationUrydike001_1_1");
    papSplManufConn_[3] = getConnection_SplineManufactureManager("FormationUrydike001_0_2");
    papSplManufConn_[4] = getConnection_SplineManufactureManager("FormationUrydike001_1_2");
    papSplManufConn_[5] = getConnection_SplineManufactureManager("FormationUrydike001_0_3");
    papSplManufConn_[6] = getConnection_SplineManufactureManager("FormationUrydike001_1_3");
    papSplManufConn_[7] = getConnection_SplineManufactureManager("FormationUrydike001_0_4");
    papSplManufConn_[8] = getConnection_SplineManufactureManager("FormationUrydike001_1_4");
}

void FormationUrydike001::processBehavior() {
    FormationUrydike::processBehavior();
}

void FormationUrydike001::onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) {
    EnemyUrydike* pUrydike = (EnemyUrydike*)prm_pActor;
    if (pUrydike->pKurokoLeader_) {
        throwGgafCriticalException("FormationUrydike001::onCallUp pUrydike->pKurokoLeader_が設定されてます。pUrydike="<<pUrydike<<"("<<pUrydike->getName()<<")");
    } else {
        SplineKurokoLeader* pKurokoLeader = papSplManufConn_[prm_col]->peek()->
                                                createKurokoLeader(pUrydike->getKuroko());
        pUrydike->pKurokoLeader_ = pKurokoLeader;
    }
    double rate_x = pUrydike->pKurokoLeader_->_pManufacture->_rate_x;
    double d_col = -1.0 * papSplManufConn_[prm_col]->peek()->_sp->_rotmat._41; //横との間隔
    float X = d_col*rate_x; //rate_xを掛けることにより、ここで X はcoordの単位となる。

    float sinRz = ANG_SIN(entry_pos_.rz);
    float cosRz = ANG_COS(entry_pos_.rz);
    float sinRy = ANG_SIN(entry_pos_.ry);
    float cosRy = ANG_COS(entry_pos_.ry);

    //(X,0,0) を Rz > Ry 回転移動させると
    //(X*cosRz*cosRy, X*sinRz, X*cosRz*-sinRy)
    coord dx = X*cosRz*cosRy;
    coord dy = X*sinRz;
    coord dz = X*cosRz*-sinRy;
    pUrydike->pKurokoLeader_->fixStartPosition(entry_pos_.x + dx,
                                               entry_pos_.y + dy,
                                               entry_pos_.z + dz);
    pUrydike->pKurokoLeader_->fixStartMvAngle(entry_pos_.rz, entry_pos_.ry);


    pUrydike->position( RND_ABOUT(entry_pos_.x + dx, PX_C(700)),
                        RND_ABOUT(entry_pos_.y + dy, PX_C(700)),
                        RND_ABOUT(entry_pos_.z + dz, PX_C(700)) );
    pUrydike->setFaceAngTwd(entry_pos_.x + dx,
                            entry_pos_.y + dy,
                            entry_pos_.z + dz);
    pUrydike->getKuroko()->setMvAngByFaceAng();
    pUrydike->getKuroko()->setMvVelo(0);
    pUrydike->getKuroko()->setMvAcce(80);

    double r = RANGE_CONV(0, getFormationColNum()                      , prm_col         , 0.3, 1.0);
    double g = RANGE_CONV(0, getFormationColNum()*getFormationRowNum() , prm_col*prm_row , 0.3, 1.0);
    double b = RANGE_CONV(0, getFormationRowNum()                      , prm_row         , 0.3, 1.0);
    pUrydike->setMaterialColor(r, g, b);
}

void FormationUrydike001::onFinshLeading(GgafDxCore::GgafDxDrawableActor* prm_pActor) {

}

FormationUrydike001::~FormationUrydike001() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

