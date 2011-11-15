#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

// �y�����z�{�N���X�̍l�����ƒP��̕\��
//
// ���Q��ނ̕�����
// �u�L�����̕����v�Ƃ������t���B���Ȃ��߁A���̂Q��ނ̒P����`����B�u�ړ����p�i�����j�v�Ɓu���ʕ��p�i�����j�v�B
// �u�ړ����p�v�̓L�����̐i�s�����݂̂�\������B����́u�ړ����x�v�Ɣ����āA�L�����͍��W�����ړ����邱�ƂƂ���B
// �u���ʕ��p�v�̓L�����̌����i�O���������j�݂̂�\�����鎖�Ƃ���B
// �L�����N�^����ʂ̏㕔���牺���ֈړ����Ă��A�L�����N�^�͉��������Ƃ͌��炸���@�Ɍ����Ăق����ꍇ������B
// �܂��́A�E�ɃL�������������āA���Ɉړ������������Ƃ�����B���ꂼ��Q�̕����ݒ肪�K�v�B
//
// ���ړ����p�̂Q��ނ̕\�����@��
// �L�������i�ޕ����A�܂�ړ����p�̕����́A���_����P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g�� (_vX, _vY, _vZ) �ŕ\�����@�ƁA
// �Q�̎���]�A���O���l (_angRzMv, _angRyMv) �ŕ\�����@�̂Q��ޗp�ӂ����B�N�H�[�^�j�I���͍��̂Ƃ��떳���B
// _angRzMv �� Z����]�p�A _angRyMv �� Y����]�p ���Ӗ����Ă���B
// ����͕����x�N�g�����A�ܓx�ƌo�x�A�i�p�ƃA�W�}�X�j�̊֌W�Ɍ����āA�Ή������悤�Ƃ����݌v�B
// ���ӂ��邱�Ƃ́AY����]�p���o�x �͏�ɐ��藧���AZ����]�p���ܓx �́AZ����]�p �� Y����]�p�̏��Ԃł���ꍇ�Ɍ��萬�藧�B
// �{�N���X�ł́A�uZ����] �� Y����]�̏��Ԃł�Z����]�p�EY����]�p�v���ȗ����āA�P�ɁuZ����]�p�EY����]�p�v�ƕ\�����鎖�Ƃ���B
// �������ʂɕ\���������ꍇ�́A���ꂼ��u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�Ə������Ƃɂ���B
//
// �\�[�X�R�[�h���́A�ϐ��⃁�\�b�h��
// �uRz�v�Ƃ����\�L�́u�ړ����p�iZ���j�v���Ӗ����Ă���B
// �uRy�v�Ƃ����\�L�́u�ړ����p�iY���j�v���Ӗ����Ă���B
// �uRzRy�v�Ƃ����\���́uZ����] �� Y����]�̏��Ԃ̈ړ����p�v��\���Ă���B
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
// �܂�u�ړ����p�v(_vX, _vY, _vZ)�Ɂu�ړ����x�v(_veloMv)���|���Z���Ă���B�P�t���[����̍��W��
// (_vX*_veloMv, _vY*_veloMv, _vZ*_veloMv) �ł���B  ����ɖ{���C�u�����̒P�ʋ���(�Q�[�����̒����P�ƍl���鐮���{�l�j���|����B
// ����āA(_vX*_veloMv*LEN_UNIT, _vY*_veloMv*LEN_UNIT, _vZ*_veloMv*LEN_UNIT)���P�t���[����̍��W�B

// �����ʕ��p:AngFace��
// �L�����̃��[�J�����W�Ō����Ă�����p�i�����j���u���ʕ��p�v�ƌĂԂ��Ƃɂ���B
//�u���ʕ��p�v�́A���[���h�ϊ��s��̎���]�Ɠ�����]���@�ł���B
// ���[���h�ϊ��s��̎���]�Ƃ́AX����]�p�AY����]�p�AZ����]�p�̂��ƂŁA���ꂼ��A
// _angFace[AXIS_X], _angFace[AXIS_Y], _angFace[AXIS_Z] �ƈ�v����B
// �{���C�u�����ł́A�����x�N�g��(1, 0, 0) ���L�����́u�O���v�Ɛݒ肵�Ă���B
// X�t�@�C���Ȃǂ̃��b�V�����f�����AX���̐��̕����Ɍ����Ă��郂�m�Ƃ���B�܂��A���f���u������́v�́i0, 1, 0)�Ƃ���B
// ���[���h�ϊ��s��̉�]�s��̊|���鏇�Ԃ́A��{�I�� �uX����]�s�� > Z����]�s�� > Y����]�s�� > �ړ��s�� > (�g��k��) �v �Ƃ���B
// (��  X�� > Y�� > Z�� �̏��ł͂Ȃ���I�j
// ����āAX����]�p�͊���]�����悤�Ƃ��A�L�����������Ă�������͕ς�炸�A�c���Z����]�p�ƁAY����]�p�ŃL�����������Ă�����������肷�邱�ƂƂ���B
// X����]�p�̓L�����̃X�s���A�̂���Q�p�iZ����]�p�EY����]�p�j�ŃL�����́u�O���v���p�������肷��Ƃ����ꍇ�A
// �u���ʕ��p�v����قǂ́u�ړ����p�v�Ɠ����悤�ɁAZ����]�p��Y����]�p�i�ܓx�ƌo�x)�̂Q�̃A���O���l
// (_angFace[AXIS_Z], _angFace[AXIS_Y])�ŕ\���ł���B
// �܂�A�u�O���v�� Z����]�p�EY����]�p����0�x�Ƃ��A�Ⴆ�΁u���v��[Z����]�p,Y����]�p]=[0�x,180�x] �ƕ\������B�B
// �P�ɁuZ����]�p�v�ȂǂƏ����ƁA�u�ړ����p�v��Z����]�p�Ȃ̂��A�u���ʕ��p�v��Z����]�p�Ȃ̂��B���ɂȂ邽�߁A
// �u���ʕ��p(Z��)�v�u���ʕ��p(Y��)�v�Ə������ƂƂ���B�i���u���ʕ��p(X��)�v�����邪�A����̓X�s����\�������ւ̉e���͖����j
// �����Œ��ӂ́A�P�̃L�����������Ă�����p�ɑ΂��āA��ɂQ�ʂ�̃A�N�Z�X������@������Ƃ������ƁB�Ⴆ�΁A
// �u�O��(1, 0, 0)�������Đ^�E�����v �� [���ʕ��p(Z��), ���ʕ��p(Y��)]=[0, 90�x] or [180�x,270�x] �Ƃŕ\���ł���B
// �i�����ʕ��p(Y��)�͍���n���W�̂���Y���̐������������Ĕ����v���j
// ���� �u�O���v �� [180�x,180�x]�Ƃ��\���ł��邵�A�u�^���v �� [0�x,180�x] �Ƃ� [180�x,0�x] �Ƃ��\���ł���B
// �ǂ���������Ă�������͓��������A�p��(�L�����̏����)���قȂ�B�p�����قȂ�Ƃ܂����L�����͒��ӂ��邱�ƁB
// ���R�A�u�ړ����p�v�ł��A�Q�ʂ�̃A�N�Z�X������@������̂����A������͌����ڂ͍��������B�����������p�x�v�Z����Ƃ��ɉe�����ł�������Ȃ��B


// �������O�������@�\��
// ���Ă����� �u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v���A���ꂼ��u���ʕ��p(Z��)�v�u���ʕ��p(Y��)�v �փR�s�[���Ă��ƁA
// �Ȃ�ƈړ����p�ƁA�L�����N�^�̌����̓������ȒP�Ɏ��邶��Ȃ����I
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
// �����]������ꍇ�A�^�[�Q�b�g�ƂȂ�p�x�ւ̓��B����A�N�Z�X���@�͂Q�ʂ肾���A�l�����͏��5�ʂ肠��B
// �u��ɔ����v��ōs���v�u��Ɏ��v���ōs���v�u�߂��p�̎�������ōs���v�u�����Ȋp�̎�������ōs���v�u���݉���Ă�������ōs���v
// �ł���B���ꂼ��p�r������̂ŁA�I�v�V���������ȂǂŁA�I���ł���悤�ɂ������ȁB���ł����B

