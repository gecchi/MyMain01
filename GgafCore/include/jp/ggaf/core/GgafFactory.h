#ifndef GGAFCORE_GGAFGACTORY_H_
#define GGAFCORE_GGAFGACTORY_H_
#include "GgafCommonHeader.h"

#ifndef _MSC_VER
    #include <atomic>
#endif

#define ORDER_ID_MAX     (0xffffffffffffffffULL)

namespace GgafCore {

/**
 * インスタンス生成工場クラス .
 * メインスレッド（この世のシーンツリー）から、注文(GgafOrder)を渡されると、別スレッド（工場）に、
 * そのインスタンスを生成(new)させます。<BR>
 * 出来上がったインスタンス(商品と呼ぶ)のポインタ達は工場でストックされ、メイン処理から必要に応じて商品を
 * 取り出すことが出来ます<BR>
 * 【補足】<BR>
 * なぜこんなややこしい事をするのか。それは、大量インスタンスをある時点で生成しなければいけないような個所で、
 * 滑らかに処理をしたいため。<BR>
 * ステージのローディングや、昔よくあったのですが、ボス前等で、ゲーム進行が一瞬「ウッ」と止まる(わかるかなぁ)
 * のを無くしたかったたためです。<BR>
 * 注文を早めにしておくと、スムーズにゲームが進行するはずだと目論む。<BR>
 * @version 1.00
 * @since 2007/12/27
 * @author Masatoshi Tsuge
 */
class GgafFactory {
    friend class GgafGod;

private:
    /**
     * 工場に注文を行う .
     * @param prm_order_id	注文識別ID番号
     * @param prm_pFunc	実際に製造処理を行う関数のポインタ
     * @param prm_pOrderer 発注者
     * @param prm_pArg1	製造処理を行う関数への引数1
     * @param prm_pArg2	製造処理を行う関数への引数2
     * @param prm_pArg3	製造処理を行う関数への引数3
     */
    static void order(uint64_t prm_order_id,
                      GgafObject* (*prm_pFunc)(void*, void*, void*),
                      GgafObject* prm_pOrderer,
                      void* prm_pArg1,
                      void* prm_pArg2,
                      void* prm_pArg3);

    /**
     * 注文した商品を取り出す .
     * 未製造だった場合、製造が完了するまで待つ。<BR>
     * @param   prm_order_id	注文識別ID番号
     * @param   prm_org 注文元（デバッグ用）
     * @return	製品のポインタ
     */
    static void* obtain(uint64_t prm_order_id, GgafObject* prm_org);

public:
    /** 先頭の注文 */
    static GgafOrder* ROOT_ORDER;
    /** 現在製造中の注文 */
    static GgafOrder* CREATING_ORDER;
    //CREATING_ORDER は、全て製造済みの場合、最終注文を指しつづける
    //全て製造済みかつ、製品が全て取得されてしまった場合は nullptr になる。
    //_is_last_order_flg == false を常に判定し、最終注文でなくなったら（新規注文があれば）、
    //製造を行って次に進める。 _is_last_order_flg == false になるまで製造しつづける

#ifdef _MSC_VER
    //x86系ならばアトミック性がある・・・・・・・・。
    /** [r]活動フラグ(神が操作する) */
    static volatile bool _is_working_flg;
    /** [r]休むフラグ */
    static volatile bool _have_to_rest_flg;
    /** [r]休でいるフラグ */
    static volatile bool _is_resting_flg;
    /** [r]完全店終い */
    static volatile bool _was_finished_flg;
#else
    /** [r]活動フラグ(神が操作する) */
    static volatile std::atomic<bool> _is_working_flg;
    /** [r]休むフラグ */
    static volatile std::atomic<bool> _have_to_rest_flg;
    /** [r]休でいるフラグ */
    static volatile std::atomic<bool> _is_resting_flg;
    /** [r]完全店終い */
    static volatile std::atomic<bool> _was_finished_flg;
#endif
public:
    /**
     * 工場にアクター作成の注文を行う（メインスレッドが使用） .
     * メイン処理が呼び出します。<BR>
     * @param prm_id    注文識別ID番号
     * @param prm_pFunc 実際に製造処理を行う関数のポインタ
     * @param prm_pOrderer 注文元オブジェクト
     * @param prm_pArg1 製造処理を行う関数への引数1
     * @param prm_pArg2 製造処理を行う関数への引数2
     * @param prm_pArg3 製造処理を行う関数への引数3
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
     * 工場にシーン作成の注文を行う（メインスレッドが使用） .
     * メイン処理が呼び出します。<BR>
     * @param prm_id	注文識別ID番号
     * @param prm_pFunc	実際に製造処理を行う関数のポインタ
     * @param prm_pOrderer 注文元オブジェクト
     * @param prm_pArg1	製造処理を行う関数への引数1
     * @param prm_pArg2	製造処理を行う関数への引数2
     * @param prm_pArg3	製造処理を行う関数への引数3
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
     * 注文したアクターを取り出す。（メインスレッドが使用） .
     * メイン処理が呼び出します。<BR>
     * 未製造だった場合、製造が完了するまで待つ。<BR>
     * @param   prm_id	注文識別ID
     * @param   prm_org 注文元（デバッグ用）
     * @return	生成されたアクターのポインタ
     */
    static GgafMainActor* obtainActor(uint64_t prm_order_id, GgafObject* prm_org);

