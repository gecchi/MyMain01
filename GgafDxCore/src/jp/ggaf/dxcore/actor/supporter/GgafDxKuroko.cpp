#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

#include <math.h>
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperC.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKuroko::GgafDxKuroko(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {

    _pHelperA = nullptr;
    _pHelperB = nullptr;
    _pHelperC = nullptr;

    for (int ax = 0; ax < 3; ax++) { // i=0:X���A1:Y���A2:Z�� ��\��
        //���ʕ��p
        _angFace[ax] = 0; //0 angle �� �R���̕��p�������Ă���
        //���ʕ��p�̊p���x�i���ʕ��p�̑����j= 0 angle/fream
        _angveloFace[ax] = 0; //1�t���[���ɉ��Z����鐳�ʕ��p�̊p�����B�f�t�H���g�͐��ʕ��p�̊p���������A�܂�U����������B
        //���ʕ��p�̊p���x��� �� 360,000 angle/fream
        _angveloTopFace[ax] = D360ANG; //_angveloFace[n] �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȑ��ʕ��p�ɐU����������o���鎖���Ӗ�����
        //���ʕ��p�̊p���x���� �� -360,000 angle/fream
        _angveloBottomFace[ax] = D360ANG * -1; //_angveloFace[n] �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȑ��ʕ��p�ɐU����������o���鎖���Ӗ�����
        //���ʕ��p�̊p�����x�i�p���x�̑����j �� 0 angle/fream^2
        _angacceFace[ax] = 0; //_angveloFace[n] �̑����B�f�t�H���g�͐��ʕ��p�̊p�����x����

        _angjerkFace[ax] = 0;
        //�ڕW���ʕ��p�ւ̎��������t���O = ����
        _face_ang_targeting_flg[ax] = false;
        //�ڕW���ʕ��p�ւ̎�����~�t���O = ����
        _face_ang_targeting_stop_flg[ax] = false;
        //�ڕW�̐��ʕ��p
        _angTargetFace[ax] = 0; //�ڕW���ʕ��p�ւ̎�������t���O = �����A�̏ꍇ�͖��Ӗ�
        //�ڕW�̐��ʕ��p������~�@�\���L���ɂȂ��]����
        _face_ang_target_allow_way[ax] = TURN_BOTH;
        //�ڕW�̐��ʕ��p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj
        _face_ang_target_allow_velo[ax] = D180ANG;
    }

    //////////////////////////////////////////////////////
    //�L�����̈ړ����p�P�ʃx�N�g��
    _vX = 1.0f;
    _vY = _vZ = 0.0f;
    //�ړ����p��Z����]
    _angRzMv = 0;
    //�ړ����p��Y����]
    _angRyMv = 0;
    //�ړ����x
    _veloMv = 0;
    //�ړ����x��� = 256 px/fream
    _veloTopMv = INT_MAX; //_veloMv �� 256000(=256px) ������ړ��ʂł����Ă��A�����I�ɍ��W������ 256px �ɗ}������B
    //�ړ����x���� = 0   px/fream
    _veloBottomMv = INT_MIN; //_veloMv �� -256000(-256px) �������ړ��ʂ������Ă��A�����I�ɍ��W������ -256000px �ɗ}������B
    //�ړ������x�i�ړ����x�̑����j = 0 px/fream^2
    _accMv = 0; //_veloMv �̑����B�f�t�H���g�͉�������

    //_jerkMv = 0;
    //�ړ����p�iZ����]�j�̊p���x = 0 angle/fream
    _angveloRzMv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iZ����]�j�̊p���x��� = +360,000 angle/fream
    _angveloRzTopMv = D360ANG; //_angveloRzMv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p���x���� = -360,000 angle/fream
    _angveloRzBottomMv = D360ANG * -1; //_angveloRzMv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p�����x = 0 angle/fream^2
    _angacceRzMv = 0; //_angveloRzMv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _angjerkRzMv = 0;
    //�ڕW�ړ����p�iZ����]�j�ւ̎��������t���O = ����
    _mv_ang_rz_target_flg = false;
    //�ڕW�ړ����p�iZ����]�j�ւ̎�����~�t���O = ����
    _mv_ang_rz_target_stop_flg = false;

    //�ڕW�̈ړ����p�iZ����]�j
    _angTargetRzMv = 0;
    //�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ��]����
    _mv_ang_rz_target_allow_way = TURN_BOTH;
    //�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
    _mv_ang_rz_target_allow_velo = D180ANG;
    //�ړ����p�iZ����]�j�ɔ���Z���ʕ��p�̓��������@�\�t���O �� ����
    _relate_RzFaceAng_with_RzMvAng_flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z���ʕ��p�������ɂȂ�B

    //�ړ����p�iY����]�j�̊p���x = 0 angle/fream
    _angveloRyMv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iY����]�j�̊p���x��� = +360,000 angle/fream
    _angveloRyTopMv = D360ANG; //_angveloRyMv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p���x���� = -360,000 angle/fream
    _angveloRyBottomMv = D360ANG * -1; //_angveloRyMv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p�����x = 0 angle/fream^2
    _angacceRyMv = 0; //_angveloRyMv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _angjerkRyMv = 0;
    //�ڕW�ړ����p�iY����]�j�ւ̎��������t���O = ����
    _mv_ang_ry_target_flg = false;
    //�ڕW�ړ����p�iY����]�j�ւ̎�����~�t���O = ����
    _mv_ang_ry_target_stop_flg = false;
    //�ڕW�̈ړ����p�iY����]�j
    _angTargetRyMv = 0;
    //�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ��]����
    _mv_ang_ry_target_allow_way = TURN_BOTH;
    //�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
    _mv_ang_ry_target_allow_velo = D180ANG;
    //�ړ����p�iY����]�j�ɔ���Z���ʕ��p�̓��������@�\�t���O �� ����
    _relate_RyFaceAng_with_RyMvAng_flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z���ʕ��p�������ɂȂ�B

    _taget_face_ang_alltime_flg = false;
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_tx = 0;
    _taget_face_ang_alltime_ty = 0;
    _taget_face_ang_alltime_tz = 0;
    _taget_face_ang_alltime_angVelo = 0;
    _taget_face_ang_alltime_angAcce = 0;
    _taget_face_ang_alltime_way = TURN_CLOSE_TO;
    _taget_face_ang_alltime_optimize_ang = true;

}
GgafDxKurokoHelperA* GgafDxKuroko::helperA() {
    return _pHelperA ? _pHelperA : _pHelperA = NEW GgafDxKurokoHelperA(this);
}
GgafDxKurokoHelperB* GgafDxKuroko::helperB() {
    return _pHelperB ? _pHelperB : _pHelperB = NEW GgafDxKurokoHelperB(this);
}
GgafDxKurokoHelperC* GgafDxKuroko::helperC() {
    return _pHelperC ? _pHelperC : _pHelperC = NEW GgafDxKurokoHelperC(this);
}
void GgafDxKuroko::behave() {
    if (_pHelperA) {
        _pHelperA->behave();
    }
    if (_pHelperB) {
        _pHelperB->behave();
    }
    if (_pHelperC) {
        _pHelperC->behave();
    }
    //���ʕ��p����
    for (axis ax = 0; ax < 3; ax++) {
        if (_face_ang_targeting_flg[ax]) { //�^�[�Q�b�g����������ꍇ
            _angveloFace[ax] += _angacceFace[ax];
            if (_angveloFace[ax] > _angveloTopFace[ax]) {
                _angveloFace[ax] = _angveloTopFace[ax];
            } else if (_angveloFace[ax] < _angveloBottomFace[ax]) {
                _angveloFace[ax] = _angveloBottomFace[ax];
            }
            if (_angveloFace[ax] > 0) { //�����v���̏ꍇ
                angle angDistance = getFaceAngDistance(ax, _angTargetFace[ax], TURN_COUNTERCLOCKWISE);
                if (_angveloFace[ax] > angDistance && _face_ang_target_allow_way[ax] != TURN_CLOCKWISE
                        && _face_ang_target_allow_velo[ax] >= _angveloFace[ax]) {
                    addFaceAng(ax, angDistance);
                    if (_face_ang_targeting_stop_flg[ax]) {
                        _face_ang_targeting_flg[ax] = false; //�t���O��߂��ďI��
                        _face_ang_targeting_stop_flg[ax] = false;
                    }
                } else {
                    addFaceAng(ax, _angveloFace[ax]);
                }
            } else if (_angveloFace[ax] < 0) { //���v���̏ꍇ
                angle angDistance = getFaceAngDistance(ax, _angTargetFace[ax], TURN_CLOCKWISE);
                if (_angveloFace[ax] < angDistance && _face_ang_target_allow_way[ax] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_ang_target_allow_velo[ax] <= _angveloFace[ax]) { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                    addFaceAng(ax, angDistance);
                    if (_face_ang_targeting_stop_flg[ax]) { //��~���ėL��Ȃ��
                        _face_ang_targeting_flg[ax] = false; //�t���O��߂��ďI��
                    }
                } else {
                    addFaceAng(ax, _angveloFace[ax]);
                }
            } else {
                //_angveloFace[ax] == 0
                addFaceAng(ax, 0);
            }

            if (_face_ang_targeting_flg[ax] == false) {
                //�ڕW�����ɓ��B�������̏���
                //_angveloTopFace[ax] = D360ANG; //���ʕ��p�̊p���x��� �� 360,000 angle/fream
                //_angveloBottomFace[ax] = D360ANG * -1; //���ʕ��p�̊p���x���� �� -360,000 angle/fream

                //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
                _angacceFace[ax] = 0; //����]�����p�A�p���x���O��
                setFaceAngVelo(ax, 0); //����]�����p�A�p�����x���O��
            }

        } else {
            //if (_angacceFace[ax] != 0) {
            //�t���[�����̐��ʕ��p����̏���
            _angveloFace[ax] += _angacceFace[ax];
            if (_angveloFace[ax] != 0) {
                addFaceAng(ax, _angveloFace[ax]);
            }
            //}
        }

    }

    //Actor�ɔ��f
    _pActor->_rx = _angFace[AXIS_X];
    _pActor->_ry = _angFace[AXIS_Y];
    _pActor->_rz = _angFace[AXIS_Z];

    ///////////////////////////////////////////////////Mover

    //_accMv += _jerkMv;
    //�ړ������x�̏���
    _veloMv += _accMv;
    if (_veloMv > _veloTopMv) {
        _veloMv = _veloTopMv;
    } else if (_veloMv < _veloBottomMv) {
        _veloMv = _veloBottomMv;
    }

    ///////////
    //�ڕW�ړ����p�iZ����]�j�A���O��������~�@�\�g�p���̏ꍇ
    if (_mv_ang_rz_target_flg) {

        _angveloRzMv += _angacceRzMv;
        setRzMvAngVelo(_angveloRzMv);

        if (_angveloRzMv > 0) { //�����v���̏ꍇ
            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_COUNTERCLOCKWISE);
            if (_angveloRzMv > angDistance && _mv_ang_rz_target_allow_way != TURN_CLOCKWISE
                    && _mv_ang_rz_target_allow_velo >= _angveloRzMv) { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                addRzMvAng(angDistance);
                if (_mv_ang_rz_target_stop_flg) { //��~�w�肠��Ȃ��
                    _mv_ang_rz_target_flg = false; //�t���O��߂��ďI��
                }
            } else {
                addRzMvAng(_angveloRzMv);
            }
        } else if (_angveloRzMv < 0) { //���v���̏ꍇ

            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_CLOCKWISE);
            if (_angveloRzMv < angDistance && _mv_ang_rz_target_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_mv_ang_rz_target_allow_velo <= _angveloRzMv) {
                addRzMvAng(angDistance);
                if (_mv_ang_rz_target_stop_flg) { //��~�w�肠��Ȃ��
                    _mv_ang_rz_target_flg = false; //�t���O��߂��ďI��
                }
            } else {
                addRzMvAng(_angveloRzMv);
            }
        } else {
            addRzMvAng(0);
        }
        if (_mv_ang_rz_target_flg == false) {
            //_angveloRzTopMv = D360ANG; //�ړ����p�iZ����]�j�̊p���x��� �� 360,000 angle/fream
            //_angveloRzBottomMv = D360ANG * -1; //�ړ����p�iZ����]�j�̊p���x���� �� -360,000 angle/fream

            //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
            _angacceRzMv = 0; //Z���ړ������p�A�p�����x���O��
            setRzMvAngVelo(0); //Z���ړ������p�A�p���x���O��
        }

    } else {
        //if (_angacceRzMv != 0) {

        _angacceRzMv += _angjerkRzMv;
        //�t���[�����̈ړ����p�iZ����]�j����̏���
        _angveloRzMv += _angacceRzMv;
        if (_angveloRzMv != 0) {
            addRzMvAng(_angveloRzMv);
        }
        //}
    }
    ////////////////
    //�ڕW�ړ����p�iY����]�j�A���O��������~�@�\�g�p���̏ꍇ
    if (_mv_ang_ry_target_flg) {

        _angveloRyMv += _angacceRyMv;
        setRyMvAngVelo(_angveloRyMv);

        if (_angveloRyMv > 0) { //���݂͔����v���̏ꍇ
            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_COUNTERCLOCKWISE);
            if (_angveloRyMv > angDistance &&
                _mv_ang_ry_target_allow_way != TURN_CLOCKWISE &&
                _mv_ang_ry_target_allow_velo >= _angveloRyMv)
            { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                addRyMvAng(angDistance);
                if (_mv_ang_ry_target_stop_flg) { //��~�w�肠��Ȃ��
                    _mv_ang_ry_target_flg = false; //�t���O��߂��ďI��
                }
            } else {
                addRyMvAng(_angveloRyMv);
            }
        } else if (_angveloRyMv < 0) { //���݂͎��v���̏ꍇ

            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_CLOCKWISE);
            if (_angveloRyMv < angDistance &&
                _mv_ang_ry_target_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_mv_ang_ry_target_allow_velo <= _angveloRyMv)
            {
                addRyMvAng(angDistance);
                if (_mv_ang_ry_target_stop_flg) { //��~�w�肠��Ȃ��
                    _mv_ang_ry_target_flg = false; //�t���O��߂��ďI��
                }
            } else {
                addRyMvAng(_angveloRyMv);
            }
        } else {
            //_angveloRyMv==0
            addRyMvAng(0);
        }
        if (_mv_ang_ry_target_flg == false) {
            //_angveloRyTopMv = D360ANG; //�ړ����p�iY����]�j�̊p���x��� �� 360,000 angle/fream
            //_angveloRyBottomMv = D360ANG*-1; //�ړ����p�iY����]�j�̊p���x���� �� -360,000 angle/fream

            //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
            _angacceRyMv = 0; //Y���ړ������p�A�p�����x���O��
            setRyMvAngVelo(0); //Y���ړ������p�A�p���x���O��
        }

    } else {
        //if (_angacceRyMv != 0) {
        _angacceRyMv += _angjerkRyMv;
        //�t���[�����̈ړ����p�iY����]�j����̏���
        _angveloRyMv += _angacceRyMv;
        if(_angveloRyMv != 0) {
            addRyMvAng(_angveloRyMv);
        }
        //}
    }

    ///////////////
    if (_taget_face_ang_alltime_flg && _face_ang_targeting_flg[AXIS_Z] == false && _face_ang_targeting_flg[AXIS_Y] == false) {
        if (_taget_face_ang_alltime_pActor) {
            keepOnTurningFaceAngTwd(
                    _taget_face_ang_alltime_pActor,
                    _taget_face_ang_alltime_angVelo,
                    _taget_face_ang_alltime_angAcce,
                    _taget_face_ang_alltime_way,
                    _taget_face_ang_alltime_optimize_ang);
        } else {
            keepOnTurningFaceAngTwd(
                    _taget_face_ang_alltime_pActor->_x,
                    _taget_face_ang_alltime_pActor->_y,
                    _taget_face_ang_alltime_pActor->_z,
                    _taget_face_ang_alltime_angVelo,
                    _taget_face_ang_alltime_angAcce,
                    _taget_face_ang_alltime_way,
                    _taget_face_ang_alltime_optimize_ang);
        }

    }
    //Actor�ɔ��f
    _pActor->_x += (coord)(_vX * _veloMv);
    _pActor->_y += (coord)(_vY * _veloMv);
    _pActor->_z += (coord)(_vZ * _veloMv);
}

