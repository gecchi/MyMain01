#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


WateringLaserChip::WateringLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "WateringLaserChip";
    _tmpX = 0;
    _tmpY = 0;
    _tmpZ = 0;
}

void WateringLaserChip::initialize() {
    //�����ݒ�ł��B
    //30px/frame �̈ړ����x
    //�����蔻�肠��B
    //����0.99
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    _pKurokoA->setMvVelo(30000);
    _fAlpha = 0.99;
}


void WateringLaserChip::onActive() {
    //���[�U�[�`�b�v�o��������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}

void WateringLaserChip::onInactive() {
    //���[�U�[�`�b�v����������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onInactive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onInactive();
}

void WateringLaserChip::processBehavior() {
    LaserChip::processBehavior();
    //_pKurokoA->behave();
    _pKurokoB->behave();
    //���W���R�s�[
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}
void WateringLaserChip::processSettlementBehavior() {
    //���ϋȐ����W�ݒ�B(���[�U�[�����炩�ɂ���m�[�}���C�Y�j
    //processSettlementBehavior() �̃��\�b�h�̈Ӌ`�Ƃ͗���č��W��������ړ����Ă���B
    //�{���� processBehaviorAfter() �I�ȈӖ��̏����ł��邪�A�S���[�U�[�`�b�v���ړ���łȂ��ƈӖ����Ȃ��̂�
    //�d���Ȃ��̂�processSettlementBehavior()�ɐH������ł��܂��B
    //���������Ė{�N���X���p�������ꍇ�A�p���N���X��processSettlementBehavior()�ł́A�擪�ŌĂяo���������ǂ��B
    if (_was_paused_flg) {
        GgafDx9GeometricActor::processSettlementBehavior();
//        LaserChip::processSettlementBehavior();
    } else {
        if (_pChip_front == NULL) {
            //��[
            if (_pChip_behind != NULL && _pChip_behind->isActiveActor()) {
                //���ʂ̐�[
            } else {
                //��[�Ŗ��[
                //�ǂ��ւł������Ȃ͂�
            }
        } else if (_pChip_behind == NULL) {
            //���[
            if (_pChip_front != NULL && _pChip_front->isActiveActor()) {
                //���ʂ̖��[

            } else {
                //���[�Ő�[
                //�ǂ��ւł������Ȃ͂�
            }
        } else if (_pChip_front->_is_active_flg && _pChip_behind->_is_active_flg) {
            //_pChip_behind == NULL �̔��肾���ł͂��߁B_pChip_behind->isActiveActor()�Ɣ��肷�邱��
            //�Ȃ��Ȃ�employ�̏u�Ԃ�_pChip_behind != NULL �ƂȂ邪�Aactive()�ɂ��L���ɂȂ�͎̂��t���[��������
            //_X,_Y,_Z �ɂ͂܂��ςȒl�������Ă���B
            WateringLaserChip* pF = (WateringLaserChip*)_pChip_front;
            WateringLaserChip* pB = (WateringLaserChip*)_pChip_behind;
            //���ԍ��W�ɍĐݒ�
            _X = (pF->_tmpX + _tmpX + pB->_tmpX) / 3;
            _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
            _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
//            _pKurokoB->_veloVxMv = (pF->_pKurokoB->_veloVxMv + _pKurokoB->_veloVxMv) / 2;
//            _pKurokoB->_veloVyMv = (pF->_pKurokoB->_veloVyMv + _pKurokoB->_veloVyMv) / 2;
//            _pKurokoB->_veloVzMv = (pF->_pKurokoB->_veloVzMv + _pKurokoB->_veloVzMv) / 2;
//            _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
//            _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
//            _pKurokoB->_veloVxMv = (pF->_pKurokoB->_veloVxMv + _pKurokoB->_veloVxMv + pB->_pKurokoB->_veloVxMv) / 3;
//            _pKurokoB->_veloVyMv = (pF->_pKurokoB->_veloVyMv + _pKurokoB->_veloVyMv + pB->_pKurokoB->_veloVyMv) / 3;
//            _pKurokoB->_veloVzMv = (pF->_pKurokoB->_veloVzMv + _pKurokoB->_veloVzMv + pB->_pKurokoB->_veloVzMv) / 3;
        }
        LaserChip::processSettlementBehavior();
    }
//    //���ϋȐ����W�ݒ�B(���[�U�[�����炩�ɂ���m�[�}���C�Y�j
//    //processSettlementBehavior() �̃��\�b�h�̈Ӌ`�Ƃ͗���č��W��������ړ����Ă���B
//    //�{���� processBehaviorAfter() �I�ȈӖ��̏����ł��邪�A�S���[�U�[�`�b�v���ړ���łȂ��ƈӖ����Ȃ��̂�
//    //�d���Ȃ��̂�processSettlementBehavior()�ɐH������ł��܂��B
//    //���������Ė{�N���X���p�������ꍇ�A�p���N���X��processSettlementBehavior()�ł́A�擪�ŌĂяo���������ǂ��B
//    if (_was_paused_flg) {
//        GgafDx9GeometricActor::processSettlementBehavior();
//    } else {
//        if (_pChip_front == NULL) {
//            //��[
//            if (_pChip_behind != NULL && _pChip_behind->isActiveActor()) {
//                //���ʂ̐�[
//            } else {
//                //��[�Ŗ��[
//                //�ǂ��ւł������Ȃ͂�
//            }
//        } else if (_pChip_behind == NULL) {
//            //���[
//            if (_pChip_front != NULL && _pChip_front->isActiveActor()) {
//                //���ʂ̖��[
//
//            } else {
//                //���[�Ő�[
//                //�ǂ��ւł������Ȃ͂�
//            }
//        } else if (_pChip_front->_is_active_flg && _pChip_behind->_is_active_flg) {
//            //_pChip_behind == NULL �̔��肾���ł͂��߁B_pChip_behind->isActiveActor()�Ɣ��肷�邱��
//            //�Ȃ��Ȃ�employ�̏u�Ԃ�_pChip_behind != NULL �ƂȂ邪�Aactive()�ɂ��L���ɂȂ�͎̂��t���[��������
//            //_X,_Y,_Z �ɂ͂܂��ςȒl�������Ă���B
//            WateringLaserChip* pF = (WateringLaserChip*)_pChip_front;
//            WateringLaserChip* pB = (WateringLaserChip*)_pChip_behind;
//            //���ԍ��W�ɍĐݒ�
//            _X = (pF->_tmpX + _tmpX + pB->_tmpX) / 3;
//            _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
//            _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
//            _pKurokoB->_veloVxMv = (pF->_pKurokoB->_veloVxMv + _pKurokoB->_veloVxMv + pB->_pKurokoB->_veloVxMv) / 3;
//            _pKurokoB->_veloVyMv = (pF->_pKurokoB->_veloVyMv + _pKurokoB->_veloVyMv + pB->_pKurokoB->_veloVyMv) / 3;
//            _pKurokoB->_veloVzMv = (pF->_pKurokoB->_veloVzMv + _pKurokoB->_veloVzMv + pB->_pKurokoB->_veloVzMv) / 3;
//        }
//        LaserChip::processSettlementBehavior();
//    }
}

void WateringLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

WateringLaserChip::~WateringLaserChip() {
}

