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
    /** [r]自身が所属するグループの団長 */
    GroupHead* _pGroupHead;
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
     * MainActorの場合、配下の _pSceneChief 及び _pGroupHead に nullptr がセットされる。<BR>
     * @return  自ノードのポインタ
     */
    virtual MainActor* extract() override;

    /**
     * シーンチーフを設定する。 .
     */
    virtual void setSceneChief(SceneChief* prm_pSceneChief);

    /**
     * 団長を設定する。<BR>
     */
    virtual void setGroupHead(GroupHead* prm_pGroupHead);

    /**
     * 所属シーンのシーンチーフ取得。但しシーンに所属していない場合は、この世(Spacetime)のシーンチーフを返す .
     * @return 所属シーンチーフのチーフ。(いない場合 この世(Spacetime)のチーフ)
     */
    SceneChief* getSceneChief();

    /**
     * シーン団長を取得する。 .
     * @return 団長 ／ いない場合 nullptr
     */
    virtual GroupHead* getGroupHead();

    /**
     * 新たに種別を設定し、アクターを配下に追加する。
     * 種別はアクターが保持する種別を無視し、引数の種別を優先する。<BR>
     * 自身と種別が異なる場合は子に団長(GroupHead)を挟んでそのまた子に引数のアクターを追加します。<BR>
     * 自身と種別が同じ場合は、単に子に引数のアクターを追加します。<BR>
     * @param prm_kind 種別
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 引数アクターの団長(GroupHead)
     */
    GroupHead* appendGroupChild(kind_t prm_kind, MainActor* prm_pMainActor);

    /**
     * 新たに種別を設定し、アクターを配下に追加する。 .
     * ただし、種別はアクターが保持する種別を採用する。<BR>
     * 自身と種別が異なる場合は子に団長(GroupHead)を挟んでそのまた子に引数のアクターを追加します。<BR>
     * 自身と種別が同じ場合は、単に子に引数のアクターを追加します。<BR>
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 引数アクターの団長(GroupHead)
     */
    GroupHead* appendGroupChild(MainActor* prm_pMainActor);

    /**
     * 配下の生存可能な団長を探す。
     * @param prm_kind 探したい団長の種別
     * @return 団長、或いは存在しなければ nullptr
     */
    GroupHead* searchChildGroupHead(kind_t prm_kind);

    /**
     * 管理者に謁見 .
     * @return  呼ばれて出てきた管理者
     */
    virtual Caretaker* askCaretaker() override;

    /**
     * 所属している団長の種別を取得する .
     * 下位の実装で自由に使用することを想定。
     * @return
     */
    kind_t lookUpKind();

    bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
    }

    /**
     * 破壊されたことを通知 .
     * 所属シーンにも通知して Scene::onDestroyedActor(Actor*) をコールバックします
     */
    virtual void notifyDestroyed() override;

    virtual ~MainActor();
};

}
#endif /*GGAF_CORE_MAINACTOR_H_*/
