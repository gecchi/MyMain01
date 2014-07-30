#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/RefractionLaserChip.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"

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

    _pDispatche_RefractionEffect = nullptr;
    _pRefractionEffect = nullptr;
    _prev_pRefractionEffect = nullptr;

    _begining_x = _x;
    _begining_y = _y;
    _begining_z = _z;
    _begining_rx = _rx;
    _begining_ry = _ry;
    _begining_rz = _rz;
    _prev_x  = _x;
    _prev_y  = _y;
    _prev_z  = _z;
    _prev_rx = _rx;
    _prev_ry = _ry;
    _prev_rz = _rz;
    _prev_is_refracting = false;
    _is_fix_begin_pos = true;
}

void RefractionLaserChip::config(int prm_num_refraction,
                                 frame prm_frame_between_refraction,
                                 frame prm_frame_standstill_refraction,
                                 bool prm_is_fix_begin_pos,
                                 GgafActorDepository* prm_pDispatche_RefractionEffect) {
#ifdef MY_DEBUG
    if (prm_frame_between_refraction == 0) {
        throwGgafCriticalException("RefractionLaserChip::config ���i�Ԋu�t���[������0�͐ݒ�s�ł��Bname="<<getName());
    }
    if (prm_frame_standstill_refraction == 0) {
        throwGgafCriticalException("RefractionLaserChip::config ���ܗ��t���[������0�͐ݒ�s�ł��Bname="<<getName());
    }
#endif
    _num_refraction = prm_num_refraction;
    _frame_between_refraction = prm_frame_between_refraction;
    _frame_standstill_refraction = prm_frame_standstill_refraction;
    _is_fix_begin_pos = prm_is_fix_begin_pos;
    _pDispatche_RefractionEffect = prm_pDispatche_RefractionEffect;
}

