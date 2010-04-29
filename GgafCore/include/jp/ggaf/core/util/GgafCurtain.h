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
    float _closeing_velocity;

    /**
     * コンストラクタ .
     * カーテンの長さは1.0に設定されます。<BR>
     * また、初期状態はカーテンは開いています。<BR>
     * @param _pScene カーテンを取り付けるシーン
     * @return
     */
    GgafCurtain(GgafScene* prm_pScene);

    /**
     * カーテンを開ける .
     * @param prm_opening_velocity カーテンを開ける速度
     */
    virtual void open(float prm_opening_velocity);

    /**
     * カーテンを閉める .
     * @param prm_closeing_velocity カーテンを閉める速度
     */
    virtual void close(float prm_closeing_velocity);

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
    virtual void processOpenBegin() {}

    /**
     * カーテンが開いていく途中の処理 .
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processOpening() {}

    /**
     * カーテンが開ききった時の処理 .
     * _now_curtain_lengthが0になった際１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processOpenDone() {}

    /**
     * カーテンが閉まり始める瞬間の処理 .
     * close() 時に１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processCloseBegin() {}

    /**
     * カーテンが閉まっていく途中の処理 .
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processClosing() {}

    /**
     * カーテンが閉まった時の処理 .
     * _now_curtain_length が _curtain_length になった際１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processCloseDone() {}

    virtual ~GgafCurtain();
};

}
#endif /*GGAFCURTAIN_H_*/
