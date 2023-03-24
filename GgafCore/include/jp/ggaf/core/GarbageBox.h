#ifndef GGAF_CORE_GARBAGEBOX_H_
#define GGAF_CORE_GARBAGEBOX_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#ifndef _MSC_VER
    #include <atomic>
#endif

namespace GgafCore {

/**
 * ゴミ箱 .
 * 不要になったオブジェクト（アクター、シーン）は、とりあえずココに登録。<BR>
 * ココに登録されると、CPUの余裕のあるときに管理者が勝手にちびちびと delete してゆきます<BR>
 * (旧TrashBox)
 * @version 1.00
 * @since 2008/12/16
 * @author Masatoshi Tsuge
 */
class GarbageBox : public Object {
#ifdef _MSC_VER
    /** 同時に追加されないためのセマフォ */
    static volatile bool _wait;
#else
    /** 同時に追加されないためのセマフォ */
    static volatile std::atomic<bool> _wait;
#endif
public:
    /** [r]ゴミ箱(不要なアクター置き場) */
    static GarbageBox* _pGarbageBox;
    /** [r]掃除オブジェクト数 */
    static int _cnt_cleaned;
    /** [r]まもなくdeleteされるアクターのツリートップのノード */
    DisusedActor* _pDisusedActor;
    /** [r]まもなくdeleteされるシーンのツリートップのノード */
    DisusedScene* _pDisusedScene;

public:
    /**
     * コンストラクタ .
     */
    GarbageBox();

    /**
     * ゴミ箱にアクターを追加 .
     * 他のツリーに所属していても、
     * メソッド内で連結を切り離してから追加するため、
     * いきなりaddしても構わない。
     * @param prm_pActor 追加するアクター
     */
    void add(Actor* prm_pActor);

    /**
     * ゴミ箱にシーンを追加 .
     * 他のツリーに所属していても、
     * メソッド内で連結を切り離してから追加するため、
     * いきなりaddしても構わない。
     * @param prm_pScene 追加するシーン
     */
    void add(Scene* prm_pScene);

    /**
     * ゴミ箱に溜まっているオブジェクトをdeleteする .
     * 通常、管理者(Caretaker)がこれを行います。
     * @param prm_num_cleaning deleteするオブジェクト数
     */
    void clean(int prm_num_cleaning);

    virtual ~GarbageBox();
};

}
#endif /*GGAF_CORE_GARBAGEBOX_H_*/