void RefractionLaserChip::onActive() {
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();

    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
    //���[�U�[�`�b�v�o��������
    if (pChip_front == nullptr) {
        _is_leader = true;
        //���g���擪�̏ꍇ
        _begining_x = _x;
        _begining_y = _y;
        _begining_z = _z;
        _begining_rx = _rx;
        _begining_ry = _ry;
        _begining_rz = _rz;
        _cnt_refraction = 0;
        _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction;
        _frame_refraction_out = _frame_refraction_enter + _frame_standstill_refraction;
        //onRefractionBegin(_cnt_refraction);
        onRefractionFinish(_cnt_refraction);  //�R�[���o�b�N 0��ڂ̋��܏I������X�^�[�g����
    } else {
        _is_leader = false;
        _begining_x = pChip_front->_begining_x;
        _begining_y = pChip_front->_begining_y;
        _begining_z = pChip_front->_begining_z;
        _begining_rx = pChip_front->_begining_rx;
        _begining_ry = pChip_front->_begining_ry;
        _begining_rz = pChip_front->_begining_rz;
        if (_is_fix_begin_pos) {
            _x = _begining_x;
            _y = _begining_y;
            _z = _begining_z;
            _rx = _begining_rx;
            _ry = _begining_ry;
            _rz = _begining_rz;
        }
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
    //������Ɩ��ʂ��ۂ����ǁA�����Ȃ��ΐ擪�̎��̃`�b�v���̈�O�Ɍ������Ĉړ�����Ƃ͌���Ȃ��̂ŁA��͂�K�v�B
    if (_pChip_behind) {
        RefractionLaserChip* const pChip_behind = (RefractionLaserChip*)_pChip_behind;
        GgafDxKuroko* const pChip_behind_pKuroko = pChip_behind->getKuroko();
        GgafDxKuroko* pKuroko = getKuroko();
        pChip_behind_pKuroko->_vX = pKuroko->_vX;
        pChip_behind_pKuroko->_vY = pKuroko->_vY;
        pChip_behind_pKuroko->_vZ = pKuroko->_vZ;
        pChip_behind_pKuroko->_ang_rz_mv = pKuroko->_ang_rz_mv;
        pChip_behind_pKuroko->_ang_ry_mv = pKuroko->_ang_ry_mv;
        pChip_behind_pKuroko->_velo_mv  = pKuroko->_velo_mv;
        pChip_behind->_rx = _rx;
        pChip_behind->_ry = _ry;
        pChip_behind->_rz = _rz;
        pChip_behind->_cnt_refraction = _cnt_refraction;
        pChip_behind->_frame_refraction_enter = _frame_refraction_enter;
        pChip_behind->_frame_refraction_out = _frame_refraction_out;
        pChip_behind->_is_refracting = _is_refracting;
        //���܃G�t�F�N�g������
        if (_pRefractionEffect) {
            _pRefractionEffect->sayonara();
            _pRefractionEffect = nullptr;
        }
        if (_prev_pRefractionEffect) {
            _prev_pRefractionEffect->sayonara();
            _prev_pRefractionEffect = nullptr;
        }
        pChip_behind->_pRefractionEffect = _pRefractionEffect;
    } else {
        //���܃G�t�F�N�g������
        if (_pRefractionEffect) {
            _pRefractionEffect->sayonara();
            _pRefractionEffect = nullptr;
        }
        if (_prev_pRefractionEffect) {
            _prev_pRefractionEffect->sayonara();
            _prev_pRefractionEffect = nullptr;
        }
    }
    LaserChip::onInactive(); //�Ȃ����ؒf����
}

void RefractionLaserChip::processBehavior() {
    //���[�U�[�`�b�v����������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
    //���W�ɔ��f
    GgafDxKuroko* pKuroko = getKuroko();
    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
    if (getActiveFrame() > 1) {
        //GgafActorDepository::dispatch() ��
        //�擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ������B
        //���������āA���[�U�[�̐擪���珇�Ԃ�processBehavior() ���Ă΂�邽�߁A�ȉ��̂悤�ɂ����
        //����q���ɂȂ�B
        if (pChip_front == nullptr) {
            //�{���̐擪�`�b�v���A�����͂ɂ킩�擪�`�b�v�̏ꍇ�̋��ʏ���
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _prev_is_refracting = _is_refracting;
            _prev_pRefractionEffect = _pRefractionEffect;

            _pRefractionEffect = nullptr;
            if (!_is_refracting) {
                if (getBehaveingFrame() >= _frame_refraction_enter) {
                    if (_cnt_refraction < _num_refraction) {
                        _cnt_refraction++;
                        onRefractionBegin(_cnt_refraction); //�R�[���o�b�N
                        _frame_refraction_out = getBehaveingFrame()  + _frame_standstill_refraction;
                        _is_refracting = true;

                        if (_pDispatche_RefractionEffect) {
                            _pRefractionEffect = (GgafDxDrawableActor*)_pDispatche_RefractionEffect->dispatch();
                            if (_pRefractionEffect) {
                                _pRefractionEffect->positionAs(this);
                                //�Œ����Ԃ̉����\��B
                                //�����̔��q�H�iTODO:�v�����j�Ń��[�U�[�`�b�v�����ł����ꍇ�A������sayonara()�o���Ȃ��ꍇ������B���̏ꍇ�̕ی��B
                                _pRefractionEffect->inactivateDelay(_pDepo->_num_chip_max +_frame_standstill_refraction);
                            }
                        }
                    }
                }
            }

            if (_is_refracting) {
                if (getBehaveingFrame() >= _frame_refraction_out) {
                    onRefractionFinish(_cnt_refraction); //�R�[���o�b�N
                    _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction;
                    //���W��ς������������]��
                    coord x = _x; coord y = _y; coord z = _z;
                    pKuroko->behave(); //
                    _x = x; _y = y; _z = z;
                    _is_refracting = false;

                    return;
                }
            }

            if (!_is_refracting) {
                //_is_refracting���͒�~���Ȃ��Ă͂����Ȃ�����getKuroko()->behave()�����s���Ȃ��B
                //pKuroko->behave();�ȊO�ō��W�𑀍삵�Ă���ꍇ�́A���S�Ȓ�~�ɂȂ�Ȃ��̂Œ���
                pKuroko->behave();
            }

        } else {
            //�擪�ȊO�̃`�b�v����q������
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _prev_is_refracting = _is_refracting;
            _prev_pRefractionEffect = _pRefractionEffect;
            _x  = pChip_front->_prev_x;
            _y  = pChip_front->_prev_y;
            _z  = pChip_front->_prev_z;
            _rx = pChip_front->_prev_rx;
            _ry = pChip_front->_prev_ry;
            _rz = pChip_front->_prev_rz;
            _is_refracting =  pChip_front->_prev_is_refracting;
            _pRefractionEffect = pChip_front->_prev_pRefractionEffect;
            if (_pChip_behind == nullptr) {
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

