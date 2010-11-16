#ifndef GGAFCURTAIN_H_
#define GGAFCURTAIN_H_
namespace GgafCore {

enum GgafCurtainState {
    OPEN,
    OPENING,
    OPENED,
    CLOSE,
    CLOSING,
    CLOSED
};

/**
 * シーンのカーテン .
 * カーテンを開く、閉じるの管理します。<BR>
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class GgafCurtain : public GgafObject {

public:
    /** [r]カーテンを取り付けるシーン */
    GgafScene* _pScene;
    /** [r]現在のカーテンの状態 */
    GgafCurtainState _state;
    /** [r]カーテンの長さ */
    float _curtain_length;
    /** [r]現在のカーテンの長さ(開き具合) */
    float _now_curtain_length;
    /** [r]カーテンを開く際の速度 */
    float _opening_velocity;
    /** [r]カーテンを閉める際の速度 */
    float _closing_velocity;

    /**
     * コンストラクタ .
     * カーテンの長さは1.0に設定されます。<BR>
     * また、初期状態はカーテンは開いています。<BR>
     * @param prm_pScene カーテンを取り付けるシーン
     * @return
     */
    GgafCurtain(GgafScene* prm_pScene);

    /**
     * カーテンを徐々に開ける .
     * @param prm_opening_velocity カーテンを開ける速度
     */
    virtual void open(float prm_opening_velocity);

    /**
     * カーテンを即座に最大に開ける .
     */
    virtual void open();

    /**
     * カーテンを徐々に閉める .
     * @param prm_closing_velocity カーテンを閉める速度
     */
    virtual void close(float prm_closing_velocity);

    /**
     * カーテンを即座に閉めきる .
     */
    virtual void close();

    /**
     * カーテンを動かす .
     * 本クラスを機能させるにには、毎フレームこのメソッドを実行してください。
     * 毎フレーム behave() することで次のメソッドが適宜呼び出されるようになります。
     * <code>
     * processOpenBegin()
     * processOpening()
     * processOpenDone()
     * processCloseBegin()
     * processClosing()
     * processCloseDone()
     * </code>
     */
    virtual void behave();

    /**
     * カーテンが開き始める瞬間の処理 .
     * open() 時に１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processOpenBegin() = 0;

    /**
     * カーテンが開いていく途中の処理 .
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processOpening() = 0;

    /**
     * カーテンが開ききった時の処理 .
     * _now_curtain_lengthが0になった際１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processOpenDone() = 0;

    /**
     * カーテンが閉まり始める瞬間の処理 .
     * close() 時に１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processCloseBegin() = 0;

    /**
     * カーテンが閉まっていく途中の処理 .
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processClosing() = 0;

    /**
     * カーテンが閉まった時の処理 .
     * _now_curtain_length が _curtain_length になった際１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processCloseDone() = 0;


    virtual ~GgafCurtain();
};

}
#endif /*GGAFCURTAIN_H_*/
