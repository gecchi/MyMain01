#ifndef GGAFGOD_H_
#define GGAFGOD_H_



class GgafGod : public GgafObject {

public:
	static int _s_iNumClean_Node;

	static DWORD _dwNextTimeOffset[];
	/** GgafSubcontractor::work スレッドハンドル  */
	HANDLE _handleFactory01;
	/** GgafSubcontractor::work スレッドID  */
	unsigned int _thID01;
	/** クリティカルセクション（セマフォ） */
	static CRITICAL_SECTION CS1;
	static CRITICAL_SECTION CS2;
	/** フレーム開始システム時間 */
	DWORD _dwTime_FrameBegin;
	/** 次にGgafWorldを活動させる時間 */
	DWORD _dwTime_ScheduledNextFrame;
	/** 神誕生からのフレーム数 */
	DWORD _dwFrame_God;
	/** スキップフレームカウンタ */
	DWORD _dwFrame_SkipCount;

	/** fps値（約1000ms毎に計算される） */
	float _fFps;
	/** 前回fps計算時のシステム時間 */
	DWORD _dwTime_Prev;
	/** 描画フレームカウンタ */
	DWORD _dwFrame_Visualize;
	/** 前回fps計算時の描画フレームカウント値 */
	DWORD _dwFrame_PrevVisualize;

	/** 直下のワールドシーン */
	GgafWorld* _pWorld;

	GgafGod();

	/**
	 * 存在する<BR>
	 */
	void be();

//	/**
//	 * フレームを進める<BR>
//	 */
//	virtual void nextFrame();

	/**
	 * 世界を存在させる<BR>
	 */
	virtual void makeWorldBe();

	/**
	 * 世界を審判する<BR>
	 */
	virtual void makeWorldJudge();

	/**
	 * 具現化する<BR>
	 */
	virtual void makeWorldMaterialize();

	/**
	 * 視覚化する<BR>
	 */
	virtual void makeWorldVisualize();

	/**
	 * 最終<BR>
	 */
	virtual void makeWorldFinalize();


	virtual GgafWorld* getWorld();

    /**
     * Worldシーンを作成。
	 */
	virtual GgafWorld* createWorld() = 0;


	virtual ~GgafGod();
};



#endif /*GGAFGOD_H_*/
