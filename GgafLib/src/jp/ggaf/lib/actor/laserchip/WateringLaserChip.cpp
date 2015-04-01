#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WateringLaserChip::WateringLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "WateringLaserChip";
    _tmpX = 0;
    _tmpY = 0;
    _tmpZ = 0;
}

void WateringLaserChip::onActive() {
    //���[�U�[�`�b�v�o��������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();
    _tmpX = _x;
    _tmpY = _y;
    _tmpZ = _z;
}

void WateringLaserChip::processBehavior() {
    //���W���R�s�[
    _tmpX = _x;
    _tmpY = _y;
    _tmpZ = _z;
}
void WateringLaserChip::processSettlementBehavior() {
    //���ϋȐ����W�ݒ�B(���[�U�[�����炩�ɂ���m�[�}���C�Y�j
    //processSettlementBehavior() �̃��\�b�h�̈Ӌ`�Ƃ͗���č��W��������ړ����Ă���B
    //�{���� processBehaviorAfter() �I�ȈӖ��̏����ł��邪�A�S���[�U�[�`�b�v���ړ���łȂ��ƈӖ����Ȃ��̂�
    //�d���Ȃ��̂�processSettlementBehavior()�ɐH������ł��܂��B
    //���������Ė{�N���X���p�������ꍇ�A�p���N���X��processSettlementBehavior()�ł́A�擪�ŌĂяo���������ǂ��B
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        const WateringLaserChip* pF = (WateringLaserChip*)_pChip_front;
        const WateringLaserChip* pB = (WateringLaserChip*)_pChip_behind;
        if (pF && pB && pF->_is_active_flg && pB->_is_active_flg) {
            //_pChip_behind == nullptr �̔��肾���ł͂��߁B_pChip_behind->_is_active_flg �Ɣ��肷�邱��
            //�Ȃ��Ȃ� dispatch �̏u�Ԃ�_pChip_behind != nullptr �ƂȂ邪�Aactive()�ɂ��L���ɂȂ�͎̂��t���[��������
            //_x,_y,_z �ɂ͂܂��ςȒl�������Ă���B

            //���ԍ��W�ɍĐݒ�
            _x = ((pF->_tmpX + pB->_tmpX)/2 + _tmpX)/2;
            _y = ((pF->_tmpY + pB->_tmpY)/2 + _tmpY)/2;
            _z = ((pF->_tmpZ + pB->_tmpZ)/2 + _tmpZ)/2;
        }
        LaserChip::processSettlementBehavior();
    }
}


WateringLaserChip::~WateringLaserChip() {
}

