#ifndef GGAFDIRECTOR_H_
#define GGAFDIRECTOR_H_
namespace GgafCore {

/**
 * 監督クラス .
 * 団長(GgafGroupHead)の親階層のアクターで、団長達を管理します。<BR>
 * また、シーンクラスとの橋渡しを行う特別なアクターでもあります。<BR>
 * シーンクラスと監督は普通のhasAの関係です。（監督と団長は階層関係になっています）<BR>
 * 全てのシーン(GgafSceaneオブジェクト)に必ず１人つ監督のが居ます。<BR>
 * 監督は、必ずアクター達ツリーの最も頂点に位置します。<BR>
 * 監督(GgafDirector)のサブアクターは必ず団長(GgafGroupHead)になっています。<BR>
 * さらに団長の下に普通のアクターが居ます。<BR>
 * 監督へのメソッド実行は、その配下全ての団長＋アクターへの指示となります。<BR>
 * 団長(GgafGroupHead)の解説もあわせて参照して下さい。
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafDirector : public GgafActor {

private:

    /**
     * 使用不可 .
     */
    GgafDirector* extract() override {
        throwGgafCriticalException("GgafDirector に extract() は実行できません。name="<<getName());
    }

public:
    GgafDirector(GgafScene* prm_pScene_Platform);

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

    void throwEventToUpperTree(hashval prm_no, void* prm_pSource) override {
        GgafScene* s = getPlatformScene();
        if (s) {
            s->throwEventToUpperTree(prm_no, this); //自分より上位は居ない。そこで所属シーンへ投げる
        }
    }


    /**
     * 当たり判定不要のため常にfalseを返す .
     * @param prm_pOtherActor
     * @return false
     */
    bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    void onHit(GgafActor* prm_pOtherActor) override {
    }

    void remove();

    /**
     * グループとして引数のアクターをサブアクターに追加します .
     * これは自動でGgafGroupHeadオブジェクトが間に挿入されます。<BR>
     * したがってグループ種別と共に登録が必要です。<BR>
     * 種別とは、内部で生成される GgafGroupHead名 にも使用されます。<BR>
     * GgafGroupHeadオブジェクト は初回種別登録時だけ生成され、２回目以降の同一種別登録は、<BR>
     * 既存の GgafGroupHeadオブジェクトのサブに追加されます。<BR>
     * <pre>
     * ＜使用例１＞
     *
     *  addSubGroup(KIND_XXX, pActor);
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
     * addSubGroup(KIND_AAA, pActor01);
     * addSubGroup(KIND_BBB, pActor02);
     * addSubGroup(KIND_AAA, pActor03);
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
     *       ・所属シーンメンバ (_pScene_Platform)
     *       ・監督アクターメンバ(_pDirector)
     *       ・団長アクターメンバ(_pGroupHead) ※但し下位に他の団長がいた場合はそこまで
     *       の更新を行います。
     * @param   prm_kind    種別名（＝GgafGroupHead名）
     * @param   prm_pMainActor   登録するアクター
     */
    GgafGroupHead* addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * 単独GgafActor、或いはGgafDummyActorが単独親となるGgafActor連続体を<BR>
     * 種別は引数子アクターのステータス(_pStatus)の項目 'STAT_DEFAULT_ACTOR_KIND' の値が、種別として
     * 上書きコピーされる。
     * 本関数はの部的処理は prm_pActor を GgafGroupHead の子アクターとしているだけである。<BR>
     * @param   prm_pMainActor   登録するアクター
     */
    GgafGroupHead* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * サブの団長アクターを取得、無ければNULLを帰す
     * @param prm_kind
     * @return
     */
    GgafGroupHead* searchSubGroupHead(actorkind prm_kind);



    /**
     * 神に謁見 .
     * @return	呼ばれて出てきた神
     */
    GgafGod* askGod();

    virtual ~GgafDirector();
};

}
#endif /**GGAFDIRECTOR_H_*/