    /**
     * 注文したシーンを取り出す。（メインスレッドが使用） .
     * メイン処理が呼び出します。<BR>
     * 未製造だった場合、製造が完了するまで待つ。<BR>
     * @param   prm_id	注文識別ID
     * @param   prm_org 注文元（デバッグ用）
     * @return	生成されたシーンのポインタ
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
     * 注文した商品が出来上がっているか調べる。（メインスレッドが使用） .
     * @param   prm_order_id   注文識別ID
     * @return   注文識別IDの商品の進捗具合(-2:工場自体が動いてない/-1:注文すらしていない/0:注文済みで工場未着手/1:製造中/2:製造済み）
     */
    static int chkProgress(uint64_t prm_order_id);

    /**
     * 工場を掃除する（メインスレッドが使用） .
     * メイン処理の神が呼び出します。<BR>
     * ROOT_ORDER が指している製品の連結リストを全て解放する<BR>
     * 注意：必ず以下のようにクリティカルセクションで囲んで呼び出してください！。<BR>
     * ＜コード例＞ <BR>
     *     BEGIN_SYNCHRONIZED1; // ----->排他開始<BR>
     * GgafFactory::clean();<BR>
     *     END_SYNCHRONIZED1; // <----- 排他終了<BR>
     */
    static void clean();

    /**
     * 稼動する。（工場スレッドメインループ）.
     * 神（GgafGod）が初期設定時に別スレッドで一度実行され、メソッド内部で無限ループしてます。<BR>
     * 注文があれば作成し、ストックします。<BR>
     * 神が死ぬまで（アプリ終了まで）永遠に稼動しっ放しである。<BR>
     */
    static unsigned __stdcall work(void* prm_arg);

    /**
     * 工場一時休止を指示 （メインスレッドが使用） .
     * しかし呼び出しても直ぐに休止状態になるとは限りません。<BR>
     * isResting() で完全休止するまで調べる続ける必要があります。<BR>
     */
    static void beginRest();
    /**
     * 工場の状態を取得（メインスレッドが使用） .
     * @return true=休止状態/false=稼動状態
     */
    static bool isResting();

    /**
     * 工場休止の解除を指示 （メインスレッドが使用） .
     */
    static void finishRest();

    template<class X>
    static X* create(void* p1, void* p2, void* p3) {
        //p1 : 名称
        X* p = NEW X((char*)p1);
        return p;
    }
    template<class X>
    static X* create2(void* p1, void* p2, void* p3) {
        //p1 : 名称
        X* p = NEW X((char*)p1, (char*)p2);
        return p;
    }

    template<class X>
    static X* createActor(void* p1, void* p2, void* p3) {
        //p1 : 名称
        X* p = NEW X((char*)p1);
        return p;
    }

    template<class X>
    static X* createScene(void* p1, void* p2, void* p3) {
        //Scene生成で一番多い形の引数。
        //p1 : 識別名称
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
