#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

#include <math.h>
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantC.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKuroko::GgafDxKuroko(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {
    _pAsstA = nullptr;
    _pAsstB = nullptr;
    _pAsstC = nullptr;
    reset();
}
GgafDxKurokoAssistantA* GgafDxKuroko::asstA() {
    return _pAsstA ? _pAsstA : _pAsstA = NEW GgafDxKurokoAssistantA(this);
}
GgafDxKurokoAssistantB* GgafDxKuroko::asstB() {
    return _pAsstB ? _pAsstB : _pAsstB = NEW GgafDxKurokoAssistantB(this);
}
GgafDxKurokoAssistantC* GgafDxKuroko::asstC() {
    return _pAsstC ? _pAsstC : _pAsstC = NEW GgafDxKurokoAssistantC(this);
}

void GgafDxKuroko::reset() {
    GGAF_DELETE_NULLABLE(_pAsstA);
    GGAF_DELETE_NULLABLE(_pAsstB);
    GGAF_DELETE_NULLABLE(_pAsstC);

    _actor_ang_face[0] = &(_pActor->_rx);
    _actor_ang_face[1] = &(_pActor->_ry);
    _actor_ang_face[2] = &(_pActor->_rz);

    for (int ax = 0; ax < 3; ax++) { // i=0:X���A1:Y���A2:Z�� ��\��
        //���ʕ��p�̊p���x�i���ʕ��p�̑����j= 0 angle/fream
        _angvelo_face[ax] = 0; //1�t���[���ɉ��Z����鐳�ʕ��p�̊p�����B�f�t�H���g�͐��ʕ��p�̊p���������A�܂�U����������B
        //���ʕ��p�̊p���x��� �� 360,000 angle/fream
        _top_angvelo_face[ax] = D360ANG; //_angvelo_face[n] �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȑ��ʕ��p�ɐU����������o���鎖���Ӗ�����
        //���ʕ��p�̊p���x���� �� -360,000 angle/fream
        _bottom_angvelo_face[ax] = D360ANG * -1; //_angvelo_face[n] �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȑ��ʕ��p�ɐU����������o���鎖���Ӗ�����
        //���ʕ��p�̊p�����x�i�p���x�̑����j �� 0 angle/fream^2
        _angacce_face[ax] = 0; //_angvelo_face[n] �̑����B�f�t�H���g�͐��ʕ��p�̊p�����x����

        _angjerk_face[ax] = 0;
        //�ڕW���ʕ��p�ւ̎��������t���O = ����
        _is_targeting_ang_face[ax] = false;
        //�ڕW���ʕ��p�ւ̎�����~�t���O = ����
        _ang_face_targeting_stop_flg[ax] = false;
        //�ڕW�̐��ʕ��p
        _target_ang_face[ax] = 0; //�ڕW���ʕ��p�ւ̎�������t���O = �����A�̏ꍇ�͖��Ӗ�
        //�ڕW�̐��ʕ��p������~�@�\���L���ɂȂ��]����
        _ang_face_stop_allow_way[ax] = TURN_BOTH;
        //�ڕW�̐��ʕ��p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj
        _ang_face_stop_allow_angvelo[ax] = D360ANG;
    }

    //////////////////////////////////////////////////////
    //�L�����̈ړ����p�P�ʃx�N�g��
    _vX = 1.0f;
    _vY = _vZ = 0.0f;
    //�ړ����p��Z����]
    _ang_rz_mv = 0;
    //�ړ����p��Y����]
    _ang_ry_mv = 0;
    //�ړ����x
    _velo_mv = 0;
    //�ړ����x���
    _top_velo_mv = INT_MAX;
    //�ړ����x����
    _bottom_velo_mv = INT_MIN;
    //�ړ������x�i�ړ����x�̑����j = 0 px/fream^2
    _acc_mv = 0; //_velo_mv �̑����B�f�t�H���g�͉�������

    //_jerkMv = 0;
    //�ړ����p�iZ����]�j�̊p���x = 0 angle/fream
    _angvelo_rz_mv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iZ����]�j�̊p���x��� = +360,000 angle/fream
    _top_angvelo_rz_mv = D360ANG; //_angvelo_rz_mv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p���x���� = -360,000 angle/fream
    _bottom_angvelo_rz_mv = D360ANG * -1; //_angvelo_rz_mv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p�����x = 0 angle/fream^2
    _angacce_rz_mv = 0; //_angvelo_rz_mv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _angjerk_rz_mv = 0;
    //�ڕW�ړ����p�iZ����]�j�ւ̎��������t���O = ����
    _is_targeting_ang_rz_mv = false;
    //�ڕW�ړ����p�iZ����]�j�ւ̎�����~�t���O = ����
    _ang_rz_mv_targeting_stop_flg = false;

    //�ڕW�̈ړ����p�iZ����]�j
    _target_ang_rz_mv = 0;
    //�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ��]����
    _ang_rz_mv_stop_allow_way = TURN_BOTH;
    //�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
    _ang_rz_mv_stop_allow_angvelo = D360ANG;
    //�ړ����p�iZ����]�j�ɔ���Z���ʕ��p�̓��������@�\�t���O �� ����
    _relate_RzFaceAng_with_RzMvAng_flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z���ʕ��p�������ɂȂ�B

    //�ړ����p�iY����]�j�̊p���x = 0 angle/fream
    _angvelo_ry_mv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iY����]�j�̊p���x��� = +360,000 angle/fream
    _top_angvelo_ry_mv = D360ANG; //_angvelo_ry_mv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p���x���� = -360,000 angle/fream
    _bottom_angvelo_ry_mv = D360ANG * -1; //_angvelo_ry_mv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p�����x = 0 angle/fream^2
    _angacce_ry_mv = 0; //_angvelo_ry_mv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _angjerk_ry_mv = 0;
    //�ڕW�ړ����p�iY����]�j�ւ̎��������t���O = ����
    _is_targeting_ang_ry_mv = false;
    //�ڕW�ړ����p�iY����]�j�ւ̎�����~�t���O = ����
    _ang_ry_mv_targeting_stop_flg = false;
    //�ڕW�̈ړ����p�iY����]�j
    _target_ang_ry_mv = 0;
    //�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ��]����
    _ang_ry_mv_stop_allow_way = TURN_BOTH;
    //�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
    _ang_ry_mv_stop_allow_angvelo = D360ANG;
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