// ���������ړ�: VxMv VyMv VzMv��
// ��L�̈ړ��̌n�Ƃ͂܂������ʂɁA�Ɨ����� X���AY���AZ���ɕ��s�Ȉړ��w�肪�ł���B
// �uX�������ړ����x�v�uY�������ړ����x�v�uZ�������ړ����x�v��ݒ肷��ƁA���t���[��(_X,_Y,_Z)�ɂ��ꂼ��̈ړ�������
// ���Z�����B

//�����̑��ǋL��
//�E�ړ����x�A�ړ����p�p���x�A����]�p�p���x�ɂ́A���ꂼ������x���ݒ�ł���B
//�E����]�́A�{���� Z > X > Y �̎���]���Ԃɂ���̂���ʓI�̂悤���B�܂�O���̊T�O��Z���ŉ��ł���킯���A�Ȃ�قǂ킩��₷���B
//  ���݂� X > Z > Y �́A����Z�������O����X���ł���B
//  ���Ƃ���2D�̉��X�N���[���V���[�e�B���O����낤�Ǝv���Ă���A���� X > Z �����Ő݌v���s���Ă����̂������ł��邪�A�������ǂ�Ȃ��B
//  �܂����A3D�V���[�e�B���O�ɂ���Ƃ͎����ł��v���Ă��݂Ȃ������E�E�E

//2010/02/19�ǋL
// �����܂ɁuRyRz�v�Ƃ����\�������݂���i�uRzRy�v�ƈقȂ�j���A����́uY����] �� Z����]�̏��Ԃ̈ړ����p�v��\���Ă���̂Œ��ӁB
// �@�܂��A�u�ړ����p�iZ���j�v������]�̏��Ԃ̈Ⴂ�𖾊m�ɂ��邽��
// �@�uRzRy��Rz�v�uRyRz��Rz�v�Ə������肵�Ă���Ƃ��������B�i�P�ɁuRz�v�����̏ꍇ�́uRzRy��Rz�v���Ӗ����Ă���j

//�ǋL
//�E���炩�ړ����\�ɁI

//TODO:
//���x�i�������x�j�̒ǉ�
//�C�ӎ���]�i�N�H�[�^�j�I���j
//�N���X�̔�剻
//�y�����z��Z�߂�



GgafDxKurokoA::GgafDxKurokoA(GgafDxGeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;
    for (int i = 0; i < 3; i++) { // i=0:X���A1:Y���A2:Z�� ��\��

        //���ʕ��p
        _angFace[i] = 0; //0 angle �� �R���̕��p�������Ă���
        //���ʕ��p�̊p���x�i���ʕ��p�̑����j= 0 angle/fream
        _ang_veloFace[i] = 0; //1�t���[���ɉ��Z����鐳�ʕ��p�̊p�����B�f�t�H���g�͐��ʕ��p�̊p���������A�܂�U����������B
        //���ʕ��p�̊p���x��� �� 360,000 angle/fream
        _ang_veloTopFace[i] = D360ANG; //_ang_veloFace[n] �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȑ��ʕ��p�ɐU����������o���鎖���Ӗ�����
        //���ʕ��p�̊p���x���� �� -360,000 angle/fream
        _ang_veloBottomFace[i] = D360ANG * -1; //_ang_veloFace[n] �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȑ��ʕ��p�ɐU����������o���鎖���Ӗ�����
        //���ʕ��p�̊p�����x�i�p���x�̑����j �� 0 angle/fream^2
        _ang_acceFace[i] = 0; //_ang_veloFace[n] �̑����B�f�t�H���g�͐��ʕ��p�̊p�����x����

        _ang_jerkFace[i] = 0;
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
    _ang_veloRzMv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iZ����]�j�̊p���x��� = +360,000 angle/fream
    _ang_veloRzTopMv = D360ANG; //_ang_veloRzMv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p���x���� = -360,000 angle/fream
    _ang_veloRzBottomMv = D360ANG * -1; //_ang_veloRzMv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p�����x = 0 angle/fream^2
    _ang_acceRzMv = 0; //_ang_veloRzMv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _ang_jerkRzMv = 0;
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
    _ang_veloRyMv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iY����]�j�̊p���x��� = +360,000 angle/fream
    _ang_veloRyTopMv = D360ANG; //_ang_veloRyMv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p���x���� = -360,000 angle/fream
    _ang_veloRyBottomMv = D360ANG * -1; //_ang_veloRyMv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p�����x = 0 angle/fream^2
    _ang_acceRyMv = 0; //_ang_veloRyMv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _ang_jerkRyMv = 0;
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

    _smooth_mv_velo_seq_flg = false;
    _smooth_mv_velo_seq_endacc_flg = true;
    _smooth_mv_velo_seq_top_velo = 0;
    _smooth_mv_velo_seq_end_velo = 0;
    _smooth_mv_velo_seq_target_distance = 0;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_target_frames = 0;
    _smooth_mv_velo_seq_frame_of_spent = 0;
    _smooth_mv_velo_seq_p1 = 0;
    _smooth_mv_velo_seq_p2 = 0;
    _smooth_mv_velo_seq_progress = -1;


    _taget_mv_ang_alltime_flg = false;
    _taget_mv_ang_alltime_pActor = NULL;
    _taget_mv_ang_alltime_tX = 0;
    _taget_mv_ang_alltime_tY = 0;
    _taget_mv_ang_alltime_tZ = 0;
    _taget_mv_ang_alltime_angVelo = 0;
    _taget_mv_ang_alltime_angAcce = 0;
    _taget_mv_ang_alltime_way = TURN_CLOSE_TO;
    _taget_mv_ang_alltime_optimize_ang = true;

}

