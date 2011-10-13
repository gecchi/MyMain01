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
    float _min_alpha;
    float _max_alpha;
    float _range_alpha;
    float _alpha;

    GgafDxAlphaCurtain(GgafDxScene* prm_pScene, float prm_min_alpha = 0.0f, float prm_max_alpha = 1.0f);

    void processOpenBegin() override {
    }

    void processOpening() override {
        _alpha = _max_alpha - _now_curtain_length;
    }

    void processOpenDone() override {
        _alpha = _max_alpha;
    }

    void processCloseBegin() override {
    }

    void processClosing() override {
        _alpha = _max_alpha - _now_curtain_length;
    }

    void processCloseDone() override {
        _alpha = _min_alpha;
    }

    virtual ~GgafDxAlphaCurtain();
};

}
#endif /*GGAFDXALPHACURTAIN_H_*/

