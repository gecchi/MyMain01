#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {

#define  ___BeginSynchronized ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  ___EndSynchronized ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))

/**
 * 神クラス.
 * 主にこの世(GgafUniverse)を管理します。<BR>
 * この世がゲームアプリとするならば、このクラスが一番えらい。<BR>
 * 基本的にインスタンスは１個です。<BR>
 * その他アプリ内でグローバルな参照を集中させたり、なにかと煩雑で便利屋クラスでもある。<BR>
 * TODO:最終的には 神を２個 new して、交互に be() を実行すれば、ゲームが２個平行動作するようにしようかな。
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
    static int _num_actor_playing;

    bool _is_behaved_flg;
    bool _is_materialized_flg;

    /**
     * コンストラクタ.
     * 別スレッドで工場を稼動させます。
     */
    GgafGod();

    /**
     * ここに居てます.<BR>
     */
    void be();

    /**
     * この世をの瞬間を作成<BR>
     */
    virtual void makeUniversalMoment();

    /**
     * この世を審判する<BR>
     */
    virtual void makeUniversalJudge();

    /**
     * この世を具現化する<BR>
     */
    virtual void makeUniversalMaterialize();

    /**
     * この世を視覚化する<BR>
     */
    virtual void makeUniversalVisualize();

    /**
     * この世の後始末<BR>
     */
    virtual void makeUniversalFinalize();

    /**
     * この世を取得<BR>
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
