#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

//�y���������z�{���C�u�����̕\���ƍl����
//
//�����p�Ƃ������t�ɂ��ā�
//�u�ړ����p�i�����j�v�̓L�����̐i�s�����݂̂�\����B
//�u�ړ����x�v�Ɣ����āA�L�����͍��W�����ړ�����B
//�u����]���p�v�̓L�����̌����݂̂�\����B
//�L�����N�^����ʂ̏㕔���牺���ֈړ����Ă��A�L�����N�^�͉��������Ƃ͌��炸���@�Ɍ����Ăق����ꍇ������B�B
//�E�ɃL�������������āA���Ɉړ������������Ƃ�����B���ꂼ��ݒ肪�K�v�B

//���ړ����p��
//�L�������i�ޕ����A�܂�u�ړ����p�i�����j�v�̕����́A���_����P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g�� (_vX, _vY, _vZ) �ŕ\�����@�ƁA
//�ܓx�ƌo�x(�܂��́A�A�W�}�X�Ƌp)�̂Q�̃A���O���l (_angRzMove, _angRyMove) �ŕ\�����@�̂Q��ޗp�ӂ����B
//�P�Ɂu�ړ����p�v�ƌĂԏꍇ�́A�ړ������̃x�N�g����\�����Ă���ꍇ�����邪�A��L�̗��R�ɂ��
//�����ł́A�Q�̃A���O���l���Z�b�g�̎����u�ړ����p�v�ƌĂԏꍇ�������B
//�ŁA�ܓx�o�x�\���̏ꍇ�A�ܓx��Z����]�p�A�o�x��Y����]�p �ƌ����Ă鎖���ł���̂ŁA���ꂼ��̐����𕪂��ĕ\���������ꍇ
//���ꂼ��u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�ƕ\�����邱�Ƃɂ���B�E�E�E���p�A�ȂǂƂ������t�����A���e�͊p�x�̒l�ł��B
//�܂�A�u�ړ����p�iY���j�v�Ƃ������t�̌�b�́A�܂�肭�ǂ��ڂ����\������ƁA
//�u�L�����̐i�s�������A�����x�N�g���ł͖����ܓx�o�x�Ɍ����Ă�Z����]�p��Y����]�p�ŕ\�������ꍇ��Y����]�p�����݂̂̃A���O���l�v�Ƃ������ƂƂ���B
//
//�ړ����p�ɂ͈ܓx�o�x�w��(_angRzMove, _angRyMove)�ƒP�ʃx�N�g���w��(_vX, _vY, _vZ) ������ƌ��������A
//�����ς�g���͈̂ܓx�o�x�w��ł���B(�֗��Ȃ̂�)
//�������A�ŏI�I�ɂ� ���[���h�ϊ��s��̈ړ���̍s������߂邽�߁A�P�ʃx�N�g��(_vX, _vY, _vZ) �� �ړ����x �Ƃ����v�Z������K�v������B
//���̂��ߍŌ�Ɍ��ǒP�ʃx�N�g�����߂Ă���B
//�{�N���X�̃��\�b�h���g�p�������A����(_angRzMove, _angRyMove)��(_vX, _vY, _vZ) �́A�����͂Ƃ�Ă���B

//���ړ���
//�L�����́u�ړ����x�v(_veloMove)��ێ����Ă���B�ړ�����̂͊ȒP�ŁA���t���[���u�ړ����p�v�Ɂu�ړ����x�v�����������ł���B
//�����I�ɂ́u�ړ����p�v(_vX, _vY, _vZ)�Ɂu�ړ����x�v���|���Z���Ă���B

//������]���p��
//�L�����������Ă�����p�i�����j�A���u����]���p�v�ƌĂԂ��Ƃɂ���B�u����]���p�v�́A�Ō�̓��[���h�ϊ��s��̎���]�ɑΉ����Ă���B
//���[���h�ϊ��s��̎���]�Ƃ́AX����]�p�AY����]�p�AZ����]�p�̂��ƂŁA_angRot[AXIS_X]�A_angRot[AXIS_Y]�A_angRot[AXIS_Z] ���ێ����Ă���B
//�{���C�u�����ł́A�L���������_�ɂ���Ƃ��āA�P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g��(1, 0, 0) ���L�����́u�O���v�Ɛݒ肵�Ă���B�u����v�́i-1, 0, 0)�B
//�܂��A���[���h�ϊ��s��̉�]�s��̂����鏇�Ԃ́A��{�I�� �uX����]�p�s�� > Z����]�p�s�� > Y����]�p�s�� > �ړ��s�� �v�B
//���������āAX����]�p�͊���]�����悤�Ƃ��A�L�����������Ă�������͕ς�炸�A�c���Z����]�p�ƁAY����]�p�ŃL�����������Ă�����������肷��B
//
//���̂悤�Ȃ킯��X����]�p�̓L�����̃X�s���A�̂���Q�p�iZ����]�p�EY����]�p�j�ŃL�����́u�O���v���p�������肷��Ƃ����ꍇ�A
//�u����]���p�v����قǂ́u�ړ����p�i�����j�v�Ɠ����悤�ɁA�ܓx�ƌo�x(�܂��́A�A�W�}�X�Ƌp)�̂Q�̃A���O���l(_angRot[AXIS_Z], _angRot[AXIS_Y])
//�ŕ\���ł���B
//�u�O���v�� Z����]�p�EY����]�p����0�x�A�u�O���������Č������v��[Z����]�p,Y����]�p]=[180�x,0�x] ������ [0�x,180�x] �ƕ\������B
//�P�ɁuZ����]�p�v�ȂǂƏ����ƁA�u�ړ����p�v��Z����]�p�Ȃ̂��A�u����]���p�v��Z����]�p�Ȃ̂���₱�����Ȃ��߁A
//�u����]���p(Z��)�v�u����]���p(Y��)�v�Ə������ƂƂ���B
//�u�O���������E�����v�� [����]���p(Z��), ����]���p(Y��)]=[0, 90�x] or [180�x,270�x] �ƕ\���ł���B
//�i������]���p(Y��)�͍���n���W�̂���Y���̐������������Ĕ����v���j
//���̂悤�ɂP�̃L�����������Ă�����p�ɑ΂��āA�Q�ʂ�̃A�N�Z�X������@������̂Œ��ӁB���́u�O���v��[180�x,180�x]�ƕ\���ł���B
//�ǂ���������Ă�������͓��������p���͈قȂ�B

