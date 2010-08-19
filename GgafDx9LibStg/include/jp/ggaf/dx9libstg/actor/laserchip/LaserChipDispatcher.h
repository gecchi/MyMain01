#ifndef LASERCHIPDISPATCHER_H_
#define LASERCHIPDISPATCHER_H_
namespace GgafDx9LibStg {

/**
 * ���[�U�[�`�b�v�g���܂킵�Ǘ��N���X .
 * new ������ addSubLast ���\�b�h�� LaserChip�C���X�^���X���D���Ȍ��o�^���Ă��������B<BR>
 * new ���� initialize()�܂ŁA���͐����ύX���L���ȃp�����[�^<BR>
 * �E_num_chip_interval �E�E�E�e�؂�t���[�����i�f�t�H���g:20�j<BR>
 * �E_pSeCon_Laser �E�E�E ���[�U�[�`�b�v���ˎ�SE�i�f�t�H���g:NULL�j<BR>
 */
class LaserChipDispatcher : public GgafCore::GgafActorDispatcher {
    friend class LaserChip;
public:
    /** [r]�ێ����郌�[�U�[�`�b�v��(�ǂݎ���p) */
    int _num_chip_max;
    /** [r]���������[�U�[�`�b�v��(�ǂݎ���p) */
    int _num_chip_active;
    /** [r]���[�U�[�`�b�v�ؒf���ꂽ�t���O(�ǂݎ���p�Atrue=�A�����ˏ�Ԃ͎Ւf����Ă���/false=�A�����ˏ��) */
    bool _is_tear_laser;
    /** [r]�O��i�O�t���[���j�擾���ꂽ���[�U�[�`�b�v(�ǂݎ���p) */
    LaserChip* _pChip_prev_employ;
    /** [r]�O��i�O�t���[���j�擾���ꂽ���[�U�[�`�b�v�̎擾���ꂽ���_�̊����t���[��(�ǂݎ���p) */
    frame _frame_of_behaving_prev_employ;
    /** [r]���[�U�[�`�b�v�A���擾�J�E���g(�ǂݎ���p) */
    int _num_continual_employ_count;
    /** [r]���[�U�[�`�b�v�A�����擾�J�E���g(�ǂݎ���p) */
    int _num_interval_frame_count;

    /** [r/w]�e�؂�Ɉڍs����`�b�v�̘A���擾���B�i�ǂݏ����^�f�t�H���g�FaddSubLast()������ _num_chip_max �Ɠ����ɂȂ��Ă���B */
    int _num_continual_employ_max;
    /** [r/w]�e�؂�t���[�����i�ǂݏ����^�f�t�H���g=20�j */
    int _num_chip_interval;
    /** [r/w]���[�U�[���ˎ��G�t�F�N�g�B�s�v�̏ꍇ��NULL��ݒ肷�� */
    GgafDx9Core::GgafDx9DrawableActor* _pEffectActor_Irradiate;

    LaserChipDispatcher(const char* prm_name);

    /**
     * LaserChipDispatcher��ݒ肷��B
     * @param prm_num_continual_employ_max �����I�ɒe�؂�Ɉڍs����`�b�v�̘A���擾���B
     * @param prm_num_chip_interval �e�؂�t���[����
     * @param prm_pEffectActor_Irradiate �V�[�������ςݔ��˒��G�t�F�N�g(�s�v����NULL)�B����͌Ăь��ŁB
     */
    virtual void config(int prm_num_continual_employ_max,
                        UINT32 prm_num_chip_interval,
                        GgafDx9Core::GgafDx9DrawableActor* prm_pEffectActor_Irradiate = NULL);

    virtual void processBehavior() override {
    }

    virtual void processFinal() override;

    /**
     * ���[�U�[�`�b�v�̎؂��������݂� .
     * �X�g�b�N�؂�̏ꍇ�� NULL ���Ԃ�B�K���`�F�b�N���邱�ƁB
     * �g���I���� sayonara() ���Ainactivate() �����s���Ă��������B�����I�ɃX�g�b�N�ɖ߂�܂��B
     * @return �؂���ꂵ�����[�U�[�`�b�v�B�؂����ł��Ȃ��ꍇ��NULL
     */
    virtual LaserChip* employ() override;

    /**
     * ���[�U�[�`�b�v�X�g�b�N�̒ǉ� .
     * �D���Ȃ����ǉ����ĉ������B
     * �ǉ�����΂���قǋʐ؂ꂪ�����ɂ���
     * @param prm_pLaserChip ���[�U�[�`�b�v
     */
    void addSubLast(LaserChip* prm_pLaserChip);

     virtual ~LaserChipDispatcher();

};

}
#endif /*LASERCHIPDISPATCHER_H_*/
