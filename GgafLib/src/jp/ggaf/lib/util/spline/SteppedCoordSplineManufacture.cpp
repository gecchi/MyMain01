#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineManufacture.h"

#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SteppedCoordSplineManufacture::SteppedCoordSplineManufacture(const char* prm_source_file,
                                                               int prm_turn_way,
                                                               bool prm_turn_optimaize) :
        SplineManufacture(prm_source_file) {
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;
    _paDistance_to = NEW coord[_sp->_rnum];
    _paFrame_need_at = NEW float[_sp->_rnum];
    _point_index = 0;
}

SteppedCoordSplineManufacture::SteppedCoordSplineManufacture(SplineSource* prm_pSplSrc,
                                                               int prm_turn_way,
                                                               bool prm_turn_optimaize) :
        SplineManufacture(prm_pSplSrc) {
    _turn_way = prm_turn_way;
    _turn_optimize = prm_turn_optimaize;
    _paDistance_to = NEW coord[_sp->_rnum];
    _paFrame_need_at = NEW float[_sp->_rnum];
    _point_index = 0;
}

void SteppedCoordSplineManufacture::calculate() {

}

SplineKurokoLeader* SteppedCoordSplineManufacture::createKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko) {
    return NEW SteppedCoordSplineKurokoLeader(this, prm_pKuroko);
}

SteppedCoordSplineManufacture::~SteppedCoordSplineManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
    GGAF_DELETEARR_NULLABLE(_paFrame_need_at);
}