//���ړ����p�Ǝ���]���p�œ�����
//������ �u�ړ����p�iZ���j�v���u����]���p(Z��)�v�ցA�u�ړ����p�iY���j�v���u����]���p(Y��)�v �փR�s�[���Ă��ƁA
//�Ȃ�ƈړ����p�ƁA�L�����N�^�̌����̓������ȒP�Ɏ��邶��܂����B
//�t�ɃL�����������Ă�������Ɉړ���Ǐ]�����邱�Ƃ��ȒP�ɉ\�B

//�������O�������@�\��
//�����O�������@�\�Ƃ́u�ړ����p�v��ݒ肷��ƁA����ɔ����Ď����I�Ɂu����]���p�v��ݒ肷�鎖���Ӗ����Ă���B
//��̓I�ɂ́A�ȉ��̂悤�Ƀt���[�����ɁA�A���O���l���㏑���R�s�[���Ă��邾���B
// �E�ړ����p�iZ���j �� ����]���p(Z��)
// �E�ړ����p�iY���j �� ����]���p(Y��)
//�������u����]���p�v��ݒ�Ă��u�ړ����p�v�ω����Ȃ��i�t�͊֘A���Ȃ��j�̂Œ��ӁB

//���p���x��
//�u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�A�u����]���p(Z��)�v�u����]���p(Y��)�v�ɂ́A���ꂼ��́u�p���x�v��݂��Ă���B
//�Ⴆ��90�x�E�Ɍ��������ꍇ�A�L�����������Ȃ�J�N���ƌ�����ς��Ă͔߂����̂ŁA���t���[���p���x�����p�����Z����悤�ɂ��āA
//���炩�Ɍ�����ς���A�����͈ړ����p��ς��邱�Ƃ��o����B
//�u�p���x�v�͐����̒��ӂ��K�v�B���̏ꍇ�͔����v���A���̏ꍇ�͎��v���ɂȂ�B
//�����]������ꍇ�A�^�[�Q�b�g�ƂȂ�p�x�ւ̍s�����̍l�����́A��ɂS�ʂ肠��B
//�u�����v��ōs���v�u���v���ōs���v�u�߂��p�̎�������ōs���v�u�����Ȋp�̎�������ōs���v
//���ꂼ��p�r������̂ŁA�I�v�V���������ȂǂŁA�I���ł���悤�ɂ��Ă���B

//���������ړ���
//��L�̈ړ��̌n�Ƃ͕ʂɁA�Ɨ����� X���AY���AZ���ɕ��s�Ȉړ��w�肪�ł���B
//�uX�������ړ����x�v�uY�������ړ����x�v�uZ�������ړ����x�v��ݒ肷��ƁA���t���[��(_X,_Y,_Z)�ɂ��ꂼ��̈ړ�������
//���Z�����B


