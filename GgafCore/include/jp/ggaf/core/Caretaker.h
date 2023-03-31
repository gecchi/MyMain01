#ifndef GGAF_CORE_CARETAKER_H_
#define GGAF_CORE_CARETAKER_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#ifndef _MSC_VER
    #include <atomic>
#endif

#define ORDER_ID_MAX     (0xffffffffffffffffULL)

#undef pCARETAKER
#define pCARETAKER (GgafCore::Caretaker::ask())

namespace GgafCore {

#define  BEGIN_SYNCHRONIZED1   ::EnterCriticalSection(&(GgafCore::Caretaker::CS1))
#define  END_SYNCHRONIZED1     ::LeaveCriticalSection(&(GgafCore::Caretaker::CS1))
#define  BEGIN_SYNCHRONIZED2   ::EnterCriticalSection(&(GgafCore::Caretaker::CS2))
#define  END_SYNCHRONIZED2     ::LeaveCriticalSection(&(GgafCore::Caretaker::CS2))
//#define  BEGIN_SYNCHRONIZED3   ::EnterCriticalSection(&(GgafCore::Caretaker::CS3))
//#define  END_SYNCHRONIZED3     ::LeaveCriticalSection(&(GgafCore::Caretaker::CS3))
#define  SLOWDOWN_MODE_DEFAULT 0
#define  SLOWDOWN_MODE1 1
#define  SLOWDOWN_MODE2 2
/**
 * 管理者 .
 * 主にこの世(Spacetime)を管理し操作することを目的とするクラスです。たぶん一番えらい。<BR>
 * 本クラスの present() メソッドを呼び続けることで、この世が動くことになる、という設計。<BR>
 * インスタンスは１個です。<BR>
 * TODO:グローバルな参照を保持したり便利屋クラスになりつつある；。<BR>
 * TODO:最終的には 管理者を２個 new して、交互に present() を実行すれば、ゲームが２個平行動作するようにしようかな。
 * (旧名:GdxfwWorldクラス)
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class Caretaker : public Object {

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
//    /** [r] クリティカルセクションその３ */
//    static CRITICAL_SECTION CS3;
    /** [r] 自身 */
    static Caretaker* _pCaretaker;
    /** [r] 次にこの世を活動させる時間のオフセット */
    //static DWORD _aaTime_offset_of_next_view[3][60];
    //static double _aTime_offset_of_next_view[3];

    //WORD _base_fps;
    DWORD* _apaTime_offset_of_next_view[3];
    double _aTime_offset_of_next_view[3];

    /** [r] 生成管理者(別スレッド)のエラー状態。nullptr＝正常稼働中／not nullptr＝異常発生 */
    CriticalException* _pException_god;


    /** [r] GgafCore::Caretaker::love スレッドハンドル  */
    HANDLE _handle_god_love01;
    /** [r] GgafCore::Caretaker::love スレッドID  */
    unsigned int _th_id01;

    /** [r] GgafCore::Caretaker::send スレッドハンドル  */
    HANDLE _handle_god_send03;
    /** [r] GgafCore::Caretaker::send スレッドID  */
    unsigned int _th_id03;

//    /** [r] 管理者のフレーム開始システム時間 */
//    DWORD _time_at_beginning_frame;
    /** [r] 次にこの世を活動させるシステム時間 */
    DWORD _time_of_next_view;

    DWORD _time_calc_fps_next;

    /** [r] 管理者誕生からのフレーム数 */
    frame _frame_of_Caretaker;
    frame _cnt_frame;

    /** [r] この世を視覚化できなかった（スキップした）回数 */
    int _skip_count_of_frame;
    /** [r] この世 */
    Spacetime* _pSpacetime;
    /** [r] fps値（約1000ms毎に計算される） */
    double _fps;


    /** [r] 描画フレームカウンタ */
    frame _visualize_frames;
    /** [r] 前回fps計算時の描画フレームカウント値 */
    frame _prev_visualize_frames;
#ifdef MY_DEBUG
    /** [r] 1フレームの描画回数 */
    static unsigned int _num_draw;
    static unsigned int _num_draw_actors;
#endif
    /** [r] 1フレームの活動中アクター */
    static unsigned int _num_active_actors;

