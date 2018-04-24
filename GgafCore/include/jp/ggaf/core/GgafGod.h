#ifndef GGAFCORE_GGAFGOD_H_
#define GGAFCORE_GGAFGOD_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#ifndef _MSC_VER
    #include <atomic>
#endif

#define ORDER_ID_MAX     (0xffffffffffffffffULL)

#undef pGOD
#define pGOD (GgafCore::GgafGod::_pGod)

namespace GgafCore {

#define  BEGIN_SYNCHRONIZED1   ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  END_SYNCHRONIZED1     ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))
#define  BEGIN_SYNCHRONIZED2   ::EnterCriticalSection(&(GgafCore::GgafGod::CS2))
#define  END_SYNCHRONIZED2     ::LeaveCriticalSection(&(GgafCore::GgafGod::CS2))
#define  SLOWDOWN_MODE_DEFAULT 0
#define  SLOWDOWN_MODE_40FPS 1
#define  SLOWDOWN_MODE_30FPS 2
/**
 * 神クラス.
 * 主にこの世(GgafSpacetime)を管理し操作することを目的とするクラスです。たぶん一番えらい。<BR>
 * 本クラスの be() メソッドを呼び続けることで、この世が動くことになる、という設計。<BR>
 * インスタンスは１個です。<BR>
 * TODO:グローバルな参照を保持したり便利屋クラスになりつつある；。<BR>
 * TODO:最終的には 神を２個 new して、交互に be() を実行すれば、ゲームが２個平行動作するようにしようかな。
 * (旧名:GdxfwWorldクラス)
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class GgafGod : public GgafObject {

private:
    /** behaveを行ったかフラグ */
    bool _is_behaved_flg;
    /** materializeを行ったかフラグ */
    bool _is_materialized_flg;

public:
    /** [r] クリティカルセクションその１ */
    static CRITICAL_SECTION CS1;
    /** [r] クリティカルセクションその２ */
    static CRITICAL_SECTION CS2;
    /** [r] 自身 */
    static GgafGod* _pGod;
    /** [r] 次にこの世を活動させる時間のオフセット */
    static DWORD _aaTime_offset_of_next_view[3][60];

    /** [r] 生成神(別スレッド)のエラー状態。nullptr＝正常稼働中／not nullptr＝異常発生 */
    GgafCriticalException* _pException_god;


    /** [r] GgafGod::love スレッドハンドル  */
    HANDLE _handle_god_love01;
    /** [r] GgafGod::love スレッドID  */
    unsigned int _th_id01;
    /** [r] 神のフレーム開始システム時間 */
    DWORD _time_at_beginning_frame;
    /** [r] 次にこの世を活動させるシステム時間 */
    DWORD _time_of_next_view;
    /** [r] 神誕生からのフレーム数 */
    frame _frame_of_God;
    int _cnt_frame;

    /** [r] この世を視覚化できなかった（スキップした）回数 */
    int _skip_count_of_frame;
    /** [r] この世 */
    GgafSpacetime* _pSpacetime;
    /** [r] fps値（約1000ms毎に計算される） */
    float _fps;

    DWORD _time_calc_fps_next;
    /** [r] 描画フレームカウンタ */
    frame _visualize_frames;
    /** [r] 前回fps計算時の描画フレームカウント値 */
    frame _prev_visualize_frames;
#ifdef MY_DEBUG
    /** [r] 1フレームの描画回数 */
    static unsigned int _num_drawing;
#endif
    /** [r] 1フレームの活動中アクター */
    static unsigned int _num_active_actor;

    /** [r] 描画処理、最高スキップフレーム数 */
    int _max_skip_frames;
    /** [r] 現在の処理落ちモード 0:60fps 1:40fps 2:30fps。_aaTime_offset_of_next_viewの一つ目の要素 */
    int _slowdown_mode;
    /** [r] 時間とフレームの同期調整モード中はtrue */
    bool _sync_frame_time;
    bool _was_cleaned;

public:
    /**
     * コンストラクタ .
     * 別スレッドで神を稼動させます。
     */
    GgafGod();

    /**
     * 「存在する」というメソッド .
     * 神が存在する、すなわち、この世(GgafSpacetime)が動き、アプリが進行します。<BR>
     * 初回呼び出し時、この世(GgafSpacetime)が作成されます。<BR>
     * アプリケーションは、最小時間単位でこのメソッドをひたすら呼び続けてください。<BR>
     */
    void be();