GgafDx9GeometryMover::GgafDx9GeometryMover(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;


    for (int i = 0; i < 3; i++) { // i=0:X���A1:Y���A2:Z�� ��\��

        //����]���p
        _angRot[i] = 0; //0 angle �� �R���̕��p�������Ă���
        //����]���p�̊p���x�i����]���p�̑����j= 0 angle/fream
        _angveloRot[i] = 0; //1�t���[���ɉ��Z����鎲��]���p�̊p�����B�f�t�H���g�͎���]���p�̊p���������A�܂�U����������B
        //����]���p�̊p���x��� �� 360,000 angle/fream
        _angveloTopRot[i] = ANGLE360; //_angveloRot[n] �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȏ���]���p�ɐU����������o���鎖���Ӗ�����
        //����]���p�̊p���x���� �� -360,000 angle/fream
        _angveloBottomRot[i] = ANGLE360 * -1; //_angveloRot[n] �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȏ���]���p�ɐU����������o���鎖���Ӗ�����
        //����]���p�̊p�����x�i�p���x�̑����j �� 0 angle/fream^2
        _angacceRot[i] = 0; //_angveloRot[n] �̑����B�f�t�H���g�͎���]���p�̊p�����x����
        //�ڕW����]���p�ւ̎�������t���O = ����
        _rot_angle_targeting_flg[i] = false;
        //�ڕW�̎���]���p
        _angTargetRot[i] = 0; //�ڕW����]���p�ւ̎�������t���O = �����A�̏ꍇ�͖��Ӗ�
        //�ڕW�̎���]���p������~�@�\���L���ɂȂ��]����
        _rot_angle_target_allow_way[i] = TURN_BOTH;
        //�ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj
        _rot_angle_target_allow_velocity[i] = ANGLE180;
    }

    //////////////////////////////////////////////////////
    //�L�����̈ړ����p�P�ʃx�N�g��
    _vX = 1.0f;
    _vY = _vZ = 0.0f;
    //�ړ����p��Z����]
    _angRzMove = 0;
    //�ړ����p��Y����]
    _angRyMove = 0;
    //�ړ����x
    _veloMove = 0;
    //�ړ����x��� = 256 px/fream
    _veloTopMove = 256 * LEN_UNIT; //_veloMove �� 256000(=256px) ������ړ��ʂł����Ă��A�����I�ɍ��W������ 256px �ɗ}������B
    //�ړ����x���� = 0   px/fream
    _veloBottomMove = -256 * LEN_UNIT; //_veloMove �� -256000(-256px) �������ړ��ʂ������Ă��A�����I�ɍ��W������ -256000px �ɗ}������B
    //�ړ������x�i�ړ����x�̑����j = 0 px/fream^2
    _accMove = 0; //_veloMove �̑����B�f�t�H���g�͉�������

    //�ړ����p�iZ����]�j�̊p���x = 0 angle/fream
    _angveloRzMove = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iZ����]�j�̊p���x��� = +360,000 angle/fream
    _angveloRzTopMove = ANGLE360; //_angveloRzMove �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p���x���� = -360,000 angle/fream
    _angveloRzBottomMove = ANGLE360 * -1; //_angveloRzMove �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p�����x = 0 angle/fream^2
    _angacceRzMove = 0; //_angveloRzMove �̑����B�f�t�H���g�͈ړ����p�̊p�����x����
    //�ڕW�ړ����p�iZ����]�j�ւ̎�������t���O = ����
    _move_angle_rz_target_flg = false;
    //�ڕW�̈ړ����p�iZ����]�j
    _angTargetRzMove = 0;
    //�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ��]����
    _move_angle_rz_target_allow_way = TURN_BOTH;
    //�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
    _move_angle_rz_target_allow_velocity = ANGLE180;
    //�ړ����p�iZ����]�j�ɔ���Z����]���p�̓��������@�\�t���O �� ����
    _synchronize_ZRotAngle_to_RzMoveAngle_flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B

    //�ړ����p�iY����]�j�̊p���x = 0 angle/fream
    _angveloRyMove = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iY����]�j�̊p���x��� = +360,000 angle/fream
    _angveloRyTopMove = ANGLE360; //_angveloRyMove �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p���x���� = -360,000 angle/fream
    _angveloRyBottomMove = ANGLE360 * -1; //_angveloRyMove �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p�����x = 0 angle/fream^2
    _angacceRyMove = 0; //_angveloRyMove �̑����B�f�t�H���g�͈ړ����p�̊p�����x����
    //�ڕW�ړ����p�iY����]�j�ւ̎�������t���O = ����
    _move_angle_ry_target_flg = false;
    //�ڕW�̈ړ����p�iY����]�j
    _angTargetRyMove = 0;
    //�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ��]����
    _move_angle_ry_target_allow_way = TURN_BOTH;
    //�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
    _move_angle_ry_target_allow_velocity = ANGLE180;
    //�ړ����p�iY����]�j�ɔ���Z����]���p�̓��������@�\�t���O �� ����
    _synchronize_YRotAngle_to_RyMoveAngle_flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B

    //X�������ړ����x�iX�ړ����W�����j�� 0 px/fream
    _veloVxMove = 0;
    //X�������ړ����x��� �� 256 px/fream
    _veloTopVxMove = 256 * LEN_UNIT;
    //X�������ړ����x���� �� 256 px/fream
    _veloBottomVxMove = -256 * LEN_UNIT;
    //X�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVxMove = 0;
    //Y�������ړ����x�iY�ړ����W�����j�� 0 px/fream
    _veloVyMove = 0;
    //Y�������ړ����x��� �� 256 px/fream
    _veloTopVyMove = 256 * LEN_UNIT;
    //Y�������ړ����x���� �� 256 px/fream
    _veloBottomVyMove = -256 * LEN_UNIT;
    //Y�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVyMove = 0;
    //Z�������ړ����x�iZ�ړ����W�����j�� 0 px/fream
    _veloVzMove = 0;
    //Z�������ړ����x��� �� 256 px/fream
    _veloTopVzMove = 256 * LEN_UNIT;
    //Z�������ړ����x���� �� 256 px/fream
    _veloBottomVzMove = -256 * LEN_UNIT;
    //Z�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVzMove = 0;

    _progSP = NULL;

}

