#ifndef GGAF_LIB_REFRACTIONLASERCHIP_H_
#define GGAF_LIB_REFRACTIONLASERCHIP_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * ���ˁi���܁j���[�U�[�p�|�����C���̃`�b�v .
 * ���ˁi���܁j���[�U�[�Ȃǂǂƕ\�����Ă��邪�A���m�ɂ� <BR>
 * �E���ˍ��W�Œ�i���ˌ����W�͒ʏ�͈ړ��s�j <BR>
 * �E�ړ������A���x�͐擪�`�b�v���݂̂����߁A�c��`�b�v�͒P�ɒǏ]����<BR>
 * �E�ړ������͒��i�A�A�����Ԋu�ňړ��������ω� <BR>
 * �ƌ����ׂ����A�_���C�A�X�̃{�X�̑��i���[�U�[�ƌ����ׂ����A����Ȋ����B<BR>
 * �f�|�W�g���o�^�O��config()�Őݒ肵�Ă��������B<BR>
 * �擪�`�b�v��  GgafDx::VecVehicle#behave() �ňړ����܂��B<BR>
 * dispatch() ������A�������W�� VecVehicle�i���x�E�����j��ݒ肵�ĉ������B<BR>
 * @version 1.00
 * @since 2010/01/19
 * @author Masatoshi Tsuge
 */
class RefractionLaserChip : public LaserChip {
    friend class LaserChipDepository;

private:
    /** [r](�����)���܊J�n�t���[�� */
    frame _frame_refraction_enter;
    /** [r]���܏I���t���[�� */
    frame _frame_refraction_out;
    /** [r]���܂��ɋ��ܒ��i�ړ����Ă��Ȃ��j�̏ꍇtrue */
    bool _is_refracting;
    /** [r]���݂̋��܉� */
    int _cnt_refraction;

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

    bool _prev_is_refracting;
    GgafDx::FigureActor* _prev_pRefractionEffect;

    /** ���܃G�t�F�N�g�A�N�^�[�̃f�|�W�g���i�V�[�������ς݂ł��邱�Ɓj */
    GgafCore::ActorDepository* _pDepo_refraction_effect;
    GgafDx::FigureActor* _pRefractionEffect;
    /** ���܏I���܂ł̃t���[���� */
    frame _refraction_end_frames;
public:
    /** �擱�`�b�v�i�{���̐擪�`�b�v�j�t���O */
    bool _is_leader; //�{���̐擪�`�b�v�Ƃ́A���[�U�[�ړ����ɂ�����Ĕ�������ɂ킩�擪�`�b�v�ł͖����Ƃ����Ӗ��B;
    /** [r]�ŏI�I�ȋ��܉� */
    int _num_refraction;
    /** [r]���i�J�n(���܏I��)�`���i�`���i�I��(���܊J�n)�A�̃t���[����(>= 1) */
    frame _frame_between_refraction;
    /** [r]���܎�(���i�I��(���܊J�n)�`��~�`���i�J�n(���܏I��))�̒�ؒ��߃t���[����(>= 1) */
    frame _frame_standstill_refraction;
    /** [r]���ˊJ�n���W�Œ肩�ۂ�(true:�Œ�A�Ăь��̍��W�����㏑�����āA�ŏ���[0]�̍��W�ɋ����㏑��/false:��Œ�B�X�N���[���V�[���z�����̏ꍇ�� false ���ǂ� */
    bool _is_fix_begin_pos;

public:
    RefractionLaserChip(const char* prm_name, const char* prm_model);

    /**
     * ���t���N�V�������[�U�[���` .
     * @param prm_num_refraction ������܂��邩
     * @param prm_frame_between_refraction ���i�J�n(���܏I��)�`���i�`���i�I��(���܊J�n)�A�̃t���[����(>= 1)
     * @param prm_frame_standstill_refraction ���܎�(���i�I��(���܊J�n)�`��~�`���i�J�n(���܏I��))�̒�ؒ��߃t���[����(>= 1)
     * @param prm_is_fix_beginning_pos true:���[�U�[���ˌ��́A�擪���[�U�[�`�b�v�̍��W�ɌŒ肳���B�^false:���ꂼ��̃��[�U�[�`�b�v�̍��W�Ɉˑ�
     * @param prm_pDepo_refraction_effect ���܎��̃G�t�F�N�g�A�N�^�[�̃f�|�W�g��(�����̏ꍇ��nullptr)
     */
    virtual void config(int prm_num_refraction,
                        frame prm_frame_between_refraction,
                        frame prm_frame_standstill_refraction,
                        bool prm_is_fix_begin_pos,
                        GgafCore::ActorDepository* prm_pDepo_refraction_effect);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍ہA�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
     * ���������́A
     * �擪�`�b�v�́AGgafDx::VecVehicle#behave() �����s�ɂ��ړ����s���܂��B
     * ���ܒ��� GgafDx::VecVehicle#behave() �ɂ��ړ��͍s���܂���B
     * �擪�ȊO�̃`�b�v�ȊO�́A�擪�`�b�v�ɒǏ]����Ƃ����������s���܂��B
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    /**
     * �擪�`�b�v�̃��[�U�[�̒��i�I���`���܊J�n���̏��� .
     * �擪�`�b�v�̂݃R�[���o�b�N����܂��B<BR>
     * @param prm_num_refraction ���܃J�E���g(����ڂ̋��܊J�n��)(0�`)
     */
    virtual void onRefractionInto(int prm_num_refraction) = 0;

    /**
     * �擪�`�b�v�̃��[�U�[�̂��ߌ���܌�I���`���i�J�n���̏��� .
     * �擪�`�b�v�̂݃R�[���o�b�N����܂��B<BR>
     * ���ۂɂ͑��݂��Ȃ�0��ڂ̋��܏I������X�^�[�g����B<BR>
     * 0��ڂ̋��܏I���� onActive() ���ɃR�[���o�b�N����܂��B<BR>
     * �I�[�o�[���C�h���A���܌�̎��̈ړ������Ƒ��x��͎�A�ɐݒ肷�������
     * �s���Ă��������B<BR>
     * @param prm_num_refraction ���܃J�E���g(����ڂ̋��܏I����)(0�`)
     */
    virtual void onRefractionOutOf(int prm_num_refraction) = 0;

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

    /**
     * ���܃��[�U�[�J�n�`�I���܂ł̃t���[�����𓾂� .
     * @return ���܃��[�U�[�J�n�`�I���܂ł̃t���[����
     */
    inline frame getRefractionFinishFrames() {
        return _refraction_end_frames;
    }

    virtual ~RefractionLaserChip();

};

}
#endif /*GGAF_LIB_HOMINGLASERCHIP_H_*/

