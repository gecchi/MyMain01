#ifndef GGAFLORDACTOR_H_
#define GGAFLORDACTOR_H_
namespace GgafCore {

/**
 * 管理者クラス .
 * 団長(GgafHeadActor)の親階層のアクターで、団長を管理します。<BR>
 * また、シーンクラスとの橋渡しを行う特別なアクターでもあります。<BR>
 * シーンクラスと管理者は普通のhasAの関係です。（管理者と団長は階層関係になっています）<BR>
 * 全てのシーン(GgafSceaneオブジェクト)に必ず１人つ管理者のインタンスがあります。<BR>
 * 管理者は、必ずアクター達ツリーの最も頂点に位置します。<BR>
 * 管理者(GgafLordActor)のサブアクターは必ず団長(GgafHeadActor)になっています。<BR>
 * 団長(GgafHeadActor)の解説もあわせて参照して下さい。
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafLordActor : public GgafActor {
public:
    GgafLordActor(GgafScene* prm_pScene_Platform);

    /**
     * 初期処理<BR>
     */
    void initialize() {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processBehavior() {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processJudgement() {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processDrawPrior() {
    }
    /**
     * ＜OverRide です＞<BR>
     */
    void processDrawMain() {
    }
    /**
     * ＜OverRide です＞<BR>
     */
    void processDrawTerminate() {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processHappen(int prm_no) {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processFinal() {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
        return false;
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processOnHit(GgafActor* prm_pActor_Opponent) {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void remove();

    /**
     * 単独GgafActor、或いはGgafDummyActorが単独親となるGgafActor連続体を<BR>
     * 種別と共に登録する。
     * 種別とは、内部で生成される GgafHeadActor名 になる。<BR>
     * GgafHeadActor は初回種別登録時だけ生成される。２回目以降の同一種別登録は、<BR>
     * 既存の GgafHeadActor が使用される。<BR>
     * 本関数はの部的処理は prm_pActor を GgafHeadActor の子アクターとしているだけである。<BR>
     * @param   prm_kind    種別名（＝GgafHeadActor名）
     * @param   prm_pMainActor   登録するアクター
     */
    void accept(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * 単独GgafActor、或いはGgafDummyActorが単独親となるGgafActor連続体を<BR>
     * 種別は0(無し)で登録される
     * 本関数はの部的処理は prm_pActor を GgafHeadActor の子アクターとしているだけである。<BR>
     * @param   prm_pMainActor   登録するアクター
     */
    void accept(GgafMainActor* prm_pMainActor);

    bool hasSubHeadActor(actorkind prm_kind);
    GgafHeadActor* getSubHeadActor(actorkind prm_kind);

    /**
     * 直属のGgafHeadActorを取得する。<BR>
     * @param   prm_kind    種別("*"による省略可能)
     * @param   prm_pActor   登録するアクター
     */
    //    virtual GgafHeadActor* getHeadActor(std::string prm_kind);


    /**
     * 神に謁見 .
     * @return	呼ばれて出てきた神
     */
    virtual GgafGod* askGod();

    virtual ~GgafLordActor();
};

}
#endif /**GGAFLORDACTOR_H_*/