void GgafDxKuroko::behave() {
    if (_pAsstA) {
        _pAsstA->behave();
    }
    if (_pAsstB) {
        _pAsstB->behave();
    }
    if (_pAsstC) {
        _pAsstC->behave();
    }

    //���ʕ��p����
    for (axis ax = 0; ax < 3; ax++) {

        _angvelo_face[ax] += _angacce_face[ax];
        if (_angvelo_face[ax] > _top_angvelo_face[ax]) {
            _angvelo_face[ax] = _top_angvelo_face[ax];
        } else if (_angvelo_face[ax] < _bottom_angvelo_face[ax]) {
            _angvelo_face[ax] = _bottom_angvelo_face[ax];
        }

        if (_is_targeting_ang_face[ax]) { //�^�[�Q�b�g����������ꍇ

            if (_angvelo_face[ax] > 0) { //�����v���̏ꍇ
                const angle angDistance = getFaceAngDistance(ax, _target_ang_face[ax], TURN_COUNTERCLOCKWISE);
                if (_angvelo_face[ax] > angDistance && _ang_face_stop_allow_way[ax] != TURN_CLOCKWISE &&
                        _ang_face_stop_allow_angvelo[ax] >= _angvelo_face[ax]) {
                    _angvelo_face[ax] = angDistance;
                    if (_ang_face_targeting_stop_flg[ax]) {
                        _is_targeting_ang_face[ax] = false; //�t���O��߂��ďI��
                        _ang_face_targeting_stop_flg[ax] = false;
                    }
                } else {
                    // �Ȃɂ����Ȃ��Ă悢
                }
            } else if (_angvelo_face[ax] < 0) { //���v���̏ꍇ
                const angle angDistance = getFaceAngDistance(ax, _target_ang_face[ax], TURN_CLOCKWISE);
                if (_angvelo_face[ax] < angDistance && _ang_face_stop_allow_way[ax] != TURN_COUNTERCLOCKWISE
                        && -1 * _ang_face_stop_allow_angvelo[ax] <= _angvelo_face[ax]) { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                    _angvelo_face[ax] = angDistance;
                    if (_ang_face_targeting_stop_flg[ax]) {
                        _is_targeting_ang_face[ax] = false; //�t���O��߂��ďI��
                        _ang_face_targeting_stop_flg[ax] = false;
                    }
                } else {
                    // �Ȃɂ����Ȃ��Ă悢
                }
            } else {
                //_angvelo_face[ax] == 0
                const angle angDistance = getFaceAngDistance(ax, _target_ang_face[ax], TURN_CLOSE_TO);
                if (angDistance == 0) {
                    if (_ang_face_targeting_stop_flg[ax]) {
                        _is_targeting_ang_face[ax] = false; //�t���O��߂��ďI��
                        _ang_face_targeting_stop_flg[ax] = false;
                    }
                } else {
                    _TRACE_("���x����GgafDxKuroko::behave() : _angvelo_face["<<ax<<"]="<<_angvelo_face[ax]<<" �ŁA�^�[�Q�b�g�܂ł̋���angDistance="<<angDistance<<" �Ȃ̂ŁA"<<
                            "���܂ł��^�[�Q�b�g�ɓ��B���Ȃ��̂ł͂Ȃ����낤���H_pActor="<<_pActor->getName()<<"("<<_pActor<<")�i�v�m�F�j");
                }
            }

            //Actor�ɔ��f
            (*(_actor_ang_face[ax])) = UTIL::simplifyAng((*(_actor_ang_face[ax])) + _angvelo_face[ax]);
            if (_is_targeting_ang_face[ax] == false) {
                //�ڕW�����ɓ��B�������̏���
                //_top_angvelo_face[ax] = D360ANG; //���ʕ��p�̊p���x��� �� 360,000 angle/fream
                //_bottom_angvelo_face[ax] = D360ANG * -1; //���ʕ��p�̊p���x���� �� -360,000 angle/fream
                //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
                _angacce_face[ax] = 0; //����]�����p�A�p���x���O��
                setFaceAngVelo(ax, 0); //����]�����p�A�p�����x���O��
            }

        } else {
            //�^�[�Q�b�g�����������ꍇ
            //Actor�ɔ��f
            (*(_actor_ang_face[ax])) = UTIL::simplifyAng((*(_actor_ang_face[ax])) +  _angvelo_face[ax]);
        }

    }


    ///////////////////////////////////////////////////Mover

    //_acc_mv += _jerkMv;
    //�ړ������x�̏���
    _velo_mv += _acc_mv;
    if (_velo_mv > _top_velo_mv) {
        _velo_mv = _top_velo_mv;
    } else if (_velo_mv < _bottom_velo_mv) {
        _velo_mv = _bottom_velo_mv;
    }

    ///////////
    //�ڕW�ړ����p�iZ����]�j�A���O��������~�@�\�g�p���̏ꍇ
    if (_is_targeting_ang_rz_mv) {

        _angvelo_rz_mv += _angacce_rz_mv;
        setRzMvAngVelo(_angvelo_rz_mv);

        if (_angvelo_rz_mv > 0) { //�����v���̏ꍇ
            const angle angDistance = getRzMvAngDistance(_target_ang_rz_mv, TURN_COUNTERCLOCKWISE);
            if (_angvelo_rz_mv > angDistance && _ang_rz_mv_stop_allow_way != TURN_CLOCKWISE
                    && _ang_rz_mv_stop_allow_angvelo >= _angvelo_rz_mv) { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                addRzMvAng(angDistance);
                if (_ang_rz_mv_targeting_stop_flg) { //��~�w�肠��Ȃ��
                    _is_targeting_ang_rz_mv = false; //�t���O��߂��ďI��
                    _ang_rz_mv_targeting_stop_flg = false;
                }
            } else {
                addRzMvAng(_angvelo_rz_mv);
            }
        } else if (_angvelo_rz_mv < 0) { //���v���̏ꍇ

            const angle angDistance = getRzMvAngDistance(_target_ang_rz_mv, TURN_CLOCKWISE);
            if (_angvelo_rz_mv < angDistance && _ang_rz_mv_stop_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_ang_rz_mv_stop_allow_angvelo <= _angvelo_rz_mv) {
                addRzMvAng(angDistance);
                if (_ang_rz_mv_targeting_stop_flg) { //��~�w�肠��Ȃ��
                    _is_targeting_ang_rz_mv = false; //�t���O��߂��ďI��
                    _ang_rz_mv_targeting_stop_flg = false;
                }
            } else {
                addRzMvAng(_angvelo_rz_mv);
            }
        } else {
            const angle angDistance = getRzMvAngDistance(_target_ang_rz_mv, TURN_CLOSE_TO);
            if (angDistance == 0) {
                addRzMvAng(angDistance);
                if (_ang_rz_mv_targeting_stop_flg) { //��~�w�肠��Ȃ��
                    _is_targeting_ang_rz_mv = false; //�t���O��߂��ďI��
                    _ang_rz_mv_targeting_stop_flg = false;
                }
            } else {
                _TRACE_("���x����GgafDxKuroko::behave() : _angvelo_rz_mv="<<_angvelo_rz_mv<<" �ŁA�^�[�Q�b�g�܂ł̋���angDistance="<<angDistance<<" �Ȃ̂ŁA"<<
                        "���܂ł��^�[�Q�b�g�ɓ��B���Ȃ��̂ł͂Ȃ����낤���H_pActor="<<_pActor->getName()<<"("<<_pActor<<")�i�v�m�F�j");
            }
        }
        if (_is_targeting_ang_rz_mv == false) {
            //_top_angvelo_rz_mv = D360ANG; //�ړ����p�iZ����]�j�̊p���x��� �� 360,000 angle/fream
            //_bottom_angvelo_rz_mv = D360ANG * -1; //�ړ����p�iZ����]�j�̊p���x���� �� -360,000 angle/fream

            //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
            _angacce_rz_mv = 0; //Z���ړ������p�A�p�����x���O��
            setRzMvAngVelo(0); //Z���ړ������p�A�p���x���O��
        }

    } else {
        //if (_angacce_rz_mv != 0) {

        _angacce_rz_mv += _angjerk_rz_mv;
        //�t���[�����̈ړ����p�iZ����]�j����̏���
        _angvelo_rz_mv += _angacce_rz_mv;
        if (_angvelo_rz_mv != 0) {
            addRzMvAng(_angvelo_rz_mv);
        }
        //}
    }
    ////////////////
    //�ڕW�ړ����p�iY����]�j�A���O��������~�@�\�g�p���̏ꍇ
    if (_is_targeting_ang_ry_mv) {

        _angvelo_ry_mv += _angacce_ry_mv;
        setRyMvAngVelo(_angvelo_ry_mv);

        if (_angvelo_ry_mv > 0) { //���݂͔����v���̏ꍇ
            angle angDistance = getRyMvAngDistance(_target_ang_ry_mv, TURN_COUNTERCLOCKWISE);
            if (_angvelo_ry_mv > angDistance &&
                _ang_ry_mv_stop_allow_way != TURN_CLOCKWISE &&
                _ang_ry_mv_stop_allow_angvelo >= _angvelo_ry_mv)
            { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                addRyMvAng(angDistance);
                if (_ang_ry_mv_targeting_stop_flg) { //��~�w�肠��Ȃ��
                    _is_targeting_ang_ry_mv = false; //�t���O��߂��ďI��
                }
            } else {
                addRyMvAng(_angvelo_ry_mv);
            }
        } else if (_angvelo_ry_mv < 0) { //���݂͎��v���̏ꍇ

            angle angDistance = getRyMvAngDistance(_target_ang_ry_mv, TURN_CLOCKWISE);
            if (_angvelo_ry_mv < angDistance &&
                _ang_ry_mv_stop_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_ang_ry_mv_stop_allow_angvelo <= _angvelo_ry_mv)
            {
                addRyMvAng(angDistance);
                if (_ang_ry_mv_targeting_stop_flg) { //��~�w�肠��Ȃ��
                    _is_targeting_ang_ry_mv = false; //�t���O��߂��ďI��
                }
            } else {
                addRyMvAng(_angvelo_ry_mv);
            }
        } else { //_angvelo_ry_mv==0
            angle angDistance = getRyMvAngDistance(_target_ang_ry_mv, TURN_CLOSE_TO);
            if (angDistance == 0) {
                addRyMvAng(angDistance);
                if (_ang_ry_mv_targeting_stop_flg) { //��~�w�肠��Ȃ��
                    _is_targeting_ang_ry_mv = false; //�t���O��߂��ďI��
                    _ang_ry_mv_targeting_stop_flg = false;
                }
            } else {
                _TRACE_("���x����GgafDxKuroko::behave() : _angvelo_ry_mv="<<_angvelo_ry_mv<<" �ŁA�^�[�Q�b�g�܂ł̋���angDistance="<<angDistance<<" �Ȃ̂ŁA"<<
                        "���܂ł��^�[�Q�b�g�ɓ��B���Ȃ��̂ł͂Ȃ����낤���H_pActor="<<_pActor->getName()<<"("<<_pActor<<")�i�v�m�F�j");
            }
        }
        if (_is_targeting_ang_ry_mv == false) {
            //_top_angvelo_ry_mv = D360ANG; //�ړ����p�iY����]�j�̊p���x��� �� 360,000 angle/fream
            //_bottom_angvelo_ry_mv = D360ANG*-1; //�ړ����p�iY����]�j�̊p���x���� �� -360,000 angle/fream

            //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
            _angacce_ry_mv = 0; //Y���ړ������p�A�p�����x���O��
            setRyMvAngVelo(0); //Y���ړ������p�A�p���x���O��
        }

    } else {
        //if (_angacce_ry_mv != 0) {
        _angacce_ry_mv += _angjerk_ry_mv;
        //�t���[�����̈ړ����p�iY����]�j����̏���
        _angvelo_ry_mv += _angacce_ry_mv;
        if(_angvelo_ry_mv != 0) {
            addRyMvAng(_angvelo_ry_mv);
        }
        //}
    }

    ///////////////
    if (_taget_face_ang_alltime_flg && _is_targeting_ang_face[AXIS_Z] == false && _is_targeting_ang_face[AXIS_Y] == false) {
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
    _pActor->_x += (coord)(_vX * _velo_mv);
    _pActor->_y += (coord)(_vY * _velo_mv);
    _pActor->_z += (coord)(_vZ * _velo_mv);
}

void GgafDxKuroko::setFaceAngVelo(axis prm_axis, angvelo prm_angvelo) {
    if (prm_angvelo > _top_angvelo_face[prm_axis]) {
        _angvelo_face[prm_axis] = _top_angvelo_face[prm_axis];
    } else if (prm_angvelo < _bottom_angvelo_face[prm_axis]) {
        _angvelo_face[prm_axis] = _bottom_angvelo_face[prm_axis];
    } else {
        _angvelo_face[prm_axis] = prm_angvelo;
    }
}

void GgafDxKuroko::setRollPitchYawFaceAngVelo(angvelo prm_axis_x_angvelo,
                                              angvelo prm_axis_z_angvelo,
                                              angvelo prm_axis_y_angvelo) {
    setFaceAngVelo(AXIS_X, prm_axis_x_angvelo);
    setFaceAngVelo(AXIS_Z, prm_axis_z_angvelo);
    setFaceAngVelo(AXIS_Y, prm_axis_y_angvelo);
}

void GgafDxKuroko::forceFaceAngVeloRange(axis prm_axis,
                                         angvelo prm_angvelo01,
                                         angvelo prm_angvelo02) {
    if (prm_angvelo01 < prm_angvelo02) {
        _top_angvelo_face[prm_axis] = prm_angvelo02;
        _bottom_angvelo_face[prm_axis] = prm_angvelo01;
    } else {
        _top_angvelo_face[prm_axis] = prm_angvelo01;
        _bottom_angvelo_face[prm_axis] = prm_angvelo02;
    }
    setFaceAngVelo(prm_axis, _angvelo_face[prm_axis]); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKuroko::setFaceAngAcce(axis prm_axis, angacce prm_angacce) {
    _angacce_face[prm_axis] = prm_angacce;
}

void GgafDxKuroko::setStopTargetFaceAngTwd(axis prm_axis,
                                           coord prm_tx,
                                           coord prm_ty,
                                           int prm_way_allow,
                                           angvelo prm_angvelo_allow) {
    setStopTargetFaceAng(
      prm_axis,
      UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
      prm_way_allow,
      prm_angvelo_allow
    );
}

void GgafDxKuroko::setStopTargetFaceAng(axis prm_axis,
                                        angle prm_ang_target,
                                        int prm_way_allow,
                                        angvelo prm_angvelo_allow) {
    _is_targeting_ang_face[prm_axis] = true;
    _ang_face_targeting_stop_flg[prm_axis] = true;
    _target_ang_face[prm_axis] = UTIL::simplifyAng(prm_ang_target);
    _ang_face_stop_allow_way[prm_axis] = prm_way_allow;
    _ang_face_stop_allow_angvelo[prm_axis] = prm_angvelo_allow;
}

angle GgafDxKuroko::getFaceAngDistance(axis prm_axis, coord prm_tx, coord prm_ty, int prm_way) {
    return getFaceAngDistance(
               prm_axis,
               UTIL::getAngle2D(prm_tx-(_pActor->_x), prm_ty-(_pActor->_y)),
               prm_way);
}

angle GgafDxKuroko::getFaceAngDistance(axis prm_axis, angle prm_ang_target, int prm_way) {
    return UTIL::getAngDiff( (*(_actor_ang_face[prm_axis])),  prm_ang_target, prm_way);
}

void GgafDxKuroko::forceMvVeloRange(velo prm_velo) {
    forceMvVeloRange(-prm_velo, prm_velo);
}

void GgafDxKuroko::forceMvVeloRange(velo prm_velo_mv01, velo prm_velo_mv02) {
    if (prm_velo_mv01 < prm_velo_mv02) {
        _top_velo_mv = prm_velo_mv02;
        _bottom_velo_mv = prm_velo_mv01;
    } else {
        _top_velo_mv = prm_velo_mv01;
        _bottom_velo_mv = prm_velo_mv02;
    }
    setMvVelo(_velo_mv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKuroko::setMvVelo(velo prm_velo_mv) {
    if (prm_velo_mv > _top_velo_mv) {
        _velo_mv = _top_velo_mv;
    } else if (prm_velo_mv < _bottom_velo_mv) {
        _velo_mv = _bottom_velo_mv;
    } else {
        _velo_mv = prm_velo_mv;
    }
}

void GgafDxKuroko::addMvVelo(velo prm_velo_mv_Offset) {
    setMvVelo(_velo_mv + prm_velo_mv_Offset);
}

void GgafDxKuroko::setMvAcce(int prm_acceMove) {
    _acc_mv = prm_acceMove;
}

frame GgafDxKuroko::setMvAcceToStop(coord prm_target_distance) {
    double acc = UTIL::getAcceToStop(prm_target_distance, _velo_mv);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _acc_mv = acc;
    return (frame)((2.0*prm_target_distance) / _velo_mv); //�g�p�t���[����
}

frame GgafDxKuroko::setFaceAngAcceToStop(axis prm_axis, angle prm_target_angle_distance) {
    double acc = UTIL::getAcceToStop(prm_target_angle_distance, _angvelo_face[prm_axis]);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacce_face[prm_axis] = acc;
    return (frame)((2.0*prm_target_angle_distance) / _angvelo_face[prm_axis]); //�g�p�t���[����
}

frame GgafDxKuroko::setMvAcceByD(coord prm_target_distance, velo prm_target_velo) {
    double acc = UTIL::getAcceByVd(_velo_mv, prm_target_velo, prm_target_distance);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _acc_mv = acc;
    return (frame)((1.0*prm_target_velo - _velo_mv) / acc); //�g�p�t���[����
}
frame GgafDxKuroko::setFaceAngAcceByD(axis prm_axis, angle prm_target_angle_distance, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByVd(prm_target_angvelo, prm_target_angle_distance, _angvelo_face[prm_axis]);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacce_face[prm_axis] = acc;
    return (frame)((1.0*prm_target_angvelo - _angvelo_face[prm_axis]) / acc); //�g�p�t���[����
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
    double acc = UTIL::getAcceByTv(prm_target_frames, _velo_mv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _acc_mv = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_velo_mv + prm_target_velo) * prm_target_frames) / 2 ;
}
angle GgafDxKuroko::setFaceAngAcceByT(axis prm_axis, frame prm_target_frames, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _angvelo_face[prm_axis], prm_target_angvelo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacce_face[prm_axis] = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_angvelo_face[prm_axis] + prm_target_angvelo) * prm_target_frames) / 2 ;
}

void GgafDxKuroko::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _ang_rz_mv) {
        _ang_rz_mv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_ang_rz_mv, _ang_ry_mv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _ang_rz_mv;
    }
}

