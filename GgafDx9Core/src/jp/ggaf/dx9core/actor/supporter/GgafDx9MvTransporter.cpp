#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

// �y�����z�{�N���X�̍l�����ƒP��̕\��
//
// ���Q��ނ̕�����
// �u�L�����̕����v�Ƃ������t���B���Ȃ��߁A���̂Q��ނ̒P����`����B�u�ړ����p�i�����j�v�Ɓu����]���p�i�����j�v�B
// �u�ړ����p�i�����j�v�̓L�����̐i�s�����݂̂�\������B����́u�ړ����x�v�Ɣ����āA�L�����͍��W�����ړ����邱�ƂƂ���B
// �u����]���p�i�����j�v�̓L�����̌����i�O���������j�݂̂�\�����鎖�Ƃ���B
// �L�����N�^����ʂ̏㕔���牺���ֈړ����Ă��A�L�����N�^�͉��������Ƃ͌��炸���@�Ɍ����Ăق����ꍇ������B
// �܂��́A�E�ɃL�������������āA���Ɉړ������������Ƃ�����B���ꂼ��Q�̕����ݒ肪�K�v�B
//
// ���ړ����p�i�����j�̂Q��ނ̕\�����@��
// �L�������i�ޕ����A�܂�ړ����p�̕����́A���_����P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g�� (_vX, _vY, _vZ) �ŕ\�����@�ƁA
// �Q�̎���]�A���O���l (_angRzMv, _angRyMv) �ŕ\�����@�̂Q��ޗp�ӂ����B�N�H�[�^�j�I���͍��̂Ƃ��떳���B
// _angRzMv �� Z����]�p�A _angRyMv �� Y����]�p ���Ӗ����Ă���B�����Ƃ�0�x���A�����x�N�g��(1, 0, 0) �̕����ƒ�`����B
// ����͕����x�N�g�����A�ܓx�ƌo�x�A�i�p�ƃA�W�}�X�j�̊֌W�Ɍ����āA�Ή������悤�Ƃ����݌v�B
// ���ӂ��邱�Ƃ́AY����]�p���o�x �͏�ɐ��藧���AZ����]�p���ܓx �́AZ����]�p �� Y����]�p�̏��Ԃł���ꍇ�Ɍ��萬�藧�B
// (�� Y����]�p �� Z����]�p �̏��Ԃŉ�]�������ꍇ�AZ����]�p���ܓx �ƂȂ�Ȃ��Ƃ����Ӗ�)
// �{�N���X�ł́A�uZ����] �� Y����]�̏��Ԃł�Z����]�p�v���ȗ����āA�P�ɁuZ����]�p�v�ƕ\�����鎖�Ƃ���B
// �������ʂɕ\���������ꍇ�́A���ꂼ��u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�Ə������Ƃɂ���B
//
// �\�[�X�R�[�h���́A�ϐ��⃁�\�b�h��
// �uRz�v�Ƃ����\�L�́u�ړ����p�iZ���j�i�A��Z����] �� Y����]�̏��ԁj�v���Ӗ����Ă���B
// �uRy�v�Ƃ����\�L�́u�ړ����p�iY���j�v���Ӗ����Ă���B
// �uRzRy�v�Ƃ����\���́uZ����] �� Y����]�̏��Ԃ̈ړ����p�v��\���Ă���B
//
// Z����]�p�AY����]�p�������Ƃ�0�x���A�����x�N�g��(1, 0, 0) �̕����ƒ�`����B
// Z����]�p�̐��̑����́AZ���̐��̕����������Ĕ����v���B
// Y����]�p�̐��̑����́AY���̐��̕����������Ĕ����v���B�Ƃ���B
//
// �u�ړ����p�v�ɂ�Z����]�p��Y����]�p�ɂ��w��(_angRzMv, _angRyMv)�ƒP�ʃx�N�g���w��(_vX, _vY, _vZ) ������Ɛ����������A
// �u���p�v�𕁒ʂɍl�����ꍇ�́A���Ԉ�ʂł͕����x�N�g���iXYZ�̒l�j�̂��Ƃ��w�����Ƃ������Ǝv���B
// ���������̃N���X�ł́A�悭�g���̂͑O�҂̕��ŁA�{�N���X�̃��\�b�h�� _angRzMv �� _angRyMv �𑀍삷����̂��قƂ�ǂł���B
// �������A�ŏI�I�ɂ� ���[���h�ϊ��s����쐬���邽�߁A�u�P�ʃx�N�g��(_vX, _vY, _vZ)*�ړ����x �v�Ƃ����v�Z������K�v������B
// ���ǂ͒P�ʃx�N�g�������߂Ă���̂����A���W��]�v�Z���A�����^�� _angRzMv �� _angRyMv �ł��񂴂�s���Ă���A
// �Ō�ɂP��P�ʃx�N�g�������߂�B�Ƃ������������̂ł͂ƍl�������߁A���̂悤�Ȑ݌v�ɂȂ����B
// TODO:�œK���̗]�n�����Ԏc���Ă���i���A�܂������j�B
//
// �{�N���X���C�u�����ł́A����(_angRzMv, _angRyMv)����ɑ��삵�āA�����ŕ����x�N�g��(_vX, _vY, _vZ) �𓯊������Ă���B
// (_vX, _vY, _vZ)�݂̂����\�b�h���g�킸���ڑ��삷��ƁA(_angRzMv, _angRyMv)�Ƃ̓����������̂Œ��ӁB
// �{�N���X�̃��\�b�h���g�p�������ł́A����Ȃ��Ƃ͋N����Ȃ����ƂƂ���B
//
// ���ړ����x:Velo or MvVelo��
// �L�����́u�ړ����x�v(_veloMv)��ێ����Ă���B�ړ�������@�͊ȒP�ŁA��{�I�ɖ��t���[���u�ړ����p�v�Ɂu�ړ����x�v�����������B
// �܂�u�ړ����p�v(_vX, _vY, _vZ)�Ɂu�ړ����x�v(_veloMv)���|���Z���Ă���B�P�t���[����̍��W��
// (_vX*_veloMv, _vY*_veloMv, _vZ*_veloMv) �ł���B  ����ɖ{���C�u�����̒P�ʋ���(�Q�[�����̒����P�ƍl���鐮���{�l�j���|����B
// ����āA(_vX*_veloMv*LEN_UNIT, _vY*_veloMv*LEN_UNIT, _vZ*_veloMv*LEN_UNIT)���P�t���[����̍��W�B

