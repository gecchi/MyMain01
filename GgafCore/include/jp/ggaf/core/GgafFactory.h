#ifndef GGAFGACTORY_H_
#define GGAFGACTORY_H_
namespace GgafCore {

/**
 * �C���X�^���X�����H��N���X .
 * ���C����������A����(GgafOrder)��n�����ƁA�ʃX���b�h�ɂ��̃C���X�^���X�𐶐�(new)�����܂��B<BR>
 * �o���オ�����C���X�^���X(���i�ƌĂ�)�̃|�C���^�B�͍H��ŃX�g�b�N����A���C����������K�v�ɉ����ď��i�����o�����Ƃ��o���܂�<BR>
 * �y�⑫�z<BR>
 * �Ȃ�����Ȃ�₱������������̂��B����́A��ʃC���X�^���X�����鎞�_�Ő������Ȃ���΂����Ȃ��悤�Ȍ��ŁA���炩�ɏ��������������߁B<BR>
 * �܂�A�̂悭�������X�e�[�W�ƃX�e�[�W�̊Ԃ�A�{�X�O���ŁA�u�E�b�v�ƈ�u�~�܂�(��ɺ���)�̂𖳂����������������߁A���̃N���X���쐬�B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
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
     * @param prm_id	��������ID�ԍ�
     * @param prm_pFunc	���ۂɐ����������s���֐��̃|�C���^
     * @param prm_pArg1	���̈���1
     * @param prm_pArg2	���̈���2
     * @param prm_pArg3	���̈���3
     */
    static void order(unsigned long prm_id,
                      GgafObject* (*prm_pFunc)(void*, void*, void*),
                      void* prm_pArg1,
                      void* prm_pArg2,
                      void* prm_pArg3);

    /**
     * �����������i�����o���B<BR>
     * �������������ꍇ�A��������������܂ő҂B<BR>
     * @param   prm_id	��������ID�ԍ�
     * @return	���i�̃|�C���^
     */
    static void* obtain(unsigned long prm_id);

public:
    /** �S�~��(�s�v�ȃA�N�^�[�u����) */
    static GgafGarbageBox* _pGarbageBox;

    /** �|���I�u�W�F�N�g�� */
    static int _s_iCountCleanedNode;

    /** �����t���O(�_�����삷��) */
    static bool _isWorking;
    /** �x�ރt���O */
    static bool _isRest;
    /** �x�ł���t���O */
    static bool _isResting;
    /** ���S�X�I�� */
    static bool _isFinish;

    /**
     * �H��ɃA�N�^�[�쐬�̒������s�� .
     * ���C���������Ăяo���܂��B<BR>
     * @param prm_id	��������ID�ԍ�
     * @param prm_pFunc	���ۂɐ����������s���֐��̃|�C���^
     * @param prm_pArg1	���̈���1
     * @param prm_pArg2	���̈���2
     * @param prm_pArg3	���̈���3
     */
    template<class X>
    static void orderActor(unsigned long prm_id,
                           X* (*prm_pFunc)(void*, void*, void*),
                           void* prm_pArg1,
                           void* prm_pArg2,
                           void* prm_pArg3) {
        order(prm_id, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * �H��ɃV�[���쐬�̒������s�� .
     * ���C���������Ăяo���܂��B<BR>
     * @param prm_id	��������ID�ԍ�
     * @param prm_pFunc	���ۂɐ����������s���֐��̃|�C���^
     * @param prm_pArg1	���̈���1
     * @param prm_pArg2	���̈���2
     * @param prm_pArg3	���̈���3
     */
    template<class X>
    static void orderScene(unsigned long prm_id,
                           X* (*prm_pFunc)(void*, void*, void*),
                           void* prm_pArg1,
                           void* prm_pArg2,
                           void* prm_pArg3) {
        order(prm_id, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * ���������A�N�^�[�����o���B .
     * ���C���������Ăяo���܂��B<BR>
     * �������������ꍇ�A��������������܂ő҂B<BR>
     * @param   prm_id	��������ID
     * @return	�������ꂽ�A�N�^�[�̃|�C���^
     */
    static GgafMainActor* obtainActor(unsigned long prm_id);

    /**
     * ���������V�[�������o���B .
     * ���C���������Ăяo���܂��B<BR>
     * �������������ꍇ�A��������������܂ő҂B<BR>
     * @param   prm_id	��������ID
     * @return	�������ꂽ�V�[���̃|�C���^
     */
    static GgafMainScene* obtainScene(unsigned long prm_id);

    /**
     * �H���|������<BR>
     * ���C�������̐_���Ăяo���܂��B<BR>
     * ROOT_ORDER ���w���Ă��鐻�i�̘A�����X�g��S�ĉ������<BR>
     * ���ӁF�K���ȉ��̂悤�ɃN���e�B�J���Z�N�V�����ň͂�ŌĂяo���Ă��������I�B<BR>
     * ���R�[�h�၄ <BR>
     *  ___BeginSynchronized; // ----->�r���J�n<BR>
     * GgafFactory::clean();<BR>
     *  ___EndSynchronized; // <----- �r���I��<BR>
     */
    static void clean();

    /**
     * �ғ�����B<BR>
     * �ʃX���b�h�Ŗ������[�v���Ă܂��B����������΍쐬���A�X�g�b�N���܂��B<BR>
     * �_�������ݒ莞�ɕʃX���b�h�ň�x���s����B�_�����ʂ܂Łi�A�v���I���܂Łj�i���ɉғ����������ł���B<BR>
     */
    static unsigned __stdcall work(void* prm_arg);

    /**
     * �ꎞ�x�~���w�� .
     * �������Ăяo���Ă������ɋx�~��ԂɂȂ�Ƃ͌���܂���B<BR>
     * isResting() �Œ��ׂ�K�v������܂��B<BR>
     */
    static void beginRest() {
        _TRACE_("GgafFactory::beginRest() ���_���H��A�x�e���Ȃ���");
        _isRest = true;
    }

    /**
     * �H��̏�Ԃ��擾<BR>
     * @return true=�x�~���/false=�ғ����
     */
    static bool isResting() {
        if (_isResting) {
            _TRACE_("GgafFactory::isResting() �H��x�~���");
        } else {
            _TRACE_("GgafFactory::isResting() �H��ғ����");
        }
        return _isResting;
    }

    /**
     * �x�~�̉������w�� .
     */
    static void finishRest() {
        _TRACE_("GgafFactory::beginRest() ���_���H��A�x�e�͂����܂��B���������I");
        _isRest = false;
    }
};

}
#endif /*GGAFGACTORY_H_*/
