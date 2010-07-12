#ifndef GGAFGROUPACTOR_H_
#define GGAFGROUPACTOR_H_
namespace GgafCore {

/**
 * 団長(GgafGroupActor)クラス .
 * とある意味合いで纏ったアクター達の、階層ツリー頂点のアクターで種別を表現する役割を持ったアクターです。<BR>
 * 頂点と言っても、必ず管理者(GgafLordActor）の配下にいます。アクターの役職的にNo.2なポジションです。<BR>
 * 団長は主にアクターの種別を表現しているアクターで、当たり判定等に利用されます。<BR>
 * 種別とは、当たり判定時の [自機の弾]ｘ[敵本体] 等の [] の中身を表現しているような分類表現を意味します。<BR>
 * 団長は配下のアクターが消滅すると、次のフレームに自身も寂しくなって自殺します。部下を持たない上役は資源（メモリ）の無駄使いです！<BR>
 * 管理者(GgafLordActor)の直下のサブアクターは、全て必ずこの団長になっています。<BR>
 * また、団長配下のアクターに、さらに団長が存在することも可能です。<BR>
 * 但し団長の直接配下に団長は置けません。これは、団長の配下には少なくとも一人は普通のアクターが存在しなければいけないという仕組み上の問題です。<BR>
 * 複数の団長を経た末端のアクターの種別は、直近の団長の種別が優先されます。<BR>
 * ＜補足：団長クラス(GgafGroupActor)のオブジェクトイメージ図＞<BR>
 * <PRE>
 * 　　　　・・・⇔ GgafScene ⇔ GgafScene ⇔・・・
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
    /** [r]管理者 */
    GgafLordActor* _pLordActor;
    /** [r/w]種別 */
    actorkind _kind;

    GgafGroupActor(actorkind prm_kind);

    /**
     * 初期処理 .
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    /**
     * 毎フレームのGgafGroupActor判定処理 .
     * サブが無ければ自動的に死亡する処理になっている。
     */
    void processJudgement() override {
        //サブが無ければ自殺
        if (getSubFirst() == NULL) {
            end();
        }
    }

    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }

    void processHappen(int prm_no) override {
    }

    void processFinal() override {
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

    /**
     * 管理者(GgafLordActor)を取得 .
     * @return 自身が管理されている管理者
     */
    GgafLordActor* getLordActor();

    /**
     * 管理者(GgafLordActor)を設定 .
     * @param prm_pLordActor 管理者
     */
    void setLordActor(GgafLordActor* prm_pLordActor);

    /**
     * 神に謁見 .
     * @return	呼ばれて出てきた神
     */
    GgafGod* askGod();

    virtual ~GgafGroupActor();
};

}
#endif /*GGAFGROUPACTOR_H_*/