void GgafDxKuroko::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_bottom_angvelo_rz_mv > prm_angDistance) {
        angOffset = _bottom_angvelo_rz_mv;
    } else if (prm_angDistance > _top_angvelo_rz_mv) {
        angOffset = _top_angvelo_rz_mv;
    }
    setRzMvAng(_ang_rz_mv + angOffset);
}

void GgafDxKuroko::setRzMvAngVelo(angvelo prm_angvelo_rz_mv) {
    if (prm_angvelo_rz_mv > _top_angvelo_rz_mv) {
        _angvelo_rz_mv = _top_angvelo_rz_mv;
    } else if (prm_angvelo_rz_mv < _bottom_angvelo_rz_mv) {
        _angvelo_rz_mv = _bottom_angvelo_rz_mv;
    } else {
        _angvelo_rz_mv = prm_angvelo_rz_mv;
    }
}

void GgafDxKuroko::setRzMvAngAcce(angacce prm_angacce_rz_mv) {
    _angacce_rz_mv = prm_angacce_rz_mv;
}

void GgafDxKuroko::forceRzMvAngVeloRange(angvelo prm_angvelo_rz_mv01,
                                         angvelo prm_angvelo_rz_mv02) {
    if (prm_angvelo_rz_mv01 < prm_angvelo_rz_mv02) {
        _top_angvelo_rz_mv = prm_angvelo_rz_mv02;
        _bottom_angvelo_rz_mv = prm_angvelo_rz_mv01;
    } else {
        _top_angvelo_rz_mv = prm_angvelo_rz_mv01;
        _bottom_angvelo_rz_mv = prm_angvelo_rz_mv02;
    }
    setRzMvAngVelo(_angvelo_rz_mv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKuroko::setStopTargetRzMvAng(angle prm_target_ang_rz_mv,
                                        int prm_way_allow,
                                        angvelo prm_angvelo_allow) {
    _is_targeting_ang_rz_mv = true;
    _ang_rz_mv_targeting_stop_flg = true;
    _target_ang_rz_mv = UTIL::simplifyAng(prm_target_ang_rz_mv);
    _ang_rz_mv_stop_allow_way = prm_way_allow;
    _ang_rz_mv_stop_allow_angvelo = prm_angvelo_allow;
}

angle GgafDxKuroko::getRzMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRzMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)), prm_way);
}

