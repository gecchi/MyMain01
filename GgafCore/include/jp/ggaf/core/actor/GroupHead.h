#ifndef GGAF_CORE_GROUPHEAD_H_
#define GGAF_CORE_GROUPHEAD_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * 団長(GroupHead)クラス .
 * とある意味合いで纏ったアクター達のツリー頂点に位置するアクターです。<BR>
 * いわゆる『種別』を意味付ける役割を持ったアクターで、具象なアクターではありません。<BR>
 * 団長配下の全てのアクターの『種別』は、団長の『種別』と一致する。という仕組みになっています。<BR>
 * 『種別』とは、当たり判定時の [自機の弾]対[敵本体] の [] の中身の事を指します。（分類と表現すべきなのかもしれません）<BR>
 * 団長は配下のアクターが消滅すると、次フレームに自身も寂しくなって自殺します。部下を持たない上役は無意味です！<BR>
 * 仲介者(SceneMediator)の直下の子アクターは、全て必ずこの団長になっています。<BR>
 * また、団長配下のアクターに、さらに団長が存在することも可能です。<BR>
 * 但し団長の直接配下に団長は置けません。これは、団長の配下には少なくとも一人は普通のアクターが存在しなければいけないという仕組み上の問題です。<BR>
 * 複数の団長を経た末端のアクターの種別は、直近の団長の種別が優先されます。<BR>
 * ＜補足：団長クラス(GroupHead)のオブジェクトイメージ図＞<BR>
 * <PRE>
 *         ・・・⇔ Scene ⇔ Scene ⇔・・・
 *                   ｜
 *                   ↓メンバー
 *           SceneMediator  （←1つのSceneに必ず１つのMediator）
 *               ｜
 *               ｜getChildFirst()
 *               ↓
 *          GroupHead ⇔ GroupHead ⇔ GroupHead ⇔
 *           ｜                ｜                ｜
 *           ｜getChildFirst() ｜                ｜
 *           ↓                ↓                ↓
 *     キャラのアクター達  キャラのアクター達  キャラのアクター
 * </PRE>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GroupHead : public Actor {

public:
    /** [r]シーン仲介者 */
    SceneMediator* _pSceneMediator;
    /** [r/w]配下アクターグループの種別 */
    kind_t _kind;

public:
    GroupHead(kind_t prm_kind);

    /**
     * 配下アクターグループの種別を設定 .
     * @param prm_kind アクターグループの種別
     */
    void setKind(kind_t prm_kind);

    /**
     * 初期処理 .
     */
    void initialize() override {
    }

    void processBehavior() override {
    }
    void processPreJudgement() override {
    }
    /**
     * 毎フレームのGroupHead判定処理 .
     * 子が無ければ自動的に死亡する処理になっている。
     */
    void processJudgement() override {
        if (getChildFirst() == nullptr) {
            //団長が居なければシーン仲介者も不要、さようなら。
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
    bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
    }

    void onHit(const Actor* prm_pOtherActor) override {
    }

    /**
     * 自身が管理されているシーンの仲介者を取得 .
     * @return シーン仲介者
     */
    SceneMediator* getSceneMediator();

    /**
     * シーン仲介者(SceneMediator)を設定 .
     * @param prm_pSceneMediator 仲介者
     */
    void setSceneMediator(SceneMediator* prm_pSceneMediator);

    /**
     * 管理者に謁見 .
     * @return    呼ばれて出てきた管理者
     */
    Caretaker* askCaretaker();

    void updateActiveInTheTree() override;


    virtual ~GroupHead();
};

}
#endif /*GGAF_CORE_GROUPHEADACTOR_H_*/
