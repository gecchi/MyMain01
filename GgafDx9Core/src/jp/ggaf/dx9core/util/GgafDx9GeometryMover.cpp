#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

// �y���������z�l�����ƒP��
//
// ���Q��ނ̕�����
// �u�����v�ɂ͂Q��ނ���B�u�ړ����p�i�����j�v�Ɓu����]���p�i�����j�v�ł���B
// �u�ړ����p�i�����j�v�̓L�����̐i�s�����݂̂�\������B����́u�ړ����x�v�Ɣ����āA�L�����͍��W�����ړ����邱�ƂƂ���B
// �u����]���p�v�̓L�����̌����݂̂�\����B
// �L�����N�^����ʂ̏㕔���牺���ֈړ����Ă��A�L�����N�^�͉��������Ƃ͌��炸���@�Ɍ����Ăق����ꍇ������B
// �E�ɃL�������������āA���Ɉړ������������Ƃ�����B���ꂼ��ݒ肪�K�v�B

// ���ړ����p��
// �L�������i�ޕ����A�܂�u�ړ����p�v�̕����́A���_����P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g�� (_vX, _vY, _vZ) �ŕ\�����@�ƁA
// �ܓx�ƌo�x(�܂��́A�A�W�}�X�Ƌp)�̂Q�̃A���O���l (_angRzMove, _angRyMove) �ŕ\�����@�̂Q��ޗp�ӂ����B
// �P�Ɂu�ړ����p�v�ƌĂԏꍇ�́A��ʓI�Ɉړ������̃x�N�g���̂��Ƃ��w�����A�����ł́A�Q�̃A���O���l���Z�b�g�̎����u�ړ����p�v
// �ƌĂԏꍇ�������i���ƂƂ���j�B
// �ܓx�o�x�\���̏ꍇ�A�ܓx��Z����]�p�A�o�x��Y����]�p �ƌ����Ă鎖���ł���̂ŁA�������ʂɕ\���������ꍇ
// ���ꂼ��u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�ƕ\�����邱�Ƃɂ���B�E�E�E���p�A�ȂǂƂ������t�����A���e�͊p�x�̒l�B
// �܂�A�u�ړ����p�iY���j�v�Ƃ������t�̌�b�́A�܂�肭�ǂ���������ƁA
// �u�L�����̐i�s�������A�����x�N�g���ł͖����ܓx�o�x�Ɍ����Ă�Z����]�p��Y����]�p�ŕ\�������ꍇ��Y����]�p�����݂̂̃A���O���l�v
// �Ƃ������ƂƂ���B
//
// �ړ����p�ɂ�Z����]�p��Y����]�p�ɂ��w��(_angRzMove, _angRyMove)�ƒP�ʃx�N�g���w��(_vX, _vY, _vZ) ������ƌ��������A
// �����ς�g���̂͑O�҂̕��ł���B�{���C�u�����̃��\�b�h�� _angRzMove �� _angRyMove �𑀍삷����̂������B
// �������A�ŏI�I�ɂ� ���[���h�ϊ��s��̈ړ���̍s������߂邽�߁A�u�P�ʃx�N�g��(_vX, _vY, _vZ)*�ړ����x �v  �Ƃ����v�Z������K�v������B
// ���ǍŌ�͒P�ʃx�N�g�����߂Ă���̂����B�ړ����̍��W�v�Z�Ȃǂ́A���񂴂�_angRzMove �� _angRyMove�ōs���āA�Ō�ɂP��P�ʃx�N�g����
// ���߂�A�Ƃ����̂����z�I�B�����œK���̗]�n�����Ԏc���Ă���i���A�܂������j�B
//
// �{�N���X���C�u�����ł́A����(_angRzMove, _angRyMove)�𑀍삵�āA���̃A���O���l�ɕ����x�N�g��(_vX, _vY, _vZ) ��Ǐ]�����Ă���B
// (_vX, _vY, _vZ)�̂ݒ��ڑ��삷��ƁA(_angRzMove, _angRyMove)�Ƃ̓���������邽�߁A�����͎��ȐӔC�ŁB
// �{�N���X�̃��\�b�h���g�p�������ł́A����Ȃ��Ƃ͋N����Ȃ����ƂƂ���B
//

