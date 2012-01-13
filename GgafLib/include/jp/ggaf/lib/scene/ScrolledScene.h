#ifndef SCROLLEDSCENE_H_
#define SCROLLEDSCENE_H_
namespace GgafLib {

/**
 * スクロールシーン .
 * 配下ツリーシーンの全アクターに対し、
 * 移動を適用することが可能。そんなシーンです。
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class ScrolledScene : public DefaultScene {
    /** スクロール速度 */
    velo _scroll_speed;
    /** [r/w]スクロール関数へのポインタ */
    void (*_pFuncScrolling)(GgafCore::GgafObject*, void*, void*);
public:

    /**
     * X軸方法にスクロール .
     * @param pThat アクター
     * @param p1 スクロールスピード(_scroll_speedへのポインタ)
     * @param p2 任意（引数は特に無し）
     */
    static void scroll_X(GgafObject* pThat, void* p1, void* p2);


    /**
     * スクロール関数を設定する。
     * 設定されたスクロール関数を配下ツリーシーンの全アクターに実行を行う。<BR>
     * 第１引数には、対象アクター、第２引数には、スクロールスピード(_scroll_speedへのポインタ)が渡される。<BR>
     * デフォルトでは ScrolledScene::scroll_X(GgafObject*, void*, void*) が設定されているが、<BR>
     * 本メソッドによって、ユーザー定義スクロール関数に切り替えができる。<BR>
     * @param prm_pFuncScrolling 引数が(GgafObject*, void*, void*) となる関数ポインタ
     */
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

    /**
     * 活動状態ならば、毎フレームスクロール関数を配下ツリーシーンの全アクターに実行。
     */
    virtual void processBehavior() override;


    virtual ~ScrolledScene();
};

}
#endif /*SCROLLEDSCENE_H_*/