void GgafDx9GeometryMover::behave() {

    //�X�v���C���Ȑ��ړ�
    if (_progSP != NULL) {
        _progSP->behave();
    }

    //����]���p����
    static angle angDistance;
    for (int i = 0; i < 3; i++) {
        if (_rot_angle_targeting_flg[i]) {
            _angveloRot[i] += _angacceRot[i];
            setRotAngleVelocity(i, _angveloRot[i]);

            if (_angveloRot[i] > 0) { //�����v���̏ꍇ
                angDistance = getDifferenceFromRotAngleTo(i, _angTargetRot[i], TURN_COUNTERCLOCKWISE);
                if (_angveloRot[i] > angDistance && _rot_angle_target_allow_way[i] != TURN_CLOCKWISE
                        && _rot_angle_target_allow_velocity[i] >= _angveloRot[i]) {
                    addRotAngle(i, angDistance);
                    _rot_angle_targeting_flg[i] = false; //�t���O��߂��ďI��
                } else {
                    addRotAngle(i, _angveloRot[i]);
                }
            } else if (_angveloRot[i] < 0) { //���v���̏ꍇ
                angDistance = getDifferenceFromRotAngleTo(i, _angTargetRot[i], TURN_CLOCKWISE);
                if (_angveloRot[i] < angDistance && _rot_angle_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _rot_angle_target_allow_velocity[i] <= _angveloRot[i]) { //�ڕW���s���߂��Ă��܂���������ȓ�
                    addRotAngle(i, angDistance);
                    _rot_angle_targeting_flg[i] = false; //�t���O��߂��ďI��
                } else {
                    addRotAngle(i, _angveloRot[i]);
                }
            } else {
                //_angveloRot[i] == 0
                addRotAngle(i, 0);
            }

            if (_rot_angle_targeting_flg[i] == false) {
                //�ڕW�����ɓ��B�������̏���
                //_angveloTopRot[i] = ANGLE360; //����]���p�̊p���x��� �� 360,000 angle/fream
                //_angveloBottomRot[i] = ANGLE360 * -1; //����]���p�̊p���x���� �� -360,000 angle/fream

                //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
                _angacceRot[i] = 0; //����]�����p�A�p���x���O��
                setRotAngleVelocity(i, 0); //����]�����p�A�p�����x���O��
            }

        } else {
            //if (_angacceRot[i] != 0) {
            //�t���[�����̎���]���p����̏���
            _angveloRot[i] += _angacceRot[i];
            if (_angveloRot[i] != 0) {
                addRotAngle(i, _angveloRot[i]);
            }
            //}
        }
    }

    //Actor�ɔ��f
    _pActor->_RX = _angRot[AXIS_X];
    _pActor->_RY = _angRot[AXIS_Y];
    _pActor->_RZ = _angRot[AXIS_Z];

    ///////////////////////////////////////////////////Mover
    //X�������ړ������x�̏���
    _veloVxMove += _acceVxMove;
    setVxMoveVelocity(_veloVxMove);
    //Y�������ړ������x�̏���
    _veloVyMove += _acceVyMove;
    setVyMoveVelocity(_veloVyMove);
    //Z�������ړ������x�̏���
    _veloVzMove += _acceVzMove;
    setVzMoveVelocity(_veloVzMove);

    //�ړ������x�̏���
    _veloMove += _accMove;
    setMoveVelocity(_veloMove);
    ///////////
    //�ڕW�ړ����p�iZ����]�j�A���O��������~�@�\�g�p���̏ꍇ
    if (_move_angle_rz_target_flg) {

        _angveloRzMove += _angacceRzMove;
        setRzMoveAngleVelocity(_angveloRzMove);

        if (_angveloRzMove > 0) { //�����v���̏ꍇ
            angle angDistance = getDifferenceFromRzMoveAngleTo(_angTargetRzMove, TURN_COUNTERCLOCKWISE);
            if (_angveloRzMove > angDistance && _move_angle_rz_target_allow_way != TURN_CLOCKWISE
                    && _move_angle_rz_target_allow_velocity >= _angveloRzMove) { //�ڕW���s���߂��Ă��܂���������ȓ�
                addRzMoveAngle(angDistance);
                _move_angle_rz_target_flg = false; //�t���O��߂��ďI��
            } else {
                addRzMoveAngle(_angveloRzMove);
            }
        } else if (_angveloRzMove < 0) { //���v���̏ꍇ

            angle angDistance = getDifferenceFromRzMoveAngleTo(_angTargetRzMove, TURN_CLOCKWISE);
            if (_angveloRzMove < angDistance && _move_angle_rz_target_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_move_angle_rz_target_allow_velocity <= _angveloRzMove) {
                addRzMoveAngle(angDistance);
                _move_angle_rz_target_flg = false; //�t���O��߂��ďI��
            } else {
                addRzMoveAngle(_angveloRzMove);
            }
        } else {
            addRzMoveAngle(0);
        }
        if (_move_angle_rz_target_flg == false) {
            //_angveloRzTopMove = ANGLE360; //�ړ����p�iZ����]�j�̊p���x��� �� 360,000 angle/fream
            //_angveloRzBottomMove = ANGLE360 * -1; //�ړ����p�iZ����]�j�̊p���x���� �� -360,000 angle/fream

            //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
            _angacceRzMove = 0; //Z���ړ������p�A�p�����x���O��
            setRzMoveAngleVelocity(0); //Z���ړ������p�A�p���x���O��
        }

    } else {
        //if (_angacceRzMove != 0) {
        //�t���[�����̈ړ����p�iZ����]�j����̏���
        _angveloRzMove += _angacceRzMove;
        if (_angveloRzMove != 0) {
            addRzMoveAngle(_angveloRzMove);
        }
        //}
    }
    ////////////////
    //�ڕW�ړ����p�iY����]�j�A���O��������~�@�\�g�p���̏ꍇ
    if (_move_angle_ry_target_flg) {

        _angveloRyMove += _angacceRyMove;
        setRyMoveAngleVelocity(_angveloRyMove);

        if (_angveloRyMove > 0) { //�����v���̏ꍇ
            angle angDistance = getDifferenceFromRyMoveAngleTo(_angTargetRyMove, TURN_COUNTERCLOCKWISE);
            if (_angveloRyMove > angDistance &&
                _move_angle_ry_target_allow_way != TURN_CLOCKWISE &&
                _move_angle_ry_target_allow_velocity >= _angveloRyMove)
            { //�ڕW���s���߂��Ă��܂���������ȓ�
                addRyMoveAngle(angDistance);
                _move_angle_ry_target_flg = false; //�t���O��߂��ďI��
            } else {
                addRyMoveAngle(_angveloRyMove);
            }
        } else if (_angveloRyMove < 0) { //���v���̏ꍇ

            angle angDistance = getDifferenceFromRyMoveAngleTo(_angTargetRyMove, TURN_CLOCKWISE);
            if (_angveloRyMove < angDistance &&
                _move_angle_ry_target_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_move_angle_ry_target_allow_velocity <= _angveloRyMove)
            {
                addRyMoveAngle(angDistance);
                _move_angle_ry_target_flg = false; //�t���O��߂��ďI��
            } else {
                addRyMoveAngle(_angveloRyMove);
            }
        } else {
            //_angveloRyMove==0
            addRyMoveAngle(0);
        }
        if (_move_angle_ry_target_flg == false) {
            //_angveloRyTopMove = ANGLE360; //�ړ����p�iY����]�j�̊p���x��� �� 360,000 angle/fream
            //_angveloRyBottomMove = ANGLE360*-1; //�ړ����p�iY����]�j�̊p���x���� �� -360,000 angle/fream

            //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
            _angacceRyMove = 0; //Y���ړ������p�A�p�����x���O��
            setRyMoveAngleVelocity(0); //Y���ړ������p�A�p���x���O��
        }
    } else {
        //if (_angacceRyMove != 0) {
        //�t���[�����̈ړ����p�iY����]�j����̏���
        _angveloRyMove += _angacceRyMove;
        if(_angveloRyMove != 0) {
            addRyMoveAngle(_angveloRyMove);
        }
        //}
    }
    ///////////////

    //Actor�ɔ��f
    _pActor->_X += (int)(_vX * _veloMove + _veloVxMove);
    _pActor->_Y += (int)(_vY * _veloMove + _veloVyMove);
    _pActor->_Z += (int)(_vZ * _veloMove + _veloVzMove);

}


angle GgafDx9GeometryMover::simplifyAngle(angle prm_ang) {
    static angle angSimple;
    angSimple = prm_ang;
    while (angSimple >= ANGLE360) {
        angSimple -= ANGLE360;
    }
    while (angSimple < 0) {
        angSimple += ANGLE360;
    }
    return angSimple;
}

