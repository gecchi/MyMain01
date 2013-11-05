#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKurokoA* const prm_pKurokoA_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKurokoA_target) {
    _pFixedFrameSplManuf = (FixedFrameSplineManufacture*)prm_pManufacture;
    _sinRzMv_begin = 0;
    _cosRzMv_begin = 0;
    _sinRyMv_begin = 0;
    _cosRyMv_begin = 0;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}
FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(GgafDxKurokoA* const prm_pKurokoA_target,
                                                           SplineLine* prmpSpl,
                                                           frame prm_spent_frame,
                                                           angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKurokoA_target) {  //nullptr�œn�����ɂ��A_is_created_pManufacture �� false�ɂȂ�

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prmpSpl), prm_spent_frame, prm_angveloRzRyMv);
    _pFixedFrameSplManuf->calculate();//������Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
    _pManufacture = _pFixedFrameSplManuf;

    _sinRzMv_begin = 0.0f;
    _cosRzMv_begin = 0.0f;
    _sinRyMv_begin = 0.0f;
    _cosRyMv_begin = 0.0f;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}

void FixedFrameSplineKurokoLeader::getPointCoord(int prm_point_index, coord &out_x, coord& out_y, coord& out_z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pFixedFrameSplManuf->_sp->_rnum) {
        throwGgafCriticalException("FixedFrameSplineKurokoLeader::getPointCoord �|�C���g�̃C���f�b�N�X�I�[�o�[�B"<<
                                   "�⊮�_��="<<(_pFixedFrameSplManuf->_sp->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
    double dx = _flip_x*pSpl->_x_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_x + _offset_x;
    double dy = _flip_y*pSpl->_y_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_y + _offset_y;
    double dz = _flip_z*pSpl->_z_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_z + _offset_z;
    //���̕�ԓ_�ior����_)�Ɉړ����p��������
    if (_option == RELATIVE_DIRECTION) {
        if (_is_leading == false) {
            GgafDxKurokoA* const pKurokoA_target = _pActor_target->_pKurokoA;
            _sinRzMv_begin = ANG_SIN(pKurokoA_target->_angRzMv);
            _cosRzMv_begin = ANG_COS(pKurokoA_target->_angRzMv);
            _sinRyMv_begin = ANG_SIN(pKurokoA_target->_angRyMv);
            _cosRyMv_begin = ANG_COS(pKurokoA_target->_angRyMv);
            if (!_is_fix_start_pos) {
                _x_start = _pActor_target->_x;
                _y_start = _pActor_target->_y;
                _z_start = _pActor_target->_z;
            }
        }
        //    ���s�ړ� �� Z����] �� Y����]
        //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
        //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
        //    | sinRy                                  , 0                    , cosRy                                   , 0 |
        //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
        out_x = ((dx*_cosRzMv_begin + dy*-_sinRzMv_begin) *  _cosRyMv_begin + dz*_sinRyMv_begin) + _x_start;
        out_y =  (dx*_sinRzMv_begin + dy* _cosRzMv_begin)                                          + _y_start;
        out_z = ((dx*_cosRzMv_begin + dy*-_sinRzMv_begin) * -_sinRyMv_begin + dz*_cosRyMv_begin) + _z_start;
    } else if (_option == RELATIVE_COORD) {
        //���΍��W�^�[�Q�b�g
        if (_is_leading == false) {
            if (!_is_fix_start_pos) {
                _x_start = _pActor_target->_x;
                _y_start = _pActor_target->_y;
                _z_start = _pActor_target->_z;
            }
        }
        out_x = dx + _x_start;
        out_y = dy + _y_start;
        out_z = dz + _z_start;
    } else { //RELATIVE_DIRECTION
        //��΍��W�^�[�Q�b�g
        out_x = dx;
        out_y = dy;
        out_z = dz;
    }
}

void FixedFrameSplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pFixedFrameSplManuf) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        restart();
    } else {
        throwGgafCriticalException("FixedFrameSplineKurokoLeader::start Manufacture������܂���B_pActor_target="<<_pActor_target->getName());
    }
}
void FixedFrameSplineKurokoLeader::restart() {
    _leading_frames = 0;
    _hosei_frames = 0;
    _point_index = 0;
    _prev_point_index = -1;
    SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
    double P0X = (_flip_x * pSpl->_x_compute[0] * _pFixedFrameSplManuf->_rate_x) + _offset_x;
    double P0Y = (_flip_y * pSpl->_y_compute[0] * _pFixedFrameSplManuf->_rate_y) + _offset_y;
    double P0Z = (_flip_z * pSpl->_z_compute[0] * _pFixedFrameSplManuf->_rate_z) + _offset_z;
    if (!_is_fix_start_pos) {
        _x_start = _pActor_target->_x;
        _y_start = _pActor_target->_y;
        _z_start = _pActor_target->_z;
    }
    if (_option == RELATIVE_DIRECTION) {
        _sinRzMv_begin = ANG_SIN(_pActor_target->_pKurokoA->_angRzMv);
        _cosRzMv_begin = ANG_COS(_pActor_target->_pKurokoA->_angRzMv);
        _sinRyMv_begin = ANG_SIN(_pActor_target->_pKurokoA->_angRyMv);
        _cosRyMv_begin = ANG_COS(_pActor_target->_pKurokoA->_angRyMv);
        _distance_to_begin = UTIL::getDistance(
                                       0.0  , 0.0  , 0.0  ,
                                       P0X, P0Y, P0Z
                                  );

    } else if (_option == RELATIVE_COORD) {
        _distance_to_begin = UTIL::getDistance(
                                       0.0  , 0.0  , 0.0  ,
                                       P0X, P0Y, P0Z
                                  );
    } else { //ABSOLUTE_COORD
        _distance_to_begin = UTIL::getDistance(
                                (double)(_pActor_target->_x),
                                (double)(_pActor_target->_y),
                                (double)(_pActor_target->_z),
                                P0X, P0Y, P0Z
                             );
    }
    //�n�_�֍s�����ʏ����B
    //�n�_�ւ̋���(_distance_to_begin) ���킩���Ă���̂ŁA
    //
    // �n�_�ւ̑��x = (velo)(_distance_to_begin / _pFixedFrameSplManuf->_fFrame_of_segment)
    //
    //�Ƃ��������A
    //_pFixedFrameSplManuf->_fFrame_of_segment �́A�����W�`�n�_ ��������
    //�v�Z�ŋ��߂Ă���̂ŁA�⊮�_�������Ȃ��ꍇ�A��₳���t���[�����v�̌덷���傫���B
    //�����Ŏn�_�ւ̋���0�Ƃ݂Ȃ���ꍇ�ɂ́A�����W�`�n�_ ���Ȃ������R�g�ɂ���B
    //�����łȂ���Ύd���Ȃ��̂ŁA��₳���t���[�����v�̌덷��F�߂�d�l�Ƃ���B
    if (ABS(_distance_to_begin) <= PX_C(1)) {
        //�n�_�ւ̋����������A�Ԉ����B
        //_TRACE_("���x����FixedFrameSplineKurokoLeader::start("<<prm_option<<") _pActor_target="<<_pActor_target->getName()<<
        //    " �����W�`�n�_[0]�ւ̋����� 0 �ł��邽�߁A�����W�`�n�_�ւ̈ړ��v���Z�X�̓J�b�g����܂��B");
        _hosei_frames = _pFixedFrameSplManuf->_fFrame_of_segment;
        //����ɂ��A_point_index �́A���񂢂��Ȃ�1����n�܂�B
    } else {
        _TRACE_("���x����FixedFrameSplineKurokoLeader::restart("<<_option<<") _pActor_target="<<_pActor_target->getName()<<
            " �����W�`�n�_[0]�ւ̋���("<<_distance_to_begin<<" coord)������Ă��邽�߁A�����W�`�n�_�ւ̈ړ��v���Z�X�Ƃ��ăZ�O�����g���{�P����܂��B"<<
            "���̂��߁A���v�ړ��t���[�����ԂɌ덷(+"<<_pFixedFrameSplManuf->_fFrame_of_segment<<"�t���[��)�������܂��B���������������܂��B");
        _hosei_frames = 0;
        //����ɂ��A_point_index �́A����0����n�܂�B
    }

}

void FixedFrameSplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKurokoA* const pKurokoA_target = _pActor_target->_pKurokoA;
        //���݂̓_INDEX
        _point_index = (_leading_frames+_hosei_frames) / _pFixedFrameSplManuf->_fFrame_of_segment;
        if ( _point_index == _pFixedFrameSplManuf->_sp->_rnum) {
            if (_cnt_loop == _max_loop) {
                //�I��
                _is_leading = false;
                return;
            } else {
                //���[�v
                _cnt_loop++;
                restart();
                _point_index = (_leading_frames+_hosei_frames) / _pFixedFrameSplManuf->_fFrame_of_segment;
            }
        }

        //�ς���
        if (_prev_point_index != _point_index) {
            _prev_point_index = _point_index;
            coord X, Y, Z;
            getPointCoord(_point_index, X, Y, Z);
            pKurokoA_target->turnMvAngTwd(X, Y, Z,
                                          _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                          _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            if (_point_index == 0) {
                //�����W�ƊJ�n������Ă���B
                //�덷���d���Ȃ��̂� _fFrame_of_segment �Ŏn�_�Ɉړ����鑬�x��t�^
                pKurokoA_target->setMvVelo((velo)(_distance_to_begin / _pFixedFrameSplManuf->_fFrame_of_segment));
            } else {
                pKurokoA_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index]);
            }
        }
        _leading_frames++;
    }

}
FixedFrameSplineKurokoLeader::~FixedFrameSplineKurokoLeader() {

}
