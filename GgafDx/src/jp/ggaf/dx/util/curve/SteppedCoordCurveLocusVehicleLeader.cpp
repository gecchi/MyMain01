#include "jp/ggaf/dx/util/curve/SteppedCoordCurveLocusVehicleLeader.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/SteppedCoordCurveManufacture.h"

using namespace GgafDx;

SteppedCoordCurveLocusVehicleLeader::SteppedCoordCurveLocusVehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::LocusVehicle* prm_pLocusVehicle_target) :
        VehicleLeader(prm_pManufacture, prm_pLocusVehicle_target->_pActor) {
    _pLocusVehicle_target = prm_pLocusVehicle_target;
    _pSteppedSplManuf = (SteppedCoordCurveManufacture*)prm_pManufacture;
    _leading_frames = 0;
    _point_index = -1;
}

void SteppedCoordCurveLocusVehicleLeader::restart() {
    VehicleLeader::restart();
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

void SteppedCoordCurveLocusVehicleLeader::behave() {
    if (_is_leading) {
        GgafDx::LocusVehicle* pLocusVehicle_target = _pActor_target->getLocusVehicle();
        _point_index++;
        if (_point_index == _pSteppedSplManuf->_pCurve->_rnum) {
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
        pLocusVehicle_target->setMvAngTwd(x, y, z);
        pLocusVehicle_target->setMvVelo(d);
        _leading_frames++;
    }
}

SteppedCoordCurveLocusVehicleLeader::~SteppedCoordCurveLocusVehicleLeader() {
}
