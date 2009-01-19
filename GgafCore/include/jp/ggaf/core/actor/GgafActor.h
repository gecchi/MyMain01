#ifndef GGAFACTOR_H_
#define GGAFACTOR_H_
namespace GgafCore {


/**
 * �A�N�^�[�̊��N���X .
 * �{�v���O�����Ō����w�A�N�^�[�i���ҁj�x�Ƃ́A��ɃQ�[���̃L�����N�^�[��\���܂��B<BR>
 * �S�ẴA�N�^�[�N���X�́A�{�N���X�𒼐ځE�Ԑڌp�����Ȃ���΂Ȃ�܂���B<BR>
 * GgafElement�ɓ����蔻�����������d�g�݂��������N���X�ɂȂ��Ă��܂��B<BR>
 * ���e���v���[�g�N���X�� GgafNode �ƁAGgafElement �̐������Q�Ƃ̂��ƁB
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafActor : public GgafElement<GgafActor> {

    friend class GgafGod;
    friend class GgafMainActor;
    friend class GgafLordActor;
    friend class GgafHeadActor;
    friend class GgafDummyActor;
    friend class GgafScene;
    friend class GgafWorld;

private:

	/** ���݂̏����V�[�� */
    GgafScene* _pScene_Platform;


	/** ���[�v�p */
    GgafActor* _pActor_tmp;
    GgafActor* _pActor_tmp1;
    GgafActor* _pActor_tmp2;
    GgafActor* _pActor_tmp3;
    GgafActor* _pActor_tmp4;



	/**
	 * �����V�[����ݒ肷��B .
	 */
	void setScenePlatform(GgafScene* prm_pScene_Platform);

	/**
	 * �y���A�N�^�[ �� ���c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[�z�̏Փ˔��菈�������s���� .
	 * �{���\�b�h�� executeBumpChk2_WeAnd(GgafActor*)����Ăяo������p���\�b�h�B�ėp���͂Ȃ��B<BR>
	 * ���s����Ǝ��A�N�^�[��processHitLogic()���Ăяo���A���̌��ʂ�true�̏ꍇ(�Փ˂����ꍇ)�͎��g��processOnHit()�ƁA
	 * ����̃A�N�^�[��processOnHit()���Ăяo���B<BR>
	 * �߂�l�� bool �̓q�b�g����or���ĂȂ����Ӗ����镨�ł͂Ȃ��̂ŖY���ȁB<BR>
	 * @param	prm_pActor_Opponent	�Փ˔��肷�鎩�c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[
	 * @retval	true	�p�����[�^�����A�N�^�[
	 * @retval	false	�p�����[�^�����A�N�^�[�ȊO
	 */
	bool executeBumpChk2_MeAnd(GgafActor* prm_pActor_Opponent);

	/**
	 * �y���c���[�A�N�^�[ �� ���c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[�z���ďՓ˔��菈��(executeBumpChk_MeAnd)�����s���� .
	 * executeBumpChkRoundRobin2() ����Ăяo�����B<BR>
	 * executeBumpChk_WeAnd(GgafActor*)�Ɗ�{�I�ɓ����A���S���Y���ł��邪�A�K������Ă��鎩�A�N�^�[���m�����蔻��̃`�F�b�N���s���悤�ɂȂ��Ă��܂������_��<BR>
	 * ���E���A����ȏ�ċA���[�v���s��Ȃ��悤���Ă���B�c��̑g�ݍ��킹�͌㑱�̃��[�v�ŕ����B�i�n�Y�ł���j<BR>
	 * ���E���闝�R�́A���A�N�^�[�z�����m�̑�������ł��邽�߁A�P�����F�̑g�ݍ��킹�ōs����<BR>
	 *  Actor�@ �� Actor�A �@�@�i���͏Փ˔��肷��Ƃ����Ӗ��j<BR>
	 *  Actor�A �� Actor�@<BR>
	 * �̂悤�ɁA�Փ˔��菈�����d�����Ă��܂����߁A���������邽�ߓr���Ń��[�v���E����̂ł���B<BR>
	 * executeBumpChkRoundRobin2() ��p���\�b�h�Ƃ����Ă��ǂ��B�ėp���͖����B<BR>
	 * �߂�l�� bool �̓q�b�g����or���ĂȂ����Ӗ����镨�ł͂Ȃ��̂ŖY���ȁB<BR>
	 * @param	prm_pActor_Opponent	�Փ˔��肷�鎩�c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[
	 * @retval	true	�ċA�����ł��؂�
	 * @retval	false	�ċA�������s
	 */
	bool executeBumpChk2_WeAnd(GgafActor* prm_pActor_Opponent);



public:


	/** �A�N�^�[�J�n�V�X�e������ */
	DWORD _start_system_time;

  	/** �A�N�^�[�Փ˔���L���t���O */
	bool _canBump ;

	/** ����`�惌�x���̎��̃A�N�^�[ */
    GgafActor* _pNext_TheSameDrawDepthLevel;