// ���ړ����x��
// �L�����́u�ړ����x�v(_veloMove)��ێ����Ă���B�ړ�������@�͊ȒP�ŁA���t���[���u�ړ����p�v�Ɂu�ړ����x�v�����������ł���B
// �܂�u�ړ����p�v(_vX, _vY, _vZ)�Ɂu�ړ����x�v(_veloMove)���|���Z���Ă���B�P�t���[����̍��W��
// (_vX*_veloMove, _vY*_veloMove, _vZ*_veloMove) �ł���B  ����ɖ{���C�u�����̒P�ʋ���(�Q�[�����̒����P�ƍl���鐮���{�l�j���|����B
// ����āA(_vX*_veloMove*LEN_UNIT, _vY*_veloMove*LEN_UNIT, _vZ*_veloMove*LEN_UNIT)���P�t���[����̍��W�B

// ������]���p��
// �L�����������Ă�����p�i�����j�A���u����]���p�v�ƌĂԂ��Ƃɂ���B�u����]���p�v�́A���[���h�ϊ��s��̎���]�ƁA�P�΂P�ɑΉ����Ă���B
// ���[���h�ϊ��s��̎���]�Ƃ́AX����]�p�AY����]�p�AZ����]�p�̂��ƂŁA_angFace[AXIS_X]�A_angFace[AXIS_Y]�A_angFace[AXIS_Z]
// ���ێ����Ă���B
// �{���C�u�����ł́A�L���������_�ɂ���Ƃ��āA�P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g��(1, 0, 0) ���L�����́u�O���v�Ɛݒ肵�Ă���B�u����v�́i-1, 0, 0)�B
// �܂��A���[���h�ϊ��s��̉�]�s��̂����鏇�Ԃ́A��{�I�� �uX����]�s�� > Z����]�s�� > Y����]�s�� > �ړ��s�� > (�g��k��) �v �Ƃ���B
// (�� X�� > Y�� > Z�� �̏��ł͂Ȃ���I�j
// ����āAX����]�p�͊���]�����悤�Ƃ��A�L�����������Ă�������͕ς�炸�A�c���Z����]�p�ƁAY����]�p�ŃL�����������Ă�����������肷�邱�ƂƂ���B
// �����ŁAX����]�p�̓L�����̃X�s���A�̂���Q�p�iZ����]�p�EY����]�p�j�ŃL�����́u�O���v���p�������肷��Ƃ����ꍇ�A
// �u����]���p�v����قǂ́u�ړ����p�v�Ɠ����悤�ɁAZ����]�p��Y����]�p�i�ܓx�ƌo�x)�̂Q�̃A���O���l
// (_angFace[AXIS_Z], _angFace[AXIS_Y])�ŕ\���ł���B
// �܂�A�u�O���v�� Z����]�p�EY����]�p����0�x�Ƃ��A�Ⴆ�΁u�O���������Č������v��[Z����]�p,Y����]�p]=[0�x,180�x] �ƕ\������B�B
// �P�ɁuZ����]�p�v�ȂǂƏ����ƁA�u�ړ����p�v��Z����]�p�Ȃ̂��A�u����]���p�v��Z����]�p�Ȃ̂��B���ɂȂ邽�߁A
// �u����]���p(Z��)�v�u����]���p(Y��)�v�Ə������ƂƂ���B�i���ꉞ�u����]���p(X��)�v�����邪�A����̓X�s����\���A�O���Ƃ��������ւ̉e���͖����j
// �����Œ��ӂ́A�P�̃L�����������Ă�����p�ɑ΂��āA�Q�ʂ�̃A�N�Z�X������@������Ƃ������ƁB�Ⴆ�΁A
// �u�O���������ĉE�����v �� [����]���p(Z��), ����]���p(Y��)]=[0, 90�x] or [180�x,270�x] �Ƃŕ\���ł���B
// �i������]���p(Y��)�͍���n���W�̂���Y���̐������������Ĕ����v���j
// ���� �u�O���v �� [180�x,180�x]�Ƃ��\���ł��邵�A�u�O���������Č������v �� [0�x,180�x] �Ƃ��\���ł���B
// �ǂ���������Ă�������͓����A�A���p���͈قȂ�B
// ���R�A�u�ړ����p�v�ł��A�Q�ʂ�̃A�N�Z�X������@������̂����A������͌����ڂɍ��������B

// ���ړ����p�Ǝ���]���p�œ�����
// ������ �u�ړ����p�iZ���j�v���u����]���p(Z��)�v�ցA�u�ړ����p�iY���j�v���u����]���p(Y��)�v �փR�s�[���Ă��ƁA
// �Ȃ�ƈړ����p�ƁA�L�����N�^�̌����̓������ȒP�Ɏ��邶��܂����B
// �t�ɃL�����������Ă�������Ɉړ���Ǐ]�����邱�Ƃ��\���ȁB

