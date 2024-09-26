#ifndef GGAF_CORE_MAINACTOR_H_
#define GGAF_CORE_MAINACTOR_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * 普通のアクター(演者) .
 * 下位アクタークラスへのインターフェイスであり、<BR>
 * 新たにアクタークラスを作る場合本クラスを継承してアクタークラスを作ることとする。<BR>
 * @version 1.00
 * @since 2008/03/24
 * @author Masatoshi Tsuge
 */
class MainActor : public Actor {

public:
    /** [r]自身が所属するグループの団長のシーンチーフ */
    SceneChief* _pSceneChief;

public:
    MainActor(const char* prm_name);

    virtual MainActor* getNext() const override { //共変戻り値
        return (MainActor*)Actor::getNext();
    }

    virtual MainActor* getPrev() const override { //共変戻り値
        return (MainActor*)Actor::getPrev();
    }

    void updateActiveInTheTree() override;

    /**
     * 自ツリーノードを連結リストから切り離し、独立する。 .
     * 切り離され穴が開いた部分は、周りのノードが穴を埋めます（再連結します）<BR>
     * 自ノードに子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
     * 配下の _pSceneChief に nullptr がセットされる。<BR>
     * @return  自ノードのポインタ
     */
    virtual MainActor* extract() override;

    /**
     * シーンチーフを設定する。 .
     */
    virtual void setSceneChief(SceneChief* prm_pSceneChief);

    /**
     * 所属シーンのシーンチーフ取得。但しシーンに所属していない場合は、この世(Spacetime)のシーンチーフを返す .
     * @return 所属シーンチーフのチーフ。(いない場合 この世(Spacetime)のチーフ)
     */
    SceneChief* getSceneChief();

    /**
     * 管理者に謁見 .
     * @return  呼ばれて出てきた管理者
     */
    virtual Caretaker* askCaretaker() override;

    /**
     * 破壊されたことを通知 .
     * 所属シーンにも通知して Scene::onDestroyedActor(Actor*) をコールバックします
     */
    virtual void notifyDestroyed() override;

    virtual ~MainActor();
};

}
#endif /*GGAF_CORE_MAINACTOR_H_*/
