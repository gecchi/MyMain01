#ifndef SCROLLEDSCENE_H_
#define SCROLLEDSCENE_H_
namespace GgafLib {

/**
 * スクロールシーン .
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class ScrolledScene : public DefaultScene {
    /** スクロール速度 */
    velo _scroll_speed;
    /** [r/w]毎フレームprocessSettlementBehavior()で、配下アクター全てに実行される関数。*/
    void (*_pFuncScrolling)(GgafCore::GgafObject*, void*, void*);
public:

    static void scroll_X(GgafObject* pThat, void* p1, void* p2);


    void setScrollingFunction(void (*prm_pFuncScrolling)(GgafCore::GgafObject*, void*, void*)) {
        _pFuncScrolling = prm_pFuncScrolling;
    }

    void setScrollSpeed(velo prm_scroll_speed) {
        _scroll_speed = prm_scroll_speed;
    }

    velo getScrollSpeed() {
        return _scroll_speed;
    }

    void addScrollSpeed(acce prm_acce) {
        _scroll_speed += prm_acce;
    }


    /**
     *
     * @param prm_name
     * @return
     */
    ScrolledScene(const char* prm_name);


    virtual void processBehavior() override;


    virtual ~ScrolledScene();
};

}
#endif /*SCROLLEDSCENE_H_*/
