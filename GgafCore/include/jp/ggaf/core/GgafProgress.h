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
    frame* _paFrame_ProgressChange;
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
     * 進捗IDが起こった時のフレーム取得 .
     * @param prm_progress 進捗ID(1～99)
     * @return 引数の直近の進捗IDが起こったときのフレーム
     */
    virtual frame getFrameAtChanged(int prm_progress);

    virtual frame getActivePartFrameIn();

    /**
     * 進捗IDを設定 .
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
    virtual bool onActive(int prm_progress);

    virtual bool onInactive(int prm_progress);

    /**
     * 進捗IDが変化したか（前回と同じかどうか）調べる .
     * @return 0 又は 進捗ID
     *         0    ：変化していない
     *         0以外：変化が有りで、その新しい進捗ID
     */
    virtual int getOnActive();

    virtual int getOnInactive();


    virtual void update();

    virtual ~GgafProgress();
};

}
#endif /*GGAFCURTAIN_H_*/