// �������O�������@�\��
// �����O�������@�\�Ƃ́u�ړ����p�v��ݒ肷��ƁA����ɔ����Ď����I�Ɂu����]���p�v��ݒ肷�鎖���Ӗ����Ă���B
// ��̓I�ɂ́A�ȉ��̂悤�Ƀt���[�����ɁA�A���O���l���㏑���R�s�[���Ă��邾���B
//  �E�ړ����p�iZ���j �� ����]���p(Z��)
//  �E�ړ����p�iY���j �� ����]���p(Y��)
// �������u����]���p�v��ݒ�Ă��u�ړ����p�v�ω����Ȃ��i�t�͊֘A���Ȃ��j�̂Œ��ӁB

// ���p���x��
// �u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�A�u����]���p(Z��)�v�u����]���p(Y��)�v�ɂ́A���ꂼ��́u�p���x�v��݂��Ă���B
// �Ⴆ��90�x�E�Ɍ��������ꍇ�A�L�����������Ȃ�J�N���ƌ�����ς��Ă͔߂����̂ŁA���t���[���p���x�����p�����Z����悤�ɂ��āA
// ���炩�Ɍ�����ς���悤�ɂ���B
// �u�p���x�v�͐����̒��ӂ��K�v�B���̏ꍇ�͔����v���A���̏ꍇ�͎��v���ɂȂ�B
// �����]������ꍇ�A�^�[�Q�b�g�ƂȂ�p�x�ւ̓��B������@�̍l�����́A5�ʂ肠��B�i�A�N�Z�X���@�͂Q�ʂ肵���Ȃ��j
// �u��ɔ����v��ōs���v�u��Ɏ��v���ōs���v�u�߂��p�̎�������ōs���v�u�����Ȋp�̎�������ōs���v�u���݉���Ă�������ōs���v
// �ł���B���ꂼ��p�r������̂ŁA�I�v�V���������ȂǂŁA�I���ł���悤�ɂ������ȁB

// ���������ړ���
// ��L�̈ړ��̌n�Ƃ͂܂������ʂɁA�Ɨ����� X���AY���AZ���ɕ��s�Ȉړ��w�肪�ł���B
// �uX�������ړ����x�v�uY�������ړ����x�v�uZ�������ړ����x�v��ݒ肷��ƁA���t���[��(_X,_Y,_Z)�ɂ��ꂼ��̈ړ�������
// ���Z�����B


