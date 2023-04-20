#include "jp/ggaf/dx/util/curve/FixedFrameCurveCoordVehicleLeader.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveManufacture.h"

using namespace GgafDx;

FixedFrameCurveCoordVehicleLeader::FixedFrameCurveCoordVehicleLeader(
                                       CurveManufacture* prm_pManufacture,
                                       GgafDx::CoordVehicle* prm_pCoordVehicle_target) :
        VehicleLeader(prm_pManufacture, prm_pCoordVehicle_target->_pActor) {
    _pCoordVehicle_target = prm_pCoordVehicle_target;
    _pFixedFrameSplManuf = (FixedFrameCurveManufacture*)prm_pManufacture;
    _leading_frames = 0;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}

void FixedFrameCurveCoordVehicleLeader::restart() {
    VehicleLeader::restart();
    _leading_frames = 0;
    _hosei_frames = 0;
    _point_index = 0;
    _prev_point_index = -1;

    //始点へ行く特別処理。
    //始点への距離(_distance_to_begin) がわかっているので、
    //
    // 始点への速度 = (velo)(_distance_to_begin / _pFixedFrameSplManuf->_frame_of_segment)
    //
    //としたいが、
    //_pFixedFrameSplManuf->_frame_of_segment は、現座標～始点 を除いた
    //計算で求めているので、補完点数が少ない場合、費やされるフレーム合計の誤差が大きい。
    //そこで始点への距離0とみなせる場合には、現座標～始点 をなかったコトにする。
    //そうでなければ仕方ないので、費やされるフレーム合計の誤差を認める仕様とする。
//    if (ABS(_distance_to_begin) <= PX_C(1)) {
    if ( (ucoord)(_distance_to_begin + PX_C(1)) <= (ucoord)(PX_C(2)) ) {
        //始点への距離が無い、間引く。
        //_TRACE_("【警告】FixedFrameCurveCoordVehicleLeader::start("<<prm_option<<") _pActor_target="<<_pActor_target->getName()<<
        //    " 現座標～始点[0]への距離は 0 であるため、現座標～始点への移動プロセスはカットされます。");
        _hosei_frames = _pFixedFrameSplManuf->_frame_of_segment;
        //これにより、_point_index は、初回いきなり1から始まる。
    } else {
        _TRACE_("【警告】FixedFrameCurveCoordVehicleLeader::restart("<<_option<<") _pActor_target="<<_pActor_target->getName()<<
            " 現座標～始点[0]への距離("<<_distance_to_begin<<" coord)が離れているため、現座標～始点への移動プロセスとしてセグメントが＋１されます。"<<
            "そのため、合計移動フレーム時間に誤差(+"<<_pFixedFrameSplManuf->_frame_of_segment<<"フレーム)が生じます。ご了承くださいませ。");
        _hosei_frames = 0;
        //これにより、_point_index は、初回0から始まる。
    }

}

void FixedFrameCurveCoordVehicleLeader::behave() {
    if (_is_leading) {
        GgafDx::CoordVehicle* const pCoordVehicle_target = _pCoordVehicle_target;
        const double frame_of_segment = _pFixedFrameSplManuf->_frame_of_segment;
        //現在の点INDEX
        _point_index = (_leading_frames+_hosei_frames) / frame_of_segment;
        if ( _point_index == _pFixedFrameSplManuf->_pCurve->_rnum) {
            if (_cnt_loop == _max_loop) {
                //終了
                _is_leading = false;
                pCoordVehicle_target->stopGravitationMvSequence();
                return;
            } else {
                //ループ
                _cnt_loop++;
                restart();
                _point_index = (_leading_frames+_hosei_frames) / frame_of_segment;
            }
        }

        //変わり目
        if (_prev_point_index != _point_index) {
            _prev_point_index = _point_index;
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            velo mv_velo = 0;
            const coord calc_d = _pFixedFrameSplManuf->_paDistance_to[_point_index];
            if (_point_index == 0) {
                //現座標と開始が離れている。
                //誤差も仕方ないので _frame_of_segment で始点に移動する速度を付与
                mv_velo = (velo)(_distance_to_begin / frame_of_segment);
            } else {
                const coord actually_d = UTIL::getDistance(
                                        _pActor_target->_x,
                                        _pActor_target->_y,
                                        _pActor_target->_z,
                                        x, y, z);

                if (calc_d*1.06 < actually_d) {
                    //速度補正：距離が予想より開いている(1.06倍以上空いてる)ので少し急ぐ(1.05倍のスピードにする)
                    mv_velo = _pFixedFrameSplManuf->_paSPMvVeloTo[_point_index] * 1.05;
                } if (calc_d*0.94 > actually_d) {
                    //速度補正：距離が予想より近い(0.94倍以内になっている)ので少しゆっくりする(0.95倍のスピードにする)
                    mv_velo = _pFixedFrameSplManuf->_paSPMvVeloTo[_point_index] * (((1.0*actually_d)/calc_d)*0.95);
                } else {
                    mv_velo = _pFixedFrameSplManuf->_paSPMvVeloTo[_point_index];
                }
            }
            //pCoordVehicle_target->setVeloXYZTwd(x, y, z, mv_velo);
            pCoordVehicle_target->execGravitationMvSequenceTwd(x, y, z, mv_velo*2, mv_velo/10, calc_d/10);
        }
        _leading_frames++;
    }
}
FixedFrameCurveCoordVehicleLeader::~FixedFrameCurveCoordVehicleLeader() {

}
