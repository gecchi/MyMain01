#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


RefractionLaserChip::RefractionLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "RefractionLaserChip";
    _is_leader = false;
    _num_refraction = 2;
    _frame_standstill = 10;
    _frame_refraction_interval = 20;

    _cnt_refraction = 0;
    _frame_refraction_enter = 0;
    _frame_refraction_outer = 0;
    _isRefracting = false;
}

void RefractionLaserChip::initialize() {
    //�����ݒ�ł��B
    //30px/frame �̈ړ����x
    //�����蔻�肠��B
    //����0.99
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    _pMover->setMoveVelocity(30000);
    _fAlpha = 0.99;
}


void RefractionLaserChip::onActive() {
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();


    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
    //���[�U�[�`�b�v�o��������
    if (pChip_front == NULL) {
        _is_leader = true;
        //���g���擪�̏ꍇ
        _begining_X = _X;
        _begining_Y = _Y;
        _begining_Z = _Z;
        _begining_RX = _RX;
        _begining_RY = _RY;
        _begining_RZ = _RZ;
        _cnt_refraction = 0;
        _frame_refraction_enter = _frame_of_active + _frame_refraction_interval;
        _frame_refraction_outer = _frame_refraction_enter + _frame_standstill;
    } else {
        _is_leader = false;
        _begining_X = pChip_front->_begining_X;
        _begining_Y = pChip_front->_begining_Y;
        _begining_Z = pChip_front->_begining_Z;
        _begining_RX = pChip_front->_begining_RX;
        _begining_RY = pChip_front->_begining_RY;
        _begining_RZ = pChip_front->_begining_RZ;

        _X = _begining_X;
        _Y = _begining_Y;
        _Z = _begining_Z;
        _RX = _begining_RX;
        _RY = _begining_RY;
        _RZ = _begining_RZ;
        _cnt_refraction = INT_MAX;
        _frame_refraction_enter = INT_MAX;
        _frame_refraction_outer = INT_MAX;
    }
    onRefraction(_cnt_refraction);

    _isRefracting = false;
}

void RefractionLaserChip::onInactive() {
    //���[�U�[�`�b�v����������

    //�����̃`�b�v������΁A�����̈ӎv�i�ړ��Ȃǁj�������p������
    //����́A���[�U�[�������ꂽ�ꍇ�A�ȉ��̃p�����[�^�[�݈̂����p�����A�ړ����p�������邽�߁B
    //�����x�Ȃ�A�ړ��\��Ȃǈ����p����Ȃ����̂���������̂ŁA���G�Ȉړ�������ۂ́A�R�R�ɒ��ӂ𕥂����ƁI
    //���[�U�[���Q�[���̈�O�ɂ��������Ƃ����A�擪�`�b�v���珇�ɘA���ň��p�����������邱�ƂɂȂ�B
    //������Ɩ��ʂ��ۂ����ǁA�����Ȃΐ擪�̎��̃`�b�v���̈�O�Ɍ������Ĉړ�����Ƃ͌���Ȃ��̂ŁA��͂�K�v�B
    if (_pChip_behind) {
        _pChip_behind->_pMover->_vX = _pMover->_vX;
        _pChip_behind->_pMover->_vY = _pMover->_vY;
        _pChip_behind->_pMover->_vZ = _pMover->_vZ;
        _pChip_behind->_pMover->_angRzMove = _pMover->_angRzMove;
        _pChip_behind->_pMover->_angRyMove = _pMover->_angRyMove;
        _pChip_behind->_pMover->_veloMove = _pMover->_veloMove;
        _pChip_behind->_pMover->_angFace[AXIS_X] = _pMover->_angFace[AXIS_X];
        _pChip_behind->_pMover->_angFace[AXIS_Y] = _pMover->_angFace[AXIS_Y];
        _pChip_behind->_pMover->_angFace[AXIS_Z] = _pMover->_angFace[AXIS_Z];
    }

    LaserChip::onInactive(); //�Ȃ����ؒf����
}

void RefractionLaserChip::processBehavior() {
    LaserChip::processBehavior();

    //���[�U�[�`�b�v����������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
    _dwActiveFrame++;
    //���W�ɔ��f
    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
    if (_dwActiveFrame > 1) {
        //ActorDispatcher::employ() ��
        //�擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ������B
        //���������āA���[�U�[�̐擪���珇�Ԃ�processBehavior() ���Ă΂�邽�߁A�ȉ��̂悤�ɂ����
        //����q���ɂȂ�B
        if (pChip_front == NULL) {
            //�{���̐擪�`�b�v���A�����͂ɂ킩�擪�`�b�v�̏ꍇ�̋��ʏ���
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;

		    if (_isRefracting) {
		        if (_frame_of_active >= _frame_refraction_outer) {
		            _cnt_refraction++;
		            RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
		            if (_cnt_refraction <= _num_refraction && pChip_front == NULL) {
		                onRefraction(_cnt_refraction);
                        _frame_refraction_enter = _frame_of_active + _frame_refraction_interval;
                        _frame_refraction_outer = _frame_refraction_enter + _frame_standstill;
		            } else {
		                _cnt_refraction = INT_MAX;
		                _frame_refraction_enter = INT_MAX;
		                _frame_refraction_outer = INT_MAX;
		            }
		            _isRefracting = false;
                } else {
                    return;
                }
		    }
            _pMover->behave();
        } else {
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;
            _X  = pChip_front->_prev_X;
            _Y  = pChip_front->_prev_Y;
            _Z  = pChip_front->_prev_Z;
            _RX = pChip_front->_prev_RX;
            _RY = pChip_front->_prev_RY;
            _RZ = pChip_front->_prev_RZ;
        }
    }
    if (_frame_of_active >= _frame_refraction_enter) {
        _isRefracting = true;
    }
}

void RefractionLaserChip::processJudgement() {
    LaserChip::processJudgement();
    GgafDx9Util::calcWorldMatrix_RxRzRyScMv(this, _matWorld);
}

RefractionLaserChip::~RefractionLaserChip() {
}

