#include "jp/ggaf/lib/util/spline/SteppedCoordSplineRikishaLeader.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineManufacture.h"



using namespace GgafLib;

SteppedCoordSplineRikishaLeader::SteppedCoordSplineRikishaLeader(SplineManufacture* prm_pManufacture, GgafDx::Rikisha* prm_pRikisha_target) :
        SplineLeader(prm_pManufacture, prm_pRikisha_target->_pActor) {
    _pRikisha_target = prm_pRikisha_target;
    _pSteppedSplManuf = (SteppedCoordSplineManufacture*)prm_pManufacture;
    _leading_frames = 0;
    _point_index = -1;
}

void SteppedCoordSplineRikishaLeader::restart() {
    SplineLeader::restart();
    _leading_frames = 0;
    //始点へ行く特別処理。
//    if (ABS(_distance_to_begin) <= PX_C(1)) {
    if ( (ucoord)(_distance_to_begin + PX_C(1)) <= (ucoord)(PX_C(2)) ) {
        //始点との距離が無い場合(PX_C(1)以下)の場合、
        //スプライン補間点の第１点目を間引いて、始点の次の補間点からスタート
        _point_index = 0;
    } else {
        //始点との距離が離れていれば、１フレーム費やし始点へ
        _point_index = -1;
    }
}

void SteppedCoordSplineRikishaLeader::behave() {
    if (_is_leading) {
        GgafDx::Rikisha* const pRikisha_target = _pActor_target->callRikisha();
        _point_index++;
        if (_point_index == _pSteppedSplManuf->_pSpl->_rnum) {
            if (_cnt_loop == _max_loop) {
                //終了
                _is_leading = false;
                return;
            } else {
                //ループ
                _cnt_loop++;
                restart();
                _point_index++;
            }
        }
        coord x, y, z;
        getPointCoord(_point_index, x, y, z);
        coord d = UTIL::getDistance(_pActor_target->_x, _pActor_target->_y, _pActor_target->_z, x, y, z);
        pRikisha_target->setMvAngTwd(x, y, z);
        pRikisha_target->setMvVelo(d);
        _leading_frames++;
    }
}

SteppedCoordSplineRikishaLeader::~SteppedCoordSplineRikishaLeader() {
}
