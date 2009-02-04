#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {


#define SUPER GgafCore::GgafNode<T>

/**
 * GgafNodeに、様々な状態管理（フラグ管理）を追加するクラス。
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

protected:

	/** 神への近道 */
	GgafGod* _pGod;
	/** initializeが行われたどうかのフラグ(true=行われた) */
	bool _wasInitialized;

public:
	/** 余命 */
	DWORD _dwGodFrame_ofDeath;
	/** ノードが誕生(addSubされた）時からのフレーム */
	DWORD _dwFrame;
    /** 相対フレーム計算用 */
    DWORD _dwFrame_relative;
	/** ノード活動フラグ */
	bool _isPlaying;
	/** 一時停止フラグ */
	bool _wasPaused;
	/** 一時非表示フラグ */
	bool _wasBlinded;
	/** ノード生存フラグ */
	bool _isAlive;

	/** 次フレームのフレーム加算時に設定されるノード活動フラグ */
	bool _willPlayNextFrame;
	/** 次フレームのフレーム加算時に設定される一時停止フラグ */
	bool _willPauseNextFrame;
	/** 次フレームのフレーム加算時に設定される表示フラグ  */
	bool _willBlindNextFrame;
	/** 次フレームのフレーム加算時に設定される一時非表示フラグ */
	bool _willBeAliveNextFrame;

	/** 次フレームのフレーム加算時に、自ノードが先頭ノードに移動することを示したフラグ */
	bool _willMoveFirstNextFrame;
	/** 次フレームのフレーム加算時に、自ノードが末尾ノードに移動することを示したフラグ */
	bool _willMoveLastNextFrame;

	/** あとで活動フラグ */
	bool _willPlayAfterFrame;
	/** あとで活動の残フレーム数（神フレームと一致したら活動） */
	DWORD _dwGodFremeWhenPlay;

	/** あとで停止フラグ */
	bool _willStopAfterFrame;
	/** あとで停止の残フレーム数（神フレームと一致したら停止） */
	DWORD _dwGodFremeWhenStop;

	/** ノードが活動に切り替わった(stop→play)瞬間に１フレームだけセットされるフラグ */
	bool _switchedToPlay;
	/** ノードが停止に切り替わった(play→stop)瞬間に１フレームだけセットされるフラグ */
	bool _switchedToStop;

	/** 描画されましたフラグ */
	bool _wasExecuted_processDrawMain;


	/**
	 * コンストラクタ
	 * @param prm_name ノード名称（ユニークにして下さい）
	 */
	GgafElement(char* prm_name);

	/**
	 * デストラクタ。自ツリーノードを解放します。 .
	 */
	virtual ~GgafElement();

	/**
	 * 掃除 .
	 * 神が処理時間に余裕がでたとき等に呼ばれます。<BR>
	 * 配下ノードの中にノード生存フラグ(_isAlive)が false になっているノードがあれば prm_iNumCleanNode 個だけ delete します。<BR>
	 * @param prm_iNumCleanNode 解放するオブジェクト数
	 */
	virtual void cleane(int prm_iNumCleanNode);

	/**
	 * ノード初期処理 .
	 * インスタンス生成後、nextFrame(),behave(),judge(),drawPrior(),drawMain(),drawTerminate(),happen(int),finally() の
	 * 何れかが呼び出された時、最初に必ず１回だけ呼び出されます。<BR>
	 */
	virtual void initialize() {};

	/**
	 * ノードのフレームを加算と、フレーム開始にあたってのいろいろな初期処理 .
	 * 活動フラグ、生存フラグがセットされている場合ノードのフレームを加算します。その直後に<BR>
	 * _willPlayNextFrame, _willPauseNextFrame, _willBlindNextFrame, _willBeAliveNextFrame を<BR>
	 * _isPlaying, _wasPaused, _wasBlinded, _isAlive に反映（コピー）します。<BR>
	 * また、_willMoveFirstNextFrame, _willMoveLastNextFrame が true の場合は、<BR>
	 * それぞれ、自ノードの先頭ノードへの移動、末尾ノードへの移動も実行されます。<BR>
	 * その後、配下ノード全てに nextFrame() を実行します。<BR>
	 * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、behave()を実行します。<BR>
	 */
	virtual void nextFrame();

	/**
	 * ノードのフレーム毎の振る舞い処理 .
	 * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
	 * （_isPlaying && !_wasPaused && _isAlive）の場合 <BR>
	 * processBehavior() をコールした後、配下のノード全てについて behave() を実行します。<BR>
	 * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、judge()を実行します。<BR>
	 */
	virtual void behave();

	/**
	 * 再生時処理 .
	 * 停止状態から再生状態に変化したときに１度だけ呼ばれる。
	 * 必要に応じてオーバーライドします。
	 */
	virtual void onPlay() {};

	/**
	 * 停止時処理 .
	 * 再生状態から停止状態に変化したときに１度だけ呼ばれる。
	 * 必要に応じてオーバーライドします。
	 */
	virtual void onStop() {};

	/**
	 * ノードのフレーム毎の判定処理 .
	 * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
	 * (つまり _isPlaying && !_wasPaused && _isAlive)の場合 <BR>
	 * processJudgement() をコールした後、配下のノード全てについて judge() を実行します。<BR>
	 * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、フレーム時間に余裕があれば drawPrior()、無ければ finally()を実行します。<BR>
	 */
	virtual void judge();

	/**
	 * ノードのフレーム毎の描画事前処理（但し高負荷時は、神の判断でフレームスキップされて呼び出されないい場合もあります。） .
	 * 活動フラグ、生存フラグがセット、かつ一時非表示フラグがアンセット<BR>
	 * (つまり _isPlaying && !_wasBlinded && _isAlive)の場合 <BR>
	 * processDrawPrior() をコールした後、配下のノード全てについて drawPrior() を実行します。<BR>
	 * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、drawMain() を実行します。<BR>
	 */
	virtual void drawPrior();

	/**
	 * ノードのフレーム毎の描画本処理（但し高負荷時は、神の判断でフレームスキップされて呼び出されない場合もあります。） .
	 * 活動フラグ、生存フラグがセット、かつ一時非表示フラグがアンセット<BR>
	 * (つまり _isPlaying && !_wasBlinded && _isAlive)の場合 <BR>
	 * processDrawMain() をコールした後、配下のノード全てについて drawMain() を実行します。<BR>
	 * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、drawTerminate() を実行します。<BR>
	 */
	virtual void drawMain();

	/**
	 * ノードのフレーム毎の描画事後処理（但し高負荷時は、神の判断でフレームスキップされて呼び出されない場合もあります。） .
	 * 活動フラグ、生存フラグがセット、かつ一時非表示フラグがアンセット<BR>
	 * (つまり _isPlaying && !_wasBlinded && _isAlive)の場合 <BR>
	 * processTerminate() をコールした後、配下のノード全てについて drawTerminate() を実行します。<BR>
	 * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、finally() を実行します。<BR>
	 */
	virtual void drawTerminate();

	/**
	 * ノードのフレーム毎の最終処理 .
	 * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
	 * （_isPlaying && !_wasPaused && _isAlive）の場合 <BR>
	 * processFinally() をコールした後、配下のノード全てについて finally() を実行します。<BR>
	 * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、フレーム時間に余裕があれば cleane() を実行します。<BR>
	 */
	virtual void finally();

	/**
	 * ノードの何かの処理(フレーム毎ではない) .
	 * 活動フラグがセット、(つまり _isPlaying)の場合 <BR>
	 * processHappen(int) をコールした後、配下のノード全てについて happen() を実行します。<BR>
	 * @param	prm_no 何かの番号
	 */
	virtual void happen(int prm_no);

	/**
	 * フレーム毎の個別振る舞い処理を実装。 .
	 * behave() 時の処理先頭でコールバックされます。<BR>
	 * このメンバ関数を下位クラスでオーバーライドして、ノード個別の振る舞いを処理を実装します。<BR>
	 * 想定している振る舞い処理とは、主に座標計算と移動処理等です。<BR>
	 * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、nextFrame() が実行済みであることを保証します<BR>
	 */
	virtual void processBehavior() = 0;

	/**
	 * フレーム毎の個別判断処理を実装。 .
	 * judge() 時の処理先頭でコールバックされます。<BR>
	 * このメンバ関数をオーバーライドして、ノード個別判断処理を記述します。<BR>
	 * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、behave() が実行済みであることを保証します。<BR>
	 * 本メンバ関数の存在意図として、processBehavior() で座標移動処理が全て完了した後､本メンバ関数で当たり判定処理を実装するといった使い方を想定しています。<BR>
	 */
	virtual void processJudgement() = 0;

	/**
	 * ノードのフレーム毎の個別描画事前処理を実装。 .
	 * drawPrior() 時の処理先頭でコールバックされます。 但し、神(GgafGod)が描画スキップした場合、フレーム内で呼び出されません。<BR>
	 * このメンバ関数をオーバーライドして、ノード個別描画事前処理を実装します。<BR>
	 * 個別描画事前処理とは、主に当たり背景描画などです。<BR>
	 * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、judge() が実行済みであることも保証します<BR>
	 * さらに、本メンバ関数実行後、processDrawMain()、processDrawTerminate() が呼び出されることも保証されます。
	 */
	virtual void processDrawPrior() = 0;

	/**
	 * ノードのフレーム毎の個別描画本処理を実装。 .
	 * drawMain() 時の処理先頭でコールバックされます。 但し、drawPrior() と同様に神(GgafGod)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
	 * このメンバ関数をオーバーライドして、ノード個別描画本処理を実装します。<BR>
	 * 個別描画本処理とは主にキャラクタや、背景の描画を想定しています。
	 * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、drawPrior() が実行済みであることを保証します<BR>
	 */
	virtual void processDrawMain() = 0;

	/**
	 * ノードのフレーム毎の個別表示事後処理を記述
	 * drawTerminate() 時の処理先頭でコールバックされます。 但し、drawPrior() と同様に神(GgafGod)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
	 * このメンバ関数をオーバーライドして、ノード個別表示事後処理を実装します。<BR>
	 * 個別表示事後処理とは、最前面レイヤーで実現するフェードエフェクトや、常に最前面に表示される情報表示などです。<BR>
	 * 本メンバがコールバックされると言う事は、自ツリーノード全てに対して、drawMain() が実行済みであることを保証します<BR>
	 */
	virtual void processDrawTerminate() = 0;


	/**
	 * ノードのフレーム毎の個別終端処理を実装。 .
	 * finally() 時の処理先頭でコールバックされます。<BR>
	 * このメンバ関数を下位クラスでオーバーライドして、ノード個別の終端処理を実装します。<BR>
	 * 終端処理とは、フラグ管理の実行などです。<BR>
	 * 想定している振る舞い処理とは、主に座標計算と移動処理です。その他なんでも良いです。<BR>
	 * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、judge() が実行済みであることを保証します<BR>
	 */
	virtual void processFinal() = 0;

	/**
	 * ノードの個別何かの処理を記述
	 * happen() 時の処理先頭でコールバックされます。
	 * 利用目的不定の汎用イベント用メソッド
	 * @param	int prm_no 何かの番号
	 */
	virtual void processHappen(int prm_no) = 0;

    /**
	 * 神に謁見 .
	 * @return	呼ばれて出てきた神
	 */
	virtual GgafGod* askGod() = 0;

	/**
	 * 自ノードだけを次フレームから再生状態にする .
	 * <B>[補足]</B>ノード生成直後は、再生状態となっている。<BR>
	 */
	void playAlone();

	/**
	 * 自ツリーノードを次フレームから再生状態にする .
	 * 自身と自分より下位のノード全てに再生(play())が実行される。<BR>
	 * <B>[補足]</B>ノード生成直後は、再生状態となっている。<BR>
	 */
	void play();

	/**
	 * 自ノードだけをを即座に再生状態にする .
	 * <B>[補足]</B><BR>
	 * processFinal()以外に実装や、this 以外に実行する場合、そのノードの影響を良く考えて注意して使用すること。<BR>
	 */
	void playAloneImmediately();

	/**
	 * 自ツリーノードを即座に再生状態にする .
	 * 自身と自分より下位のノード全てに再生(playImmediately())が実行される。<BR>
	 * <B>[補足]</B><BR>
	 * processFinal()以外に実装や、this 以外に実行する場合、そのノードの影響を良く考えて注意して使用すること。<BR>
	 */
	void playImmediately();

	/**
	 * 自ツリーノードをNフレーム後に再生状態にする .
	 * @param prm_dwFrameOffset 遅延フレーム数
	 */
	void playAfter(DWORD prm_dwFrameOffset);

	/**
	 * 自ノードだけを次フレームから停止状態にする .
	 */
	void stopAlone();

	/**
	 * 自ツリーノードを次フレームから停止状態にする .
	 * 自身と自分より下位のノード全てに停止(play())が実行される。<BR>
	 */
	void stop();

	/**
	 * 自ノードだけを即座に停止状態にする .
	 * <B>[補足]</B><BR>
	 * processFinal()以外に実装や、this 以外で実行する場合、そのノードの影響を良く考えて注意して使用すること。<BR>
	 */
	void stopAloneImmediately();

	/**
	 * 自ツリーノードを即座に停止状態にする .
	 * 自身と自分より下位のノード全てに停止(playImmediately())が実行される。<BR>
	 * <B>[補足]</B><BR>
	 * processFinal()以外に実装や、this 以外で実行する場合、そのノードの影響を良く考えて注意して使用すること。<BR>
	 */
	void stopImmediately();

	/**
	 * 自ツリーノードをNフレーム後に停止状態にする .
	 * @param prm_dwFrameOffset 遅延フレーム数
	 */
	void stopAfter(DWORD prm_dwFrameOffset);

	/**
	 * 自ツリーノードを次フレームから一時停止状態にする .
	 * 自身と自分より下位のノード全てに一時停止(pause())が実行される。<BR>
	 * <B>[補足]</B>再生中に本関数を実行すると静止画像表示状態となる。<BR>
	 */
	void pause();

	/**
	 * 自ツリーノードを即座に一時停止状態にする .
	 * 自身と自分より下位のノード全てに一時停止状態(pauseImmediately())が実行される。<BR>
	 * <B>[補足]</B><BR>
	 * processFinal()以外に実装や、this 以外で実行する場合、そのノードの影響を良く考えて注意して使用すること。<BR>
	 */
	void pauseImmediately();

	/**
	 * 自ツリーノードを次フレームから一時停止解除にする .
	 * 自身と自分より下位のノード全てに一時停止解除(unpause())が実行される。<BR>
	 * <B>[補足]</B>pause()を行なわずに本メソッドを呼び出しても何も行いません。<BR>
	 */
	void unpause();

	/**
	 * 自ツリーノードを即座に一時停止解除にする .
	 * 自身と自分より下位のノード全てに一時停止状態(unpauseImmediately())が実行される。<BR>
	 * <B>[補足]</B><BR>
	 * processFinal()以外に実装や、this 以外で実行する場合、そのノードの影響を良く考えて注意して使用すること。<BR>
	 */
	void unpauseImmediately();

	/**
	 * 自ツリーノードを次フレームから非表示状態にする .
	 * 自身と自分より下位のノード全てに非表示状態(blind())が実行される。<BR>
	 * <B>[補足]</B>再生中に本関数を実行すると、オブジェクトは表示されないものの、内部的に座標移動、当たり判定などの活動は継続される。<BR>
	 */
	void blind();

	/**
	 * 自ノードだけ次フレームから非表示状態にする .
	 * <B>[補足]</B>再生中に本関数を実行すると、オブジェクトは表示されないものの、内部的に座標移動、当たり判定などの活動は継続される。<BR>
	 */
	void blindAlone();

	/**
	 * 自ツリーノードを即座に非表示状態にする .
	 * 自身と自分より下位のノード全てに非表示状態(blindImmediately())が実行される。<BR>
	 * <B>[補足]</B><BR>
	 * processFinal()以外に実装や、this 以外で実行する場合、そのノードの影響を良く考えて注意して使用すること。<BR>
	 */
	void blindImmediately();

	/**
	 * 自ノードだけ即座に非表示状態にする .
	 * <B>[補足]</B><BR>
	 * processFinal()以外に実装や、this 以外で実行する場合、そのノードの影響を良く考えて注意して使用すること。<BR>
	 */
	void blindAloneImmediately();

	/**
	 * 自ツリーノードを次フレームから非表示解除にする .
	 * 自身と自分より下位のノード全てに非表示解除(非表示())が実行される。<BR>
	 * <B>[補足]</B>blind()を行なわずに本メソッドを呼び出しても何も行いません。<BR>
	 */
	void unblind();

	/**
	 * 自ツリーノードを即座に非表示解除にする .
	 * 自身と自分より下位のノード全てに非表示状態(unblindImmediately())が実行される。<BR>
	 * <B>[補足]</B><BR>
	 * processFinal()以外に実装や、this 以外で実行する場合、そのノードの影響を良く考えて注意して使用すること。<BR>
	 */
	void unblindImmediately();

	/**
	 * 自ノードを次フレームから絶命させることを宣言します .
	 * 自身と自分より下位のノード全てに人生終了(farewell())がお知らせが届く。<BR>
	 * 絶命させるとは具体的には、表示フラグ(_wasBlinded)、振る舞いフラグ(_isPlaying)、生存フラグ(_isAlive) を <BR>
	 * 次フレームからアンセットする事である。<BR>
	 * これにより、神(GgafGod)が処理時間の余裕のあるフレームに実行する cleane()時に delete の対象となる。<BR>
	 * したがって、本メンバ関数を実行しても、フラグはアンセットされるため表面にはでませんが、インスタンスがすぐに解放されるとは限りません。<BR>
	 */
	void farewell(DWORD prm_dwFrameOffset = 0);

	/**
	 * 自ツリーノードを最終ノードに順繰りする .
	 * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの最終にシフトします。<BR>
	 * <B>[注意]</B>即座に順繰り処理が実行されるわけではありません。<BR>
	 */
	void moveLast();

	/**
	 * 自ツリーノードを先頭ノードに順繰りする .
	 * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの先頭にシフトします。<BR>
	 * <B>[注意]</B>即座に順繰り処理が実行されるわけではありません。<BR>
	 */
	void moveFirst();

	/**
	 * 所属ツリーから独立する
	 * @return	T* 脱退し独立した自ノードのポインタ
	 *
	 */
	T* becomeIndependent();

	/**
	 * 生存可能か調べる
	 * @return	bool true:生存可能／false:生存不可
	 */
	bool isAlive();

	/**
	 * 再生中か
	 * @return	bool true:再生中／false:停止中
	 */
	bool isPlaying();


	/**
	 * 停止から再生に切り替わったかどうか .
	 * ただし、onPlay() で代用できる場合は、そちらをオーバーライドしたほうがすっきり記述できるはず。
	 * @return	bool true:切り替わった／false:切り替わっていない
	 */
	bool switchedToPlay();

	/**
	 * 再生から停止に切り替わったかどうか .
	 * このメソッドは今のところ使いどころは無いかもしれません。
	 * @return	bool true:切り替わった／false:切り替わっていない
	 */
	bool switchedToStop();


	/**
	 * 活動しているか
	 * @return	bool true:活動可能／false:活動不可
	 */
	bool isBehaving();

	/**
	 * 描画できるか（非表示でないかどうか）
	 * @return	bool true:描画できる／false:描画はしない
	 */
	bool canDraw();

	/**
	 * ノードの現在の経過フレームを取得する
	 */
	DWORD getFrame();


	/**
	 * 相対経過フレームの判定。
	 * 直前の relativeFrame(int) 実行時（結果がtrue/falseに関わらず）のフレーム数からの経過フレーム数に達したか判定する。
	 * 注意：入れ子や条件分岐により、relativeFrame(int) が呼び出される回数が変化する場合、相対経過フレームも変化します。
	 * @param	prm_dwFrame_relative	経過フレーム数
	 * @return	bool	true:経過フレーム数に達した/false:達していない
	 */
	bool relativeFrame(DWORD prm_dwFrame_relative);

};



