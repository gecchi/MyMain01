#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {

#define  ___BeginSynchronized ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  ___EndSynchronized ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))
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
    bool _can_be;
    /** be() 中かどうか */
    bool _is_being;
    /** [r]自身 */
    static GgafGod* _pGod;
    /** [r]生成工場(別スレッド)のエラー状態。NULL＝正常稼働中／not NULL＝異常発生 */
    static GgafCriticalException* _pException_Factory;
    /** [r]次にこの世を活動させる時間のオフセット */
    static DWORD _aTime_OffsetOfNextFrame[];
    /** [r]GgafFactory::work スレッドハンドル  */
    HANDLE _handleFactory01;
    /** [r]GgafFactory::work スレッドID  */
    unsigned int _thID01;
    /** [r]クリティカルセクション（セマフォ） */
    static CRITICAL_SECTION CS1;
    /** [r]クリティカルセクション（セマフォ） */
    static CRITICAL_SECTION CS2;
    /** [r]神のフレーム開始システム時間 */
    DWORD _time_at_beginning_frame;
    /** [r]次にこの世を活動させるシステム時間 */
    DWORD _expected_time_of_next_frame;
    /** [r]神誕生からのフレーム数 */
    DWORD _godframe;
    /** [r]この世を視覚化できなかった（スキップした）回数 */
    DWORD _skip_count_of_frame;
    /** [r]この世 */
    GgafUniverse* _pUniverse;
    /** [r]fps値（約1000ms毎に計算される） */
    float _fps;
    /** [r]前回fps計算時のシステム時間 */
    DWORD _time_prev;
    /** [r]描画フレームカウンタ */
    DWORD _frame_of_visualize;
    /** [r]前回fps計算時の描画フレームカウント値 */
    DWORD _frame_of_prev_visualize;
    /** [r]元フレームの描画回数 */
    static int _num_actor_drawing;


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

    virtual void clean();

    virtual ~GgafGod();
};

}
#endif /*GGAFGOD_H_*/