GgafDx9GeometryMover::GgafDx9GeometryMover(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;


    for (int i = 0; i < 3; i++) { // i=0:X���A1:Y���A2:Z�� ��\��

        //����]���p
        _angFace[i] = 0; //0 angle �� �R���̕��p�������Ă���
        //����]���p�̊p���x�i����]���p�̑����j= 0 angle/fream
        _angveloRotFace[i] = 0; //1�t���[���ɉ��Z����鎲��]���p�̊p�����B�f�t�H���g�͎���]���p�̊p���������A�܂�U����������B
        //����]���p�̊p���x��� �� 360,000 angle/fream
        _angveloRotTopFace[i] = ANGLE360; //_angveloRotFace[n] �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȏ���]���p�ɐU����������o���鎖���Ӗ�����
        //����]���p�̊p���x���� �� -360,000 angle/fream
        _angveloRotBottomFace[i] = ANGLE360 * -1; //_angveloRotFace[n] �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȏ���]���p�ɐU����������o���鎖���Ӗ�����
        //����]���p�̊p�����x�i�p���x�̑����j �� 0 angle/fream^2
        _angacceRotFace[i] = 0; //_angveloRotFace[n] �̑����B�f�t�H���g�͎���]���p�̊p�����x����
        //�ڕW����]���p�ւ̎�������t���O = ����
        _face_angle_targeting_flg[i] = false;
        //�ڕW�̎���]���p
        _angTargetRotFace[i] = 0; //�ڕW����]���p�ւ̎�������t���O = �����A�̏ꍇ�͖��Ӗ�
        //�ڕW�̎���]���p������~�@�\���L���ɂȂ��]����
        _face_angle_target_allow_way[i] = TURN_BOTH;
        //�ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj
        _face_angle_target_allow_velocity[i] = ANGLE180;
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
    _synchronize_RzFaceAngle_to_RzMoveAngle_flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B

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
    _synchronize_RyFaceAngle_to_RyMoveAngle_flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B

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
        if (_face_angle_targeting_flg[i]) {
            _angveloRotFace[i] += _angacceRotFace[i];
            setFaceAngleVelocity(i, _angveloRotFace[i]);

            if (_angveloRotFace[i] > 0) { //�����v���̏ꍇ
                angDistance = getFaceAngleDistance(i, _angTargetRotFace[i], TURN_COUNTERCLOCKWISE);
                if (_angveloRotFace[i] > angDistance && _face_angle_target_allow_way[i] != TURN_CLOCKWISE
                        && _face_angle_target_allow_velocity[i] >= _angveloRotFace[i]) {
                    addFaceAngle(i, angDistance);
                    _face_angle_targeting_flg[i] = false; //�t���O��߂��ďI��
                } else {
                    addFaceAngle(i, _angveloRotFace[i]);
                }
            } else if (_angveloRotFace[i] < 0) { //���v���̏ꍇ
                angDistance = getFaceAngleDistance(i, _angTargetRotFace[i], TURN_CLOCKWISE);
                if (_angveloRotFace[i] < angDistance && _face_angle_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_angle_target_allow_velocity[i] <= _angveloRotFace[i]) { //�ڕW���s���߂��Ă��܂���������ȓ�
                    addFaceAngle(i, angDistance);
                    _face_angle_targeting_flg[i] = false; //�t���O��߂��ďI��
                } else {
                    addFaceAngle(i, _angveloRotFace[i]);
                }
            } else {
                //_angveloRotFace[i] == 0
                addFaceAngle(i, 0);
            }

            if (_face_angle_targeting_flg[i] == false) {
                //�ڕW�����ɓ��B�������̏���
                //_angveloRotTopFace[i] = ANGLE360; //����]���p�̊p���x��� �� 360,000 angle/fream
                //_angveloRotBottomFace[i] = ANGLE360 * -1; //����]���p�̊p���x���� �� -360,000 angle/fream

                //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
                _angacceRotFace[i] = 0; //����]�����p�A�p���x���O��
                setFaceAngleVelocity(i, 0); //����]�����p�A�p�����x���O��
            }

        } else {
            //if (_angacceRotFace[i] != 0) {
            //�t���[�����̎���]���p����̏���
            _angveloRotFace[i] += _angacceRotFace[i];
            if (_angveloRotFace[i] != 0) {
                addFaceAngle(i, _angveloRotFace[i]);
            }
            //}
        }
    }

    //Actor�ɔ��f
    _pActor->_RX = _angFace[AXIS_X];
    _pActor->_RY = _angFace[AXIS_Y];
    _pActor->_RZ = _angFace[AXIS_Z];

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
            angle angDistance = getRzMoveAngleDistance(_angTargetRzMove, TURN_COUNTERCLOCKWISE);
            if (_angveloRzMove > angDistance && _move_angle_rz_target_allow_way != TURN_CLOCKWISE
                    && _move_angle_rz_target_allow_velocity >= _angveloRzMove) { //�ڕW���s���߂��Ă��܂���������ȓ�
                addRzMoveAngle(angDistance);
                _move_angle_rz_target_flg = false; //�t���O��߂��ďI��
            } else {
                addRzMoveAngle(_angveloRzMove);
            }
        } else if (_angveloRzMove < 0) { //���v���̏ꍇ

            angle angDistance = getRzMoveAngleDistance(_angTargetRzMove, TURN_CLOCKWISE);
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

        if (_angveloRyMove > 0) { //���݂͔����v���̏ꍇ
            angle angDistance = getRyMoveAngleDistance(_angTargetRyMove, TURN_COUNTERCLOCKWISE);
            if (_angveloRyMove > angDistance &&
                _move_angle_ry_target_allow_way != TURN_CLOCKWISE &&
                _move_angle_ry_target_allow_velocity >= _angveloRyMove)
            { //�ڕW���s���߂��Ă��܂���������ȓ�
                addRyMoveAngle(angDistance);
                _move_angle_ry_target_flg = false; //�t���O��߂��ďI��
            } else {
                addRyMoveAngle(_angveloRyMove);
            }
        } else if (_angveloRyMove < 0) { //���݂͎��v���̏ꍇ

            angle angDistance = getRyMoveAngleDistance(_angTargetRyMove, TURN_CLOCKWISE);
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

void GgafDx9GeometryMover::setFaceAngle(int prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = simplifyAngle(prm_angFace);
}

void GgafDx9GeometryMover::setFaceAngle(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAngle(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDx9GeometryMover::addFaceAngle(int prm_axis, angle prm_angDistance) {
    static angle angOffsetrot_FaceAngle;
    angOffsetrot_FaceAngle = prm_angDistance;
    if (_angveloRotBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAngle = _angveloRotBottomFace[prm_axis];
    } else if (prm_angDistance > _angveloRotTopFace[prm_axis]) {
        angOffsetrot_FaceAngle = _angveloRotTopFace[prm_axis];
    }
    setFaceAngle(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAngle);
}

void GgafDx9GeometryMover::setFaceAngleVelocity(int prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloRotTopFace[prm_axis]) {
        _angveloRotFace[prm_axis] = _angveloRotTopFace[prm_axis];
    } else if (prm_angveloRot < _angveloRotBottomFace[prm_axis]) {
        _angveloRotFace[prm_axis] = _angveloRotBottomFace[prm_axis];
    } else {
        _angveloRotFace[prm_axis] = prm_angveloRot;
    }
}

void GgafDx9GeometryMover::setFaceAngleVeloRenge(int prm_axis,
                                                    angvelo prm_angveloRot01,
                                                    angvelo prm_angveloRot02) {
    if (prm_angveloRot01 < prm_angveloRot02) {
        _angveloRotTopFace[prm_axis] = prm_angveloRot02;
        _angveloRotBottomFace[prm_axis] = prm_angveloRot01;
    } else {
        _angveloRotTopFace[prm_axis] = prm_angveloRot01;
        _angveloRotBottomFace[prm_axis] = prm_angveloRot02;
    }
    setFaceAngleVelocity(prm_axis, _angveloRotFace[prm_axis]); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometryMover::setFaceAngleVeloAcceleration(int prm_axis, angacce prm_angacceRot) {
    _angacceRotFace[prm_axis] = prm_angacceRot;
}

void GgafDx9GeometryMover::setSuspendTarget_FaceAngleV(int prm_axis,
                                                  int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMove) {
    setSuspendTarget_FaceAngle(
      prm_axis,
      GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
      prm_way_allow,
      prm_angveloAllowRyMove
    );
}

void GgafDx9GeometryMover::setSuspendTarget_FaceAngle(int prm_axis,
                                             angle prm_angTargetRot,
                                             int prm_way_allow,
                                             angvelo prm_angveloAllow) {
    _face_angle_targeting_flg[prm_axis] = true;
    _angTargetRotFace[prm_axis] = simplifyAngle(prm_angTargetRot);
    _face_angle_target_allow_way[prm_axis] = prm_way_allow;
    _face_angle_target_allow_velocity[prm_axis] = prm_angveloAllow;
}

angle GgafDx9GeometryMover::getFaceAngleDistance(int prm_axis, int prm_tX, int prm_tY, int prm_way) {
    return getFaceAngleDistance(prm_axis, GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY
            - (_pActor->_Y)), prm_way);
}

angle GgafDx9GeometryMover::getFaceAngleDistance(int prm_axis, angle prm_angTargetRot, int prm_way) {
    static angle _angTargetRot;
    _angTargetRot = simplifyAngle(prm_angTargetRot);
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < ANGLE180) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return -1 * (_angFace[prm_axis] - _angTargetRot);
            } else if (_angTargetRot == _angFace[prm_axis]) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot < _angFace[prm_axis]
                    + ANGLE180) {
                return _angTargetRot - _angFace[prm_axis];
            } else if (_angTargetRot == _angFace[prm_axis] + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angFace[prm_axis] + ANGLE180 < _angTargetRot && _angTargetRot <= ANGLE360) {
                return -1 * (_angFace[prm_axis] + (ANGLE360 - _angTargetRot));
            } else {
                //��������
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
            }
        } else if (ANGLE180 <= _angFace[prm_axis] && _angFace[prm_axis] <= ANGLE360) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis] - ANGLE180) {
                return ANGLE360 - _angFace[prm_axis] + _angTargetRot;
            } else if (_angTargetRot == _angFace[prm_axis] - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -ANGLE180;
            } else if (_angFace[prm_axis] - ANGLE180 < _angTargetRot && _angTargetRot
                    < _angFace[prm_axis]) {
                return -1 * (_angFace[prm_axis] - _angTargetRot);
            } else if (_angFace[prm_axis] == _angTargetRot) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot <= ANGLE360) {
                return _angTargetRot - _angFace[prm_axis];
            } else {
                //��������
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < ANGLE180) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return ANGLE360 - _angFace[prm_axis] + _angTargetRot;
            } else if (_angTargetRot == _angFace[prm_axis]) {
                //�d�Ȃ��Ă�ꍇ
                return ANGLE360;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot < _angFace[prm_axis] + ANGLE180) {
                return -1 * ( _angFace[prm_axis] + (ANGLE360 -_angTargetRot));
            } else if (_angTargetRot == _angFace[prm_axis] + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angFace[prm_axis] + ANGLE180 < _angTargetRot && _angTargetRot <= ANGLE360) {
                return _angTargetRot - _angFace[prm_axis];
            } else {
                //��������
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
            }
        } else if (ANGLE180 <= _angFace[prm_axis] && _angFace[prm_axis] <= ANGLE360) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis] - ANGLE180) {
                return -1 * (_angTargetRot - _angFace[prm_axis]);
            } else if (_angTargetRot == _angFace[prm_axis] - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return -ANGLE180;
            } else if (_angFace[prm_axis] - ANGLE180 < _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return (ANGLE360 - _angFace[prm_axis]) + _angTargetRot;
            } else if (_angFace[prm_axis] == _angTargetRot) {
                //�d�Ȃ��Ă�ꍇ
                return -ANGLE360;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot <= ANGLE360) {
                return (_angFace[prm_axis] + (ANGLE360 - _angTargetRot)) ;
            } else {
                //��������
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return (_angTargetRot - _angFace[prm_axis]);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] < ANGLE360) {
            return ANGLE360 - _angFace[prm_axis] + _angTargetRot;
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return -1 * (_angFace[prm_axis] + ANGLE360 - _angTargetRot);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] < ANGLE360) {
            return -1 * (_angFace[prm_axis] - _angTargetRot);
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDx9GeometryMover::getFaceAngleDistance() ���̂�����p�̋��������߂�܂���B(2)");
}