angle GgafDxKuroko::getRzMvAngDistance(angle prm_target_ang_rz_mv, int prm_way) {
    return UTIL::getAngDiff(_ang_rz_mv, prm_target_ang_rz_mv, prm_way);
}


//void GgafDxKuroko::setRyMvAngTwd(coord prm_tx, coord prm_ty) {
//    setRyMvAng(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)));
//}

void GgafDxKuroko::setRyMvAng(angle prm_ang) {
    if (prm_ang != _ang_ry_mv) {
        _ang_ry_mv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_ang_rz_mv, _ang_ry_mv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ang_ry_mv;
    }
}

void GgafDxKuroko::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_bottom_angvelo_ry_mv > prm_angDistance) {
        angOffset = _bottom_angvelo_ry_mv;
    } else if (prm_angDistance > _top_angvelo_ry_mv) {
        angOffset = _top_angvelo_ry_mv;
    }
    setRyMvAng(_ang_ry_mv + angOffset);
}

void GgafDxKuroko::setRyMvAngVelo(angvelo prm_angvelo_ry_mv) {
    if (prm_angvelo_ry_mv > _top_angvelo_ry_mv) {
        _angvelo_ry_mv = _top_angvelo_ry_mv;
    } else if (prm_angvelo_ry_mv < _bottom_angvelo_ry_mv) {
        _angvelo_ry_mv = _bottom_angvelo_ry_mv;
    } else {
        _angvelo_ry_mv = prm_angvelo_ry_mv;
    }
}

