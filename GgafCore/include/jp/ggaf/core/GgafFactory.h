#ifndef GGAFGACTORY_H_
#define GGAFGACTORY_H_
namespace GgafCore {

/**
 * �C���X�^���X�����H��N���X .
 * ���C���X���b�h����A����(GgafOrder)��n�����ƁA�ʃX���b�h�ɂ��̃C���X�^���X�𐶐�(new)�����܂��B<BR>
 * �o���オ�����C���X�^���X(���i�ƌĂ�)�̃|�C���^�B�͍H��ŃX�g�b�N����A���C����������K�v�ɉ����ď��i�����o�����Ƃ��o���܂�<BR>
 * �y�⑫�z<BR>
 * �Ȃ�����Ȃ�₱������������̂��B����́A��ʃC���X�^���X�����鎞�_�Ő������Ȃ���΂����Ȃ��悤�Ȍ��ŁA���炩�ɏ��������������߁B<BR>
 * �X�e�[�W�̃��[�f�B���O��A�̂悭�������̂ł����A�{�X�O���ŁA�Q�[���i�s����u�u�E�b�v�Ǝ~�܂�(�킩�邩�Ȃ�)�̂𖳂����������������߂ł��B<BR>
 * �����𑁂߂ɂ��Ă����ƁA�X���[�Y�ɃQ�[�����i�s����͂����Ɩژ_�ށB<BR>
 * @version 1.00
 * @since 2007/12/27
 * @author Masatoshi Tsuge
 */
class GgafFactory {
    friend class GgafGod;

private:
    /** �擪�̒��� */
    static GgafOrder* ROOT_ORDER;
    /** ���ݐ������̒��� */
    static GgafOrder* CREATING_ORDER;
    //CREATING_ORDER �́A�S�Đ����ς݂̏ꍇ�A�ŏI�������w���Â���
    //�S�Đ����ς݂��A���i���S�Ď擾����Ă��܂����ꍇ�� NULL �ɂȂ�B
    //_is_last_order_flg == false ����ɔ��肵�A�ŏI�����łȂ��Ȃ�����i�V�K����������΁j�A
    //�������s���Ď��ɐi�߂�B _is_last_order_flg == false �ɂȂ�܂Ő������Â���


    /**
     * �H��ɒ������s�� .
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
     * �����������i�����o�� .
     * �������������ꍇ�A��������������܂ő҂B<BR>
     * @param   prm_id	��������ID�ԍ�
     * @return	���i�̃|�C���^
     */
    static void* obtain(unsigned long prm_id);

public:
    /** [r]�S�~��(�s�v�ȃA�N�^�[�u����) */
    static GgafGarbageBox* _pGarbageBox;

    /** [r]�|���I�u�W�F�N�g�� */
    static int _cnt_cleaned;

    /** [r]�����t���O(�_�����삷��) */
    static bool _is_working_flg;
    /** [r]�x�ރt���O */
    static bool _have_to_rest_flg;
    /** [r]�x�ł���t���O */
    static bool _is_resting_flg;
    /** [r]���S�X�I�� */
    static bool _was_finished_flg;

    /**
     * �H��ɃA�N�^�[�쐬�̒������s���i���C���X���b�h���g�p�j .
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
     * �H��ɃV�[���쐬�̒������s���i���C���X���b�h���g�p�j .
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
     * ���������A�N�^�[�����o���B�i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * �������������ꍇ�A��������������܂ő҂B<BR>
     * @param   prm_id	��������ID
     * @return	�������ꂽ�A�N�^�[�̃|�C���^
     */
    static GgafMainActor* obtainActor(unsigned long prm_id);

    /**
     * ���������V�[�������o���B�i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * �������������ꍇ�A��������������܂ő҂B<BR>
     * @param   prm_id	��������ID
     * @return	�������ꂽ�V�[���̃|�C���^
     */
    static GgafMainScene* obtainScene(unsigned long prm_id);

    /**
     * �����������i���o���オ���Ă��邩���ׂ�B�i���C���X���b�h���g�p�j .
     * @return  �i���(-2:�H�ꎩ�̂������ĂȂ�/-1:�������炵�Ă��Ȃ�/0:�����ς݂ōH�ꖢ����/1:������/2:�����ς݁j
     */
    static int chkProgress(unsigned long prm_id);

    /**
     * �H���|������i���C���X���b�h���g�p�j .
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
     * �ғ�����B�i�H��X���b�h���C�����[�v�j.
     * �_�iGgafGod�j�������ݒ莞�ɕʃX���b�h�ň�x���s����A���\�b�h�����Ŗ������[�v���Ă܂��B<BR>
     * ����������΍쐬���A�X�g�b�N���܂��B<BR>
     * �_�����ʂ܂Łi�A�v���I���܂Łj�i���ɉғ����������ł���B<BR>
     */
    static unsigned __stdcall work(void* prm_arg);

    /**
     * �H��ꎞ�x�~���w�� �i���C���X���b�h���g�p�j .
     * �������Ăяo���Ă������ɋx�~��ԂɂȂ�Ƃ͌���܂���B<BR>
     * isResting() �Ŋ��S�x�~����܂Œ��ׂ鑱����K�v������܂��B<BR>
     */
    static void beginRest() {
        _TRACE_("GgafFactory::beginRest() ���_���H��A�x�e���Ȃ���");
        _have_to_rest_flg = true;
    }

    /**
     * �H��̏�Ԃ��擾�i���C���X���b�h���g�p�j .
     * @return true=�x�~���/false=�ғ����
     */
    static bool isResting() {
        if (_is_resting_flg) {
            _TRACE_("GgafFactory::isResting() �H��x�~���");
        } else {
            _TRACE_("GgafFactory::isResting() �H��ғ����");
        }
        return _is_resting_flg;
    }

    /**
     * �H��x�~�̉������w�� �i���C���X���b�h���g�p�j .
     */
    static void finishRest() {
        _TRACE_("GgafFactory::beginRest() ���_���H��A�x�e�͂����܂��B���������I");
        _have_to_rest_flg = false;
    }
};

}
#endif /*GGAFGACTORY_H_*/
