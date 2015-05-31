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
        SplineKurokoLeader(nullptr, prm_pKuroko_target) {  //nullptr�œn�����ɂ��A_is_created_pManufacture �� false�ɂȂ�

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prm_pSpl), prm_spent_frame, prm_angveloRzRyMv);
    _pFixedFrameSplManuf->calculate();//������Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
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
    if (ABS(_distance_to_begin) <= PX_C(1)) {
        //�n�_�ւ̋����������A�Ԉ����B
        //_TRACE_("���x����FixedFrameSplineKurokoLeader::start("<<prm_option<<") _pActor_target="<<_pActor_target->getName()<<
        //    " �����W�`�n�_[0]�ւ̋����� 0 �ł��邽�߁A�����W�`�n�_�ւ̈ړ��v���Z�X�̓J�b�g����܂��B");
        _hosei_frames = _pFixedFrameSplManuf->_frame_of_segment;
        //����ɂ��A_point_index �́A���񂢂��Ȃ�1����n�܂�B
    } else {
        _TRACE_("���x����FixedFrameSplineKurokoLeader::restart("<<_option<<") _pActor_target="<<_pActor_target->getName()<<
            " �����W�`�n�_[0]�ւ̋���("<<_distance_to_begin<<" coord)������Ă��邽�߁A�����W�`�n�_�ւ̈ړ��v���Z�X�Ƃ��ăZ�O�����g���{�P����܂��B"<<
            "���̂��߁A���v�ړ��t���[�����ԂɌ덷(+"<<_pFixedFrameSplManuf->_frame_of_segment<<"�t���[��)�������܂��B���������������܂��B");
        _hosei_frames = 0;
        //����ɂ��A_point_index �́A����0����n�܂�B
    }

}

void FixedFrameSplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
        //���݂̓_INDEX
        _point_index = (_leading_frames+_hosei_frames) / _pFixedFrameSplManuf->_frame_of_segment;
        if ( _point_index == _pFixedFrameSplManuf->_sp->_rnum) {
            if (_cnt_loop == _max_loop) {
                //�I��
                _is_leading = false;
                pKuroko_target->stopTurningMvAng();
                return;
            } else {
                //���[�v
                _cnt_loop++;
                restart();
                _point_index = (_leading_frames+_hosei_frames) / _pFixedFrameSplManuf->_frame_of_segment;
            }
        }

        //�ς���
        if (_prev_point_index != _point_index) {
            _prev_point_index = _point_index;
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            pKuroko_target->turnMvAngTwd(x, y, z,
                                         _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                         _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            if (_point_index == 0) {
                //�����W�ƊJ�n������Ă���B
                //�덷���d���Ȃ��̂� _frame_of_segment �Ŏn�_�Ɉړ����鑬�x��t�^
                pKuroko_target->setMvVelo((velo)(_distance_to_begin / _pFixedFrameSplManuf->_frame_of_segment));
            } else {
                const coord d = UTIL::getDistance(
                                        _pActor_target->_x,
                                        _pActor_target->_y,
                                        _pActor_target->_z,
                                        x, y, z);
                if (_pFixedFrameSplManuf->_paDistance_to[_point_index]*1.1 < d) {
                    //�␳�F�������\�z���J���Ă���̂ŏ����}��(1.1�{�̃X�s�[�h�ɂ���)
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