//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */


template<class T>
GgafElement<T>::GgafElement(char* prm_name) : SUPER (prm_name),
_pGod(NULL),
_wasInitialized(false),
_dwGodFrame_ofDeath(MAXDWORD),
_dwFrame(0),
_dwFrame_relative(0),
_isPlaying(true),
_wasPaused(false),
_wasBlinded(false),
_isAlive(true),
_willPlayNextFrame(true),
_willPauseNextFrame(false),
_willBlindNextFrame(false),
_willBeAliveNextFrame(true),
_willMoveFirstNextFrame(false),
_willMoveLastNextFrame(false),
_willPlayAfterFrame(false),
_dwGodFremeWhenPlay(0),
_willStopAfterFrame(false),
_dwGodFremeWhenStop(0),
_switchedToPlay(false),
_switchedToStop(false),
_wasExecuted_processDrawMain(false)
{
}


template<class T>
void GgafElement<T>::nextFrame() {
	TRACE("GgafElement::nextFrame BEGIN _dwFrame="<<_dwFrame<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);

	//死の時????????????????????????????????????????ここか？
	if (_dwGodFrame_ofDeath == (askGod()->_dwFrame_God)) {
		//_TRACE_("_dwGodFrame_ofDeath == _dwFrame<"<<SUPER::_class_name << ">::farewell() :"<< SUPER::getName() <<"_dwGodFrame_ofDeath="<<_dwGodFrame_ofDeath<<"/_dwFrame="<<_dwFrame);

		_willPlayNextFrame = false;
		_willBeAliveNextFrame = false;
	}

	if (_willMoveLastNextFrame) {
		_willMoveLastNextFrame = false;
		SUPER::moveLast();
	} else {

		if(_wasInitialized == false) {
			initialize();
			_wasInitialized = true;
		}

		_wasExecuted_processDrawMain = false; //未描画に

		if (_isAlive) {
			if (_willPlayAfterFrame) {
				//遅延play処理
				if (askGod()->_dwFrame_God == _dwGodFremeWhenPlay) {
					playImmediately();
					_willPlayAfterFrame = false;
				}
			} else if (_willStopAfterFrame) {
				//遅延stop処理
				if (askGod()->_dwFrame_God == _dwGodFremeWhenPlay) {
					stopImmediately();
					_willStopAfterFrame = false;
				}
			}
			if (_isPlaying) {
				_dwFrame++;
			}
		}

		//フラグたちを反映
		if (_isPlaying == false && _willPlayNextFrame) {
			// not Play → Play 状態の場合
			_switchedToPlay = true;
		} else if (_isPlaying && _willPlayNextFrame == false) {
			// Play → not Play 状態の場合
			_switchedToStop = true;
		} else {
			_switchedToPlay = false;
			_switchedToStop = false;
		}
		_isPlaying = _willPlayNextFrame;
		_wasPaused = _willPauseNextFrame;
		_wasBlinded = _willBlindNextFrame;
		_isAlive = _willBeAliveNextFrame;

		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				if (pElementTemp->_isLast) {
					pElementTemp->nextFrame();
					if (pElementTemp->_isAlive == false) {
						GgafFactory::_pGarbageBox->add(pElementTemp);
					}
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
					pElementTemp->SUPER::_pPrev->nextFrame();
					if (pElementTemp->SUPER::_pPrev->_isAlive == false) {
						GgafFactory::_pGarbageBox->add(pElementTemp->SUPER::_pPrev);
					}
				}
			}
		}

		if (_willMoveFirstNextFrame) {
			_willMoveFirstNextFrame = false;
			SUPER::moveFirst();
		}


	}
	TRACE("GgafElement::nextFrame END _dwFrame="<<_dwFrame<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);
}

