#include "FormationUrydike002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/EnemyUrydike.h"
#include "jp/ggaf/core/util/GgafXpm.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUrydike002::FormationUrydike002(const char* prm_name) :
        FormationUrydike(prm_name, "FormationUrydike002_Xpm", 8) {
    _class_name = "FormationUrydike002";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationColNum()];
    papSplManufConn_[0] = getConnection_SplineManufactureManager("FormationUrydike002/0");
    papSplManufConn_[1] = getConnection_SplineManufactureManager("FormationUrydike002/1");
    papSplManufConn_[2] = getConnection_SplineManufactureManager("FormationUrydike002/2");
    papSplManufConn_[3] = getConnection_SplineManufactureManager("FormationUrydike002/3");
    papSplManufConn_[4] = getConnection_SplineManufactureManager("FormationUrydike002/4");
    papSplManufConn_[5] = getConnection_SplineManufactureManager("FormationUrydike002/5");
    papSplManufConn_[6] = getConnection_SplineManufactureManager("FormationUrydike002/6");
    papSplManufConn_[7] = getConnection_SplineManufactureManager("FormationUrydike002/7");
    papSplManufConn_[8] = getConnection_SplineManufactureManager("FormationUrydike002/8");
}

void FormationUrydike002::processBehavior() {
    FormationUrydike::processBehavior();
}

void FormationUrydike002::onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyUrydike* pUrydike = (EnemyUrydike*)prm_pActor;
    if (pUrydike->pKurokoLeader_) {
        throwGgafCriticalException("FormationUrydike002::onCallUp pUrydike->pKurokoLeader_が設定されてます。pUrydike="<<pUrydike<<"("<<pUrydike->getName()<<")");
    } else {
        pUrydike->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                     createKurokoLeader(pUrydike->getKuroko());
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
    pUrydike->pKurokoLeader_->fixStartAngle(entry_pos_.rz, entry_pos_.ry);

    pUrydike->position( RND_ABOUT(entry_pos_.x + dx, PX_C(700)),
                        RND_ABOUT(entry_pos_.y + dy, PX_C(700)),
                        RND_ABOUT(entry_pos_.z + dz, PX_C(700)) );
    pUrydike->setFaceAngTwd(entry_pos_.x + dx,
                            entry_pos_.y + dy,
                            entry_pos_.z + dz);
    pUrydike->getKuroko()->setMvAngByFaceAng();
    pUrydike->getKuroko()->setMvVelo(0);
    pUrydike->getKuroko()->setMvAcce(80);

    //色を設定
    GgafXpm* pXpM = pXpmConnection_->peek();
    pUrydike->setMaterialColor(pXpM->getColor(prm_row, prm_col));
}

void FormationUrydike002::onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) {

}

FormationUrydike002::~FormationUrydike002() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