void GgafDxKuroko::setFaceAng(axis prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = UTIL::simplifyAng(prm_angFace);
}

void GgafDxKuroko::setFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    UTIL::convVectorToRzRy(
                   prm_tx - _pActor->_x,
                   prm_ty - _pActor->_y,
                   prm_tz - _pActor->_z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDxKuroko::addFaceAng(axis prm_axis, angle prm_angDistance) {
    angle angOffsetrot_FaceAng;
    angOffsetrot_FaceAng = prm_angDistance;
    if (_angveloBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAng = _angveloBottomFace[prm_axis];
    } else if (prm_angDistance > _angveloTopFace[prm_axis]) {
        angOffsetrot_FaceAng = _angveloTopFace[prm_axis];
    }
    setFaceAng(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAng);
}

void GgafDxKuroko::setFaceAngVelo(axis prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloTopFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloTopFace[prm_axis];
    } else if (prm_angveloRot < _angveloBottomFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloBottomFace[prm_axis];
    } else {
        _angveloFace[prm_axis] = prm_angveloRot;
    }
}

void GgafDxKuroko::setFaceAngVelo(angvelo prm_axis_x_angveloRot,
                                   angvelo prm_axis_y_angveloRot,
                                   angvelo prm_axis_z_angveloRot) {
    setFaceAngVelo(AXIS_X, prm_axis_x_angveloRot);
    setFaceAngVelo(AXIS_Y, prm_axis_y_angveloRot);
    setFaceAngVelo(AXIS_Z, prm_axis_z_angveloRot);
}

