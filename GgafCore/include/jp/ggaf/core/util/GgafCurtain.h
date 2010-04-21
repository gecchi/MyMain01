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

    float _curtain_length;
    float _now_curtain_length;
    float _opening_velocity;
    float _closeing_velocity;

    /**
     * コンストラクタ .
     * @param prm_curtain_length カーテンの長さ
     * @return
     */
    GgafCurtain();

    virtual void open(float prm_opening_velocity);

    virtual void close(float prm_closeing_velocity);

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