    /** [r] 描画処理、最高スキップフレーム数 */
    int _max_skip_frames;
    /** [r] 現在の処理落ちモード 0:60fps 1:40fps 2:30fps。_aaTime_offset_of_next_viewの一つ目の要素 */
    int _slowdown_mode;

    bool _was_cleaned;
public:
    /**
     * コンストラクタ .
     * 別スレッドで管理者を稼動させます。
     */
    Caretaker();

    /**
     * 提供する .
     * 管理者が提供する、すなわち、この世(Spacetime)が動き、アプリが進行します。<BR>
     * 初回呼び出し時、この世(Spacetime)が作成されます。<BR>
     * アプリケーションは、最小時間単位でこのメソッドをひたすら呼び続けてください。<BR>
     */
    void present();

    /**
     * この世のFPSを設定する .
     * 未設定の場合はデフォルトで 60 FPS
     * @param prm_fps FPS値
     */
    void setSpacetimeFps(int prm_fps);

    /**
     * この世の、最小時間単位の時間を流す .
     */
    virtual void presentMoment();

    /**
     * この世の、最小時間単位の振る舞いを行う .
     */
    virtual void presentBehave();

    /**
     * この世の、最小時間単位の瞬間について審判（チェック）する .
     */
    virtual void presentJudge();

    /**
     * この世の、最小時間単位の瞬間を具体化する .
     */
    virtual void presentMaterialize();

    /**
     * 具体化された物を、異界の人間共（俺ら）にも認識できるように視覚化する .
     */
    virtual void presentVisualize();

    /**
     * この世の次の最小時間単位の瞬間を創造するための準備、後始末 .
     */
    virtual void presentClosing();

    /**
     * この世を取得 .
     * 下位でオーバーライド可能。<BR>
     * @return この世
     */
    virtual Spacetime* getSpacetime() {
        return _pSpacetime;
    }

    /**
     * この世を創造 .
     * 下位でこの世の創造方法を実装してください。<BR>
     * @return この世
     */
    virtual Spacetime* createSpacetime() = 0;

    /**
     * フレームと時間の同期を行う
     */
    void syncTimeFrame() {
        _sync_frame_time = true;
    }

    void calmDown();

    virtual void clean();

    /**
     * 管理者「しまった～！」 .
     * 例外発生時にコールバックされます。
     */
    virtual void oops() {
        _TRACE_("(-_-;) {Oops!");
    }

    /**
     * 謁見 .
     * @return 私だ
     */
    static Caretaker* ask() {
        return GgafCore::Caretaker::_pCaretaker;
    }

    virtual ~Caretaker();


private:

    DWORD* getArrTimeOffset(DWORD sec, DWORD fps);

    /**
     * 管理者へのゆりかごの待ち行列に新たなゆりかご追加する（メインスレッドが使用） .
     * @param prm_cradle_no	ゆりかご番号
     * @param prm_pFunc	実際に祝福処理を行う関数のポインタ
     * @param prm_pWisher 望んだ人
     * @param prm_pReceiver 受け取り予定者
     * @param prm_pArg1	祝福処理を行う関数への引数1
     * @param prm_pArg2	祝福処理を行う関数への引数2
     * @param prm_pArg3	祝福処理を行う関数への引数3
     */
    void addCradle(uint64_t prm_cradle_no,
                   Object* (*prm_pFunc)(void*, void*, void*),
                   Object* prm_pWisher,
                   Object* prm_pReceiver,
                   void* prm_pArg1,
                   void* prm_pArg2,
                   void* prm_pArg3);

