#include "stdafx.h"
#include "FormationDelheid001.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/EnemyDelheid.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationDelheid001::FormationDelheid001(const char* prm_name) :
        FormationDelheid(prm_name) {
    _class_name = "FormationDelheid001";
    pSplManufConnection_ = connect_SplineManufactureManager("FormationDelheid001");
}

void FormationDelheid001::onCallUpDelheid(EnemyDelheid* pEnemyDelheid) {
    pEnemyDelheid->positionAs(&geoLocate_);
    pEnemyDelheid->_pKurokoA->setRzRyMvAng(geoLocate_.RZ, geoLocate_.RY);
}

GgafLib::SplineManufacture* FormationDelheid001::getSplManuf() {
    return pSplManufConnection_->peek(); //e
}
void FormationDelheid001::processBehavior() {
    FormationDelheid::processBehavior();
}

FormationDelheid001::~FormationDelheid001() {
    pSplManufConnection_->close();
}
