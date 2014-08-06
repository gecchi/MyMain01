#include "stdafx.h"
#include "FormationDelheid001.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/EnemyDelheid.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationDelheid001::FormationDelheid001(const char* prm_name) :
        FormationDelheid(prm_name) {
    _class_name = "FormationDelheid001";
    pConn_pSplManuf_ = getConnection_SplineManufactureManager("FormationDelheid001");
}

void FormationDelheid001::onCallUpDelheid(EnemyDelheid* pEnemyDelheid) {
    pEnemyDelheid->positionAs(&geoLocate_);
    pEnemyDelheid->getKuroko()->setRzRyMvAng(geoLocate_.rz, geoLocate_.ry);
}

GgafLib::SplineManufacture* FormationDelheid001::getSplManuf() {
    return pConn_pSplManuf_->peek(); //e
}
void FormationDelheid001::processBehavior() {
    FormationDelheid::processBehavior();
}

FormationDelheid001::~FormationDelheid001() {
    pConn_pSplManuf_->close();
}