void GgafDxKuroko::forceFaceAngVeloRange(axis prm_axis,
                                          angvelo prm_angveloRot01,
                                          angvelo prm_angveloRot02) {
    if (prm_angveloRot01 < prm_angveloRot02) {
        _angveloTopFace[prm_axis] = prm_angveloRot02;
        _angveloBottomFace[prm_axis] = prm_angveloRot01;
    } else {
        _angveloTopFace[prm_axis] = prm_angveloRot01;
        _angveloBottomFace[prm_axis] = prm_angveloRot02;
    }
    setFaceAngVelo(prm_axis, _angveloFace[prm_axis]); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKuroko::setFaceAngAcce(axis prm_axis, angacce prm_angacceRot) {
    _angacceFace[prm_axis] = prm_angacceRot;
}

void GgafDxKuroko::setStopTargetFaceAngTwd(axis prm_axis,
                                            coord prm_tx,
                                            coord prm_ty,
                                            int prm_way_allow,
                                            angvelo prm_angveloAllowRyMv) {
    setStopTargetFaceAng(
      prm_axis,
      UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
      prm_way_allow,
      prm_angveloAllowRyMv
    );
}

void GgafDxKuroko::setStopTargetFaceAng(axis prm_axis,
                                         angle prm_angTargetRot,
                                         int prm_way_allow,
                                         angvelo prm_angveloAllow) {
    _face_ang_targeting_flg[prm_axis] = true;
    _face_ang_targeting_stop_flg[prm_axis] = true;
    _angTargetFace[prm_axis] = UTIL::simplifyAng(prm_angTargetRot);
    _face_ang_target_allow_way[prm_axis] = prm_way_allow;
    _face_ang_target_allow_velo[prm_axis] = prm_angveloAllow;
}

angle GgafDxKuroko::getFaceAngDistance(axis prm_axis, coord prm_tx, coord prm_ty, int prm_way) {
    return getFaceAngDistance(
               prm_axis,
               UTIL::getAngle2D(prm_tx-(_pActor->_x), prm_ty-(_pActor->_y)),
               prm_way);
}

angle GgafDxKuroko::getFaceAngDistance(axis prm_axis, angle prm_angTargetRot, int prm_way) {
    angle _angTargetRot;
    _angTargetRot = UTIL::simplifyAng(prm_angTargetRot);
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < D180ANG) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return -1 * (_angFace[prm_axis] - _angTargetRot);
            } else if (_angTargetRot == _angFace[prm_axis]) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot < _angFace[prm_axis]
                    + D180ANG) {
                return _angTargetRot - _angFace[prm_axis];
            } else if (_angTargetRot == _angFace[prm_axis] + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return D180ANG;
            } else if (_angFace[prm_axis] + D180ANG < _angTargetRot && _angTargetRot <= D360ANG) {
                return -1 * (_angFace[prm_axis] + (D360ANG - _angTargetRot));
            } else {
                //��������
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDxKuroko::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angFace[prm_axis] && _angFace[prm_axis] <= D360ANG) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis] - D180ANG) {
                return D360ANG - _angFace[prm_axis] + _angTargetRot;
            } else if (_angTargetRot == _angFace[prm_axis] - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -D180ANG;
            } else if (_angFace[prm_axis] - D180ANG < _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return -1 * (_angFace[prm_axis] - _angTargetRot);
            } else if (_angFace[prm_axis] == _angTargetRot) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot <= D360ANG) {
                return _angTargetRot - _angFace[prm_axis];
            } else {
                //��������
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDxKuroko::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < D180ANG) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return D360ANG - _angFace[prm_axis] + _angTargetRot;
            } else if (_angTargetRot == _angFace[prm_axis]) {
                //�d�Ȃ��Ă�ꍇ
                return D360ANG;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot < _angFace[prm_axis] + D180ANG) {
                return -1 * ( _angFace[prm_axis] + (D360ANG -_angTargetRot));
            } else if (_angTargetRot == _angFace[prm_axis] + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return D180ANG;
            } else if (_angFace[prm_axis] + D180ANG < _angTargetRot && _angTargetRot <= D360ANG) {
                return _angTargetRot - _angFace[prm_axis];
            } else {
                //��������
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDxKuroko::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angFace[prm_axis] && _angFace[prm_axis] <= D360ANG) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis] - D180ANG) {
                return -1 * (_angTargetRot - _angFace[prm_axis]);
            } else if (_angTargetRot == _angFace[prm_axis] - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return -D180ANG;
            } else if (_angFace[prm_axis] - D180ANG < _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return (D360ANG - _angFace[prm_axis]) + _angTargetRot;
            } else if (_angFace[prm_axis] == _angTargetRot) {
                //�d�Ȃ��Ă�ꍇ
                return -D360ANG;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot <= D360ANG) {
                return (_angFace[prm_axis] + (D360ANG - _angTargetRot)) ;
            } else {
                //��������
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDxKuroko::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return (_angTargetRot - _angFace[prm_axis]);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] <= D360ANG) {
            return D360ANG - _angFace[prm_axis] + _angTargetRot;
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDxKuroko::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(5)�B_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return -1 * (_angFace[prm_axis] + D360ANG - _angTargetRot);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] <= D360ANG) {
            return -1 * (_angFace[prm_axis] - _angTargetRot);
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDxKuroko::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(6)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDxKuroko::getFaceAngDistance() ���̂�����p�̋��������߂�܂���Bprm_way�͐������ł����H(2)�Bprm_way="<<prm_way<<" _pActor="<<_pActor->getName());
}

void GgafDxKuroko::forceMvVeloRange(velo prm_velo) {
    forceMvVeloRange(-prm_velo, prm_velo);
}

