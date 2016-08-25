#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedVelocitySplineKurokoLeader::FixedVelocitySplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKuroko* prm_pKuroko_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKuroko_target) {
    _pFixedVeloSplManuf = (FixedVelocitySplineManufacture*)prm_pManufacture;
    _leadning_float_frames = 0.0f;
    _float_frame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
}

FixedVelocitySplineKurokoLeader::FixedVelocitySplineKurokoLeader(GgafDxKuroko* prm_pKuroko_target,
                                                                 SplineLine* prm_pSpl,
                                                                 angvelo prm_angvelo_rzry_mv):
        SplineKurokoLeader(nullptr, prm_pKuroko_target) { //nullptrで渡す事により、_is_created_pManufacture が falseになる
    _pFixedVeloSplManuf = NEW FixedVelocitySplineManufacture(NEW SplineSource(prm_pSpl), prm_angvelo_rzry_mv);
    _pFixedVeloSplManuf->calculate(); //忘れないように。いずれこのタイプは消す
    _pManufacture = _pFixedVeloSplManuf; //基底メンバーセット。忘れないように。いずれこのタイプは消す
    _leadning_float_frames = 0.0f;
    _float_frame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
}

void FixedVelocitySplineKurokoLeader::restart() {
    SplineKurokoLeader::restart();
    _leadning_float_frames = 0.0f;
    _float_frame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
}

void FixedVelocitySplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
        //変わり目
        if (_leadning_float_frames >= _float_frame_of_next) {
again:
            _point_index++;
            if ( _point_index == _pFixedVeloSplManuf->_sp->_rnum) {
                if (_cnt_loop == _max_loop) {
                    //終了
                    _is_leading = false;
                    pKuroko_target->stopTurningMvAng();
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
                _float_frame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit);
            } else {
                //始点以外の場合次の補完点までに必要なフレーム数を更新
                _float_frame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit) +
                                     _pFixedVeloSplManuf->_paFrame_need_at[_point_index];
            }
        }
        if (_leadning_float_frames >= _float_frame_of_next) {
            //_float_frame_of_nextを次に進めても足りない場合、もう一つ_point_indexを進める
            goto again;
        }
        coord x, y, z;
        getPointCoord(_point_index, x, y, z);
        pKuroko_target->turnMvAngTwd(x, y, z,
                                     _pFixedVeloSplManuf->_angvelo_rzry_mv, 0,
                                     _pFixedVeloSplManuf->_turn_way,
                                     _pFixedVeloSplManuf->_turn_optimize);
        //キャラの速度が1000ならば、_leadning_float_frames ++;
        //キャラの速度が2000ならば  _leadning_float_frames += 2.0;
        //キャラの速度が500ならば、 _leadning_float_frames += 0.5
        _leadning_float_frames += (pKuroko_target->_velo_mv * (1.0 / LEN_UNIT));
    }
}

FixedVelocitySplineKurokoLeader::~FixedVelocitySplineKurokoLeader() {
}
