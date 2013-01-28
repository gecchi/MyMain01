#ifndef GGAFMAINACTOR_H_
#define GGAFMAINACTOR_H_

namespace GgafCore {

/**
 * 普通のアクター(演者).
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
    /** [r]自身が所属するグループの団長の監督 */
    GgafDirector* _pDirector;

public:
    GgafMainActor(const char* prm_name, GgafStatus* prm_pStat);

    /**
     * 次のノード取得する。 .
     * @return  次ノード
     */
    virtual GgafMainActor* getNext() override {
        return (GgafMainActor*)GgafActor::getNext();
    }

    /**
     * 前のノード取得する。 .
     * @return  前ノード
     */
    virtual GgafMainActor* getPrev() override {
        return (GgafMainActor*)GgafActor::getPrev();
    }

    /**
     * 子ノードのグループの先頭ノードを取得する .
     * 子ノードが存在しない場合はエラー。
     * @return  子ノードの先頭ノード
     */
    virtual GgafMainActor* getSubFirst() override {
        return (GgafMainActor*)GgafActor::getSubFirst();
    }


    void updateActiveInTheTree() override;

    /**
     * 自ツリーノードを連結リストから切り離し、独立する。 .
     * 切り離され穴が開いた部分は、周りのノードが穴を埋めます（再連結します）<BR>
     * 自ノードに子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
     * @return  自ノードのポインタ
     */
    virtual GgafMainActor* extract() override;

    /**
     * シーン監督を設定する。 .
     */
    virtual void setSceneDirector(GgafDirector* prm_pDirector);

    /**
     * 団長を設定する。<BR>
     */
    virtual void setGroupHead(GgafGroupHead* prm_pGroupHead);

    /**
     * シーン監督取得。 .
     * @return 監督 ／ いない場合 nullptr
     */
    virtual GgafDirector* getSceneDirector();

    /**
     * シーン団長を取得する。 .
     * @return 団長 ／ いない場合 nullptr
     */
    virtual GgafGroupHead* getMyGroupHead();

    /**
     * 新たに種別を設定し、アクターを配下に追加する。
     * 種別はアクターが保持する種別を無視し、引数の種別を優先する。<BR>
     * 自身と種別が異なる場合はサブに団長(GgafGroupHead)を挟んでそのまたサブに引数のアクターを追加します。<BR>
     * 自身と種別が同じ場合は、単にサブに引数のアクターを追加します。<BR>
     * @param prm_kind 種別
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 引数アクターの団長(GgafGroupHead)
     */
    GgafGroupHead* addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * 新たに種別を設定し、アクターを配下に追加する。 .
     * ただし、種別はアクターが保持する種別を採用する。<BR>
     * 自身と種別が異なる場合はサブに団長(GgafGroupHead)を挟んでそのまたサブに引数のアクターを追加します。<BR>
     * 自身と種別が同じ場合は、単にサブに引数のアクターを追加します。<BR>
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 引数アクターの団長(GgafGroupHead)
     */
    GgafGroupHead* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * 配下の生存可能な団長を探す。
     * @param prm_kind 探したい団長の種別
     * @return 団長、或いは存在しなければ nullptr
     */
    GgafGroupHead* searchSubGroupHead(actorkind prm_kind);

    /**
     * 神に謁見 .
     * @return  呼ばれて出てきた神
     */
    virtual GgafGod* askGod() override;

    /**
     * 種別を取得する .
     * 下位の実装で自由に使用することを想定。
     * @return
     */
    actorkind getKind();

    virtual ~GgafMainActor();
};

}
#endif /*GGAFMAINACTOR_H_*/
