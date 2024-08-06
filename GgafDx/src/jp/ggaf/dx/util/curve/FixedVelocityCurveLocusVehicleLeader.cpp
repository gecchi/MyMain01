#include "jp/ggaf/dx/util/curve/FixedVelocityCurveLocusVehicleLeader.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAngAssistant.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"

using namespace GgafDx;

FixedVelocityCurveLocusVehicleLeader::FixedVelocityCurveLocusVehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::LocusVehicle* prm_pLocusVehicle_target) :
        VehicleLeader(prm_pManufacture, prm_pLocusVehicle_target->_pActor) {
    _pLocusVehicle_target = prm_pLocusVehicle_target;
    _pFixedVeloSplManuf = (FixedVelocityCurveManufacture*)prm_pManufacture;
    _leadning_double_frames = 0.0;
    _double_frame_of_next = -0.00001;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
}

void FixedVelocityCurveLocusVehicleLeader::restart() {
    VehicleLeader::restart();
    _leadning_double_frames = 0.0;
    _double_frame_of_next = -0.00001;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
}

void FixedVelocityCurveLocusVehicleLeader::behave() {
    if (_is_leading) {
        GgafDx::LocusVehicle* pLocusVehicle_target = _pLocusVehicle_target;
        //変わり目
        const int sp_rnum = _pFixedVeloSplManuf->_pCurve->_rnum;
        if (_leadning_double_frames >= _double_frame_of_next) {
again:
            _point_index++;
            if (_point_index == sp_rnum) {
                if (_cnt_loop == _max_loop) {
                    //終了
                    _is_leading = false;
                    pLocusVehicle_target->stopTurningMvAng();
                    return;
                } else {
                    //ループ
                    _cnt_loop++;
                    restart();
                    _point_index++;
                }
            }
            if (_point_index == 0) {
                //最初の必然ブレイク、始点へ行く
                //始点までに必要なフレーム数取得
                _double_frame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit);
            } else {
                //始点以外の場合次の補完点までに必要なフレーム数を更新
                _double_frame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit) +
                                     _pFixedVeloSplManuf->_paFrame_need_at[_point_index];
            }
            if (_leadning_double_frames >= _double_frame_of_next) {
                //_double_frame_of_nextを次に進めても足りない場合、もう一つ_point_indexを進める
                goto again;
            }
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            if (_turn_smooth) {
                pLocusVehicle_target->asstMvAng()->turnByVdTwd(
                        _pFixedVeloSplManuf->_angvelo_rzry_mv,
                        x, y, z, _pFixedVeloSplManuf->_turn_way, _pFixedVeloSplManuf->_turn_optimize,
                        0.3, 0.7, 0,
                        true);
            } else {
                pLocusVehicle_target->turnMvAngTwd(x, y, z,
                                             _pFixedVeloSplManuf->_angvelo_rzry_mv, 0,
                                             _pFixedVeloSplManuf->_turn_way,
                                             _pFixedVeloSplManuf->_turn_optimize);
            }
        }
        //キャラの速度が1000ならば、_leadning_double_frames ++;
        //キャラの速度が2000ならば  _leadning_double_frames += 2.0;
        //キャラの速度が500ならば、 _leadning_double_frames += 0.5
        _leadning_double_frames += (pLocusVehicle_target->_velo_mv * (1.0 / LEN_UNIT));
    }
}

FixedVelocityCurveLocusVehicleLeader::~FixedVelocityCurveLocusVehicleLeader() {
}