// ������]���p:AngFace��
// �L�����̃��[�J�����W�Ō����Ă�����p�i�����j���u����]���p�v�ƌĂԂ��Ƃɂ���B
//�u����]���p�v�́A���[���h�ϊ��s��̎���]�Ɠ�����]���@�Ƃ���B
// ���[���h�ϊ��s��̎���]�Ƃ́AX����]�p�AY����]�p�AZ����]�p�̂��ƂŁA���ꂼ��A
// _angFace[AXIS_X], _angFace[AXIS_Y], _angFace[AXIS_Z] ���ێ����Ă���B
// �{���C�u�����ł́A�L�������̃��[�J�����W�n�̒P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g��(1, 0, 0) ���L�����́u�O���v�Ɛݒ肵�Ă���B
// X�t�@�C���Ȃǂ̃��b�V�����f�����AX���̐��̕����Ɍ����Ă��郂�m�Ƃ���B�܂��A���f���u������́v�́i0, 1, 0)�Ƃ���B
// ���[���h�ϊ��s��̉�]�s��̊|���鏇�Ԃ́A��{�I�� �uX����]�s�� > Z����]�s�� > Y����]�s�� > �ړ��s�� > (�g��k��) �v �Ƃ���B
// (��  X�� > Y�� > Z�� �̏��ł͂Ȃ���I�j
// ����āAX����]�p�͊���]�����悤�Ƃ��A�L�����������Ă�������͕ς�炸�A�c���Z����]�p�ƁAY����]�p�ŃL�����������Ă�����������肷�邱�ƂƂ���B
// X����]�p�̓L�����̃X�s���A�̂���Q�p�iZ����]�p�EY����]�p�j�ŃL�����́u�O���v���p�������肷��Ƃ����ꍇ�A
// �u����]���p�v����قǂ́u�ړ����p�v�Ɠ����悤�ɁAZ����]�p��Y����]�p�i�ܓx�ƌo�x)�̂Q�̃A���O���l
// (_angFace[AXIS_Z], _angFace[AXIS_Y])�ŕ\���ł���B
// �܂�A�u�O���v�� Z����]�p�EY����]�p����0�x�Ƃ��A�Ⴆ�΁u���v��[Z����]�p,Y����]�p]=[0�x,180�x] �ƕ\������B�B
// �P�ɁuZ����]�p�v�ȂǂƏ����ƁA�u�ړ����p�v��Z����]�p�Ȃ̂��A�u����]���p�v��Z����]�p�Ȃ̂��B���ɂȂ邽�߁A
// �u����]���p(Z��)�v�u����]���p(Y��)�v�Ə������ƂƂ���B�i���u����]���p(X��)�v�����邪�A����̓X�s����\�������ւ̉e���͖����j
// �����Œ��ӂ́A�P�̃L�����������Ă�����p�ɑ΂��āA���͂Q�ʂ�̃A�N�Z�X������@������Ƃ������ƁB�Ⴆ�΁A
// �u�O��(1, 0, 0)�������Đ^�E�����v �� [����]���p(Z��), ����]���p(Y��)]=[0, 90�x] or [180�x,270�x] �Ƃŕ\���ł���B
// �i������]���p(Y��)�͍���n���W�̂���Y���̐������������Ĕ����v���j
// ���� �u�O���v �� [180�x,180�x]�Ƃ��\���ł��邵�A�u�^���v �� [0�x,180�x] �Ƃ� [180�x,0�x] �Ƃ��\���ł���B
// �ǂ���������Ă�������͓��������A�p��(�L�����̏����)���قȂ�B�p�����قȂ�Ƃ܂����L�����͒��ӂ��邱�ƁB
// ���R�A�u�ړ����p�v�ł��A�Q�ʂ�̃A�N�Z�X������@������̂����A������͌����ڂ͍��������B�����������p�x�v�Z����Ƃ��ɉe�����ł�������Ȃ��B


