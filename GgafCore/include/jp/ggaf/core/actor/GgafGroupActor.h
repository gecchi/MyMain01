#ifndef GGAFGROUPACTOR_H_
#define GGAFGROUPACTOR_H_
namespace GgafCore {

/**
 * 団長(GgafGroupActor)クラス .
 * とある種別で纏ったアクター達の、階層ツリー頂点のアクターで種別を表現する役割を持ったアクターです。<BR>
 * 頂点と言っても、もうひとつ1つ上位階層には、管理者(GgafLoadActor）がいます。アクターの役職的にNo.2なポジションです。<BR>
 * 配下のアクターの種別を表現しているアクターで、当たり判定等に利用されます。<BR>
 * 種別とは、当たり判定時の [自機の弾]ｘ[敵本体] 等の [] の中身を表現しているような分類表現を意味します。<BR>
 * 団長は配下のアクターが消滅すると、次のフレームに自身も寂しくなって自殺します。部下を持たない上役は資源の無駄使いです！<BR>
 * 管理者(GgafLordActor)のサブアクターは、全て必ずこの団長になっています。<BR>
 * また、団長配下のアクターに、さらに団長が存在することも可能です。（但し団長の直接配下に団長は置けません）
 * この場合、末端のアクター種別は、直近の団長の種別が優先されます。<BR>
 * ＜補足：団長クラス(GgafGroupActor)のオブジェクトイメージ図＞<BR>
 * <PRE STYLE="font-size:18px">
 * 　　　　･･･⇔ GgafScene ⇔ GgafScene ⇔･･･
 * 　　　　　　　　　｜
 * 　　　　　　　　　↓メンバー
 * 　　　　　GgafLordActor　（←1つのSceneに必ず１つのLordActor）
 * 　　　　　　　｜
 * 　　　　　　　｜getSubFirst()
 * 　　　　　　　↓
 * 　　GgafGroupActor ⇔ GgafGroupActor ⇔ GgafGroupActor ⇔
 * 　　　　　｜　　　　　　　　　｜　　　　　　　　　｜
 * 　　　　　｜getSubFirst()　　 ｜　　　　　　　　　｜
 * 　　　　　↓　　　　　　　　　↓　　　　　　　　　↓
 * 　　キャラのアクター達　　キャラのアクター達　　キャラのアクター
 * </PRE>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafGroupActor : public GgafActor {

public:
    /** 管理者 */
    GgafLordActor* _pLordActor;

    actorkind _kind;

    GgafGroupActor(actorkind prm_kind);

    /**
     * 初期処理<BR>
     */
    void initialize() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processBehavior() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processJudgement() override;

    /**
     * ＜OverRide です＞<BR>
     */
    void processPreDraw() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processDraw() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processAfterDraw() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processHappen(int prm_no) override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processFinal() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    bool processBumpChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processOnHit(GgafActor* prm_pOtherActor) override {
    }

    GgafLordActor* getLordActor();

	void setLordActor(GgafLordActor* prm_pLordActor);



    /**
     * 神に謁見 .
     * @return	呼ばれて出てきた神
     */
    virtual GgafGod* askGod();

    virtual ~GgafGroupActor();
};

}
#endif /*GGAFGROUPACTOR_H_*/
