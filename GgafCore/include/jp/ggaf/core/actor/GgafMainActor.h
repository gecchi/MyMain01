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

protected:

public:
    /** [r]自身が所属するグループの団長 */
    GgafGroupHead* _pGroupHead;
    /** [r]自身が所属するグループの団長の監督 */
    GgafDirector* _pDirector;

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

    /**
     * 自ツリーノードを連結リストから切り離し、独立する。 .
     * 切り離され穴が開いた部分は、周りのノードが穴を埋めます（再連結します）<BR>
     * 自ノードに子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
     * @return  自ノードのポインタ
     */
    virtual GgafMainActor* extract() override;

//    /**
//     * 活動中か調べる .
//     * フラグにによる活動判定に、所属元シーンが活動中であるかも条件に加える。
//     * これは、シーンのみがinactiveに状態になった場合、
//     * そこに所属するアクター達のフラグは影響を受けず矛盾する場合がある。
//     * TODO:厳密には、シーンの親シーンも全て調査する必要があるのだが、そのようなぶった切りは行わないように工夫する。
//     * @return アクターが活動中（かつ所属元シーンも活動中）
//     */
//    virtual bool isActive() override;

//        if (isActive() && _can_hit_flg) {
//            return true;
//        } else {
//            return false;
//        }
//    }

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
     * @return 監督
     */
    virtual GgafDirector* getSceneDirector();

    /**
     * シーン団長を取得する。 .
     * @return 団長
     */
    virtual GgafGroupHead* getMyGroupHead();

    /**
     * 新たに種別を設定し、アクターを配下に追加する。
     * 種別はアクターが保持する種別を無視し、引数の種別を優先する。
     * 配下に団長(GgafGroupHead)を挟んでその配下に引数のアクターを追加します。
     * GgafDirector::addSubGroup(actorkind, GgafMainActor) の説明を参照して下さい。
     * @param prm_kind 種別
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 挟み込まれている配下の団長(GgafGroupHead)
     */
    GgafGroupHead* addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * 新たに種別を設定し、アクターを配下に追加する。 .
     * ただし、種別はアクターが保持する種別を採用する。
     * 配下に団長(GgafGroupHead)を挟んでその配下に引数のアクターを追加します。
     * GgafDirector::addSubGroup(actorkind, GgafMainActor) の説明を参照して下さい。
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 挟み込まれている配下の団長(GgafGroupHead)
     */
    GgafGroupHead* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * 配下の生存可能な団長を探す。
     * @param prm_kind 探したい団長の種別
     * @return 団長、或いは存在しなければ NULL
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
