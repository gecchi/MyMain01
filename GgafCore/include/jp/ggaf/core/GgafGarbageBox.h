#ifndef GGAFCORE_GGAFGARBAGEBOX_H_
#define GGAFCORE_GGAFGARBAGEBOX_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#ifndef _MSC_VER
    #include <atomic>
#endif

namespace GgafCore {

/**
 * �S�~�� .
 * �s�v�ɂȂ����I�u�W�F�N�g�i�A�N�^�[�A�V�[���j�́A�Ƃ肠�����R�R�ɓo�^�B<BR>
 * �R�R�ɓo�^�����ƁACPU�̗]�T�̂���Ƃ��ɐ_������ɂ��т��т� delete ���Ă䂫�܂�<BR>
 * (��GgafTrashBox)
 * @version 1.00
 * @since 2008/12/16
 * @author Masatoshi Tsuge
 */
class GgafGarbageBox : public GgafObject {
#ifdef _MSC_VER
    static volatile bool _wait;
#else
    static volatile std::atomic<bool> _wait;
#endif
public:
    /** [r]�S�~��(�s�v�ȃA�N�^�[�u����) */
    static GgafGarbageBox* _pGarbageBox;
    /** [r]�|���I�u�W�F�N�g�� */
    static int _cnt_cleaned;

    /** [r]�܂��Ȃ�delete�����A�N�^�[�̃c���[�g�b�v�̃m�[�h */
    GgafDisusedActor* _pDisusedActor;
    /** [r]�܂��Ȃ�delete�����V�[���̃c���[�g�b�v�̃m�[�h */
    GgafDisusedScene* _pDisusedScene;

public:
    /**
     * �R���X�g���N�^ .
     */
    GgafGarbageBox();

    /**
     * �S�~���ɃA�N�^�[��ǉ� .
     * ���̃c���[�ɏ������Ă��Ă��A
     * ���\�b�h���ŘA����؂藣���Ă���ǉ����邽�߁A
     * �����Ȃ�add���Ă��\��Ȃ��B
     * @param prm_pActor �ǉ�����A�N�^�[
     */
    void add(GgafActor* prm_pActor);

    /**
     * �S�~���ɃV�[����ǉ� .
     * ���̃c���[�ɏ������Ă��Ă��A
     * ���\�b�h���ŘA����؂藣���Ă���ǉ����邽�߁A
     * �����Ȃ�add���Ă��\��Ȃ��B
     * @param prm_pScene �ǉ�����V�[��
     */
    void add(GgafScene* prm_pScene);

    /**
     * �S�~���ɗ��܂��Ă���I�u�W�F�N�g��delete���� .
     * �ʏ�A�_(GgafGod)��������s���܂��B
     * @param prm_num_cleaning delete����I�u�W�F�N�g��
     */
    void clean(int prm_num_cleaning);

    virtual ~GgafGarbageBox();
};

}
#endif /*GGAFCORE_GGAFGARBAGEBOX_H_*/