void GgafDxKuroko::setRyMvAngAcce(angacce prm_angacce_ry_mv) {
    _angacce_ry_mv = prm_angacce_ry_mv;
}

void GgafDxKuroko::forceRyMvAngVeloRange(angvelo prm_angvelo_ry_mv01,
                                         angvelo prm_angvelo_ry_mv02) {
    if (prm_angvelo_ry_mv01 < prm_angvelo_ry_mv02) {
        _top_angvelo_ry_mv = prm_angvelo_ry_mv02;
        _bottom_angvelo_ry_mv = prm_angvelo_ry_mv01;
    } else {
        _top_angvelo_ry_mv = prm_angvelo_ry_mv01;
        _bottom_angvelo_ry_mv = prm_angvelo_ry_mv02;
    }
    setRyMvAngVelo(_angvelo_ry_mv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKuroko::forceRzRyMvAngVeloRange(angvelo prm_angvelo_rzry_mv01, angvelo prm_angvelo_rzry_mv02) {
    if (prm_angvelo_rzry_mv01 < prm_angvelo_rzry_mv02) {
        _top_angvelo_rz_mv = prm_angvelo_rzry_mv02;
        _bottom_angvelo_rz_mv = prm_angvelo_rzry_mv01;
        _top_angvelo_ry_mv = prm_angvelo_rzry_mv02;
        _bottom_angvelo_ry_mv = prm_angvelo_rzry_mv01;
    } else {
        _top_angvelo_rz_mv = prm_angvelo_rzry_mv01;
        _bottom_angvelo_rz_mv = prm_angvelo_rzry_mv02;
        _top_angvelo_ry_mv = prm_angvelo_rzry_mv01;
        _bottom_angvelo_ry_mv = prm_angvelo_rzry_mv02;
    }
    setRzMvAngVelo(_angvelo_rz_mv); //�Đݒ肵�Ĕ͈͓��ɕ␳
    setRyMvAngVelo(_angvelo_ry_mv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKuroko::setRzRyMvAngAcce(angacce prm_angacce_rz_mv, angacce prm_angacce_ry_mv) {
    _angacce_rz_mv = prm_angacce_rz_mv;
    _angacce_ry_mv = prm_angacce_ry_mv;
}

void GgafDxKuroko::setRzRyMvAngVelo(angvelo prm_angvelo_rz_mv, angvelo prm_angvelo_ry_mv) {
    if (prm_angvelo_rz_mv > _top_angvelo_rz_mv) {
        _angvelo_rz_mv = _top_angvelo_rz_mv;
    } else if (prm_angvelo_rz_mv < _bottom_angvelo_rz_mv) {
        _angvelo_rz_mv = _bottom_angvelo_rz_mv;
    } else {
        _angvelo_rz_mv = prm_angvelo_rz_mv;
    }
    if (prm_angvelo_ry_mv > _top_angvelo_ry_mv) {
        _angvelo_ry_mv = _top_angvelo_ry_mv;
    } else if (prm_angvelo_ry_mv < _bottom_angvelo_ry_mv) {
        _angvelo_ry_mv = _bottom_angvelo_ry_mv;
    } else {
        _angvelo_ry_mv = prm_angvelo_ry_mv;
    }
}

void GgafDxKuroko::setStopTargetRyMvAng(angle prm_target_ang_ry_mv,
                                        int prm_way_allow,
                                        angvelo prm_angvelo_allow) {
    _is_targeting_ang_ry_mv = true;
    _ang_ry_mv_targeting_stop_flg = true;
    _target_ang_ry_mv = UTIL::simplifyAng(prm_target_ang_ry_mv);
    _ang_ry_mv_stop_allow_way = prm_way_allow;
    _ang_ry_mv_stop_allow_angvelo = prm_angvelo_allow;
}

angle GgafDxKuroko::getRyMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRyMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
                                        prm_way);
}

angle GgafDxKuroko::getRyMvAngDistance(angle prm_target_ang_ry_mv, int prm_way) {
    return UTIL::getAngDiff(_ang_ry_mv, prm_target_ang_ry_mv, prm_way);
}

void GgafDxKuroko::getRzRyMvAngDistanceTwd(angle prm_target_ang_rz, angle prm_target_ang_ry, int prm_way,
                                           angle& out_d_ang_rz, angle& out_d_ang_ry) {
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        //�ڕW�ɓ��B���邽�߂ɂ́A��������ɂQ�p�^�[������B
        //���ꂼ�ꋅ�ʏ�̂Q�_�̋������ȈՋߎ��l�i���x�D��̂��߁j�Ŕ�r���A�߂��Ǝv����ق����̗p����B
        angle d1_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_CLOSE_TO); //Rz�̍�
        angle d1_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_CLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_CLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) { //���߂������̗p
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) {
        angle d1_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_ANTICLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 >= d2) { //��艓�������̗p
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        angle d1_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_COUNTERCLOCKWISE);
        angle d1_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_COUNTERCLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_COUNTERCLOCKWISE);
        angle d2_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_COUNTERCLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        angle d1_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_CLOCKWISE);
        angle d1_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_CLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_CLOCKWISE);
        angle d2_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_CLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else {
        //��������
        throwGgafCriticalException("GgafDxKuroko::getRzRyMvAngDistanceTwd() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDxKuroko::getRzRyFaceAngDistanceTwd(angle prm_target_ang_rz, angle prm_target_ang_ry,int prm_way,
                                               angle& out_d_ang_rz, angle& out_d_ang_ry) {
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_CLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_CLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_CLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }

    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_ANTICLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 >= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_COUNTERCLOCKWISE);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_COUNTERCLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_COUNTERCLOCKWISE);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_COUNTERCLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_CLOCKWISE);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_CLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_CLOCKWISE);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_CLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else {
        //��������
        throwGgafCriticalException("GgafDxKuroko::getRzRyMvAngDistanceTwd() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDxKuroko::setRzRyMvAng(angle prm_ang_rz, angle prm_ang_ry) {
    if (prm_ang_rz != _ang_rz_mv || prm_ang_ry !=_ang_ry_mv ) {
        _ang_rz_mv = UTIL::simplifyAng(prm_ang_rz);
        _ang_ry_mv = UTIL::simplifyAng(prm_ang_ry);
        UTIL::convRzRyToVector(_ang_rz_mv, _ang_ry_mv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _ang_rz_mv;
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ang_ry_mv;
    }
}

void GgafDxKuroko::setRzRyMvAng_by_RyRz(angle prm_ang_ryRz_Ry, angle prm_ang_ryRz_Rz) {
    angle RyRz_Ry = UTIL::simplifyAng(prm_ang_ryRz_Ry);
    angle RyRz_Rz = UTIL::simplifyAng(prm_ang_ryRz_Rz);
    float out_vY, out_vZ;
    UTIL::convRzRyToVector(RyRz_Ry, D360ANG-RyRz_Rz, _vX, out_vY, out_vZ);
    _vY = -1.0f*out_vZ;
    _vZ = out_vY;
    UTIL::convVectorToRzRy(_vX, _vZ, _vY, _ang_rz_mv, _ang_ry_mv);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _ang_rz_mv;
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ang_ry_mv;
    }
}


void GgafDxKuroko::setMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //�A�N�^�[�̍��W�ɓ������̂ŁA�������Ȃ��B
    } else {
        UTIL::convVectorToRzRy( vx,  vy,  vz,
                               _vX, _vY, _vZ,
                               _ang_rz_mv, _ang_ry_mv );
        if (_relate_RzFaceAng_with_RzMvAng_flg) {
            _pActor->_rz = _ang_rz_mv;
        }
        if (_relate_RyFaceAng_with_RyMvAng_flg) {
            _pActor->_ry = _ang_ry_mv;
        }
    }
}