void GgafDx9GeometryMover::setRotAngle(int prm_axis, angle prm_angRot) {
    _angRot[prm_axis] = simplifyAngle(prm_angRot);
}

void GgafDx9GeometryMover::setRotAngle(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAngle(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _angRot[AXIS_Z],
                   _angRot[AXIS_Y]
                 );
}

void GgafDx9GeometryMover::addRotAngle(int prm_axis, angle prm_angDistance) {
    static angle angOffsetrot_RotAngle;
    angOffsetrot_RotAngle = prm_angDistance;
    if (_angveloBottomRot[prm_axis] > prm_angDistance) {
        angOffsetrot_RotAngle = _angveloBottomRot[prm_axis];
    } else if (prm_angDistance > _angveloTopRot[prm_axis]) {
        angOffsetrot_RotAngle = _angveloTopRot[prm_axis];
    }
    setRotAngle(prm_axis, _angRot[prm_axis] + angOffsetrot_RotAngle);
}

void GgafDx9GeometryMover::setRotAngleVelocity(int prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloTopRot[prm_axis]) {
        _angveloRot[prm_axis] = _angveloTopRot[prm_axis];
    } else if (prm_angveloRot < _angveloBottomRot[prm_axis]) {
        _angveloRot[prm_axis] = _angveloBottomRot[prm_axis];
    } else {
        _angveloRot[prm_axis] = prm_angveloRot;
    }
}

void GgafDx9GeometryMover::setRotAngleVelocityRenge(int prm_axis,
                                                    angvelo prm_angveloRot01,
                                                    angvelo prm_angveloRot02) {
    if (prm_angveloRot01 < prm_angveloRot02) {
        _angveloTopRot[prm_axis] = prm_angveloRot02;
        _angveloBottomRot[prm_axis] = prm_angveloRot01;
    } else {
        _angveloTopRot[prm_axis] = prm_angveloRot01;
        _angveloBottomRot[prm_axis] = prm_angveloRot02;
    }
    setRotAngleVelocity(prm_axis, _angveloRot[prm_axis]); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometryMover::setRotAngleAcceleration(int prm_axis, angacce prm_angacceRot) {
    _angacceRot[prm_axis] = prm_angacceRot;
}

void GgafDx9GeometryMover::setSuspendTargetRotAngleV(int prm_axis,
                                                  int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMove) {
    setSuspendTargetRotAngle(
      prm_axis,
      GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
      prm_way_allow,
      prm_angveloAllowRyMove
    );
}

void GgafDx9GeometryMover::setSuspendTargetRotAngle(int prm_axis,
                                             angle prm_angTargetRot,
                                             int prm_way_allow,
                                             angvelo prm_angveloAllow) {
    _rot_angle_targeting_flg[prm_axis] = true;
    _angTargetRot[prm_axis] = simplifyAngle(prm_angTargetRot);
    _rot_angle_target_allow_way[prm_axis] = prm_way_allow;
    _rot_angle_target_allow_velocity[prm_axis] = prm_angveloAllow;
}

angle GgafDx9GeometryMover::getDifferenceFromRotAngleTo(int prm_axis, int prm_tX, int prm_tY, int prm_way) {
    return getDifferenceFromRotAngleTo(prm_axis, GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY
            - (_pActor->_Y)), prm_way);
}

angle GgafDx9GeometryMover::getDifferenceFromRotAngleTo(int prm_axis, angle prm_angTargetRot, int prm_way) {
    static angle _angTargetRot;
    _angTargetRot = simplifyAngle(prm_angTargetRot);
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        if (0 <= _angRot[prm_axis] && _angRot[prm_axis] < ANGLE180) {
            if (0 <= _angTargetRot && _angTargetRot < _angRot[prm_axis]) {
                return -1 * (_angRot[prm_axis] - _angTargetRot);
            } else if (_angTargetRot == _angRot[prm_axis]) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRot[prm_axis] < _angTargetRot && _angTargetRot < _angRot[prm_axis]
                    + ANGLE180) {
                return _angTargetRot - _angRot[prm_axis];
            } else if (_angTargetRot == _angRot[prm_axis] + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRot[prm_axis] + ANGLE180 < _angTargetRot && _angTargetRot <= ANGLE360) {
                return -1 * (_angRot[prm_axis] + (ANGLE360 - _angTargetRot));
            } else {
                //��������
                _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRotAngleTo() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
            }
        } else if (ANGLE180 <= _angRot[prm_axis] && _angRot[prm_axis] <= ANGLE360) {
            if (0 <= _angTargetRot && _angTargetRot < _angRot[prm_axis] - ANGLE180) {
                return ANGLE360 - _angRot[prm_axis] + _angTargetRot;
            } else if (_angTargetRot == _angRot[prm_axis] - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRot[prm_axis] - ANGLE180 < _angTargetRot && _angTargetRot
                    < _angRot[prm_axis]) {
                return -1 * (_angRot[prm_axis] - _angTargetRot);
            } else if (_angRot[prm_axis] == _angTargetRot) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRot[prm_axis] < _angTargetRot && _angTargetRot <= ANGLE360) {
                return _angTargetRot - _angRot[prm_axis];
            } else {
                //��������
                _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRotAngleTo() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angRot[prm_axis] && _angRot[prm_axis] < _angTargetRot) {
            return (_angTargetRot - _angRot[prm_axis]);
        } else if (_angTargetRot < _angRot[prm_axis] && _angRot[prm_axis] < ANGLE360) {
            return ANGLE360 - _angRot[prm_axis] + _angTargetRot;
        } else if (_angRot[prm_axis] == _angTargetRot) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRotAngleTo() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angRot[prm_axis] && _angRot[prm_axis] < _angTargetRot) {
            return -1 * (_angRot[prm_axis] + ANGLE360 - _angTargetRot);
        } else if (_angTargetRot < _angRot[prm_axis] && _angRot[prm_axis] < ANGLE360) {
            return -1 * (_angRot[prm_axis] - _angTargetRot);
        } else if (_angRot[prm_axis] == _angTargetRot) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRotAngleTo() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
        }
    }
    _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRotAngleTo() ���̂�����p�̋��������߂�܂���B(2)");
}


