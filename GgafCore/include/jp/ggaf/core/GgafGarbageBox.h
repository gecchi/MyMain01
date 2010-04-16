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
    /** [r]まもなくdeleteされるアクターのツリートップのノード */
    GgafSayonaraActor* _pSayonaraActor;
    /** [r]まもなくdeleteされるシーンのツリートップのノード */
    GgafSayonaraScene* _pSayonaraScene;

    /**
     * コンストラクタ .
     */
    GgafGarbageBox();

    /**
     * ゴミ箱にアクターを追加 .
     * 他のツリーに所属していても、
     * メソッド内で連結を切り離してから追加するため、
     * いきなりaddしても構わない。
     * @param prm_pActor 追加するアクター
     */
    void add(GgafActor* prm_pActor);

    /**
     * ゴミ箱にシーンを追加 .
     * 他のツリーに所属していても、
     * メソッド内で連結を切り離してから追加するため、
     * いきなりaddしても構わない。
     * @param prm_pScene 追加するシーン
     */
    void add(GgafScene* prm_pScene);

    /**
     * ゴミ箱に溜まっているオブジェクトをdeleteする .
     * 通常、神(GgafGod)がこれを行います。
     * @param prm_num_cleaning deleteするオブジェクト数
     */
    void cleane(int prm_num_cleaning);

    virtual ~GgafGarbageBox();
};

}
#endif /*GGAFGARBAGEBOX_H_*/