void GgafDxKuroko::reverseMvAng() {
    _vX = -_vX;
    _vY = -_vY;
    _vZ = -_vZ;
    _ang_rz_mv = UTIL::simplifyAng(_ang_rz_mv-D180ANG);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _ang_rz_mv;
    }
}

void GgafDxKuroko::setStopTargetMvAngTwd(const GgafDxGeometricActor* prm_pActor_target) {
    setStopTargetMvAngTwd(
        prm_pActor_target->_x,
        prm_pActor_target->_y,
        prm_pActor_target->_z
    );
}

void GgafDxKuroko::setStopTargetMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //�A�N�^�[�̍��W�ɓ������̂ŁA�������Ȃ��B
    } else {
        angle angRz_Target;
        angle angRy_Target;
        float dummy1, dummy2, dummy3;

        UTIL::convVectorToRzRy(
                       vx, vy, vz,
                       dummy1, dummy2, dummy3,
                       angRz_Target, angRy_Target
                     );
        setStopTargetRzMvAng(angRz_Target);
        setStopTargetRyMvAng(angRy_Target);
    }
}

void GgafDxKuroko::turnRzRyFaceAngTo(angle prm_ang_rz_target, angle prm_ang_ry_target,
                                     angvelo prm_angvelo, angacce prm_angacce,
                                     int prm_way, bool prm_optimize_ang) {
    angle out_d_ang_rz;
    angle out_d_ang_ry;
    if (prm_optimize_ang) {
        getRzRyFaceAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target,prm_way,
                                   out_d_ang_rz, out_d_ang_ry);
    } else {
        out_d_ang_rz = getFaceAngDistance(AXIS_Z, prm_ang_rz_target, prm_way);
        out_d_ang_ry = getFaceAngDistance(AXIS_Y, prm_ang_ry_target, prm_way);
    }
    double drz = ABS(out_d_ang_rz);
    double dry = ABS(out_d_ang_ry);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_ang_rz > 0) {
            setFaceAngVelo(AXIS_Z, prm_angvelo);
            setFaceAngAcce(AXIS_Z, prm_angacce);
        } else {
            setFaceAngVelo(AXIS_Z, -prm_angvelo);
            setFaceAngAcce(AXIS_Z, -prm_angacce);
        }

        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_ang_ry > 0) {
            setFaceAngVelo(AXIS_Y, rv);
            setFaceAngAcce(AXIS_Y, ra);
        } else {
            setFaceAngVelo(AXIS_Y, -rv);
            setFaceAngAcce(AXIS_Y, -ra);
        }
    } else if (drz < dry) {
        double drr = drz / dry ;

        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_ang_rz > 0) {
            setFaceAngVelo(AXIS_Z, rv);
            setFaceAngAcce(AXIS_Z, ra);
        } else {
            setFaceAngVelo(AXIS_Z, -rv);
            setFaceAngAcce(AXIS_Z, -ra);
        }
        if (out_d_ang_ry > 0) {
            setFaceAngVelo(AXIS_Y, prm_angvelo);
            setFaceAngAcce(AXIS_Y, prm_angacce);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angvelo);
            setFaceAngAcce(AXIS_Y, -prm_angacce);
        }
    } else {
        if (out_d_ang_rz > 0) {
            setFaceAngVelo(AXIS_Z, prm_angvelo);
            setFaceAngAcce(AXIS_Z, prm_angacce);
        } else {
            setFaceAngVelo(AXIS_Z, -prm_angvelo);
            setFaceAngAcce(AXIS_Z, -prm_angacce);
        }
        if (out_d_ang_ry > 0) {
            setFaceAngVelo(AXIS_Y, prm_angvelo);
            setFaceAngAcce(AXIS_Y, prm_angacce);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angvelo);
            setFaceAngAcce(AXIS_Y, -prm_angacce);
        }
    }

    setStopTargetFaceAng(AXIS_Z, prm_ang_rz_target);
    setStopTargetFaceAng(AXIS_Y, prm_ang_ry_target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKuroko::turnFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                  angvelo prm_angvelo, angacce prm_angacce,
                                  int prm_way, bool prm_optimize_ang) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //���g�̍��W�ɓ������̂ŁA�������Ȃ�
    } else {
        angle out_angRz_Target;
        angle out_angRy_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_angRz_Target, out_angRy_Target);

        turnRzRyFaceAngTo(out_angRz_Target, out_angRy_Target,
                          prm_angvelo, prm_angacce,
                          prm_way, prm_optimize_ang);
    }
}


