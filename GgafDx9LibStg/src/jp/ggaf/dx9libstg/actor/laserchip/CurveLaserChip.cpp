#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


CurveLaserChip::CurveLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "CurveLaserChip";
    _tmpX = 0;
    _tmpY = 0;
    _tmpZ = 0;
}

void CurveLaserChip::initialize() {
    //�����ݒ�ł��B
    //30px/frame �̈ړ����x
    //�����蔻�肠��B
    //����0.99
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    _pMover->setMvVelo(30000);
    _fAlpha = 0.99;
}


void CurveLaserChip::onActive() {
    //���[�U�[�`�b�v�o��������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}

void CurveLaserChip::onInactive() {
    //���[�U�[�`�b�v����������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onInactive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onInactive();
}

void CurveLaserChip::processBehavior() {
    LaserChip::processBehavior();
    _pMover->behave();
    //���W���R�s�[
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}
void CurveLaserChip::processSettlementBehavior() {
    //���ϋȐ����W�ݒ�B(���[�U�[�����炩�ɂ���m�[�}���C�Y�j
    //processSettlementBehavior() �̃��\�b�h�̈Ӌ`�Ƃ͗���č��W��������ړ����Ă���B
    //�{���� processBehaviorAfter() �I�ȈӖ��̏����ł��邪�A�S���[�U�[�`�b�v���ړ���łȂ��ƈӖ����Ȃ��̂�
    //�d���Ȃ��̂�processSettlementBehavior()�ɐH������ł��܂��B
    //���������Ė{�N���X���p�������ꍇ�A�p���N���X��processSettlementBehavior()�ł́A�擪�ŌĂяo���������ǂ��B

    if (_pChip_front == NULL) {
        //��[
        if (_pChip_behind != NULL && _pChip_behind->isActive()) {
            //���ʂ̐�[
        } else {
            //��[�Ŗ��[
            //�ǂ��ւł������Ȃ͂�
        }
    } else if (_pChip_behind == NULL) {
        //���[
        if (_pChip_front != NULL && _pChip_front->isActive()) {
            //���ʂ̖��[

        } else {
            //���[�Ő�[
            //�ǂ��ւł������Ȃ͂�
        }
    } else if (_pChip_front->isActive() && _pChip_behind->isActive()) {
        //_pChip_behind == NULL �̔��肾���ł͂��߁B_pChip_behind->isActive()�Ɣ��肷�邱��
        //�Ȃ��Ȃ�employ�̏u�Ԃ�_pChip_behind != NULL �ƂȂ邪�Aactive()�ɂ��L���ɂȂ�͎̂��t���[��������
        //_X,_Y,_Z �ɂ͂܂��ςȒl�������Ă���B
        CurveLaserChip* pF = (CurveLaserChip*)_pChip_front;
        CurveLaserChip* pB = (CurveLaserChip*)_pChip_behind;
        //���ԍ��W�ɍĐݒ�
        _X = (pF->_tmpX + _tmpX + pB->_tmpX) / 3;
        _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
        _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
        _pMover->_veloVxMv = (pF->_pMover->_veloVxMv + _pMover->_veloVxMv + pB->_pMover->_veloVxMv) / 3;
        _pMover->_veloVyMv = (pF->_pMover->_veloVyMv + _pMover->_veloVyMv + pB->_pMover->_veloVyMv) / 3;
        _pMover->_veloVzMv = (pF->_pMover->_veloVzMv + _pMover->_veloVzMv + pB->_pMover->_veloVzMv) / 3;
    }
    LaserChip::processSettlementBehavior();
}

void CurveLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

CurveLaserChip::~CurveLaserChip() {
}

