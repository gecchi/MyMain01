#ifndef GGAF_CORE_SPACETIME_H_
#define GGAF_CORE_SPACETIME_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/scene/MainScene.h"

#include "jp/ggaf/core/Caretaker.h"

namespace GgafCore {

/**
 * この世クラス .
 * 本プログラムでの『この世』とは、全てのシーン階層構造の頂点に位置する特別なシーンです。<BR>
 * 管理者(Caretaker)自らが new してくれます。本クラスが new されると、芋づる的に配下シーン(Scene)が new されます。<BR>
 * アプリケーションで少なくとも１つはこの世をnewしなければいけません。<BR>
 * 『この世』 へのメソッド実行は、全てのシーンとアクターに影響します。<BR>
 * @version 1.00
 * @since 2009/07/23
 * @author Masatoshi Tsuge
 */
class Spacetime : public MainScene {
    friend class Caretaker;
    friend class Scene;

public:
    Spacetime(const char* prm_name);

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
     * フレーム毎の当たり判定実行処理<BR>
     */
    virtual void processHitCheck() = 0;

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
     * @param prm_event_val イベント番号
     * @param prm_pSource イベント発生元
     */
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    /**
     * 最終処理<BR>
     */
    virtual void processFinal() override {
    }

    void updateActiveInTheTree() override;

    virtual ~Spacetime();
};

}
#endif /*GGAF_CORE_SPACETIME_H_*/
