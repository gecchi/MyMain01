#ifndef LASERCHIPDEPOSITORY_H_
#define LASERCHIPDEPOSITORY_H_
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * ���[�U�P�{��(���[�U�[�`�b�v�g���܂킵�Ǘ��N���X�B) .
 * new ������ addSubLast ���\�b�h�� LaserChip�C���X�^���X���D���Ȍ��o�^���Ă��������B<BR>
 * new ���� initialize()�܂ŁA���͐����ύX���L���ȃp�����[�^<BR>
 * �E_num_chip_interval �E�E�E�e�؂�t���[�����i�f�t�H���g:20�j<BR>
 * �E_pSeConnection_Laser �E�E�E ���[�U�[�`�b�v���ˎ�SE�i�f�t�H���g:nullptr�j<BR>
 * <�g�p��><BR>
 * <code><pre>
 *
 * ----- ���O�����i�R���X�g���N�^�łP�{���쐬��j --------------
 *
 * LaserChipDepository* pLaserDepo = new LaserChipDepository("MyLaserDp");  //�{�f�|�W�g���N���X�𐶐�����
 * MyStraightLaserChip* pChip;                    //MyStraightLaserChip �� LaserChip �p���N���X�B
 * for (int i = 0; i < 60; i++) {                 //1�{��60�̃`�b�v�ō\��
 *     pChip = new MyStraightLaserChip("chip");   //LaserChip �N���X���p���E���������I�u�W�F�N�g�쐬
 *     pChip->setSource(this);                    //�p�� LaserChip �ŗL�̐ݒ���{���B���̗�̓��C���_�[�̂��߂̔��ˌ��ݒ�B
 *     pLaserDepo->addSubLast(pChip);             //�{�f�|�W�g���� LaserChip �I�u�W�F�N�g��o�^(�T�u�ɏ���������)
 * }
 * pLaserDepo->config(40, 25);                    //LaserChip �̍ő�A�����A�e�؂�t���[������ݒ�B
 * addSubGroup(_pLaserChipDepo);                  //�f�|�W�g�����̂������\�ɂ����邽�߁A�������ɏ���������B
 *
 *
 * ----- ���ˏ����iZ�L�[�������ςȂ��Ŕ��˗�j --------------
 *
 * if (GgafDxInput::isBeingPressedKey(DIK_Z)) {   //Z�L�[����
 *     pLaserDepo->dispatch();                    //dispatch()���邱�ƂŁA�o�^���ꂽMyStraightLaserChip�B����������B
 * }
 *
 * </pre></code>
 */
class LaserChipDepository : public GgafCore::GgafActorDepository {
    friend class LaserChip;

public:
    /** [r]�ێ����郌�[�U�[�`�b�v��(�ǂݎ���p) */
    int _num_chip_max;
    /** [r]���������[�U�[�`�b�v��(�ǂݎ���p) */
    int _num_chip_active;
    /** [r]���[�U�[�`�b�v�ؒf���ꂽ�t���O(�ǂݎ���p�Atrue=�A�����ˏ�Ԃ͎Ւf����Ă���/false=�A�����ˏ��) */
    bool _is_tear_laser;
    /** [r]�O��i�O�t���[���j�擾���ꂽ���[�U�[�`�b�v(�ǂݎ���p) */
    LaserChip* _pChip_prev_dispatch;
    /** [r]�O��i�O�t���[���j�擾���ꂽ���[�U�[�`�b�v�̎擾���ꂽ���_�̊����t���[��(�ǂݎ���p) */
    frame _frame_of_behaving_prev_dispatch;
    /** [r]���[�U�[�`�b�v�A���擾�J�E���g(�ǂݎ���p) */
    int _num_continual_dispatch_count;
    /** [r]���[�U�[�`�b�v�A�����擾�J�E���g(�ǂݎ���p) */
    int _num_interval_frame_count;

    /** [r/w]�e�؂�Ɉڍs����`�b�v�̘A���擾���B�i�ǂݏ����^�f�t�H���g�FaddSubLast()������ _num_chip_max �Ɠ����ɂȂ��Ă���B */
    int _num_continual_dispatch_max;
    /** [r/w]�e�؂�t���[�����i�ǂݏ����^�f�t�H���g=20�j */
    int _num_chip_interval;
    /** [r]�e�؂�̎��A�������܂����甭��(dispatch()) �o����悤�ɂ��邩 */
    int _num_chip_dispatch_able;
    /** [r/w]���[�U�[���ˎ��G�t�F�N�g�B�s�v�̏ꍇ��nullptr��ݒ肷�� */
    GgafDxCore::GgafDxDrawableActor* _pEffectActor_Irradiate;

public:
    LaserChipDepository(const char* prm_name, GgafCore::GgafStatus* prm_pStat = nullptr);

    /**
     * LaserChipDepository��ݒ肷��B
     * @param prm_num_continual_dispatch_max �����I�ɒe�؂�Ɉڍs����`�b�v�̘A���擾���B
     * @param prm_num_chip_interval �e�؂�t���[����
     * @param prm_pEffectActor_Irradiate �V�[�������ςݔ��˒��G�t�F�N�g(�s�v����nullptr)�B����͌Ăь��ŁB
     */
    virtual void config(int prm_num_continual_dispatch_max,
                        uint32_t prm_num_chip_interval,
                        GgafDxCore::GgafDxDrawableActor* prm_pEffectActor_Irradiate = nullptr);

    virtual void processBehavior() override {
    }

    virtual void processFinal() override;

    /**
     * ���[�U�[�`�b�v�̎؂��������݁A�؂����ł���Ύ擾��������Ԃɂ���B .
     * �X�g�b�N�؂�A�����͒e�؂ꒆ�̏ꍇ�͖߂�� nullptr ���Ԃ�B
     * �擾�����`�b�v�̗��p���I������ꍇ�� sayonara() (������inactivate()) �����s���Ă��������B
     * �����I�ɃX�g�b�N�ɖ߂�܂��B
     * @return �؂���ꂵ�����[�U�[�`�b�v�B�؂����ł��Ȃ��ꍇ��nullptr
     */
    virtual LaserChip* dispatch(int prm_offset_frames = 1) override;

    /**
     * ���[�U�[�`�b�v�X�g�b�N�̒ǉ� .
     * �D���Ȃ����ǉ����ĉ������B
     * �ǉ�����΂���قǋʐ؂ꂪ�����ɂ���
     * @param prm_pLaserChip ���[�U�[�`�b�v
     */
    void addSubLast(LaserChip* prm_pLaserChip);

    /**
     * ���Z�b�g���̏��� .
     * �����o�[��S��inactivateImmed()���܂��B
     */
    virtual void onReset() override;


     virtual ~LaserChipDepository();

};

}
#endif /*LASERCHIPDEPOSITORY_H_*/
