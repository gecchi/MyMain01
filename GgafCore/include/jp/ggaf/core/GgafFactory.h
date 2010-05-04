#ifndef GGAFGACTORY_H_
#define GGAFGACTORY_H_
namespace GgafCore {

/**
 * インスタンス生成工場クラス .
 * メイン処理から、注文(GgafOrder)を渡されると、別スレッドにそのインスタンスを生成(new)させます。<BR>
 * 出来上がったインスタンス(商品と呼ぶ)のポインタ達は工場でストックされ、メイン処理から必要に応じて商品を取り出すことが出来ます<BR>
 * 【補足】<BR>
 * なぜこんなややこしい事をするのか。それは、大量インスタンスをある時点で生成しなければいけないような個所で、滑らかに処理をしたいため。<BR>
 * ステージのローディングや、昔よくあったのですが、ボス前等で、一瞬「ウッ」と詰まる(ナンノコッチャ)のを無くしたかったたためです。<BR>
 * 注文を早めにしておくと、スムーズにゲームが進行するはずだと目論む。<BR>
 * @version 1.00
 * @since 2007/12/27
 * @author Masatoshi Tsuge
 */
class GgafFactory {
    friend class GgafGod;

private:
    /** 先頭の注文 */
    static GgafOrder* ROOT_ORDER;
    /** 現在製造中の注文 */
    static GgafOrder* CREATING_ORDER;
    //CREATING_ORDER は、全て製造済みの場合、最終注文を指しつづける
    //全て製造済みかつ、製品が全て取得されてしまった場合は NULL になる。
    //_is_last_order_flg == false を常に判定し、最終注文でなくなったら（新規注文があれば）、
    //製造を行って次に進める。 _is_last_order_flg == false になるまで製造しつづける


    /**
     * 工場に注文を行う<BR>
     * @param prm_id	注文識別ID番号
     * @param prm_pFunc	実際に製造処理を行う関数のポインタ
     * @param prm_pArg1	その引数1
     * @param prm_pArg2	その引数2
     * @param prm_pArg3	その引数3
     */
    static void order(unsigned long prm_id,
                      GgafObject* (*prm_pFunc)(void*, void*, void*),
                      void* prm_pArg1,
                      void* prm_pArg2,
                      void* prm_pArg3);

    /**
     * 注文した商品を取り出す。<BR>
     * 未製造だった場合、製造が完了するまで待つ。<BR>
     * @param   prm_id	注文識別ID番号
     * @return	製品のポインタ
     */
    static void* obtain(unsigned long prm_id);

public:
    /** [r]ゴミ箱(不要なアクター置き場) */
    static GgafGarbageBox* _pGarbageBox;

    /** [r]掃除オブジェクト数 */
    static int _cnt_cleaned;

    /** [r]活動フラグ(神が操作する) */
    static bool _is_working_flg;
    /** [r]休むフラグ */
    static bool _have_to_rest_flg;
    /** [r]休でいるフラグ */
    static bool _is_resting_flg;
    /** [r]完全店終い */
    static bool _was_finished_flg;

    /**
     * 工場にアクター作成の注文を行う .
     * メイン処理が呼び出します。<BR>
     * @param prm_id	注文識別ID番号
     * @param prm_pFunc	実際に製造処理を行う関数のポインタ
     * @param prm_pArg1	その引数1
     * @param prm_pArg2	その引数2
     * @param prm_pArg3	その引数3
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
     * 工場にシーン作成の注文を行う .
     * メイン処理が呼び出します。<BR>
     * @param prm_id	注文識別ID番号
     * @param prm_pFunc	実際に製造処理を行う関数のポインタ
     * @param prm_pArg1	その引数1
     * @param prm_pArg2	その引数2
     * @param prm_pArg3	その引数3
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
     * 注文したアクターを取り出す。 .
     * メイン処理が呼び出します。<BR>
     * 未製造だった場合、製造が完了するまで待つ。<BR>
     * @param   prm_id	注文識別ID
     * @return	生成されたアクターのポインタ
     */
    static GgafMainActor* obtainActor(unsigned long prm_id);

    /**
     * 注文したシーンを取り出す。 .
     * メイン処理が呼び出します。<BR>
     * 未製造だった場合、製造が完了するまで待つ。<BR>
     * @param   prm_id	注文識別ID
     * @return	生成されたシーンのポインタ
     */
    static GgafMainScene* obtainScene(unsigned long prm_id);

    /**
     * 注文した商品が出来上がっているか調べる。 .
     * @return  進捗具合(-2:工場自体が動いてない/-1:注文すらしていない/0:未着手/1:製造中/2:製造済み）
     */
    static int chkProgress(unsigned long prm_id);

    /**
     * 工場を掃除する<BR>
     * メイン処理の神が呼び出します。<BR>
     * ROOT_ORDER が指している製品の連結リストを全て解放する<BR>
     * 注意：必ず以下のようにクリティカルセクションで囲んで呼び出してください！。<BR>
     * ＜コード例＞ <BR>
     *  ___BeginSynchronized; // ----->排他開始<BR>
     * GgafFactory::clean();<BR>
     *  ___EndSynchronized; // <----- 排他終了<BR>
     */
    static void clean();

    /**
     * 稼動する。<BR>
     * 別スレッドで無限ループしてます。注文があれば作成し、ストックします。<BR>
     * 神が初期設定時に別スレッドで一度実行する。神が死ぬまで（アプリ終了まで）永遠に稼動しっ放しである。<BR>
     */
    static unsigned __stdcall work(void* prm_arg);

    /**
     * 一時休止を指示 .
     * しかし呼び出しても直ぐに休止状態になるとは限りません。<BR>
     * isResting() で調べる必要があります。<BR>
     */
    static void beginRest() {
        _TRACE_("GgafFactory::beginRest() ＜神＞工場、休憩しなさい");
        _have_to_rest_flg = true;
    }

    /**
     * 工場の状態を取得<BR>
     * @return true=休止状態/false=稼動状態
     */
    static bool isResting() {
        if (_is_resting_flg) {
            _TRACE_("GgafFactory::isResting() 工場休止状態");
        } else {
            _TRACE_("GgafFactory::isResting() 工場稼働状態");
        }
        return _is_resting_flg;
    }

    /**
     * 休止の解除を指示 .
     */
    static void finishRest() {
        _TRACE_("GgafFactory::beginRest() ＜神＞工場、休憩はおしまい。さあ動け！");
        _have_to_rest_flg = false;
    }
};

}
#endif /*GGAFGACTORY_H_*/
