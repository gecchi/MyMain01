#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/KurokoMvAngAssistant.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"



using namespace GgafLib;

FixedVelocitySplineKurokoLeader::FixedVelocitySplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDx::Kuroko* prm_pKuroko_target) :
        SplineLeader(prm_pManufacture, prm_pKuroko_target->_pActor) {
    _pKuroko_target = prm_pKuroko_target;
    _pFixedVeloSplManuf = (FixedVelocitySplineManufacture*)prm_pManufacture;
    _leadning_float_frames = 0.0f;
    _float_frame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
}

void FixedVelocitySplineKurokoLeader::restart() {
    SplineLeader::restart();
    _leadning_float_frames = 0.0f;
    _float_frame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
}

void FixedVelocitySplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDx::Kuroko* pKuroko_target = _pKuroko_target;
        //変わり目
        const int sp_rnum = _pFixedVeloSplManuf->_pSpl->_rnum;
        if (_leadning_float_frames >= _float_frame_of_next) {
again:
            _point_index++;
            if (_point_index == sp_rnum) {
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
            if (_leadning_float_frames >= _float_frame_of_next) {
                //_float_frame_of_nextを次に進めても足りない場合、もう一つ_point_indexを進める
                goto again;
            }
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            if (_turn_smooth) {
                pKuroko_target->asstMvAng()->turnByVdTwd(
                        _pFixedVeloSplManuf->_angvelo_rzry_mv,
                        x, y, z, _pFixedVeloSplManuf->_turn_way, _pFixedVeloSplManuf->_turn_optimize,
                        0.3, 0.7, 0,
                        true);
            } else {
                pKuroko_target->turnMvAngTwd(x, y, z,
                                             _pFixedVeloSplManuf->_angvelo_rzry_mv, 0,
                                             _pFixedVeloSplManuf->_turn_way,
                                             _pFixedVeloSplManuf->_turn_optimize);
            }
        }
        //キャラの速度が1000ならば、_leadning_float_frames ++;
        //キャラの速度が2000ならば  _leadning_float_frames += 2.0;
        //キャラの速度が500ならば、 _leadning_float_frames += 0.5
        _leadning_float_frames += (pKuroko_target->_velo_mv * (1.0 / LEN_UNIT));
    }
}

FixedVelocitySplineKurokoLeader::~FixedVelocitySplineKurokoLeader() {
}