void GgafDxKuroko::forceMvVeloRange(velo prm_veloMv01, velo prm_veloMv02) {
    if (prm_veloMv01 < prm_veloMv02) {
        _veloTopMv = prm_veloMv02;
        _veloBottomMv = prm_veloMv01;
    } else {
        _veloTopMv = prm_veloMv01;
        _veloBottomMv = prm_veloMv02;
    }
    setMvVelo(_veloMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKuroko::setMvVelo(velo prm_veloMv) {
    if (prm_veloMv > _veloTopMv) {
        _veloMv = _veloTopMv;
    } else if (prm_veloMv < _veloBottomMv) {
        _veloMv = _veloBottomMv;
    } else {
        _veloMv = prm_veloMv;
    }
}

void GgafDxKuroko::addMvVelo(velo prm_veloMv_Offset) {
    setMvVelo(_veloMv + prm_veloMv_Offset);
}

void GgafDxKuroko::setMvAcce(int prm_acceMove) {
    _accMv = prm_acceMove;
}

frame GgafDxKuroko::setMvAcceToStop(coord prm_target_distance) {
    double acc = UTIL::getAcceToStop(prm_target_distance, _veloMv);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _accMv = acc;
    return (frame)((2.0*prm_target_distance) / _veloMv); //�g�p�t���[����
}

frame GgafDxKuroko::setFaceAngAcceToStop(axis prm_axis, angle prm_target_angle_distance) {
    double acc = UTIL::getAcceToStop(prm_target_angle_distance, _angveloFace[prm_axis]);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacceFace[prm_axis] = acc;
    return (frame)((2.0*prm_target_angle_distance) / _angveloFace[prm_axis]); //�g�p�t���[����
}

frame GgafDxKuroko::setMvAcceByD(coord prm_target_distance, velo prm_target_velo) {
    double acc = UTIL::getAcceByVd(_veloMv, prm_target_velo, prm_target_distance);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _accMv = acc;
    return (frame)((1.0*prm_target_velo - _veloMv) / acc); //�g�p�t���[����
}
frame GgafDxKuroko::setFaceAngAcceByD(axis prm_axis, angle prm_target_angle_distance, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByVd(prm_target_angvelo, prm_target_angle_distance, _angveloFace[prm_axis]);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacceFace[prm_axis] = acc;
    return (frame)((1.0*prm_target_angvelo - _angveloFace[prm_axis]) / acc); //�g�p�t���[����
}
    // �y�⑫�z
    // V0 <= 0  ����  Vt <= 0 �ꍇ�A���邢��  V0 >= 0  ����  Vt >= 0  �ꍇ�́AD(�ڕW����)����L���Ŗ��Ȃ��B
    // �ł�
    // V0 < 0   ����  Vt > 0  �ꍇ�A���邢��  V0 > 0   ����  Vt < 0   �ꍇ�́A�ǂ��Ȃ邩�H
    //
    //    ���x(v)
    //     ^        a:�����x
    //     |        D:�ړ������i�ڕW���B���x�ɒB����܂łɔ�₷�����j
    //     |       V0:�����_�̑��x
    //     |       Vt:�ڕW���B���x
    //     |       Te:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
    //  V0 |
    //     |�_
    //     |  �_  �X����a
    //     | D1 �_
    //     |      �_ Tc     Te
    //   --+--------�_------+---> ����(t)
    //   0 |          �_ D2 |
    //     |            �_  |
    //   Vt|..............�_|
    //     |
    //
    //    D ��S�̂̈ړ������Ƃ���
    //    D = D1 - D2 , v = 0 �� t �� Tc �Ƃ���
    //
    //    D1 = (1/2) V0 Tc
    //    D2 = (1/2) -Vt (Te - Tc)
    //    D = D1 - D2 ���
    //    D = (1/2) V0 Tc -  { (1/2) -Vt (Te - Tc) }
    //      = (V0 Tc + Vt Te - Vt Tc) / 2    �E�E�E�@
    //
    //    ���� v = a t + V0 �ɂ����� v = 0 �� t = Tc �ł���̂�
    //    0 = a Tc + V0
    //    Tc = -V0 / a
    //    ����� �@ �֑��
    //    D = (V0 (-V0 / a) + Vt Te - Vt (-V0 / a)) / 2 �E�E�E�A
    //    �܂� a = (Vt - V0) / Te �ł���̂�
    //    Te = (Vt - V0) / a ����� �A �֑��
    //    �����
    //    D = (V0 (-V0 / a) + Vt ((Vt - V0) / a) - Vt (-V0 / a)) / 2
    //
    //    a �ɂ��ĉ���
    //
    //    D = ( -(V0^2) / a  + (Vt (Vt - V0)) / a + (Vt V0) / a) / 2
    //    a D = { -(V0^2) + (Vt (Vt - V0)) + (Vt V0) } / 2
    //    a = { -(V0^2) + (Vt (Vt - V0)) + (Vt V0) } / 2D
    //    a = (-(V0^2) + Vt^2 - Vt V0 + Vt V0) / 2D
    //    a = (Vt^2 - V0^2) / 2D
    //
    //    ���� a = (Vt^2 - V0^2) / 2D �ƂȂ�̂�
    //    V0 <= 0  ����  Vt <= 0 �ꍇ�A���邢��  V0 >= 0  ����  Vt >= 0  �ꍇ�Ɠ����ł���

coord GgafDxKuroko::setMvAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _veloMv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _accMv = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_veloMv + prm_target_velo) * prm_target_frames) / 2 ;
}
angle GgafDxKuroko::setFaceAngAcceByT(axis prm_axis, frame prm_target_frames, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _angveloFace[prm_axis], prm_target_angvelo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacceFace[prm_axis] = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_angveloFace[prm_axis] + prm_target_angvelo) * prm_target_frames) / 2 ;
}

void GgafDxKuroko::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _angRzMv) {
        _angRzMv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDxKuroko::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRzBottomMv > prm_angDistance) {
        angOffset = _angveloRzBottomMv;
    } else if (prm_angDistance > _angveloRzTopMv) {
        angOffset = _angveloRzTopMv;
    }
    setRzMvAng(_angRzMv + angOffset);
}

void GgafDxKuroko::setRzMvAngVelo(angvelo prm_angveloRzMv) {
    if (prm_angveloRzMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzMv;
    }
}

void GgafDxKuroko::setRzMvAngAcce(angacce prm_angacceRzMv) {
    _angacceRzMv = prm_angacceRzMv;
}

void GgafDxKuroko::forceRzMvAngVeloRange(angvelo prm_angveloRzMv01,
                                          angvelo prm_angveloRzMv02) {
    if (prm_angveloRzMv01 < prm_angveloRzMv02) {
        _angveloRzTopMv = prm_angveloRzMv02;
        _angveloRzBottomMv = prm_angveloRzMv01;
    } else {
        _angveloRzTopMv = prm_angveloRzMv01;
        _angveloRzBottomMv = prm_angveloRzMv02;
    }
    setRzMvAngVelo(_angveloRzMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKuroko::setStopTargetRzMvAng(angle prm_angTargetRzMv,
                                         int prm_way_allow,
                                         angvelo prm_angveloAllowRyMv) {
    _mv_ang_rz_target_flg = true;
    _mv_ang_rz_target_stop_flg = true;
    _angTargetRzMv = UTIL::simplifyAng(prm_angTargetRzMv);
    _mv_ang_rz_target_allow_way = prm_way_allow;
    _mv_ang_rz_target_allow_velo = prm_angveloAllowRyMv;
}

angle GgafDxKuroko::getRzMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRzMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)), prm_way);
}

angle GgafDxKuroko::getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way) {
    angle angTargetRzMv = UTIL::simplifyAng(prm_angTargetRzMv);
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        if (0 <= _angRzMv && _angRzMv < D180ANG) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv) {
                return -1 * (_angRzMv - angTargetRzMv);
            } else if (angTargetRzMv == _angRzMv) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv < _angRzMv + D180ANG) {
                return angTargetRzMv - _angRzMv;
            } else if (angTargetRzMv == _angRzMv + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return D180ANG;
            } else if (_angRzMv + D180ANG < angTargetRzMv && angTargetRzMv <= D360ANG) {
                return -1 * (_angRzMv + (D360ANG - angTargetRzMv));
            } else {
                //��������
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDxKuroko::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angRzMv && _angRzMv <= D360ANG) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv - D180ANG) {
                return D360ANG - _angRzMv + angTargetRzMv;
            } else if (angTargetRzMv == _angRzMv - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -D180ANG;
            } else if (_angRzMv - D180ANG < angTargetRzMv && angTargetRzMv < _angRzMv) {
                return -1 * (_angRzMv - angTargetRzMv);
            } else if (_angRzMv == angTargetRzMv) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv <= D360ANG) {
                return angTargetRzMv - _angRzMv;
            } else {
                //��������
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDxKuroko::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        if (0 <= _angRzMv && _angRzMv < D180ANG) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv) {
                return D360ANG - _angRzMv + angTargetRzMv;
            } else if (angTargetRzMv == _angRzMv) {
                //�d�Ȃ��Ă�ꍇ
                return D360ANG;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv < _angRzMv + D180ANG) {
                return -1*(_angRzMv + (D360ANG-angTargetRzMv));
            } else if (angTargetRzMv == _angRzMv + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return D180ANG;
            } else if (_angRzMv + D180ANG < angTargetRzMv && angTargetRzMv <= D360ANG) {
                return angTargetRzMv - _angRzMv;
            } else {
                //��������
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDxKuroko::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angRzMv && _angRzMv <= D360ANG) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv - D180ANG) {
                return  -1*(_angRzMv - angTargetRzMv);
            } else if (angTargetRzMv == _angRzMv - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -D180ANG;
            } else if (_angRzMv - D180ANG < angTargetRzMv && angTargetRzMv < _angRzMv) {
                return _angRzMv + (D360ANG - angTargetRzMv);
            } else if (_angRzMv == angTargetRzMv) {
                //�d�Ȃ��Ă�ꍇ
                return -D360ANG;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv <= D360ANG) {
                return angTargetRzMv + (D360ANG - _angRzMv);
            } else {
                //��������
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDxKuroko::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return (angTargetRzMv - _angRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv <= D360ANG) {
            return D360ANG - _angRzMv + angTargetRzMv;
        } else if (_angRzMv == angTargetRzMv) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDxKuroko::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(5)�B_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return -1 * (_angRzMv + D360ANG - angTargetRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv <= D360ANG) {
            return -1 * (_angRzMv - angTargetRzMv);
        } else if (_angRzMv == angTargetRzMv) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDxKuroko::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(6)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
    throwGgafCriticalException("GgafDxKuroko::getRzMvAngDistance() ���̂�����p�̋��������߂�܂���(1)�B_pActor="<<_pActor->getName());
}


//void GgafDxKuroko::setRyMvAngTwd(coord prm_tx, coord prm_ty) {
//    setRyMvAng(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)));
//}

void GgafDxKuroko::setRyMvAng(angle prm_ang) {
    if (prm_ang != _angRyMv) {
        _angRyMv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKuroko::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRyBottomMv > prm_angDistance) {
        angOffset = _angveloRyBottomMv;
    } else if (prm_angDistance > _angveloRyTopMv) {
        angOffset = _angveloRyTopMv;
    }
    setRyMvAng(_angRyMv + angOffset);
}

void GgafDxKuroko::setRyMvAngVelo(angvelo prm_angveloRyMv) {
    if (prm_angveloRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRyMv;
    }
}