    /**
     * この世の、とある最小時間単位の瞬間を創造 .
     */
    virtual void presentSpacetimeMoment();

    /**
     * この世の、創造された最小時間単位の瞬間について審判（チェック）する .
     */
    virtual void executeSpacetimeJudge();

    /**
     * この世の、創造された最小時間単位の瞬間を具現化する .
     */
    virtual void makeSpacetimeMaterialize();

    /**
     * この世に描いた物を、異界の人間共にも認識（目視）できるように表面化する .
     */
    virtual void presentSpacetimeVisualize();

    /**
     * この世の次の最小時間単位の瞬間を創造するための準備、後始末 .
     */
    virtual void finalizeSpacetime();

    /**
     * この世を取得 .
     * 下位でオーバーライド可能。<BR>
     * @return この世
     */
    virtual GgafSpacetime* getSpacetime() {
        return _pSpacetime;
    }

    /**
     * この世を創造 .
     * 下位でこの世の創造方法を実装してください。<BR>
     * @return この世
     */
    virtual GgafSpacetime* createSpacetime() = 0;

    /**
     * 描画を一時停止し、フレームと時間の同期を行う
     */
    void syncTimeFrame() {
        _sync_frame_time = true;
    }

    virtual void clean();

    /**
     * 神「しまった〜！」 .
     * 例外発生時にコールバックされます。
     */
    virtual void oops() {
        _TRACE_("(-_-;) {Oops!");
    }

    virtual ~GgafGod();


private:
    /**
     * 神にゆりかごを行う（メインスレッドが使用） .
     * @param prm_cradle_no	ゆりかご番号
     * @param prm_pFunc	実際に祝福処理を行う関数のポインタ
     * @param prm_pWisher 望んだ人
     * @param prm_pReceiver 受け取り予定者
     * @param prm_pArg1	祝福処理を行う関数への引数1
     * @param prm_pArg2	祝福処理を行う関数への引数2
     * @param prm_pArg3	祝福処理を行う関数への引数3
     */
    void createCradle(uint64_t prm_cradle_no,
                      GgafObject* (*prm_pFunc)(void*, void*, void*),
                      GgafObject* prm_pWisher,
                      GgafObject* prm_pReceiver,
                      void* prm_pArg1,
                      void* prm_pArg2,
                      void* prm_pArg3);

    /**
     * 望んだ命を受け取る（メインスレッドが使用） .
     * 未祝福だった場合、祝福が完了するまで待つ。<BR>
     * @param   prm_cradle_no	ゆりかご番号
     * @param   prm_pReceiver	受取人
     * @return	命のポインタ
     */
    void* receive(uint64_t prm_cradle_no, GgafObject* prm_pReceiver);

public:
    /** 先頭のゆりかご */
    GgafCradle* ROOT_CRADLE;
    /** 現在祝福中のゆりかご */
    GgafCradle* CREATING_CRADLE;
    //CREATING_CRADLE は、全て祝福済みの場合、最終ゆりかごを指しつづける
    //全て祝福済みかつ、ゆりかごが全て引き取られた場合は nullptr になる。
    //_is_last_cradle_flg == false を常に判定し、最終ゆりかごでなくなったら（新規ゆりかごがあれば）、
    //祝福を行って次に進める。 _is_last_cradle_flg == false になるまで祝福しつづける
    // また、先頭と末尾のゆりかごもポインタでつながっている(環状)