    /**
     * 管理者へのゆりかご行列を検索し、命を受け取る（メインスレッドが使用） .
     * 未祝福だった場合、祝福が完了するまで待つ。<BR>
     * @param prm_cradle_no	ゆりかご番号
     * @param prm_pReceiver	受取人
     * @param prm_was_just_wondering ちょっと気になっただけフラグ
     *                  true:命を受けとるまで待つが、ゆりかごリストから取り出さない
     *                  false:命を受けとり、ゆりかごリストから削除
     * @return	命のポインタ
     */
    void* takeOutObject(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering);


public:
    /** 先頭のゆりかご */
    Cradle* _pCradleRoot;
    /** 現在祝福中のゆりかご */
    Cradle* _pCradleBlessing;
    //_pCradleBlessing は、全て祝福済みの場合、最終ゆりかごを指しつづける
    //全て祝福済みかつ、ゆりかごが全て引き取られた場合は nullptr になる。
    //_is_last_cradle_flg == false を常に判定し、最終ゆりかごでなくなったら（新規ゆりかごがあれば）、
    //祝福を行って次に進める。 _is_last_cradle_flg == false になるまで祝福しつづける
    // また、先頭と末尾のゆりかごもポインタでつながっている(環状)

    //      _pCradleRoot
    //        ↓
    //      pCradle <-> pCradle <-> pCradle <-> pCradle <-> pCradle <-> pCradle
    //     (祝福済)     (祝福済)   （祝福中）   (未着手)    (未着手)    (未着手)
    //                                 ↑                                _is_last_cradle_flg == true
    //                           _pCradleBlessing
    //                      祝福を終えると右に動く  ===>
    //
    //prev <------古いゆりかご----------------------------------新しいゆりかご-----> next
    //                                               ゆりかごは末尾についてくる
#ifdef _MSC_VER
    //x86系ならばアトミック性がある・・・・・・・・。
    /** [r]愛してるフラグ */
    volatile bool _is_loving_flg;
    /** [r]休むフラグ */
    volatile bool _have_to_rest_flg;
    /** [r]休でいるフラグ */
    volatile bool _is_resting_flg;
    /** [r]愛のおわり */
    volatile bool _was_finished_loving_flg;
    /** [r]異界送り中フフラグ */
    volatile bool _is_sending_flg;
    /** [r]異界送のおわり */
    volatile bool _was_finished_sending_flg;
    /** [r] 時間とフレームの同期調整モード中はtrue */
    volatile bool _sync_frame_time;
#else
    /** [r]愛してるフラグ */
    volatile std::atomic<bool> _is_loving_flg;
    /** [r]休むフラグ */
    volatile std::atomic<bool> _have_to_rest_flg;
    /** [r]休でいるフラグ */
    volatile std::atomic<bool> _is_resting_flg;
    /** [r]愛のおわり */
    volatile std::atomic<bool> _was_finished_loving_flg;
    /** [r]異界送り中フラグ */
    volatile std::atomic<bool> _is_sending_flg;
    /** [r]異界送のおわり */
    volatile std::atomic<bool> _was_finished_sending_flg;
    /** [r] 時間とフレームの同期調整モード中はtrue */
    volatile std::atomic<bool> _sync_frame_time;
#endif
public:
    /**
     * 管理者にアクターを祝福してもらうための、ゆりかごをつくる（メインスレッドが使用） .
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
    void addActorCradle(uint64_t prm_cradle_no,
                        X* (*prm_pFunc)(void*, void*, void*),
                        Object* prm_pWisher,
                        Object* prm_pReceiver,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
        addCradle(prm_cradle_no, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * 管理者にシーン作成（祝福）してもらうための、ゆりかごをつくる（メインスレッドが使用） .
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
    void addSceneCradle(uint64_t prm_cradle_no,
                        X* (*prm_pFunc)(void*, void*, void*),
                        Object* prm_pWisher,
                        Object* prm_pReceiver,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
        addCradle(prm_cradle_no, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * 望んだアクターを受け取る。（メインスレッドが使用） .
     * メイン処理が呼び出します。<BR>
     * 未祝福だった場合、祝福が完了するまで待つ。<BR>
     * @param   prm_cradle_no ゆりかご番号
     * @param   prm_pReceiver 受取人
     * @param   prm_was_just_wondering ちょっと気になっただけフラグ
     *                  true:命を受けとるまで待つが、ゆりかごリストから取り出さない
     *                  false:命を受けとり、ゆりかごリストから削除
     * @return	生成されたアクターのポインタ
     */
    MainActor* takeOutActor(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering = false);