void GgafDxKuroko::setRyMvAngAcce(angacce prm_angacceRyMv) {
    _angacceRyMv = prm_angacceRyMv;
}

void GgafDxKuroko::forceRyMvAngVeloRange(angvelo prm_angveloRyMv01,
                                          angvelo prm_angveloRyMv02) {
    if (prm_angveloRyMv01 < prm_angveloRyMv02) {
        _angveloRyTopMv = prm_angveloRyMv02;
        _angveloRyBottomMv = prm_angveloRyMv01;
    } else {
        _angveloRyTopMv = prm_angveloRyMv01;
        _angveloRyBottomMv = prm_angveloRyMv02;
    }
    setRyMvAngVelo(_angveloRyMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKuroko::forceRzRyMvAngVeloRange(angvelo prm_angveloRzRyMv01, angvelo prm_angveloRzRyMv02) {
    if (prm_angveloRzRyMv01 < prm_angveloRzRyMv02) {
        _angveloRzTopMv = prm_angveloRzRyMv02;
        _angveloRzBottomMv = prm_angveloRzRyMv01;
        _angveloRyTopMv = prm_angveloRzRyMv02;
        _angveloRyBottomMv = prm_angveloRzRyMv01;
    } else {
        _angveloRzTopMv = prm_angveloRzRyMv01;
        _angveloRzBottomMv = prm_angveloRzRyMv02;
        _angveloRyTopMv = prm_angveloRzRyMv01;
        _angveloRyBottomMv = prm_angveloRzRyMv02;
    }
    setRzMvAngVelo(_angveloRzMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
    setRyMvAngVelo(_angveloRyMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}
void GgafDxKuroko::setRzRyMvAngVelo(angvelo prm_angveloRzRyMv) {
    if (prm_angveloRzRyMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzRyMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzRyMv;
    }
    if (prm_angveloRzRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRzRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRzRyMv;
    }
}
void GgafDxKuroko::setRzRyMvAngAcce(angacce prm_angacceRzRyMv) {
    _angacceRzMv = prm_angacceRzRyMv;
    _angacceRyMv = prm_angacceRzRyMv;
}
void GgafDxKuroko::setRzRyMvAngAcce(angacce prm_angacceRzMv, angacce prm_angacceRyMv) {
    _angacceRzMv = prm_angacceRzMv;
    _angacceRyMv = prm_angacceRyMv;
}

void GgafDxKuroko::setRzRyMvAngVelo(angvelo prm_angveloRzMv, angvelo prm_angveloRyMv) {
    if (prm_angveloRzMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzMv;
    }
    if (prm_angveloRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRyMv;
    }
}

void GgafDxKuroko::setStopTargetRyMvAng(angle prm_angTargetRyMv,
                                         int prm_way_allow,
                                         angvelo prm_angveloAllowRyMv) {
    _mv_ang_ry_target_flg = true;
    _mv_ang_ry_target_stop_flg = true;
    _angTargetRyMv = UTIL::simplifyAng(prm_angTargetRyMv);
    _mv_ang_ry_target_allow_way = prm_way_allow;
    _mv_ang_ry_target_allow_velo = prm_angveloAllowRyMv;
}

angle GgafDxKuroko::getRyMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRyMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
                                        prm_way);
}

angle GgafDxKuroko::getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way) {
    angle angTargetRyMv;
    angTargetRyMv = UTIL::simplifyAng(prm_angTargetRyMv);
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        if (0 <= _angRyMv && _angRyMv < D180ANG) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv) {
                return -1 * (_angRyMv - angTargetRyMv);
            } else if (angTargetRyMv == _angRyMv) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv < _angRyMv + D180ANG) {
                return angTargetRyMv - _angRyMv;
            } else if (angTargetRyMv == _angRyMv + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return D180ANG;
            } else if (_angRyMv + D180ANG < angTargetRyMv && angTargetRyMv <= D360ANG) {
                return -1 * (_angRyMv + (D360ANG - angTargetRyMv));
            } else {
                //��������
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDxKuroko::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angRyMv && _angRyMv <= D360ANG) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv - D180ANG) {
                return D360ANG - _angRyMv + angTargetRyMv;
            } else if (angTargetRyMv == _angRyMv - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -D180ANG;
            } else if (_angRyMv - D180ANG < angTargetRyMv && angTargetRyMv < _angRyMv) {
                return -1 * (_angRyMv - angTargetRyMv);
            } else if (_angRyMv == angTargetRyMv) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv <= D360ANG) {
                return angTargetRyMv - _angRyMv;
            } else {
                //��������
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDxKuroko::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        if (0 <= _angRyMv && _angRyMv < D180ANG) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv) {
                return D360ANG - _angRyMv + angTargetRyMv;
            } else if (angTargetRyMv == _angRyMv) {
                //�d�Ȃ��Ă�ꍇ
                return D360ANG;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv < _angRyMv + D180ANG) {
                return -1*(_angRyMv + (D360ANG-angTargetRyMv));
            } else if (angTargetRyMv == _angRyMv + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return D180ANG;
            } else if (_angRyMv + D180ANG < angTargetRyMv && angTargetRyMv <= D360ANG) {
                return angTargetRyMv - _angRyMv;
            } else {
                //��������
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDxKuroko::getRyMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angRyMv && _angRyMv <= D360ANG) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv - D180ANG) {
                return  -1*(_angRyMv - angTargetRyMv);
            } else if (angTargetRyMv == _angRyMv - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return -D180ANG;
            } else if (_angRyMv - D180ANG < angTargetRyMv && angTargetRyMv < _angRyMv) {
                return _angRyMv + (D360ANG - angTargetRyMv);
            } else if (_angRyMv == angTargetRyMv) {
                //�d�Ȃ��Ă�ꍇ
                return -D360ANG;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv <= D360ANG) {
                return angTargetRyMv + (D360ANG - _angRyMv);
            } else {
                //��������
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDxKuroko::getRyMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return (angTargetRyMv - _angRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv <= D360ANG) {
            return D360ANG - _angRyMv + angTargetRyMv;
        } else if (_angRyMv == angTargetRyMv) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDxKuroko::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(5)�B_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return -1 * (_angRyMv + D360ANG - angTargetRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv <= D360ANG) {
            return -1 * (_angRyMv - angTargetRyMv);
        } else if (_angRyMv == angTargetRyMv) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDxKuroko::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(6)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
    throwGgafCriticalException("GgafDxKuroko::getRyMvAngDistance() ���̂�����p�̋��������߂�܂���(1)�B_pActor="<<_pActor->getName());
}