    //      ROOT_CRADLE
    //        ↓
    //      pCradle <-> pCradle <-> pCradle <-> pCradle <-> pCradle <-> pCradle
    //     (祝福済)   (祝福済)  （祝福中）  (未着手)   (未着手)   (未着手)
    //                              ↑                            _is_last_cradle_flg == true
    //                        CREATING_CRADLE
    //                    祝福を終えると右に動く  ===>
    //
    //prev <------古いゆりかご----------------------------------新しいゆりかご-----> next
    //                                               ゆりかごは末尾についてくる
#ifdef _MSC_VER
    //x86系ならばアトミック性がある・・・・・・・・。
    /** [r]活動フラグ(神が操作する) */
    volatile bool _is_working_flg;
    /** [r]休むフラグ */
    volatile bool _have_to_rest_flg;
    /** [r]休でいるフラグ */
    volatile bool _is_resting_flg;
    /** [r]完全店終い */
    volatile bool _was_finished_flg;
#else
    /** [r]活動フラグ(神が操作する) */
    volatile std::atomic<bool> _is_working_flg;
    /** [r]休むフラグ */
    volatile std::atomic<bool> _have_to_rest_flg;
    /** [r]休でいるフラグ */
    volatile std::atomic<bool> _is_resting_flg;
    /** [r]完全店終い */
    volatile std::atomic<bool> _was_finished_flg;
#endif
public:
    /**
     * 神にアクターを祝福してもらうための、ゆりかごをつくる（メインスレッドが使用） .
     * @tparam X ゆりかごアクターの型
     * @param prm_cradle_no ゆりかご番号
     * @param prm_pFunc 実際に祝福処理を行う関数のポインタ
     * @param prm_pWisher ゆりかご者
     * @param prm_pReceiver 受取人
     * @param prm_pArg1 祝福処理を行う関数への引数1
     * @param prm_pArg2 祝福処理を行う関数への引数2
     * @param prm_pArg3 祝福処理を行う関数への引数3
     */
    template<class X>
    void createActorCradle(uint64_t prm_cradle_no,
                                  X* (*prm_pFunc)(void*, void*, void*),
                                  GgafObject* prm_pWisher,
                                  GgafObject* prm_pReceiver,
                                  void* prm_pArg1,
                                  void* prm_pArg2,
                                  void* prm_pArg3) {
        createCradle(prm_cradle_no, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * 神にシーン作成（祝福）してもらうための、ゆりかごをつくる（メインスレッドが使用） .
     * @tparam X ゆりかごシーンの型
     * @param prm_cradle_no ゆりかご番号
     * @param prm_pFunc	実際に祝福処理を行う関数のポインタ
     * @param prm_pWisher ゆりかご者
     * @param prm_pReceiver 受取人
     * @param prm_pArg1	祝福処理を行う関数への引数1
     * @param prm_pArg2	祝福処理を行う関数への引数2
     * @param prm_pArg3	祝福処理を行う関数への引数3
     */
    template<class X>
    void createSceneCradle(uint64_t prm_cradle_no,
                                  X* (*prm_pFunc)(void*, void*, void*),
                                  GgafObject* prm_pWisher,
                                  GgafObject* prm_pReceiver,
                                  void* prm_pArg1,
                                  void* prm_pArg2,
                                  void* prm_pArg3) {
        createCradle(prm_cradle_no, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * 望んだアクターを受け取る。（メインスレッドが使用） .
     * メイン処理が呼び出します。<BR>
     * 未祝福だった場合、祝福が完了するまで待つ。<BR>
     * @param   prm_cradle_no ゆりかご番号
     * @param   prm_pReceiver 受取人
     * @return	生成されたアクターのポインタ
     */
    GgafMainActor* receiveActor2(uint64_t prm_cradle_no, GgafObject* prm_pReceiver);

    /**
     * 望んだシーンを受け取る。（メインスレッドが使用） .
     * メイン処理が呼び出します。<BR>
     * 未祝福だった場合、祝福が完了するまで待つ。<BR>
     * @param   prm_cradle_no ゆりかご番号
     * @param   prm_pReceiver 受取人
     * @return	生成されたシーンのポインタ
     */
    GgafMainScene* receiveScene2(uint64_t prm_cradle_no, GgafObject* prm_pReceiver);

    /**
     * 望んで、祝福されるまで待って、すぐに受け取る。
     * @tparam X ゆりかご命の型
     * @param prm_pFunc
     * @param prm_pWisher
     * @param prm_pReceiver
     * @param prm_pArg1
     * @param prm_pArg2
     * @param prm_pArg3
     * @param prm_org
     * @return 出来上がった命
     */
    template<class X>
    X* makeObject(X* (*prm_pFunc)(void*, void*, void*),
                         GgafObject* prm_pWisher,
                         GgafObject* prm_pReceiver,
                         void* prm_pArg1,
                         void* prm_pArg2,
                         void* prm_pArg3,
                         GgafObject* prm_org) {
        createCradle(ORDER_ID_MAX, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(receive(ORDER_ID_MAX, prm_org));
    }

    /**
     * 望んだ命が出来上がっているか調べる。（メインスレッドが使用） .
     * @param   prm_cradle_no   ゆりかご番号
     * @return   ゆりかご番号の命の進捗具合(-2:神自体が動いてない/-1:ゆりかごすらしていない/0:ゆりかご済みで神未着手/1:祝福中/2:祝福済み）
     */
    int chkProgress(uint64_t prm_cradle_no);

    /**
     * ゆりかごを掃除する（メインスレッドが使用） .
     * メイン処理の神が呼び出します。<BR>
     * ROOT_CRADLE が指しているゆりかごの連結リストを全て解放する<BR>
     * 注意：必ず以下のようにクリティカルセクションで囲んで呼び出してください！。<BR>
     * ＜コード例＞ <BR>
     *     BEGIN_SYNCHRONIZED1; // ----->排他開始<BR>
     * GgafGod::clean();<BR>
     *     END_SYNCHRONIZED1; // <----- 排他終了<BR>
     */
    void cleanCradle();

    /**
     * 運命 .
     * @param prm_pReceiver 授かるはずだった人
     */
    void fate(GgafObject* prm_pReceiver);

    /**
     * 愛 .
     * 神（GgafGod）が初期設定時に別スレッドで一度実行され、メソッド内部で無限ループしてます。<BR>
     * ゆりかごがあれば作成し、ストックします。<BR>
     * 神が死ぬまで（アプリ終了まで）永遠に愛し続けます。<BR>
     */
    static unsigned __stdcall loveth(void* prm_arg);
    unsigned love(void* prm_arg);

    /**
     * 神一時休止を指示 （メインスレッドが使用） .
     * しかし呼び出しても直ぐに休止状態になるとは限りません。<BR>
     * isResting() で完全休止するまで調べる続ける必要があります。<BR>
     */
    void beginRest();
    /**
     * 神の状態を取得（メインスレッドが使用） .
     * @return true=休止状態/false=稼動状態
     */
    bool isResting();

    /**
     * 神休止の解除を指示 （メインスレッドが使用） .
     */
    void finishRest();

    /**
     * 祝福する(引数は１つ) .
     * @tparam X 命の型
     * @param p1 命生成の為の引数1 (使用される)
     * @param p2 命生成の為の引数2 (無視される)
     * @param p3 命生成の為の引数3 (無視される)
     * @return 生成された命
     */
    template<class X>
    static X* bless(void* p1, void* p2, void* p3) {
        //p1 : 名称
        X* p = NEW X((const char*)p1);
        return p;
    }

    /**
     * 祝福する(引数は２つ) .
     * @tparam X 命の型
     * @param p1 命生成の為の引数1 (使用される)
     * @param p2 命生成の為の引数2 (使用される)
     * @param p3 命生成の為の引数3 (無視される)
     * @return 生成された命
     */
    template<class X>
    static X* bless2(void* p1, void* p2, void* p3) {
        //p1 : 名称
        X* p = NEW X((const char*)p1, (const char*)p2);
        return p;
    }

    void debuginfo();

};

/** シーンを神に望む */
#define wishScene(ID, CLASS, NAME) (pGOD->createSceneCradle<CLASS>((ID),GgafCore::GgafGod::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
/** アクターを神に望む */
#define wishActor(ID, CLASS, NAME) (pGOD->createActorCradle<CLASS>((ID),GgafCore::GgafGod::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
/** 祝福されたアクターを受け取る */
#define grantActor(ID) (pGOD->receiveActor2((ID),this))
/** 祝福されたシーンを受け取る */
#define grantScene(ID) (pGOD->receiveScene2((ID),this))
/** 神に望む */
#define believeIn(CLASS, NAME) (pGOD->makeObject<CLASS>(GgafCore::GgafGod::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr),this))
#define believeIn2(CLASS, NAME, MODEL) (pGOD->makeObject<CLASS>(GgafCore::GgafGod::bless2, this, this, (void*)(NAME),(void*)(MODEL),(void*)(nullptr),this))

}
#endif /*GGAFCORE_GGAFGOD_H_*/