	/**
	 * �R���X�g���N�^ .
	 * @param prm_name �A�N�^�[�̖��O
	 */
	GgafActor(string prm_name);

	/**
	 * �f�X�g���N�^ .
	 * ���c���[�A�N�^�[�̉�����s���܂��B
	 */
	virtual ~GgafActor();


	/**
	 * ���A�N�^�[�̏Փ˔���L����ݒ肷��B .
	 * @param	prm_canBump  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     */
	virtual void setBumpableAlone(bool prm_canBump);

	/**
	 * ���c���[�A�N�^�[�̏Փ˔���L����ݒ肷��B .
	 * @param	prm_canBump  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
	 */
	virtual void setBumpable(bool prm_canBump);

	/**
	 * �Փ˂ł��邩�ǂ���
	 * @return	bool true:�Փ˂ł���^false:�Փ˂ł��Ȃ�
	 */
	virtual bool canBump();

	/**
	 * �������Ă���V�[�����擾�B .
	 * @return	GgafScene*	�������Ă���V�[��
	 */
	virtual GgafScene* getPlatformScene();


	/**
	 * �y���A�N�^�[ �� ���A�N�^�[�z�̏Փ˔��菈�������s���� .
	 * ���g��processHitLogic()�̌��ʁA�Փ˂����ꍇ(true)�͎��g��processOnHit()�ƁA����A�N�^�[��processOnHit()�����s����� .
	 * @param	prm_pActor_Opponent	����̑��A�N�^�[
	 */
	virtual void executeBumpChk_MeAnd(GgafActor* prm_pActor_Opponent);

	/**
	 * �y���c���[�A�N�^�[ �� ���A�N�^�[�z�̏Փ˔��菈�������s���� .
	 * �����I�ɂ́A���c���[�A�N�^�[ �S�Ăɂ��āAexecuteBumpChk_MeAnd(GgafActor*) ���������s�B<BR>
	 * @param	prm_pActor_Opponent	����̑��A�N�^�[
	 */
	virtual void executeBumpChk_WeAnd(GgafActor* prm_pActor_Opponent);

	/**
     * �y���c���[�A�N�^�[ �� ���c���[�A�N�^�[�z�̑�������ŏՓ˔�������s���� .
	 * �����I�ɂ́A�����ł��� ���c���[�A�N�^�[ �̑S�Ăɂ��āAexecuteBumpChk_WeAnd(GgafActor*) ���������s���Ă��邾���B<BR>
	 * @param	prm_pActor_Opponent	����̑��c���[�A�N�^�[
	 */
	virtual void executeBumpChkRoundRobin(GgafActor* prm_pActor_Opponent);


	/**
     * �y���c���[�A�N�^�[ �� ���c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[�𒸓_�Ƃ���c���[�A�N�^�[�z�̑�������ŏՓ˔�������s����B.
	 * �����I�ɂ́A�����̃A�N�^�[ �̑S�Ăɂ��āAexecuteBumpChk2_WeAnd(GgafActor*) ���������s���Ă��邾���B<BR>	 * �A�����A�N�^�[���m�̏d���g�ݍ��킹�𖳎�����B <BR>
	 * @param	prm_pActor_Opponent	���c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[
	 */
	virtual void executeBumpChkRoundRobin2(GgafActor* prm_pActor_Opponent);

	/**
	 * ���A�N�^�[�Ƒ��A�N�^�[�ƏՓ˂������ǂ������肷��B .
	 * executeBumpChk_MeAnd(GgafActor*) �����s���ꂽ�ꍇ�ɌĂяo����邱�ƂɂȂ�܂��B<BR>
	 * ���ʃN���X�ŏՓ˔��胍�W�b�N���������Ă��������B<BR>
	 * @param	prm_pActor_Opponent	����̑��A�N�^�[
	 * @retval	true	�Փ˂��Ă���
	 * @retval	false	�Փ˂��Ă��Ȃ�
	 */
	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) = 0;


	/**
	 * ���A�N�^�[�ƏՓ˂������̏��� .
	 * processBumpChkLogic(GgafActor*) �̏ꍇ�ɌĂяo����邱�ƂɂȂ�܂��B<BR>
	 * �����́A����̃A�N�^�[�� processBumpChkLogic(GgafActor*) �̏ꍇ���Ăяo����܂��B<BR>
	 * �Փ˔���̌��ʁA�Փ˂����ꍇ�̏��������ʃN���X�������Ă��������B<BR>
	 * @param	prm_pActor_Opponent	�Փ˂��Ă��鑊��̃A�N�^�[�i�P�j
	 */
	virtual void processOnHit(GgafActor* prm_pActor_Opponent) = 0;


	/**
	 * �f�o�b�O�p�F�c���[�\����\��<BR>
	 */
	virtual void dump();

	/**
	 * �f�o�b�O�p�Fdump()����g�p�����<BR>
	 */
	virtual void dump(string prm_parent);

};


}
#endif /**GGAFACTOR_H_*/