void GgafDxKuroko::getRzRyMvAngDistanceTwd(angle prm_target_angRz, angle prm_target_angRy, int prm_way,
                                             angle& out_d_angRz, angle& out_d_angRy) {
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        //�ڕW�ɓ��B���邽�߂ɂ́A��������ɂQ�p�^�[������B
        //���ꂼ�ꋅ�ʏ�̂Q�_�̋������ȈՋߎ��l�i���x�D��̂��߁j�Ŕ�r���A�߂��Ǝv����ق����̗p����B
        angle d1_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOSE_TO); //Rz�̍�
        angle d1_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) { //���߂������̗p
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) {
        angle d1_angRz = getRzMvAngDistance(prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getRyMvAngDistance(prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getRzMvAngDistance(prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 >= d2) { //��艓�������̗p
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        angle d1_angRz = getRzMvAngDistance(prm_target_angRz, TURN_COUNTERCLOCKWISE);
        angle d1_angRy = getRyMvAngDistance(prm_target_angRy, TURN_COUNTERCLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getRzMvAngDistance(prm_target_angRz, TURN_COUNTERCLOCKWISE);
        angle d2_angRy = getRyMvAngDistance(prm_target_angRy, TURN_COUNTERCLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        angle d1_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOCKWISE);
        angle d1_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOCKWISE);
        angle d2_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else {
        //��������
        throwGgafCriticalException("GgafDxKuroko::getRzRyMvAngDistanceTwd() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDxKuroko::getRzRyFaceAngDistanceTwd(angle prm_target_angRz, angle prm_target_angRy,int prm_way,
                                               angle& out_d_angRz, angle& out_d_angRy) {
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }

    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 >= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_COUNTERCLOCKWISE);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_COUNTERCLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_COUNTERCLOCKWISE);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_COUNTERCLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOCKWISE);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOCKWISE);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else {
        //��������
        throwGgafCriticalException("GgafDxKuroko::getRzRyMvAngDistanceTwd() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDxKuroko::setRzRyMvAng(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMv || prm_angRy !=_angRyMv ) {
        _angRzMv = UTIL::simplifyAng(prm_angRz);
        _angRyMv = UTIL::simplifyAng(prm_angRy);
        UTIL::convRzRyToVector(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKuroko::setRzRyMvAng_by_RyRz(angle prm_angRyRz_Ry, angle prm_angRyRz_Rz) {
    angle RyRz_Ry = UTIL::simplifyAng(prm_angRyRz_Ry);
    angle RyRz_Rz = UTIL::simplifyAng(prm_angRyRz_Rz);
    float out_vY, out_vZ;
    UTIL::convRzRyToVector(RyRz_Ry, D360ANG-RyRz_Rz, _vX, out_vY, out_vZ);
    _vY = -1.0f*out_vZ;
    _vZ = out_vY;
    UTIL::convVectorToRzRy(_vX, _vZ, _vY, _angRzMv, _angRyMv);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}


void GgafDxKuroko::setMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    UTIL::convVectorToRzRy(prm_tx - _pActor->_x,
                           prm_ty - _pActor->_y,
                           prm_tz - _pActor->_z,
                           _vX, _vY, _vZ,
                           _angRzMv, _angRyMv );
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKuroko::reverseMvAng() {
    _vX = -_vX;
    _vY = -_vY;
    _vZ = -_vZ;
    _angRzMv = UTIL::simplifyAng(_angRzMv-D180ANG);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDxKuroko::setStopTargetMvAngTwd(GgafDxGeometricActor* prm_pActor_Target) {
    setStopTargetMvAngTwd(
        prm_pActor_Target->_x,
        prm_pActor_Target->_y,
        prm_pActor_Target->_z
    );
}

void GgafDxKuroko::setStopTargetMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    angle angRz_Target;
    angle angRy_Target;
    float dummy1, dummy2, dummy3;

    UTIL::convVectorToRzRy(
                   prm_tx - _pActor->_x,
                   prm_ty - _pActor->_y,
                   prm_tz - _pActor->_z,
                   dummy1,
                   dummy2,
                   dummy3,
                   angRz_Target,
                   angRy_Target
                 );
    setStopTargetRzMvAng(angRz_Target);
    setStopTargetRyMvAng(angRy_Target);
}

void GgafDxKuroko::turnRzRyFaceAngTo(angle prm_angRz_Target, angle prm_angRy_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    if (prm_optimize_ang) {
        getRzRyFaceAngDistanceTwd(prm_angRz_Target, prm_angRy_Target,prm_way,
                                   out_d_angRz, out_d_angRy);
    } else {
        out_d_angRz = getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way);
        out_d_angRy = getFaceAngDistance(AXIS_Y, prm_angRy_Target, prm_way);
    }
    double drz = ABS(out_d_angRz);
    double dry = ABS(out_d_angRy);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_angRz > 0) {
            setFaceAngVelo(AXIS_Z, prm_angVelo);
            setFaceAngAcce(AXIS_Z, prm_angAcce);
        } else {
            setFaceAngVelo(AXIS_Z, -prm_angVelo);
            setFaceAngAcce(AXIS_Z, -prm_angAcce);
        }
        if (out_d_angRy > 0) {
            setFaceAngVelo(AXIS_Y, prm_angVelo*drr);
            setFaceAngAcce(AXIS_Y, prm_angAcce*drr);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angVelo*drr);
            setFaceAngAcce(AXIS_Y, -prm_angAcce*drr);
        }
    } else {
        double drr = drz / dry ;
        if (out_d_angRz > 0) {
            setFaceAngVelo(AXIS_Z, prm_angVelo*drr);
            setFaceAngAcce(AXIS_Z, prm_angAcce*drr);
        } else {
            setFaceAngVelo(AXIS_Z, -prm_angVelo*drr);
            setFaceAngAcce(AXIS_Z, -prm_angAcce*drr);
        }
        if (out_d_angRy > 0) {
            setFaceAngVelo(AXIS_Y, prm_angVelo);
            setFaceAngAcce(AXIS_Y, prm_angAcce);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angVelo);
            setFaceAngAcce(AXIS_Y, -prm_angAcce);
        }
    }

    setStopTargetFaceAng(AXIS_Z, prm_angRz_Target);
    setStopTargetFaceAng(AXIS_Y, prm_angRy_Target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKuroko::turnFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                   angvelo prm_angVelo, angacce prm_angAcce,
                                   int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    UTIL::convVectorToRzRy(prm_tx - _pActor->_x,
                           prm_ty - _pActor->_y,
                           prm_tz - _pActor->_z,
                           out_angRz_Target,
                           out_angRy_Target);

    turnRzRyFaceAngTo(out_angRz_Target, out_angRy_Target,
                      prm_angVelo, prm_angAcce,
                      prm_way, prm_optimize_ang);
}


void GgafDxKuroko::turnFaceAng(axis prm_axis,
                               angle prm_angular_distance,
                               angvelo prm_angVelo, angacce prm_angAcce) {
    int s = SGN(prm_angular_distance);
    setFaceAngVelo(prm_axis, ABS(prm_angVelo)*s);
    setFaceAngAcce(prm_axis, ABS(prm_angAcce)*s);
    setStopTargetFaceAng(prm_axis, _angFace[prm_axis] + prm_angular_distance);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}


void GgafDxKuroko::turnRzFaceAngTo(angle prm_angRz_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way) {
    if (getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Z, prm_angVelo);
        setFaceAngAcce(AXIS_Z, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Z, -prm_angVelo);
        setFaceAngAcce(AXIS_Z, -prm_angAcce);
    }
    setStopTargetFaceAng(AXIS_Z, prm_angRz_Target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKuroko::turnRyFaceAngTo(angle prm_angRy_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way) {
    if (getFaceAngDistance(AXIS_Y, prm_angRy_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Y, prm_angVelo);
        setFaceAngAcce(AXIS_Y, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Y, -prm_angVelo);
        setFaceAngAcce(AXIS_Y, -prm_angAcce);
    }
    setStopTargetFaceAng(AXIS_Y, prm_angRy_Target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKuroko::spinRxFaceAngTo(angle prm_angRx_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way) {
    if (getFaceAngDistance(AXIS_X, prm_angRx_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_X, prm_angVelo);
        setFaceAngAcce(AXIS_X, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_X, -prm_angVelo);
        setFaceAngAcce(AXIS_X, -prm_angAcce);
    }
    setStopTargetFaceAng(AXIS_X, prm_angRx_Target);
}

void GgafDxKuroko::turnRzRyMvAngTo(angle prm_angRz_Target, angle prm_angRy_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    if (prm_optimize_ang) {
        getRzRyMvAngDistanceTwd(prm_angRz_Target, prm_angRy_Target,prm_way,
                               out_d_angRz, out_d_angRy);
    } else {
        out_d_angRz = getRzMvAngDistance(prm_angRz_Target, prm_way);
        out_d_angRy = getRyMvAngDistance(prm_angRy_Target, prm_way);
    }

    //Rz, Ry ���A�ڕW�A���O���֓����ɓ��B����悤�Ɋp���x�𒲐�
    double drz = ABS(out_d_angRz);
    double dry = ABS(out_d_angRy);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_angRz > 0) {
            setRzMvAngVelo(prm_angVelo);
            setRzMvAngAcce(prm_angAcce);
        } else {
            setRzMvAngVelo(-prm_angVelo);
            setRzMvAngAcce(-prm_angAcce);
        }
        if (out_d_angRy > 0) {
            setRyMvAngVelo(prm_angVelo*drr);
            setRyMvAngAcce(prm_angAcce*drr);
        } else {
            setRyMvAngVelo(-prm_angVelo*drr);
            setRyMvAngAcce(-prm_angAcce*drr);
        }
    } else {
        double drr = drz / dry;
        if (out_d_angRz > 0) {
            setRzMvAngVelo(prm_angVelo*drr);
            setRzMvAngAcce(prm_angAcce*drr);
        } else {
            setRzMvAngVelo(-prm_angVelo*drr);
            setRzMvAngAcce(-prm_angAcce*drr);
        }
        if (out_d_angRy > 0) {
            setRyMvAngVelo(prm_angVelo);
            setRyMvAngAcce(prm_angAcce);
        } else {
            setRyMvAngVelo(-prm_angVelo);
            setRyMvAngAcce(-prm_angAcce);
        }
    }

    setStopTargetRzMvAng(prm_angRz_Target);
    setStopTargetRyMvAng(prm_angRy_Target);

}


void GgafDxKuroko::turnMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                 angvelo prm_angVelo, angacce prm_angAcce,
                                 int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    UTIL::convVectorToRzRy(prm_tx - _pActor->_x,
                           prm_ty - _pActor->_y,
                           prm_tz - _pActor->_z,
                           out_angRz_Target,
                           out_angRy_Target);
    turnRzRyMvAngTo(out_angRz_Target, out_angRy_Target,
                    prm_angVelo, prm_angAcce,
                    prm_way, prm_optimize_ang);
}
void GgafDxKuroko::turnRzMvAng(angle prm_angular_distance,
                                angvelo prm_angVelo, angacce prm_angAcce) {
    int s = SGN(prm_angular_distance);
    setRzMvAngVelo(ABS(prm_angVelo) * s);
    setRzMvAngAcce(ABS(prm_angAcce) * s);
    setStopTargetRzMvAng(_angRzMv+prm_angular_distance);
}

