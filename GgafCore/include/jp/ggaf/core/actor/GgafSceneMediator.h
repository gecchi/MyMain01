#ifndef GGAFCORE_GGAFSCENEMEDIATOR_H_
#define GGAFCORE_GGAFSCENEMEDIATOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/GgafActor.h"

namespace GgafCore {

/**
 * シーンの仲介者クラス .
 * 団長(GgafGroupHead)の親階層のアクターで、団長達を管理します。<BR>
 * また、シーンクラスとの橋渡しを行う特別なアクターでもあります。<BR>
 * シーンクラスとシーン仲介者は普通のhasAの関係です。（仲介者と団長は階層関係になっています）<BR>
 * 全てのシーン(GgafSceaneオブジェクト)に必ず１人シーン仲介者が居ます。<BR>
 * 仲介者は、アクター達ツリーの最も頂点に位置します。<BR>
 * 仲介者(GgafSceneMediator)の子アクターは必ず団長(GgafGroupHead)になっています。<BR>
 * さらに団長の下に普通のアクターが居ます。<BR>
 * 仲介者へのメソッド実行は、その配下全ての団長＋アクターへの指示となります。<BR>
 * 団長(GgafGroupHead)の解説もあわせて参照して下さい。
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafSceneMediator : public GgafActor {

private:
    /** 現在の所属シーン */
    GgafScene* _pScene_platform;

private:
    /**
     * 使用不可 .
     */
    GgafSceneMediator* extract() override {
        throwGgafCriticalException("GgafSceneMediator に extract() は実行できません。name="<<getName());
        return (GgafSceneMediator*)nullptr;
    }

    /**
     * 所属シーンを設定する。.
     */
    void setPlatformScene(GgafScene* prm_pScene_platform) {
        _pScene_platform = prm_pScene_platform;
    }

public:
    GgafSceneMediator(GgafScene* prm_pScene_platform);

    /**
     * 初期処理<BR>
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    void processSettlementBehavior() override {
    }

    void processPreJudgement() override {
    }

    void processJudgement() override {
    }

    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }


    void processFinal() override {
    }


    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void throwEventUpperTree(hashval prm_no, void* prm_pSource) override;
    void throwEventUpperTree(hashval prm_no) override {
        throwEventUpperTree(prm_no, this);
    }
    /**
     * 当たり判定不要のため常にfalseを返す .
     * @param prm_pOtherActor
     * @return false
     */
    bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    void onHit(const GgafActor* prm_pOtherActor) override {
    }

    void remove();

    /**
     * 所属しているシーンを取得。 .
     * @return	GgafScene*	所属しているシーン
     */
    virtual GgafScene* getPlatformScene() {
        return _pScene_platform;
    }

    /**
     * グループとして引数のアクターを子アクターに追加します .
     * これは自動でGgafGroupHeadオブジェクトが間に挿入されます。<BR>
     * したがってグループ種別と共に登録が必要です。<BR>
     * 種別とは、内部で生成される GgafGroupHead名 にも使用されます。<BR>
     * GgafGroupHeadオブジェクト は初回種別登録時だけ生成され、２回目以降の同一種別登録は、<BR>
     * 既存の GgafGroupHeadオブジェクトの子に追加されます。<BR>
     * <pre>
     * ＜使用例１＞
     *
     *  appendGroupChild(KIND_XXX, pActor);
     *
     *  とした場合、階層構造は次のようになる。
     *
     *  this
     *    |
     *    +- pObject(GgafGroupHead[KIND_XXX])
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
     *    +- pObject(GgafGroupHead[KIND_AAA]) -- pObject(GgafGroupHead[KIND_BBB])
     *         |                                    |
     *         +- pActor01 -- pActor03              + pActor02
     * </pre>
     * 補足：引数の prm_pMainActor 以下全てのアクターに関して、
     *       ・所属シーンメンバ (_pScene_platform)
     *       ・仲介者アクターメンバ(_pSceneMediator)
     *       ・団長アクターメンバ(_pGroupHead) ※但し下位に他の団長がいた場合はそこまで
     *       の更新を行います。
     * @param   prm_kind    種別名（＝GgafGroupHead名）
     * @param   prm_pMainActor   登録するアクター
     */
    GgafGroupHead* appendGroupChild(kind_t prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * 単独GgafActor、或いはGgafDestructActorが単独親となるGgafActor連続体を<BR>
     * 種別は引数子アクターのステータス(getStatus())の項目 'STAT_DEFAULT_ACTOR_KIND' の値が、種別として
     * 上書きコピーされる。
     * 本関数はの部的処理は prm_pActor を GgafGroupHead の子アクターとしているだけである。<BR>
     * @param   prm_pMainActor   登録するアクター
     */
    GgafGroupHead* appendGroupChild(GgafMainActor* prm_pMainActor);

    /**
     * 子の団長アクターを取得、無ければnullptrを帰す
     * @param prm_kind
     * @return
     */
    GgafGroupHead* searchChildGroupHead(kind_t prm_kind);

    void updateActiveInTheTree() override;

    /**
     * 神に謁見 .
     * @return    呼ばれて出てきた神
     */
    GgafGod* askGod();

    /**
     * 配下ツリーアクターから、引数の名前を持つアクターを探す .
     * 引数は、アクター名を GgafUtil::easy_hash(const char* str) でHASH値に変換した値を渡す。
     * @param prm_name_hash アクター名HASH値
     * @return 最初に発見したアクター／発見できない場合は nullptr
     */
    GgafActor* search(hashval prm_name_hash);

    virtual ~GgafSceneMediator();
};

}
#endif /**GGAFSCENEMEDIATOR_H_*/
