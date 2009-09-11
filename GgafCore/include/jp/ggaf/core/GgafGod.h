#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {

#define  ___BeginSynchronized ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  ___EndSynchronized ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))

/**
 * 神クラス.
 * 主にこの世を管理し操作することを目的とするクラスです。一番えらい。<BR>
 * 本クラスの be() メソッドを呼び続けることで、この余は動きます。<BR>
 * 基本的にインスタンスは１個です。<BR>
 * その他、アプリ内でグローバルな参照が在ったり便利屋クラスでもある。<BR>
 * TODO:最終的には 神を２個 new して、交互に be() を実行すれば、ゲームが２個平行動作するようにしよう。
 */
class GgafGod : public GgafObject {

public:
    /** 自身 */
    static GgafGod* _pGod;

    /** 生成工場(別スレッド)のエラー状態。NULL＝正常稼働中／not NULL＝異常発生 */
    static GgafCriticalException* _pException_Factory;
    /** 次にこの世を活動させる時間のオフセット */
    static DWORD _aTime_OffsetOfNextFrame[];

    /** GgafFactory::work スレッドハンドル  */
    HANDLE _handleFactory01;
    /** GgafFactory::work スレッドID  */
    unsigned int _thID01;
    /** クリティカルセクション（セマフォ） */
    static CRITICAL_SECTION CS1;
    static CRITICAL_SECTION CS2;

    /** 神のフレーム開始システム時間 */
    DWORD _time_at_beginning_frame;
    /** 次にこの世を活動させるシステム時間 */
    DWORD _expected_time_of_next_frame;
    /** 神誕生からのフレーム数 */
    DWORD _godframe;
    /** この世を視覚化できなかった（スキップした）回数 */
    DWORD _skip_count_of_frame;
    /** この世 */
    GgafUniverse* _pUniverse;

    /** fps値（約1000ms毎に計算される） */
    float _fps;
    /** 前回fps計算時のシステム時間 */
    DWORD _time_prev;
    /** 描画フレームカウンタ */
    DWORD _frame_of_visualize;
    /** 前回fps計算時の描画フレームカウント値 */
    DWORD _frame_of_prev_visualize;

    /**  */
    static int _num_actor_drawing;

    bool _is_behaved_flg;
    bool _is_materialized_flg;

    /**
     * コンストラクタ.
     * 別スレッドで工場を稼動させます。
     */
    GgafGod();

    /**
     * 在ります。というメソッド。.<BR>
     * 神が在るすなわち、この世が動き、アプリが進行します。<BR>
     * OS側で、このメソッドをひたすら呼び続けてください。<BR>
     */
    void be();

    /**
     * この世の瞬間を創造<BR>
     */
    virtual void presentUniversalMoment();

    /**
     * この世の瞬間を審判する<BR>
     */
    virtual void enforcementUniversalJudge();

    /**
     * この世の瞬間の具現的なものを作成<BR>
     */
    virtual void makeUniversalMaterialize();

    /**
     * この世の瞬間の状態を映像化<BR>
     */
    virtual void presentUniversalVisualize();

    /**
     * この世の後始末<BR>
     */
    virtual void finalizeUniversal();

    /**
     * この世を取得<BR>
     * 下位でオーバーライドしてください。<BR>
     * @return この世
     */
    virtual GgafUniverse* getUniverse() {
        return _pUniverse;
    }

    /**
     * この世を創造<BR>
     * @return この世
     */
    virtual GgafUniverse* createUniverse() = 0;

    virtual ~GgafGod();
};

}
#endif /*GGAFGOD_H_*/