void GgafDxKuroko::turnFaceAng(axis prm_axis,
                               angle prm_angular_distance,
                               angvelo prm_angvelo, angacce prm_angacce) {
    int s = SGN(prm_angular_distance);
    setFaceAngVelo(prm_axis, ABS(prm_angvelo)*s);
    setFaceAngAcce(prm_axis, ABS(prm_angacce)*s);
    setStopTargetFaceAng(prm_axis, (*(_actor_ang_face[prm_axis])) + prm_angular_distance);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}


void GgafDxKuroko::turnRzFaceAngTo(angle prm_ang_rz_target,
                                    angvelo prm_angvelo, angacce prm_angacce,
                                    int prm_way) {
    if (getFaceAngDistance(AXIS_Z, prm_ang_rz_target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Z, prm_angvelo);
        setFaceAngAcce(AXIS_Z, prm_angacce);
    } else {
        setFaceAngVelo(AXIS_Z, -prm_angvelo);
        setFaceAngAcce(AXIS_Z, -prm_angacce);
    }
    setStopTargetFaceAng(AXIS_Z, prm_ang_rz_target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKuroko::turnRyFaceAngTo(angle prm_ang_ry_target,
                                   angvelo prm_angvelo, angacce prm_angacce,
                                   int prm_way) {
    if (getFaceAngDistance(AXIS_Y, prm_ang_ry_target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Y, prm_angvelo);
        setFaceAngAcce(AXIS_Y, prm_angacce);
    } else {
        setFaceAngVelo(AXIS_Y, -prm_angvelo);
        setFaceAngAcce(AXIS_Y, -prm_angacce);
    }
    setStopTargetFaceAng(AXIS_Y, prm_ang_ry_target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKuroko::rollFaceAngTo(angle prm_ang_rx_Target,
                                   angvelo prm_angvelo, angacce prm_angacce,
                                   int prm_way) {
    if (getFaceAngDistance(AXIS_X, prm_ang_rx_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_X, prm_angvelo);
        setFaceAngAcce(AXIS_X, prm_angacce);
    } else {
        setFaceAngVelo(AXIS_X, -prm_angvelo);
        setFaceAngAcce(AXIS_X, -prm_angacce);
    }
    setStopTargetFaceAng(AXIS_X, prm_ang_rx_Target);
}

void GgafDxKuroko::turnRzRyMvAngTo(angle prm_ang_rz_target, angle prm_ang_ry_target,
                                   angvelo prm_angvelo, angacce prm_angacce,
                                   int prm_way, bool prm_optimize_ang) {
    angle out_d_ang_rz;
    angle out_d_ang_ry;
    if (prm_optimize_ang) {
        getRzRyMvAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target,prm_way,
                                out_d_ang_rz, out_d_ang_ry);
    } else {
        out_d_ang_rz = getRzMvAngDistance(prm_ang_rz_target, prm_way);
        out_d_ang_ry = getRyMvAngDistance(prm_ang_ry_target, prm_way);
    }

    //Rz, Ry ���A�ڕW�A���O���֓����ɓ��B����悤�Ɋp���x�𒲐�
    double drz = ABS(out_d_ang_rz);
    double dry = ABS(out_d_ang_ry);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_ang_rz > 0) {
            setRzMvAngVelo(prm_angvelo);
            setRzMvAngAcce(prm_angacce);
        } else {
            setRzMvAngVelo(-prm_angvelo);
            setRzMvAngAcce(-prm_angacce);
        }
        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_ang_ry > 0) {
            setRyMvAngVelo(rv);
            setRyMvAngAcce(ra);
        } else {
            setRyMvAngVelo(-rv);
            setRyMvAngAcce(-ra);
        }
    } else if (drz < dry) {
        double drr = drz / dry;

        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_ang_rz > 0) {
            setRzMvAngVelo(rv);
            setRzMvAngAcce(ra);
        } else {
            setRzMvAngVelo(-rv);
            setRzMvAngAcce(-ra);
        }
        if (out_d_ang_ry > 0) {
            setRyMvAngVelo(prm_angvelo);
            setRyMvAngAcce(prm_angacce);
        } else {
            setRyMvAngVelo(-prm_angvelo);
            setRyMvAngAcce(-prm_angacce);
        }
    } else {
        if (out_d_ang_rz > 0) {
            setRzMvAngVelo(prm_angvelo);
            setRzMvAngAcce(prm_angacce);
        } else {
            setRzMvAngVelo(-prm_angvelo);
            setRzMvAngAcce(-prm_angacce);
        }
        if (out_d_ang_ry > 0) {
            setRyMvAngVelo(prm_angvelo);
            setRyMvAngAcce(prm_angacce);
        } else {
            setRyMvAngVelo(-prm_angvelo);
            setRyMvAngAcce(-prm_angacce);
        }
    }
    setStopTargetRzMvAng(prm_ang_rz_target);
    setStopTargetRyMvAng(prm_ang_ry_target);
}

void GgafDxKuroko::turnMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                angvelo prm_angvelo, angacce prm_angacce,
                                int prm_way, bool prm_optimize_ang) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //�A�N�^�[�̍��W�ɓ������̂ŁA�������Ȃ��B
    } else {
        angle out_angRz_Target;
        angle out_angRy_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_angRz_Target,
                               out_angRy_Target);
        turnRzRyMvAngTo(out_angRz_Target, out_angRy_Target,
                        prm_angvelo, prm_angacce,
                        prm_way, prm_optimize_ang);
    }
}

void GgafDxKuroko::turnRzMvAng(angle prm_angular_distance,
                               angvelo prm_angvelo, angacce prm_angacce) {
    int s = SGN(prm_angular_distance);
    setRzMvAngVelo(ABS(prm_angvelo) * s);
    setRzMvAngAcce(ABS(prm_angacce) * s);
    setStopTargetRzMvAng(_ang_rz_mv+prm_angular_distance);
}

void GgafDxKuroko::turnRyMvAng(angle prm_angular_distance,
                               angvelo prm_angvelo, angacce prm_angacce) {
    int s = SGN(prm_angular_distance);
    setRyMvAngVelo(ABS(prm_angvelo) * s);
    setRyMvAngAcce(ABS(prm_angacce) * s);
    setStopTargetRyMvAng(_ang_ry_mv+prm_angular_distance);
}

