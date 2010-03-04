#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


HomingLaserChip::HomingLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "HomingLaserChip";
    _is_leader = false;
}

void HomingLaserChip::initialize() {
    //�����ݒ�ł��B
    //30px/frame �̈ړ����x
    //�����蔻�肠��B
    //����0.99
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    _pMover->setMvVelo(30000);
    _fAlpha = 0.99;
}


void HomingLaserChip::onActive() {
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;

    //���[�U�[�`�b�v�o��������
    if (pChip_front == NULL) {
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front == NULL");
        _is_leader = true;
        //���g���擪�̏ꍇ
        _begining_X = _X;
        _begining_Y = _Y;
        _begining_Z = _Z;
        _begining_RX = _RX;
        _begining_RY = _RY;
        _begining_RZ = _RZ;
    } else {
        _is_leader = false;
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front =="<<(pChip_front->getName()));
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
    }




}

void HomingLaserChip::onInactive() {
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
        _pChip_behind->_pMover->_angRzMv = _pMover->_angRzMv;
        _pChip_behind->_pMover->_angRyMv = _pMover->_angRyMv;
        _pChip_behind->_pMover->_veloMv = _pMover->_veloMv;
        _pChip_behind->_pMover->_angFace[AXIS_X] = _pMover->_angFace[AXIS_X];
        _pChip_behind->_pMover->_angFace[AXIS_Y] = _pMover->_angFace[AXIS_Y];
        _pChip_behind->_pMover->_angFace[AXIS_Z] = _pMover->_angFace[AXIS_Z];
    }

    LaserChip::onInactive(); //�Ȃ����ؒf����
}

void HomingLaserChip::processBehavior() {
    LaserChip::processBehavior();

    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
    //���W�ɔ��f
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;
    if (getPartFrame() > 1) {
        //GgafActorDispatcher::employ() ��
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
//            _prev_vX = _pMover->_vX;
//            _prev_vY = _pMover->_vY;
//            _prev_vZ = _pMover->_vZ;
//            _prev_RzMvAng = _pMover->_angRzMv;
//            _prev_RyMvAng = _pMover->_angRyMv;

            processBehaviorHeadChip();
        } else {

            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;
//            _prev_vX = _pMover->_vX;
//            _prev_vY = _pMover->_vY;
//            _prev_vZ = _pMover->_vZ;
//            _prev_RzMvAng = _pMover->_angRzMv;
//            _prev_RyMvAng = _pMover->_angRyMv;

            _X  = pChip_front->_prev_X;
            _Y  = pChip_front->_prev_Y;
            _Z  = pChip_front->_prev_Z;
            _RX = pChip_front->_prev_RX;
            _RY = pChip_front->_prev_RY;
            _RZ = pChip_front->_prev_RZ;
//            _pMover->_vX = pChip_front->_prev_vX;
//            _pMover->_vY = pChip_front->_prev_vY;
//            _pMover->_vZ = pChip_front->_prev_vZ;
//            _pMover->_angRzMv = pChip_front->_prev_RzMvAng;
//            _pMover->_angRyMv = pChip_front->_prev_RyMvAng;
        }
    }
}

void HomingLaserChip::processJudgement() {
    LaserChip::processJudgement();
    GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

HomingLaserChip::~HomingLaserChip() {
}

