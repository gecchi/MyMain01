#ifndef GGAFGARBAGEBOX_H_
#define GGAFGARBAGEBOX_H_
namespace GgafCore {

/**
 * �S�~�� .
 * �s�v�ɂȂ����I�u�W�F�N�g�́A�Ƃ肠�����R�R�ɓo�^�B<BR>
 * �R�R�ɓo�^�����ƁACPU�̗]�T�̂���Ƃ��ɍH��(GgafFactory)������ɂ��т��т� delete ���Ă䂫�܂�<BR>
 * (��GgafTrashBox)
 * @version 1.00
 * @since 2008/12/16
 * @author Masatoshi Tsuge
 */
class GgafGarbageBox : public GgafObject {

public:

    GgafGarbageRootActor* _pGarbageRootActor;
    GgafGarbageRootScene* _pGarbageRootScene;

    GgafGarbageBox();

    void add(GgafActor* prm_pActor);

    void add(GgafScene* prm_pScene);

    void cleane(int prm_num_cleaning);

    virtual ~GgafGarbageBox();
};

}
#endif /*GGAFGARBAGEBOX_H_*/
