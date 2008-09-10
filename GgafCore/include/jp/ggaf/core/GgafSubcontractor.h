#ifndef GGAFSUBCONTRACTOR_H_
#define GGAFSUBCONTRACTOR_H_

class GgafSubcontractor {
	friend class GgafGod;

private:
	static GgafGod* _pGod;

	/** �擪�̒��� */
	static GgafOrder* _pOrder_First;
	/** ���ݐ������̒��� */
	static GgafOrder* _pOrder_InManufacturing;
	//�S�Đ����ς݂̏ꍇ�A�ŏI�������w���Â���
	//�S�Đ����ς݂��A���i���S�Ď擾����Ă��܂����ꍇ�� NULL �ɂȂ�B
	//_isLastOrder == false ����ɔ��肵�A�ŏI�����łȂ��Ȃ�����i�V�K����������΁j�A
	//�������s���Ď��ɐi�߂�B _isLastOrder == false �ɂȂ�܂Ő������Â���


	/**
	 * �H��ɒ������s��<BR>
	 * @param   prm_id	��������ID
	 * 			prm_functionForBuild	���ۂɐ����������s���֐��̃|�C���^<BR>
	 * 			prm_argumentForBuild	���̈���<BR>
	 */
	static void order(string prm_id, GgafObject* (*prm_functionForBuild)(void*), void* prm_argumentForBuild);

	/**
	 * �����������i�����o���B<BR>
	 * �������������ꍇ�A��������������܂ő҂B<BR>
	 * @param   prm_id	��������ID
	 * @return	���i�̃|�C���^
	 */
	static void* obtain(string prm_id);

public:
	/** �����t���O(�_�����삷��) */
	static bool _isWorking;

	/**
	 * �H��ɃA�N�^�[�쐬�̒������s��<BR>
	 * @param   prm_id	��������ID
	 * 			prm_functionForBuild	���ۂɐ����������s���֐��̃|�C���^<BR>
	 * 			prm_argumentForBuild	���̈���<BR>
	 */
	static void orderActor(string prm_id, GgafMainActor* (*prm_functionForBuild)(void*), void* prm_argumentForBuild);

	/**
	 * �H��ɃV�[���쐬�̒������s��<BR>
	 * @param   prm_id	��������ID
	 * 			prm_functionForBuild	���ۂɐ����������s���֐��̃|�C���^<BR>
	 * 			prm_argumentForBuild	���̈���<BR>
	 */
	static void orderScene(string prm_id, GgafMainScene* (*prm_functionForBuild)(void*), void* prm_argumentForBuild);

	/**
	 * ���������A�N�^�[�����o���B<BR>
	 * �������������ꍇ�A��������������܂ő҂B<BR>
	 * @param   prm_id	��������ID
	 * @return	�������ꂽ�A�N�^�[�̃|�C���^
	 */
	static GgafMainActor* obtainActor(string prm_id);

	/**
	 * ���������V�[�������o���B<BR>
	 * �������������ꍇ�A��������������܂ő҂B<BR>
	 * @param   prm_id	��������ID
	 * @return	�������ꂽ�V�[���̃|�C���^
	 */
	static GgafMainScene* obtainScene(string prm_id);

	/**
	 * �H���|������<BR>
	 * _pOrder_First ���w���Ă��鐻�i�̘A�����X�g��S�ĉ������<BR>
	 * ���ӁF�K���ȉ��̂悤�ɃN���e�B�J���Z�N�V�����ň͂�ŌĂяo���Ă��������I�B<BR>
	 * ���R�[�h�၄ <BR>
	 * ::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n<BR>
	 * GgafSubcontractor::clean();<BR>
	 * ::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��<BR>
	 */
	static void clean();

	/**
	 * �ғ�����B<BR>
	 * �_�������ݒ莞�ɕʃX���b�h�ň�x���s����B�_�����ʂ܂Łi�A�v���I���܂Łj�i���ɉғ����������ł���B<BR>
	 */
	static unsigned __stdcall work(void* prm_arg);

};



#endif /*GGAFSUBCONTRACTOR_H_*/
