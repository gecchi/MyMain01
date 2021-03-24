#ifndef GGAF_LIB_HOMINGLASERCHIP_H_
#define GGAF_LIB_HOMINGLASERCHIP_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * �z�[�~���O���[�U�[�p�|�����C���̃`�b�v .
 * �z�[�~���O���[�U�[�Ȃǂƕ\�����Ă��邪�A���m�ɂ� <BR>
 * �E���ˍ��W�ʒu�Œ�i���ˌ����W���ʏ�ړ��s�j<BR>
 * �E�ړ������A���x�͐擪�`�b�v���݂̂����߁A�c��`�b�v�͒P�ɒǏ]����<BR>
 * �ƌ����ׂ����A���C�t�H�[�X�̃��b�N�I�����[�U�[�ƌ����ׂ����A����Ȋ����B<BR>
 * �擪�̃`�b�v�̓����� processBehaviorHeadChip() �Ɏ������ĉ������BVecDriver �ňړ����܂��B<BR>
 * dispatch() ������A���W�� VecDriver�i�������x�j��ݒ肵�ĉ������B<BR>
 * �擪�̃`�b�v�̏ꍇ�̂݁A���W�� VecDriver�i�������x�j�̐ݒ肪�K�p����A
 * ����ȍ~�̃`�b�v�͈�O���̃`�b�v�̍��W�������g���[�X���܂��B<BR>
 * @version 1.00
 * @since 2009/11/04
 * @author Masatoshi Tsuge
 */
class HomingLaserChip : public LaserChip {
    friend class LaserChipDepository;

public:
    /** �擱�`�b�v�i�{���̐擪�`�b�v�j�t���O */
    bool _is_leader; //�{���̐擪�`�b�v�Ƃ́A���[�U�[�ړ����ɂ�����Ĕ�������ɂ킩�擪�`�b�v�ł͖����Ƃ����Ӗ��B
    int _begining_x;
    int _begining_y;
    int _begining_z;
    angle _begining_rx;
    angle _begining_ry;
    angle _begining_rz;
    angle _begining_rz_mv;
    angle _begining_ry_mv;
    velo _begining_velo_mv;
    int _prev_x;
    int _prev_y;
    int _prev_z;
    angle _prev_rx;
    angle _prev_ry;
    angle _prev_rz;
    angle _prev_rz_mv;
    angle _prev_ry_mv;
    velo _prev_velo_mv;
    /** [r]���ˊJ�n���W�Œ肩�ۂ�(true:�Œ�A�Ăь��̍��W�����㏑�����āA�ŏ���[0]�̍��W�ɋ����㏑��/false:��Œ�B�X�N���[���V�[���z�����̏ꍇ�� false ���ǂ� */
    bool _is_fix_begin_pos;

public:
    HomingLaserChip(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    /**
     * �z�[�~���O���[�U�[�̐擪�`�b�v�̓������������� .
     * �{���̐擪�`�b�v�̏ꍇ�͂������R�[���o�b�N����邪�A
     * �ɂ킩�擪�`�b�v�i������ċ}�ɐ擪�ɂȂ����`�b�v�j�̏ꍇ���R�[���o�b�N����܂��B
     */
    virtual void processBehaviorHeadChip() = 0;

    /**
     * ���[�U�[�`�b�v�o�������� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void onActive() override;

    /**
     * ���[�U�[�`�b�v���������� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� onInactive() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void onInactive() override;


    virtual ~HomingLaserChip();

};

}
#endif /*GGAF_LIB_HOMINGLASERCHIP_H_*/

