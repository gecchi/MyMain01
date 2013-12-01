#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKurokoA::GgafDxKurokoA(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {

    for (int i = 0; i < 3; i++) { // i=0:X���A1:Y���A2:Z�� ��\��
        //���ʕ��p
        _angFace[i] = 0; //0 angle �� �R���̕��p�������Ă���
        //���ʕ��p�̊p���x�i���ʕ��p�̑����j= 0 angle/fream
        _angveloFace[i] = 0; //1�t���[���ɉ��Z����鐳�ʕ��p�̊p�����B�f�t�H���g�͐��ʕ��p�̊p���������A�܂�U����������B
        //���ʕ��p�̊p���x��� �� 360,000 angle/fream
        _angveloTopFace[i] = D360ANG; //_angveloFace[n] �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȑ��ʕ��p�ɐU����������o���鎖���Ӗ�����
        //���ʕ��p�̊p���x���� �� -360,000 angle/fream
        _angveloBottomFace[i] = D360ANG * -1; //_angveloFace[n] �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȑ��ʕ��p�ɐU����������o���鎖���Ӗ�����
        //���ʕ��p�̊p�����x�i�p���x�̑����j �� 0 angle/fream^2
        _angacceFace[i] = 0; //_angveloFace[n] �̑����B�f�t�H���g�͐��ʕ��p�̊p�����x����

        _angjerkFace[i] = 0;
        //�ڕW���ʕ��p�ւ̎��������t���O = ����
        _face_ang_targeting_flg[i] = false;
        //�ڕW���ʕ��p�ւ̎�����~�t���O = ����
        _face_ang_targeting_stop_flg[i] = false;
        //�ڕW�̐��ʕ��p
        _angTargetFace[i] = 0; //�ڕW���ʕ��p�ւ̎�������t���O = �����A�̏ꍇ�͖��Ӗ�
        //�ڕW�̐��ʕ��p������~�@�\���L���ɂȂ��]����
        _face_ang_target_allow_way[i] = TURN_BOTH;
        //�ڕW�̐��ʕ��p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj
        _face_ang_target_allow_velo[i] = D180ANG;
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

    _slide_mv_flg = false;
    _slide_mv_endacc_flg = true;
    _slide_mv_top_velo = 0;
    _slide_mv_end_velo = 0;
    _slide_mv_target_distance = 0;
    _slide_mv_moved_distances = 0;
    _slide_mv_target_frames = 0;
    _slide_mv_frame_of_spent = 0;
    _slide_mv_p1 = 0;
    _slide_mv_p2 = 0;
    _slide_mv_progress = -1;


    _taget_face_ang_alltime_flg = false;
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_tx = 0;
    _taget_face_ang_alltime_ty = 0;
    _taget_face_ang_alltime_tz = 0;
    _taget_face_ang_alltime_angVelo = 0;
    _taget_face_ang_alltime_angAcce = 0;
    _taget_face_ang_alltime_way = TURN_CLOSE_TO;
    _taget_face_ang_alltime_optimize_ang = true;


    _smooth_turn_rz_faceang_flg = false;
    _smooth_turn_rz_faceang_endacc_flg = true;
    _smooth_turn_rz_faceang_top_angvelo = 0;
    _smooth_turn_rz_faceang_end_angvelo = 0;
    _smooth_turn_rz_faceang_target_distanceangle = 0;
    _smooth_turn_rz_faceang_turned_angles = 0;
    _smooth_turn_rz_faceang_angacce_a0 = 0;
    _smooth_turn_rz_faceang_targetangle_sgn = 1;
    _smooth_turn_rz_faceang_target_frames = 0;
    _smooth_turn_rz_faceang_frame_of_spent = 0;
    _smooth_turn_rz_faceang_p0 = 0;
    _smooth_turn_rz_faceang_p1 = 0;
    _smooth_turn_rz_faceang_p2 = 0;
    _smooth_turn_rz_faceang_progress = -1;
}

