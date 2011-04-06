#ifndef GGAFPROGRESS_H_
#define GGAFPROGRESS_H_
namespace GgafCore {


/**
 * 進捗管理クラス .
 * @version 1.00
 * @since 2010/11/18
 * @author Masatoshi Tsuge
 */
class GgafProgress : public GgafObject {

public:

    /** [r]現在進捗ID(1～99) */
    int _progress;
    /** [r]１フレーム前進捗ID(1～99) */
    int _progress_prev;
    /** [r]次フレーム加算時に反映予定の進捗ID(1～99) */
    int _progress_nextframe;
    /** [r]進捗IDイベント時フレームストック */
    frame* _paFrame_ProgressChanged;
    frame* _pFrame_behaving;

    /**
     * コンストラクタ .
     */
    GgafProgress(frame* prm_pFrame_behaving, int prm_num);


    /**
     * 現在の進捗ID取得 .
     * @return 進捗ID(1～99)
     */
    virtual int get();

    /**
     * 現在の進捗を設定する .
     * 即座に反映される。<BR>
     * 初期化などではこの set(int) を使用し、<BR>
     * 状態変化時は change(int) を使用する。<BR>
     * という設計。<BR>
     * @param prm_progress 進捗ID(1～99)
     */
    virtual void set(int prm_progress);

    /**
     * 進捗IDが起こった時のフレーム取得 .
     * @param prm_progress 進捗ID(1～99)
     * @return 引数の直近の進捗IDが起こったときのフレーム
     */
    virtual frame getFrameWhenChanged(int prm_progress);

    /**
     * 進捗内経過フレームを取得 .
     * @return 進捗内経過フレーム
     */
    virtual frame getActivePartFrameInProgress();

    /**
     * 進捗IDを変更 .
     * 但し、同一フレーム内では反映されず、nextFrame() 時に反映される。
     * @param prm_progress 進捗ID(1～99)
     */
    virtual void change(int prm_progress);

    /**
     * 進捗IDを+1する .
     * 1～99 の範囲となるように注意すること。
     * 但し、同一フレーム内では反映されず、nextFrame() 時に反映される。
     */

    virtual void changeNext();

    /**
     * 引数の進捗IDに切り替わったかどうか調べる。.
     * 切り替わった nextFrame() 時に1フレームだけtrueになります。
     * @param prm_progress 切り替わったかどうか調べたい進捗ID
     * @return true:引数の進捗IDに切り替わった／false:それ以外
     */
    virtual bool wasChangedTo(int prm_progress);

    /**
     * 現在の進捗に切り替わった直後なのかを判定。
     * change(int) により切り替えられた際、 nextFrame() 時に1フレームだけ true になります。
     * @return true:進捗に切り替わった直後である／false:それ以外
     */
    virtual bool isJustChanged();

    /**
     * 引数の進捗IDから切り替わったのかどうかを調べる。.
     * 切り替わった際に、直前の進捗IDを条件として調べることが出来る。
     * 切り替わった nextFrame() 時に1フレームだけtrueになります。
     * @param prm_progress 切り替わった際、前の進捗IDは何であったかどうか調べたい進捗ID
     * @return true:切り替わった際、前の進捗IDは引数の進捗IDだった／false:それ以外
     */
    virtual bool wasChangedFrom(int prm_progress);

    /**
     * 進捗IDが変化したか（前回と同じかどうか）調べる .
     * 変化した場合、その新しい進捗IDを返す。
     * @return 0 又は 進捗ID
     *         0    ：変化していない
     *         0以外：変化が有りで、その新しい進捗ID
     */
    virtual int getChangedTo();

    /**
     * 進捗IDが変化したか（前回と同じかどうか）調べる .
     * 変化した場合、その元の進捗IDを返す。
     * @return 0 又は 進捗ID
     *         0    ：変化していない
     *         0以外：変化が有りで、変化前の元の進捗ID
     */
    virtual int getChangedFrom();


    virtual void update();

    virtual ~GgafProgress();
};

}
#endif /*GGAFCURTAIN_H_*/