// �������O�������@�\��
// ���Ă����� �u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v���A���ꂼ��u����]���p(Z��)�v�u����]���p(Y��)�v �փR�s�[���Ă��ƁA
// �Ȃ�ƈړ����p�ƁA�L�����N�^�̌����̓������ȒP�Ɏ��邶��Ȃ����I
// �u�����O�������@�\�v�Ƃ́A�u�ړ����p�v��ݒ肷��ƁA����ɔ����Ď����I�Ɂu����]���p�v��ݒ肷�鎖�Ƃ���B
// ��̓I�ɂ́A�ȉ��̂悤�Ƀt���[�����ɁA�A���O���l���㏑���R�s�[�i�����j�B�����͍��������Z�i�������������炩�ɕ`��j���Ă����B
//  �E�ړ����p�iZ���j �� ����]���p(Z��)
//  �E�ړ����p�iY���j �� ����]���p(Y��)
// �������u����]���p�v��ݒ�Ă��u�ړ����p�v�ω����Ȃ��i�t�͊֘A���Ȃ��j�̂Œ��ӁB

// ���p���x:AngVelo��
// �u�ړ����p�iZ���j�v�u�ړ����p�iY���j�v�A�u����]���p(Z��)�v�u����]���p(Y��)�v�ɂ́A���ꂼ��́u�p���x�v��݂��Ă���B
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
//�E�X�v���C���̊�_�A��ԓ_�������Œʉ߂���悤�ȓ������ŋ߉\�ɂȂ����B�i�ŋ߂��Ă��G�j
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



GgafDx9MvTransporter::GgafDx9MvTransporter(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;

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

    _gravitation_mv_seq_target_X = 0;
    _gravitation_mv_seq_target_Y = 0;
    _gravitation_mv_seq_target_Z = 0;
    _gravitation_mv_seq_pActor_target = NULL;
    _gravitation_mv_seq_max_velo = 1000;
    _gravitation_mv_seq_acce = 1000;
    _gravitation_mv_seq_stop_renge = 1000;
    _gravitation_mv_seq_flg = false;

}