void GgafDxKuroko::turnRyMvAng(angle prm_angular_distance,
                                angvelo prm_angVelo, angacce prm_angAcce) {
    int s = SGN(prm_angular_distance);
    setRyMvAngVelo(ABS(prm_angVelo) * s);
    setRyMvAngAcce(ABS(prm_angAcce) * s);
    setStopTargetRyMvAng(_angRyMv+prm_angular_distance);
}

void GgafDxKuroko::turnRzMvAngTo(angle prm_angRz_Target,
                                  angvelo prm_angVelo, angacce prm_angAcce,
                                  int prm_way) {
    if (getRzMvAngDistance(prm_angRz_Target, prm_way) > 0) {
        setRzMvAngVelo(prm_angVelo);
        setRzMvAngAcce(prm_angAcce);
    } else {
        setRzMvAngVelo(-prm_angVelo);
        setRzMvAngAcce(-prm_angAcce);
    }
    setStopTargetRzMvAng(prm_angRz_Target);
}

void GgafDxKuroko::turnRyMvAngTo(angle prm_angRy_Target,
                                  angvelo prm_angVelo, angacce prm_angAcce,
                                  int prm_way) {
    if (getRyMvAngDistance(prm_angRy_Target, prm_way) > 0) {
        setRyMvAngVelo(prm_angVelo);
        setRyMvAngAcce(prm_angAcce);
    } else {
        setRyMvAngVelo(-prm_angVelo);
        setRyMvAngAcce(-prm_angAcce);
    }
    setStopTargetRyMvAng(prm_angRy_Target);
}

void GgafDxKuroko::takeoverMvFrom(GgafDxKuroko* const prm_pKuroko) {
    // �L�����̈ړ����p�P�ʃx�N�g��
    _vX = prm_pKuroko->_vX;
    _vY = prm_pKuroko->_vY;
    _vZ = prm_pKuroko->_vZ;
    // �ړ����p��Z����]�p
    _angRzMv = prm_pKuroko->_angRzMv;
    // �ړ����p��Y����]�p
    _angRyMv = prm_pKuroko->_angRyMv;
    // �ړ����x
    _veloMv = prm_pKuroko->_veloMv;
    // �ړ����x���
    _veloTopMv = prm_pKuroko->_veloTopMv;
    // �ړ����x����
    _veloBottomMv = prm_pKuroko->_veloBottomMv;
    // �ړ������x
    _accMv = prm_pKuroko->_accMv;
    // �ړ����x
    //_jerkMv = prm_pKuroko->_jerkMv;
}

GgafDxKuroko::~GgafDxKuroko() {
    GGAF_DELETE_NULLABLE(_pHelperA);
    GGAF_DELETE_NULLABLE(_pHelperB);
    GGAF_DELETE_NULLABLE(_pHelperC);
}


// �y���Y�^�����z�{�N���X�̍l�����ƃR�����g�̒P��̕\��
//
// ���Q��ނ̕�����
// �u�L�����̕����v�Ƃ������t���B���Ȃ��߁A���̂Q��ނ̒P����`����B�u�ړ����p�i�����j�v�Ɓu���ʕ��p�i�����j�v�B
// �u�ړ����p�v�̓L�����̐i�s�����݂̂�\������B����́u�ړ����x�v�Ɣ����āA�L�����͍��W�����ړ����邱�ƂƂ���B
// �u���ʕ��p�v�̓L�����̌����i�O���������j�݂̂�\�����鎖�Ƃ���B
// �L�����N�^����ʂ̏㕔���牺���ֈړ����Ă��A�L�����N�^�͉��������Ƃ͌��炸���@�Ɍ����Ăق����ꍇ������B
// �܂��́A�E�ɃL�������������āA���Ɉړ������������Ƃ�����B���ꂼ��Q�̕����ݒ肪�K�v�B
//
// ���ړ����p�̂Q��ނ̕\�����@��
// �L�������i�ޕ����A�܂�u�ړ����p�v�̕����́A���_����P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g�� (_vX, _vY, _vZ) �ŕ\�����@�ƁA
// �Q����]�A���O���l (_angRzMv, _angRyMv) �ŕ\�����@�̂Q��ޗp�ӂ����B�N�H�[�^�j�I���͍��̂Ƃ��떳���B
// _angRzMv �� Z����]�p�A _angRyMv �� Y����]�p ���Ӗ����Ă���B
// ����͕����x�N�g�����A�ܓx�ƌo�x�A�i�p�ƃA�W�}�X�j�̊֌W�Ɍ����āA�Ή������悤�Ƃ����B
// ���ӂ��邱�Ƃ́AY����]�p���o�x �͏�ɐ��藧���AZ����]�p���ܓx �́AZ����]�p �� Y����]�p�̏��Ԃł���ꍇ�Ɍ��萬�藧�B
// �{�N���X�ł́A�uZ����] �� Y����]�̏��Ԃł�Z����]�p�EY����]�p�v���ȗ����āA�P�ɁuZ����]�p�EY����]�p�v�ƕ\�����鎖�Ƃ���B
// ���ꂼ����u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�ƕ\�����鎖������B
//
// �\�[�X�R�[�h���́A�ϐ��⃁�\�b�h��
// �uRzMv�v�Ƃ����\�L�́u�ړ����p�iZ���j�v���Ӗ����Ă���B
// �uRyMv�v�Ƃ����\�L�́u�ړ����p�iY���j�v���Ӗ����Ă���B
// �uRzRyMv�v�Ƃ����\���́uZ����] �� Y����]�̏��Ԃ̈ړ����p�v��\���Ă���B
//
// Z����]�p�AY����]�p�������Ƃ�0�x���A�����x�N�g��(1, 0, 0) �̕����ƒ�`����B
// Z����]�p�̐��̑����́AZ���̐��̕����������Ĕ����v���B
// Y����]�p�̐��̑����́AY���̐��̕����������Ĕ����v���B�Ƃ���B
//
// �Ƃ���Ő��w�I�Ɂu���p�v�́A�����x�N�g���iXYZ�̒l�j�ŕ\�����邱�Ƃ������Ǝv���B
// ���������̖{�N���X�ł́A�悭�g���̂͂Q���\���̕��ŁA���\�b�h�� _angRzMv �� _angRyMv �𑀍삷����̂����S�ƂȂ��Ă���B
// ���͌��Ǔ����ŒP�ʕ����x�N�g�������߂Ă���̂����A���W��]�v�Z���A�����^�� _angRzMv �� _angRyMv �ł��񂴂�s���Ă���A
// �Ō�ɂP��P�ʃx�N�g�������߂�B�Ƃ������������̂ł͂ƍl�������߁A���̂悤�Ȑ݌v�ɂȂ����B
// TODO:�œK���̗]�n�����Ԏc���Ă���n�Y�B�܂������B
// (_angRzMv, _angRyMv)�����\�b�h�ɂ�葀�삵�āA�e�t���[���̍Ō�̓��������ŕ����x�N�g��(_vX, _vY, _vZ) �𓯊������Ă���B
// (_vX, _vY, _vZ)�����o�[�����\�b�h���g�킸���ڑ��삷��ƁA(_angRzMv, _angRyMv)�Ƃ̓����������̂Œ��ӁB
// �{�N���X�̃��\�b�h���g�p�������ł́A����Ȃ��Ƃ͋N����Ȃ��B
//
// ���ړ����x:Velo or MvVelo��
// �L�����́u�ړ����x�v(_veloMv)��ێ����Ă���B�ړ�������@�͊ȒP�ŁA��{�I�ɖ��t���[���u�ړ����p�v�Ɂu�ړ����x�v�����������B
// ���W�����́u�ړ����p�v(_vX, _vY, _vZ)�Ɂu�ړ����x�v(_veloMv)���|���Z���Ă���B
// �P�t���[����̍��W�͌��݂̍��W���� (_vX*_veloMv, _vY*_veloMv, _vZ*_veloMv) �ړ������ꏊ�ł���B
// ���̃x�N�g���ɖ{���C�u�����̒P�ʋ���(�Q�[�����̒����P�ƍl���鐮���{�l�j���悶��B
// ����āA(_vX*_veloMv*LEN_UNIT, _vY*_veloMv*LEN_UNIT, _vZ*_veloMv*LEN_UNIT)���P�t���[����̍��W�����B

