#ifndef SCROLLEDSCENE_H_
#define SCROLLEDSCENE_H_
namespace GgafLib {

/**
 * �X�N���[���V�[�� .
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class ScrolledScene : public DefaultScene {
    /** �X�N���[�����x */
    velo _scroll_speed;
    /** [r/w]���t���[��processSettlementBehavior()�ŁA�z���A�N�^�[�S�ĂɎ��s�����֐��B*/
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
