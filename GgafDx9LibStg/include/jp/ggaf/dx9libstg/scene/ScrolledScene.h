#ifndef SCROLLEDSCENE_H_
#define SCROLLEDSCENE_H_
namespace GgafDx9LibStg {

/**
 * スクロールシーン .
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class ScrolledScene : public DefaultScene {
    /** スクロール速度 */
    velo _scrool_speed;
    /** [r/w]毎フレームprocessSettlementBehavior()で、配下アクター全てに実行される関数。*/
    void (*_pFuncScrolling)(GgafCore::GgafObject*, void*, void*);
public:

    static void scroll_X(GgafObject* pThat, void* p1, void* p2);


    void setScrollingFunction(void (*prm_pFuncScrolling)(GgafCore::GgafObject*, void*, void*)) {
        _pFuncScrolling = prm_pFuncScrolling;
    }

    void setScroolSpeed(velo prm_scrool_speed) {
        _scrool_speed = prm_scrool_speed;
    }

    velo getScroolSpeed() {
        return _scrool_speed;
    }

    void addScroolSpeed(acce prm_acce) {
        _scrool_speed += prm_acce;
    }


    /**
     *
     * @param prm_name
     * @return
     */
    ScrolledScene(const char* prm_name);


    virtual void processSettlementBehavior() override;


    virtual ~ScrolledScene();
};

}
#endif /*SCROLLEDSCENE_H_*/
