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

//    _tmpX = 0;
//    _tmpY = 0;
//    _tmpZ = 0;
}

void CurveLaserChip::onInactive() {
    //���[�U�[�`�b�v����������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onInactive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onInactive();
}

void CurveLaserChip::processBehavior() {

    //���W�ɔ��f
    //����ɂ�蔭�ˌ��̍�������\�������
    //if (getActivePartFrame() > 0) {
        LaserChip::processBehavior();
        _pMover->behave();
    //}

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
//            CurveLaserChip* pB = (CurveLaserChip*)_pChip_behind;
//            _X = (_tmpX + pB->_tmpX) / 2;
//            _Y = (_tmpY + pB->_tmpY) / 2;
//            _Z = (_tmpZ + pB->_tmpZ) / 2;
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
//        if (_pChip_front->_pChip_front != NULL && _pChip_front->_pChip_front->isActive()) {
//            if (_pChip_behind->_pChip_behind != NULL && _pChip_behind->_pChip_behind->isActive()) {
//                    CurveLaserChip* pFF = (CurveLaserChip*)_pChip_front->_pChip_front;
//                    CurveLaserChip* pF = (CurveLaserChip*)_pChip_front;
//                    CurveLaserChip* pB = (CurveLaserChip*)_pChip_behind;
//                    CurveLaserChip* pBB = (CurveLaserChip*)_pChip_behind->_pChip_behind;
//                    _X = (pFF->_tmpX + pF->_tmpX + _tmpX + pB->_tmpX + pBB->_tmpX) / 5;
//                    _Y = (pFF->_tmpY + pF->_tmpY + _tmpY + pB->_tmpY + pBB->_tmpY) / 5;
//                    _Z = (pFF->_tmpZ + pF->_tmpZ + _tmpZ + pB->_tmpZ + pBB->_tmpZ) / 5;
//                    _pMover->_veloVxMv = (pFF->_pMover->_veloVxMv + pF->_pMover->_veloVxMv + _pMover->_veloVxMv + pB->_pMover->_veloVxMv + pBB->_pMover->_veloVxMv) / 5;
//                    _pMover->_veloVyMv = (pFF->_pMover->_veloVyMv + pF->_pMover->_veloVyMv + _pMover->_veloVyMv + pB->_pMover->_veloVyMv + pBB->_pMover->_veloVyMv) / 5;
//                    _pMover->_veloVxMv = (pFF->_pMover->_veloVxMv + pF->_pMover->_veloVxMv + _pMover->_veloVxMv + pB->_pMover->_veloVxMv + pBB->_pMover->_veloVxMv) / 5;
//			} else {
//	            CurveLaserChip* pF = (CurveLaserChip*)_pChip_front;
//	            CurveLaserChip* pB = (CurveLaserChip*)_pChip_behind;
//	            //���ԍ��W�ɍĐݒ�
//	            _X = (pF->_tmpX + _tmpX + pB->_tmpX) / 3;
//	            _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
//	            _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
//                _pMover->_veloVxMv = (pF->_pMover->_veloVxMv + _pMover->_veloVxMv + pB->_pMover->_veloVxMv) / 3;
//                _pMover->_veloVyMv = (pF->_pMover->_veloVyMv + _pMover->_veloVyMv + pB->_pMover->_veloVyMv) / 3;
//                _pMover->_veloVxMv = (pF->_pMover->_veloVxMv + _pMover->_veloVxMv + pB->_pMover->_veloVxMv) / 3;
//
//			}
//
//        } else {
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
            _pMover->_veloVxMv = (pF->_pMover->_veloVxMv + _pMover->_veloVxMv + pB->_pMover->_veloVxMv) / 3;
//        }
    }
    LaserChip::processSettlementBehavior();
}

void CurveLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

CurveLaserChip::~CurveLaserChip() {
}