void GgafDxKurokoA::behave() {

    //���ʕ��p����
    for (int i = 0; i < 3; i++) {
        if (_face_ang_targeting_flg[i]) { //�^�[�Q�b�g����������ꍇ
            _angveloFace[i] += _angacceFace[i];
            if (_angveloFace[i] > _angveloTopFace[i]) {
                _angveloFace[i] = _angveloTopFace[i];
            } else if (_angveloFace[i] < _angveloBottomFace[i]) {
                _angveloFace[i] = _angveloBottomFace[i];
            }

            if (_angveloFace[i] > 0) { //�����v���̏ꍇ
                angle angDistance = getFaceAngDistance((axis)i, _angTargetFace[i], TURN_COUNTERCLOCKWISE);
                if (_angveloFace[i] > angDistance && _face_ang_target_allow_way[i] != TURN_CLOCKWISE
                        && _face_ang_target_allow_velo[i] >= _angveloFace[i]) {
                    addFaceAng((axis)i, angDistance);
                    if (_face_ang_targeting_stop_flg[i]) {
                        _face_ang_targeting_flg[i] = false; //�t���O��߂��ďI��
                        _face_ang_targeting_stop_flg[i] = false;
                    }
                } else {
                    addFaceAng((axis)i, _angveloFace[i]);
                }
            } else if (_angveloFace[i] < 0) { //���v���̏ꍇ
                angle angDistance = getFaceAngDistance((axis)i, _angTargetFace[i], TURN_CLOCKWISE);
                if (_angveloFace[i] < angDistance && _face_ang_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_ang_target_allow_velo[i] <= _angveloFace[i]) { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                    addFaceAng((axis)i, angDistance);
                    if (_face_ang_targeting_stop_flg[i]) { //��~���ėL��Ȃ��
                        _face_ang_targeting_flg[i] = false; //�t���O��߂��ďI��
                    }
                } else {
                    addFaceAng((axis)i, _angveloFace[i]);
                }
            } else {
                //_angveloFace[i] == 0
                addFaceAng((axis)i, 0);
            }

            if (_face_ang_targeting_flg[i] == false) {
                //�ڕW�����ɓ��B�������̏���
                //_angveloTopFace[i] = D360ANG; //���ʕ��p�̊p���x��� �� 360,000 angle/fream
                //_angveloBottomFace[i] = D360ANG * -1; //���ʕ��p�̊p���x���� �� -360,000 angle/fream

                //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
                _angacceFace[i] = 0; //����]�����p�A�p���x���O��
                setFaceAngVelo((axis)i, 0); //����]�����p�A�p�����x���O��
            }

        } else {
            //if (_angacceFace[i] != 0) {
            //�t���[�����̐��ʕ��p����̏���
            _angveloFace[i] += _angacceFace[i];
            if (_angveloFace[i] != 0) {
                addFaceAng((axis)i, _angveloFace[i]);
            }
            //}
        }
    }



    //�Ȃ߂炩��]�V�[�N�G���X�N����
    if (_smooth_turn_rz_faceang_flg) {
        if (_smooth_turn_rz_faceang_target_frames < 0) {
            //�ڕW�����w��̏ꍇ
            if (_smooth_turn_rz_faceang_progress == 0) {
                //�񕜃t�F�[�Y
                setFaceAngAcce(AXIS_Z, _smooth_turn_rz_faceang_angacce_a0);
                _smooth_turn_rz_faceang_progress++;
            } else if (_smooth_turn_rz_faceang_progress == 1) {
                //�񕜒�
                if (_smooth_turn_rz_faceang_turned_angles >= _smooth_turn_rz_faceang_p0) {
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 2) {
                //�����ݒ�
                setFaceAngAcceByD(
                    AXIS_Z,
                    _smooth_turn_rz_faceang_p1-_smooth_turn_rz_faceang_turned_angles,
                    _smooth_turn_rz_faceang_top_angvelo);
                _smooth_turn_rz_faceang_progress++;
            } else if (_smooth_turn_rz_faceang_progress == 3) {
                //������
                if (_smooth_turn_rz_faceang_turned_angles >= _smooth_turn_rz_faceang_p1) {
                    //p1 �ɓ��B����� ������
                    setFaceAngAcce(AXIS_Z, 0);
                    setFaceAngVelo(AXIS_Z, _smooth_turn_rz_faceang_top_angvelo);
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 4) {
                //������
                if (_smooth_turn_rz_faceang_turned_angles >= _smooth_turn_rz_faceang_p2) {
                    //p2 �ɓ��B����� ����t���[�����猸����
                    setFaceAngAcceByD(
                        AXIS_Z,
                        _smooth_turn_rz_faceang_target_distanceangle - _smooth_turn_rz_faceang_turned_angles,
                        _smooth_turn_rz_faceang_end_angvelo);
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 5) {
                //������
                if (_pActor->getBehaveingFrame() % 4U == 0) {
                    //�␳�E�␳�E�␳
                    setFaceAngAcceByD(
                            AXIS_Z,
                            _smooth_turn_rz_faceang_target_distanceangle - _smooth_turn_rz_faceang_turned_angles,
                            _smooth_turn_rz_faceang_end_angvelo);
                }
                if (_smooth_turn_rz_faceang_turned_angles >= _smooth_turn_rz_faceang_target_distanceangle) {
                    //�ڕW�����֓��B
                    setFaceAngVelo(AXIS_Z, _smooth_turn_rz_faceang_end_angvelo);
                    if (_smooth_turn_rz_faceang_endacc_flg) {
                        setFaceAngAcce(AXIS_Z, 0);
                    }
                    _smooth_turn_rz_faceang_progress++;
                    _smooth_turn_rz_faceang_flg = false; //�����܂�
                }
            }
        } else {
            //�ڕW���Ԏw��̏ꍇ
            if (_smooth_turn_rz_faceang_progress == 0) {
                _TRACE_("_smooth_turn_rz_faceang_progress == 0");
                _TRACE_("_smooth_turn_rz_faceang_p1="<<_smooth_turn_rz_faceang_p1<<" _smooth_turn_rz_faceang_top_angvelo="<<_smooth_turn_rz_faceang_top_angvelo);
                //�����ݒ�
                setFaceAngAcceByT(AXIS_Z, _smooth_turn_rz_faceang_p1, _smooth_turn_rz_faceang_top_angvelo);
                _smooth_turn_rz_faceang_progress++;
            } else if (_smooth_turn_rz_faceang_progress == 1) {
                _TRACE_("_smooth_turn_rz_faceang_progress == 1");
                _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent<<" _smooth_turn_rz_faceang_p1="<<_smooth_turn_rz_faceang_p1);
                //������
                if (_smooth_turn_rz_faceang_frame_of_spent >= _smooth_turn_rz_faceang_p1) {
                    //p1 �ɓ��B����� ������
                    setFaceAngAcce(AXIS_Z, 0);
                    setFaceAngVelo(AXIS_Z, _smooth_turn_rz_faceang_top_angvelo);
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 2) {
                _TRACE_("_smooth_turn_rz_faceang_progress == 2");
                _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent<<"  _smooth_turn_rz_faceang_p2="<<_smooth_turn_rz_faceang_p2);
                //������
                if (_smooth_turn_rz_faceang_frame_of_spent >= _smooth_turn_rz_faceang_p2) {
                    //p2 �ɓ��B����� ����t���[�����猸����
                    setFaceAngAcceByT(AXIS_Z, _smooth_turn_rz_faceang_target_frames - _smooth_turn_rz_faceang_frame_of_spent, _smooth_turn_rz_faceang_end_angvelo);
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 3) {

                _TRACE_("_smooth_turn_rz_faceang_progress == 3");
                _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent<<"  _smooth_turn_rz_faceang_target_frames="<<_smooth_turn_rz_faceang_target_frames);

                //������
                if (_pActor->getBehaveingFrame() % 4U == 0) {
                    //�␳�E�␳�E�␳
                    setFaceAngAcceByT(AXIS_Z, _smooth_turn_rz_faceang_target_frames - _smooth_turn_rz_faceang_frame_of_spent, _smooth_turn_rz_faceang_end_angvelo);
                }

                if (_smooth_turn_rz_faceang_frame_of_spent >= _smooth_turn_rz_faceang_target_frames) {

                    _TRACE_("//�ڕW�����֓��B");
                    _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent<<"  _smooth_turn_rz_faceang_target_frames="<<_smooth_turn_rz_faceang_target_frames);


                    //�ڕW�����֓��B
                    setFaceAngVelo(AXIS_Z, _smooth_turn_rz_faceang_end_angvelo);
                    if (_smooth_turn_rz_faceang_endacc_flg) {
                        setFaceAngAcce(AXIS_Z, 0);
                    }
                    _smooth_turn_rz_faceang_progress++;
                    _smooth_turn_rz_faceang_flg = false; //�����܂�
                }
            }
        }
    } else {
        _smooth_turn_rz_faceang_progress = -1;
    }

    if (_smooth_turn_rz_faceang_flg) {
        _smooth_turn_rz_faceang_frame_of_spent++;
        _smooth_turn_rz_faceang_turned_angles += ABS(_angveloFace[AXIS_Z]);
    } else {

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
    //�Ȃ߂炩�ړ��V�[�N�G���X�N����
    if (_slide_mv_flg) {
        if (_slide_mv_target_frames < 0) {
            //�ڕW�����w��̏ꍇ
            if (_slide_mv_progress == 0) {
                //�����ݒ�
                setMvAcceByD(_slide_mv_p1, _slide_mv_top_velo);
                _slide_mv_progress++;
            } else if (_slide_mv_progress == 1) {
                //������
                if (_slide_mv_moved_distances >= _slide_mv_p1) {
                    //p1 �ɓ��B����� ������
                    setMvAcce(0);
                    setMvVelo(_slide_mv_top_velo);
                    _slide_mv_progress++;
                }
            } else if (_slide_mv_progress == 2) {
                //������
                if (_slide_mv_moved_distances >= _slide_mv_p2) {
                    //p2 �ɓ��B����� ����t���[�����猸����
                    setMvAcceByD(_slide_mv_target_distance - _slide_mv_moved_distances, _slide_mv_end_velo);
                    _slide_mv_progress++;
                }
            } else if (_slide_mv_progress == 3) {
                //������
                if (_pActor->getBehaveingFrame() % 8U == 0) {
                    //�␳�E�␳�E�␳
                    setMvAcceByD(_slide_mv_target_distance - _slide_mv_moved_distances, _slide_mv_end_velo);
                }

                if (_slide_mv_moved_distances >= _slide_mv_target_distance) {
                    //�ڕW�����֓��B
                    setMvVelo(_slide_mv_end_velo);
                    if (_slide_mv_endacc_flg) {
                        setMvAcce(0);
                    }
                    _slide_mv_progress++;
                    _slide_mv_flg = false; //�����܂�
                }
            }
        } else {
            //�ڕW���Ԏw��̏ꍇ
            if (_slide_mv_progress == 0) {
                //�����ݒ�
                setMvAcceByT(_slide_mv_p1, _slide_mv_top_velo);
                _slide_mv_progress++;
            } else if (_slide_mv_progress == 1) {
                //������
                if (_slide_mv_frame_of_spent >= _slide_mv_p1) {
                    //p1 �ɓ��B����� ������
                    setMvAcce(0);
                    setMvVelo(_slide_mv_top_velo);
                    _slide_mv_progress++;
                }
            } else if (_slide_mv_progress == 2) {
                //������
                if (_slide_mv_frame_of_spent >= _slide_mv_p2) {
                    //p2 �ɓ��B����� ����t���[�����猸����
                    setMvAcceByT(_slide_mv_target_frames - _slide_mv_frame_of_spent, _slide_mv_end_velo);
                    _slide_mv_progress++;
                }
            } else if (_slide_mv_progress == 3) {
                //������
                if (_pActor->getBehaveingFrame() % 8U == 0) {
                    //�␳�E�␳�E�␳
                    setMvAcceByT(_slide_mv_target_frames - _slide_mv_frame_of_spent, _slide_mv_end_velo);
                }

                if (_slide_mv_frame_of_spent >= _slide_mv_target_frames) {
                    //�ڕW�����֓��B
                    setMvVelo(_slide_mv_end_velo);
                    if (_slide_mv_endacc_flg) {
                        setMvAcce(0);
                    }
                    _slide_mv_progress++;
                    _slide_mv_flg = false; //�����܂�
                }
            }
        }
    } else {
        _slide_mv_progress = -1;
    }

    if (_slide_mv_flg) {
        if (_slide_mv_target_frames < 0) {
            _slide_mv_moved_distances+=ABS(_veloMv);
        } else {
            _slide_mv_frame_of_spent++;
        }
    } else {

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

void GgafDxKurokoA::setFaceAng(axis prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = UTIL::simplifyAng(prm_angFace);
}

void GgafDxKurokoA::setFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    UTIL::convVectorToRzRy(
                   prm_tx - _pActor->_x,
                   prm_ty - _pActor->_y,
                   prm_tz - _pActor->_z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDxKurokoA::addFaceAng(axis prm_axis, angle prm_angDistance) {
    angle angOffsetrot_FaceAng;
    angOffsetrot_FaceAng = prm_angDistance;
    if (_angveloBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAng = _angveloBottomFace[prm_axis];
    } else if (prm_angDistance > _angveloTopFace[prm_axis]) {
        angOffsetrot_FaceAng = _angveloTopFace[prm_axis];
    }
    setFaceAng(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAng);
}

void GgafDxKurokoA::setFaceAngVelo(axis prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloTopFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloTopFace[prm_axis];
    } else if (prm_angveloRot < _angveloBottomFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloBottomFace[prm_axis];
    } else {
        _angveloFace[prm_axis] = prm_angveloRot;
    }
}

void GgafDxKurokoA::setFaceAngVelo(angvelo prm_axis_x_angveloRot,
                                   angvelo prm_axis_y_angveloRot,
                                   angvelo prm_axis_z_angveloRot) {
    setFaceAngVelo(AXIS_X, prm_axis_x_angveloRot);
    setFaceAngVelo(AXIS_Y, prm_axis_y_angveloRot);
    setFaceAngVelo(AXIS_Z, prm_axis_z_angveloRot);
}

void GgafDxKurokoA::forceFaceAngVeloRange(axis prm_axis,
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

void GgafDxKurokoA::setFaceAngAcce(axis prm_axis, angacce prm_angacceRot) {
    _angacceFace[prm_axis] = prm_angacceRot;
}

void GgafDxKurokoA::setStopTargetFaceAngTwd(axis prm_axis,
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

void GgafDxKurokoA::setStopTargetFaceAng(axis prm_axis,
                                         angle prm_angTargetRot,
                                         int prm_way_allow,
                                         angvelo prm_angveloAllow) {
    _face_ang_targeting_flg[prm_axis] = true;
    _face_ang_targeting_stop_flg[prm_axis] = true;
    _angTargetFace[prm_axis] = UTIL::simplifyAng(prm_angTargetRot);
    _face_ang_target_allow_way[prm_axis] = prm_way_allow;
    _face_ang_target_allow_velo[prm_axis] = prm_angveloAllow;
}

angle GgafDxKurokoA::getFaceAngDistance(axis prm_axis, coord prm_tx, coord prm_ty, int prm_way) {
    return getFaceAngDistance(
               prm_axis,
               UTIL::getAngle2D(prm_tx-(_pActor->_x), prm_ty-(_pActor->_y)),
               prm_way);
}

angle GgafDxKurokoA::getFaceAngDistance(axis prm_axis, angle prm_angTargetRot, int prm_way) {
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
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(5)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(6)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���̂�����p�̋��������߂�܂���Bprm_way�͐������ł����H(2)�Bprm_way="<<prm_way<<" _pActor="<<_pActor->getName());
}

void GgafDxKurokoA::forceMvVeloRange(velo prm_velo) {
    forceMvVeloRange(-prm_velo, prm_velo);
}

void GgafDxKurokoA::forceMvVeloRange(velo prm_veloMv01, velo prm_veloMv02) {
    if (prm_veloMv01 < prm_veloMv02) {
        _veloTopMv = prm_veloMv02;
        _veloBottomMv = prm_veloMv01;
    } else {
        _veloTopMv = prm_veloMv01;
        _veloBottomMv = prm_veloMv02;
    }
    setMvVelo(_veloMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKurokoA::setMvVelo(velo prm_veloMv) {
    if (prm_veloMv > _veloTopMv) {
        _veloMv = _veloTopMv;
    } else if (prm_veloMv < _veloBottomMv) {
        _veloMv = _veloBottomMv;
    } else {
        _veloMv = prm_veloMv;
    }
}

void GgafDxKurokoA::addMvVelo(velo prm_veloMv_Offset) {
    setMvVelo(_veloMv + prm_veloMv_Offset);
}

void GgafDxKurokoA::setMvAcce(int prm_acceMove) {
    _accMv = prm_acceMove;
}

frame GgafDxKurokoA::setMvAcceToStop(coord prm_target_distance) {
    double acc = UTIL::getAcceToStop(prm_target_distance, _veloMv);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _accMv = acc;
    return (frame)((2.0*prm_target_distance) / _veloMv); //�g�p�t���[����
}

frame GgafDxKurokoA::setFaceAngAcceToStop(axis prm_axis, angle prm_target_angle_distance) {
    double acc = UTIL::getAcceToStop(prm_target_angle_distance, _angveloFace[prm_axis]);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacceFace[prm_axis] = acc;
    return (frame)((2.0*prm_target_angle_distance) / _angveloFace[prm_axis]); //�g�p�t���[����
}

frame GgafDxKurokoA::setMvAcceByD(coord prm_target_distance, velo prm_target_velo) {
    double acc = UTIL::getAcceByD(prm_target_distance, _veloMv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _accMv = acc;
    return (frame)((1.0*prm_target_velo - _veloMv) / acc); //�g�p�t���[����
}
frame GgafDxKurokoA::setFaceAngAcceByD(axis prm_axis, angle prm_target_angle_distance, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByD(prm_target_angle_distance, _angveloFace[prm_axis], prm_target_angvelo);
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

coord GgafDxKurokoA::setMvAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByT(prm_target_frames, _veloMv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _accMv = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_veloMv + prm_target_velo) * prm_target_frames) / 2 ;
}
angle GgafDxKurokoA::setFaceAngAcceByT(axis prm_axis, frame prm_target_frames, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByT(prm_target_frames, _angveloFace[prm_axis], prm_target_angvelo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacceFace[prm_axis] = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_angveloFace[prm_axis] + prm_target_angvelo) * prm_target_frames) / 2 ;
}
void GgafDxKurokoA::slideMvByDT(velo prm_end_velo, coord prm_target_distance,
                                int prm_target_frames, float prm_p1, float prm_p2,
                                bool prm_endacc_flg) {
    _slide_mv_flg = true;
    _slide_mv_p1 = (int)(prm_target_frames*prm_p1);
    _slide_mv_p2 = (int)(prm_target_frames*prm_p2);
    _slide_mv_end_velo = prm_end_velo;
    _slide_mv_target_distance = prm_target_distance;
    _slide_mv_moved_distances = 0;
    _slide_mv_target_frames = prm_target_frames;
    _slide_mv_frame_of_spent = 0;
    _slide_mv_progress = 0;

    //���g�b�v�X�s�[�h(Vt) ���v�Z��
    //
    //    ���x(v)
    //     ^
    //     |                          D:�ڕW�ړ�����
    //     |                         V0:�����_�̑��x
    //     |                         Vt:�g�b�v�X�s�[�h
    //     |                         Ve:�ŏI���x
    //   Vt|....�Q�Q�Q�Q�Q           Te:�ڕW���ԁi�t���[�����j
    //     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��
    //   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��
    //     | /  :         :    |        (0.0 < p1 < p2 < 1.0)
    //     |/   :         :    |
    //   V0|    :    D    :    |
    //     |    :         :    |
    //   --+----+---------+----+-----> ����(t:�t���[��)
    //   0 |  p1*Te     p2*Te  Te
    //
    // �ړ�����D�́A���̑�`�{�����̒����`�{�E�̑�` �̖ʐςł���A
    // D = (1/2) (V0 + Vt) p1 Te + Vt (p2-p1)Te  +  (1/2) (Ve + Vt) (1-p2)Te
    // �����Vt�ɂ��ĉ���
    // Vt = ( 2D - p1 Te V0 + (p2 - 1) Te Ve ) / ( (p2 - p1 + 1) Te )
    _slide_mv_top_velo =
         ((2.0*prm_target_distance) - (prm_p1*prm_target_frames*_veloMv) + ((prm_p2-1.0)*prm_target_frames*prm_end_velo))
         / ((prm_p2-prm_p1+1.0)*prm_target_frames);

}

void GgafDxKurokoA::slideMvByVD(velo prm_top_velo, velo prm_end_velo,
                                coord prm_target_distance, float prm_p1, float prm_p2,
                                bool prm_endacc_flg) {
    _slide_mv_flg = true;
    _slide_mv_endacc_flg = prm_endacc_flg;
    _slide_mv_top_velo = prm_top_velo;
    _slide_mv_end_velo = prm_end_velo;
    _slide_mv_target_distance = prm_target_distance;
    _slide_mv_moved_distances = 0;
    _slide_mv_target_frames = -1; //�ڕW���Ԃ͎g��Ȃ��ꍇ�͕���ݒ肵�Ă���(��������Ŏg�p)
    _slide_mv_frame_of_spent = 0;
    _slide_mv_p1 = (int)(prm_target_distance*prm_p1);
    _slide_mv_p2 = (int)(prm_target_distance*prm_p2);
    _slide_mv_progress = 0;
}


void GgafDxKurokoA::slideMvByVT(velo prm_top_velo, velo prm_end_velo,
                                int prm_target_frames, float prm_p1, float prm_p2,
                                bool prm_endacc_flg) {
    _slide_mv_flg = true;
    _slide_mv_endacc_flg = prm_endacc_flg;
    _slide_mv_top_velo = prm_top_velo;
    _slide_mv_end_velo = prm_end_velo;
    _slide_mv_target_distance = 0;
    _slide_mv_moved_distances = 0;
    _slide_mv_target_frames = prm_target_frames;
    _slide_mv_frame_of_spent = 0;
    _slide_mv_p1 = (int)(prm_target_frames*prm_p1);
    _slide_mv_p2 = (int)(prm_target_frames*prm_p1);
    _slide_mv_progress = 0;
}


//void GgafDxKurokoA::slideMv4(velo prm_end_velo, coord prm_target_distance, int prm_target_frames,
//                                                      bool prm_endacc_flg) {
//    _slide_mv_flg = true;
//    _slide_mv_p1 = (int)(prm_target_distance*1.0 / 4.0);
//    _slide_mv_p2 = (int)(prm_target_distance*3.0 / 4.0);
//    _slide_mv_end_velo = prm_end_velo;
//    _slide_mv_target_distance = prm_target_distance;
//    _slide_mv_moved_distances = 0;
//    _slide_mv_target_frames = -1; //�ڕW���Ԃ͎g��Ȃ��ꍇ�͕���ݒ肵�Ă���(��������Ŏg�p)
//    _slide_mv_frame_of_spent = 0;
//    _slide_mv_progress = 0;
//
//    //    ���x
//    //     ^
//    //     |                       D:�ړ�����
//    //     |                      V0:�����_�̑��x
//    //     |                      Vt:����1/4 �` 3/4 �̑��x
//    //     |                      Ve:�ŏI�ڕW���B���x
//    //   Vt|....�Q�Q�Q�Q            Te:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
//    //     |   /|      |�_
//    //   Ve|../.|......|..�_
//    //     | /  |      |   |
//    //     |/   |      |   |
//    //   V0| 1/4|  2/4 |1/4|
//    //     |  D |   D  | D |
//    //   --+----+------+---+-----> ����(�t���[��)
//    //   0 |   tp1    tp2  Te
//
//    // ������ �u��`�{�����`�{��`�v �̖ʐρB�䂦��
//    // (1/4)D = (1/2) (V0 + Vt) tp1           �c�@ ��`
//    // (2/4)D = Vt (tp2 - tp1)                �c�A �����`
//    // (1/4)D = (1/2) (Ve + Vt) (Te - tp2)     �c�B ��`
//
//
//    // (1/4)D = Vt tp1 -  (1/2) tp1 (Vt - V0)
//    // �܂��A������ �u�S�̂̒����` �] �O�p�`�����Q�v �̖ʐςł�����B�䂦��
//    // D = Te Vt - (1/2) tp1 (Vt - V0) - (1/2) (Te - tp2) (Vt - Ve) �c�C
//
//    //�@���
//    //tp1 = (D / 2 (V0 + Vt) )        �c�D
//    //�B���
//    //(Te - tp2) = (D / 2 (Ve + Vt) )  �c�E
//    //�D�E���C�֑��
//    //D = Te Vt - D(Vt - V0) / 4 (V0 + Vt) - D(Vt - Ve) / 4 (Ve + Vt)
//    //�����Vt�ɂ��ĉ�����
//
//    //    Vt =
//    //    (sqrt((-9*V0^2+9*Ve*V0-9*Ve^2)*D^4-(4*Te*V0^3-6*Te*Ve*V0^2-6*Te*Ve^2*V0+4*Te*Ve^3)*D^3+(-4*Te^2*V0^4+8*Te^2*Ve*V0^3-12*Te^2*Ve^2*V0^2+8*Te^2*Ve^3*V0-4*Te^2*Ve^4)*D^2-4*Te^4*Ve^2*V0^4+8*Te^4*Ve^3*V0^3-4*Te^4*Ve^4*V0^2)/(4*3^(3/2)*Te^2)-
//    //    (Te^3*(8*V0^3-12*Ve*V0^2-12*Ve^2*V0+8*Ve^3)-27*D^3)/(216*Te^3))^(1/3)+(9*D^2+Te^2*(4*V0^2-4*Ve*V0+4*Ve^2))/(36*Te^2*(
//    //    sqrt((-9*V0^2+9*Ve*V0-9*Ve^2)*D^4-(4*Te*V0^3-6*Te*Ve*V0^2-6*Te*Ve^2*V0+4*Te*Ve^3)*D^3+(-4*Te^2*V0^4+8*Te^2*Ve*V0^3-12*Te^2*Ve^2*V0^2+8*Te^2*Ve^3*V0-4*Te^2*Ve^4)*D^2-4*Te^4*Ve^2*V0^4+8*Te^4*Ve^3*V0^3-4*Te^4*Ve^4*V0^2)/(4*3^(3/2)*Te^2)-
//    //    (Te^3*(8*V0^3-12*Ve*V0^2-12*Ve^2*V0+8*Ve^3)-27*D^3)/(216*Te^3))^(1/3))+(3*D-Te*(2*V0+2*Ve))/(6*Te)
//    //�Ȃ񂶂Ⴑ��E�E�E
//
//
//
//
//
//    _slide_mv_top_velo = (8.0*prm_target_distance/prm_target_frames - _veloMv - prm_end_velo) / 6.0;
//}



bool GgafDxKurokoA::isSlidingMv() {
    return _slide_mv_flg;
}

void GgafDxKurokoA::stopSlidingMv() {
    _slide_mv_flg = false;
}

bool GgafDxKurokoA::isJustFinishSlidingMv() {
    if (_slide_mv_flg == false && _slide_mv_progress != -1) {
        return true;
    } else {
        return false;
    }
}

void GgafDxKurokoA::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _angRzMv) {
        _angRzMv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDxKurokoA::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRzBottomMv > prm_angDistance) {
        angOffset = _angveloRzBottomMv;
    } else if (prm_angDistance > _angveloRzTopMv) {
        angOffset = _angveloRzTopMv;
    }
    setRzMvAng(_angRzMv + angOffset);
}

void GgafDxKurokoA::setRzMvAngVelo(angvelo prm_angveloRzMv) {
    if (prm_angveloRzMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzMv;
    }
}

void GgafDxKurokoA::setRzMvAngAcce(angacce prm_angacceRzMv) {
    _angacceRzMv = prm_angacceRzMv;
}

void GgafDxKurokoA::forceRzMvAngVeloRange(angvelo prm_angveloRzMv01,
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

void GgafDxKurokoA::setStopTargetRzMvAng(angle prm_angTargetRzMv,
                                         int prm_way_allow,
                                         angvelo prm_angveloAllowRyMv) {
    _mv_ang_rz_target_flg = true;
    _mv_ang_rz_target_stop_flg = true;
    _angTargetRzMv = UTIL::simplifyAng(prm_angTargetRzMv);
    _mv_ang_rz_target_allow_way = prm_way_allow;
    _mv_ang_rz_target_allow_velo = prm_angveloAllowRyMv;
}

angle GgafDxKurokoA::getRzMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRzMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)), prm_way);
}

angle GgafDxKurokoA::getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way) {
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
                throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(5)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(6)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
    throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() ���̂�����p�̋��������߂�܂���(1)�B_pActor="<<_pActor->getName());
}


//void GgafDxKurokoA::setRyMvAngTwd(coord prm_tx, coord prm_ty) {
//    setRyMvAng(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)));
//}

void GgafDxKurokoA::setRyMvAng(angle prm_ang) {
    if (prm_ang != _angRyMv) {
        _angRyMv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKurokoA::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRyBottomMv > prm_angDistance) {
        angOffset = _angveloRyBottomMv;
    } else if (prm_angDistance > _angveloRyTopMv) {
        angOffset = _angveloRyTopMv;
    }
    setRyMvAng(_angRyMv + angOffset);
}

void GgafDxKurokoA::setRyMvAngVelo(angvelo prm_angveloRyMv) {
    if (prm_angveloRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRyMv;
    }
}

void GgafDxKurokoA::setRyMvAngAcce(angacce prm_angacceRyMv) {
    _angacceRyMv = prm_angacceRyMv;
}

void GgafDxKurokoA::forceRyMvAngVeloRange(angvelo prm_angveloRyMv01,
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

void GgafDxKurokoA::forceRzRyMvAngVeloRange(angvelo prm_angveloRzRyMv01, angvelo prm_angveloRzRyMv02) {
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
void GgafDxKurokoA::setRzRyMvAngVelo(angvelo prm_angveloRzRyMv) {
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
void GgafDxKurokoA::setRzRyMvAngAcce(angacce prm_angacceRzRyMv) {
    _angacceRzMv = prm_angacceRzRyMv;
    _angacceRyMv = prm_angacceRzRyMv;
}
void GgafDxKurokoA::setRzRyMvAngAcce(angacce prm_angacceRzMv, angacce prm_angacceRyMv) {
    _angacceRzMv = prm_angacceRzMv;
    _angacceRyMv = prm_angacceRyMv;
}

void GgafDxKurokoA::setRzRyMvAngVelo(angvelo prm_angveloRzMv, angvelo prm_angveloRyMv) {
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

void GgafDxKurokoA::setStopTargetRyMvAng(angle prm_angTargetRyMv,
                                         int prm_way_allow,
                                         angvelo prm_angveloAllowRyMv) {
    _mv_ang_ry_target_flg = true;
    _mv_ang_ry_target_stop_flg = true;
    _angTargetRyMv = UTIL::simplifyAng(prm_angTargetRyMv);
    _mv_ang_ry_target_allow_way = prm_way_allow;
    _mv_ang_ry_target_allow_velo = prm_angveloAllowRyMv;
}

angle GgafDxKurokoA::getRyMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRyMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
                                        prm_way);
}

angle GgafDxKurokoA::getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way) {
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
                throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(5)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(6)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
    throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() ���̂�����p�̋��������߂�܂���(1)�B_pActor="<<_pActor->getName());
}

void GgafDxKurokoA::getRzRyMvAngDistance(int prm_way,
                                         angle prm_target_angRz, angle prm_target_angRy,
                                         angle& out_d_angRz, angle& out_d_angRy) {
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        //�ڕW�ɓ��B���邽�߂ɂ́A��������ɂQ�p�^�[������B
        //���ꂼ�ꋅ�ʏ�̂Q�_�̋������ȈՋߎ��l�i���x�D��̂��߁j�Ŕ�r���A�߂��Ǝv����ق����̗p����B
        angle d1_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOSE_TO); //Rz�̍�
        angle d1_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) > ABS(d1_angRy) ? ABS(d1_angRz) : ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOSE_TO);
        angle d2 = ABS(d2_angRz) > ABS(d2_angRy) ? ABS(d2_angRz) : ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        angle d1_angRz = getRzMvAngDistance(prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getRyMvAngDistance(prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d1 = ABS(d1_angRz) > ABS(d1_angRy) ? ABS(d1_angRz) : ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getRzMvAngDistance(prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) > ABS(d2_angRy) ? ABS(d2_angRz) : ABS(d2_angRy);
        if (d1 >= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        out_d_angRz = getRzMvAngDistance(prm_target_angRz, TURN_COUNTERCLOCKWISE);
        out_d_angRy = getRyMvAngDistance(prm_target_angRy, TURN_COUNTERCLOCKWISE);
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        out_d_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOCKWISE);
        out_d_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOCKWISE);
    } else {
        //��������
        throwGgafCriticalException("GgafDxKurokoA::getRzRyMvAngDistance() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDxKurokoA::getRzRyFaceAngDistance(int prm_way,
                                           angle prm_target_angRz, angle prm_target_angRy,
                                           angle& out_d_angRz, angle& out_d_angRy) {
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) > ABS(d1_angRy) ? ABS(d1_angRz) : ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOSE_TO) * ((UTIL::COS[UTIL::simplifyAng(prm_target_angRz*2)/SANG_RATE]/2.0) + 0.5);
        angle d2 = ABS(d2_angRz) > ABS(d2_angRy) ? ABS(d2_angRz) : ABS(d2_angRy);
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
        angle d1 = ABS(d1_angRz) > ABS(d1_angRy) ? ABS(d1_angRz) : ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) > ABS(d2_angRy) ? ABS(d2_angRz) : ABS(d2_angRy);
        if (d1 >= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        out_d_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_COUNTERCLOCKWISE);
        out_d_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_COUNTERCLOCKWISE);
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        out_d_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOCKWISE);
        out_d_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOCKWISE);
    } else {
        //��������
        throwGgafCriticalException("GgafDxKurokoA::getRzRyMvAngDistance() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDxKurokoA::setRzRyMvAng(angle prm_angRz, angle prm_angRy) {
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

void GgafDxKurokoA::setRzRyMvAng_by_RyRz(angle prm_angRyRz_Ry, angle prm_angRyRz_Rz) {
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


void GgafDxKurokoA::setMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
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

void GgafDxKurokoA::reverseMvAng() {
    _vX = -_vX;
    _vY = -_vY;
    _vZ = -_vZ;
    _angRzMv = UTIL::simplifyAng(_angRzMv-D180ANG);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDxKurokoA::setStopTargetMvAngTwd(GgafDxGeometricActor* prm_pActor_Target) {
    setStopTargetMvAngTwd(
        prm_pActor_Target->_x,
        prm_pActor_Target->_y,
        prm_pActor_Target->_z
    );
}

void GgafDxKurokoA::setStopTargetMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
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

void GgafDxKurokoA::turnRzRyFaceAngTo(angle prm_angRz_Target, angle prm_angRy_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    if (prm_optimize_ang) {
        getRzRyFaceAngDistance(prm_way,
                               prm_angRz_Target, prm_angRy_Target,
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

void GgafDxKurokoA::turnFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
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

void GgafDxKurokoA::turnRzFaceAngTo(angle prm_angRz_Target,
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

void GgafDxKurokoA::turnRyFaceAngTo(angle prm_angRy_Target,
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

void GgafDxKurokoA::turnRxSpinAngTo(angle prm_angRx_Target,
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

void GgafDxKurokoA::turnRzRyMvAngTo(angle prm_angRz_Target, angle prm_angRy_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    if (prm_optimize_ang) {
        getRzRyMvAngDistance(prm_way,
                             prm_angRz_Target, prm_angRy_Target,
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


void GgafDxKurokoA::turnMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
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


void GgafDxKurokoA::turnRzMvAngTo(angle prm_angRz_Target,
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

void GgafDxKurokoA::turnRyMvAngTo(angle prm_angRy_Target,
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


void GgafDxKurokoA::turnSmoothlyRzFaceAngByDtTo(
        angle prm_angRz_Target, int prm_way,
        angvelo prm_end_angvelo,
        int prm_target_frames, float prm_p1, float prm_p2,
        bool prm_endacc_flg) {

    angle dang = getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;

    _smooth_turn_rz_faceang_flg = true;
    _smooth_turn_rz_faceang_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_turn_rz_faceang_p2 = (int)(prm_target_frames*prm_p2);
    _smooth_turn_rz_faceang_end_angvelo = prm_end_angvelo;
    _smooth_turn_rz_faceang_target_distanceangle = dang;
    _smooth_turn_rz_faceang_target_frames = prm_target_frames;
    _smooth_turn_rz_faceang_frame_of_spent = 0;
    _smooth_turn_rz_faceang_progress = 0;

    //���g�b�v�X�s�[�h(Vt) ���v�Z��
    //
    //    ���x(v)
    //     ^
    //     |                          D:�ڕW�ړ�����
    //     |                         V0:�����_�̑��x
    //     |                         Vt:�g�b�v�X�s�[�h
    //     |                         Ve:�ŏI���x
    //   Vt|....�Q�Q�Q�Q�Q           Te:�ڕW���ԁi�t���[�����j
    //     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��
    //   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��
    //     | /  :         :    |        (0.0 < p1 < p2 < 1.0)
    //     |/   :         :    |
    //   V0|    :    D    :    |
    //     |    :         :    |
    //   --+----+---------+----+-----> ����(t:�t���[��)
    //   0 |  p1*Te     p2*Te  Te
    //
    // �ړ�����D�́A���̑�`�{�����̒����`�{�E�̑�` �̖ʐςł���A
    // D = (1/2) (V0 + Vt) p1 Te + Vt (p2-p1)Te  +  (1/2) (Ve + Vt) (1-p2)Te
    // �����Vt�ɂ��ĉ���
    // Vt = ( 2D - p1 Te V0 + (p2 - 1) Te Ve ) / ( (p2 - p1 + 1) Te )
    _smooth_turn_rz_faceang_top_angvelo =
         ((2.0*dang) - (prm_p1*prm_target_frames*_angveloFace[AXIS_Z]) + ((prm_p2-1.0)*prm_target_frames*prm_end_angvelo))
         / ((prm_p2-prm_p1+1.0)*prm_target_frames);

}


void GgafDxKurokoA::turnSmoothlyRzFaceAngByVdTo(
        angle prm_angRz_Target, int prm_way,
        angvelo prm_top_angvelo, angvelo prm_end_angvelo,
        float prm_p1, float prm_p2,
        bool prm_endacc_flg ) {

    double target_angle_distance = getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way); //��
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
    int s_target_angle_distance = SGN(target_angle_distance);                     //�Ƃ̐���
    int s_w0 = SGN(_angveloFace[AXIS_Z]); //��0�̐���

    if (s_w0 == 0 || s_target_angle_distance == s_w0) {  //��������v
        //�y�p�^�[���P�z
        //
        //        �p���x(��)                       ��0:�����_�̑��x      (_angveloFace[])
        //         ^                               ��t:�g�b�v�X�s�[�h    (prm_top_angvelo)
        //         |                               ��e:�ŏI���x          (prm_end_angvelo)
        //         |                                ��:�ڕW��]�����p��  (��1+��2+��3)                     �E�E�E �v�Z���ċ��߂�
        //         |                                p1:�g�b�v�X�s�[�h�ɒB����p�����ƂȂ�悤�ȁA�p����(��)�ɑ΂��銄��
        //         |       ��=��1+��2+��3               �܂�     ��1 = ��*p1 �ƂȂ�悤�� p1 (0.0�`1.0)
        //      ��t|....___________                 p2:�������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
        //         |   /|         |�_                   �܂� ��1+��2 = ��*p2 �ƂȂ�悤�� p2 (0.0�`1.0)
        //      ��e|../.|.........|..�_             T1: ��1     = ��*p1 �ɔ�₳���K�v���ԃt���[����     �E�E�E �v�Z���ċ��߂�
        //         | /  |         |    |            T2: ��1+��2 = ��*p2 �ɔ�₳���K�v���ԃt���[����     �E�E�E �v�Z���ċ��߂�
        //         |/   |         |    |            Te:��₳���K�v���ԃt���[����                        �E�E�E �v�Z���ċ��߂�
        //      ��0|��1 |   ��2   |��3 |
        //         |    |         |    |
        //       --+----+---------+----+-----> ����(t:�t���[��)
        //       0 |    T1        T2   Te
        //

        double W0 = _angveloFace[AXIS_Z];
        double Wt = ABS(prm_top_angvelo) * s_target_angle_distance;
        double We = ABS(prm_end_angvelo) * s_target_angle_distance;
        _smooth_turn_rz_faceang_flg = true;
        _smooth_turn_rz_faceang_endacc_flg = prm_endacc_flg;
        _smooth_turn_rz_faceang_top_angvelo = Wt;
        _smooth_turn_rz_faceang_end_angvelo = We;
        _smooth_turn_rz_faceang_target_distanceangle = ABS(target_angle_distance);
        _smooth_turn_rz_faceang_turned_angles = 0;
        _smooth_turn_rz_faceang_targetangle_sgn = s_target_angle_distance;
        _smooth_turn_rz_faceang_target_frames = -1; //���Ԗ��g�p
        _smooth_turn_rz_faceang_frame_of_spent = 0;
        _smooth_turn_rz_faceang_p0 = 0; //���g�p
        _smooth_turn_rz_faceang_p1 = ABS(target_angle_distance) * prm_p1;
        _smooth_turn_rz_faceang_p2 = ABS(target_angle_distance) * prm_p2;
        _smooth_turn_rz_faceang_progress = 2; //�񕜃t�F�[�Y���΂�
    } else {

        //                                                      ��0:�����_�̑��x      (_angveloFace[])
        //        ���x(v)                                       ��t:�g�b�v�X�s�[�h    (prm_top_angvelo)
        //        ^                                              ��e:�ŏI���x          (prm_end_angvelo)
        //        |                                               ��:�X�^�[�g���_�̊p�x����̖ڕW��]�����p                     �E�E�E �v�Z���ċ��߂�
        //        |                                              ��p:�p���x�O�ɂȂ��Ă���̖ڕW��]�����p(��p1 + ��p2 + ��p3)   �E�E�E �v�Z���ċ��߂�
        //        |                                                s:�p���x�O�ɂȂ�܂ł̋t��]����                             �E�E�E �v�Z���ċ��߂�
        //        |                                               p1:�g�b�v�X�s�[�h�ɒB����p�����ƂȂ�悤�ȁA�p����(��)�ɑ΂��銄��
        //        |           ��  = (��p1-s) + ��p2 + ��p3                 �܂� ��p1 = ��p*p1 �ƂȂ�悤�� p1 (0.0�`1.0)    ����
        //        |           ��p = ��p1 + ��p2 + ��p3            p2:�������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
        //     ��t|...............___________                          �܂� ��p1+��p2 = ��p*p2 �ƂȂ�悤�� p2 (0.0�`1.0)  ����
        //        |            A /|         |�_B                  T0: �p���x�O�ɂȂ�܂łɔ�₳���K�v���ԃt���[����  �E�E�E �v�Z���ċ��߂�
        //        |             / |         |  �_                 T1: ��p1      = ��p*p1 �ɔ�₳���K�v���ԃt���[����  �E�E�E �v�Z���ċ��߂�
        //        |            /  |         |    �_               T2: ��p1+��p2 = ��p*p2 �ɔ�₳���K�v���ԃt���[����  �E�E�E �v�Z���ċ��߂�
        //        |           /   |         |      �_             Te:��₳���K�v���ԃt���[����                        �E�E�E �v�Z���ċ��߂�
        //        |          /��p1|   ��p2  | ��p3   �_
        //        |         /:    |         |          �_
        //     ��e|......../.:....|.........|............�_  C
        //        |       /  :    |         |             |
        //        |      / s :    |         |             |
        //   -----+-----+----+----+---------+-------------+----------> ����(t:�t���[��)
        //      0 | s�^ Ts       T1        T2            Te
        //        |�^
        //     ��0| ^    <-s-><-----------��-------------->
        //        | |
        //        | |    <--------------��p--------------->
        //        | |
        //        | |    <--��p1--><--��p2--><----��p3---->
        //        | |
        //        | �����񕜊p�����x(a0)�Œ�
        //        |
        //
        //
        //        ���� t �� 0 �` Ts ���̊p���x�� W �Ƃ����
        //        ���� W = a0*t - W0 ���    (�������񕜊p�����x(a0)�͒萔)
        //        t = Ts �̎�  W = 0  �ł���̂�
        //        0 = a0*Ts - W0
        //        Ts = W0/a0  �E�E�E(1)
        //        �܂�
        //        s = (1/2) * Ts * -W0       (��O�p�`�̖ʐ�)
        //        �����(1)����
        //        s = (1/2) * (W0/a0) * -W0
        //        s = -(W0^2)/(2*a0)  �E�E�E(2)
        //        �܂�
        //
        //        D + s =  Dp = (Dp1 + Dp2 + Dp3) �E�E�E(3)
        //        ���
        //        Dp = D + (-W0^2/(2*a0))  �E�E�E(4)
        double W0 = _angveloFace[AXIS_Z];
        double Wt = ABS(prm_top_angvelo) * s_target_angle_distance;
        double We = ABS(prm_end_angvelo) * s_target_angle_distance;
        double a0 = 500 * -s_w0; //�����p���x�̐����t
        double s = -(W0*W0)/(2*a0);
        double Dp = s + target_angle_distance;

        _TRACE_("a0="<<a0);
        _TRACE_("s="<<s);
        _TRACE_("Dp="<<Dp);
        _smooth_turn_rz_faceang_flg = true;
        _smooth_turn_rz_faceang_endacc_flg = prm_endacc_flg;
        _smooth_turn_rz_faceang_top_angvelo = Wt;
        _smooth_turn_rz_faceang_end_angvelo = We;
        _smooth_turn_rz_faceang_target_distanceangle = ABS(Dp) + ABS(s);
        _smooth_turn_rz_faceang_turned_angles = 0;
        _smooth_turn_rz_faceang_angacce_a0 = a0;
        _smooth_turn_rz_faceang_targetangle_sgn = s_target_angle_distance;
        _smooth_turn_rz_faceang_target_frames = -1; //���Ԗ��g�p
        _smooth_turn_rz_faceang_frame_of_spent = 0;
        _smooth_turn_rz_faceang_p0 = ABS(s);
        _smooth_turn_rz_faceang_p1 = ABS(s)  +  (ABS(Dp) * prm_p1);
        _smooth_turn_rz_faceang_p2 = ABS(s)  +  (ABS(Dp) * prm_p2);
        _smooth_turn_rz_faceang_progress = 0; //�񕜃t�F�[�Y����

    }
    _TRACE_("GgafDxKurokoA::turnSmoothlyRzFaceAngByVdTo");
    _TRACE_("_smooth_turn_rz_faceang_flg="<<_smooth_turn_rz_faceang_flg);
    _TRACE_("_smooth_turn_rz_faceang_endacc_flg="<<_smooth_turn_rz_faceang_endacc_flg);
    _TRACE_("_smooth_turn_rz_faceang_top_angvelo="<<_smooth_turn_rz_faceang_top_angvelo);
    _TRACE_("_smooth_turn_rz_faceang_end_angvelo="<<_smooth_turn_rz_faceang_end_angvelo);
    _TRACE_("_smooth_turn_rz_faceang_target_distanceangle="<<_smooth_turn_rz_faceang_target_distanceangle);
    _TRACE_("_smooth_turn_rz_faceang_turned_angles="<<_smooth_turn_rz_faceang_turned_angles);
    _TRACE_("_smooth_turn_rz_faceang_angacce_a0="<<_smooth_turn_rz_faceang_angacce_a0);
    _TRACE_("_smooth_turn_rz_faceang_targetangle_sgn="<<_smooth_turn_rz_faceang_targetangle_sgn);
    _TRACE_("_smooth_turn_rz_faceang_target_frames="<<_smooth_turn_rz_faceang_target_frames);
    _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent);
    _TRACE_("_smooth_turn_rz_faceang_p0="<<_smooth_turn_rz_faceang_p0);
    _TRACE_("_smooth_turn_rz_faceang_p1="<<_smooth_turn_rz_faceang_p1);
    _TRACE_("_smooth_turn_rz_faceang_p2="<<_smooth_turn_rz_faceang_p2);
    _TRACE_("_smooth_turn_rz_faceang_progress="<<_smooth_turn_rz_faceang_progress);



//    } else {  //�������˂���
//        //---------------------------------------------------------------------------------------------------------------------------------------------------------
//        //�y�p�^�[���Q�z
//        //                                                          ��0:�����_�̑��x      (_angveloFace[])
//        //             ���x(v)                                      ��t:�g�b�v�X�s�[�h    (prm_top_angvelo)
//        //            ^                                             ��e:�ŏI���x          (prm_end_angvelo)
//        //            |                                              ��:�ڕW��]�����p��  (��1+��2+��3)                     �E�E�E �v�Z���ċ��߂�
//        //            |                                              p1:�g�b�v�X�s�[�h�ɒB����p�����ƂȂ�悤�ȁA�p����(��)�ɑ΂��銄��
//        //            |                                                  �܂�     ��1 = ��*p1 �ƂȂ�悤�� p1 (0.0�`1.0)
//        //            |        ��= (-s + s) + ��1 + ��2 + ��3        p2:�������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
//        //         ��t|.............___________                          �܂� ��1+��2 = ��*p2 �ƂȂ�悤�� p2 (0.0�`1.0)
//        //            |            /|         |�_                    Ts: ���x�X�^�[�g���_�ɖ߂��Ă��鎞�_�ɔ�₳���K�v���ԃt���[����     �E�E�E �v�Z���ċ��߂�
//        //            |           / |         |  �_                  T1: ��1     = ��*p1 �ɔ�₳���K�v���ԃt���[����     �E�E�E �v�Z���ċ��߂�
//        //            |          /  |         |    �_                T2: ��1+��2 = ��*p2 �ɔ�₳���K�v���ԃt���[����     �E�E�E �v�Z���ċ��߂�
//        //        -��0|........./��1|   ��2   | ��3  �_              Te:��₳���K�v���ԃt���[����                        �E�E�E �v�Z���ċ��߂�
//        //            |        /|   |         |        �_
//        //         ��e|......./.|...|.........|..........�_
//        //            |      /  |   |         |           |
//        //            |     / s |   |         |           |
//        //       -----+----/----+---+---------+-----------+----------> ����(t:�t���[��)
//        //          0 |-s /     Ts  T1        T2          Te
//        //            |  /
//        //            | /
//        //            |/
//        //         ��0|
//        //            |
//        //
//        //    ���� t �� 0 �` T1 ���̊p���x�� �ցA�p�����x�� a �Ƃ���B
//        //    ���� �� = a*t + ��0 ���
//        //    t = Ts  �̎�  �� = -��0  �ł���̂�
//        //    -��0 = a*Ts + ��0
//        //    ����� Ts �ɂ��ĉ�����
//        //    Ts = -(2*��0)/a    �E�E�E�@
//        //
//        //    ���� �� = a*t + ��0 ���
//        //    t = T1  �̎�  �� = ��t  �ł���̂�
//        //    ��t = a*T1 + ��0
//        //    ����� a �ɂ��ĉ�����
//        //    a = (��t-��0)/T1     �E�E�E�A
//        //
//        //    �A���@�֑��
//        //    Ts = -(2*��0) /( (��t-��0)/T1 )
//        //    Ts = (2*��0*T1) / (��0-��t)      �E�E�E�B
//        //
//        //    ������ T1�AT2�ATe  �����߂�
//        //    �� = ��1 + ��2 + ��3
//        //    ��`�{�����`�{��`�̖ʐς��
//        //    ��1 = (1/2) * (-��0 + ��t) * (T1-Ts)       �E�E�E �C
//        //    ��2 = (T2-T1) * ��t                       �E�E�E �D
//        //    ��3 = (1/2) * ( ��e + ��t) * (Te-T2)       �E�E�E �E
//        //
//        //    �B���C�֑��
//        //    ��1 = (1/2) * (-��0 + ��t) * (T1-(  (2*��0*T1) / (��0-��t)  ))
//        //    ��1 = ((��t+��0)*T1)/2      �E�E�E �F
//        //
//        //    ���Ƃ̓p�^�[���P���l��
//        //    �F���
//        //    T1= (2*��1)/(��t+��0)       �E�E�E �G
//        //
//        //    �G���D�֑��
//        //    ��2 = (T2-(  (2*��1)/(��t+��0)  )) * ��t
//        //    T2 = (��t*��2+��0*��2+2*��t*��1) / (��t*(��t+��0))    �E�E�E �H
//        //
//        //    �H���E�֑��
//        //    ��3 = (1/2) * ( ��e + ��t) * (Te-(  (��t*��2+��0*��2+2*��t*��1) / (��t*(��t+��0))  ))
//        //    Te = ((2*��t^2+2*��0*��t)*��3+(��t^2+(��e+��0)*��t+��0*��e)*��2+(2*��t^2+2*��e*��t)*��1) / (��t*(��t+��0)*(��t+��e))   �E�E�E�I
//        //
//        //
//        //    s�����߂�B�O�p�`�̖ʐς��
//        //    s = (1/2) * ((1/2) * Ts * -��0)   �E�E�E�J
//        //
//        //    �Ƃ����
//        //
//        //    Ts = (2*��0*T1) / (��0-��t)       �E�E�E�B
//        //    T1 = (2*��1)/(��t+��0)            �E�E�E�G
//        //    ��� �G���B�֑������
//        //    Ts = (2*��0* (  (2*��1)/(��t+��0)  ) ) / (��0-��t)
//        //    Ts = (4*��0*��1)/((��0-��t)*(��t+��0))  �E�E�E�K
//        //
//        //    ���̇K���J�֑������
//        //    s = (1/2) * ((1/2) * (  (4*��0*��1)/((��0-��t)*(��t+��0))  ) * -��0)
//        //    s = (��0^2*��1) / (��t^2-��0^2)   �E�E�E�L
//        //
//        //    �L�K�G�H�I���
//        //    s  = (��0^2*��1) / (��t^2-��0^2)
//        //    Ts = (4*��0*��1) / ((��0-��t)*(��t+��0))
//        //    T1 = (2*��1) / (��t+��0)
//        //    T2 = (��t*��2+��0*��2+2*��t*��1) / (��t*(��t+��0))
//        //    Te = ((2*��t^2+2*��0*��t)*��3+(��t^2+(��e+��0)*��t+��0*��e)*��2+(2*��t^2+2*��e*��t)*��1) / (��t*(��t+��0)*(��t+��e))
//
//        double D1 = D * prm_p1;
//        double D2 = D * (prm_p2 - prm_p1);    //D*(p2 - p1)
//        double D3 = D * (1.0 - prm_p2);       //D*(1 - p2)
//
//        double s  = (W0^2*D1) / (Wt^2-W0^2)
//        double Ts = (4*W0*D1) / ((W0-Wt)*(Wt+W0))
//        double T1 = (2*D1) / (Wt+W0)
//        double T2 = (Wt*D2+W0*D2+2*Wt*D1) / (Wt*(Wt+W0))
//        double Te = ((2*Wt^2+2*W0*Wt)*D3+(Wt^2+(We+W0)*Wt+W0*We)*D2+(2*Wt^2+2*We*Wt)*D1) / (Wt*(Wt+W0)*(Wt+We))
//
//        _smooth_turn_rz_faceang_flg = true;
//        _smooth_turn_rz_faceang_endacc_flg = prm_endacc_flg;
//        _smooth_turn_rz_faceang_top_angvelo = Wt;
//        _smooth_turn_rz_faceang_end_angvelo = We;
//        _smooth_turn_rz_faceang_target_distanceangle = D;
//        _smooth_turn_rz_faceang_target_frames = Te;
//        _smooth_turn_rz_faceang_frame_of_spent = 0;
//        _smooth_turn_rz_faceang_p1 = T1;
//        _smooth_turn_rz_faceang_p2 = T2;
//        _smooth_turn_rz_faceang_progress = 0;
//    }



}


void GgafDxKurokoA::takeoverMvFrom(GgafDxKurokoA* const prm_pKurokoA) {
    // �L�����̈ړ����p�P�ʃx�N�g��
    _vX = prm_pKurokoA->_vX;
    _vY = prm_pKurokoA->_vY;
    _vZ = prm_pKurokoA->_vZ;
    // �ړ����p��Z����]�p
    _angRzMv = prm_pKurokoA->_angRzMv;
    // �ړ����p��Y����]�p
    _angRyMv = prm_pKurokoA->_angRyMv;
    // �ړ����x
    _veloMv = prm_pKurokoA->_veloMv;
    // �ړ����x���
    _veloTopMv = prm_pKurokoA->_veloTopMv;
    // �ړ����x����
    _veloBottomMv = prm_pKurokoA->_veloBottomMv;
    // �ړ������x
    _accMv = prm_pKurokoA->_accMv;
    // �ړ����x
    //_jerkMv = prm_pKurokoA->_jerkMv;
}

GgafDxKurokoA::~GgafDxKurokoA() {
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
// �i�������̋@�\�� GgafDxKurokoB �ɏW�񂳂�Ɨ������N���X�ƂȂ�܂����I�j

//2010/02/19�ǋL
// �����܂ɁuRyRz�v�Ƃ����\�������݂���i�uRzRy�v�ƈقȂ�j���A����́uY����] �� Z����]�̏��Ԃ̈ړ����p�v��\���Ă���̂Œ��ӁB
//   �܂��A�u�ړ����p�iZ���j�v������]�̏��Ԃ̈Ⴂ�𖾊m�ɂ��邽��
//   �uRzRy��Rz�v�uRyRz��Rz�v�Ə������肵�Ă���Ƃ��������B�i�P�ɁuRz�v�����̏ꍇ�́uRzRy��Rz�v���Ӗ����Ă���j

//�ǋL
//�E���炩�ړ����\�ɁI

//TODO:
//���x�i�������x�j�̒ǉ�
//�C�ӎ���]�i�N�H�[�^�j�I���j
//�N���X�̔�剻 �� ���qB�������
//�y�����z��Z�߂�
