#ifndef GGAFGARBAGEBOX_H_
#define GGAFGARBAGEBOX_H_
namespace GgafCore {

/**
 * ゴミ箱 .
 * 不要になったオブジェクトは、とりあえずココに登録。<BR>
 * ココに登録されると、CPUの余裕のあるときに工場(GgafFactory)が勝手にちびちびと delete してゆきます<BR>
 * (旧GgafTrashBox)
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
