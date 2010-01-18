#ifndef LASERCHIPDISPATCHER_H_
#define LASERCHIPDISPATCHER_H_
namespace MyStg2nd {

/**
 * ���[�U�[�`�b�v�g���܂킵�Ǘ��N���X .
 * new ������ addSubLast ���\�b�h�� LaserChip�C���X�^���X���D���Ȍ��o�^���Ă��������B<BR>
 * new ���� initialize()�܂ŁA���͐����ύX���L���ȃp�����[�^<BR>
 * �E_num_chip_interval ����e�؂�t���[�����i�f�t�H���g:20�j<BR>
 * �E_pSeCon_Laser ��� ���[�U�[�`�b�v���ˎ�SE�i�f�t�H���g:NULL�j<BR>
 */
class LaserChipDispatcher : public GgafDx9LibStg::ActorDispatcher {
    friend class LaserChip;
public:
    /** �ێ����郌�[�U�[�`�b�v��(�ǂݎ���p) */
    int _num_chip_max;
    /** ���������[�U�[�`�b�v��(�ǂݎ���p) */
    int _num_chip_active;
    /** ���[�U�[�`�b�v�ؒf���ꂽ�t���O(�ǂݎ���p�Atrue=�A�����ˏ�Ԃ͎Ւf����Ă���/false=�A�����ˏ��) */
    bool _is_tear_laser;
    /** �O��i�O�t���[���j�擾���ꂽ���[�U�[�`�b�v(�ǂݎ���p) */
    LaserChip* _pChip_prev_employ;
    /** �O��i�O�t���[���j�擾���ꂽ���[�U�[�`�b�v�̎擾���ꂽ���_�̊����t���[��(�ǂݎ���p) */
    DWORD _frame_of_active_prev_employ;
    /** ���[�U�[�`�b�v�A���擾�J�E���g(�ǂݎ���p) */
    int _num_continual_employ_count;
    /** ���[�U�[�`�b�v�A�����擾�J�E���g(�ǂݎ���p) */
    int _num_interval_frame_count;


    /** �e�؂�t���[�����i�ǂݏ����^�f�t�H���g=20�j */
    int _num_chip_interval;
    /** ���[�U�[�`�b�v���ˎ�SE�i�ǂݏ����^�f�t�H���g=NULL�j */
    GgafDx9Core::GgafDx9SeConnection* _pSeConnection;

    LaserChipDispatcher(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * ���[�U�[�`�b�v�̎؂��������݂� .
     * �X�g�b�N�؂�̏ꍇ�� NULL ���Ԃ�B�K���`�F�b�N���邱�ƁB
     * �g���I���� inactivate() �����s���Ă��������B�����I�ɃX�g�b�N�ɖ߂�܂��B
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
