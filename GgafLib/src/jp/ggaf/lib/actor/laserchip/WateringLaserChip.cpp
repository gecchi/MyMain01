#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WateringLaserChip::WateringLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "WateringLaserChip";
}

void WateringLaserChip::onActive() {
    //���[�U�[�`�b�v�o��������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();
}

void WateringLaserChip::processBehavior() {
}

void WateringLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}


WateringLaserChip::~WateringLaserChip() {
}

