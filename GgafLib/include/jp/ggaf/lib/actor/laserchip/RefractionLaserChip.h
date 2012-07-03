#ifndef REFRACTIONLASERCHIP_H_
#define REFRACTIONLASERCHIP_H_

namespace GgafLib {

/**
 * ���ˁi���܁j���[�U�[�p�|�����C���̃`�b�v .
 * ���ˁi���܁j���[�U�[�Ȃǂǂƕ\�����Ă��邪�A���m�ɂ� <BR>
 * �E���ˍ��W�Œ�i���ˌ����W���ړ��s�j <BR>
 * �E�ړ������A���x�͐擪�`�b�v���݂̂����߁A�c��`�b�v�͒P�ɒǏ]����<BR>
 * �E�ړ������͒��i�A�A�����Ԋu�ňړ��������ω� <BR>
 * �ƌ����ׂ����A�_���C�A�X�̃{�X�̑��i���[�U�[�ƌ����ׂ����A����Ȋ����B
 * @version 1.00
 * @since 2010/01/19
 * @author Masatoshi Tsuge
 */
class RefractionLaserChip : public LaserChip {
    friend class LaserChipDepository;

private:
    frame _frame_refraction_enter;
    frame _frame_refraction_out;
    bool _is_refracting;
    int _cnt_refraction;

    /** �擱�`�b�v�i�{���̐擪�`�b�v�j�t���O */
    bool _is_leader; //�{���̐擪�`�b�v�Ƃ́A���[�U�[�ړ����ɂ�����Ĕ�������ɂ킩�擪�`�b�v�ł͖����Ƃ����Ӗ��B;
    int _begining_X;
    int _begining_Y;
    int _begining_Z;
    angle _begining_RX;
    angle _begining_RY;
    angle _begining_RZ;
    int _prev_X;
    int _prev_Y;
    int _prev_Z;
    angle _prev_RX;
    angle _prev_RY;
    angle _prev_RZ;

    bool _prev_is_refracting;
    GgafDxCore::GgafDxDrawableActor* _prev_pRefractionEffect;
    int _num_refraction;
    frame _frame_between_refraction;
    frame _frame_standstill_refraction;

    /** ���܃G�t�F�N�g�A�N�^�[�̃f�|�W�g���i�V�[�������ς݂ł��邱�Ɓj */
    GgafCore::GgafActorDepository* _pDispatche_RefractionEffect;
    GgafDxCore::GgafDxDrawableActor* _pRefractionEffect;

public:
    RefractionLaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=NULL);

    /**
     * ���t���N�V�������[�U�[���` .
     * @param prm_num_refraction ������܂��邩
     * @param prm_frame_between_refraction ���i�J�n(���܏I��)�`���i�`���i�I��(���܊J�n)�A�̃t���[����(>= 1)
     * @param prm_frame_standstill_refraction ���܎�(���i�I��(���܊J�n)�`��~�`���i�J�n(���܏I��))�̒�ؒ��߃t���[����(>= 1)
     * @param prm_pDispatche_RefractionEffect ���܎��̃G�t�F�N�g�A�N�^�[�̃f�|�W�g��(�����̏ꍇ��NULL)
     */
    virtual void config(int prm_num_refraction,
                        frame prm_frame_between_refraction,
                        frame prm_frame_standstill_refraction,
                        GgafCore::GgafActorDepository* prm_pDispatche_RefractionEffect);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    /**
     * �擪�`�b�v�̃��[�U�[�̒��i�I���`���܊J�n���̏��� .
     * @param prm_num_refraction ���܃J�E���g(����ڂ̋��܊J�n��)(0�`)
     */
    virtual void onRefractionBegin(int prm_num_refraction) = 0;

    /**
     * �擪�`�b�v�̃��[�U�[�̂��ߌ���܌�I���`���i�J�n���̏��� .
     * ���ۂɂ͑��݂��Ȃ�0��ڂ̋��܏I������X�^�[�g����B
     * @param prm_num_refraction ���܃J�E���g(����ڂ̋��܏I����)(0�`)
     */
    virtual void onRefractionFinish(int prm_num_refraction) = 0;

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

    virtual ~RefractionLaserChip();

};

}
#endif /*HOMINGLASERCHIP_H_*/