void GgafDx9GeometryMover::setMoveVelocityRenge(int prm_veloMove01, int prm_veloMove02) {
    if (prm_veloMove01 < prm_veloMove02) {
        _veloTopMove = prm_veloMove02;
        _veloBottomMove = prm_veloMove01;
    } else {
        _veloTopMove = prm_veloMove01;
        _veloBottomMove = prm_veloMove02;
    }
    setMoveVelocity(_veloMove); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometryMover::setMoveVelocity(int prm_veloMove) {
    if (prm_veloMove > _veloTopMove) {
        _veloMove = _veloTopMove;
    } else if (prm_veloMove < _veloBottomMove) {
        _veloMove = _veloBottomMove;
    } else {
        _veloMove = prm_veloMove;
    }
}

void GgafDx9GeometryMover::addMoveVelocity(int prm_veloMove_Offset) {
    setMoveVelocity(_veloMove + prm_veloMove_Offset);
}

void GgafDx9GeometryMover::setMoveAcceleration(int prm_acceMove) {
    _accMove = prm_acceMove;
}

void GgafDx9GeometryMover::setRzMoveAngle(int prm_tX, int prm_tY) {
    setRzMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometryMover::setRzMoveAngle(angle prm_angle) {
    if (prm_angle !=  _angRzMove) {
        _angRzMove = simplifyAngle(prm_angle);
        GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    }
    if (_synchronize_ZRotAngle_to_RzMoveAngle_flg) {
        setRotAngle(AXIS_Z, _angRzMove);
    }
}

void GgafDx9GeometryMover::addRzMoveAngle(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRzBottomMove > prm_angDistance) {
        angOffset = _angveloRzBottomMove;
    } else if (prm_angDistance > _angveloRzTopMove) {
        angOffset = _angveloRzTopMove;
    }
    setRzMoveAngle(_angRzMove + angOffset);
}

void GgafDx9GeometryMover::setRzMoveAngleVelocity(angvelo prm_angveloRzMove) {
    if (prm_angveloRzMove > _angveloRzTopMove) {
        _angveloRzMove = _angveloRzTopMove;
    } else if (prm_angveloRzMove < _angveloRzBottomMove) {
        _angveloRzMove = _angveloRzBottomMove;
    } else {
        _angveloRzMove = prm_angveloRzMove;
    }
}

void GgafDx9GeometryMover::setRzMoveAngleAcceleration(angacce prm_angacceRzMove) {
    _angacceRzMove = prm_angacceRzMove;
}

void GgafDx9GeometryMover::setRzMoveAngleVelocityRenge(angvelo prm_angveloRzMove01,
                                                       angvelo prm_angveloRzMove02) {
    if (prm_angveloRzMove01 < prm_angveloRzMove02) {
        _angveloRzTopMove = prm_angveloRzMove02;
        _angveloRzBottomMove = prm_angveloRzMove01;
    } else {
        _angveloRzTopMove = prm_angveloRzMove01;
        _angveloRzBottomMove = prm_angveloRzMove02;
    }
    setRzMoveAngleVelocity(_angveloRzMove); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometryMover::setSuspendTargetRzMoveAngle(angle prm_angTargetRzMove,
                                                    int prm_way_allow,
                                                    angvelo prm_angveloAllowRyMove) {
    _move_angle_rz_target_flg = true;
    _angTargetRzMove = simplifyAngle(prm_angTargetRzMove);
    _move_angle_rz_target_allow_way = prm_way_allow;
    _move_angle_rz_target_allow_velocity = prm_angveloAllowRyMove;
}

void GgafDx9GeometryMover::setSuspendTargetRzMoveAngleV(int prm_tX,
                                                     int prm_tY,
                                                     int prm_way_allow,
                                                     angvelo prm_angveloAllowRyMove) {
    setSuspendTargetRzMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getDifferenceFromRzMoveAngleTo(int prm_tX, int prm_tY, int prm_way) {
    return getDifferenceFromRzMoveAngleTo(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getDifferenceFromRzMoveAngleTo(angle prm_angTargetRzMove, int prm_way) {
    angle angTargetRzMove = simplifyAngle(prm_angTargetRzMove);
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        if (0 <= _angRzMove && _angRzMove < ANGLE180) {
            if (0 <= angTargetRzMove && angTargetRzMove < _angRzMove) {
                return -1 * (_angRzMove - angTargetRzMove);
            } else if (angTargetRzMove == _angRzMove) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRzMove < angTargetRzMove && angTargetRzMove < _angRzMove + ANGLE180) {
                return angTargetRzMove - _angRzMove;
            } else if (angTargetRzMove == _angRzMove + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRzMove + ANGLE180 < angTargetRzMove && angTargetRzMove <= ANGLE360) {
                return -1 * (_angRzMove + (ANGLE360 - angTargetRzMove));
            } else {
                //��������
                _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
            }
        } else if (ANGLE180 <= _angRzMove && _angRzMove <= ANGLE360) {
            if (0 <= angTargetRzMove && angTargetRzMove < _angRzMove - ANGLE180) {
                return ANGLE360 - _angRzMove + angTargetRzMove;
            } else if (angTargetRzMove == _angRzMove - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRzMove - ANGLE180 < angTargetRzMove && angTargetRzMove < _angRzMove) {
                return -1 * (_angRzMove - angTargetRzMove);
            } else if (_angRzMove == angTargetRzMove) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRzMove < angTargetRzMove && angTargetRzMove <= ANGLE360) {
                return angTargetRzMove - _angRzMove;
            } else {
                //��������
                _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRzMoveAngleTo() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angRzMove && _angRzMove < angTargetRzMove) {
            return (angTargetRzMove - _angRzMove);
        } else if (angTargetRzMove < _angRzMove && _angRzMove < ANGLE360) {
            return ANGLE360 - _angRzMove + angTargetRzMove;
        } else if (_angRzMove == angTargetRzMove) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRzMoveAngleTo() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angRzMove && _angRzMove < angTargetRzMove) {
            return -1 * (_angRzMove + ANGLE360 - angTargetRzMove);
        } else if (angTargetRzMove < _angRzMove && _angRzMove < ANGLE360) {
            return -1 * (_angRzMove - angTargetRzMove);
        } else if (_angRzMove == angTargetRzMove) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRzMoveAngleTo() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
        }
    }

    _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
    throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRzMoveAngleTo() ���̂�����p�̋��������߂�܂���B(1)");

}


void GgafDx9GeometryMover::setRyMoveAngle(int prm_tX, int prm_tY) {
    setRyMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometryMover::setRyMoveAngle(angle prm_angle) {
    if (prm_angle != _angRyMove) {
        _angRyMove = simplifyAngle(prm_angle);
        GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    }
    if (_synchronize_YRotAngle_to_RyMoveAngle_flg) {
        setRotAngle(AXIS_Y, _angRyMove);
    }
}

void GgafDx9GeometryMover::addRyMoveAngle(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRyBottomMove > prm_angDistance) {
        angOffset = _angveloRyBottomMove;
    } else if (prm_angDistance > _angveloRyTopMove) {
        angOffset = _angveloRyTopMove;
    }
    setRyMoveAngle(_angRyMove + angOffset);
}

void GgafDx9GeometryMover::setRyMoveAngleVelocity(angvelo prm_angveloRyMove) {
    if (prm_angveloRyMove > _angveloRyTopMove) {
        _angveloRyMove = _angveloRyTopMove;
    } else if (prm_angveloRyMove < _angveloRyBottomMove) {
        _angveloRyMove = _angveloRyBottomMove;
    } else {
        _angveloRyMove = prm_angveloRyMove;
    }
}

void GgafDx9GeometryMover::setRyMoveAngleAcceleration(angacce prm_angacceRyMove) {
    _angacceRyMove = prm_angacceRyMove;
}

void GgafDx9GeometryMover::setRyMoveAngleVelocityRenge(angvelo prm_angveloRyMove01,
                                                       angvelo prm_angveloRyMove02) {
    if (prm_angveloRyMove01 < prm_angveloRyMove02) {
        _angveloRyTopMove = prm_angveloRyMove02;
        _angveloRyBottomMove = prm_angveloRyMove01;
    } else {
        _angveloRyTopMove = prm_angveloRyMove01;
        _angveloRyBottomMove = prm_angveloRyMove02;
    }
    setRyMoveAngleVelocity(_angveloRyMove); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometryMover::setSuspendTargetRyMoveAngle(angle prm_angTargetRyMove,
                                                int prm_way_allow,
                                                angvelo prm_angveloAllowRyMove) {
    _move_angle_ry_target_flg = true;
    _angTargetRyMove = simplifyAngle(prm_angTargetRyMove);
    _move_angle_ry_target_allow_way = prm_way_allow;
    _move_angle_ry_target_allow_velocity = prm_angveloAllowRyMove;
}

void GgafDx9GeometryMover::setSuspendTargetRyMoveAngleV(int prm_tX,
                                                 int prm_tY,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMove) {
    setSuspendTargetRyMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getDifferenceFromRyMoveAngleTo(int prm_tX, int prm_tY, int prm_way) {
    return getDifferenceFromRyMoveAngleTo(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getDifferenceFromRyMoveAngleTo(angle prm_angTargetRyMove, int prm_way) {
    static angle angTargetRyMove;
    angTargetRyMove = simplifyAngle(prm_angTargetRyMove);
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        if (0 <= _angRyMove && _angRyMove < ANGLE180) {
            if (0 <= angTargetRyMove && angTargetRyMove < _angRyMove) {
                return -1 * (_angRyMove - angTargetRyMove);
            } else if (angTargetRyMove == _angRyMove) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRyMove < angTargetRyMove && angTargetRyMove < _angRyMove + ANGLE180) {
                return angTargetRyMove - _angRyMove;
            } else if (angTargetRyMove == _angRyMove + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRyMove + ANGLE180 < angTargetRyMove && angTargetRyMove <= ANGLE360) {
                return -1 * (_angRyMove + (ANGLE360 - angTargetRyMove));
            } else {
                //��������
                _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
            }
        } else if (ANGLE180 <= _angRyMove && _angRyMove <= ANGLE360) {
            if (0 <= angTargetRyMove && angTargetRyMove < _angRyMove - ANGLE180) {
                return ANGLE360 - _angRyMove + angTargetRyMove;
            } else if (angTargetRyMove == _angRyMove - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRyMove - ANGLE180 < angTargetRyMove && angTargetRyMove < _angRyMove) {
                return -1 * (_angRyMove - angTargetRyMove);
            } else if (_angRyMove == angTargetRyMove) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRyMove < angTargetRyMove && angTargetRyMove <= ANGLE360) {
                return angTargetRyMove - _angRyMove;
            } else {
                //��������
                _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRyMoveAngleTo() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angRyMove && _angRyMove < angTargetRyMove) {
            return (angTargetRyMove - _angRyMove);
        } else if (angTargetRyMove < _angRyMove && _angRyMove < ANGLE360) {
            return ANGLE360 - _angRyMove + angTargetRyMove;
        } else if (_angRyMove == angTargetRyMove) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRyMoveAngleTo() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angRyMove && _angRyMove < angTargetRyMove) {
            return -1 * (_angRyMove + ANGLE360 - angTargetRyMove);
        } else if (angTargetRyMove < _angRyMove && _angRyMove < ANGLE360) {
            return -1 * (_angRyMove - angTargetRyMove);
        } else if (_angRyMove == angTargetRyMove) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRyMoveAngleTo() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
        }
    }

    _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
    throwGgafCriticalException("GgafDx9GeometryMover::getDifferenceFromRyMoveAngleTo() ���̂�����p�̋��������߂�܂���B(1)");

}


void GgafDx9GeometryMover::setRzRyMoveAngle(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMove || prm_angRy !=_angRyMove ) {
        _angRzMove = simplifyAngle(prm_angRz);
        _angRyMove = simplifyAngle(prm_angRy);
        GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    }
    if (_synchronize_ZRotAngle_to_RzMoveAngle_flg) {
        setRotAngle(AXIS_Z, _angRzMove);
    }
    if (_synchronize_YRotAngle_to_RyMoveAngle_flg) {
        setRotAngle(AXIS_Y, _angRyMove);
    }

}


