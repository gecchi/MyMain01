#ifndef GGAFCORE_GGAFGACTORY_H_
#define GGAFCORE_GGAFGACTORY_H_
#include "GgafCommonHeader.h"

#ifndef _MSC_VER
    #include <atomic>
#endif

#define ORDER_ID_MAX     (0xffffffffffffffffULL)

namespace GgafCore {

/**
 * �C���X�^���X�����H��N���X .
 * ���C���X���b�h�i���̐��̃V�[���c���[�j����A����(GgafOrder)��n�����ƁA�ʃX���b�h�i�H��j�ɁA
 * ���̃C���X�^���X�𐶐�(new)�����܂��B<BR>
 * �o���オ�����C���X�^���X(���i�ƌĂ�)�̃|�C���^�B�͍H��ŃX�g�b�N����A���C����������K�v�ɉ����ď��i��
 * ���o�����Ƃ��o���܂�<BR>
 * �y�⑫�z<BR>
 * �Ȃ�����Ȃ�₱������������̂��B����́A��ʃC���X�^���X�����鎞�_�Ő������Ȃ���΂����Ȃ��悤�Ȍ��ŁA
 * ���炩�ɏ��������������߁B<BR>
 * �X�e�[�W�̃��[�f�B���O��A�̂悭�������̂ł����A�{�X�O���ŁA�Q�[���i�s����u�u�E�b�v�Ǝ~�܂�(�킩�邩�Ȃ�)
 * �̂𖳂����������������߂ł��B<BR>
 * �����𑁂߂ɂ��Ă����ƁA�X���[�Y�ɃQ�[�����i�s����͂����Ɩژ_�ށB<BR>
 * @version 1.00
 * @since 2007/12/27
 * @author Masatoshi Tsuge
 */
class GgafFactory {
    friend class GgafGod;

private:
    /**
     * �H��ɒ������s�� .
     * @param prm_order_id	��������ID�ԍ�
     * @param prm_pFunc	���ۂɐ����������s���֐��̃|�C���^
     * @param prm_pOrderer ������
     * @param prm_pArg1	�����������s���֐��ւ̈���1
     * @param prm_pArg2	�����������s���֐��ւ̈���2
     * @param prm_pArg3	�����������s���֐��ւ̈���3
     */
    static void order(uint64_t prm_order_id,
                      GgafObject* (*prm_pFunc)(void*, void*, void*),
                      GgafObject* prm_pOrderer,
                      void* prm_pArg1,
                      void* prm_pArg2,
                      void* prm_pArg3);

    /**
     * �����������i�����o�� .
     * �������������ꍇ�A��������������܂ő҂B<BR>
     * @param   prm_order_id	��������ID�ԍ�
     * @param   prm_org �������i�f�o�b�O�p�j
     * @return	���i�̃|�C���^
     */
    static void* obtain(uint64_t prm_order_id, GgafObject* prm_org);

public:
    /** �擪�̒��� */
    static GgafOrder* ROOT_ORDER;
    /** ���ݐ������̒��� */
    static GgafOrder* CREATING_ORDER;
    //CREATING_ORDER �́A�S�Đ����ς݂̏ꍇ�A�ŏI�������w���Â���
    //�S�Đ����ς݂��A���i���S�Ď擾����Ă��܂����ꍇ�� nullptr �ɂȂ�B
    //_is_last_order_flg == false ����ɔ��肵�A�ŏI�����łȂ��Ȃ�����i�V�K����������΁j�A
    //�������s���Ď��ɐi�߂�B _is_last_order_flg == false �ɂȂ�܂Ő������Â���

#ifdef _MSC_VER
    //x86�n�Ȃ�΃A�g�~�b�N��������E�E�E�E�E�E�E�E�B
    /** [r]�����t���O(�_�����삷��) */
    static volatile bool _is_working_flg;
    /** [r]�x�ރt���O */
    static volatile bool _have_to_rest_flg;
    /** [r]�x�ł���t���O */
    static volatile bool _is_resting_flg;
    /** [r]���S�X�I�� */
    static volatile bool _was_finished_flg;
#else
    /** [r]�����t���O(�_�����삷��) */
    static volatile std::atomic<bool> _is_working_flg;
    /** [r]�x�ރt���O */
    static volatile std::atomic<bool> _have_to_rest_flg;
    /** [r]�x�ł���t���O */
    static volatile std::atomic<bool> _is_resting_flg;
    /** [r]���S�X�I�� */
    static volatile std::atomic<bool> _was_finished_flg;
#endif
public:
    /**
     * �H��ɃA�N�^�[�쐬�̒������s���i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * @param prm_id    ��������ID�ԍ�
     * @param prm_pFunc ���ۂɐ����������s���֐��̃|�C���^
     * @param prm_pOrderer �������I�u�W�F�N�g
     * @param prm_pArg1 �����������s���֐��ւ̈���1
     * @param prm_pArg2 �����������s���֐��ւ̈���2
     * @param prm_pArg3 �����������s���֐��ւ̈���3
     */
    template<class X>
    static void orderActor(uint64_t prm_order_id,
                           X* (*prm_pFunc)(void*, void*, void*),
                           GgafObject* prm_pOrderer,
                           void* prm_pArg1,
                           void* prm_pArg2,
                           void* prm_pArg3) {
        order(prm_order_id, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pOrderer, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * �H��ɃV�[���쐬�̒������s���i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * @param prm_id	��������ID�ԍ�
     * @param prm_pFunc	���ۂɐ����������s���֐��̃|�C���^
     * @param prm_pOrderer �������I�u�W�F�N�g
     * @param prm_pArg1	�����������s���֐��ւ̈���1
     * @param prm_pArg2	�����������s���֐��ւ̈���2
     * @param prm_pArg3	�����������s���֐��ւ̈���3
     */
    template<class X>
    static void orderScene(uint64_t prm_order_id,
                           X* (*prm_pFunc)(void*, void*, void*),
                           GgafObject* prm_pOrderer,
                           void* prm_pArg1,
                           void* prm_pArg2,
                           void* prm_pArg3) {
        order(prm_order_id, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pOrderer, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * ���������A�N�^�[�����o���B�i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * �������������ꍇ�A��������������܂ő҂B<BR>
     * @param   prm_id	��������ID
     * @param   prm_org �������i�f�o�b�O�p�j
     * @return	�������ꂽ�A�N�^�[�̃|�C���^
     */
    static GgafMainActor* obtainActor(uint64_t prm_order_id, GgafObject* prm_org);

    /**
     * ���������V�[�������o���B�i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * �������������ꍇ�A��������������܂ő҂B<BR>
     * @param   prm_id	��������ID
     * @param   prm_org �������i�f�o�b�O�p�j
     * @return	�������ꂽ�V�[���̃|�C���^
     */
    static GgafMainScene* obtainScene(uint64_t prm_order_id, GgafObject* prm_org);


    template<class X>
    static X* makeObject(X* (*prm_pFunc)(void*, void*, void*),
                         GgafObject* prm_pOrderer,
                         void* prm_pArg1,
                         void* prm_pArg2,
                         void* prm_pArg3,
                         GgafObject* prm_org) {
        order(ORDER_ID_MAX, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pOrderer, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(obtain(ORDER_ID_MAX, prm_org));
    }


    /**
     * �����������i���o���オ���Ă��邩���ׂ�B�i���C���X���b�h���g�p�j .
     * @param   prm_order_id   ��������ID
     * @return   ��������ID�̏��i�̐i���(-2:�H�ꎩ�̂������ĂȂ�/-1:�������炵�Ă��Ȃ�/0:�����ς݂ōH�ꖢ����/1:������/2:�����ς݁j
     */
    static int chkProgress(uint64_t prm_order_id);

    /**
     * �H���|������i���C���X���b�h���g�p�j .
     * ���C�������̐_���Ăяo���܂��B<BR>
     * ROOT_ORDER ���w���Ă��鐻�i�̘A�����X�g��S�ĉ������<BR>
     * ���ӁF�K���ȉ��̂悤�ɃN���e�B�J���Z�N�V�����ň͂�ŌĂяo���Ă��������I�B<BR>
     * ���R�[�h�၄ <BR>
     *     BEGIN_SYNCHRONIZED1; // ----->�r���J�n<BR>
     * GgafFactory::clean();<BR>
     *     END_SYNCHRONIZED1; // <----- �r���I��<BR>
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
    static void beginRest();
    /**
     * �H��̏�Ԃ��擾�i���C���X���b�h���g�p�j .
     * @return true=�x�~���/false=�ғ����
     */
    static bool isResting();

    /**
     * �H��x�~�̉������w�� �i���C���X���b�h���g�p�j .
     */
    static void finishRest();

    template<class X>
    static X* create(void* p1, void* p2, void* p3) {
        //p1 : ����
        X* p = NEW X((char*)p1);
        return p;
    }
    template<class X>
    static X* create2(void* p1, void* p2, void* p3) {
        //p1 : ����
        X* p = NEW X((char*)p1, (char*)p2);
        return p;
    }

    template<class X>
    static X* createActor(void* p1, void* p2, void* p3) {
        //p1 : ����
        X* p = NEW X((char*)p1);
        return p;
    }

    template<class X>
    static X* createScene(void* p1, void* p2, void* p3) {
        //Scene�����ň�ԑ����`�̈����B
        //p1 : ���ʖ���
        X* p = NEW X((char*)p1);
        return p;
    }

    static void debuginfo();


};
#define orderSceneToFactory(ID, CLASS, NAME) (GgafCore::GgafFactory::orderScene<CLASS>((ID),GgafCore::GgafFactory::createScene, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
#define orderActorToFactory(ID, CLASS, NAME) (GgafCore::GgafFactory::orderActor<CLASS>((ID),GgafCore::GgafFactory::createActor, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
#define obtainActorFromFactory(ID) (GgafCore::GgafFactory::obtainActor((ID),this))
#define obtainSceneFromFactory(ID) (GgafCore::GgafFactory::obtainScene((ID),this))
#define createInFactory(CLASS, NAME) (GgafCore::GgafFactory::makeObject<CLASS>(GgafCore::GgafFactory::create, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr),this))
#define createInFactory2(CLASS, NAME, MODEL) (GgafCore::GgafFactory::makeObject<CLASS>(GgafCore::GgafFactory::create2, this, (void*)(NAME),(void*)(MODEL),(void*)(nullptr),this))

}
#endif /*GGAFCORE_GGAFGACTORY_H_*/
