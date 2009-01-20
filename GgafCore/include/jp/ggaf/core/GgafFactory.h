#ifndef GGAFGACTORY_H_
#define GGAFGACTORY_H_
namespace GgafCore {


/**
 * �C���X�^���X�����H��N���X .
 * ���C����������A����(GgafOrder)��n�����ƁA�ʃX���b�h�ɂ��̃C���X�^���X�𐶐�(new)�����܂��B<BR>
 * �o���オ�����C���X�^���X(���i�ƌĂ�)�̃|�C���^�B�͍H��ŃX�g�b�N����A���C����������K�v�ɉ����ď��i�����o�����Ƃ��o���܂�<BR>
 * �y�⑫�z<BR>
 * �X�e�[�W�ƃX�e�[�W�̊Ԃ�A�{�X�O���A��ʃC���X�^���X�𐶐����Ȃ���΂����Ȃ����ŁA���炩�ɏ��������������B<BR>
 * �܂�A�̂悭�������u�E�b�v�Ǝ~�܂�̂𖳂��������������ߐ��܂ꂽ(��ɺ���)<BR>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafFactory {
	friend class GgafGod;

private:
	static GgafGod* _pGod;


	/** �擪�̒��� */
	static GgafOrder* ROOT_ORDER;
	/** ���ݐ������̒��� */
	static GgafOrder* CREATING_ORDER;
	//�S�Đ����ς݂̏ꍇ�A�ŏI�������w���Â���
	//�S�Đ����ς݂��A���i���S�Ď擾����Ă��܂����ꍇ�� NULL �ɂȂ�B
	//_isLastOrder == false ����ɔ��肵�A�ŏI�����łȂ��Ȃ�����i�V�K����������΁j�A
	//�������s���Ď��ɐi�߂�B _isLastOrder == false �ɂȂ�܂Ő������Â���


	/**
	 * �H��ɒ������s��<BR>
	 * @param   prm_id	��������ID
	 * 			prm_pFunc	���ۂɐ����������s���֐��̃|�C���^<BR>
	 * 			prm_pArg	���̈���<BR>
	 */
	static void order(std::string prm_id, GgafObject* (*prm_pFunc)(void*, void*), void* prm_pArg1, void* prm_pArg2);

	/**
	 * �����������i�����o���B<BR>
	 * �������������ꍇ�A��������������܂ő҂B<BR>
	 * @param   prm_id	��������ID
	 * @return	���i�̃|�C���^
	 */
	static void* obtain(std::string prm_id);

public:
	/** �S�~��(�s�v�ȃA�N�^�[�u����) */
	static GgafGarbageBox* _pGarbageBox;

	/** �|���I�u�W�F�N�g�� */
	static int _s_iCountCleanedNode;


	/** �����t���O(�_�����삷��) */
	static bool _isWorking;

	/** ���S�X�I�� */
	static bool _isFinish;

	/**
	 * �H��ɃA�N�^�[�쐬�̒������s��<BR>
	 * @param   prm_id	��������ID
	 * 			prm_pFunc	���ۂɐ����������s���֐��̃|�C���^<BR>
	 * 			prm_pArg	���̈���<BR>
	 */
	template <class X>
	static void orderActor(std::string prm_id, X* (*prm_pFunc)(void*, void*), void* prm_pArg1, void* prm_pArg2) {
		order(prm_id, (GgafObject* (*)(void*, void*))prm_pFunc, prm_pArg1, prm_pArg2);
	}

	/**
	 * �H��ɃV�[���쐬�̒������s��<BR>
	 * @param   prm_id	��������ID
	 * 			prm_pFunc	���ۂɐ����������s���֐��̃|�C���^<BR>
	 * 			prm_pArg	���̈���<BR>
	 */
	template <class X>
	static void orderScene(std::string prm_id, X* (*prm_pFunc)(void*, void*), void* prm_pArg1, void* prm_pArg2) {
		order(prm_id, (GgafObject* (*)(void*, void*))prm_pFunc, prm_pArg1, prm_pArg2);
	}

	/**
	 * ���������A�N�^�[�����o���B<BR>
	 * �������������ꍇ�A��������������܂ő҂B<BR>
	 * @param   prm_id	��������ID
	 * @return	�������ꂽ�A�N�^�[�̃|�C���^
	 */
	static GgafMainActor* obtainActor(std::string prm_id);

	/**
	 * ���������V�[�������o���B<BR>
	 * �������������ꍇ�A��������������܂ő҂B<BR>
	 * @param   prm_id	��������ID
	 * @return	�������ꂽ�V�[���̃|�C���^
	 */
	static GgafMainScene* obtainScene(std::string prm_id);

	/**
	 * �H���|������<BR>
	 * ROOT_ORDER ���w���Ă��鐻�i�̘A�����X�g��S�ĉ������<BR>
	 * ���ӁF�K���ȉ��̂悤�ɃN���e�B�J���Z�N�V�����ň͂�ŌĂяo���Ă��������I�B<BR>
	 * ���R�[�h�၄ <BR>
	 * ::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n<BR>
	 * GgafFactory::clean();<BR>
	 * ::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��<BR>
	 */
	static void clean();

	/**
	 * �ғ�����B<BR>
	 * �_�������ݒ莞�ɕʃX���b�h�ň�x���s����B�_�����ʂ܂Łi�A�v���I���܂Łj�i���ɉғ����������ł���B<BR>
	 */
	static unsigned __stdcall work(void* prm_arg);

};


}
#endif /*GGAFGACTORY_H_*/
