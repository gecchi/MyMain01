#ifndef GGAFDX9ALPHACURTAIN_H_
#define GGAFDX9ALPHACURTAIN_H_
namespace GgafDx9Core {

/**
 * αカーテン .
 * TODO:もっと汎用化
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class GgafDx9AlphaCurtain : public GgafCore::GgafCurtain {
public:
    GgafDx9Scene* _pDxScene;
    float _alpha;
    GgafDx9AlphaCurtain(GgafDx9Scene* prm_pScene);

    virtual void processOpenBegin() {}

    virtual void processOpening() {
        _alpha = 1.0 - _now_curtain_length;
    }

    virtual void processOpenDone() {
        _alpha = 1.0f;
    }

    virtual void processCloseBegin() {}

    virtual void processClosing() {
        _alpha = 1.0 - _now_curtain_length;
    }

    virtual void processCloseDone() {
        _alpha = 0.0f;
    }

    virtual ~GgafDx9AlphaCurtain();
};

}
#endif /*GGAFDX9ALPHACURTAIN_H_*/

