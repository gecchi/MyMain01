#include "FormationOebius002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
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

FormationOebius002::FormationOebius002(const char* prm_name, EnemyOebiusController* prm_pController) :
        FormationOebius(prm_name, "FormationOebius002_Xpm", 8, prm_pController) {
    _class_name = "FormationOebius002";

    papSplManufConn_ = NEW SplineManufactureConnection*[getFormationColNum()];
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col] = getConnection_SplineManufactureManager(("FormationOebius002/"+XTOS(col)).c_str());
    }
}

void FormationOebius002::processBehavior() {
    FormationOebius::processBehavior();
}

void FormationOebius002::onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) {
    EnemyOebius* pOebius = (EnemyOebius*)prm_pActor;
    if (pOebius->pKurokoLeader_) {
        throwGgafCriticalException("FormationOebius002::onCallUp pOebius->pKurokoLeader_Ç™ê›íËÇ≥ÇÍÇƒÇ‹Ç∑ÅBpOebius="<<pOebius<<"("<<pOebius->getName()<<")");
    } else {
        pOebius->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createKurokoLeader(pOebius->getKuroko());
    }
    double rate_z = pOebius->pKurokoLeader_->_pManufacture->_rate_z;

    //Z = (prm_col*0.4)*rate_z //0.4ÇÕó◊ÇÃóÒÇ∆ÇÃä‘äu
    //(0, 0, Z) Ç Rz > Ry âÒì]à⁄ìÆÇ≥ÇπÇÈÇ∆
    //(Z*sinRy, 0, Z*cosRy)
    float sinRy = ANG_SIN(entry_pos_.ry);
    float cosRy = ANG_COS(entry_pos_.ry);
    double d_col = -1.0 * papSplManufConn_[prm_col]->peek()->_sp->_rotmat._43;
    float Z = d_col*rate_z; //rate_zÇä|ÇØÇÈÇ±Ç∆Ç…ÇÊÇËÅAÇ±Ç±Ç≈ Z ÇÕcoordÇÃíPà Ç∆Ç»ÇÈÅB
    coord dx = Z*sinRy;
    coord dy = 0;
    coord dz = Z*cosRy;
    pOebius->pKurokoLeader_->fixStartPosition(entry_pos_.x + dx,
                                              entry_pos_.y + dy,
                                              entry_pos_.z + dz);
    pOebius->pKurokoLeader_->fixStartAngle(entry_pos_.rz, entry_pos_.ry);

    pOebius->position( RND_ABOUT(entry_pos_.x + dx, PX_C(700)),
                       RND_ABOUT(entry_pos_.y + dy, PX_C(700)),
                       RND_ABOUT(entry_pos_.z + dz, PX_C(700)) );
    pOebius->setFaceAngTwd(entry_pos_.x + dx,
                           entry_pos_.y + dy,
                           entry_pos_.z + dz);
    pOebius->getKuroko()->setMvAngByFaceAng();
    pOebius->getKuroko()->setMvVelo(0);
    pOebius->getKuroko()->setMvAcce(80);

    //êFÇê›íË
    GgafXpm* pXpM = pXpmConnection_->peek();
    pOebius->setMaterialColor(pXpM->getColor(prm_row, prm_col));
}

void FormationOebius002::onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) {

}

FormationOebius002::~FormationOebius002() {
    for (int col = 0; col < getFormationColNum(); col++) {
        papSplManufConn_[col]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

