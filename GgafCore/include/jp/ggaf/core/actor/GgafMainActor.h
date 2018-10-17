#ifndef GGAFCORE_GGAFMAINACTOR_H_
#define GGAFCORE_GGAFMAINACTOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/GgafActor.h"

namespace GgafCore {

/**
 * 普通のアクター(演者) .
 * 下位アクタークラスへのインターフェイスであり、<BR>
 * 新たにアクタークラスを作る場合本クラスを継承してアクタークラスを作ることとする。<BR>
 * @version 1.00
 * @since 2008/03/24
 * @author Masatoshi Tsuge
 */
class GgafMainActor : public GgafActor {

public:
    /** [r]自身が所属するグループの団長 */
    GgafGroupHead* _pGroupHead;
    /** [r]自身が所属するグループの団長のシーン仲介者 */
    GgafSceneMediator* _pSceneMediator;

public:
    GgafMainActor(const char* prm_name, GgafStatus* prm_pStat);

    virtual GgafMainActor* getNext() const override { //共変戻り値
        return (GgafMainActor*)GgafActor::getNext();
    }

    virtual GgafMainActor* getPrev() const override { //共変戻り値
        return (GgafMainActor*)GgafActor::getPrev();
    }

    void updateActiveInTheTree() override;

    /**
     * 自ツリーノードを連結リストから切り離し、独立する。 .
     * 切り離され穴が開いた部分は、周りのノードが穴を埋めます（再連結します）<BR>
     * 自ノードに子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
     * GgafMainActorの場合、配下の _pSceneMediator 及び _pGroupHead に nullptr がセットされる。<BR>
     * @return  自ノードのポインタ
     */
    virtual GgafMainActor* extract() override;

    /**
     * シーン仲介者を設定する。 .
     */
    virtual void setMySceneMediator(GgafSceneMediator* prm_pSceneMediator);

    /**
     * 団長を設定する。<BR>
     */
    virtual void setMyGroupHead(GgafGroupHead* prm_pGroupHead);

    /**
     * 所属シーンのシーン仲介者取得。但しシーンに所属していない場合は、この世(Spacetime)のシーン仲介者を返す .
     * @return 所属シーン仲介者の仲介者。(いない場合 この世(Spacetime)の仲介者)
     */
    GgafSceneMediator* getMySceneMediator();

    /**
     * シーン団長を取得する。 .
     * @return 団長 ／ いない場合 nullptr
     */
    virtual GgafGroupHead* getMyGroupHead();

    /**
     * 新たに種別を設定し、アクターを配下に追加する。
     * 種別はアクターが保持する種別を無視し、引数の種別を優先する。<BR>
     * 自身と種別が異なる場合は子に団長(GgafGroupHead)を挟んでそのまた子に引数のアクターを追加します。<BR>
     * 自身と種別が同じ場合は、単に子に引数のアクターを追加します。<BR>
     * @param prm_kind 種別
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 引数アクターの団長(GgafGroupHead)
     */
    GgafGroupHead* appendGroupChild(kind_t prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * 新たに種別を設定し、アクターを配下に追加する。 .
     * ただし、種別はアクターが保持する種別を採用する。<BR>
     * 自身と種別が異なる場合は子に団長(GgafGroupHead)を挟んでそのまた子に引数のアクターを追加します。<BR>
     * 自身と種別が同じ場合は、単に子に引数のアクターを追加します。<BR>
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 引数アクターの団長(GgafGroupHead)
     */
    GgafGroupHead* appendGroupChild(GgafMainActor* prm_pMainActor);

    /**
     * 配下の生存可能な団長を探す。
     * @param prm_kind 探したい団長の種別
     * @return 団長、或いは存在しなければ nullptr
     */
    GgafGroupHead* searchChildGroupHead(kind_t prm_kind);

    /**
     * 神に謁見 .
     * @return  呼ばれて出てきた神
     */
    virtual GgafGod* askGod() override;

    /**
     * 所属している団長の種別を取得する .
     * 下位の実装で自由に使用することを想定。
     * @return
     */
    kind_t lookUpKind();

    virtual ~GgafMainActor();
};

}
#endif /*GGAFCORE_GGAFMAINACTOR_H_*/
