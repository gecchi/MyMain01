#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

RefractionLaserChip::RefractionLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "RefractionLaserChip";
    _is_leader = false;
    _num_refraction = 2;
    _frame_standstill_refraction = 10;
    _frame_between_refraction = 20;

    _cnt_refraction = 0;
    _frame_refraction_enter = 0;
    _frame_refraction_out = 0;
    _is_refracting = false;

    _pDispatche_RefractionEffect = NULL;
    _pRefractionEffect = NULL;
    _prev_pRefractionEffect = NULL;
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
        _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction;
        _frame_refraction_out = _frame_refraction_enter + _frame_standstill_refraction;
        //onRefractionBegin(_cnt_refraction);
        onRefractionFinish(_cnt_refraction);  //0��ڂ̋��܏I������X�^�[�g����
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
        _frame_refraction_out = INT_MAX;
    }

    _is_refracting = false;
    _prev_is_refracting = false;
}

void RefractionLaserChip::onInactive() {
    //���[�U�[�`�b�v����������

    //�����̃`�b�v������΁A�����̈ӎv�i�ړ��Ȃǁj�������p������
    //����́A���[�U�[�������ꂽ�ꍇ�A�ȉ��̃p�����[�^�[�݈̂����p�����A�ړ����p�������邽�߁B
    //�����x��A�ړ��\��Ȃǈ����p����Ȃ����̂���������̂ŁA���G�Ȉړ�������ۂ́A�R�R�ɒ��ӂ𕥂����ƁI
    //���[�U�[���Q�[���̈�O�ɂ��������Ƃ����A�擪�`�b�v���珇�ɘA���ň��p�����������邱�ƂɂȂ�B
    //������Ɩ��ʂ��ۂ����ǁA�����Ȃΐ擪�̎��̃`�b�v���̈�O�Ɍ������Ĉړ�����Ƃ͌���Ȃ��̂ŁA��͂�K�v�B
    if (_pChip_behind) {
        RefractionLaserChip* pChip_behind = (RefractionLaserChip*)_pChip_behind;
        pChip_behind->_pKurokoA->_vX = _pKurokoA->_vX;
        pChip_behind->_pKurokoA->_vY = _pKurokoA->_vY;
        pChip_behind->_pKurokoA->_vZ = _pKurokoA->_vZ;
        pChip_behind->_pKurokoA->_angRzMv = _pKurokoA->_angRzMv;
        pChip_behind->_pKurokoA->_angRyMv = _pKurokoA->_angRyMv;
        pChip_behind->_pKurokoA->_veloMv = _pKurokoA->_veloMv;
        pChip_behind->_pKurokoA->_angFace[AXIS_X] = _pKurokoA->_angFace[AXIS_X];
        pChip_behind->_pKurokoA->_angFace[AXIS_Y] = _pKurokoA->_angFace[AXIS_Y];
        pChip_behind->_pKurokoA->_angFace[AXIS_Z] = _pKurokoA->_angFace[AXIS_Z];
        pChip_behind->_cnt_refraction = _cnt_refraction;
        pChip_behind->_frame_refraction_enter = _frame_refraction_enter;
        pChip_behind->_frame_refraction_out = _frame_refraction_out;
        pChip_behind->_is_refracting = _is_refracting;
        //���܃G�t�F�N�g������
        if (_pRefractionEffect) {
            _pRefractionEffect->sayonara();
            _pRefractionEffect = NULL;
        }
        if (_prev_pRefractionEffect) {
            _prev_pRefractionEffect->sayonara();
            _prev_pRefractionEffect = NULL;
        }
        pChip_behind->_pRefractionEffect = _pRefractionEffect;
    } else {
        //���܃G�t�F�N�g������
        if (_pRefractionEffect) {
            _pRefractionEffect->sayonara();
            _pRefractionEffect = NULL;
        }
        if (_prev_pRefractionEffect) {
            _prev_pRefractionEffect->sayonara();
            _prev_pRefractionEffect = NULL;
        }
    }
    LaserChip::onInactive(); //�Ȃ����ؒf����
}

void RefractionLaserChip::processBehavior() {
    //���[�U�[�`�b�v����������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
    //���W�ɔ��f
    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
    if (getActivePartFrame() > 1) {
        //GgafActorDepository::dispatch() ��
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
            _prev_is_refracting = _is_refracting;
            _prev_pRefractionEffect = _pRefractionEffect;

            _pRefractionEffect = NULL;
            if (!_is_refracting) {
                if (getBehaveingFrame() >= _frame_refraction_enter) {
                    if (_cnt_refraction < _num_refraction) {
                        _cnt_refraction++;
                        onRefractionBegin(_cnt_refraction);
                        _frame_refraction_out = getBehaveingFrame()  + _frame_standstill_refraction;
                        _is_refracting = true;

                        if (_pDispatche_RefractionEffect) {
                            _pRefractionEffect = (GgafDxDrawableActor*)_pDispatche_RefractionEffect->dispatch();
                            if (_pRefractionEffect) {
                                _pRefractionEffect->locateWith(this);
                                //�Œ����Ԃ̉����\��B
                                //�����̔��q�Ń��[�U�[�`�b�v�����ł����ꍇ�A������sayonara()�o���Ȃ��ꍇ������B���̏ꍇ�̕ی��B
                                _pRefractionEffect->inactivateDelay(_pDepo->_num_chip_max +_frame_standstill_refraction);
                            }
                        }
                    }
                }
            }

            if (_is_refracting) {
                if (getBehaveingFrame() >= _frame_refraction_out) {
                    onRefractionFinish(_cnt_refraction);
                    _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction;
                    //���W��ς������������]��
                    int X, Y, Z;
                    X = _X; Y = _Y; Z = _Z;
                    _pKurokoA->behave(); //
                    _X = X; _Y = Y; _Z = Z;
                    _is_refracting = false;

                    return;
                }
            }

            if (!_is_refracting) {
                //_is_refracting���͒�~���Ȃ��Ă͂����Ȃ�����_pKurokoA->behave()�����s���Ȃ��B
                //_pKurokoA->behave();�ȊO�ō��W�𑀍삵�Ă���ꍇ�́A���S�Ȓ�~�ɂȂ�Ȃ��̂Œ���
                _pKurokoA->behave();
            }

        } else {
            //�擪�ȊO�̃`�b�v����q������
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;
            _prev_is_refracting = _is_refracting;
            _prev_pRefractionEffect = _pRefractionEffect;
            _X  = pChip_front->_prev_X;
            _Y  = pChip_front->_prev_Y;
            _Z  = pChip_front->_prev_Z;
            _RX = pChip_front->_prev_RX;
            _RY = pChip_front->_prev_RY;
            _RZ = pChip_front->_prev_RZ;
            _is_refracting =  pChip_front->_prev_is_refracting;
            _pRefractionEffect = pChip_front->_prev_pRefractionEffect;
            if (_pChip_behind == NULL) {
                if (_pRefractionEffect) {
                    //_TRACE_("_pRefractionEffect->sayonara();");
                    _pRefractionEffect->sayonara(_frame_standstill_refraction);
                }
            }
        }
    }
}

void RefractionLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

RefractionLaserChip::~RefractionLaserChip() {
}

