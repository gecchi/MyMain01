#ifndef GGAFGROUPHEAD_H_
#define GGAFGROUPHEAD_H_
namespace GgafCore {

/**
 * 団長(GgafGroupHead)クラス .
 * とある意味合いで纏ったアクター達のツリー頂点に位置するアクターです。<BR>
 * いわゆる『種別』を意味付ける役割を持ったアクターで、具象なアクターではありません。<BR>
 * 団長配下の全てのアクターの『種別』は、団長の『種別』と一致する。という仕組みになっています。<BR>
 * 『種別』とは、当たり判定時の [自機の弾]対[敵本体] の [] の中身の事を指します。（分類と表現すべきなのかもしれません）<BR>
 * 団長は配下のアクターが消滅すると、次フレームに自身も寂しくなって自殺します。部下を持たない上役は無意味です！<BR>
 * 監督(GgafDirector)の直下のサブアクターは、全て必ずこの団長になっています。<BR>
 * また、団長配下のアクターに、さらに団長が存在することも可能です。<BR>
 * 但し団長の直接配下に団長は置けません。これは、団長の配下には少なくとも一人は普通のアクターが存在しなければいけないという仕組み上の問題です。<BR>
 * 複数の団長を経た末端のアクターの種別は、直近の団長の種別が優先されます。<BR>
 * ＜補足：団長クラス(GgafGroupHead)のオブジェクトイメージ図＞<BR>
 * <PRE>
 *         ・・・⇔ GgafScene ⇔ GgafScene ⇔・・・
 *                   ｜
 *                   ↓メンバー
 *           GgafDirector  （←1つのSceneに必ず１つのDirector）
 *               ｜
 *               ｜getSubFirst()
 *               ↓
 *     GgafGroupHead ⇔ GgafGroupHead ⇔ GgafGroupHead ⇔
 *           ｜                ｜                ｜
 *           ｜getSubFirst()   ｜                ｜
 *           ↓                ↓                ↓
 *     キャラのアクター達  キャラのアクター達  キャラのアクター
 * </PRE>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafGroupHead : public GgafActor {

public:
    /** [r]監督 */
    GgafDirector* _pDirector;
    /** [r/w]本グループの種別 */
    actorkind _kind;

    GgafGroupHead(actorkind prm_kind, GgafStatus* prm_pStat = NULL);

    /**
     * 初期処理 .
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    /**
     * 毎フレームのGgafGroupHead判定処理 .
     * サブが無ければ自動的に死亡する処理になっている。
     */
    void processJudgement() override {
        if (getSubFirst() == NULL) {
            //団長が居なければ監督も不要、さようなら。
            sayonara();
        }
    }

    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
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
     * 監督(GgafDirector)を取得 .
     * @return 自身が管理されている監督
     */
    GgafDirector* getSceneDirector();

    /**
     * 監督(GgafDirector)を設定 .
     * @param prm_pDirector 監督
     */
    void setSceneDirector(GgafDirector* prm_pDirector);

    /**
     * 神に謁見 .
     * @return	呼ばれて出てきた神
     */
    GgafGod* askGod();

    virtual void updateActiveInTheTree() override;

    virtual ~GgafGroupHead();
};

}
#endif /*GGAFGROUPHEADACTOR_H_*/
