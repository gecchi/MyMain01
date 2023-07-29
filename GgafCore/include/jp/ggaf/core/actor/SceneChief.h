#ifndef GGAF_CORE_SCENECHIEF_H_
#define GGAF_CORE_SCENECHIEF_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * シーンのチーフクラス .
 * シーンクラスとアクターの橋渡しを行う特別なアクター。<BR>
 * シーンクラスとシーンチーフは普通のhasAの関係です。（チーフと団長は階層関係になっています）<BR>
 * 全てのシーン(Sceaneオブジェクト)に必ず１人シーンチーフが居ます。<BR>
 * チーフは、アクター達ツリーの最も頂点に位置します。<BR>
 * チーフ(SceneChief)の子アクターは必ず団長(GroupHead)になっています。<BR>
 * さらに団長の下に普通のアクターが居ます。<BR>
 * チーフへのメソッド実行は、その配下全ての団長＋アクターへの指示となります。<BR>
 * 団長(GroupHead)の解説もあわせて参照して下さい。
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class SceneChief : public Actor {

private:
    /** 現在の所属シーン */
    Scene* _pScene_platform;

private:
    /**
     * 使用不可 .
     */
    SceneChief* extract() override {
        throwCriticalException("SceneChief に extract() は実行できません。name="<<getName());
        return (SceneChief*)nullptr;
    }

    /**
     * 所属シーンを設定する。.
     */
    void setPlatformScene(Scene* prm_pScene_platform) {
        _pScene_platform = prm_pScene_platform;
    }

public:
    SceneChief(Scene* prm_pScene_platform);

    /**
     * 初期処理<BR>
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    void processSettlementBehavior() override {
    }

    void processJudgement() override {
    }
    bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
    }
    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }


    void processFinal() override {
    }


    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void throwEventUpperTree(eventval prm_event_val, void* prm_pSource) override;
    void throwEventUpperTree(eventval prm_event_val) override {
        throwEventUpperTree(prm_event_val, this);
    }
    void onHit(const Actor* prm_pOtherActor) override {
    }

    void remove();

    /**
     * 所属しているシーンを取得。 .
     * @return	Scene*	所属しているシーン
     */
    virtual Scene* getPlatformScene() {
        return _pScene_platform;
    }

    /**
     * グループとして引数のアクターを子アクターに追加します .
     * これは自動でGroupHeadオブジェクトが間に挿入されます。<BR>
     * したがってグループ種別と共に登録が必要です。<BR>
     * 種別とは、内部で生成される GroupHead名 にも使用されます。<BR>
     * GroupHeadオブジェクト は初回種別登録時だけ生成され、２回目以降の同一種別登録は、<BR>
     * 既存の GroupHeadオブジェクトの子に追加されます。<BR>
     * <pre>
     * ＜使用例１＞
     *
     *  appendGroupChild(KIND_XXX, pActor);
     *
     *  とした場合、階層構造は次のようになる。
     *
     *  this
     *    |
     *    +- pObject(GroupHead[KIND_XXX])
     *         |
     *         +- pActor
     *
     *
     * ＜使用例２＞
     *
     * appendGroupChild(KIND_AAA, pActor01);
     * appendGroupChild(KIND_BBB, pActor02);
     * appendGroupChild(KIND_AAA, pActor03);
     *
     * とした場合、階層構造は次のようになる。
     *
     *  this
     *    |
     *    +- pObject(GroupHead[KIND_AAA]) -- pObject(GroupHead[KIND_BBB])
     *         |                                    |
     *         +- pActor01 -- pActor03              + pActor02
     * </pre>
     * 補足：引数の prm_pMainActor 以下全てのアクターに関して、
     *       ・所属シーンメンバ (_pScene_platform)
     *       ・チーフアクターメンバ(_pSceneChief)
     *       ・団長アクターメンバ(_pGroupHead) ※但し下位に他の団長がいた場合はそこまで
     *       の更新を行います。
     * @param   prm_kind    種別名（＝GroupHead名）
     * @param   prm_pMainActor   登録するアクター
     */
    GroupHead* appendGroupChild(kind_t prm_kind, MainActor* prm_pMainActor);

    /**
     * 単独Actor、或いはDestructActorが単独親となるActor連続体を<BR>
     * 種別は引数子アクターのステータス(getStatus())の項目 'STAT_DEFAULT_ACTOR_KIND' の値が、種別として
     * 上書きコピーされる。
     * 本関数はの部的処理は prm_pActor を GroupHead の子アクターとしているだけである。<BR>
     * @param   prm_pMainActor   登録するアクター
     */
    GroupHead* appendGroupChild(MainActor* prm_pMainActor);

    /**
     * 子の団長アクターを取得、無ければnullptrを帰す
     * @param prm_kind
     * @return
     */
    GroupHead* searchChildGroupHead(kind_t prm_kind);

    void updateActiveInTheTree() override;

    /**
     * 管理者に謁見 .
     * @return    呼ばれて出てきた管理者
     */
    Caretaker* askCaretaker();

    /**
     * 配下ツリーアクターから、引数の名前を持つアクターを探す .
     * 引数は、アクター名を Util::easy_hash(const char* str) でHASH値に変換した値を渡す。
     * @param prm_name_hash アクター名HASH値
     * @return 最初に発見したアクター／発見できない場合は nullptr
     */
    Actor* search(hashval prm_name_hash);

    virtual ~SceneChief();
};

}
#endif /**GGAF_CORE_SCENECHIEF_H_*/
