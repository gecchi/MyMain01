#ifndef GGAF_LIB_WATERINGLASERCHIP_H_
#define GGAF_LIB_WATERINGLASERCHIP_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * ���T�����[�U�[�p�|�����C���̃`�b�v .
 * ���T�����[�U�[�Ȃǂƕ\�����Ă��邪�A���m�ɂ�<BR>
 * �E���ˍ��W�C�Ӂi���ˌ����W���ړ��\�j<BR>
 * �E�e�`�b�v�̈ړ������A���x���ɌŒ�<BR>
 * �E�������A�אڂ���`�b�v�ƃ`�b�v�������荇���A�p���Ƃ�Ċ��炩�ɂȂ�B�`�b�v�Ԃɓ����蔻�肪����<BR>
 * �Ƃ����ׂ����A�O���f�B�E�X�u�̃f�B���N�V�������[�U�[(TYPE2)�ƌ����ׂ����A����Ȋ����B<BR>
 * AxisVehicle �ňړ����܂��Bdispatch() ������A���W�� AxisVehicle�i�e���̈ړ����x�j��ݒ肵�ĉ������B<BR>
 * @version 1.00
 * @since 2009/08/27
 * @author Masatoshi Tsuge
 */
class WateringLaserChip : public LaserChip {
    friend class LaserChipDepository;

public:
    WateringLaserChip(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * ���[�U�[�`�b�v�o�������� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void onActive() override;

    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A���W�v�Z��A�Ō�ɖ{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    virtual ~WateringLaserChip();

};

}
#endif /*GGAF_LIB_WATERINGLASERCHIP_H_*/

