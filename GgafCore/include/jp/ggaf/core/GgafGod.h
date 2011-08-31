#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {

#define  ___BeginSynchronized ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  ___EndSynchronized ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))
#define  SLOWDOWN_MODE_DEFAULT 0
#define  SLOWDOWN_MODE_40FPS 1
#define  SLOWDOWN_MODE_30FPS 2
/**
 * 神クラス.
 * 主にこの世(GgafUniverse)を管理し操作することを目的とするクラスです。一番えらい。<BR>
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
    /** be() できるかどうか */
    static volatile bool _can_be;
    /** [r]クリティカルセクション（セマフォ） */
    static CRITICAL_SECTION CS1;

    /** be() 中かどうか */
    bool _is_being;
    /** [r]自身 */
    static GgafGod* _pGod;
    /** [r]生成工場(別スレッド)のエラー状態。NULL＝正常稼働中／not NULL＝異常発生 */
    static GgafCriticalException* _pException_Factory;
    /** [r]次にこの世を活動させる時間のオフセット */
    static DWORD _aaTime_OffsetOfNextFrame[3][60];
    /** [r]GgafFactory::work スレッドハンドル  */
    HANDLE _handleFactory01;
    /** [r]GgafFactory::work スレッドID  */
    unsigned int _thID01;
    /** [r]神のフレーム開始システム時間 */
    DWORD _time_at_beginning_frame;
    /** [r]次にこの世を活動させるシステム時間 */
    DWORD _expected_time_of_next_frame;
    /** [r]神誕生からのフレーム数 */
    frame _frame_of_God;
    /** [r]この世を視覚化できなかった（スキップした）回数 */
    int _skip_count_of_frame;
    /** [r]この世 */
    GgafUniverse* _pUniverse;
    /** [r]fps値（約1000ms毎に計算される） */
    float _fps;
    /** [r]前回fps計算時のシステム時間 */
    DWORD _time_prev;
    /** [r]描画フレームカウンタ */
    frame _frame_of_visualize;
    /** [r]前回fps計算時の描画フレームカウント値 */
    frame _frame_of_prev_visualize;
    /** [r]元フレームの描画回数 */
    static int _num_actor_drawing;

    int _max_skip_frames;
    /** 現在の処理落ちモード 0:60fps 1:40fps 2:30fps。_aaTime_OffsetOfNextFrameの一つ目の要素 */
    int _slowdown_mode;
    /** 時間とフレームの動機調整モード中はtrue */
    bool _sync_frame_time;
    bool _was_cleaned;

    /**
     * コンストラクタ .
     * 別スレッドで工場を稼動させます。
     */
    GgafGod();

    /**
     * 在ります。というメソッド .
     * 神が在るすなわち、この世が動き、アプリが進行します。<BR>
     * OS側で、このメソッドをひたすら呼び続けてください。<BR>
     */
    void be();

    /**
     * この世の瞬間を創造 .
     */
    virtual void presentUniversalMoment();

    /**
     * この世を審判する .
     */
    virtual void executeUniversalJudge();

    /**
     * この世の具現的なものを作成 .
     */
    virtual void makeUniversalMaterialize();

    /**
     * この世の状態を視覚化 .
     */
    virtual void presentUniversalVisualize();

    /**
     * この世の後始末 .
     */
    virtual void finalizeUniversal();

    /**
     * この世を取得 .
     * 下位でオーバーライド可能。<BR>
     * @return この世
     */
    virtual GgafUniverse* getUniverse() {
        return _pUniverse;
    }

    /**
     * この世を創造 .
     * 下位でこの世の生成方法を実装してください。<BR>
     * @return この世
     */
    virtual GgafUniverse* createUniverse() = 0;

    /**
     * 描画を一時停止し、フレームと時間の同期を行う
     */
    void syncTimeFrame() {
        _sync_frame_time = true;
    }

    virtual void clean();

    /**
     * しまった～！、という時に呼び出す。
     */
    virtual void oops() {
        _TRACE_("(-_-;) {Oops!");
    }

    virtual ~GgafGod();
};

}
#endif /*GGAFGOD_H_*/
