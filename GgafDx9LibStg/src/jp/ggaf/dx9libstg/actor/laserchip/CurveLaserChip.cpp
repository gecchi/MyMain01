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
    _pKuroko->setMvVelo(30000);
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
    _pKuroko->behave();
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
    if (_was_paused_flg) {
        GgafDx9GeometricActor::processSettlementBehavior();
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
        } else if (_pChip_front->isActiveActor() && _pChip_behind->isActiveActor()) {
            //_pChip_behind == NULL �̔��肾���ł͂��߁B_pChip_behind->isActiveActor()�Ɣ��肷�邱��
            //�Ȃ��Ȃ�employ�̏u�Ԃ�_pChip_behind != NULL �ƂȂ邪�Aactive()�ɂ��L���ɂȂ�͎̂��t���[��������
            //_X,_Y,_Z �ɂ͂܂��ςȒl�������Ă���B
            CurveLaserChip* pF = (CurveLaserChip*)_pChip_front;
            CurveLaserChip* pB = (CurveLaserChip*)_pChip_behind;
            //���ԍ��W�ɍĐݒ�
            _X = (pF->_tmpX + _tmpX + pB->_tmpX) / 3;
            _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
            _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
            _pKuroko->_veloVxMv = (pF->_pKuroko->_veloVxMv + _pKuroko->_veloVxMv + pB->_pKuroko->_veloVxMv) / 3;
            _pKuroko->_veloVyMv = (pF->_pKuroko->_veloVyMv + _pKuroko->_veloVyMv + pB->_pKuroko->_veloVyMv) / 3;
            _pKuroko->_veloVzMv = (pF->_pKuroko->_veloVzMv + _pKuroko->_veloVzMv + pB->_pKuroko->_veloVzMv) / 3;
        }
        LaserChip::processSettlementBehavior();
    }
}

void CurveLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

CurveLaserChip::~CurveLaserChip() {
}

