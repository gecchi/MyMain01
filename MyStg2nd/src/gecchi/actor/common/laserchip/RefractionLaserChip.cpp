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

    _pDispatche_RefractionEffect = NULL;
    _pRefractionEffect = NULL;
    _prev_pRefractionEffect = NULL;
}

void RefractionLaserChip::initialize() {
    //�����ݒ�ł��B
    //30px/frame �̈ړ����x
    //�����蔻�肠��B
    //����0.99
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    _pMover->setMvVelo(30000);
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
        _frame_refraction_enter = getBehaveingFrame() + _frame_refraction_interval;
        _frame_refraction_outer = _frame_refraction_enter + _frame_standstill;
		onRefractionEnterHeadChip(_cnt_refraction); //0��ڂ̋���
		onRefractionOutHeadChip(_cnt_refraction);
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
        _cnt_refraction = 0;
        _frame_refraction_enter = INT_MAX;
        _frame_refraction_outer = INT_MAX;
    }

    _isRefracting = false;
    _prev_isRefracting = false;
}

void RefractionLaserChip::onInactive() {
    //���[�U�[�`�b�v����������

    //�����̃`�b�v������΁A�����̈ӎv�i�ړ��Ȃǁj�������p������
    //����́A���[�U�[�������ꂽ�ꍇ�A�ȉ��̃p�����[�^�[�݈̂����p�����A�ړ����p�������邽�߁B
    //�����x�Ȃ�A�ړ��\��Ȃǈ����p����Ȃ����̂���������̂ŁA���G�Ȉړ�������ۂ́A�R�R�ɒ��ӂ𕥂����ƁI
    //���[�U�[���Q�[���̈�O�ɂ��������Ƃ����A�擪�`�b�v���珇�ɘA���ň��p�����������邱�ƂɂȂ�B
    //������Ɩ��ʂ��ۂ����ǁA�����Ȃΐ擪�̎��̃`�b�v���̈�O�Ɍ������Ĉړ�����Ƃ͌���Ȃ��̂ŁA��͂�K�v�B
    if (_pChip_behind) {
        RefractionLaserChip* pChip = (RefractionLaserChip*)_pChip_behind;
        pChip->_pMover->_vX = _pMover->_vX;
        pChip->_pMover->_vY = _pMover->_vY;
        pChip->_pMover->_vZ = _pMover->_vZ;
        pChip->_pMover->_angRzMv = _pMover->_angRzMv;
        pChip->_pMover->_angRyMv = _pMover->_angRyMv;
        pChip->_pMover->_veloMv = _pMover->_veloMv;
        pChip->_pMover->_angFace[AXIS_X] = _pMover->_angFace[AXIS_X];
        pChip->_pMover->_angFace[AXIS_Y] = _pMover->_angFace[AXIS_Y];
        pChip->_pMover->_angFace[AXIS_Z] = _pMover->_angFace[AXIS_Z];
        pChip->_cnt_refraction = _cnt_refraction;
        pChip->_frame_refraction_enter = _frame_refraction_enter;
        pChip->_frame_refraction_outer = _frame_refraction_outer;
        pChip->_isRefracting = _isRefracting;
    }

    LaserChip::onInactive(); //�Ȃ����ؒf����
}

void RefractionLaserChip::processBehavior() {
    LaserChip::processBehavior();

    //���[�U�[�`�b�v����������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
    //���W�ɔ��f
    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
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
            _prev_isRefracting = _isRefracting;
            _prev_pRefractionEffect = _pRefractionEffect;

            _pRefractionEffect = NULL;
            if (!_isRefracting) {
                if (getBehaveingFrame() >= _frame_refraction_enter) {
                    if (_cnt_refraction < _num_refraction) {
                        _cnt_refraction++;
                        onRefractionEnterHeadChip(_cnt_refraction);
                        _frame_refraction_outer = getBehaveingFrame()  + _frame_standstill;
                        _isRefracting = true;

                        if (_pDispatche_RefractionEffect) {
							_pRefractionEffect = (GgafDx9DrawableActor*)_pDispatche_RefractionEffect->employ();
							//_TRACE_("_pRefractionEffect->employ();");
                            if (_pRefractionEffect) {
                                _pRefractionEffect->setGeometry(this);
                                _pRefractionEffect->activate();
                            }
                        }
                    }
                }
            }

            if (_isRefracting) {
                if (getBehaveingFrame() >= _frame_refraction_outer) {
                    onRefractionOutHeadChip(_cnt_refraction);
                    _frame_refraction_enter = getBehaveingFrame() + _frame_refraction_interval;
                    //���W��ς������������]��
                    int X, Y, Z;
                    X = _X; Y = _Y; Z = _Z;
                    _pMover->behave(); //
                    _X = X; _Y = Y; _Z = Z;
                    _isRefracting = false;

                    return;
                }
            }

            if (!_isRefracting) {
                //_isRefracting���͒�~���Ȃ��Ă͂����Ȃ�����_pMover->behave()�����s���Ȃ��B
                //_pMover->behave();�ȊO�ō��W�𑀍삵�Ă���ꍇ�́A���S�Ȓ�~�ɂȂ�Ȃ��̂Œ���
                _pMover->behave();
            }

        } else {
            //�擪�ȊO�̃`�b�v����q������
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;
            _prev_isRefracting = _isRefracting;
            _prev_pRefractionEffect = _pRefractionEffect;
            _X  = pChip_front->_prev_X;
            _Y  = pChip_front->_prev_Y;
            _Z  = pChip_front->_prev_Z;
            _RX = pChip_front->_prev_RX;
            _RY = pChip_front->_prev_RY;
            _RZ = pChip_front->_prev_RZ;
            _isRefracting =  pChip_front->_prev_isRefracting;
            _pRefractionEffect = pChip_front->_prev_pRefractionEffect;
            if (_pChip_behind == NULL) {
                if (_pRefractionEffect) {
                    //_TRACE_("_pRefractionEffect->sayonara();");
                    _pRefractionEffect->sayonara(_frame_standstill);
                }
            }
        }
    }
}

void RefractionLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //TODO:�R�����g�����؁@���Ԃ���Ȃ�
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

RefractionLaserChip::~RefractionLaserChip() {
}