void GgafDx9MvTransporter::behave() {



    if(_gravitation_mv_seq_flg) {
        int dX, dY, dZ;
        if (_gravitation_mv_seq_pActor_target) {
            dX = _gravitation_mv_seq_pActor_target->_X - _pActor->_X;
            dY = _gravitation_mv_seq_pActor_target->_Y - _pActor->_Y;
            dZ = _gravitation_mv_seq_pActor_target->_Z - _pActor->_Z;
        } else {
            dX = _gravitation_mv_seq_target_X - _pActor->_X;
            dY = _gravitation_mv_seq_target_Y - _pActor->_Y;
            dZ = _gravitation_mv_seq_target_Z - _pActor->_Z;
        }

        velo last_veloVxMv = _veloVxMv;
        velo new_veloVxMv = _gravitation_mv_seq_max_velo * (dX * 1.0 / _gravitation_mv_seq_stop_renge);
        if (last_veloVxMv - _gravitation_mv_seq_acce <= new_veloVxMv &&
                                                        new_veloVxMv <= last_veloVxMv + _gravitation_mv_seq_acce) {
            _veloVxMv = new_veloVxMv;
        } else {
            if (last_veloVxMv - _gravitation_mv_seq_acce > new_veloVxMv) {
                _veloVxMv = last_veloVxMv - _gravitation_mv_seq_acce;
            } else if (new_veloVxMv > last_veloVxMv + _gravitation_mv_seq_acce) {
                _veloVxMv = last_veloVxMv + _gravitation_mv_seq_acce;
            }
        }

        velo last_veloVyMv = _veloVyMv;
        velo new_veloVyMv = _gravitation_mv_seq_max_velo * (dY * 1.0 / _gravitation_mv_seq_stop_renge);
        if (last_veloVyMv - _gravitation_mv_seq_acce <= new_veloVyMv &&
                                                        new_veloVyMv <= last_veloVyMv + _gravitation_mv_seq_acce) {
            _veloVyMv = new_veloVyMv;
        } else {
            if (last_veloVyMv - _gravitation_mv_seq_acce > new_veloVyMv) {
                _veloVyMv = last_veloVyMv - _gravitation_mv_seq_acce;
            } else if (new_veloVyMv > last_veloVyMv + _gravitation_mv_seq_acce) {
                _veloVyMv = last_veloVyMv + _gravitation_mv_seq_acce;
            }
        }

        velo last_veloVzMv = _veloVzMv;
        velo new_veloVzMv = _gravitation_mv_seq_max_velo * (dZ * 1.0 / _gravitation_mv_seq_stop_renge);
        if (last_veloVzMv - _gravitation_mv_seq_acce <= new_veloVzMv &&
                                                        new_veloVzMv <= last_veloVzMv + _gravitation_mv_seq_acce) {
            _veloVzMv = new_veloVzMv;
        } else {
            if (last_veloVzMv - _gravitation_mv_seq_acce > new_veloVzMv) {
                _veloVzMv = last_veloVzMv - _gravitation_mv_seq_acce;
            } else if (new_veloVzMv > last_veloVzMv + _gravitation_mv_seq_acce) {
                _veloVzMv = last_veloVzMv + _gravitation_mv_seq_acce;
            }
        }
    }


    //X�������ړ������x�̏���
    _veloVxMv += _acceVxMv;
    setVxMvVelo(_veloVxMv);
    //Y�������ړ������x�̏���
    _veloVyMv += _acceVyMv;
    setVyMvVelo(_veloVyMv);
    //Z�������ړ������x�̏���
    _veloVzMv += _acceVzMv;
    setVzMvVelo(_veloVzMv);

    //Actor�ɔ��f
    _pActor->_X += _veloVxMv;
    _pActor->_Y += _veloVyMv;
    _pActor->_Z += _veloVzMv;


}



