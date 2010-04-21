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
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class GgafCurtain : public GgafObject {

public:
    /** カーテンを取り付けるシーン */
    GgafScene* _pScene;

    GgafCurtainState _state;

    int _curtain_length;
    int _now_curtain_length;
    int _opening_velocity;
    int _closeing_velocity;

    /**
     * コンストラクタ .
     * @param prm_pScene カーテンを取り付けるシーン
     * @return
     */
    GgafCurtain(int prm_curtain_length);

    virtual void open(int prm_opening_velocity);

    virtual void close(int prm_closeing_velocity);

    virtual void behave();

    virtual void processOpenBegin() {}

    virtual void processOpening() {}

    virtual void processOpenDone() {}

    virtual void processCloseBegin() {}

    virtual void processClosing() {}

    virtual void processCloseDone() {}

    virtual ~GgafCurtain();
};

}
#endif /*GGAFCURTAIN_H_*/
