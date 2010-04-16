﻿#ifndef GGAFMAINACTOR_H_
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
    /** [r]シーン管理者 */
    GgafLordActor* _pLordActor;
    /** [r]グループを司る直近の団長 */
    GgafGroupActor* _pGroupActor;

    GgafMainActor(const char* prm_name);

    /**
     * 次のノード取得する。 .
     * @return	次ノード
     */
    virtual GgafMainActor* getNext() override {
        return (GgafMainActor*)GgafActor::getNext();
    }

    /**
     * 前のノード取得する。 .
     * @return	前ノード
     */
    virtual GgafMainActor* getPrev() override {
        return (GgafMainActor*)GgafActor::getPrev();
    }

    /**
     * 子ノードのグループの先頭ノードを取得する .
     * 子ノードが存在しない場合はエラー。
     * @return	子ノードの先頭ノード
     */
    virtual GgafMainActor* getSubFirst() override {
        return (GgafMainActor*)GgafActor::getSubFirst();
    }

    /**
     * 自ツリーノードを連結リストから切り離し、独立する。 .
     * 切り離され穴が開いた部分は、周りのノードが穴を埋めます（再連結します）<BR>
     * 自ノードに子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
     * @return	自ノードのポインタ
     */
    virtual GgafMainActor* extract() override {
        return (GgafMainActor*)GgafActor::extract();
    }

    /**
     * シーン管理者を設定する。 .
     */
    virtual void setLordActor(GgafLordActor* prm_pLordActor);

    /**
     * 団長を設定する。<BR>
     */
    virtual void setGroupActor(GgafGroupActor* prm_pGroupActor);

    /**
     * シーン管理者取得。 .
     * @return 管理者
     */
    virtual GgafLordActor* getLordActor();

    /**
     * シーン団長を取得する。 .
     * @return 団長
     */
    virtual GgafGroupActor* getGroupActor();

    /**
     * 新たに種別を設定し、アクターを配下に追加する。
     * 種別はアクターが保持する種別を無視し、引数の種別を優先する。
     * 配下に団長(GgafGroupActor)を挟んでその配下に引数のアクターを追加します。
     * GgafLordActor::addSubGroup(actorkind, GgafMainActor) の説明を参照して下さい。
     * @param prm_kind 種別
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 挟み込まれている配下の団長(GgafGroupActor)
     */
    GgafGroupActor* addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * 新たに種別を設定し、アクターを配下に追加する。 .
     * ただし、種別はアクターが保持する種別を採用する。
     * 配下に団長(GgafGroupActor)を挟んでその配下に引数のアクターを追加します。
     * GgafLordActor::addSubGroup(actorkind, GgafMainActor) の説明を参照して下さい。
     * @param prm_pMainActor 種別と共に追加したいアクター
     * @return 挟み込まれている配下の団長(GgafGroupActor)
     */
    GgafGroupActor* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * 配下の団長を探す。
     * @param prm_kind 探したい団長の種別
     * @return 団長、或いは存在しなければ NULL
     */
    GgafGroupActor* getSubGroupActor(actorkind prm_kind);

    /**
     * 神に謁見 .
     * @return	呼ばれて出てきた神
     */
    virtual GgafGod* askGod();

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
