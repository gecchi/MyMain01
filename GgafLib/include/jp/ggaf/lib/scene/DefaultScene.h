#ifndef GGAF_LIB_DEFAULTSCENE_H_
#define GGAF_LIB_DEFAULTSCENE_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/scene/Scene.h"

#include "jp/ggaf/lib/util/ScenePhase.h"

namespace GgafLib {

/**
 * シーンの具象クラス .
 * GgafDx::Scene を継承し、空実装した具象シーンです。
 * @version 1.00
 * @since 2007/12/06
 * @author Masatoshi Tsuge
 */
class DefaultScene : public GgafDx::Scene {

public:
    /** 特色関数用引数1 */
    velo _feature_p1;
    /** [r/w]特色関数へのポインタ */
    void (*_pFuncFeature)(GgafCore::Object*, void*, void*, void*);

public:
    DefaultScene(const char* prm_name, GgafCore::SceneMediator* prm_pSceneMediator = nullptr);

    virtual ScenePhase* createAnotherPhase() override; //共変戻り値

    virtual ScenePhase* getPhase() const override; //共変戻り値

    virtual void initialize() override {
    }

    /**
     * シーンをリセットし、再利用可能にする .
     * 下位で実装してください。
     */
    virtual void onReset() override {
    }

    virtual void processBehavior() override {
    }
    /**
     * 特色処理の追加 .
     */
    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override {
    }
    virtual void processDraw() override {
    }
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }


public:
    /**
     * 特色関数を設定する。
     * 設定された特色関数を配下ツリーシーンの全アクターに実行を行う。<BR>
     * 第１引数には、対象アクター、第２引数には、特色関数用引数１(_feature_p1へのポインタ)が渡される。<BR>
     * シーンが WallSceneの場合に限り、標準で WallScene::scrollX(GgafCore::Object*, void*, void*, void*) が設定されている。<BR>
     * @param prm_pFuncFeature 引数が(GgafCore::Object*, void*, void*, void*) となる関数ポインタ
     */
    void setFeatureFunction(void (*prm_pFuncFeature)(GgafCore::Object*, void*, void*, void*)) {
        _pFuncFeature = prm_pFuncFeature;
    }

    void setFeatureParam1(velo prm_feature_p1) {
        _feature_p1 = prm_feature_p1;
    }

    velo getFeatureParam1() const {
        return _feature_p1;
    }

    void addFeatureParam1(acce prm_acce) {
        _feature_p1 += prm_acce;
    }
    /**
     * 最も直近の特色シーンを探して取得。 .
     * 検索範囲は 自シーン＋親シーン。
     * 特色関数ポインタ _pFuncFeature が nullptr でなければ、特色と判断。
     * @return 直近の特色シーン、無ければ nullptr
     */
    DefaultScene* getNearestFeatureScene();

    /**
     * 最も直近の WallScene を探して取得。 .
     * 検索範囲は 自シーン＋親シーン。
     * WallScene はX軸の負の方向にスクロールする特色が将来保証されている。
     * _pFuncFeature が nullptr であろうとなかろうと、関係はなく、WallScene ならばそれを返す。
     * @return 直近のWallScene
     */
    WallScene* getNearestWallScene();

    virtual ~DefaultScene();
};

}
#endif /*GGAF_LIB_DEFAULTSCENE_H_*/
