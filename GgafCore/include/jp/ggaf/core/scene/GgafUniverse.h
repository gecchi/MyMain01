#ifndef GGAFCORE_GGAFUNIVERSE_H_
#define GGAFCORE_GGAFUNIVERSE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/scene/GgafMainScene.h"

#include "jp/ggaf/core/GgafGod.h"

namespace GgafCore {

/**
 * この世クラス .
 * 本プログラムでの『この世』とは、全てのシーン階層構造の頂点に位置する特別なシーンです。<BR>
 * 神(GgafGod)自らが new してくれます。本クラスが new されると、芋づる的に配下シーン(GgafScene)が new されます。<BR>
 * アプリケーションで少なくとも１つはこの世をnewしなければいけません。<BR>
 * 『この世』 へのメソッド実行は、全てのシーンとアクターに影響します。<BR>
 * @version 1.00
 * @since 2009/07/23
 * @author Masatoshi Tsuge
 */
class GgafUniverse : public GgafMainScene {
    friend class GgafGod;
    friend class GgafScene;

public:
    GgafUniverse(const char* prm_name);

    /**
     * 初期処理<BR>
     */
    void initialize() override {
    }

    /**
     * フレーム毎の振る舞い処理<BR>
     */
    virtual void processBehavior() override {
    }

    /**
     * フレーム毎の振る舞いの事後処理<BR>
     */
    virtual void processSettlementBehavior() override {
    }

    /**
     * フレーム毎の判定処理<BR>
     */
    virtual void processJudgement() override {
    }

    /**
     * フレーム毎の描画事前処理<BR>
     */
    virtual void processPreDraw() override {
    }

    /**
     * フレーム毎の描画処理<BR>
     */
    virtual void draw() override {
    }

    /**
     * フレーム毎の描画処理<BR>
     */
    virtual void processDraw() override {
    }

    /**
     * フレーム毎の描画事後処理<BR>
     */
    virtual void processAfterDraw() override {
    }

    /**
     * 何かのイベント処理<BR>
     * @param prm_no イベント番号
     * @param prm_pSource イベント発生元
     */
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    /**
     * 最終処理<BR>
     */
    virtual void processFinal() override {
    }

    void updateActiveInTheTree() override;

    virtual ~GgafUniverse();
};

}
#endif /*GGAFCORE_GGAFUNIVERSE_H_*/
