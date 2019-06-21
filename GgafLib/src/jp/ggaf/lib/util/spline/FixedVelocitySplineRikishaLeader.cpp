#include "jp/ggaf/lib/util/spline/FixedVelocitySplineRikishaLeader.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/RikishaMvAngAssistant.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"



using namespace GgafLib;

FixedVelocitySplineRikishaLeader::FixedVelocitySplineRikishaLeader(SplineManufacture* prm_pManufacture, GgafDx::Rikisha* prm_pRikisha_target) :
        SplineLeader(prm_pManufacture, prm_pRikisha_target->_pActor) {
    _pRikisha_target = prm_pRikisha_target;
    _pFixedVeloSplManuf = (FixedVelocitySplineManufacture*)prm_pManufacture;
    _leadning_float_frames = 0.0f;
    _float_frame_of_next = -0.00001f;
    _point_index = -1;//�ŏ��͎n�_[0]�Ɍ������̂ŁA�n�_�O��-1�ɂȂ�B
}

void FixedVelocitySplineRikishaLeader::restart() {
    SplineLeader::restart();
    _leadning_float_frames = 0.0f;
    _float_frame_of_next = -0.00001f;
    _point_index = -1;//�ŏ��͎n�_[0]�Ɍ������̂ŁA�n�_�O��-1�ɂȂ�B
}

void FixedVelocitySplineRikishaLeader::behave() {
    if (_is_leading) {
        GgafDx::Rikisha* pRikisha_target = _pRikisha_target;
        //�ς���
        const int sp_rnum = _pFixedVeloSplManuf->_pSpl->_rnum;
        if (_leadning_float_frames >= _float_frame_of_next) {
again:
            _point_index++;
            if (_point_index == sp_rnum) {
                if (_cnt_loop == _max_loop) {
                    //�I��
                    _is_leading = false;
                    pRikisha_target->stopTurningMvAng();
                    return;
                } else {
                    //���[�v
                    _cnt_loop++;
                    restart();
                    _point_index++;
                }
            }
            if (_point_index == 0) {
                //�ŏ��̕K�R�u���C�N�A�n�_�֍s��
                //�n�_�܂łɕK�v�ȃt���[�����擾
                _float_frame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit);
            } else {
                //�n�_�ȊO�̏ꍇ���̕⊮�_�܂łɕK�v�ȃt���[�������X�V
                _float_frame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit) +
                                     _pFixedVeloSplManuf->_paFrame_need_at[_point_index];
            }
            if (_leadning_float_frames >= _float_frame_of_next) {
                //_float_frame_of_next�����ɐi�߂Ă�����Ȃ��ꍇ�A�������_point_index��i�߂�
                goto again;
            }
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            if (_turn_smooth) {
                pRikisha_target->asstMvAng()->turnByVdTwd(
                        _pFixedVeloSplManuf->_angvelo_rzry_mv,
                        x, y, z, _pFixedVeloSplManuf->_turn_way, _pFixedVeloSplManuf->_turn_optimize,
                        0.3, 0.7, 0,
                        true);
            } else {
                pRikisha_target->turnMvAngTwd(x, y, z,
                                             _pFixedVeloSplManuf->_angvelo_rzry_mv, 0,
                                             _pFixedVeloSplManuf->_turn_way,
                                             _pFixedVeloSplManuf->_turn_optimize);
            }
        }
        //�L�����̑��x��1000�Ȃ�΁A_leadning_float_frames ++;
        //�L�����̑��x��2000�Ȃ��  _leadning_float_frames += 2.0;
        //�L�����̑��x��500�Ȃ�΁A _leadning_float_frames += 0.5
        _leadning_float_frames += (pRikisha_target->_velo_mv * (1.0 / LEN_UNIT));
    }
}

FixedVelocitySplineRikishaLeader::~FixedVelocitySplineRikishaLeader() {
}
