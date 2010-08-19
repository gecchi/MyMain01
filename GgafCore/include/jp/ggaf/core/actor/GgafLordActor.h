#ifndef GGAFLORDACTOR_H_
#define GGAFLORDACTOR_H_
namespace GgafCore {

/**
 * 管理者クラス .
 * 団長(GgafGroupActor)の親階層のアクターで、団長達を管理します。<BR>
 * また、シーンクラスとの橋渡しを行う特別なアクターでもあります。<BR>
 * シーンクラスと管理者は普通のhasAの関係です。（管理者と団長は階層関係になっています）<BR>
 * 全てのシーン(GgafSceaneオブジェクト)に必ず１人つ管理者のインタンスがあります。<BR>
 * 管理者は、必ずアクター達ツリーの最も頂点に位置します。<BR>
 * 管理者(GgafLordActor)のサブアクターは必ず団長(GgafGroupActor)になっています。<BR>
 * 団長(GgafGroupActor)の解説もあわせて参照して下さい。
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafLordActor : public GgafActor {
public:
    GgafLordActor(GgafScene* prm_pScene_Platform);

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


    void catchEvent(int prm_no) override {
    }


    virtual void throwUpEvent(int prm_no) {
        GgafScene* s = getPlatformScene();
        if (s != NULL) {
            s->throwUpEvent(prm_no); //自分より上位は居ない。そこで所属シーンへ投げる
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
     * これは自動でGgafGroupActorオブジェクトが間に挿入されます。<BR>
     * したがってグループ種別と共に登録が必要です。<BR>
     * 種別とは、内部で生成される GgafGroupActor名 にも使用されます。<BR>
     * GgafGroupActorオブジェクト は初回種別登録時だけ生成され、２回目以降の同一種別登録は、<BR>
     * 既存の GgafGroupActorオブジェクトのサブに追加されます。<BR>
     * <pre>
     * ＜使用例１＞
     *
     *  addSubGroup(KIND_XXX, pActor);
     *
     *  とした場合、階層構造は次のようになる。
     *
     *  this
     *    |
     *    +- pObject(GgafGroupActor[KIND_XXX])
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
     *    +- pObject(GgafGroupActor[KIND_AAA]) -- pObject(GgafGroupActor[KIND_BBB])
     *         |                                    |
     *         +- pActor01 -- pActor03              + pActor02
     * </pre>
     * @param   prm_kind    種別名（＝GgafGroupActor名）
     * @param   prm_pMainActor   登録するアクター
     */
    GgafGroupActor* addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * 単独GgafActor、或いはGgafDummyActorが単独親となるGgafActor連続体を<BR>
     * 種別は0(無し)で登録される
     * 本関数はの部的処理は prm_pActor を GgafGroupActor の子アクターとしているだけである。<BR>
     * @param   prm_pMainActor   登録するアクター
     */
    GgafGroupActor* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * サブの団長アクターを取得、無ければNULLを帰す
     * @param prm_kind
     * @return
     */
    GgafGroupActor* getSubGroupActor(actorkind prm_kind);


    /**
     * 神に謁見 .
     * @return	呼ばれて出てきた神
     */
    GgafGod* askGod();

    virtual ~GgafLordActor();
};

}
#endif /**GGAFLORDACTOR_H_*/
