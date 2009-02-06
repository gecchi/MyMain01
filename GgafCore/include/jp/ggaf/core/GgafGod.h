#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {

/**
 * 神クラス.
 * 世界(GgafWorld)を管理します。
 */
class GgafGod : public GgafObject {

public:

    /** 生成工場(別スレッド)のエラー状態。NULL＝正常稼働中／not NULL＝異常発生 */
    static GgafCriticalException* _pException_Factory;
    /** 次に世界を活動させる時間のオフセット */
    static DWORD _aDwTime_OffsetOfNextFrame[];

    /** GgafFactory::work スレッドハンドル  */
    HANDLE _handleFactory01;
    /** GgafFactory::work スレッドID  */
    unsigned int _thID01;
    /** クリティカルセクション（セマフォ） */
    static CRITICAL_SECTION CS1;
    static CRITICAL_SECTION CS2;

    /** 神のフレーム開始システム時間 */
    DWORD _dwTime_FrameBegin;
    /** 次に世界を活動させるシステム時間 */
    DWORD _dwTime_ScheduledNextFrame;
    /** 神誕生からのフレーム数 */
    DWORD _dwFrame_God;
    /** 世界を視覚化できなかった（スキップした）回数 */
    DWORD _dwFrame_SkipCount;
    /** 世界 */
    GgafWorld* _pWorld;

    /** fps値（約1000ms毎に計算される） */
    float _fFps;
    /** 前回fps計算時のシステム時間 */
    DWORD _dwTime_Prev;
    /** 描画フレームカウンタ */
    DWORD _dwFrame_Visualize;
    /** 前回fps計算時の描画フレームカウント値 */
    DWORD _dwFrame_PrevVisualize;

    /**  */
    static int _iNumPlayingActor;

    bool _isBehaved;

    /**
     * コンストラクタ.
     * 別スレッドで工場を稼動させます。
     */
    GgafGod();

    /**
     * 神の存在<BR>
     */
    void be();

    /**
     * 世界を存在させる<BR>
     */
    virtual void makeWorldBe();

    /**
     * 世界を審判する<BR>
     */
    virtual void makeWorldJudge();

    /**
     * 世界を具現化する<BR>
     */
    virtual void makeWorldMaterialize();

    /**
     * 世界を視覚化する<BR>
     */
    virtual void makeWorldVisualize();

    /**
     * 世界の後始末<BR>
     */
    virtual void makeWorldFinalize();

    /**
     * 世界を取得<BR>
     * @return 世界
     */
    virtual GgafWorld* getWorld() {
        return _pWorld;
    }

    /**
     * 世界を創造<BR>
     * @return 世界
     */
    virtual GgafWorld* createWorld() = 0;

    virtual ~GgafGod();
};

}
#endif /*GGAFGOD_H_*/