    /**
     * 望んだシーンを受け取る。（メインスレッドが使用） .
     * メイン処理が呼び出します。<BR>
     * 未祝福だった場合、祝福が完了するまで待つ。<BR>
     * @param   prm_cradle_no ゆりかご番号
     * @param   prm_pReceiver 受取人
     * @param   prm_was_just_wondering ちょっと気になっただけフラグ
     *                  true:命を受けとるまで待つが、ゆりかごリストから取り出さない
     *                  false:命を受けとり、ゆりかごリストから削除
     * @return	生成されたシーンのポインタ
     */
    MainScene* takeOutScene(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering = false);

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
                  Object* prm_pWisher,
                  Object* prm_pReceiver,
                  void* prm_pArg1,
                  void* prm_pArg2,
                  void* prm_pArg3,
                  Object* prm_org) {
        addCradle(ORDER_ID_MAX, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(takeOutObject(ORDER_ID_MAX, prm_org, false));
    }

    template<class X>
    X* makeActor(X* (*prm_pFunc)(void*, void*, void*),
                 Object* prm_pWisher,
                 Object* prm_pReceiver,
                 void* prm_pArg1,
                 void* prm_pArg2,
                 void* prm_pArg3,
                 Object* prm_org) {
        addActorCradle(ORDER_ID_MAX, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(takeOutActor(ORDER_ID_MAX, prm_org, false));
    }

    template<class X>
    X* makeScene(X* (*prm_pFunc)(void*, void*, void*),
                 Object* prm_pWisher,
                 Object* prm_pReceiver,
                 void* prm_pArg1,
                 void* prm_pArg2,
                 void* prm_pArg3,
                 Object* prm_org) {
        addSceneCradle(ORDER_ID_MAX, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(takeOutScene(ORDER_ID_MAX, prm_org, false));
    }

    /**
     * 望んだ命が出来上がっているか調べる。（メインスレッドが使用） .
     * @param prm_cradle_no   ゆりかご番号
     * @return ゆりかご番号の命の進捗状況(-2:管理者が愛していない/-1:ゆりかご自体が無い/0:ゆりかごは在るが未祝福/1:祝福中/2:祝福済み）
     */
    int chkCradle(uint64_t prm_cradle_no);

    /**
     * 見捨てる .
     * 揺り籠（とその命）をすべて消す（メインスレッドが使用） .
     * メイン処理の管理者が呼び出します。<BR>
     * _pCradleRoot が指しているゆりかごの連結リストを全て解放する<BR>
     * 注意：必ず以下のようにクリティカルセクションで囲んで呼び出してください！。<BR>
     * ＜コード例＞ <BR>
     *     BEGIN_SYNCHRONIZED1; // ----->排他開始<BR>
     * GgafCore::Caretaker::clean();<BR>
     *     END_SYNCHRONIZED1; // <----- 排他終了<BR>
     */
    void desert();

    /**
     * 後悔する .
     * 受け取るはずだった人が来なかったので、仕方ないので
     * お願いされていた命を破棄する。
     * @param prm_pReceiver 受け取るはずだった人
     */
    void repent(Object* prm_pReceiver);

    /**
     * 愛 .
     * 管理者（Caretaker）が初期設定時に別スレッドで一度実行されます。<BR>
     * 管理者が死ぬまで（アプリ終了まで）loving します。<BR>
     */
    static unsigned __stdcall love(void* prm_arg);

    /**
     * 現在未使用 .
     * @param prm_arg
     */
    static unsigned __stdcall send(void* prm_arg);

    /**
     * 永遠の愛 .
     * ゆりかごを受付て祝福し命を誕生させます。
     * @param prm_arg
     */
    unsigned loving(void* prm_arg);

    /**
     * 現在未使用 .
     * @param prm_arg
     */
    unsigned sending(void* prm_arg);

    /**
     * 管理者一時休止を指示 （メインスレッドが使用） .
     * しかし呼び出しても直ぐに休止状態になるとは限りません。<BR>
     * isResting() で完全休止するまで調べる続ける必要があります。<BR>
     */
    void beginRest();
    /**
     * 管理者の状態を取得（メインスレッドが使用） .
     * @return true=休止状態/false=稼動状態
     */
    bool isResting();

    /**
     * 管理者休止の解除を指示 （メインスレッドが使用） .
     */
    void finishRest();

    /**
     * 祝福する(引数は１つ) .
     * @tparam X 型
     * @param p1 引数1 (使用される(名前))
     * @param p2 引数2 (無視される)
     * @param p3 引数3 (無視される)
     * @return 祝福された命
     */
    template<class X>
    static X* bless(void* p1, void* p2, void* p3) {
        //p1 : 名称
        X* p = NEW X((const char*)p1);
        return p;
    }

    /**
     * 祝福する(引数は２つ) .
     * @tparam X 型
     * @param p1 引数1 (使用される(名前))
     * @param p2 引数2 (使用される)
     * @param p3 引数3 (無視される)
     * @return 祝福された命
     */
    template<class X>
    static X* bless2(void* p1, void* p2, void* p3) {
        //p1 : 名称
        X* p = NEW X((const char*)p1, (const char*)p2);
        return p;
    }

    /**
     * 祝福する(引数は３つ) .
     * @tparam X 型
     * @param p1 引数1 (使用される(名前))
     * @param p2 引数2 (使用される)
     * @param p3 引数3 (使用される)
     * @return 祝福された命
     */
    template<class X>
    static X* bless3(void* p1, void* p2, void* p3) {
        //p1 : 名称
        X* p = NEW X((const char*)p1, (const char*)p2, (const char*)p3);
        return p;
    }

    void debuginfo();

};


#define requestActor1(ID, CLASS)                   (GgafCore::Caretaker::_pCaretaker->addActorCradle<CLASS>((ID),GgafCore::Caretaker::bless, this, this, (void*)(#CLASS "_" #ID),(void*)(nullptr),(void*)(nullptr)))
#define requestActor2(ID, CLASS, NAME)             (GgafCore::Caretaker::_pCaretaker->addActorCradle<CLASS>((ID),GgafCore::Caretaker::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
#define requestActor3(ID, CLASS, NAME, ARG1)       (GgafCore::Caretaker::_pCaretaker->addActorCradle<CLASS>((ID),GgafCore::Caretaker::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr)))
#define requestActor4(ID, CLASS, NAME, ARG1, ARG2) (GgafCore::Caretaker::_pCaretaker->addActorCradle<CLASS>((ID),GgafCore::Caretaker::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2)))
#define selectRequestActorMacro(_1,_2,_3,_4,MACRO,...) MACRO

#define requestScene1(ID, CLASS)                   (GgafCore::Caretaker::_pCaretaker->addSceneCradle<CLASS>((ID),GgafCore::Caretaker::bless, this, this, (void*)(#CLASS "_" #ID),(void*)(nullptr),(void*)(nullptr)))
#define requestScene2(ID, CLASS, NAME)             (GgafCore::Caretaker::_pCaretaker->addSceneCradle<CLASS>((ID),GgafCore::Caretaker::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
#define requestScene3(ID, CLASS, NAME, ARG1)       (GgafCore::Caretaker::_pCaretaker->addSceneCradle<CLASS>((ID),GgafCore::Caretaker::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr)))
#define requestScene4(ID, CLASS, NAME, ARG1, ARG2) (GgafCore::Caretaker::_pCaretaker->addSceneCradle<CLASS>((ID),GgafCore::Caretaker::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2)))
#define selectRequestSceneMacro(_1,_2,_3,_4,MACRO,...) MACRO

#define desireActor1(CLASS)                   (GgafCore::Caretaker::_pCaretaker->makeActor<CLASS>(GgafCore::Caretaker::bless, this, this, (void*)(#CLASS),(void*)(nullptr),(void*)(nullptr),this))
#define desireActor2(CLASS, NAME)             (GgafCore::Caretaker::_pCaretaker->makeActor<CLASS>(GgafCore::Caretaker::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr),this))
#define desireActor3(CLASS, NAME, ARG1)       (GgafCore::Caretaker::_pCaretaker->makeActor<CLASS>(GgafCore::Caretaker::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr),this))
#define desireActor4(CLASS, NAME, ARG1, ARG2) (GgafCore::Caretaker::_pCaretaker->makeActor<CLASS>(GgafCore::Caretaker::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2),this))
#define selectDesireActorMacro(_1,_2,_3,_4,MACRO,...) MACRO

#define desireScene1(CLASS)                   (GgafCore::Caretaker::_pCaretaker->makeScene<CLASS>(GgafCore::Caretaker::bless, this, this, (void*)(#CLASS),(void*)(nullptr),(void*)(nullptr),this))
#define desireScene2(CLASS, NAME)             (GgafCore::Caretaker::_pCaretaker->makeScene<CLASS>(GgafCore::Caretaker::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr),this))
#define desireScene3(CLASS, NAME, ARG1)       (GgafCore::Caretaker::_pCaretaker->makeScene<CLASS>(GgafCore::Caretaker::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr),this))
#define desireScene4(CLASS, NAME, ARG1, ARG2) (GgafCore::Caretaker::_pCaretaker->makeScene<CLASS>(GgafCore::Caretaker::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2),this))
#define selectDesireSceneMacro(_1,_2,_3,_4,MACRO,...) MACRO

#ifdef _MSC_VER
    //MSVCの場合
    #define ___EXPAND( X ) X
    /** アクターを管理者に望む */
    #define requestActor(ID,...) ___EXPAND( selectRequestActorMacro(__VA_ARGS__,requestActor4,requestActor3,requestActor2,requestActor1)(ID,__VA_ARGS__) )
    /** シーンを管理者に望む */
    #define requestScene(ID,...) ___EXPAND( selectRequestSceneMacro(__VA_ARGS__,requestScene4,requestScene3,requestScene2,requestScene1)(ID,__VA_ARGS__) )
    /** シーンを管理者に望み、祝福され、受け取れるまで強欲に待つ */
    #define desireActor(...) ___EXPAND( selectDesireActorMacro(__VA_ARGS__,desireActor4,desireActor3,desireActor2,desireActor1)(__VA_ARGS__) )
    /** シーンを管理者に望み、祝福され、受け取れるまで強欲に待つ */
    #define desireScene(...) ___EXPAND( selectDesireSceneMacro(__VA_ARGS__,desireScene4,desireScene3,desireScene2,desireScene1)(__VA_ARGS__) )
#else
    //GCCの場合
    /** アクターを管理者に望む */
    #define requestActor(ID,...) selectRequestActorMacro(__VA_ARGS__,requestActor4,requestActor3,requestActor2,requestActor1)(ID,__VA_ARGS__)
    /** シーンを管理者に望む */
    #define requestScene(ID,...) selectRequestSceneMacro(__VA_ARGS__,requestScene4,requestScene3,requestScene2,requestScene1)(ID,__VA_ARGS__)
    /** シーンを管理者に望み、祝福され、受け取れるまで強欲に待つ */
    #define desireActor(...) selectDesireActorMacro(__VA_ARGS__,desireActor4,desireActor3,desireActor2,desireActor1)(__VA_ARGS__)
    /** シーンを管理者に望み、祝福され、受け取れるまで強欲に待つ */
    #define desireScene(...) selectDesireSceneMacro(__VA_ARGS__,desireScene4,desireScene3,desireScene2,desireScene1)(__VA_ARGS__)
#endif

/** 望まれ祝福されたアクターを受け取る。presentMoment()、presentJudge() の間のみ使用可能 */
#define receiveActor(ID) (GgafCore::Caretaker::_pCaretaker->takeOutActor((ID),this,false))
/** 望まれ祝福されたシーンを受け取る。 presentMoment()、presentJudge() の間のみ使用可能 */
#define receiveScene(ID) (GgafCore::Caretaker::_pCaretaker->takeOutScene((ID),this,false))

/** 望まれ祝福されたアクターを受け取れるまで待つ。presentMoment()、presentJudge() の間のみ使用可能 */
#define waitForRequestActor(ID) (GgafCore::Caretaker::_pCaretaker->takeOutActor((ID),this,true))
/** 望まれ祝福されたシーンを受け取れるまで待つ。 presentMoment()、presentJudge() の間のみ使用可能 */
#define waitForRequestScene(ID) (GgafCore::Caretaker::_pCaretaker->takeOutScene((ID),this,true))

}
#endif /*GGAF_CORE_CARETAKER_H_*/
