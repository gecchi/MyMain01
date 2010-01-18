#ifndef GGAFUNIVERSE_H_
#define GGAFUNIVERSE_H_
namespace GgafCore {

/**
 * この世クラス .
 * 本プログラムで言う『この世』とは、全てのシーン(GgafSceneオブジェクト)の頂点に位置する特別なシーンです。<BR>
 * 神自らが new してくれます。本クラスが new されると、芋づる的にシーン(GgafScene)が new されます。<BR>
 * 少なくとも１つはこの世をnewしなければいけません。<BR>
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
     * フレーム毎の振る舞い<BR>
     */
    virtual void processBehavior() override {
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
     * 何かの処理<BR>
     * @param prm_no 何かを表す数値
     */
    virtual void processHappen(int prm_no) override {
    }

    /**
     * 最終処理<BR>
     */
    virtual void processFinal() override {
    }

    virtual ~GgafUniverse();
};

}
#endif /*GGAFUNIVERSE_H_*/