void GgafDxKurokoA::behave() {

    //���ʕ��p����
    angle angDistance;
    for (int i = 0; i < 3; i++) {
        if (_face_ang_targeting_flg[i]) { //�^�[�Q�b�g����������ꍇ
            _ang_veloFace[i] += _ang_acceFace[i];
            setFaceAngVelo((axis)i, _ang_veloFace[i]);

            if (_ang_veloFace[i] > 0) { //�����v���̏ꍇ
                angDistance = getFaceAngDistance((axis)i, _angTargetFace[i], TURN_COUNTERCLOCKWISE);
                if (_ang_veloFace[i] > angDistance && _face_ang_target_allow_way[i] != TURN_CLOCKWISE
                        && _face_ang_target_allow_velo[i] >= _ang_veloFace[i]) {

                    //_TRACE_("STOP1 _ang_veloFace["<<i<<"]="<<_ang_veloFace[i]<<" angDistance="<<angDistance<<" _face_ang_target_allow_velo["<<i<<"]="<<_face_ang_target_allow_velo[i]<<" _ang_veloFace["<<i<<"]="<<_ang_veloFace[i]);
                    addFaceAng((axis)i, angDistance);
                    if (_face_ang_targeting_stop_flg[i]) {
                        _face_ang_targeting_flg[i] = false; //�t���O��߂��ďI��
                        _face_ang_targeting_stop_flg[i] = false;
                    }
                } else {
                    addFaceAng((axis)i, _ang_veloFace[i]);
                }
            } else if (_ang_veloFace[i] < 0) { //���v���̏ꍇ
                angDistance = getFaceAngDistance((axis)i, _angTargetFace[i], TURN_CLOCKWISE);
                if (_ang_veloFace[i] < angDistance && _face_ang_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_ang_target_allow_velo[i] <= _ang_veloFace[i]) { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                    addFaceAng((axis)i, angDistance);
                    if (_face_ang_targeting_stop_flg[i]) { //��~���ėL��Ȃ��
                        _face_ang_targeting_flg[i] = false; //�t���O��߂��ďI��
                    }
                } else {
                    addFaceAng((axis)i, _ang_veloFace[i]);
                }
            } else {
                //_ang_veloFace[i] == 0
                addFaceAng((axis)i, 0);
            }

            if (_face_ang_targeting_flg[i] == false) {
                //�ڕW�����ɓ��B�������̏���
                //_ang_veloTopFace[i] = D360ANG; //���ʕ��p�̊p���x��� �� 360,000 angle/fream
                //_ang_veloBottomFace[i] = D360ANG * -1; //���ʕ��p�̊p���x���� �� -360,000 angle/fream

                //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
                _ang_acceFace[i] = 0; //����]�����p�A�p���x���O��
                setFaceAngVelo((axis)i, 0); //����]�����p�A�p�����x���O��
            }

        } else {
            //if (_ang_acceFace[i] != 0) {
            //�t���[�����̐��ʕ��p����̏���
            _ang_veloFace[i] += _ang_acceFace[i];
            if (_ang_veloFace[i] != 0) {
                addFaceAng((axis)i, _ang_veloFace[i]);
            }
            //}
        }
    }

    //Actor�ɔ��f
    _pActor->_RX = _angFace[AXIS_X];
    _pActor->_RY = _angFace[AXIS_Y];
    _pActor->_RZ = _angFace[AXIS_Z];

    ///////////////////////////////////////////////////Mover

    //_accMv += _jerkMv;
    //�ړ������x�̏���
    _veloMv += _accMv;
    setMvVelo(_veloMv);

    //�Ȃ߂炩�ړ��V�[�N�G���X�N����
    if (_smooth_mv_velo_seq_flg) {
        if (_smooth_mv_velo_seq_target_frames < 0) {
            //�ڕW�����w��̏ꍇ
            if (_smooth_mv_velo_seq_progress == 0) {
                //�����ݒ�
                setMvAcceBy_Dv(_smooth_mv_velo_seq_p1, _smooth_mv_velo_seq_top_velo);
                _smooth_mv_velo_seq_progress++;
            } else if (_smooth_mv_velo_seq_progress == 1) {
                //������
                if (_smooth_mv_velo_seq_mv_distance >= _smooth_mv_velo_seq_p1) {
                    //p1 �ɓ��B����� ������
                    setMvAcce(0);
                    setMvVelo(_smooth_mv_velo_seq_top_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 2) {
                //������
                if (_smooth_mv_velo_seq_mv_distance >= _smooth_mv_velo_seq_p2) {
                    //p2 �ɓ��B����� ����t���[�����猸����
                    setMvAcceBy_Dv(_smooth_mv_velo_seq_target_distance - _smooth_mv_velo_seq_mv_distance, _smooth_mv_velo_seq_end_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 3) {
                //������
                if (_smooth_mv_velo_seq_mv_distance >= _smooth_mv_velo_seq_target_distance) {
                    //�ڕW�����֓��B
                    setMvVelo(_smooth_mv_velo_seq_end_velo);
                    if (_smooth_mv_velo_seq_endacc_flg) {
                        setMvAcce(0);
                    }
                    _smooth_mv_velo_seq_progress++;
                    _smooth_mv_velo_seq_flg = false; //�����܂�
                }
            }
        } else {
            //�ڕW���Ԏw��̏ꍇ
            if (_smooth_mv_velo_seq_progress == 0) {
                //�����ݒ�
                setMvAcceBy_tv(_smooth_mv_velo_seq_p1, _smooth_mv_velo_seq_top_velo);
                _smooth_mv_velo_seq_progress++;
            } else if (_smooth_mv_velo_seq_progress == 1) {
                //������
                if (_smooth_mv_velo_seq_frame_of_spent >= _smooth_mv_velo_seq_p1) {
                    //p1 �ɓ��B����� ������
                    setMvAcce(0);
                    setMvVelo(_smooth_mv_velo_seq_top_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 2) {
                //������
                if (_smooth_mv_velo_seq_frame_of_spent >= _smooth_mv_velo_seq_p2) {
                    //p2 �ɓ��B����� ����t���[�����猸����
                    setMvAcceBy_tv(_smooth_mv_velo_seq_target_frames - _smooth_mv_velo_seq_frame_of_spent, _smooth_mv_velo_seq_end_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 3) {
                //������
                if (_smooth_mv_velo_seq_frame_of_spent >= _smooth_mv_velo_seq_target_frames) {
                    //�ڕW�����֓��B
                    setMvVelo(_smooth_mv_velo_seq_end_velo);
                    if (_smooth_mv_velo_seq_endacc_flg) {
                        setMvAcce(0);
                    }
                    _smooth_mv_velo_seq_progress++;
                    _smooth_mv_velo_seq_flg = false; //�����܂�
                }
            }

        }


    }



    if (_smooth_mv_velo_seq_flg) {
        if (_smooth_mv_velo_seq_target_frames < 0) {
            _smooth_mv_velo_seq_mv_distance+=abs(_veloMv);
        } else {
            _smooth_mv_velo_seq_frame_of_spent++;
        }
    }

    ///////////
    //�ڕW�ړ����p�iZ����]�j�A���O��������~�@�\�g�p���̏ꍇ
    if (_mv_ang_rz_target_flg) {

        _ang_veloRzMv += _ang_acceRzMv;
        setRzMvAngVelo(_ang_veloRzMv);

        if (_ang_veloRzMv > 0) { //�����v���̏ꍇ
            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_COUNTERCLOCKWISE);
            if (_ang_veloRzMv > angDistance && _mv_ang_rz_target_allow_way != TURN_CLOCKWISE
                    && _mv_ang_rz_target_allow_velo >= _ang_veloRzMv) { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                addRzMvAng(angDistance);
                if (_mv_ang_rz_target_stop_flg) { //��~�w�肠��Ȃ��
                    _mv_ang_rz_target_flg = false; //�t���O��߂��ďI��
                }
            } else {
                addRzMvAng(_ang_veloRzMv);
            }
        } else if (_ang_veloRzMv < 0) { //���v���̏ꍇ

            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_CLOCKWISE);
            if (_ang_veloRzMv < angDistance && _mv_ang_rz_target_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_mv_ang_rz_target_allow_velo <= _ang_veloRzMv) {
                addRzMvAng(angDistance);
                if (_mv_ang_rz_target_stop_flg) { //��~�w�肠��Ȃ��
                    _mv_ang_rz_target_flg = false; //�t���O��߂��ďI��
                }
            } else {
                addRzMvAng(_ang_veloRzMv);
            }
        } else {
            addRzMvAng(0);
        }
        if (_mv_ang_rz_target_flg == false) {
            //_ang_veloRzTopMv = D360ANG; //�ړ����p�iZ����]�j�̊p���x��� �� 360,000 angle/fream
            //_ang_veloRzBottomMv = D360ANG * -1; //�ړ����p�iZ����]�j�̊p���x���� �� -360,000 angle/fream

            //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
            _ang_acceRzMv = 0; //Z���ړ������p�A�p�����x���O��
            setRzMvAngVelo(0); //Z���ړ������p�A�p���x���O��
        }

    } else {
        //if (_ang_acceRzMv != 0) {

        _ang_acceRzMv += _ang_jerkRzMv;
        //�t���[�����̈ړ����p�iZ����]�j����̏���
        _ang_veloRzMv += _ang_acceRzMv;
        if (_ang_veloRzMv != 0) {
            addRzMvAng(_ang_veloRzMv);
        }
        //}
    }
    ////////////////
    //�ڕW�ړ����p�iY����]�j�A���O��������~�@�\�g�p���̏ꍇ
    if (_mv_ang_ry_target_flg) {

        _ang_veloRyMv += _ang_acceRyMv;
        setRyMvAngVelo(_ang_veloRyMv);

        if (_ang_veloRyMv > 0) { //���݂͔����v���̏ꍇ
            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_COUNTERCLOCKWISE);
            if (_ang_veloRyMv > angDistance &&
                _mv_ang_ry_target_allow_way != TURN_CLOCKWISE &&
                _mv_ang_ry_target_allow_velo >= _ang_veloRyMv)
            { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                addRyMvAng(angDistance);
                if (_mv_ang_ry_target_stop_flg) { //��~�w�肠��Ȃ��
                    _mv_ang_ry_target_flg = false; //�t���O��߂��ďI��
                }
            } else {
                addRyMvAng(_ang_veloRyMv);
            }
        } else if (_ang_veloRyMv < 0) { //���݂͎��v���̏ꍇ

            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_CLOCKWISE);
            if (_ang_veloRyMv < angDistance &&
                _mv_ang_ry_target_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_mv_ang_ry_target_allow_velo <= _ang_veloRyMv)
            {
                addRyMvAng(angDistance);
                if (_mv_ang_ry_target_stop_flg) { //��~�w�肠��Ȃ��
                    _mv_ang_ry_target_flg = false; //�t���O��߂��ďI��
                }
            } else {
                addRyMvAng(_ang_veloRyMv);
            }
        } else {
            //_ang_veloRyMv==0
            addRyMvAng(0);
        }
        if (_mv_ang_ry_target_flg == false) {
            //_ang_veloRyTopMv = D360ANG; //�ړ����p�iY����]�j�̊p���x��� �� 360,000 angle/fream
            //_ang_veloRyBottomMv = D360ANG*-1; //�ړ����p�iY����]�j�̊p���x���� �� -360,000 angle/fream

            //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
            _ang_acceRyMv = 0; //Y���ړ������p�A�p�����x���O��
            setRyMvAngVelo(0); //Y���ړ������p�A�p���x���O��
        }

    } else {
        //if (_ang_acceRyMv != 0) {
        _ang_acceRyMv += _ang_jerkRyMv;
        //�t���[�����̈ړ����p�iY����]�j����̏���
        _ang_veloRyMv += _ang_acceRyMv;
        if(_ang_veloRyMv != 0) {
            addRyMvAng(_ang_veloRyMv);
        }
        //}
    }
    ///////////////
    if (_taget_mv_ang_alltime_pActor && _mv_ang_ry_target_flg == false && _mv_ang_ry_target_flg == false) {
        if (_taget_mv_ang_alltime_pActor) {
            keepTurnMvAngAllTime(
                    _taget_mv_ang_alltime_pActor,
                    _taget_mv_ang_alltime_angVelo,
                    _taget_mv_ang_alltime_angAcce,
                    _taget_mv_ang_alltime_optimize_ang);
        } else {
            keepTurnMvAngAllTime(
                    _taget_mv_ang_alltime_pActor->_X - _pActor->_X,
                    _taget_mv_ang_alltime_pActor->_Y - _pActor->_Y,
                    _taget_mv_ang_alltime_pActor->_Z - _pActor->_Z,
                    _taget_mv_ang_alltime_angVelo,
                    _taget_mv_ang_alltime_angAcce,
                    _taget_mv_ang_alltime_optimize_ang);
        }

    }
    //Actor�ɔ��f
    _pActor->_X += (int)(_vX * _veloMv);
    _pActor->_Y += (int)(_vY * _veloMv);
    _pActor->_Z += (int)(_vZ * _veloMv);


}

void GgafDxKurokoA::setFaceAng(axis prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = GgafDxUtil::simplifyAng(prm_angFace);
}

void GgafDxKurokoA::setFaceAng(coord prm_tX, coord prm_tY, coord prm_tZ) {
    GgafDxUtil::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDxKurokoA::addFaceAng(axis prm_axis, angle prm_angDistance) {
    angle angOffsetrot_FaceAng;
    angOffsetrot_FaceAng = prm_angDistance;
    if (_ang_veloBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAng = _ang_veloBottomFace[prm_axis];
    } else if (prm_angDistance > _ang_veloTopFace[prm_axis]) {
        angOffsetrot_FaceAng = _ang_veloTopFace[prm_axis];
    }
    setFaceAng(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAng);
}

void GgafDxKurokoA::setFaceAngVelo(axis prm_axis, ang_velo prm_ang_veloRot) {
    if (prm_ang_veloRot > _ang_veloTopFace[prm_axis]) {
        _ang_veloFace[prm_axis] = _ang_veloTopFace[prm_axis];
    } else if (prm_ang_veloRot < _ang_veloBottomFace[prm_axis]) {
        _ang_veloFace[prm_axis] = _ang_veloBottomFace[prm_axis];
    } else {
        _ang_veloFace[prm_axis] = prm_ang_veloRot;
    }
}

void GgafDxKurokoA::forceFaceAngVeloRange(axis prm_axis,
                                               ang_velo prm_ang_veloRot01,
                                               ang_velo prm_ang_veloRot02) {
    if (prm_ang_veloRot01 < prm_ang_veloRot02) {
        _ang_veloTopFace[prm_axis] = prm_ang_veloRot02;
        _ang_veloBottomFace[prm_axis] = prm_ang_veloRot01;
    } else {
        _ang_veloTopFace[prm_axis] = prm_ang_veloRot01;
        _ang_veloBottomFace[prm_axis] = prm_ang_veloRot02;
    }
    setFaceAngVelo(prm_axis, _ang_veloFace[prm_axis]); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKurokoA::setFaceAngAcce(axis prm_axis, ang_acce prm_ang_acceRot) {
    _ang_acceFace[prm_axis] = prm_ang_acceRot;
}

void GgafDxKurokoA::setStopTarget_FaceAngV(axis prm_axis,
                                                  coord prm_tX,
                                                  coord prm_tY,
                                                  int prm_way_allow,
                                                  ang_velo prm_ang_veloAllowRyMv) {
    setStopTarget_FaceAng(
      prm_axis,
      GgafDxUtil::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
      prm_way_allow,
      prm_ang_veloAllowRyMv
    );
}

void GgafDxKurokoA::setStopTarget_FaceAng(axis prm_axis,
                                                 angle prm_angTargetRot,
                                                 int prm_way_allow,
                                                 ang_velo prm_ang_veloAllow) {
    _face_ang_targeting_flg[prm_axis] = true;
    _face_ang_targeting_stop_flg[prm_axis] = true;
    _angTargetFace[prm_axis] = GgafDxUtil::simplifyAng(prm_angTargetRot);
    _face_ang_target_allow_way[prm_axis] = prm_way_allow;
    _face_ang_target_allow_velo[prm_axis] = prm_ang_veloAllow;
}

angle GgafDxKurokoA::getFaceAngDistance(axis prm_axis, coord prm_tX, coord prm_tY, int prm_way) {
    return getFaceAngDistance(prm_axis, GgafDxUtil::getAngle2D(prm_tX - (_pActor->_X), prm_tY
            - (_pActor->_Y)), prm_way);
}

angle GgafDxKurokoA::getFaceAngDistance(axis prm_axis, angle prm_angTargetRot, int prm_way) {
    angle _angTargetRot;
    _angTargetRot = GgafDxUtil::simplifyAng(prm_angTargetRot);
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
            } else if (_angFace[prm_axis] - D180ANG < _angTargetRot && _angTargetRot
                    < _angFace[prm_axis]) {
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
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���݂̐��ʕ��p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() ���̂�����p�̋��������߂�܂���(2)�B_pActor="<<_pActor->getName());
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

void GgafDxKurokoA::setMvAcceToStop(coord prm_target_distance) {
    // a = -(Vo^2) / 2D
    _accMv  =  -(1.0*_veloMv*_veloMv) / (2.0*prm_target_distance);
    if (_accMv < 0) {
        _accMv += 1;
    } else {
        _accMv -= 1;
    }
    //(frame)((2.0*prm_target_distance) / _veloMv); //�g�p�t���[����
}
void GgafDxKurokoA::setMvAcceBy_tv(int prm_target_frames, velo prm_target_velo) {
    //a = (Vt-Vo) / Te
    _accMv = (prm_target_velo - _veloMv) / (1.0f*prm_target_frames);
}
void GgafDxKurokoA::setMvAcceBy_Dv(coord prm_target_distance, velo prm_target_velo) {
    // a = (Vt^2 - Vo^2) / 2D
    _accMv =  ((1.0f*prm_target_velo*prm_target_velo) - (1.0f*_veloMv*_veloMv)) / (2.0f*prm_target_distance);
    if (_accMv < 0) {
        _accMv += 1;
    } else {
        _accMv -= 1;
    }
    //(frame)((1.0*prm_target_velo - _veloMv) / _accMv); //�g�p�t���[����

    // �y�⑫�z
    // Vo <= 0  ����  Vt <= 0 �ꍇ�A���邢��  Vo >= 0  ����  Vt >= 0  �ꍇ�́AD(�ڕW����)����L���Ŗ��Ȃ��B
    // �ł�
    // Vo < 0   ����  Vt > 0  �ꍇ�A���邢��  Vo > 0   ����  Vt < 0   �ꍇ�́A�ǂ��Ȃ邩�H
    //
    //    ���x(v)
    //     ^        a:�����x
    //     |        D:�ړ������i�ڕW���B���x�ɒB����܂łɔ�₷�����j
    //     |       Vo:�����_�̑��x
    //     |       Vt:�ڕW���B���x
    //     |       Te:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
    //  Vo |
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
    //    D1 = (1/2) Vo Tc
    //    D2 = (1/2) -Vt (Te - Tc)
    //    D = D1 - D2 ���
    //    D = (1/2) Vo Tc -  { (1/2) -Vt (Te - Tc) }
    //      = (Vo Tc + Vt Te - Vt Tc) / 2    �E�E�E�@
    //
    //    ���� v = a t + Vo �ɂ����� v = 0 �� t = Tc �ł���̂�
    //    0 = a Tc + Vo
    //    Tc = -Vo / a
    //    ����� �@ �֑��
    //    D = (Vo (-Vo / a) + Vt Te - Vt (-Vo / a)) / 2 �E�E�E�A
    //    �܂� a = (Vt - Vo) / Te �ł���̂�
    //    Te = (Vt - Vo) / a ����� �A �֑��
    //    �����
    //    D = (Vo (-Vo / a) + Vt ((Vt - Vo) / a) - Vt (-Vo / a)) / 2
    //
    //    a �ɂ��ĉ���
    //
    //    D = ( -(Vo^2) / a  + (Vt (Vt - Vo)) / a + (Vt Vo) / a) / 2
    //    a D = { -(Vo^2) + (Vt (Vt - Vo)) + (Vt Vo) } / 2
    //    a = { -(Vo^2) + (Vt (Vt - Vo)) + (Vt Vo) } / 2D
    //    a = (-(Vo^2) + Vt^2 - Vt Vo + Vt Vo) / 2D
    //    a = (Vt^2 - Vo^2) / 2D
    //
    //    ���� a = (Vt^2 - Vo^2) / 2D �ƂȂ�̂�
    //    Vo <= 0  ����  Vt <= 0 �ꍇ�A���邢��  Vo >= 0  ����  Vt >= 0  �ꍇ�Ɠ����ł���
}

void GgafDxKurokoA::execSmoothMvVeloSequence(velo prm_end_velo, coord prm_target_distance,
                                                  int prm_target_frames, float prm_p1, float prm_p2,
                                                  bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_mv_velo_seq_p2 = (int)(prm_target_frames*prm_p2);
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_target_distance = prm_target_distance;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_target_frames = prm_target_frames;
    _smooth_mv_velo_seq_frame_of_spent = 0;
    _smooth_mv_velo_seq_progress = 0;

    //���g�b�v�X�s�[�h(Vt) ���v�Z��
    //
    //    ���x(v)
    //     ^
    //     |                          D:�ڕW�ړ�����
    //     |                         Vo:�����_�̑��x
    //     |                         Vt:�g�b�v�X�s�[�h
    //     |                         Ve:�ŏI���x
    //   Vt|....�Q�Q�Q�Q�Q           Te:�ڕW���ԁi�t���[�����j
    //     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��
    //   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��
    //     | /  :         :    |        (0.0 < p1 < p2 < 1.0)
    //     |/   :         :    |
    //   Vo|    :    D    :    |
    //     |    :         :    |
    //   --+----+---------+----+-----> ����(t:�t���[��)
    //   0 |  p1*Te     p2*Te  Te
    //
    // �ړ�����D�́A���̑�`�{�����̒����`�{�E�̑�` �̖ʐςł���A
    // D = (1/2) (Vo + Vt) p1 Te + Vt (p2-p1)Te  +  (1/2) (Ve + Vt) (1-p2)Te
    // �����Vt�ɂ��ĉ���
    // Vt = ( 2D - p1 Te Vo + (p2 - 1) Te Ve ) / ( (p2 - p1 + 1) Te )
    _smooth_mv_velo_seq_top_velo =
         ((2.0*prm_target_distance) - (prm_p1*prm_target_frames*_veloMv) + ((prm_p2-1.0)*prm_target_frames*prm_end_velo))
         / ((prm_p2-prm_p1+1.0)*prm_target_frames);

}

void GgafDxKurokoA::execSmoothMvVeloSequenceD(velo prm_top_velo, velo prm_end_velo,
                                                   coord prm_target_distance, float prm_p1, float prm_p2,
                                                   bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_mv_velo_seq_top_velo = prm_top_velo;
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_target_distance = prm_target_distance;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_target_frames = -1; //�ڕW���Ԃ͎g��Ȃ��ꍇ�͕���ݒ肵�Ă���(��������Ŏg�p)
    _smooth_mv_velo_seq_frame_of_spent = 0;
    _smooth_mv_velo_seq_p1 = (int)(prm_target_distance*prm_p1);
    _smooth_mv_velo_seq_p2 = (int)(prm_target_distance*prm_p2);
    _smooth_mv_velo_seq_progress = 0;
}


void GgafDxKurokoA::execSmoothMvVeloSequenceT(velo prm_top_velo, velo prm_end_velo,
                                                   int prm_target_frames, float prm_p1, float prm_p2,
                                                   bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_mv_velo_seq_top_velo = prm_top_velo;
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_target_distance = 0;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_target_frames = prm_target_frames;
    _smooth_mv_velo_seq_frame_of_spent = 0;
    _smooth_mv_velo_seq_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_mv_velo_seq_p2 = (int)(prm_target_frames*prm_p1);
    _smooth_mv_velo_seq_progress = 0;
}



//void GgafDxKurokoA::execSmoothMvVeloSequence4(velo prm_end_velo, coord prm_target_distance, int prm_target_frames,
//                                                      bool prm_endacc_flg) {
//    _smooth_mv_velo_seq_flg = true;
//    _smooth_mv_velo_seq_p1 = (int)(prm_target_distance*1.0 / 4.0);
//    _smooth_mv_velo_seq_p2 = (int)(prm_target_distance*3.0 / 4.0);
//    _smooth_mv_velo_seq_end_velo = prm_end_velo;
//    _smooth_mv_velo_seq_target_distance = prm_target_distance;
//    _smooth_mv_velo_seq_mv_distance = 0;
//    _smooth_mv_velo_seq_target_frames = -1; //�ڕW���Ԃ͎g��Ȃ��ꍇ�͕���ݒ肵�Ă���(��������Ŏg�p)
//    _smooth_mv_velo_seq_frame_of_spent = 0;
//    _smooth_mv_velo_seq_progress = 0;
//
//    //    ���x
//    //     ^
//    //     |                       D:�ړ�����
//    //     |                      Vo:�����_�̑��x
//    //     |                      Vt:����1/4 �` 3/4 �̑��x
//    //     |                      Ve:�ŏI�ڕW���B���x
//    //   Vt|....�Q�Q�Q�Q            Te:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
//    //     |   /|      |�_
//    //   Ve|../.|......|..�_
//    //     | /  |      |   |
//    //     |/   |      |   |
//    //   Vo| 1/4|  2/4 |1/4|
//    //     |  D |   D  | D |
//    //   --+----+------+---+-----> ����(�t���[��)
//    //   0 |   tp1    tp2  Te
//
//    // ������ �u��`�{�����`�{��`�v �̖ʐρB�䂦��
//    // (1/4)D = (1/2) (Vo + Vt) tp1           �c�@ ��`
//    // (2/4)D = Vt (tp2 - tp1)                �c�A �����`
//    // (1/4)D = (1/2) (Ve + Vt) (Te - tp2)     �c�B ��`
//
//
//    // (1/4)D = Vt tp1 -  (1/2) tp1 (Vt - Vo)
//    // �܂��A������ �u�S�̂̒����` �] �O�p�`�����Q�v �̖ʐςł�����B�䂦��
//    // D = Te Vt - (1/2) tp1 (Vt - Vo) - (1/2) (Te - tp2) (Vt - Ve) �c�C
//
//    //�@���
//    //tp1 = (D / 2 (Vo + Vt) )        �c�D
//    //�B���
//    //(Te - tp2) = (D / 2 (Ve + Vt) )  �c�E
//    //�D�E���C�֑��
//    //D = Te Vt - D(Vt - Vo) / 4 (Vo + Vt) - D(Vt - Ve) / 4 (Ve + Vt)
//    //�����Vt�ɂ��ĉ�����
//
//    //    Vt =
//    //    (sqrt((-9*Vo^2+9*Ve*Vo-9*Ve^2)*D^4-(4*Te*Vo^3-6*Te*Ve*Vo^2-6*Te*Ve^2*Vo+4*Te*Ve^3)*D^3+(-4*Te^2*Vo^4+8*Te^2*Ve*Vo^3-12*Te^2*Ve^2*Vo^2+8*Te^2*Ve^3*Vo-4*Te^2*Ve^4)*D^2-4*Te^4*Ve^2*Vo^4+8*Te^4*Ve^3*Vo^3-4*Te^4*Ve^4*Vo^2)/(4*3^(3/2)*Te^2)-
//    //    (Te^3*(8*Vo^3-12*Ve*Vo^2-12*Ve^2*Vo+8*Ve^3)-27*D^3)/(216*Te^3))^(1/3)+(9*D^2+Te^2*(4*Vo^2-4*Ve*Vo+4*Ve^2))/(36*Te^2*(
//    //    sqrt((-9*Vo^2+9*Ve*Vo-9*Ve^2)*D^4-(4*Te*Vo^3-6*Te*Ve*Vo^2-6*Te*Ve^2*Vo+4*Te*Ve^3)*D^3+(-4*Te^2*Vo^4+8*Te^2*Ve*Vo^3-12*Te^2*Ve^2*Vo^2+8*Te^2*Ve^3*Vo-4*Te^2*Ve^4)*D^2-4*Te^4*Ve^2*Vo^4+8*Te^4*Ve^3*Vo^3-4*Te^4*Ve^4*Vo^2)/(4*3^(3/2)*Te^2)-
//    //    (Te^3*(8*Vo^3-12*Ve*Vo^2-12*Ve^2*Vo+8*Ve^3)-27*D^3)/(216*Te^3))^(1/3))+(3*D-Te*(2*Vo+2*Ve))/(6*Te)
//    //�Ȃ񂶂Ⴑ��E�E�E
//
//
//
//
//
//    _smooth_mv_velo_seq_top_velo = (8.0*prm_target_distance/prm_target_frames - _veloMv - prm_end_velo) / 6.0;
//}



bool GgafDxKurokoA::isMoveingSmooth() {
    return _smooth_mv_velo_seq_flg;
}


void GgafDxKurokoA::setRzMvAng(coord prm_tX, coord prm_tY) {
    setRzMvAng(GgafDxUtil::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDxKurokoA::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _angRzMv) {
        _angRzMv = GgafDxUtil::simplifyAng(prm_ang);
        GgafDxUtil::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDxKurokoA::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_ang_veloRzBottomMv > prm_angDistance) {
        angOffset = _ang_veloRzBottomMv;
    } else if (prm_angDistance > _ang_veloRzTopMv) {
        angOffset = _ang_veloRzTopMv;
    }
    setRzMvAng(_angRzMv + angOffset);
}

void GgafDxKurokoA::setRzMvAngVelo(ang_velo prm_ang_veloRzMv) {
    if (prm_ang_veloRzMv > _ang_veloRzTopMv) {
        _ang_veloRzMv = _ang_veloRzTopMv;
    } else if (prm_ang_veloRzMv < _ang_veloRzBottomMv) {
        _ang_veloRzMv = _ang_veloRzBottomMv;
    } else {
        _ang_veloRzMv = prm_ang_veloRzMv;
    }
}

void GgafDxKurokoA::setRzMvAngAcce(ang_acce prm_ang_acceRzMv) {
    _ang_acceRzMv = prm_ang_acceRzMv;
}

void GgafDxKurokoA::forceRzMvAngVeloRange(ang_velo prm_ang_veloRzMv01,
                                                 ang_velo prm_ang_veloRzMv02) {
    if (prm_ang_veloRzMv01 < prm_ang_veloRzMv02) {
        _ang_veloRzTopMv = prm_ang_veloRzMv02;
        _ang_veloRzBottomMv = prm_ang_veloRzMv01;
    } else {
        _ang_veloRzTopMv = prm_ang_veloRzMv01;
        _ang_veloRzBottomMv = prm_ang_veloRzMv02;
    }
    setRzMvAngVelo(_ang_veloRzMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKurokoA::setStopTarget_RzMvAng(angle prm_angTargetRzMv,
                                                 int prm_way_allow,
                                                 ang_velo prm_ang_veloAllowRyMv) {
    _mv_ang_rz_target_flg = true;
    _mv_ang_rz_target_stop_flg = true;
    _angTargetRzMv = GgafDxUtil::simplifyAng(prm_angTargetRzMv);
    _mv_ang_rz_target_allow_way = prm_way_allow;
    _mv_ang_rz_target_allow_velo = prm_ang_veloAllowRyMv;
}

void GgafDxKurokoA::setStopTarget_RzMvAngV(coord prm_tX,
                                                  coord prm_tY,
                                                  int prm_way_allow,
                                                  ang_velo prm_ang_veloAllowRyMv) {
    setStopTarget_RzMvAng(GgafDxUtil::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDxKurokoA::getRzMvAngDistance(coord prm_tX, coord prm_tY, int prm_way) {
    return getRzMvAngDistance(GgafDxUtil::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDxKurokoA::getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way) {
    angle angTargetRzMv = GgafDxUtil::simplifyAng(prm_angTargetRzMv);
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
                throwGgafCriticalException("GgafDxKurokoA::behave() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::behave() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
    throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() ���̂�����p�̋��������߂�܂���(1)�B_pActor="<<_pActor->getName());
}


void GgafDxKurokoA::setRyMvAng(coord prm_tX, coord prm_tY) {
    setRyMvAng(GgafDxUtil::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDxKurokoA::setRyMvAng(angle prm_ang) {
    if (prm_ang != _angRyMv) {
        _angRyMv = GgafDxUtil::simplifyAng(prm_ang);
        GgafDxUtil::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKurokoA::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_ang_veloRyBottomMv > prm_angDistance) {
        angOffset = _ang_veloRyBottomMv;
    } else if (prm_angDistance > _ang_veloRyTopMv) {
        angOffset = _ang_veloRyTopMv;
    }
    setRyMvAng(_angRyMv + angOffset);
}

void GgafDxKurokoA::setRyMvAngVelo(ang_velo prm_ang_veloRyMv) {
    if (prm_ang_veloRyMv > _ang_veloRyTopMv) {
        _ang_veloRyMv = _ang_veloRyTopMv;
    } else if (prm_ang_veloRyMv < _ang_veloRyBottomMv) {
        _ang_veloRyMv = _ang_veloRyBottomMv;
    } else {
        _ang_veloRyMv = prm_ang_veloRyMv;
    }
}

void GgafDxKurokoA::setRyMvAngAcce(ang_acce prm_ang_acceRyMv) {
    _ang_acceRyMv = prm_ang_acceRyMv;
}

void GgafDxKurokoA::forceRyMvAngVeloRange(ang_velo prm_ang_veloRyMv01,
                                               ang_velo prm_ang_veloRyMv02) {
    if (prm_ang_veloRyMv01 < prm_ang_veloRyMv02) {
        _ang_veloRyTopMv = prm_ang_veloRyMv02;
        _ang_veloRyBottomMv = prm_ang_veloRyMv01;
    } else {
        _ang_veloRyTopMv = prm_ang_veloRyMv01;
        _ang_veloRyBottomMv = prm_ang_veloRyMv02;
    }
    setRyMvAngVelo(_ang_veloRyMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxKurokoA::setStopTarget_RyMvAng(angle prm_angTargetRyMv,
                                          int prm_way_allow,
                                          ang_velo prm_ang_veloAllowRyMv) {
    _mv_ang_ry_target_flg = true;
    _mv_ang_ry_target_stop_flg = true;
    _angTargetRyMv = GgafDxUtil::simplifyAng(prm_angTargetRyMv);
    _mv_ang_ry_target_allow_way = prm_way_allow;
    _mv_ang_ry_target_allow_velo = prm_ang_veloAllowRyMv;
}

void GgafDxKurokoA::setStopTarget_RyMvAngV(coord prm_tX,
                                                  coord prm_tY,
                                                  int prm_way_allow,
                                                  ang_velo prm_ang_veloAllowRyMv) {
    setStopTarget_RyMvAng(GgafDxUtil::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDxKurokoA::getRyMvAngDistance(coord prm_tX, coord prm_tY, int prm_way) {
    return getRyMvAngDistance(GgafDxUtil::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDxKurokoA::getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way) {
    angle angTargetRyMv;
    angTargetRyMv = GgafDxUtil::simplifyAng(prm_angTargetRyMv);
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
                throwGgafCriticalException("GgafDxKurokoA::behave() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::behave() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
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
            throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
    throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() ���̂�����p�̋��������߂�܂���(1)�B_pActor="<<_pActor->getName());
}

void GgafDxKurokoA::getRzRyMvAngDistance(int prm_way,
                                                angle prm_target_angRz, angle prm_target_angRy,
                                                angle& out_d_angRz, angle& out_d_angRy,
                                                angle& out_target_angRz, angle& out_target_angRy) {
//_TRACE_("getRzRyMvAngDistance ---->");
//_TRACE_("this: angMvRz="<<_angRzMv<<" _angRyMv="<<_angRyMv);
//_TRACE_("prm_target_angRz="<<prm_target_angRz<<" prm_target_angRy="<<prm_target_angRy);
    angle target_angRz = prm_target_angRz;
    angle target_angRy = prm_target_angRy;
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        //�ڕW�ɓ��B���邽�߂ɂ́A��������ɂQ�p�^�[������B
        //���ꂼ�ꋅ�ʏ�̂Q�_�̋������ȈՋߎ��l�i���x�D��̂��߁j�Ŕ�r���A�߂��Ǝv����ق����̗p����B

        //_TRACE_("1 target_angRz="<<target_angRz<<" target_angRy="<<target_angRy);
        angle d1_angRz = getRzMvAngDistance(target_angRz, TURN_CLOSE_TO); //Rz�̍�
        angle d1_angRy = getRyMvAngDistance(target_angRy, TURN_CLOSE_TO);
        //_TRACE_("1 d1_angRz="<<d1_angRz<<" d1_angRy="<<d1_angRy);
        angle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
        //_TRACE_("1  d1="<<((float)d1));

        GgafDxUtil::anotherRzRy(target_angRz, target_angRy);
        //_TRACE_("2 anotherRzRy target_angRz="<<target_angRz<<" target_angRy="<<target_angRy);
        angle d2_angRz = getRzMvAngDistance(target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(target_angRy, TURN_CLOSE_TO);
        //_TRACE_("2 d2_angRz="<<d2_angRz<<" d2_angRy="<<d2_angRy);
        angle d2 = abs(d2_angRz) > abs(d2_angRy) ? abs(d2_angRz) : abs(d2_angRy);
        //_TRACE_("2  d2="<<((float)d2));
        if (d1 <= d2) {
            //_TRACE_("d1 <= d2 d1���̗p����܂���");
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
            out_target_angRz = prm_target_angRz;
            out_target_angRy = prm_target_angRy;
        } else {
            //_TRACE_("d1 > d2  d2���̗p����܂���");
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
            out_target_angRz = target_angRz;
            out_target_angRy = target_angRy;
        }
        //_TRACE_("<--- getRzRyMvAngDistance");
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        angle d1_angRz = getRzMvAngDistance(target_angRz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getRyMvAngDistance(target_angRy, TURN_ANTICLOSE_TO);
        angle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
        GgafDxUtil::anotherRzRy(target_angRz, target_angRy);
        angle d2_angRz = getRzMvAngDistance(target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = abs(d2_angRz) > abs(d2_angRy) ? abs(d2_angRz) : abs(d2_angRy);
        if (d1 >= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
            out_target_angRz = prm_target_angRz;
            out_target_angRy = prm_target_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
            out_target_angRz = target_angRz;
            out_target_angRy = target_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        out_d_angRz = getRzMvAngDistance(target_angRz, TURN_COUNTERCLOCKWISE);
        out_d_angRy = getRyMvAngDistance(target_angRy, TURN_COUNTERCLOCKWISE);
        out_target_angRz = target_angRz;
        out_target_angRy = target_angRy;
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        out_d_angRz = getRzMvAngDistance(target_angRz, TURN_CLOCKWISE);
        out_d_angRy = getRyMvAngDistance(target_angRy, TURN_CLOCKWISE);
        out_target_angRz = target_angRz;
        out_target_angRy = target_angRy;
    } else {
        //��������
        throwGgafCriticalException("GgafDxKurokoA::getRzRyMvAngDistance() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDxKurokoA::getRzRyFaceAngDistance(int prm_way,
                                                  angle prm_target_angRz, angle prm_target_angRy,
                                                  angle& out_d_angRz, angle& out_d_angRy,
                                                  angle& out_target_angRz, angle& out_target_angRy) {
    angle target_angRz = prm_target_angRz;
    angle target_angRy = prm_target_angRy;
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        angle d1_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOSE_TO);
        angle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
        GgafDxUtil::anotherRzRy(target_angRz, target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOSE_TO) * ((GgafDxUtil::COS[GgafDxUtil::simplifyAng(target_angRz*2)/SANG_RATE]/2.0) + 0.5);
        angle d2 = abs(d2_angRz) > abs(d2_angRy) ? abs(d2_angRz) : abs(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
            out_target_angRz = prm_target_angRz;
            out_target_angRy = prm_target_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
            out_target_angRz = target_angRz;
            out_target_angRy = target_angRy;
        }

    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        angle d1_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_ANTICLOSE_TO);
        angle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
        GgafDxUtil::anotherRzRy(target_angRz, target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = abs(d2_angRz) > abs(d2_angRy) ? abs(d2_angRz) : abs(d2_angRy);
        if (d1 >= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
            out_target_angRz = prm_target_angRz;
            out_target_angRy = prm_target_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
            out_target_angRz = target_angRz;
            out_target_angRy = target_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        out_d_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_COUNTERCLOCKWISE);
        out_d_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_COUNTERCLOCKWISE);
        out_target_angRz = target_angRz;
        out_target_angRy = target_angRy;
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        out_d_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOCKWISE);
        out_d_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOCKWISE);
        out_target_angRz = target_angRz;
        out_target_angRy = target_angRy;
    } else {
        //��������
        throwGgafCriticalException("GgafDxKurokoA::getRzRyMvAngDistance() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDxKurokoA::setRzRyMvAng(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMv || prm_angRy !=_angRyMv ) {
        _angRzMv = GgafDxUtil::simplifyAng(prm_angRz);
        _angRyMv = GgafDxUtil::simplifyAng(prm_angRy);
        GgafDxUtil::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKurokoA::setRzRyMvAng_by_RyRz(angle prm_angRyRz_Ry, angle prm_angRyRz_Rz) {
    angle RyRz_Ry = GgafDxUtil::simplifyAng(prm_angRyRz_Ry);
    angle RyRz_Rz = GgafDxUtil::simplifyAng(prm_angRyRz_Rz);
    float out_vY, out_vZ;
    GgafDxUtil::getNormalizeVectorZY(RyRz_Ry, D360ANG-RyRz_Rz, _vX, out_vY, out_vZ);
    _vY = -1.0f*out_vZ;
    _vZ = out_vY;
    GgafDxUtil::getRzRyAng(_vX, _vZ, _vY, _angRzMv, _angRyMv);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKurokoA::setMvAng(GgafDxGeometricActor* prm_pActor_Target) {
    setMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}
void GgafDxKurokoA::setMvAng(coord prm_tX, coord prm_tY) {
    setMvAng(prm_tX, prm_tY, _pActor->_Z);
}
void GgafDxKurokoA::setMvAng(coord prm_tX, coord prm_tY, coord prm_tZ) {
    GgafDxUtil::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _vX,
                   _vY,
                   _vZ,
                   _angRzMv,
                   _angRyMv
                 );
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKurokoA::setStopTarget_RzRyMvAng(GgafDxGeometricActor* prm_pActor_Target) {
    setStopTarget_RzRyMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDxKurokoA::setStopTarget_RzRyMvAng(coord prm_tX, coord prm_tY, coord prm_tZ) {
    angle angRz_Target;
    angle angRy_Target;

    GgafDxUtil::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _dummy1,
                   _dummy2,
                   _dummy3,
                   angRz_Target,
                   angRy_Target
                 );
    setStopTarget_RzMvAng(angRz_Target);
    setStopTarget_RyMvAng(angRy_Target);
}




void GgafDxKurokoA::execTurnFaceAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                        int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    if (prm_optimize_ang) {
        getRzRyFaceAngDistance(prm_way,
                               prm_angRz_Target, prm_angRy_Target,
                               out_d_angRz, out_d_angRy,
                               prm_angRz_Target, prm_angRy_Target);
    } else {
        out_d_angRz = getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way);
        out_d_angRy = getFaceAngDistance(AXIS_Y, prm_angRy_Target, prm_way);
    }

    if (out_d_angRz > 0) {
        setFaceAngVelo(AXIS_Z, prm_angVelo);
        setFaceAngAcce(AXIS_Z, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Z, -prm_angVelo);
        setFaceAngAcce(AXIS_Z, -prm_angAcce);
    }
    if (out_d_angRy > 0) {
        setFaceAngVelo(AXIS_Y, prm_angVelo);
        setFaceAngAcce(AXIS_Y, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Y, -prm_angVelo);
        setFaceAngAcce(AXIS_Y, -prm_angAcce);
    }

    setStopTarget_FaceAng(AXIS_Z, prm_angRz_Target);
    setStopTarget_FaceAng(AXIS_Y, prm_angRy_Target);
}

void GgafDxKurokoA::execTurnFaceAngSequence(coord prm_tX, coord prm_tY, coord prm_tZ,
                                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                        int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDxUtil::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    execTurnFaceAngSequence(out_angRz_Target, out_angRy_Target,
                                 prm_angVelo, prm_angAcce,
                                 prm_way, prm_optimize_ang);
}

void GgafDxKurokoA::execTurnRzFaceAngSequence(angle prm_angRz_Target,
                                                          ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                          int prm_way) {
    if (getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Z, prm_angVelo);
        setFaceAngAcce(AXIS_Z, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Z, -prm_angVelo);
        setFaceAngAcce(AXIS_Z, -prm_angAcce);
    }
    setStopTarget_FaceAng(AXIS_Z, prm_angRz_Target);

}

void GgafDxKurokoA::execTurnRyFaceAngSequence(angle prm_angRy_Target,
                                                          ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                          int prm_way) {
    if (getFaceAngDistance(AXIS_Y, prm_angRy_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Y, prm_angVelo);
        setFaceAngAcce(AXIS_Y, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Y, -prm_angVelo);
        setFaceAngAcce(AXIS_Y, -prm_angAcce);
    }
    setStopTarget_FaceAng(AXIS_Y, prm_angRy_Target);
}

void GgafDxKurokoA::execTurnRxSpinAngSequence(angle prm_angRx_Target,
                                                            ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                            int prm_way) {
    if (getFaceAngDistance(AXIS_X, prm_angRx_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_X, prm_angVelo);
        setFaceAngAcce(AXIS_X, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_X, -prm_angVelo);
        setFaceAngAcce(AXIS_X, -prm_angAcce);
    }
    setStopTarget_FaceAng(AXIS_X, prm_angRx_Target);
}

void GgafDxKurokoA::execTurnMvAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                      ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                      int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    angle out_target_angRz;
    angle out_target_angRy;
    if (prm_optimize_ang) {
        getRzRyMvAngDistance(prm_way,
                             prm_angRz_Target, prm_angRy_Target,
                             out_d_angRz, out_d_angRy,
                             out_target_angRz, out_target_angRy);
    } else {
        out_d_angRz = getRzMvAngDistance(prm_angRz_Target, prm_way);
        out_d_angRy = getRyMvAngDistance(prm_angRy_Target, prm_way);
        out_target_angRz = prm_angRz_Target;
        out_target_angRy = prm_angRy_Target;
    }
    if (out_d_angRz > 0) {
        setRzMvAngVelo(prm_angVelo);
        setRzMvAngAcce(prm_angAcce);
    } else {
        setRzMvAngVelo(-prm_angVelo);
        setRzMvAngAcce(-prm_angAcce);
    }
    if (out_d_angRy > 0) {
        setRyMvAngVelo(prm_angVelo);
        setRyMvAngAcce(prm_angAcce);
    } else {
        setRyMvAngVelo(-prm_angVelo);
        setRyMvAngAcce(-prm_angAcce);
    }

    setStopTarget_RzMvAng(out_target_angRz);
    setStopTarget_RyMvAng(out_target_angRy);

}


void GgafDxKurokoA::execTurnMvAngSequence(coord prm_tX, coord prm_tY, coord prm_tZ,
                                                      ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                      int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDxUtil::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    execTurnMvAngSequence(out_angRz_Target, out_angRy_Target,
                               prm_angVelo, prm_angAcce,
                               prm_way, prm_optimize_ang);
}


void GgafDxKurokoA::execTurnRzMvAngSequence(angle prm_angRz_Target,
                                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                        int prm_way) {
    if (getRzMvAngDistance(prm_angRz_Target, prm_way) > 0) {
        setRzMvAngVelo(prm_angVelo);
        setRzMvAngAcce(prm_angAcce);
    } else {
        setRzMvAngVelo(-prm_angVelo);
        setRzMvAngAcce(-prm_angAcce);
    }
    setStopTarget_RzMvAng(prm_angRz_Target);

}

void GgafDxKurokoA::execTurnRyMvAngSequence(angle prm_angRy_Target,
                                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
                                                        int prm_way) {
    if (getRyMvAngDistance(prm_angRy_Target, prm_way) > 0) {
        setRyMvAngVelo(prm_angVelo);
        setRyMvAngAcce(prm_angAcce);
    } else {
        setRyMvAngVelo(-prm_angVelo);
        setRyMvAngAcce(-prm_angAcce);
    }
    setStopTarget_RyMvAng(prm_angRy_Target);
}




void GgafDxKurokoA::takeoverMvFrom(GgafDxKurokoA* prm_pKurokoA) {
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

void GgafDxKurokoA::resetMv() {
    //�L�����̈ړ����p�P�ʃx�N�g��
    _vX = _vY = _vZ = 0.0f;
    //�ړ����p��Z����]
    _angRzMv = 0;
    //�ړ����p��Y����]
    _angRyMv = 0;
    //�ړ����x
    _veloMv = 0;
    //�ړ����x��� = 256 px/fream
    _veloTopMv = 256 * LEN_UNIT; //_veloMv �� 256000(=256px) ������ړ��ʂł����Ă��A�����I�ɍ��W������ 256px �ɗ}������B
    //�ړ����x���� = 0   px/fream
    _veloBottomMv = -256 * LEN_UNIT; //_veloMv �� -256000(-256px) �������ړ��ʂ������Ă��A�����I�ɍ��W������ -256000px �ɗ}������B
    //�ړ������x�i�ړ����x�̑����j = 0 px/fream^2
    _accMv = 0; //_veloMv �̑����B�f�t�H���g�͉�������

    //_jerkMv = 0;
    //�ړ����p�iZ����]�j�̊p���x = 0 angle/fream
    _ang_veloRzMv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iZ����]�j�̊p���x��� = +360,000 angle/fream
    _ang_veloRzTopMv = D360ANG; //_ang_veloRzMv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p���x���� = -360,000 angle/fream
    _ang_veloRzBottomMv = D360ANG * -1; //_ang_veloRzMv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p�����x = 0 angle/fream^2
    _ang_acceRzMv = 0; //_ang_veloRzMv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _ang_jerkRzMv = 0;


}

GgafDxKurokoA::~GgafDxKurokoA() {
}
