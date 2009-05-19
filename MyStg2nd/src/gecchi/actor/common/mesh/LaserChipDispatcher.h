#ifndef LASERCHIPDISPATCHER_H_
#define LASERCHIPDISPATCHER_H_
namespace MyStg2nd {

/**
 * ���[�U�[�`�b�v�g���܂킵�Ǘ��N���X .
 * new ���� initialize()�܂ŁA���͐����ύX���L���ȃp�����[�^<BR>
 * �E_num_chip_interval ����e�؂�t���[�����i�f�t�H���g:3�j<BR>
 * �E_pSeCon_Laser ��� ���[�U�[�`�b�v���ˎ�SE�i�f�t�H���g:NULL�j<BR>
 */
class LaserChipDispatcher : public GgafDx9LibStg::ActorDispatcher {
    friend class LaserChip;
private:
    /** �ێ����郌�[�U�[�`�b�v�� */
    int _num_chip_max;
    /** ���������[�U�[�`�b�v�� */
    int _num_chip_active;
    /** ���[�U�[�`�b�v�ؒf���ꂽ�t���O(true=�A�����ˏ�Ԃ͎Ւf����Ă���/false=�A�����ˏ��) */
    bool _is_tear_laser;
    /** �O��i�O�t���[���j�擾���ꂽ���[�U�[�`�b�v */
    LaserChip* _pChip_prev_employ;
    /** �O��i�O�t���[���j�擾���ꂽ���[�U�[�`�b�v�̎擾���ꂽ���_�̊����t���[�� */
    DWORD _lifeframe_prev_employ;
    /** ���[�U�[�`�b�v�A���擾�J�E���g */
    int _num_continual_employ_count;
    /** ���[�U�[�`�b�v�A�����擾�J�E���g */
    int _num_interval_frame_count;

public:
    /** �e�؂�t���[�����i�����ύX�^�f�t�H���g=3�j */
    int _num_chip_interval;
    /** ���[�U�[�`�b�v���ˎ�SE�i�����ύX�^�f�t�H���g=NULL�j */
    GgafDx9Core::GgafDx9SeConnection* _pSeConnection;

    LaserChipDispatcher(const char* prm_name);

	virtual void processBehavior();

	virtual LaserChip* employ();

	void addLaserChip(LaserChip* prm_pLaserChip);

 	virtual ~LaserChipDispatcher();

};

}
#endif /*LASERCHIPDISPATCHER_H_*/
