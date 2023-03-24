#ifndef GGAF_CORE_GARBAGEBOX_H_
#define GGAF_CORE_GARBAGEBOX_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#ifndef _MSC_VER
    #include <atomic>
#endif

namespace GgafCore {

/**
 * �S�~�� .
 * �s�v�ɂȂ����I�u�W�F�N�g�i�A�N�^�[�A�V�[���j�́A�Ƃ肠�����R�R�ɓo�^�B<BR>
 * �R�R�ɓo�^�����ƁACPU�̗]�T�̂���Ƃ��ɊǗ��҂�����ɂ��т��т� delete ���Ă䂫�܂�<BR>
 * (��TrashBox)
 * @version 1.00
 * @since 2008/12/16
 * @author Masatoshi Tsuge
 */
class GarbageBox : public Object {
#ifdef _MSC_VER
    /** �����ɒǉ�����Ȃ����߂̃Z�}�t�H */
    static volatile bool _wait;
#else
    /** �����ɒǉ�����Ȃ����߂̃Z�}�t�H */
    static volatile std::atomic<bool> _wait;
#endif
public:
    /** [r]�S�~��(�s�v�ȃA�N�^�[�u����) */
    static GarbageBox* _pGarbageBox;
    /** [r]�|���I�u�W�F�N�g�� */
    static int _cnt_cleaned;
    /** [r]�܂��Ȃ�delete�����A�N�^�[�̃c���[�g�b�v�̃m�[�h */
    DisusedActor* _pDisusedActor;
    /** [r]�܂��Ȃ�delete�����V�[���̃c���[�g�b�v�̃m�[�h */
    DisusedScene* _pDisusedScene;

public:
    /**
     * �R���X�g���N�^ .
     */
    GarbageBox();

    /**
     * �S�~���ɃA�N�^�[��ǉ� .
     * ���̃c���[�ɏ������Ă��Ă��A
     * ���\�b�h���ŘA����؂藣���Ă���ǉ����邽�߁A
     * �����Ȃ�add���Ă��\��Ȃ��B
     * @param prm_pActor �ǉ�����A�N�^�[
     */
    void add(Actor* prm_pActor);

    /**
     * �S�~���ɃV�[����ǉ� .
     * ���̃c���[�ɏ������Ă��Ă��A
     * ���\�b�h���ŘA����؂藣���Ă���ǉ����邽�߁A
     * �����Ȃ�add���Ă��\��Ȃ��B
     * @param prm_pScene �ǉ�����V�[��
     */
    void add(Scene* prm_pScene);

    /**
     * �S�~���ɗ��܂��Ă���I�u�W�F�N�g��delete���� .
     * �ʏ�A�Ǘ���(Caretaker)��������s���܂��B
     * @param prm_num_cleaning delete����I�u�W�F�N�g��
     */
    void clean(int prm_num_cleaning);

    virtual ~GarbageBox();
};

}
#endif /*GGAF_CORE_GARBAGEBOX_H_*/