// �����ʕ��p:AngFace��
// �L�����̃��[�J�����W�Ō����Ă�����p�i�����j���u���ʕ��p�v�ƌĂԂ��Ƃɂ���B
//�u���ʕ��p�v�́A���[���h�ϊ��s��̎���]�Ɠ�����]���@�ł���B
// ���[���h�ϊ��s��̎���]�Ƃ́AX����]�p�AY����]�p�AZ����]�p�̂��ƂŁA���ꂼ��A
// _angFace[AXIS_X], _angFace[AXIS_Y], _angFace[AXIS_Z] �ƈ�v����B
// �{���C�u�����ł́A�����x�N�g��(1, 0, 0) ���L�����́u�O���v�Ɛݒ肵�Ă���B
// X�t�@�C���Ȃǂ̃L�������f���́A������ԂŐ���X�������Ɍ����Ă��邱�Ƃ�O��Ƃ���B�܂��A���f���u������́v�́i0, 1, 0)�Ƃ���B
// ���[���h�ϊ��s��̉�]�s��̊|���鏇�Ԃ́A��{�I�� �uX����]�s�� > Z����]�s�� > Y����]�s�� > �ړ��s�� �v �Ƃ���B
// (��  X�� > Y�� > Z�� �̏��ł͂Ȃ���I�j
// ����āAX����]�p�͊���]�����悤�Ƃ��A�L�����������Ă�������͕ς�炸�A�c���Z����]�p�ƁAY����]�p�ŃL�����������Ă�����������肷�邱�ƂƂ���B
// X����]�p�̓L�����̃X�s���A�̂���Q�p�iZ����]�p�EY����]�p�j�ŃL�����́u�O���v���p�������肷��Ƃ����ꍇ�A
// �u���ʕ��p�v����قǂ́u�ړ����p�v�Ɠ����悤�ɁAZ����]�p��Y����]�p�i�ܓx�ƌo�x)�̂Q�̃A���O���l
// (_angFace[AXIS_Z], _angFace[AXIS_Y])�ŕ\���ł���B
// �܂�A�u�O���v�� Z����]�p�EY����]�p����0�x�Ƃ��A�Ⴆ�΁u���v��(Z����]�p,Y����]�p)=(0�x,180�x) �ƕ\������B�B
// �P�ɁuZ����]�p�v�ȂǂƏ����ƁA�u�ړ����p�v��Z����]�p�Ȃ̂��A�u���ʕ��p�v��Z����]�p�Ȃ̂��B���ɂȂ邽�߁A
// �u���ʕ��p(Z��)�v�u���ʕ��p(Y��)�v�Ə������ƂƂ���B�i���u���ʕ��p(X��)�v�����邪�A����̓X�s����\�������ւ̉e���͂��Ȃ��j
// �����Œ��ӂ́A�P�̃L�����������Ă�����p�ɑ΂��āA��ɂQ�ʂ�̃A�N�Z�X������@������Ƃ������ƁB�Ⴆ�΁A
// �u�O��(1, 0, 0)�������Đ^�E�����v �� (���ʕ��p(Z��), ���ʕ��p(Y��))=(0, 90�x) or (180�x,270�x) �Ƃŕ\���ł���B
// �i�����ʕ��p(Y��)�͍���n���W�̂���Y���̐������������Ĕ����v���j
// ���� �u�O���v�� (0�x,0�x) �Ƃ� (180�x,180�x) �Ƃ��\���ł��邵�A�u�^���v �� (0�x,180�x) �Ƃ� (180�x,0�x) �Ƃ��\���ł���B
// �����Ă�������͓��������A�p��(�L�����̏����)���قȂ�B�p�����قȂ�Ƃ܂����L�����͒��ӂ��邱�ƁB
// ���R�A�u�ړ����p�v�ł��A�Q�ʂ�̃A�N�Z�X������@������̂����A������͎p���������̂Ō����ڂŕ�����Ȃ��B
// �������p�x�v�Z����Ƃ��ɉe�����o��ꍇ������̂Œ��ӂ��K�v�B


// �������O�������@�\��
// ���Ă����� �u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v���A���ꂼ��u���ʕ��p(Z��)�v�u���ʕ��p(Y��)�v �փR�s�[���Ă��ƁA
// �ړ����p�ƁA�L�����N�^�̌����̓������ȒP�Ɏ��邶��Ȃ����I
// �u�����O�������@�\�v�Ƃ́A�u�ړ����p�v��ݒ肷��ƁA����ɔ����Ď����I�Ɂu���ʕ��p�v��ݒ肷�鎖�Ƃ���B
// ��̓I�ɂ́A�ȉ��̂悤�Ƀt���[�����ɁA�A���O���l���㏑���R�s�[�i�����j�B�����͍��������Z�i�������������炩�ɕ`��j���Ă����B
//  �E�ړ����p�iZ���j �� ���ʕ��p(Z��)
//  �E�ړ����p�iY���j �� ���ʕ��p(Y��)
// �������u���ʕ��p�v��ݒ�Ă��u�ړ����p�v�ω����Ȃ��i�t�͊֘A���Ȃ��j�̂Œ��ӁB

// ���p���x:AngVelo��
// �u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�A�u���ʕ��p(Z��)�v�u���ʕ��p(Y��)�v�ɂ́A���ꂼ��́u�p���x�v��݂��Ă���B
// �Ⴆ��90�x�E�Ɍ��������ꍇ�A�L�����������Ȃ�J�N���ƌ�����ς��Ă͔߂����̂ŁA���t���[���p���x�����p�����Z����悤�ɂ��āA
// ���炩�Ɍ�����ς���悤�ɂ���B
// �u�p���x�v�͐����̒��ӂ��K�v�B���̏ꍇ�͔����v���A���̏ꍇ�͎��v���ɂȂ�B
// �����]������ꍇ�A�^�[�Q�b�g�ƂȂ�p�x�ւ̓��B����A�v���[�`�͐�����]�̂Q�ʂ肾���A
// �\����5�ʂ�̍l�����Ŏw��ł���悤�݌v�����B
// 1.�u��ɔ����v��ōs���v TURN_ANTICLOSE_TO
// 2.�u��Ɏ��v���ōs���v TURN_CLOCKWISE
// 3.�u�߂��p�̎�������ōs���vTURN_CLOSE_TO
// 4.�u�����Ȋp�̎�������ōs���vTURN_ANTICLOSE_TO
// 5.�u���݉���Ă���������̂܂܂ōs���v
// �ł���B���ꂼ��p�r������̂ŁA�I�v�V���������ȂǂŁA�I���ł���悤�ɂ������ȁB���ł����B



//�����̑��ǋL�A��������
//�E�ړ����x�A�ړ����p�p���x�A����]�p�p���x�ɂ́A���ꂼ������x���ݒ�ł���I
//�E����]�́A�{���� Z > X > Y �̎���]���Ԃɂ���̂���ʓI�̂悤���B�܂�O���̊T�O��Z���ŉ��ł���킯���A�Ȃ�قǂ킩��₷���B
//  ���݂� X > Z > Y �́A����Z�������O����X���ł���B
//  ���Ƃ���2D�̉��X�N���[���V���[�e�B���O����낤�Ǝv���Ă���A���� X > Z �����Ő݌v���s���Ă����̂������ł��邪�A�������ǂ�Ȃ��B
//  �܂����A3D�V���[�e�B���O�ɂ���Ƃ͎����ł��v���Ă��݂Ȃ������E�E�E

// ���������ړ�: VxMv VyMv VzMv��
// ��L�̈ړ��̌n�Ƃ͂܂������ʂɁA�Ɨ����� X���AY���AZ���ɕ��s�Ȉړ��w�肪�ł���B
// �uX�������ړ����x�v�uY�������ړ����x�v�uZ�������ړ����x�v��ݒ肷��ƁA���t���[��(_x,_y,_z)�ɂ��ꂼ��̈ړ�������
// ���Z�����B
// �i�������̋@�\�� GgafDxAxesMover �ɏW�񂳂�Ɨ������N���X�ƂȂ�܂����I�j

//2010/02/19�ǋL
// �����܂ɁuRyRz�v�Ƃ����\�������݂���i�uRzRy�v�ƈقȂ�j���A����́uY����] �� Z����]�̏��Ԃ̈ړ����p�v��\���Ă���̂Œ��ӁB
//   �܂��A�u�ړ����p�iZ���j�v������]�̏��Ԃ̈Ⴂ�𖾊m�ɂ��邽��
//   �uRzRy��Rz�v�uRyRz��Rz�v�Ə������肵�Ă���Ƃ��������B�i�P�ɁuRz�v�����̏ꍇ�́uRzRy��Rz�v���Ӗ����Ă���j

//�ǋL
//�E���炩�ړ����\�ɁI

//TODO:
//���x�i�������x�j�̒ǉ�
//�C�ӎ���]�i�N�H�[�^�j�I���j
//�N���X�̔�剻 �� ���s�ړ��x���������
//�y�����z��Z�߂�
