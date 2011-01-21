#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

// �y�����z�{�N���X�̍l�����ƒP��̕\��
//
// ���Q��ނ̕�����
// �u�����v�ɂ͂Q��ވӖ�������A�u�ړ����p�i�����j�v�Ɓu����]���p�i�����j�v�Ƃ���B
// �u�ړ����p�i�����j�v�̓L�����̐i�s�����݂̂�\������B����́u�ړ����x�v�Ɣ����āA�L�����͍��W�����ړ����邱�ƂƂ���B
// �u����]���p�v�̓L�����̌����݂̂�\����B
// �L�����N�^����ʂ̏㕔���牺���ֈړ����Ă��A�L�����N�^�͉��������Ƃ͌��炸���@�Ɍ����Ăق����ꍇ������B
// �E�ɃL�������������āA���Ɉړ������������Ƃ�����B���ꂼ��ݒ肪�K�v�B
// �u����]���p�i�����j�v�͈ȉ��B
//
// ���ړ����p:AngMv��
// �L�������i�ޕ����A�܂�ړ����p�̕����́A���_����P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g�� (_vX, _vY, _vZ) �ŕ\�����@�ƁA
// �Q�̎���]�A���O���l (_angRzMv, _angRyMv) �ŕ\�����@�̂Q��ޗp�ӂ����B
// �P�Ɂu�ړ����p�v�ƌĂԏꍇ�́A���Ԉ�ʂ͈ړ������̕����x�N�g���iXYZ�̒l�j�̂��Ƃ��w���B
// ���������̃N���X�ł́A�Q�̃A���O���l�̃Z�b�g�̕�����Ɉړ����p�ƌĂ�ł���B
// _angRzMv �� Z����]�p�A _angRyMv �� Y����]�p ���Ӗ����Ă���B�����Ƃ�0�x���A�����x�N�g��(1, 0, 0) �̕����ƒ�`����B
// ����͕����x�N�g�����A�ܓx�ƌo�x�A�i�p�ƃA�W�}�X�j�̊֌W�ɑΉ������悤�Ƃ����݌v�B
// Y����]�p���o�x �͏�ɐ��藧���AZ����]�p���ܓx �́AZ����]�p �� Y����]�p�̏��Ԃł���ꍇ�Ɍ��萬�藧�B
// �����łQ�̎���]�A���O���l�ŕ\���ړ����p�́A�K�� Z����] �� Y����]�̏��Ԃł���ƒ�`����B
// �����������ł͊ȗ����āA�ܓx�o�x�́A�u�ܓx�v���uZ����]�p�v �ƕ\�����܂��B
// �������ʂɕ\���������ꍇ�́A���ꂼ��u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�Ə������Ƃɂ���B
// �{�N���X�ŒP�Ɂu�ړ����p�v�Ə����Ă���ꍇ�́A2�̃A���O���l���w���Ă��邱�Ƃ������B
// ���āA�����𓥂܂��āu�ړ����p�iZ���j�v�Ƃ������t�̌�b�́A�܂�肭�ǂ���C�ɐ�������ƁA
// �u���_����P�ʋ��\�ʂɐL�т�����x�N�g�����AXYZ���W�ł͖������\�ʂɈܓx�o�x�̍��W���������Q�̐��l�ŕ\������Ƃ��āA
//  �ܓx��Z����]�p�A�o�x��Y����]�p �Ƃ݂Ȃ����i��Z����] �� Y����]�̏��ԁj�ꍇ��Z����]�p�����݂̂̃A���O���l�v
// �Ƃ������ƂɂȂ�B
// �uRz�v�Ƃ����\�L�́u�ړ����p�iZ���j�i�A��Z����] �� Y����]�̏��ԁj�v���Ӗ����Ă���B
// �uRy�v�Ƃ����\�L�́u�ړ����p�iY���j�v���Ӗ����Ă���B
// �uRzRy�v�Ƃ����\���́uZ����] �� Y����]�̏��Ԃ̈ړ����p�v��\���Ă���B
//
// Z����]�p�AY����]�p�������Ƃ�0�x���A�����x�N�g��(1, 0, 0) �̕����ƒ�`����B
// Z����]�p�̐��̑����́AZ���̐��̕����������Ĕ����v���B
// Y����]�p�̐��̑����́AY���̐��̕����������Ĕ����v���B�Ƃ���B
//
// �ړ����p�ɂ�Z����]�p��Y����]�p�ɂ��w��(_angRzMv, _angRyMv)�ƒP�ʃx�N�g���w��(_vX, _vY, _vZ) ������Ƃ������A
// �悭�g���̂͑O�҂̕��ŁA�{�N���X�̃��\�b�h�� _angRzMv �� _angRyMv �𑀍삷����̂��قƂ�ǂł���B
// �������A�ŏI�I�ɂ� ���[���h�ϊ��s��̍s����쐬���邽�߁A�u�P�ʃx�N�g��(_vX, _vY, _vZ)*�ړ����x �v  �Ƃ����v�Z������K�v������B
// ���ǍŌ�͒P�ʃx�N�g�����߂Ă���̂����A�ړ����̍��W�v�Z�Ȃǂ́A���񂴂�_angRzMv �� _angRyMv�ōs���āA�Ō�ɂP��P�ʃx�N�g����
// ���߂�A�Ƃ����̂����z�B�����œK���̗]�n�����Ԏc���Ă���i���A�܂������j�B
//
// �{�N���X���C�u�����ł́A����(_angRzMv, _angRyMv)����ɑ��삵�āA�����ŕ����x�N�g��(_vX, _vY, _vZ) �������v�Z���Ă���B
// (_vX, _vY, _vZ)�݂̂����\�b�h���g�킸���ڑ��삷��ƁA(_angRzMv, _angRyMv)�Ƃ̓����������̂Œ��ӁB
// �{�N���X�̃��\�b�h���g�p�������ł́A����Ȃ��Ƃ͋N����Ȃ����ƂƂ���B
//
// ���ړ����x:Velo or MvVelo��
// �L�����́u�ړ����x�v(_veloMv)��ێ����Ă���B�ړ�������@�͊ȒP�ŁA��{�I�ɖ��t���[���u�ړ����p�v�Ɂu�ړ����x�v�����������B
// �܂�u�ړ����p�v(_vX, _vY, _vZ)�Ɂu�ړ����x�v(_veloMv)���|���Z���Ă���B�P�t���[����̍��W��
// (_vX*_veloMv, _vY*_veloMv, _vZ*_veloMv) �ł���B  ����ɖ{���C�u�����̒P�ʋ���(�Q�[�����̒����P�ƍl���鐮���{�l�j���|����B
// ����āA(_vX*_veloMv*LEN_UNIT, _vY*_veloMv*LEN_UNIT, _vZ*_veloMv*LEN_UNIT)���P�t���[����̍��W�B

// ������]���p:AngFace��
// �L�����������Ă�����p�i�����j�A���u����]���p�v�ƌĂԂ��Ƃɂ���B�u���[�J������]���p�v�̗��ł��B
//�u����]���p�v�́A���[���h�ϊ��s��̎���]�ƑΉ����Ă���i�{�����Ⴄ���ǁj�B
// ���[���h�ϊ��s��̎���]�Ƃ́AX����]�p�AY����]�p�AZ����]�p�̂��ƂŁA���ꂼ��A
// _angFace[AXIS_X], _angFace[AXIS_Y], _angFace[AXIS_Z] ���ێ����Ă���B
// �{���C�u�����ł́A�L�������̃��[�J�����W�n�̒P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g��(1, 0, 0) ���L�����́u�O���v�Ɛݒ肵�Ă���B
// X�t�@�C���Ȃǂ̃��f����X���̐��̕����Ɍ����Ă��郂�m�Ƃ���B���f���u������́v�́i0, 1, 0)�B
// �܂��A���[���h�ϊ��s��̉�]�s��̂����鏇�Ԃ́A��{�I�� �uX����]�s�� > Z����]�s�� > Y����]�s�� > �ړ��s�� > (�g��k��) �v �Ƃ���B
// (��  X�� > Y�� > Z�� �̏��ł͂Ȃ���I�j
// ����āAX����]�p�͊���]�����悤�Ƃ��A�L�����������Ă�������͕ς�炸�A�c���Z����]�p�ƁAY����]�p�ŃL�����������Ă�����������肷�邱�ƂƂ���B
// X����]�p�̓L�����̃X�s���A�̂���Q�p�iZ����]�p�EY����]�p�j�ŃL�����́u�O���v���p�������肷��Ƃ����ꍇ�A
// �u����]���p�v����قǂ́u�ړ����p�v�Ɠ����悤�ɁAZ����]�p��Y����]�p�i�ܓx�ƌo�x)�̂Q�̃A���O���l
// (_angFace[AXIS_Z], _angFace[AXIS_Y])�ŕ\���ł���B
// �܂�A�u�O���v�� Z����]�p�EY����]�p����0�x�Ƃ��A�Ⴆ�΁u�O���������Č������v��[Z����]�p,Y����]�p]=[0�x,180�x] �ƕ\������B�B
// �P�ɁuZ����]�p�v�ȂǂƏ����ƁA�u�ړ����p�v��Z����]�p�Ȃ̂��A�u����]���p�v��Z����]�p�Ȃ̂��B���ɂȂ邽�߁A
// �u����]���p(Z��)�v�u����]���p(Y��)�v�Ə������ƂƂ���B�i���u����]���p(X��)�v�����邪�A����̓X�s����\�������ւ̉e���͖����j
// �����Œ��ӂ́A�P�̃L�����������Ă�����p�ɑ΂��āA���͂Q�ʂ�̃A�N�Z�X������@������Ƃ������ƁB�Ⴆ�΁A
// �u�O��(1, 0, 0)�������Đ^�E�����v �� [����]���p(Z��), ����]���p(Y��)]=[0, 90�x] or [180�x,270�x] �Ƃŕ\���ł���B
// �i������]���p(Y��)�͍���n���W�̂���Y���̐������������Ĕ����v���j
// ���� �u�O���v �� [180�x,180�x]�Ƃ��\���ł��邵�A�u�^���v �� [0�x,180�x] �Ƃ� [180�x,0�x] �Ƃ��\���ł���B
// �ǂ���������Ă�������͓����A�A���p��(�L�����̏����)�͈قȂ�B�p�����قȂ�Ƃ܂����L�����͒��ӂ��邱�ƁB
// ���R�A�u�ړ����p�v�ł��A�Q�ʂ�̃A�N�Z�X������@������̂����A������͌����ڂ͍��������B�����������p�x�v�Z����Ƃ��ɉe�����ł�������Ȃ��B

// ���ړ����p�Ǝ���]���p�œ�����
// ������ �u�ړ����p�iZ���j�v���u����]���p(Z��)�v�ցA�u�ړ����p�iY���j�v���u����]���p(Y��)�v �փR�s�[���Ă��ƁA
// �Ȃ�ƈړ����p�ƁA�L�����N�^�̌����̓������ȒP�Ɏ��邶��܂����I
// �t�ɃL�����������Ă�������Ɉړ���Ǐ]�����邱�Ƃ��\�ƂȂ�B

// �������O�������@�\��
// �����O�������@�\�Ƃ́u�ړ����p�v��ݒ肷��ƁA����ɔ����Ď����I�Ɂu����]���p�v��ݒ肷�鎖���Ӗ����Ă���B
// ��̓I�ɂ́A�ȉ��̂悤�Ƀt���[�����ɁA�A���O���l���㏑���R�s�[�i�����j�B�����͍��������Z�i�������������炩�ɕ`��j���Ă����B
//  �E�ړ����p�iZ���j �� ����]���p(Z��)
//  �E�ړ����p�iY���j �� ����]���p(Y��)
// �������u����]���p�v��ݒ�Ă��u�ړ����p�v�ω����Ȃ��i�t�͊֘A���Ȃ��j�̂Œ��ӁB

// ���p���x:AngVelo��
// �u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�A�u����]���p(Z��)�v�u����]���p(Y��)�v�ɂ́A���ꂼ��́u�p���x�v��݂��Ă���B
// �Ⴆ��90�x�E�Ɍ��������ꍇ�A�L�����������Ȃ�J�N���ƌ�����ς��Ă͔߂����̂ŁA���t���[���p���x�����p�����Z����悤�ɂ��āA
// ���炩�Ɍ�����ς���悤�ɂ���B
// �u�p���x�v�͐����̒��ӂ��K�v�B���̏ꍇ�͔����v���A���̏ꍇ�͎��v���ɂȂ�B
// �����]������ꍇ�A�^�[�Q�b�g�ƂȂ�p�x�ւ̓��B������@�̍l�����́A5�ʂ肠��B�i�A�N�Z�X���@�͂Q�ʂ肵���Ȃ��j
// �u��ɔ����v��ōs���v�u��Ɏ��v���ōs���v�u�߂��p�̎�������ōs���v�u�����Ȋp�̎�������ōs���v�u���݉���Ă�������ōs���v
// �ł���B���ꂼ��p�r������̂ŁA�I�v�V���������ȂǂŁA�I���ł���悤�ɂ������ȁB���ł����B

// ���������ړ�: VxMv VyMv VzMv��
// ��L�̈ړ��̌n�Ƃ͂܂������ʂɁA�Ɨ����� X���AY���AZ���ɕ��s�Ȉړ��w�肪�ł���B
// �uX�������ړ����x�v�uY�������ړ����x�v�uZ�������ړ����x�v��ݒ肷��ƁA���t���[��(_X,_Y,_Z)�ɂ��ꂼ��̈ړ�������
// ���Z�����B

//�����̑��ǋL��
//�E�ړ����x�A�ړ����p�p���x�A����]�p�p���x�ɂ́A���ꂼ������x���ݒ�ł���B
//�E�X�v���C���̊�_�A��ԓ_�������Œʉ߂���悤�ȓ������ŋ߉\�B�i���̎����j
//�E����]�́A�{���� Z > X > Y �̎���]���Ԃɂ���̂���ʓI�̂悤���B�܂�O���̊T�O��Z���ŉ��ł���킯���A�Ȃ�قǂ킩��₷���B
//  ���݂� X > Z > Y �́A����Z�������O����X���ł���B
//  ���Ƃ���2D�̉��X�N���[���V���[�e�B���O����낤�Ǝv���Ă���A���� X > Z �����Ő݌v���s���Ă����̂������ł��邪�A�������ǂ�Ȃ��B
//  �܂���3D�ȃV���[�e�B���O�ɂ���Ƃ͎����ł��v���Ă��݂Ȃ������Ȃ�

//2010/02/19�ǋL
// �����܂ɁuRyRz�v�Ƃ����\�������݂���i�uRzRy�v�ƈقȂ�j���A����́uY����] �� Z����]�̏��Ԃ̈ړ����p�v��\���Ă���̂Œ��ӁB
// �@�܂��A�u�ړ����p�iZ���j�v������]�̏��Ԃ̈Ⴂ�𖾊m�ɂ��邽��
// �@�uRzRy��Rz�v�uRyRz��Rz�v�Ə������肵�Ă���Ƃ��������B�i�P�ɁuRz�v�����̏ꍇ�́uRzRy��Rz�v���Ӗ����Ă���j

//�ǋL
//�E���炩�ړ����\�ɁI

//TODO:
//���x�i�������x�j�̒ǉ�
//�C�ӎ���]�i�N�H�[�^�j�I���j
//

GgafDx9GeometricMover::GgafDx9GeometricMover(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;


    for (int i = 0; i < 3; i++) { // i=0:X���A1:Y���A2:Z�� ��\��

        //����]���p
        _angFace[i] = 0; //0 angle �� �R���̕��p�������Ă���
        //����]���p�̊p���x�i����]���p�̑����j= 0 angle/fream
        _angveloFace[i] = 0; //1�t���[���ɉ��Z����鎲��]���p�̊p�����B�f�t�H���g�͎���]���p�̊p���������A�܂�U����������B
        //����]���p�̊p���x��� �� 360,000 angle/fream
        _angveloTopFace[i] = ANGLE360; //_angveloFace[n] �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȏ���]���p�ɐU����������o���鎖���Ӗ�����
        //����]���p�̊p���x���� �� -360,000 angle/fream
        _angveloBottomFace[i] = ANGLE360 * -1; //_angveloFace[n] �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȏ���]���p�ɐU����������o���鎖���Ӗ�����
        //����]���p�̊p�����x�i�p���x�̑����j �� 0 angle/fream^2
        _angacceFace[i] = 0; //_angveloFace[n] �̑����B�f�t�H���g�͎���]���p�̊p�����x����

        _angjerkFace[i] = 0;
        //�ڕW����]���p�ւ̎�������t���O = ����
        _face_ang_targeting_flg[i] = false;
        //�ڕW�̎���]���p
        _angTargetFace[i] = 0; //�ڕW����]���p�ւ̎�������t���O = �����A�̏ꍇ�͖��Ӗ�
        //�ڕW�̎���]���p������~�@�\���L���ɂȂ��]����
        _face_ang_target_allow_way[i] = TURN_BOTH;
        //�ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj
        _face_ang_target_allow_velo[i] = ANGLE180;
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
    _veloTopMv = 256 * LEN_UNIT; //_veloMv �� 256000(=256px) ������ړ��ʂł����Ă��A�����I�ɍ��W������ 256px �ɗ}������B
    //�ړ����x���� = 0   px/fream
    _veloBottomMv = -256 * LEN_UNIT; //_veloMv �� -256000(-256px) �������ړ��ʂ������Ă��A�����I�ɍ��W������ -256000px �ɗ}������B
    //�ړ������x�i�ړ����x�̑����j = 0 px/fream^2
    _accMv = 0; //_veloMv �̑����B�f�t�H���g�͉�������

    _jerkMv = 0;
    //�ړ����p�iZ����]�j�̊p���x = 0 angle/fream
    _angveloRzMv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iZ����]�j�̊p���x��� = +360,000 angle/fream
    _angveloRzTopMv = ANGLE360; //_angveloRzMv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p���x���� = -360,000 angle/fream
    _angveloRzBottomMv = ANGLE360 * -1; //_angveloRzMv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p�����x = 0 angle/fream^2
    _angacceRzMv = 0; //_angveloRzMv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _angjerkRzMv = 0;
    //�ڕW�ړ����p�iZ����]�j�ւ̎�������t���O = ����
    _mv_ang_rz_target_flg = false;
    //�ڕW�̈ړ����p�iZ����]�j
    _angTargetRzMv = 0;
    //�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ��]����
    _mv_ang_rz_target_allow_way = TURN_BOTH;
    //�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
    _mv_ang_rz_target_allow_velo = ANGLE180;
    //�ړ����p�iZ����]�j�ɔ���Z����]���p�̓��������@�\�t���O �� ����
    _relate_RzFaceAng_to_RzMvAng_flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B

    //�ړ����p�iY����]�j�̊p���x = 0 angle/fream
    _angveloRyMv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iY����]�j�̊p���x��� = +360,000 angle/fream
    _angveloRyTopMv = ANGLE360; //_angveloRyMv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p���x���� = -360,000 angle/fream
    _angveloRyBottomMv = ANGLE360 * -1; //_angveloRyMv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iY����]�j�̊p�����x = 0 angle/fream^2
    _angacceRyMv = 0; //_angveloRyMv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _angjerkRyMv = 0;
    //�ڕW�ړ����p�iY����]�j�ւ̎�������t���O = ����
    _mv_ang_ry_target_flg = false;
    //�ڕW�̈ړ����p�iY����]�j
    _angTargetRyMv = 0;
    //�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ��]����
    _mv_ang_ry_target_allow_way = TURN_BOTH;
    //�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
    _mv_ang_ry_target_allow_velo = ANGLE180;
    //�ړ����p�iY����]�j�ɔ���Z����]���p�̓��������@�\�t���O �� ����
    _relate_RyFaceAng_to_RyMvAng_flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B

    //X�������ړ����x�iX�ړ����W�����j�� 0 px/fream
    _veloVxMv = 0;
    //X�������ړ����x��� �� 256 px/fream
    _veloTopVxMv = 256 * LEN_UNIT;
    //X�������ړ����x���� �� 256 px/fream
    _veloBottomVxMv = -256 * LEN_UNIT;
    //X�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVxMv = 0;
    _acceTopVxMv = 256 * LEN_UNIT;
    _acceBottomVxMv = -256 * LEN_UNIT;
    //Y�������ړ����x�iY�ړ����W�����j�� 0 px/fream
    _veloVyMv = 0;
    //Y�������ړ����x��� �� 256 px/fream
    _veloTopVyMv = 256 * LEN_UNIT;
    //Y�������ړ����x���� �� 256 px/fream
    _veloBottomVyMv = -256 * LEN_UNIT;
    //Y�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVyMv = 0;

    _acceTopVyMv = 256 * LEN_UNIT;
    _acceBottomVyMv = -256 * LEN_UNIT;

    //Z�������ړ����x�iZ�ړ����W�����j�� 0 px/fream
    _veloVzMv = 0;
    //Z�������ړ����x��� �� 256 px/fream
    _veloTopVzMv = 256 * LEN_UNIT;
    //Z�������ړ����x���� �� 256 px/fream
    _veloBottomVzMv = -256 * LEN_UNIT;
    //Z�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVzMv = 0;
    _acceTopVzMv = 256 * LEN_UNIT;
    _acceBottomVzMv = -256 * LEN_UNIT;

    _smooth_mv_velo_seq_flg = false;
    _smooth_mv_velo_seq_endacc_flg = true;
    _smooth_mv_velo_seq_top_velo = 0;
    _smooth_mv_velo_seq_end_velo = 0;
    _smooth_mv_velo_seq_distance_of_target = 0;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_frame_of_spend = 0;
    _smooth_mv_velo_seq_spend_frame = 0;
    _smooth_mv_velo_seq_p1 = 0;
    _smooth_mv_velo_seq_p2 = 0;
    _smooth_mv_velo_seq_progress = -1;
}

void GgafDx9GeometricMover::behave() {

    //����]���p����
    angle angDistance;
    for (int i = 0; i < 3; i++) {
        if (_face_ang_targeting_flg[i]) { //�^�[�Q�b�g����������ꍇ
            _angveloFace[i] += _angacceFace[i];
            setFaceAngVelo(i, _angveloFace[i]);

            if (_angveloFace[i] > 0) { //�����v���̏ꍇ
                angDistance = getFaceAngDistance(i, _angTargetFace[i], TURN_COUNTERCLOCKWISE);
                if (_angveloFace[i] > angDistance && _face_ang_target_allow_way[i] != TURN_CLOCKWISE
                        && _face_ang_target_allow_velo[i] >= _angveloFace[i]) {

                    //_TRACE_("STOP1 _angveloFace["<<i<<"]="<<_angveloFace[i]<<" angDistance="<<angDistance<<" _face_ang_target_allow_velo["<<i<<"]="<<_face_ang_target_allow_velo[i]<<" _angveloFace["<<i<<"]="<<_angveloFace[i]);
                    addFaceAng(i, angDistance);
                    _face_ang_targeting_flg[i] = false; //�t���O��߂��ďI��
                } else {
                    addFaceAng(i, _angveloFace[i]);
                }
            } else if (_angveloFace[i] < 0) { //���v���̏ꍇ
                angDistance = getFaceAngDistance(i, _angTargetFace[i], TURN_CLOCKWISE);
                if (_angveloFace[i] < angDistance && _face_ang_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_ang_target_allow_velo[i] <= _angveloFace[i]) { //�ڕW���s���߂��Ă��܂������E�E�E�ȓ�
                    addFaceAng(i, angDistance);
                    _face_ang_targeting_flg[i] = false; //�t���O��߂��ďI��
                } else {
                    addFaceAng(i, _angveloFace[i]);
                }
            } else {
                //_angveloFace[i] == 0
                addFaceAng(i, 0);
            }

            if (_face_ang_targeting_flg[i] == false) {
                //�ڕW�����ɓ��B�������̏���
                //_angveloTopFace[i] = ANGLE360; //����]���p�̊p���x��� �� 360,000 angle/fream
                //_angveloBottomFace[i] = ANGLE360 * -1; //����]���p�̊p���x���� �� -360,000 angle/fream

                //�ڕW�����ɓ��B�������A��~�������s�Ȃ�
                _angacceFace[i] = 0; //����]�����p�A�p���x���O��
                setFaceAngVelo(i, 0); //����]�����p�A�p�����x���O��
            }

        } else {
            //if (_angacceFace[i] != 0) {
            //�t���[�����̎���]���p����̏���
            _angveloFace[i] += _angacceFace[i];
            if (_angveloFace[i] != 0) {
                addFaceAng(i, _angveloFace[i]);
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
    _veloVxMv += _acceVxMv;
    setVxMvVelo(_veloVxMv);
    //Y�������ړ������x�̏���
    _veloVyMv += _acceVyMv;
    setVyMvVelo(_veloVyMv);
    //Z�������ړ������x�̏���
    _veloVzMv += _acceVzMv;
    setVzMvVelo(_veloVzMv);

    //�Ȃ߂炩�ړ��V�[�N�G���X�N����
    if (_smooth_mv_velo_seq_flg) {
        if (_smooth_mv_velo_seq_frame_of_spend < 0) {
            //�ڕW�����w��̏ꍇ
            if (_smooth_mv_velo_seq_progress == 0) {
                //�����ݒ�
                setMvAcce(_smooth_mv_velo_seq_p1, _smooth_mv_velo_seq_top_velo);
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
                    setMvAcce(_smooth_mv_velo_seq_distance_of_target - _smooth_mv_velo_seq_mv_distance, _smooth_mv_velo_seq_end_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 3) {
                //������
                if (_smooth_mv_velo_seq_mv_distance >= _smooth_mv_velo_seq_distance_of_target) {
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
                setMvAcce(_smooth_mv_velo_seq_p1, _smooth_mv_velo_seq_top_velo);
                _smooth_mv_velo_seq_progress++;
            } else if (_smooth_mv_velo_seq_progress == 1) {
                //������
                if (_smooth_mv_velo_seq_spend_frame >= _smooth_mv_velo_seq_p1) {
                    //p1 �ɓ��B����� ������
                    setMvAcce(0);
                    setMvVelo(_smooth_mv_velo_seq_top_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 2) {
                //������
                if (_smooth_mv_velo_seq_spend_frame >= _smooth_mv_velo_seq_p2) {
                    //p2 �ɓ��B����� ����t���[�����猸����
                    setMvAcce2(_smooth_mv_velo_seq_frame_of_spend - _smooth_mv_velo_seq_spend_frame, _smooth_mv_velo_seq_end_velo);
                    _smooth_mv_velo_seq_progress++;
                }
            } else if (_smooth_mv_velo_seq_progress == 3) {
                //������
                if (_smooth_mv_velo_seq_spend_frame >= _smooth_mv_velo_seq_frame_of_spend) {
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

    _accMv += _jerkMv;
    //�ړ������x�̏���
    _veloMv += _accMv;
    setMvVelo(_veloMv);

    if (_smooth_mv_velo_seq_flg) {
        if (_smooth_mv_velo_seq_frame_of_spend < 0) {
            _smooth_mv_velo_seq_mv_distance+=abs(_veloMv);
        } else {
            _smooth_mv_velo_seq_spend_frame++;
        }
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
                _mv_ang_rz_target_flg = false; //�t���O��߂��ďI��
            } else {
                addRzMvAng(_angveloRzMv);
            }
        } else if (_angveloRzMv < 0) { //���v���̏ꍇ

            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_CLOCKWISE);
            if (_angveloRzMv < angDistance && _mv_ang_rz_target_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_mv_ang_rz_target_allow_velo <= _angveloRzMv) {
                addRzMvAng(angDistance);
                _mv_ang_rz_target_flg = false; //�t���O��߂��ďI��
            } else {
                addRzMvAng(_angveloRzMv);
            }
        } else {
            addRzMvAng(0);
        }
        if (_mv_ang_rz_target_flg == false) {
            //_angveloRzTopMv = ANGLE360; //�ړ����p�iZ����]�j�̊p���x��� �� 360,000 angle/fream
            //_angveloRzBottomMv = ANGLE360 * -1; //�ړ����p�iZ����]�j�̊p���x���� �� -360,000 angle/fream

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
                _mv_ang_ry_target_flg = false; //�t���O��߂��ďI��
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
                _mv_ang_ry_target_flg = false; //�t���O��߂��ďI��
            } else {
                addRyMvAng(_angveloRyMv);
            }
        } else {
            //_angveloRyMv==0
            addRyMvAng(0);
        }
        if (_mv_ang_ry_target_flg == false) {
            //_angveloRyTopMv = ANGLE360; //�ړ����p�iY����]�j�̊p���x��� �� 360,000 angle/fream
            //_angveloRyBottomMv = ANGLE360*-1; //�ړ����p�iY����]�j�̊p���x���� �� -360,000 angle/fream

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

    //Actor�ɔ��f
    _pActor->_X += (int)(_vX * _veloMv + _veloVxMv);
    _pActor->_Y += (int)(_vY * _veloMv + _veloVyMv);
    _pActor->_Z += (int)(_vZ * _veloMv + _veloVzMv);


}

void GgafDx9GeometricMover::setFaceAng(int prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = GgafDx9Util::simplifyAng(prm_angFace);
}

void GgafDx9GeometricMover::setFaceAng(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDx9GeometricMover::addFaceAng(int prm_axis, angle prm_angDistance) {
    angle angOffsetrot_FaceAng;
    angOffsetrot_FaceAng = prm_angDistance;
    if (_angveloBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAng = _angveloBottomFace[prm_axis];
    } else if (prm_angDistance > _angveloTopFace[prm_axis]) {
        angOffsetrot_FaceAng = _angveloTopFace[prm_axis];
    }
    setFaceAng(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAng);
}

void GgafDx9GeometricMover::setFaceAngVelo(int prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloTopFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloTopFace[prm_axis];
    } else if (prm_angveloRot < _angveloBottomFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloBottomFace[prm_axis];
    } else {
        _angveloFace[prm_axis] = prm_angveloRot;
    }
}

void GgafDx9GeometricMover::forceFaceAngVeloRange(int prm_axis,
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

void GgafDx9GeometricMover::setFaceAngAcce(int prm_axis, angacce prm_angacceRot) {
    _angacceFace[prm_axis] = prm_angacceRot;
}

void GgafDx9GeometricMover::setStopTarget_FaceAngV(int prm_axis,
                                                  int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMv) {
    setStopTarget_FaceAng(
      prm_axis,
      GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
      prm_way_allow,
      prm_angveloAllowRyMv
    );
}

void GgafDx9GeometricMover::setStopTarget_FaceAng(int prm_axis,
                                                 angle prm_angTargetRot,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllow) {
    _face_ang_targeting_flg[prm_axis] = true;
    _angTargetFace[prm_axis] = GgafDx9Util::simplifyAng(prm_angTargetRot);
    _face_ang_target_allow_way[prm_axis] = prm_way_allow;
    _face_ang_target_allow_velo[prm_axis] = prm_angveloAllow;
}

angle GgafDx9GeometricMover::getFaceAngDistance(int prm_axis, int prm_tX, int prm_tY, int prm_way) {
    return getFaceAngDistance(prm_axis, GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY
            - (_pActor->_Y)), prm_way);
}

angle GgafDx9GeometricMover::getFaceAngDistance(int prm_axis, angle prm_angTargetRot, int prm_way) {
    angle _angTargetRot;
    _angTargetRot = GgafDx9Util::simplifyAng(prm_angTargetRot);
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
                throwGgafCriticalException("GgafDx9GeometricMover::getFaceAngDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9GeometricMover::getFaceAngDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9GeometricMover::getFaceAngDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
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
                throwGgafCriticalException("GgafDx9GeometricMover::getFaceAngDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return (_angTargetRot - _angFace[prm_axis]);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] <= ANGLE360) {
            return ANGLE360 - _angFace[prm_axis] + _angTargetRot;
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9GeometricMover::getFaceAngDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return -1 * (_angFace[prm_axis] + ANGLE360 - _angTargetRot);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] <= ANGLE360) {
            return -1 * (_angFace[prm_axis] - _angTargetRot);
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDx9GeometricMover::getFaceAngDistance() ���݂̎���]���p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDx9GeometricMover::getFaceAngDistance() ���̂�����p�̋��������߂�܂���(2)�B_pActor="<<_pActor->getName());
}

void GgafDx9GeometricMover::forceMvVeloRange(int prm_velo) {
    forceMvVeloRange(-prm_velo, prm_velo);
}

void GgafDx9GeometricMover::forceMvVeloRange(int prm_veloMv01, int prm_veloMv02) {
    if (prm_veloMv01 < prm_veloMv02) {
        _veloTopMv = prm_veloMv02;
        _veloBottomMv = prm_veloMv01;
    } else {
        _veloTopMv = prm_veloMv01;
        _veloBottomMv = prm_veloMv02;
    }
    setMvVelo(_veloMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometricMover::setMvVelo(int prm_veloMv) {
    if (prm_veloMv > _veloTopMv) {
        _veloMv = _veloTopMv;
    } else if (prm_veloMv < _veloBottomMv) {
        _veloMv = _veloBottomMv;
    } else {
        _veloMv = prm_veloMv;
    }
}

void GgafDx9GeometricMover::addMvVelo(int prm_veloMv_Offset) {
    setMvVelo(_veloMv + prm_veloMv_Offset);
}

void GgafDx9GeometricMover::setMvAcce(int prm_acceMove) {
    _accMv = prm_acceMove;
}

void GgafDx9GeometricMover::setMvAcceToStop(int prm_distance_of_target) {
    // a = -(v0^2) / 2S
    _accMv  =  -(1.0*_veloMv*_veloMv) / (2.0*prm_distance_of_target);
    if (_accMv < 0) {
        _accMv += 1;
    } else {
        _accMv -= 1;
    }
    //(frame)((2.0*prm_distance_of_target) / _veloMv); //�g�p�t���[����
}
void GgafDx9GeometricMover::setMvAcce2(int prm_frame_of_spend, velo prm_velo_target) {
    //a = (vx-v0) / t
    _accMv = (prm_velo_target - _veloMv) / (1.0f*prm_velo_target);
}
void GgafDx9GeometricMover::setMvAcce(int prm_distance_of_target, velo prm_velo_target) {
    // a = (vx^2 - v0^2) / 2S
    _accMv =  ((1.0f*prm_velo_target*prm_velo_target) - (1.0f*_veloMv*_veloMv)) / (2.0f*prm_distance_of_target);
    if (_accMv < 0) {
        _accMv += 1;
    } else {
        _accMv -= 1;
    }
    //(frame)((1.0*prm_velo_target - _veloMv) / _accMv); //�g�p�t���[����

    // �y�⑫�z
    // v0 <= 0  ����  vx <= 0 �ꍇ�A���邢��  v0 >= 0  ����  vx >= 0  �ꍇ�́AS(�ڕW����)����L���Ŗ��Ȃ��B
    // �ł�
    // v0 < 0   ����  vx > 0  �ꍇ�A���邢��  v0 > 0   ����  vx < 0   �ꍇ�́A�ǂ��Ȃ邩�H
    //
    //    ���x
    //     ^        a:�����x
    //     |        S:�ړ������i�ڕW���B���x�ɒB����܂łɔ�₷�����j
    //     |       v0:�����_�̑��x
    //     |       vx:�ڕW���B���x
    //     |       tx:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
    //  v0 |
    //     |�_
    //     |  �_  �X����a
    //     | S1 �_
    //     |      �_ tc     tx
    //   --+--------�_------+---> ����(�t���[��)
    //   0 |          �_ S2 |
    //     |            �_  |
    //   vx|..............�_|
    //     |
    //
    //
    //    S = S1 - S2 , ��_�� tc �Ƃ���
    //
    //    S1 = (1/2) v0 tc
    //    S2 = (1/2) -vx (tx - tc)
    //    S = S1 - S2 ���
    //    S = (1/2) v0 tc -  { (1/2) -vx (tx - tc) }
    //      = (v0 tc + vx tx - vx tc) / 2    �E�E�E�@
    //
    //    ���� v = a t + v0 �ɂ����� v = 0 �� t �� tc �ł���̂�
    //    tc = -v0 / a
    //    ����� �@ �֑��
    //    S = (v0 (-v0 / a) + vx tx - vx (-v0 / a)) / 2 �E�E�E�A
    //
    //    �܂� a = (vx - v0) / tx �ł���̂�
    //    tx = (vx - v0) / a ����� �A �֑��
    //    �����
    //    S = (v0 (-v0 / a) + vx ((vx - v0) / a) - vx (-v0 / a)) / 2
    //
    //    a �ɂ��ĉ���
    //
    //    S = {( -(v0^2) / a  + (vx (vx - v0)) / a + (vx v0) / a)) / 2
    //    aS = { -(v0^2) + (vx (vx - v0)) + (vx v0) } / 2
    //    a = { -(v0^2) + (vx (vx - v0)) + (vx v0) } / 2S
    //    a = (-(v0^2) + vx^2 - vx v0 + vx v0) / 2S
    //    a = (vx^2 -v0^2) / 2S
    //
    //    ���� a = (vx^2 - v0^2) / 2S �ƂȂ�̂�
    //    v0 <= 0  ����  vx <= 0 �ꍇ�A���邢��  v0 >= 0  ����  vx >= 0  �ꍇ�Ɠ����ł���


}

void GgafDx9GeometricMover::execSmoothMvVeloSequence(velo prm_top_velo, velo prm_end_velo, int prm_distance_of_target,
                                                    bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_mv_velo_seq_top_velo = prm_top_velo;
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_distance_of_target = prm_distance_of_target;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_frame_of_spend = -1; //�ڕW���Ԃ͎g��Ȃ��ꍇ�͕���ݒ肵�Ă���(��������Ŏg�p)
    _smooth_mv_velo_seq_spend_frame = 0;
    _smooth_mv_velo_seq_p1 = (int)(prm_distance_of_target*1.0 / 4.0);
    _smooth_mv_velo_seq_p2 = (int)(prm_distance_of_target*3.0 / 4.0);
    _smooth_mv_velo_seq_progress = 0;
}


void GgafDx9GeometricMover::execSmoothMvVeloSequence2(velo prm_top_velo, velo prm_end_velo, int prm_frame_of_spend,
                                                    bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_mv_velo_seq_top_velo = prm_top_velo;
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_distance_of_target = 0;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_frame_of_spend = prm_frame_of_spend;
    _smooth_mv_velo_seq_spend_frame = 0;
    _smooth_mv_velo_seq_p1 = (int)(prm_frame_of_spend*1.0 / 4.0);
    _smooth_mv_velo_seq_p2 = (int)(prm_frame_of_spend*3.0 / 4.0);
    _smooth_mv_velo_seq_progress = 0;
}

void GgafDx9GeometricMover::execSmoothMvVeloSequence3(velo prm_end_velo, int prm_distance_of_target, int prm_frame_of_spend,
                                                      bool prm_endacc_flg) {
    _smooth_mv_velo_seq_flg = true;
    _smooth_mv_velo_seq_p1 = (int)(prm_distance_of_target*1.0 / 4.0);
    _smooth_mv_velo_seq_p2 = (int)(prm_distance_of_target*3.0 / 4.0);
    _smooth_mv_velo_seq_end_velo = prm_end_velo;
    _smooth_mv_velo_seq_distance_of_target = prm_distance_of_target;
    _smooth_mv_velo_seq_mv_distance = 0;
    _smooth_mv_velo_seq_frame_of_spend = -1; //�ڕW���Ԃ͎g��Ȃ�(_smooth_mv_velo_seq_top_velo�v�Z�ōl������邽��)
    _smooth_mv_velo_seq_spend_frame = 0;
    _smooth_mv_velo_seq_progress = 0;

    //    ���x
    //     ^
    //     |                          S:�ړ�����
    //     |                         vs:�����_�̑��x
    //     |                         vx:����1/4 �` 3/4 �̑��x
    //     |                         ve:�ŏI�ڕW���B���x
    //   vx|....�Q�Q�Q�Q�Q            t:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
    //     |   /|         |�_
    //   ve|../.|.........|..�_
    //     | /  |         |    |
    //     |/   |         |    |
    //   vs|    |    S    |    |
    //     |    |         |    |
    //   --+----+----+----+----+-----> ����(�t���[��)
    //   0 | (1/4)t    (3/4)t  t

    // ������ ��`�{�����`�{��` �̖ʐ�
    // S  = (1/2) (vs + vx) (1/4)t  + vx (2/4)t  +  (1/2) (ve + vx) (1/4)t
    // �����vx�ɂ��ĉ���
    // 8S = (vs + vx)t + 4 vx t + (ve + vx)t
    // 8S/t = vs + vx + 4vx + ve + vx
    // 6vx = 8S/t - vs - ve
    // vx = (8S/t - vs - ve) / 6
    _smooth_mv_velo_seq_top_velo = (8.0*prm_distance_of_target/prm_frame_of_spend - _veloMv - prm_end_velo) / 6.0;
}

bool GgafDx9GeometricMover::isMoveingSmooth() {
    return _smooth_mv_velo_seq_flg;
}


void GgafDx9GeometricMover::setRzMvAng(int prm_tX, int prm_tY) {
    setRzMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometricMover::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _angRzMv) {
        _angRzMv = GgafDx9Util::simplifyAng(prm_ang);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDx9GeometricMover::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRzBottomMv > prm_angDistance) {
        angOffset = _angveloRzBottomMv;
    } else if (prm_angDistance > _angveloRzTopMv) {
        angOffset = _angveloRzTopMv;
    }
    setRzMvAng(_angRzMv + angOffset);
}

void GgafDx9GeometricMover::setRzMvAngVelo(angvelo prm_angveloRzMv) {
    if (prm_angveloRzMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzMv;
    }
}

void GgafDx9GeometricMover::setRzMvAngAcce(angacce prm_angacceRzMv) {
    _angacceRzMv = prm_angacceRzMv;
}

void GgafDx9GeometricMover::forceRzMvAngVeloRange(angvelo prm_angveloRzMv01,
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

void GgafDx9GeometricMover::setStopTarget_RzMvAng(angle prm_angTargetRzMv,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMv) {
    _mv_ang_rz_target_flg = true;
    _angTargetRzMv = GgafDx9Util::simplifyAng(prm_angTargetRzMv);
    _mv_ang_rz_target_allow_way = prm_way_allow;
    _mv_ang_rz_target_allow_velo = prm_angveloAllowRyMv;
}

void GgafDx9GeometricMover::setStopTarget_RzMvAngV(int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMv) {
    setStopTarget_RzMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometricMover::getRzMvAngDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRzMvAngDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometricMover::getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way) {
    angle angTargetRzMv = GgafDx9Util::simplifyAng(prm_angTargetRzMv);
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        if (0 <= _angRzMv && _angRzMv < ANGLE180) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv) {
                return -1 * (_angRzMv - angTargetRzMv);
            } else if (angTargetRzMv == _angRzMv) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv < _angRzMv + ANGLE180) {
                return angTargetRzMv - _angRzMv;
            } else if (angTargetRzMv == _angRzMv + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRzMv + ANGLE180 < angTargetRzMv && angTargetRzMv <= ANGLE360) {
                return -1 * (_angRzMv + (ANGLE360 - angTargetRzMv));
            } else {
                //��������
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDx9GeometricMover::behave() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
            }
        } else if (ANGLE180 <= _angRzMv && _angRzMv <= ANGLE360) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv - ANGLE180) {
                return ANGLE360 - _angRzMv + angTargetRzMv;
            } else if (angTargetRzMv == _angRzMv - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -ANGLE180;
            } else if (_angRzMv - ANGLE180 < angTargetRzMv && angTargetRzMv < _angRzMv) {
                return -1 * (_angRzMv - angTargetRzMv);
            } else if (_angRzMv == angTargetRzMv) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv <= ANGLE360) {
                return angTargetRzMv - _angRzMv;
            } else {
                //��������
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDx9GeometricMover::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        if (0 <= _angRzMv && _angRzMv < ANGLE180) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv) {
                return ANGLE360 - _angRzMv + angTargetRzMv;
            } else if (angTargetRzMv == _angRzMv) {
                //�d�Ȃ��Ă�ꍇ
                return ANGLE360;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv < _angRzMv + ANGLE180) {
                return -1*(_angRzMv + (ANGLE360-angTargetRzMv));
            } else if (angTargetRzMv == _angRzMv + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRzMv + ANGLE180 < angTargetRzMv && angTargetRzMv <= ANGLE360) {
                return angTargetRzMv - _angRzMv;
            } else {
                //��������
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDx9GeometricMover::behave() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
            }
        } else if (ANGLE180 <= _angRzMv && _angRzMv <= ANGLE360) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv - ANGLE180) {
                return  -1*(_angRzMv - angTargetRzMv);
            } else if (angTargetRzMv == _angRzMv - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -ANGLE180;
            } else if (_angRzMv - ANGLE180 < angTargetRzMv && angTargetRzMv < _angRzMv) {
                return _angRzMv + (ANGLE360 - angTargetRzMv);
            } else if (_angRzMv == angTargetRzMv) {
                //�d�Ȃ��Ă�ꍇ
                return -ANGLE360;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv <= ANGLE360) {
                return angTargetRzMv + (ANGLE360 - _angRzMv);
            } else {
                //��������
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDx9GeometricMover::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return (angTargetRzMv - _angRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv <= ANGLE360) {
            return ANGLE360 - _angRzMv + angTargetRzMv;
        } else if (_angRzMv == angTargetRzMv) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDx9GeometricMover::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return -1 * (_angRzMv + ANGLE360 - angTargetRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv <= ANGLE360) {
            return -1 * (_angRzMv - angTargetRzMv);
        } else if (_angRzMv == angTargetRzMv) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDx9GeometricMover::getRzMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
    throwGgafCriticalException("GgafDx9GeometricMover::getRzMvAngDistance() ���̂�����p�̋��������߂�܂���(1)�B_pActor="<<_pActor->getName());
}


void GgafDx9GeometricMover::setRyMvAng(int prm_tX, int prm_tY) {
    setRyMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometricMover::setRyMvAng(angle prm_ang) {
    if (prm_ang != _angRyMv) {
        _angRyMv = GgafDx9Util::simplifyAng(prm_ang);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9GeometricMover::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRyBottomMv > prm_angDistance) {
        angOffset = _angveloRyBottomMv;
    } else if (prm_angDistance > _angveloRyTopMv) {
        angOffset = _angveloRyTopMv;
    }
    setRyMvAng(_angRyMv + angOffset);
}

void GgafDx9GeometricMover::setRyMvAngVelo(angvelo prm_angveloRyMv) {
    if (prm_angveloRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRyMv;
    }
}

void GgafDx9GeometricMover::setRyMvAngAcce(angacce prm_angacceRyMv) {
    _angacceRyMv = prm_angacceRyMv;
}

void GgafDx9GeometricMover::forceRyMvAngVeloRange(angvelo prm_angveloRyMv01,
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

void GgafDx9GeometricMover::setStopTarget_RyMvAng(angle prm_angTargetRyMv,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMv) {
    _mv_ang_ry_target_flg = true;
    _angTargetRyMv = GgafDx9Util::simplifyAng(prm_angTargetRyMv);
    _mv_ang_ry_target_allow_way = prm_way_allow;
    _mv_ang_ry_target_allow_velo = prm_angveloAllowRyMv;
}

void GgafDx9GeometricMover::setStopTarget_RyMvAngV(int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMv) {
    setStopTarget_RyMvAng(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometricMover::getRyMvAngDistance(int prm_tX, int prm_tY, int prm_way) {
    return getRyMvAngDistance(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometricMover::getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way) {
    angle angTargetRyMv;
    angTargetRyMv = GgafDx9Util::simplifyAng(prm_angTargetRyMv);
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        if (0 <= _angRyMv && _angRyMv < ANGLE180) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv) {
                return -1 * (_angRyMv - angTargetRyMv);
            } else if (angTargetRyMv == _angRyMv) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv < _angRyMv + ANGLE180) {
                return angTargetRyMv - _angRyMv;
            } else if (angTargetRyMv == _angRyMv + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRyMv + ANGLE180 < angTargetRyMv && angTargetRyMv <= ANGLE360) {
                return -1 * (_angRyMv + (ANGLE360 - angTargetRyMv));
            } else {
                //��������
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDx9GeometricMover::behave() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
            }
        } else if (ANGLE180 <= _angRyMv && _angRyMv <= ANGLE360) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv - ANGLE180) {
                return ANGLE360 - _angRyMv + angTargetRyMv;
            } else if (angTargetRyMv == _angRyMv - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B
                return -ANGLE180;
            } else if (_angRyMv - ANGLE180 < angTargetRyMv && angTargetRyMv < _angRyMv) {
                return -1 * (_angRyMv - angTargetRyMv);
            } else if (_angRyMv == angTargetRyMv) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv <= ANGLE360) {
                return angTargetRyMv - _angRyMv;
            } else {
                //��������
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDx9GeometricMover::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //�������̉�]
        if (0 <= _angRyMv && _angRyMv < ANGLE180) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv) {
                return ANGLE360 - _angRyMv + angTargetRyMv;
            } else if (angTargetRyMv == _angRyMv) {
                //�d�Ȃ��Ă�ꍇ
                return ANGLE360;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv < _angRyMv + ANGLE180) {
                return -1*(_angRyMv + (ANGLE360-angTargetRyMv));
            } else if (angTargetRyMv == _angRyMv + ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return ANGLE180;
            } else if (_angRyMv + ANGLE180 < angTargetRyMv && angTargetRyMv <= ANGLE360) {
                return angTargetRyMv - _angRyMv;
            } else {
                //��������
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDx9GeometricMover::behave() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B_pActor="<<_pActor->getName());
            }
        } else if (ANGLE180 <= _angRyMv && _angRyMv <= ANGLE360) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv - ANGLE180) {
                return  -1*(_angRyMv - angTargetRyMv);
            } else if (angTargetRyMv == _angRyMv - ANGLE180) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B
                return -ANGLE180;
            } else if (_angRyMv - ANGLE180 < angTargetRyMv && angTargetRyMv < _angRyMv) {
                return _angRyMv + (ANGLE360 - angTargetRyMv);
            } else if (_angRyMv == angTargetRyMv) {
                //�d�Ȃ��Ă�ꍇ
                return -ANGLE360;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv <= ANGLE360) {
                return angTargetRyMv + (ANGLE360 - _angRyMv);
            } else {
                //��������
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDx9GeometricMover::getRyMvAngDistance() �ړ����p�iZ����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return (angTargetRyMv - _angRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv <= ANGLE360) {
            return ANGLE360 - _angRyMv + angTargetRyMv;
        } else if (_angRyMv == angTargetRyMv) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDx9GeometricMover::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //���v���̏ꍇ
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return -1 * (_angRyMv + ANGLE360 - angTargetRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv <= ANGLE360) {
            return -1 * (_angRyMv - angTargetRyMv);
        } else if (_angRyMv == angTargetRyMv) {
            //�d�Ȃ��Ă�ꍇ
            return 0;
        } else {
            //��������
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDx9GeometricMover::getRyMvAngDistance() �ړ����p�iY����]�j�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
    throwGgafCriticalException("GgafDx9GeometricMover::getRyMvAngDistance() ���̂�����p�̋��������߂�܂���(1)�B_pActor="<<_pActor->getName());
}

void GgafDx9GeometricMover::getRzRyMvAngDistance(int prm_way,
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

        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
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
        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
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
        throwGgafCriticalException("GgafDx9GeometricMover::getRzRyMvAngDistance() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDx9GeometricMover::getRzRyFaceAngDistance(int prm_way,
                                                  angle prm_target_angRz, angle prm_target_angRy,
                                                  angle& out_d_angRz, angle& out_d_angRy,
                                                  angle& out_target_angRz, angle& out_target_angRy) {
    angle target_angRz = prm_target_angRz;
    angle target_angRy = prm_target_angRy;
    if (prm_way == TURN_CLOSE_TO) { //�߂��ق���]
        angle d1_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOSE_TO);
        angle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, target_angRy, TURN_CLOSE_TO) * ((GgafDx9Util::COS[GgafDx9Util::simplifyAng(target_angRz*2)/ANGLE_RATE]/2.0) + 0.5);
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
        GgafDx9Util::anotherRzRy(target_angRz, target_angRy);
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
        throwGgafCriticalException("GgafDx9GeometricMover::getRzRyMvAngDistance() prm_way="<<prm_way<<" �͑z��O�ł��B_pActor="<<_pActor->getName());
    }
}

void GgafDx9GeometricMover::setRzRyMvAng(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMv || prm_angRy !=_angRyMv ) {
        _angRzMv = GgafDx9Util::simplifyAng(prm_angRz);
        _angRyMv = GgafDx9Util::simplifyAng(prm_angRy);
        GgafDx9Util::getNormalizeVectorZY(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9GeometricMover::setRzRyMvAng_by_RyRz(angle prm_angRyRz_Ry, angle prm_angRyRz_Rz) {
    angle RyRz_Ry = GgafDx9Util::simplifyAng(prm_angRyRz_Ry);
    angle RyRz_Rz = GgafDx9Util::simplifyAng(prm_angRyRz_Rz);
    float out_vY, out_vZ;
    GgafDx9Util::getNormalizeVectorZY(RyRz_Ry, ANGLE360-RyRz_Rz, _vX, out_vY, out_vZ);
    _vY = -1.0f*out_vZ;
    _vZ = out_vY;
    GgafDx9Util::getRzRyAng(_vX, _vZ, _vY, _angRzMv, _angRyMv);
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9GeometricMover::setMvAng(GgafDx9GeometricActor* prm_pActor_Target) {
    setMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9GeometricMover::setMvAng(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRzRyAng(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _vX,
                   _vY,
                   _vZ,
                   _angRzMv,
                   _angRyMv
                 );
    if (_relate_RzFaceAng_to_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_to_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDx9GeometricMover::setStopTarget_RzRyMvAng(GgafDx9GeometricActor* prm_pActor_Target) {
    setStopTarget_RzRyMvAng(
        prm_pActor_Target->_X,
        prm_pActor_Target->_Y,
        prm_pActor_Target->_Z
    );
}

void GgafDx9GeometricMover::setStopTarget_RzRyMvAng(int prm_tX, int prm_tY, int prm_tZ) {
    angle angRz_Target;
    angle angRy_Target;

    GgafDx9Util::getRzRyAng(
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

void GgafDx9GeometricMover::forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02) {
    if (prm_veloVxMv01 < prm_veloVxMv02) {
        _veloTopVxMv = prm_veloVxMv02;
        _veloBottomVxMv = prm_veloVxMv01;
    } else {
        _veloTopVxMv = prm_veloVxMv01;
        _veloBottomVxMv = prm_veloVxMv02;
    }
    setVxMvVelo(_veloVxMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometricMover::setVxMvVelo(velo prm_veloVxMv) {
    if (prm_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (prm_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    } else {
        _veloVxMv = prm_veloVxMv;
    }
}

void GgafDx9GeometricMover::addVxMvVelo(velo prm_veloVxMv) {
    _veloVxMv += prm_veloVxMv;
    if (_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    }
}

void GgafDx9GeometricMover::setVxMvAcce(acce prm_acceVxMv) {
    if (prm_acceVxMv > _acceTopVxMv) {
        _acceVxMv = _acceTopVxMv;
    } else if (prm_acceVxMv < _acceBottomVxMv) {
        _acceVxMv = _acceBottomVxMv;
    } else {
        _acceVxMv = prm_acceVxMv;
    }
}

void GgafDx9GeometricMover::addVxMvAcce(acce prm_acceVxMv) {
    setVxMvAcce(_acceVxMv + prm_acceVxMv);
}


void GgafDx9GeometricMover::forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02) {
    if (prm_acceVxMv01 < prm_acceVxMv02) {
        _acceTopVxMv = prm_acceVxMv02;
        _acceBottomVxMv = prm_acceVxMv01;
    } else {
        _acceTopVxMv = prm_acceVxMv01;
        _acceBottomVxMv = prm_acceVxMv02;
    }
    setVxMvAcce(_acceVxMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}


void GgafDx9GeometricMover::forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02) {
    if (prm_veloVyMv01 < prm_veloVyMv02) {
        _veloTopVyMv = prm_veloVyMv02;
        _veloBottomVyMv = prm_veloVyMv01;
    } else {
        _veloTopVyMv = prm_veloVyMv01;
        _veloBottomVyMv = prm_veloVyMv02;
    }
    setVyMvVelo(_veloVyMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometricMover::setVyMvVelo(velo prm_veloVyMv) {
    if (prm_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (prm_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    } else {
        _veloVyMv = prm_veloVyMv;
    }
}

void GgafDx9GeometricMover::addVyMvVelo(velo prm_veloVyMv) {
    _veloVyMv += prm_veloVyMv;
    if (_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    }
}

void GgafDx9GeometricMover::setVyMvAcce(acce prm_acceVyMv) {
    if (prm_acceVyMv > _acceTopVyMv) {
        _acceVyMv = _acceTopVyMv;
    } else if (prm_acceVyMv < _acceBottomVyMv) {
        _acceVyMv = _acceBottomVyMv;
    } else {
        _acceVyMv = prm_acceVyMv;
    }
}

void GgafDx9GeometricMover::addVyMvAcce(acce prm_acceVyMv) {
    setVyMvAcce(_acceVyMv + prm_acceVyMv);
}


void GgafDx9GeometricMover::forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02) {
    if (prm_acceVyMv01 < prm_acceVyMv02) {
        _acceTopVyMv = prm_acceVyMv02;
        _acceBottomVyMv = prm_acceVyMv01;
    } else {
        _acceTopVyMv = prm_acceVyMv01;
        _acceBottomVyMv = prm_acceVyMv02;
    }
    setVyMvAcce(_acceVyMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometricMover::forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02) {
    if (prm_veloVzMv01 < prm_veloVzMv02) {
        _veloTopVzMv = prm_veloVzMv02;
        _veloBottomVzMv = prm_veloVzMv01;
    } else {
        _veloTopVzMv = prm_veloVzMv01;
        _veloBottomVzMv = prm_veloVzMv02;
    }
    setVzMvVelo(_veloVzMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometricMover::setVzMvVelo(velo prm_veloVzMv) {
    if (prm_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (prm_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    } else {
        _veloVzMv = prm_veloVzMv;
    }
}

void GgafDx9GeometricMover::addVzMvVelo(velo prm_veloVzMv) {
    _veloVzMv += prm_veloVzMv;
    if (_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    }
}

void GgafDx9GeometricMover::setVzMvAcce(acce prm_acceVzMv) {
    if (prm_acceVzMv > _acceTopVzMv) {
        _acceVzMv = _acceTopVzMv;
    } else if (prm_acceVzMv < _acceBottomVzMv) {
        _acceVzMv = _acceBottomVzMv;
    } else {
        _acceVzMv = prm_acceVzMv;
    }
}

void GgafDx9GeometricMover::addVzMvAcce(acce prm_acceVzMv) {
    setVzMvAcce(_acceVzMv + prm_acceVzMv);
}


void GgafDx9GeometricMover::forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02) {
    if (prm_acceVzMv01 < prm_acceVzMv02) {
        _acceTopVzMv = prm_acceVzMv02;
        _acceBottomVzMv = prm_acceVzMv01;
    } else {
        _acceTopVzMv = prm_acceVzMv01;
        _acceBottomVzMv = prm_acceVzMv02;
    }
    setVzMvAcce(_acceVzMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9GeometricMover::execTagettingFaceAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                        angvelo prm_angVelo, angacce prm_angAcce,
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

void GgafDx9GeometricMover::execTagettingFaceAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                                        angvelo prm_angVelo, angacce prm_angAcce,
                                                        int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    execTagettingFaceAngSequence(out_angRz_Target, out_angRy_Target,
                                 prm_angVelo, prm_angAcce,
                                 prm_way, prm_optimize_ang);
}

void GgafDx9GeometricMover::execTagettingRzFaceAngSequence(angle prm_angRz_Target,
                                                          angvelo prm_angVelo, angacce prm_angAcce,
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

void GgafDx9GeometricMover::execTagettingRyFaceAngSequence(angle prm_angRy_Target,
                                                          angvelo prm_angVelo, angacce prm_angAcce,
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

void GgafDx9GeometricMover::execTagettingRxSpinAngleSequence(angle prm_angRx_Target,
                                                            angvelo prm_angVelo, angacce prm_angAcce,
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

void GgafDx9GeometricMover::execTagettingMvAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                                      angvelo prm_angVelo, angacce prm_angAcce,
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


void GgafDx9GeometricMover::execTagettingMvAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                                      angvelo prm_angVelo, angacce prm_angAcce,
                                                      int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    GgafDx9Util::getRzRyAng(prm_tX - _pActor->_X,
                            prm_tY - _pActor->_Y,
                            prm_tZ - _pActor->_Z,
                            out_angRz_Target,
                            out_angRy_Target);
    execTagettingMvAngSequence(out_angRz_Target, out_angRy_Target,
                               prm_angVelo, prm_angAcce,
                               prm_way, prm_optimize_ang);
}


void GgafDx9GeometricMover::execTagettingRzMvAngSequence(angle prm_angRz_Target,
                                                        angvelo prm_angVelo, angacce prm_angAcce,
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

void GgafDx9GeometricMover::execTagettingRyMvAngSequence(angle prm_angRy_Target,
                                                        angvelo prm_angVelo, angacce prm_angAcce,
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


void GgafDx9GeometricMover::takeoverMvFrom(GgafDx9GeometricMover* prm_pMover) {
    // �L�����̈ړ����p�P�ʃx�N�g��
    _vX = prm_pMover->_vX;
    _vY = prm_pMover->_vY;
    _vZ = prm_pMover->_vZ;
    // �ړ����p��Z����]�p
    _angRzMv = prm_pMover->_angRzMv;
    // �ړ����p��Y����]�p
    _angRyMv = prm_pMover->_angRyMv;
    // �ړ����x
    _veloMv = prm_pMover->_veloMv;
    // �ړ����x���
    _veloTopMv = prm_pMover->_veloTopMv;
    // �ړ����x����
    _veloBottomMv = prm_pMover->_veloBottomMv;
    // �ړ������x
    _accMv = prm_pMover->_accMv;
    // �ړ����x
    _jerkMv = prm_pMover->_jerkMv;

    // X�������ړ����x
    _veloVxMv = prm_pMover->_veloVxMv;
    // X�������ړ����x���
    _veloTopVxMv = prm_pMover->_veloTopVxMv;
    // X�������ړ����x����
    _veloBottomVxMv = prm_pMover->_veloBottomVxMv;
    // X�������ړ������x
    _acceVxMv = prm_pMover->_acceVxMv;
    // X�������ړ������x���
    _acceTopVxMv = prm_pMover->_acceTopVxMv;
    // X�������ړ������x����
    _acceBottomVxMv = prm_pMover->_acceBottomVxMv;
    // Y�������ړ����x
    _veloVyMv = prm_pMover->_veloVyMv;
    // Y�������ړ����x���
    _veloTopVyMv = prm_pMover->_veloTopVyMv;
    // Y�������ړ����x����
    _veloBottomVyMv = prm_pMover->_veloBottomVyMv;
    // Y�������ړ������x
    _acceVyMv = prm_pMover->_acceVyMv;
    // Y�������ړ������x���
    _acceTopVyMv = prm_pMover->_acceTopVyMv;
    // Y�������ړ������x����
    _acceBottomVyMv = prm_pMover->_acceBottomVyMv;
    // Z�������ړ����x
    _veloVzMv = prm_pMover->_veloVzMv;
    // Z�������ړ����x���
    _veloTopVzMv = prm_pMover->_veloTopVzMv;
    // Z�������ړ����x����
    _veloBottomVzMv = prm_pMover->_veloBottomVzMv;
    // Z�������ړ������x
    _acceVzMv = prm_pMover->_acceVzMv;
    // Z�������ړ������x���
    _acceTopVzMv = prm_pMover->_acceTopVzMv;
    // Z�������ړ������x����
    _acceBottomVzMv = prm_pMover->_acceBottomVzMv;

}

void GgafDx9GeometricMover::resetMv() {
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

    _jerkMv = 0;
    //�ړ����p�iZ����]�j�̊p���x = 0 angle/fream
    _angveloRzMv = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B
    //�ړ����p�iZ����]�j�̊p���x��� = +360,000 angle/fream
    _angveloRzTopMv = ANGLE360; //_angveloRzMv �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p���x���� = -360,000 angle/fream
    _angveloRzBottomMv = ANGLE360 * -1; //_angveloRzMv �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����
    //�ړ����p�iZ����]�j�̊p�����x = 0 angle/fream^2
    _angacceRzMv = 0; //_angveloRzMv �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

    _angjerkRzMv = 0;

    //X�������ړ����x�iX�ړ����W�����j�� 0 px/fream
    _veloVxMv = 0;
    //X�������ړ����x��� �� 256 px/fream
    _veloTopVxMv = 256 * LEN_UNIT;
    //X�������ړ����x���� �� 256 px/fream
    _veloBottomVxMv = -256 * LEN_UNIT;
    //X�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVxMv = 0;
    _acceTopVxMv = 256 * LEN_UNIT;
    _acceBottomVxMv = -256 * LEN_UNIT;
    //Y�������ړ����x�iY�ړ����W�����j�� 0 px/fream
    _veloVyMv = 0;
    //Y�������ړ����x��� �� 256 px/fream
    _veloTopVyMv = 256 * LEN_UNIT;
    //Y�������ړ����x���� �� 256 px/fream
    _veloBottomVyMv = -256 * LEN_UNIT;
    //Y�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVyMv = 0;

    _acceTopVyMv = 256 * LEN_UNIT;
    _acceBottomVyMv = -256 * LEN_UNIT;

    //Z�������ړ����x�iZ�ړ����W�����j�� 0 px/fream
    _veloVzMv = 0;
    //Z�������ړ����x��� �� 256 px/fream
    _veloTopVzMv = 256 * LEN_UNIT;
    //Z�������ړ����x���� �� 256 px/fream
    _veloBottomVzMv = -256 * LEN_UNIT;
    //Z�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVzMv = 0;
    _acceTopVzMv = 256 * LEN_UNIT;
    _acceBottomVzMv = -256 * LEN_UNIT;
}

GgafDx9GeometricMover::~GgafDx9GeometricMover() {
}