void GgafDx9GeometryMover::setMoveAngle(GgafDx9GeometricActor* prm_pActor_Target) {
    setMoveAngle(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9GeometryMover::setMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAngle(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _vX,
                   _vY,
                   _vZ,
                   _angRzMove,
                   _angRyMove
                 );
}

void GgafDx9GeometryMover::setSuspendTargetRzRyMoveAngle(GgafDx9GeometricActor* prm_pActor_Target) {
    setSuspendTargetRzRyMoveAngle(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9GeometryMover::setSuspendTargetRzRyMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
    angle angRz_Target;
    angle angRy_Target;

    GgafDx9Util::getRzRyAngle(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _dummy1,
                   _dummy2,
                   _dummy3,
                   angRz_Target,
                   angRy_Target
                 );
    setSuspendTargetRzMoveAngle(angRz_Target);
    setSuspendTargetRyMoveAngle(angRy_Target);
}

void GgafDx9GeometryMover::setVxMoveVelocityRenge(velo prm_veloVxMove01, velo prm_veloVxMove02) {
    if (prm_veloVxMove01 < prm_veloVxMove02) {
        _veloTopVxMove = prm_veloVxMove02;
        _veloBottomVxMove = prm_veloVxMove01;
    } else {
        _veloTopVxMove = prm_veloVxMove01;
        _veloBottomVxMove = prm_veloVxMove02;
    }
    setVxMoveVelocity(_veloVxMove); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometryMover::setVxMoveVelocity(velo prm_veloVxMove) {
    if (prm_veloVxMove > _veloTopVxMove) {
        _veloVxMove = _veloTopVxMove;
    } else if (prm_veloVxMove < _veloBottomVxMove) {
        _veloVxMove = _veloBottomVxMove;
    } else {
        _veloVxMove = prm_veloVxMove;
    }
}

void GgafDx9GeometryMover::setVxMoveAcceleration(acce prm_acceVxMove) {
    _acceVxMove = prm_acceVxMove;
}

void GgafDx9GeometryMover::setVyMoveVelocityRenge(velo prm_veloVyMove01, velo prm_veloVyMove02) {
    if (prm_veloVyMove01 < prm_veloVyMove02) {
        _veloTopVyMove = prm_veloVyMove02;
        _veloBottomVyMove = prm_veloVyMove01;
    } else {
        _veloTopVyMove = prm_veloVyMove01;
        _veloBottomVyMove = prm_veloVyMove02;
    }
    setVyMoveVelocity(_veloVyMove); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometryMover::setVyMoveVelocity(velo prm_veloVyMove) {
    if (prm_veloVyMove > _veloTopVyMove) {
        _veloVyMove = _veloTopVyMove;
    } else if (prm_veloVyMove < _veloBottomVyMove) {
        _veloVyMove = _veloBottomVyMove;
    } else {
        _veloVyMove = prm_veloVyMove;
    }
}

void GgafDx9GeometryMover::setVyMoveAcceleration(acce prm_acceVyMove) {
    _acceVyMove = prm_acceVyMove;
}

void GgafDx9GeometryMover::setVzMoveVelocityRenge(velo prm_veloVzMove01, velo prm_veloVzMove02) {
    if (prm_veloVzMove01 < prm_veloVzMove02) {
        _veloTopVzMove = prm_veloVzMove02;
        _veloBottomVzMove = prm_veloVzMove01;
    } else {
        _veloTopVzMove = prm_veloVzMove01;
        _veloBottomVzMove = prm_veloVzMove02;
    }
    setVzMoveVelocity(_veloVzMove); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometryMover::setVzMoveVelocity(velo prm_veloVzMove) {
    if (prm_veloVzMove > _veloTopVzMove) {
        _veloVzMove = _veloTopVzMove;
    } else if (prm_veloVzMove < _veloBottomVzMove) {
        _veloVzMove = _veloBottomVzMove;
    } else {
        _veloVzMove = prm_veloVzMove;
    }
}

void GgafDx9GeometryMover::setVzMoveAcceleration(acce prm_acceVzMove) {
    _acceVzMove = prm_acceVzMove;
}



void GgafDx9GeometryMover::executeSplineMoveSequence(GgafDx9SplineProgram* prm_progSP, int prm_option) {
    _progSP = prm_progSP;
    _progSP->begin(_pActor, prm_option);
}

void GgafDx9GeometryMover::executeTagettingMoveAngleSequence(int prm_tX, int prm_tY, int prm_tZ, angvelo prm_angVelocity) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAngle(prm_tX - _pActor->_X,
                              prm_tY - _pActor->_Y,
                              prm_tZ - _pActor->_Z,
                              out_angRz_Target,
                              out_angRy_Target);
    if (getDifferenceFromRzMoveAngleTo(out_angRz_Target, TURN_CLOSE_TO) > 0) {
        setRzMoveAngleVelocity(prm_angVelocity);
    } else {
       setRzMoveAngleVelocity(-1 * prm_angVelocity);
    }
    if (getDifferenceFromRyMoveAngleTo(out_angRy_Target, TURN_CLOSE_TO) > 0) {
        setRyMoveAngleVelocity(prm_angVelocity);
    } else {
        setRyMoveAngleVelocity(-1 * prm_angVelocity);
    }

    setSuspendTargetRzMoveAngle(out_angRz_Target);
    setSuspendTargetRyMoveAngle(out_angRy_Target);
}




GgafDx9GeometryMover::~GgafDx9GeometryMover() {

    //DELETE_POSSIBLE_NULL(_progSP);//Actor�Ŏn������B����Ȃ�
}
