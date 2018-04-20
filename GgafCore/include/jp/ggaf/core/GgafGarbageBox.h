#ifndef GGAFCORE_GGAFGARBAGEBOX_H_
#define GGAFCORE_GGAFGARBAGEBOX_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#ifndef _MSC_VER
    #include <atomic>
#endif

namespace GgafCore {

/**
 * ゴミ箱 .
 * 不要になったオブジェクト（アクター、シーン）は、とりあえずココに登録。<BR>
 * ココに登録されると、CPUの余裕のあるときに神が勝手にちびちびと delete してゆきます<BR>
 * (旧GgafTrashBox)
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
    /** [r]ゴミ箱(不要なアクター置き場) */
    static GgafGarbageBox* _pGarbageBox;
    /** [r]掃除オブジェクト数 */
    static int _cnt_cleaned;

    /** [r]まもなくdeleteされるアクターのツリートップのノード */
    GgafDisusedActor* _pDisusedActor;
    /** [r]まもなくdeleteされるシーンのツリートップのノード */
    GgafDisusedScene* _pDisusedScene;

public:
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
    void clean(int prm_num_cleaning);

    virtual ~GgafGarbageBox();
};

}
#endif /*GGAFCORE_GGAFGARBAGEBOX_H_*/
