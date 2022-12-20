#include "jp/ggaf/dx/util/curve/FixedFrameCurveVecVehicleLeader.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveManufacture.h"

using namespace GgafDx;

FixedFrameCurveVecVehicleLeader::FixedFrameCurveVecVehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::VecVehicle* prm_pVecVehicle_target) :
        VehicleLeader(prm_pManufacture, prm_pVecVehicle_target->_pActor) {
    _pVecVehicle_target = prm_pVecVehicle_target;
    _pFixedFrameSplManuf = (FixedFrameCurveManufacture*)prm_pManufacture;
    _leading_frames = 0;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}
void FixedFrameCurveVecVehicleLeader::restart() {
    VehicleLeader::restart();
    _leading_frames = 0;
    _hosei_frames = 0;
    _point_index = 0;
    _prev_point_index = -1;

    //�n�_�֍s�����ʏ����B
    //�n�_�ւ̋���(_distance_to_begin) ���킩���Ă���̂ŁA
    //
    // �n�_�ւ̑��x = (velo)(_distance_to_begin / _pFixedFrameSplManuf->_frame_of_segment)
    //
    //�Ƃ��������A
    //_pFixedFrameSplManuf->_frame_of_segment �́A�����W�`�n�_ ��������
    //�v�Z�ŋ��߂Ă���̂ŁA�⊮�_�������Ȃ��ꍇ�A��₳���t���[�����v�̌덷���傫���B
    //�����Ŏn�_�ւ̋���0�Ƃ݂Ȃ���ꍇ�ɂ́A�����W�`�n�_ ���Ȃ������R�g�ɂ���B
    //�����łȂ���Ύd���Ȃ��̂ŁA��₳���t���[�����v�̌덷��F�߂�d�l�Ƃ���B
//    if (ABS(_distance_to_begin) <= PX_C(1)) {
    if ( (ucoord)(_distance_to_begin + PX_C(1)) <= (ucoord)(PX_C(2)) ) {
        //�n�_�ւ̋����������A�Ԉ����B
        //_TRACE_("�y�x���zFixedFrameCurveVecVehicleLeader::start("<<prm_option<<") _pActor_target="<<_pActor_target->getName()<<
        //    " �����W�`�n�_[0]�ւ̋����� 0 �ł��邽�߁A�����W�`�n�_�ւ̈ړ��v���Z�X�̓J�b�g����܂��B");
        _hosei_frames = _pFixedFrameSplManuf->_frame_of_segment;
        //����ɂ��A_point_index �́A���񂢂��Ȃ�1����n�܂�B
    } else {
        _TRACE_("�y�x���zFixedFrameCurveVecVehicleLeader::restart("<<_option<<") _pActor_target="<<_pActor_target->getName()<<
            " �����W�`�n�_[0]�ւ̋���("<<_distance_to_begin<<" coord)������Ă��邽�߁A�����W�`�n�_�ւ̈ړ��v���Z�X�Ƃ��ăZ�O�����g���{�P����܂��B"<<
            "���̂��߁A���v�ړ��t���[�����ԂɌ덷(+"<<_pFixedFrameSplManuf->_frame_of_segment<<"�t���[��)�������܂��B���������������܂��B");
        _hosei_frames = 0;
        //����ɂ��A_point_index �́A����0����n�܂�B
    }

}

void FixedFrameCurveVecVehicleLeader::behave() {
    if (_is_leading) {
        GgafDx::VecVehicle* pVecVehicle_target = _pVecVehicle_target;
        const double frame_of_segment = _pFixedFrameSplManuf->_frame_of_segment;
        //���݂̓_INDEX
        _point_index = (_leading_frames+_hosei_frames) / frame_of_segment;
        if ( _point_index == _pFixedFrameSplManuf->_pCurve->_rnum) {
            if (_cnt_loop == _max_loop) {
                //�I��
                _is_leading = false;
                pVecVehicle_target->stopTurningMvAng();
                return;
            } else {
                //���[�v
                _cnt_loop++;
                restart();
                _point_index = (_leading_frames+_hosei_frames) / frame_of_segment;
            }
        }

        //�ς���
        if (_prev_point_index != _point_index) {
            _prev_point_index = _point_index;
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            pVecVehicle_target->turnMvAngTwd(x, y, z,
                                         _pFixedFrameSplManuf->_angvelo_rzry_mv, 0,
                                         _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            if (_point_index == 0) {
                //�����W�ƊJ�n������Ă���B
                //�덷���d���Ȃ��̂� _frame_of_segment �Ŏn�_�Ɉړ����鑬�x��t�^
                pVecVehicle_target->setMvVelo((velo)(_distance_to_begin / frame_of_segment));
            } else {
                const coord calc_d = _pFixedFrameSplManuf->_paDistance_to[_point_index];
                const coord actually_d = UTIL::getDistance(
                                        _pActor_target->_x,
                                        _pActor_target->_y,
                                        _pActor_target->_z,
                                        x, y, z);

                if (calc_d*1.06 < actually_d) {
                    //���x�␳�F�������\�z���J���Ă���(1.06�{�ȏ�󂢂Ă�)�̂ŏ����}��(1.05�{�̃X�s�[�h�ɂ���)
                    pVecVehicle_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index] * 1.05) ;
                } if (calc_d*0.99 > actually_d) {
                    //���x�␳�F�������\�z���߂�(0.99�{�ȓ��ɂȂ��Ă���)�̂ŏ���������肷��(0.95�{�̃X�s�[�h�ɂ���)
                    pVecVehicle_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index] * 0.95) ;
                } else {
                    pVecVehicle_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index]);
                }
            }
        }
        _leading_frames++;
    }
    //_TRACE_(_pActor_target->getBehaveingFrame()<<": "<<_leading_frames<<": _cnt_loop="<<_cnt_loop<<"  _point_index="<<_point_index<<" velo="<<_pActor_target->getVecVehicle()->getMvVelo()<<" xyz="<<_pActor_target->_x<<","<<_pActor_target->_y<<","<<_pActor_target->_z);
}
FixedFrameCurveVecVehicleLeader::~FixedFrameCurveVecVehicleLeader() {

}