template<class T>
void GgafElement<T>::behave() {
	if(_wasInitialized == false) {
		initialize();
		_wasInitialized = true;
	}

	if (_switchedToPlay) {
		onPlay();
	} else if (_switchedToStop) {
		onStop();
	}

	if (_isPlaying && !_wasPaused && _isAlive) {
		_dwFrame_relative = 0;
		processBehavior();
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->behave();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::judge() {
	if(_wasInitialized == false) {
		initialize();
		_wasInitialized = true;
	}

	if (_isPlaying && !_wasPaused && _isAlive) {
		_dwFrame_relative = 0;
		processJudgement();
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->judge();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}


template<class T>
void GgafElement<T>::drawPrior() {
	if(_wasInitialized == false) {
		initialize();
		_wasInitialized = true;
	}

	if (_isPlaying && !_wasBlinded && _isAlive) {
		_dwFrame_relative = 0;
		processDrawPrior();
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->drawPrior();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}


template<class T>
void GgafElement<T>::drawMain() {
	if(_wasInitialized == false) {
		initialize();
		_wasInitialized = true;
	}

	if (_isPlaying && !_wasBlinded && _isAlive) {
		_dwFrame_relative = 0;
		if (!_wasExecuted_processDrawMain) {
			processDrawMain();
			_wasExecuted_processDrawMain = true;
		}
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->drawMain();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}


template<class T>
void GgafElement<T>::drawTerminate() {
	if(_wasInitialized == false) {
		initialize();
		_wasInitialized = true;
	}

	if (_isPlaying && !_wasBlinded && _isAlive) {
		_dwFrame_relative = 0;
		processDrawTerminate();
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->drawTerminate();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}


template<class T>
void GgafElement<T>::happen(int prm_no) {
	if(_wasInitialized == false) {
		initialize();
		_wasInitialized = true;
	}

	if (_isAlive) {
		_dwFrame_relative = 0;
		processHappen(prm_no);
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->happen(prm_no);
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}


template<class T>
void GgafElement<T>::finally() {
	if(_wasInitialized == false) {
		initialize();
		_wasInitialized = true;
	}

	if (_isPlaying && !_wasPaused && _isAlive) {
		_dwFrame_relative = 0;
		processFinal();
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->finally();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}


}

template<class T>
void GgafElement<T>::playAlone() {
	if (_isAlive) {
		_willPlayNextFrame = true;
		_willPauseNextFrame = false;
		_willBlindNextFrame = false;
	}
}

template<class T>
void GgafElement<T>::play() {
	if (_isAlive) {
		_willPlayNextFrame = true;
		_willPauseNextFrame = false;
		_willBlindNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->play();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}


template<class T>
void GgafElement<T>::playAloneImmediately() {
	if (_isAlive) {
		if (_isPlaying == false) {
			_switchedToPlay = true;
		} else {
			_switchedToPlay = false;
		}
		_isPlaying = true;
		_wasPaused = false;
		_wasBlinded = false;
		_willPlayNextFrame = true;
		_willPauseNextFrame = false;
		_willBlindNextFrame = false;
	}
}

template<class T>
void GgafElement<T>::playImmediately() {
	if (_isAlive) {
		if (_isPlaying == false) {
			_switchedToPlay = true;
		} else {
			_switchedToPlay = false;
		}
		_isPlaying = true;
		_wasPaused = false;
		_wasBlinded = false;
		_willPlayNextFrame = true;
		_willPauseNextFrame = false;
		_willBlindNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->playImmediately();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}


template<class T>
void GgafElement<T>::playAfter(DWORD prm_dwFrameOffset) {
	_willPlayAfterFrame = true;
	_dwGodFremeWhenPlay = askGod()->_dwFrame_God + prm_dwFrameOffset;
}

template<class T>
void GgafElement<T>::stopAlone() {
	if (_isAlive) {
		_willPlayNextFrame = false;
	}
}

template<class T>
void GgafElement<T>::stop() {
	if (_isAlive) {
		_willPlayNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->stop();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::stopAfter(DWORD prm_dwFrameOffset) {
	_willStopAfterFrame = true;
	_dwGodFremeWhenStop = askGod()->_dwFrame_God + prm_dwFrameOffset;
}

template<class T>
void GgafElement<T>::stopAloneImmediately() {
	if (_isAlive) {
		if (_isPlaying) {
			_switchedToStop = true;
		} else {
			_switchedToStop = false;
		}
		_isPlaying = false;
		_willPlayNextFrame = false;
	}
}

template<class T>
void GgafElement<T>::stopImmediately() {
	if (_isAlive) {
		if (_isPlaying) {
			_switchedToStop = true;
		} else {
			_switchedToStop = false;
		}
		_isPlaying = false;
		_willPlayNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->stopImmediately();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::pause() {
	if (_isAlive) {
		_willPauseNextFrame = true;
		_isPlaying = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->pause();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			 }
		}
	}
}

template<class T>
void GgafElement<T>::pauseImmediately() {
	if (_isAlive) {
		_wasPaused = true;
		_willPauseNextFrame = true;
		_isPlaying = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->pauseImmediately();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			 }
		}
	}
}

template<class T>
void GgafElement<T>::unpause() {
	if (_isAlive) {
		_willPauseNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->unpause();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::unpauseImmediately() {
	if (_isAlive) {
		_wasPaused = false;
		_willPauseNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->unpauseImmediately();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::blind() {
	if (_isAlive) {
		_willBlindNextFrame = true;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->blind();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::blindAlone() {
	if (_isAlive) {
		_willBlindNextFrame = true;
	}
}

template<class T>
void GgafElement<T>::blindImmediately() {
	if (_isAlive) {
		_wasBlinded = true;
		_willBlindNextFrame = true;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->blindImmediately();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::blindAloneImmediately() {
	if (_isAlive) {
		_wasBlinded = true;
		_willBlindNextFrame = true;
	}
}


template<class T>
void GgafElement<T>::unblind() {
	if (_isAlive) {
		_willBlindNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->unblind();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::unblindImmediately() {
	if (_isAlive) {
		_wasBlinded = false;
		_willBlindNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			T* pElementTemp = SUPER::_pSubFirst;
			while(true) {
				pElementTemp->unblindImmediately();
				if (pElementTemp->_isLast) {
					break;
				} else {
					pElementTemp = pElementTemp->SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::farewell(DWORD prm_dwFrameOffset) {

	_dwGodFrame_ofDeath = (askGod()->_dwFrame_God) + prm_dwFrameOffset + 1;
//	_TRACE_("GgafElement<"<<SUPER::_class_name << ">::farewell() :"<< SUPER::getName() <<"_dwGodFrame_ofDeath="<<_dwGodFrame_ofDeath<<"/_dwFrame="<<_dwFrame<<"/prm_dwFrameOffset="<<prm_dwFrameOffset);
//	_willPlayNextFrame = false;
//	_willBeAliveNextFrame = false;
//	SUPER::_name = "_x_"+SUPER::_name;
	if (SUPER::_pSubFirst != NULL) {
		T* pElementTemp = SUPER::_pSubFirst;
		while(true) {
			pElementTemp->farewell(prm_dwFrameOffset);
			if (pElementTemp->_isLast) {
				break;
			} else {
				pElementTemp = pElementTemp->SUPER::_pNext;
			}
		}
	}
}

template<class T>
DWORD GgafElement<T>::getFrame() {
	return _dwFrame;
}

template<class T>
bool GgafElement<T>::isAlive() {
	return _isAlive;
}

template<class T>
bool GgafElement<T>::isPlaying() {
	if (_isAlive && _isPlaying) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool GgafElement<T>::switchedToPlay() {
	if (_isAlive && _switchedToPlay) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool GgafElement<T>::switchedToStop() {
	if (_isAlive && _switchedToStop) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool GgafElement<T>::canDraw() {
	if (_isAlive && _isPlaying && !_wasBlinded) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool GgafElement<T>::isBehaving() {
	if (_isAlive && _isPlaying && !_wasPaused) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool GgafElement<T>::relativeFrame(DWORD prm_dwFrame_relative) {
	_dwFrame_relative += prm_dwFrame_relative;
	if (_dwFrame == _dwFrame_relative) {
		return true;
	} else {
		return false;
	}
}

template<class T>
void GgafElement<T>::moveLast() {
	_willMoveLastNextFrame = true;
}

template<class T>
void GgafElement<T>::moveFirst() {
	_willMoveFirstNextFrame = true;
}

template<class T>
T* GgafElement<T>::becomeIndependent() {
	if (_isAlive) {
		return SUPER::tear();
	} else {
		throw_GgafCriticalException("[GgafTreeNode<"<<SUPER::_class_name<<">::becomeIndependent()] ＜警告＞ "<<SUPER::getName()<<"は、いずれ死に行く運命です。");
	}
}



template<class T>
void GgafElement<T>::cleane(int prm_iNumCleanNode) {
	if (SUPER::_pSubFirst == NULL) {
		return;
	}

	//_TRACE_("[GgafElement<"<<SUPER::_class_name<<">"<<SUPER::_name<<"::cleane()");
//	if (_isAlive == false) {
//		throw_GgafCriticalException("[GgafElement<"<<SUPER::_class_name<<">::cleane()] Error! 自殺しなければいけない状況。ココの処理に来る前に親に delete されなければ、おかしいです。(name="<<SUPER::getName()+")");
//	}

	T* pElementTemp = SUPER::_pSubFirst->_pPrev;
	T* pWk;

	while(GgafFactory::_s_iCountCleanedNode < prm_iNumCleanNode) {

		if (pElementTemp->_pSubFirst) {
			//子の子がまだのっている場合さらにもぐる
			pElementTemp->cleane(prm_iNumCleanNode);
			if (GgafFactory::_s_iCountCleanedNode >= prm_iNumCleanNode) {
				break;
			}
		}

		if (pElementTemp->_isFirst) { //最後の一つ
			if (pElementTemp->_pSubFirst) {
				//子の子がまだのっている場合さらにもぐる
				pElementTemp->cleane(prm_iNumCleanNode);
				if (GgafFactory::_s_iCountCleanedNode >= prm_iNumCleanNode) {
					break;
				}
			}
			if (pElementTemp->_isAlive == false) {
				DELETE_IMPOSSIBLE_NULL(pElementTemp);
				GgafFactory::_s_iCountCleanedNode++;
				Sleep(1);
			}
			break;
		} else {
			pWk = pElementTemp;
			if (pWk->_pSubFirst) {
				//子の子がまだのっている場合さらにもぐる
				pWk->cleane(prm_iNumCleanNode);
				if (GgafFactory::_s_iCountCleanedNode >= prm_iNumCleanNode) {
					break;
				}
			}
			pElementTemp = pElementTemp->_pPrev;
			if (pWk->_isAlive == false) {
				DELETE_IMPOSSIBLE_NULL(pWk);
				GgafFactory::_s_iCountCleanedNode++;
				Sleep(1);
			}
		}
	}

//
//
////				if (pElementTemp->_isFirst) { //末尾から見て行き最後の一つ
////				if (pElementTemp->_isAlive == false) {
////					DELETE_IMPOSSIBLE_NULL(pElementTemp);
////				}
////				break;
//			}
//			if (pElementTemp->_isFirst) { //一周した
//				break;
//			}
//		}
//	}
//
//	//子を調べてdeleteする
//	T* pElementTemp = SUPER::_pSubFirst->SUPER::_pPrev;
//	T* pWk;
//	while(GgafFactory::_s_iCountCleanedNode < prm_iNumCleanNode) {
//		if (pElementTemp->_isFirst) { //末尾から見て行き最後の一つ
//
//			if (pElementTemp->_isAlive == false) {
//				DELETE_IMPOSSIBLE_NULL(pElementTemp);
//			}
//			break;
//		} else { //末尾から順に見ていく
//			pElementTemp = pElementTemp->SUPER::_pPrev;
//			if (pElementTemp->SUPER::_pNext->_isAlive == false) {
//				pWk = pElementTemp->SUPER::_pNext;
//				DELETE_IMPOSSIBLE_NULL(pWk);
//			}
//		}
//	}
//
//	//子がまだのっている場合さらにもぐる
//	if (SUPER::_pSubFirst != NULL) {
//		pElementTemp = SUPER::_pSubFirst;
//		while(true) {
//			pElementTemp->cleane(prm_iNumCleanNode);
//			if (pElementTemp->_isLast) {
//				break;
//			} else {
//				pElementTemp = pElementTemp->SUPER::_pNext;
//			}
//		}
//	}
}



template<class T>
GgafElement<T>::~GgafElement() {
	//_TRACE_("~GgafElement() <"<<SUPER::_class_name << ">::farewell() :"<< SUPER::getName() <<"_dwGodFrame_ofDeath="<<_dwGodFrame_ofDeath<<"/_dwFrame="<<_dwFrame);

}


}
#endif /*GGAFELEMENT_H_*/