void GgafDxKuroko::turnRzMvAngTo(angle prm_ang_rz_target,
                                 angvelo prm_angvelo, angacce prm_angacce,
                                 int prm_way) {
    if (getRzMvAngDistance(prm_ang_rz_target, prm_way) > 0) {
        setRzMvAngVelo(prm_angvelo);
        setRzMvAngAcce(prm_angacce);
    } else {
        setRzMvAngVelo(-prm_angvelo);
        setRzMvAngAcce(-prm_angacce);
    }
    setStopTargetRzMvAng(prm_ang_rz_target);
}

void GgafDxKuroko::turnRyMvAngTo(angle prm_ang_ry_target,
                                 angvelo prm_angvelo, angacce prm_angacce,
                                 int prm_way) {
    if (getRyMvAngDistance(prm_ang_ry_target, prm_way) > 0) {
        setRyMvAngVelo(prm_angvelo);
        setRyMvAngAcce(prm_angacce);
    } else {
        setRyMvAngVelo(-prm_angvelo);
        setRyMvAngAcce(-prm_angacce);
    }
    setStopTargetRyMvAng(prm_ang_ry_target);
}

void GgafDxKuroko::takeoverMvFrom(GgafDxKuroko* const prm_pKuroko) {
    // �L�����̈ړ����p�P�ʃx�N�g��
    _vX = prm_pKuroko->_vX;
    _vY = prm_pKuroko->_vY;
    _vZ = prm_pKuroko->_vZ;
    // �ړ����p��Z����]�p
    _ang_rz_mv = prm_pKuroko->_ang_rz_mv;
    // �ړ����p��Y����]�p
    _ang_ry_mv = prm_pKuroko->_ang_ry_mv;
    // �ړ����x
    _velo_mv = prm_pKuroko->_velo_mv;
    // �ړ����x���
    _top_velo_mv = prm_pKuroko->_top_velo_mv;
    // �ړ����x����
    _bottom_velo_mv = prm_pKuroko->_bottom_velo_mv;
    // �ړ������x
    _acc_mv = prm_pKuroko->_acc_mv;
    // �ړ����x
    //_jerkMv = prm_pKuroko->_jerkMv;
}

void GgafDxKuroko::stopTurnMvAng() {
    _is_targeting_ang_rz_mv = false;
    _ang_rz_mv_targeting_stop_flg = false;
    _is_targeting_ang_ry_mv = false;
    _ang_ry_mv_targeting_stop_flg = false;
    if (_pAsstC) {
        _pAsstC->stopTurnMvAng();
    }
    setRzRyMvAngVelo(0, 0);
    setRzRyMvAngAcce(0, 0);
}

void GgafDxKuroko::stopTurnFaceAng() {
    _is_targeting_ang_face[AXIS_X] = false;
    _is_targeting_ang_face[AXIS_Y] = false;
    _is_targeting_ang_face[AXIS_Z] = false;
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
    if (_pAsstB) {
        _pAsstB->stopTurnFaceAng();
    }
    setFaceAngVelo(AXIS_Z, 0);
    setFaceAngVelo(AXIS_Y, 0);
    setFaceAngAcce(AXIS_Z, 0);
    setFaceAngAcce(AXIS_Y, 0);
}

bool GgafDxKuroko::isTurningFaceAng() const {
    if (_is_targeting_ang_face[AXIS_X] ||
        _is_targeting_ang_face[AXIS_Y] ||
        _is_targeting_ang_face[AXIS_Z] ) {
        return true;
    } else {
        if (_pAsstB) {
            return _pAsstB->isTurningFaceAng();
        } else {
            return false;
        }
        return false;
    }
}

bool GgafDxKuroko::isTurningMvAng() const {
    if (_is_targeting_ang_rz_mv || _is_targeting_ang_ry_mv) {
        return true;
    } else {
        if (_pAsstC) {
            return _pAsstC->isTurningMvAng();
        } else {
            return false;
        }
    }
}

void GgafDxKuroko::stopMv() {
   setMvAcce(0);
   setMvVelo(0);
   if (_pAsstA) {
       _pAsstA->stopSlidingMv();
   }
}

GgafDxKuroko::~GgafDxKuroko() {
    GGAF_DELETE_NULLABLE(_pAsstA);
    GGAF_DELETE_NULLABLE(_pAsstB);
    GGAF_DELETE_NULLABLE(_pAsstC);
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
// �Q����]�A���O���l (_ang_rz_mv, _ang_ry_mv) �ŕ\�����@�̂Q��ޗp�ӂ����B�N�H�[�^�j�I���͍��̂Ƃ��떳���B
// _ang_rz_mv �� Z����]�p�A _ang_ry_mv �� Y����]�p ���Ӗ����Ă���B
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
// ���������̖{�N���X�ł́A�悭�g���̂͂Q���\���̕��ŁA���\�b�h�� _ang_rz_mv �� _ang_ry_mv �𑀍삷����̂����S�ƂȂ��Ă���B
// ���͌��Ǔ����ŒP�ʕ����x�N�g�������߂Ă���̂����A���W��]�v�Z���A�����^�� _ang_rz_mv �� _ang_ry_mv �ł��񂴂�s���Ă���A
// �Ō�ɂP��P�ʃx�N�g�������߂�B�Ƃ������������̂ł͂ƍl�������߁A���̂悤�Ȑ݌v�ɂȂ����B
// TODO:�œK���̗]�n�����Ԏc���Ă���n�Y�B�܂������B
// (_ang_rz_mv, _ang_ry_mv)�����\�b�h�ɂ�葀�삵�āA�e�t���[���̍Ō�̓��������ŕ����x�N�g��(_vX, _vY, _vZ) �𓯊������Ă���B
// (_vX, _vY, _vZ)�����o�[�����\�b�h���g�킸���ڑ��삷��ƁA(_ang_rz_mv, _ang_ry_mv)�Ƃ̓����������̂Œ��ӁB
// �{�N���X�̃��\�b�h���g�p�������ł́A����Ȃ��Ƃ͋N����Ȃ��B
//
// ���ړ����x:Velo or MvVelo��
// �L�����́u�ړ����x�v(_velo_mv)��ێ����Ă���B�ړ�������@�͊ȒP�ŁA��{�I�ɖ��t���[���u�ړ����p�v�Ɂu�ړ����x�v�����������B
// ���W�����́u�ړ����p�v(_vX, _vY, _vZ)�Ɂu�ړ����x�v(_velo_mv)���|���Z���Ă���B
// �P�t���[����̍��W�͌��݂̍��W���� (_vX*_velo_mv, _vY*_velo_mv, _vZ*_velo_mv) �ړ������ꏊ�ł���B
// ���̃x�N�g���ɖ{���C�u�����̒P�ʋ���(�Q�[�����̒����P�ƍl���鐮���{�l�j���悶��B
// ����āA(_vX*_velo_mv*LEN_UNIT, _vY*_velo_mv*LEN_UNIT, _vZ*_velo_mv*LEN_UNIT)���P�t���[����̍��W�����B

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