void GgafDx9GeometryMover::setMoveVeloRenge(int prm_veloMove01, int prm_veloMove02) {
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

void GgafDx9GeometryMover::setMoveVeloAcceleration(int prm_acceMove) {
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
    if (_synchronize_RzFaceAngle_to_RzMoveAngle_flg) {
        setFaceAngle(AXIS_Z, _angRzMove);
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

void GgafDx9GeometryMover::setRzMoveAngleVeloAcceleration(angacce prm_angacceRzMove) {
    _angacceRzMove = prm_angacceRzMove;
}

void GgafDx9GeometryMover::setRzMoveAngleVeloRenge(angvelo prm_angveloRzMove01,
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

void GgafDx9GeometryMover::setSuspendTarget_RzMoveAngle(angle prm_angTargetRzMove,
                                                    int prm_way_allow,
                                                    angvelo prm_angveloAllowRyMove) {
    _move_angle_rz_target_flg = true;
    _angTargetRzMove = simplifyAngle(prm_angTargetRzMove);
    _move_angle_rz_target_allow_way = prm_way_allow;
    _move_angle_rz_target_allow_velocity = prm_angveloAllowRyMove;
}

void GgafDx9GeometryMover::setSuspendTarget_RzMoveAngleV(int prm_tX,
                                                     int prm_tY,
                                                     int prm_way_allow,
                                                     angvelo prm_angveloAllowRyMove) {
    setSuspendTarget_RzMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getRzMoveAngleDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRzMoveAngleDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getRzMoveAngleDistance(angle prm_angTargetRzMove, int prm_way) {
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
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -ANGLE180;
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
                throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        if (0 <= _angRzMove && _angRzMove < ANGLE180) {
            if (0 <= angTargetRzMove && angTargetRzMove < _angRzMove) {
                return ANGLE360 - _angRzMove + angTargetRzMove;
            } else if (angTargetRzMove == _angRzMove) {
                //�d�Ȃ��Ă�ꍇ
                return ANGLE360;
            } else if (_angRzMove < angTargetRzMove && angTargetRzMove < _angRzMove + ANGLE180) {
                return -1*(_angRzMove + (ANGLE360-angTargetRzMove));
            } else if (angTargetRzMove == _angRzMove + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRzMove + ANGLE180 < angTargetRzMove && angTargetRzMove <= ANGLE360) {
                return angTargetRzMove - _angRzMove;
            } else {
                //��������
                _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
            }
        } else if (ANGLE180 <= _angRzMove && _angRzMove <= ANGLE360) {
            if (0 <= angTargetRzMove && angTargetRzMove < _angRzMove - ANGLE180) {
                return  -1*(_angRzMove - angTargetRzMove);
            } else if (angTargetRzMove == _angRzMove - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -ANGLE180;
            } else if (_angRzMove - ANGLE180 < angTargetRzMove && angTargetRzMove < _angRzMove) {
                return _angRzMove + (ANGLE360 - angTargetRzMove);
            } else if (_angRzMove == angTargetRzMove) {
                //�d�Ȃ��Ă�ꍇ
                return -ANGLE360;
            } else if (_angRzMove < angTargetRzMove && angTargetRzMove <= ANGLE360) {
                return angTargetRzMove + (ANGLE360 - _angRzMove);
            } else {
                //��������
                _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
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
            throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
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
            throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
        }
    }

    _TRACE_("_angRzMove=" << _angRzMove << "/angTargetRzMove=" << angTargetRzMove);
    throwGgafCriticalException("GgafDx9GeometryMover::getRzMoveAngleDistance() ���̂�����p�̋��������߂�܂���B(1)");

}


void GgafDx9GeometryMover::setRyMoveAngle(int prm_tX, int prm_tY) {
    setRyMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometryMover::setRyMoveAngle(angle prm_angle) {
    if (prm_angle != _angRyMove) {
        _angRyMove = simplifyAngle(prm_angle);
        GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    }
    if (_synchronize_RyFaceAngle_to_RyMoveAngle_flg) {
        setFaceAngle(AXIS_Y, _angRyMove);
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

void GgafDx9GeometryMover::setRyMoveAngleVeloAcceleration(angacce prm_angacceRyMove) {
    _angacceRyMove = prm_angacceRyMove;
}

void GgafDx9GeometryMover::setRyMoveAngleVeloRenge(angvelo prm_angveloRyMove01,
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

void GgafDx9GeometryMover::setSuspendTarget_RyMoveAngle(angle prm_angTargetRyMove,
                                                int prm_way_allow,
                                                angvelo prm_angveloAllowRyMove) {
    _move_angle_ry_target_flg = true;
    _angTargetRyMove = simplifyAngle(prm_angTargetRyMove);
    _move_angle_ry_target_allow_way = prm_way_allow;
    _move_angle_ry_target_allow_velocity = prm_angveloAllowRyMove;
}

void GgafDx9GeometryMover::setSuspendTarget_RyMoveAngleV(int prm_tX,
                                                 int prm_tY,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMove) {
    setSuspendTarget_RyMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getRyMoveAngleDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRyMoveAngleDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getRyMoveAngleDistance(angle prm_angTargetRyMove, int prm_way) {
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
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -ANGLE180;
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
                throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        if (0 <= _angRyMove && _angRyMove < ANGLE180) {
            if (0 <= angTargetRyMove && angTargetRyMove < _angRyMove) {
                return ANGLE360 - _angRyMove + angTargetRyMove;
            } else if (angTargetRyMove == _angRyMove) {
                //�d�Ȃ��Ă�ꍇ
                return ANGLE360;
            } else if (_angRyMove < angTargetRyMove && angTargetRyMove < _angRyMove + ANGLE180) {
                return -1*(_angRyMove + (ANGLE360-angTargetRyMove));
            } else if (angTargetRyMove == _angRyMove + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRyMove + ANGLE180 < angTargetRyMove && angTargetRyMove <= ANGLE360) {
                return angTargetRyMove - _angRyMove;
            } else {
                //��������
                _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
            }
        } else if (ANGLE180 <= _angRyMove && _angRyMove <= ANGLE360) {
            if (0 <= angTargetRyMove && angTargetRyMove < _angRyMove - ANGLE180) {
                return  -1*(_angRyMove - angTargetRyMove);
            } else if (angTargetRyMove == _angRyMove - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return -ANGLE180;
            } else if (_angRyMove - ANGLE180 < angTargetRyMove && angTargetRyMove < _angRyMove) {
                return _angRyMove + (ANGLE360 - angTargetRyMove);
            } else if (_angRyMove == angTargetRyMove) {
                //�d�Ȃ��Ă�ꍇ
                return -ANGLE360;
            } else if (_angRyMove < angTargetRyMove && angTargetRyMove <= ANGLE360) {
                return angTargetRyMove + (ANGLE360 - _angRyMove);
            } else {
                //��������
                _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
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
            throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
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
            throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
        }
    }

    _TRACE_("_angRyMove=" << _angRyMove << "/angTargetRyMove=" << angTargetRyMove);
    throwGgafCriticalException("GgafDx9GeometryMover::getRyMoveAngleDistance() ���̂�����p�̋��������߂�܂���B(1)");

}


void GgafDx9GeometryMover::setRzRyMoveAngle(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMove || prm_angRy !=_angRyMove ) {
        _angRzMove = simplifyAngle(prm_angRz);
        _angRyMove = simplifyAngle(prm_angRy);
        GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    }
    if (_synchronize_RzFaceAngle_to_RzMoveAngle_flg) {
        setFaceAngle(AXIS_Z, _angRzMove);
    }
    if (_synchronize_RyFaceAngle_to_RyMoveAngle_flg) {
        setFaceAngle(AXIS_Y, _angRyMove);
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

void GgafDx9GeometryMover::setSuspendTarget_RzRyMoveAngle(GgafDx9GeometricActor* prm_pActor_Target) {
    setSuspendTarget_RzRyMoveAngle(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9GeometryMover::setSuspendTarget_RzRyMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
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
    setSuspendTarget_RzMoveAngle(angRz_Target);
    setSuspendTarget_RyMoveAngle(angRy_Target);
}

void GgafDx9GeometryMover::setVxMoveVeloRenge(velo prm_veloVxMove01, velo prm_veloVxMove02) {
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

void GgafDx9GeometryMover::setVxMoveVeloAcceleration(acce prm_acceVxMove) {
    _acceVxMove = prm_acceVxMove;
}

void GgafDx9GeometryMover::setVyMoveVeloRenge(velo prm_veloVyMove01, velo prm_veloVyMove02) {
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

void GgafDx9GeometryMover::setVyMoveVeloAcceleration(acce prm_acceVyMove) {
    _acceVyMove = prm_acceVyMove;
}

void GgafDx9GeometryMover::setVzMoveVeloRenge(velo prm_veloVzMove01, velo prm_veloVzMove02) {
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

void GgafDx9GeometryMover::setVzMoveVeloAcceleration(acce prm_acceVzMove) {
    _acceVzMove = prm_acceVzMove;
}



void GgafDx9GeometryMover::executeSplineMoveProgram(GgafDx9SplineProgram* prm_progSP, int prm_option) {
    _progSP = prm_progSP;
    _progSP->begin(_pActor, prm_option);
}

void GgafDx9GeometryMover::executeTagettingMoveAngleSequence(int prm_tX, int prm_tY, int prm_tZ,
                                                             angvelo prm_angVelocity, int prm_way) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAngle(prm_tX - _pActor->_X,
                              prm_tY - _pActor->_Y,
                              prm_tZ - _pActor->_Z,
                              out_angRz_Target,
                              out_angRy_Target);
    if (getRzMoveAngleDistance(out_angRz_Target, prm_way) > 0) {
        setRzMoveAngleVelocity(prm_angVelocity);
    } else {
       setRzMoveAngleVelocity(-1 * prm_angVelocity);
    }
    if (getRyMoveAngleDistance(out_angRy_Target, prm_way) > 0) {
        setRyMoveAngleVelocity(prm_angVelocity);
    } else {
        setRyMoveAngleVelocity(-1 * prm_angVelocity);
    }

    setSuspendTarget_RzMoveAngle(out_angRz_Target);
    setSuspendTarget_RyMoveAngle(out_angRy_Target);
}

void GgafDx9GeometryMover::executeTagettingMoveAngleSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                             angvelo prm_angVelocity, int prm_way) {
    if (getRzMoveAngleDistance(prm_angRz_Target, prm_way) > 0) {
        setRzMoveAngleVelocity(prm_angVelocity);
    } else {
       setRzMoveAngleVelocity(-1 * prm_angVelocity);
    }
    if (getRyMoveAngleDistance(prm_angRy_Target, prm_way) > 0) {
        setRyMoveAngleVelocity(prm_angVelocity);
    } else {
        setRyMoveAngleVelocity(-1 * prm_angVelocity);
    }

    setSuspendTarget_RzMoveAngle(prm_angRz_Target);
    setSuspendTarget_RyMoveAngle(prm_angRy_Target);

}

void GgafDx9GeometryMover::executeTagettingRzMoveAngleSequence(angle prm_angRz_Target,
                                                               angvelo prm_angVelocity, int prm_way) {
    if (getRzMoveAngleDistance(prm_angRz_Target, prm_way) > 0) {
        setRzMoveAngleVelocity(prm_angVelocity);
    } else {
       setRzMoveAngleVelocity(-1 * prm_angVelocity);
    }
    setSuspendTarget_RzMoveAngle(prm_angRz_Target);

}

void GgafDx9GeometryMover::executeTagettingRyMoveAngleSequence(angle prm_angRy_Target,
                                                               angvelo prm_angVelocity, int prm_way) {
    if (getRyMoveAngleDistance(prm_angRy_Target, prm_way) > 0) {
        setRyMoveAngleVelocity(prm_angVelocity);
    } else {
        setRyMoveAngleVelocity(-1 * prm_angVelocity);
    }
    setSuspendTarget_RyMoveAngle(prm_angRy_Target);
}



GgafDx9GeometryMover::~GgafDx9GeometryMover() {

    //DELETE_POSSIBLE_NULL(_progSP);//Actor�Ŏn������B����Ȃ�
}
