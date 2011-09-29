#ifndef GGAFDXALPHACURTAIN_H_
#define GGAFDXALPHACURTAIN_H_
namespace GgafDxCore {

/**
 * αカーテン .
 * TODO:もっと汎用化
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaCurtain : public GgafCore::GgafCurtain {
public:
    GgafDxScene* _pDxScene;
    float _alpha;

    GgafDxAlphaCurtain(GgafDxScene* prm_pScene);

    void processOpenBegin() override {
    }

    void processOpening() override {
        _alpha = 1.0 - _now_curtain_length;
    }

    void processOpenDone() override {
        _alpha = 1.0f;
    }

    void processCloseBegin() override {
    }

    void processClosing() override {
        _alpha = 1.0 - _now_curtain_length;
    }

    void processCloseDone() override {
        _alpha = 0.0f;
    }

    virtual ~GgafDxAlphaCurtain();
};

}
#endif /*GGAFDXALPHACURTAIN_H_*/

