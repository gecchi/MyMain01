#ifndef GGAFGROUPACTOR_H_
#define GGAFGROUPACTOR_H_
namespace GgafCore {

/**
 * 団長クラス .
 * とある纏ったアクター達の、階層ツリー頂点のアクターです。<BR>
 * 頂点と言っても、もうひとつ1つ上位階層には、管理者(GgafLoadActor）がいます。アクターの役職的にNo.2なポジションです。<BR>
 * キャラクタを表現するアクターを纏めてグループにし、配下のアクターの種別を表現しているアクターにもなります。<BR>
 * 種別とは、当たり判定時の [自機の弾]ｘ[敵本体] 等の [] の中身を表現しているような分類を指します。<BR>
 * 団長は配下のアクターが消滅すると、次のフレームに自身も自殺します。部下を持たない上司は不要というわけです。<BR>
 * 管理者のサブアクターは、全て必ずこの団長になっています。<BR>
 * また、団長配下に団長が存在してはいけないことになっています。<BR>
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
    void processJudgement();

    /**
     * ＜OverRide です＞<BR>
     */
    void processPreDraw() {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processDraw() {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    void processAfterDraw() {
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