void GgafDx9MvTransporter::forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02) {
    if (prm_veloVxMv01 < prm_veloVxMv02) {
        _veloTopVxMv = prm_veloVxMv02;
        _veloBottomVxMv = prm_veloVxMv01;
    } else {
        _veloTopVxMv = prm_veloVxMv01;
        _veloBottomVxMv = prm_veloVxMv02;
    }
    setVxMvVelo(_veloVxMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9MvTransporter::setVxMvVelo(velo prm_veloVxMv) {
    if (prm_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (prm_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    } else {
        _veloVxMv = prm_veloVxMv;
    }
}

void GgafDx9MvTransporter::addVxMvVelo(velo prm_veloVxMv) {
    _veloVxMv += prm_veloVxMv;
    if (_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    }
}

void GgafDx9MvTransporter::setVxMvAcce(acce prm_acceVxMv) {
    if (prm_acceVxMv > _acceTopVxMv) {
        _acceVxMv = _acceTopVxMv;
    } else if (prm_acceVxMv < _acceBottomVxMv) {
        _acceVxMv = _acceBottomVxMv;
    } else {
        _acceVxMv = prm_acceVxMv;
    }
}

void GgafDx9MvTransporter::addVxMvAcce(acce prm_acceVxMv) {
    setVxMvAcce(_acceVxMv + prm_acceVxMv);
}


void GgafDx9MvTransporter::forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02) {
    if (prm_acceVxMv01 < prm_acceVxMv02) {
        _acceTopVxMv = prm_acceVxMv02;
        _acceBottomVxMv = prm_acceVxMv01;
    } else {
        _acceTopVxMv = prm_acceVxMv01;
        _acceBottomVxMv = prm_acceVxMv02;
    }
    setVxMvAcce(_acceVxMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}


void GgafDx9MvTransporter::forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02) {
    if (prm_veloVyMv01 < prm_veloVyMv02) {
        _veloTopVyMv = prm_veloVyMv02;
        _veloBottomVyMv = prm_veloVyMv01;
    } else {
        _veloTopVyMv = prm_veloVyMv01;
        _veloBottomVyMv = prm_veloVyMv02;
    }
    setVyMvVelo(_veloVyMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9MvTransporter::setVyMvVelo(velo prm_veloVyMv) {
    if (prm_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (prm_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    } else {
        _veloVyMv = prm_veloVyMv;
    }
}

void GgafDx9MvTransporter::addVyMvVelo(velo prm_veloVyMv) {
    _veloVyMv += prm_veloVyMv;
    if (_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    }
}

void GgafDx9MvTransporter::setVyMvAcce(acce prm_acceVyMv) {
    if (prm_acceVyMv > _acceTopVyMv) {
        _acceVyMv = _acceTopVyMv;
    } else if (prm_acceVyMv < _acceBottomVyMv) {
        _acceVyMv = _acceBottomVyMv;
    } else {
        _acceVyMv = prm_acceVyMv;
    }
}

void GgafDx9MvTransporter::addVyMvAcce(acce prm_acceVyMv) {
    setVyMvAcce(_acceVyMv + prm_acceVyMv);
}


void GgafDx9MvTransporter::forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02) {
    if (prm_acceVyMv01 < prm_acceVyMv02) {
        _acceTopVyMv = prm_acceVyMv02;
        _acceBottomVyMv = prm_acceVyMv01;
    } else {
        _acceTopVyMv = prm_acceVyMv01;
        _acceBottomVyMv = prm_acceVyMv02;
    }
    setVyMvAcce(_acceVyMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9MvTransporter::forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02) {
    if (prm_veloVzMv01 < prm_veloVzMv02) {
        _veloTopVzMv = prm_veloVzMv02;
        _veloBottomVzMv = prm_veloVzMv01;
    } else {
        _veloTopVzMv = prm_veloVzMv01;
        _veloBottomVzMv = prm_veloVzMv02;
    }
    setVzMvVelo(_veloVzMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDx9MvTransporter::setVzMvVelo(velo prm_veloVzMv) {
    if (prm_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (prm_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    } else {
        _veloVzMv = prm_veloVzMv;
    }
}

void GgafDx9MvTransporter::addVzMvVelo(velo prm_veloVzMv) {
    _veloVzMv += prm_veloVzMv;
    if (_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    }
}

void GgafDx9MvTransporter::setVzMvAcce(acce prm_acceVzMv) {
    if (prm_acceVzMv > _acceTopVzMv) {
        _acceVzMv = _acceTopVzMv;
    } else if (prm_acceVzMv < _acceBottomVzMv) {
        _acceVzMv = _acceBottomVzMv;
    } else {
        _acceVzMv = prm_acceVzMv;
    }
}

void GgafDx9MvTransporter::addVzMvAcce(acce prm_acceVzMv) {
    setVzMvAcce(_acceVzMv + prm_acceVzMv);
}


void GgafDx9MvTransporter::forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02) {
    if (prm_acceVzMv01 < prm_acceVzMv02) {
        _acceTopVzMv = prm_acceVzMv02;
        _acceBottomVzMv = prm_acceVzMv01;
    } else {
        _acceTopVzMv = prm_acceVzMv01;
        _acceBottomVzMv = prm_acceVzMv02;
    }
    setVzMvAcce(_acceVzMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}



void GgafDx9MvTransporter::forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02) {
    forceVxMvVeloRange(prm_veloVxyzMv01, prm_veloVxyzMv02);
    forceVyMvVeloRange(prm_veloVxyzMv01, prm_veloVxyzMv02);
    forceVzMvVeloRange(prm_veloVxyzMv01, prm_veloVxyzMv02);
}
void GgafDx9MvTransporter::forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02) {
    forceVxMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
    forceVyMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
    forceVzMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
}











void GgafDx9MvTransporter::orderGravitationVxyzMvSequence(
        int prm_tX, int prm_tY, int prm_tZ,
        velo prm_max_velo,
        acce prm_acce,
        int prm_stop_renge
        ) {
    _gravitation_mv_seq_target_X = prm_tX;
    _gravitation_mv_seq_target_Y = prm_tY;
    _gravitation_mv_seq_target_Z = prm_tZ;
    _gravitation_mv_seq_pActor_target = NULL;
    _gravitation_mv_seq_max_velo = prm_max_velo;
    _gravitation_mv_seq_acce = prm_acce;
    _gravitation_mv_seq_stop_renge = prm_stop_renge;
    _gravitation_mv_seq_flg = true;

    forceVxMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVyMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVzMvVeloRange(-prm_max_velo, prm_max_velo);
}

void GgafDx9MvTransporter::orderGravitationVxyzMvSequence(
        GgafDx9GeometricActor* prm_pActor_target,
        velo prm_max_velo,
        acce prm_acce,
        int prm_stop_renge
        ) {
    _gravitation_mv_seq_target_X = 0;
    _gravitation_mv_seq_target_Y = 0;
    _gravitation_mv_seq_target_Z = 0;
    _gravitation_mv_seq_pActor_target = prm_pActor_target;
    _gravitation_mv_seq_max_velo = prm_max_velo;
    _gravitation_mv_seq_acce = prm_acce;
    _gravitation_mv_seq_stop_renge = prm_stop_renge;
    _gravitation_mv_seq_flg = true;

    forceVxMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVyMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVzMvVeloRange(-prm_max_velo, prm_max_velo);
}



void GgafDx9MvTransporter::takeoverMvFrom(GgafDx9MvTransporter* prm_pMvTransporter) {

    // X�������ړ����x
    _veloVxMv = prm_pMvTransporter->_veloVxMv;
    // X�������ړ����x���
    _veloTopVxMv = prm_pMvTransporter->_veloTopVxMv;
    // X�������ړ����x����
    _veloBottomVxMv = prm_pMvTransporter->_veloBottomVxMv;
    // X�������ړ������x
    _acceVxMv = prm_pMvTransporter->_acceVxMv;
    // X�������ړ������x���
    _acceTopVxMv = prm_pMvTransporter->_acceTopVxMv;
    // X�������ړ������x����
    _acceBottomVxMv = prm_pMvTransporter->_acceBottomVxMv;
    // Y�������ړ����x
    _veloVyMv = prm_pMvTransporter->_veloVyMv;
    // Y�������ړ����x���
    _veloTopVyMv = prm_pMvTransporter->_veloTopVyMv;
    // Y�������ړ����x����
    _veloBottomVyMv = prm_pMvTransporter->_veloBottomVyMv;
    // Y�������ړ������x
    _acceVyMv = prm_pMvTransporter->_acceVyMv;
    // Y�������ړ������x���
    _acceTopVyMv = prm_pMvTransporter->_acceTopVyMv;
    // Y�������ړ������x����
    _acceBottomVyMv = prm_pMvTransporter->_acceBottomVyMv;
    // Z�������ړ����x
    _veloVzMv = prm_pMvTransporter->_veloVzMv;
    // Z�������ړ����x���
    _veloTopVzMv = prm_pMvTransporter->_veloTopVzMv;
    // Z�������ړ����x����
    _veloBottomVzMv = prm_pMvTransporter->_veloBottomVzMv;
    // Z�������ړ������x
    _acceVzMv = prm_pMvTransporter->_acceVzMv;
    // Z�������ړ������x���
    _acceTopVzMv = prm_pMvTransporter->_acceTopVzMv;
    // Z�������ړ������x����
    _acceBottomVzMv = prm_pMvTransporter->_acceBottomVzMv;

}

void GgafDx9MvTransporter::resetMv() {


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

GgafDx9MvTransporter::~GgafDx9MvTransporter() {
}
