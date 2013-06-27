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

FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prm_pKurokoA_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKurokoA_target) {
    _pFixedFrameSplManuf = (FixedFrameSplineManufacture*)prm_pManufacture;
    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}
FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(GgafDxKurokoA* prm_pKurokoA_target,
                                                           SplineLine* prmpSpl,
                                                           frame prm_spent_frame,
                                                           angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKurokoA_target) {  //nullptr�œn�����ɂ��A_is_created_pManufacture �� false�ɂȂ�

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prmpSpl), prm_spent_frame, prm_angveloRzRyMv);
    _pFixedFrameSplManuf->calculate();//������Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
    _pManufacture = _pFixedFrameSplManuf;

    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}

void FixedFrameSplineKurokoLeader::getPointCoord(int prm_point_index, coord &out_X, coord& out_Y, coord& out_Z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pFixedFrameSplManuf->_sp->_rnum) {
        throwGgafCriticalException("FixedFrameSplineKurokoLeader::getPointCoord �|�C���g�̃C���f�b�N�X�I�[�o�[�B"<<
                                   "�⊮�_��="<<(_pFixedFrameSplManuf->_sp->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
    double dx = _flip_X*pSpl->_X_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_X + _offset_X;
    double dy = _flip_Y*pSpl->_Y_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_Y + _offset_Y;
    double dz = _flip_Z*pSpl->_Z_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_Z + _offset_Z;
    //���̕�ԓ_�ior����_)�Ɉړ����p��������
    if (_option == RELATIVE_DIRECTION) {
        if (_is_leading == false) {
            GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
            _SIN_RzMv_begin = ANG_SIN(pKurokoA_target->_angRzMv);
            _COS_RzMv_begin = ANG_COS(pKurokoA_target->_angRzMv);
            _SIN_RyMv_begin = ANG_SIN(pKurokoA_target->_angRyMv);
            _COS_RyMv_begin = ANG_COS(pKurokoA_target->_angRyMv);
            _X_begin = _pActor_target->_X;
            _Y_begin = _pActor_target->_Y;
            _Z_begin = _pActor_target->_Z;
        }
        //    ���s�ړ� �� Z����] �� Y����]
        //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
        //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
        //    | sinRy                                  , 0                    , cosRy                                   , 0 |
        //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
        out_X = ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) *  _COS_RyMv_begin + dz*_SIN_RyMv_begin) + _X_begin;
        out_Y =  (dx*_SIN_RzMv_begin + dy* _COS_RzMv_begin)                                          + _Y_begin;
        out_Z = ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz*_COS_RyMv_begin) + _Z_begin;
    } else if (_option == RELATIVE_COORD) {
        //���΍��W�^�[�Q�b�g
        out_X = dx + _X_begin;
        out_Y = dy + _Y_begin;
        out_Z = dz + _Z_begin;
    } else { //RELATIVE_DIRECTION
        //��΍��W�^�[�Q�b�g
        out_X = dx;
        out_Y = dy;
        out_Z = dz;
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
    double P0X = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X;
    double P0Y = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y;
    double P0Z = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z;
    _X_begin = _pActor_target->_X;
    _Y_begin = _pActor_target->_Y;
    _Z_begin = _pActor_target->_Z;
    if (_option == RELATIVE_DIRECTION) {
        _SIN_RzMv_begin = ANG_SIN(_pActor_target->_pKurokoA->_angRzMv);
        _COS_RzMv_begin = ANG_COS(_pActor_target->_pKurokoA->_angRzMv);
        _SIN_RyMv_begin = ANG_SIN(_pActor_target->_pKurokoA->_angRyMv);
        _COS_RyMv_begin = ANG_COS(_pActor_target->_pKurokoA->_angRyMv);
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
                                (double)(_pActor_target->_X),
                                (double)(_pActor_target->_Y),
                                (double)(_pActor_target->_Z),
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
        GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
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
