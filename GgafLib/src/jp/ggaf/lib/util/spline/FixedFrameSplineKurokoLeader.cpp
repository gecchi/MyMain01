#include "jp/ggaf/lib/util/spline/FixedFrameSplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKuroko* prm_pKuroko_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKuroko_target) {
    _pFixedFrameSplManuf = (FixedFrameSplineManufacture*)prm_pManufacture;
    _leading_frames = 0;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}
FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(GgafDxKuroko* prm_pKuroko_target,
                                                           SplineLine* prm_pSpl,
                                                           frame prm_spent_frame,
                                                           angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKuroko_target) {  //nullptrで渡す事により、_is_created_pManufacture が falseになる

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prm_pSpl), prm_spent_frame, prm_angveloRzRyMv);
    _pFixedFrameSplManuf->calculate();//これも忘れないように。いずれこのタイプは消す
    _pManufacture = _pFixedFrameSplManuf;
    _leading_frames = 0;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}

void FixedFrameSplineKurokoLeader::restart() {
    SplineKurokoLeader::restart();
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
    if (ABS(_distance_to_begin) <= PX_C(1)) {
        //始点への距離が無い、間引く。
        //_TRACE_("＜警告＞FixedFrameSplineKurokoLeader::start("<<prm_option<<") _pActor_target="<<_pActor_target->getName()<<
        //    " 現座標～始点[0]への距離は 0 であるため、現座標～始点への移動プロセスはカットされます。");
        _hosei_frames = _pFixedFrameSplManuf->_frame_of_segment;
        //これにより、_point_index は、初回いきなり1から始まる。
    } else {
        _TRACE_("＜警告＞FixedFrameSplineKurokoLeader::restart("<<_option<<") _pActor_target="<<_pActor_target->getName()<<
            " 現座標～始点[0]への距離("<<_distance_to_begin<<" coord)が離れているため、現座標～始点への移動プロセスとしてセグメントが＋１されます。"<<
            "そのため、合計移動フレーム時間に誤差(+"<<_pFixedFrameSplManuf->_frame_of_segment<<"フレーム)が生じます。ご了承くださいませ。");
        _hosei_frames = 0;
        //これにより、_point_index は、初回0から始まる。
    }

}

void FixedFrameSplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
        //現在の点INDEX
        _point_index = (_leading_frames+_hosei_frames) / _pFixedFrameSplManuf->_frame_of_segment;
        if ( _point_index == _pFixedFrameSplManuf->_sp->_rnum) {
            if (_cnt_loop == _max_loop) {
                //終了
                _is_leading = false;
                pKuroko_target->stopTurningMvAng();
                return;
            } else {
                //ループ
                _cnt_loop++;
                restart();
                _point_index = (_leading_frames+_hosei_frames) / _pFixedFrameSplManuf->_frame_of_segment;
            }
        }

        //変わり目
        if (_prev_point_index != _point_index) {
            _prev_point_index = _point_index;
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            pKuroko_target->turnMvAngTwd(x, y, z,
                                         _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                         _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            if (_point_index == 0) {
                //現座標と開始が離れている。
                //誤差も仕方ないので _frame_of_segment で始点に移動する速度を付与
                pKuroko_target->setMvVelo((velo)(_distance_to_begin / _pFixedFrameSplManuf->_frame_of_segment));
            } else {
                const coord d = UTIL::getDistance(
                                        _pActor_target->_x,
                                        _pActor_target->_y,
                                        _pActor_target->_z,
                                        x, y, z);
                if (_pFixedFrameSplManuf->_paDistance_to[_point_index]*1.1 < d) {
                    //補正：距離が予想より開いているので少し急ぐ(1.1倍のスピードにする)
                    pKuroko_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index] * 1.1) ;
                    //pKuroko_target->setMvVelo(((velo)(d / _pFixedFrameSplManuf->_frame_of_segment)) + 1);
                } else {
                    pKuroko_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index]);
                }
            }
        }
        _leading_frames++;
    }
    //_TRACE_(_pActor_target->getBehaveingFrame()<<": "<<_leading_frames<<": _cnt_loop="<<_cnt_loop<<"  _point_index="<<_point_index<<" velo="<<_pActor_target->getKuroko()->getMvVelo()<<" xyz="<<_pActor_target->_x<<","<<_pActor_target->_y<<","<<_pActor_target->_z);
}
FixedFrameSplineKurokoLeader::~FixedFrameSplineKurokoLeader() {

}
