#include "jp/ggaf/lib/util/spline/SteppedCoordSplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SteppedCoordSplineKurokoLeader::SteppedCoordSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKuroko* prm_pKuroko_target) :
        SplineLeader(prm_pManufacture, prm_pKuroko_target->_pActor) {
    _pKuroko_target = prm_pKuroko_target;
    _pSteppedSplManuf = (SteppedCoordSplineManufacture*)prm_pManufacture;
    _leading_frames = 0;
    _point_index = -1;
}

SteppedCoordSplineKurokoLeader::SteppedCoordSplineKurokoLeader(GgafDxKuroko* prm_pKuroko_target,
                                                               SplineLine* prm_pSpl):
        SplineLeader(nullptr, prm_pKuroko_target->_pActor) { //nullptr�œn�����ɂ��A_is_created_pManufacture �� false�ɂȂ�
    _pKuroko_target = prm_pKuroko_target;
    _pSteppedSplManuf = NEW SteppedCoordSplineManufacture(NEW SplineSource(prm_pSpl));
    _pSteppedSplManuf->calculate(); //�Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
    _pManufacture = _pSteppedSplManuf; //��ꃁ���o�[�Z�b�g�B�Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
    _leading_frames = 0;
    _point_index = -1;
}

void SteppedCoordSplineKurokoLeader::restart() {
    SplineLeader::restart();
    _leading_frames = 0;
    //�n�_�֍s�����ʏ����B
    if (ABS(_distance_to_begin) <= PX_C(1)) {
        //�n�_�Ƃ̋����������ꍇ(PX_C(1)�ȉ�)�̏ꍇ�A
        //�X�v���C����ԓ_�̑�P�_�ڂ��Ԉ����āA�n�_�̎��̕�ԓ_����X�^�[�g
        _point_index = 0;
    } else {
        //�n�_�Ƃ̋���������Ă���΁A�P�t���[����₵�n�_��
        _point_index = -1;
    }
}

void SteppedCoordSplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
        _point_index++;
        if (_point_index == _pSteppedSplManuf->_sp->_rnum) {
            if (_cnt_loop == _max_loop) {
                //�I��
                _is_leading = false;
                return;
            } else {
                //���[�v
                _cnt_loop++;
                restart();
                _point_index++;
            }
        }
        coord x, y, z;
        getPointCoord(_point_index, x, y, z);
        coord d = UTIL::getDistance(_pActor_target->_x, _pActor_target->_y, _pActor_target->_z, x, y, z);
        pKuroko_target->setMvAngTwd(x, y, z);
        pKuroko_target->setMvVelo(d);
        _leading_frames++;
    }
}

SteppedCoordSplineKurokoLeader::~SteppedCoordSplineKurokoLeader() {
}
