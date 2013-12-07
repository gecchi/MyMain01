#include "stdafx.h"
#include "FormationAllas001a.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Allas/EnemyAllas.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001a::FormationAllas001a(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001a";
}

void FormationAllas001a::onCallUpAllas(EnemyAllas* prm_pAllas)  {
    prm_pAllas->pKurokoLeader_->setAbsoluteBeginCoord();
    prm_pAllas->_pKuroko->setMvVelo(velo_mv_);
}

FormationAllas001a::~FormationAllas001a() {
}
