#ifndef GGAFLIB_DEFAULTSCENE_H_
#define GGAFLIB_DEFAULTSCENE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/scene/GgafDxScene.h"

#include "jp/ggaf/lib/util/SceneProgress.h"

namespace GgafLib {

/**
 * シーンの具象クラス .
 * GgafDxCore::GgafDxScene を継承し、空実装した具象シーンです。
 * @version 1.00
 * @since 2007/12/06
 * @author Masatoshi Tsuge
 */
class DefaultScene : public GgafDxCore::GgafDxScene {

public:
    /** [r]シーンイベント用のフレーム値の配列(※「シーンCreater.xls」マクロの生成PGに組み込まれる） */
    frame* _paFrame_NextEvent;
    /** [r]シーンのイベント数（_paFrame_NextEventの要素数）(※「シーンCreater.xls」マクロの生成PGに組み込まれる） */
    int _event_num;
    /** シーンの現在イベント(※「シーンCreater.xls」マクロの生成PGに組み込まれる） */
    int _cnt_event;

    /** スクロール速度 */
    velo _scroll_speed;
    /** [r/w]スクロール関数へのポインタ */
    void (*_pFuncScrolling)(GgafCore::GgafObject*, void*, void*);

public:
    DefaultScene(const char* prm_name, GgafCore::GgafSceneMediator* prm_pSceneMediator = nullptr);

    virtual void useProgress(int prm_num = 10) override;

    virtual SceneProgress* createProgress(int prm_num = 10) override; //共変戻り値

    virtual SceneProgress* getProgress() const override; //共変戻り値

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
     * スクロール処理の追加 .
     */
    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override {
    }

    virtual void processDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }


public:

    /**
     * スクロール関数を設定する。
     * 設定されたスクロール関数を配下ツリーシーンの全アクターに実行を行う。<BR>
     * 第１引数には、対象アクター、第２引数には、スクロールスピード(_scroll_speedへのポインタ)が渡される。<BR>
     * シーンが WalledSceneの場合に限り、標準で WalledScene::scrollX(GgafObject*, void*, void*) が設定されている。<BR>
     * @param prm_pFuncScrolling 引数が(GgafObject*, void*, void*) となる関数ポインタ
     */
    void setScrollingFunction(void (*prm_pFuncScrolling)(GgafCore::GgafObject*, void*, void*)) {
        _pFuncScrolling = prm_pFuncScrolling;
    }

    void setScrollSpeed(velo prm_scroll_speed) {
        _scroll_speed = prm_scroll_speed;
    }

    velo getScrollSpeed() const {
        return _scroll_speed;
    }

    void addScrollSpeed(acce prm_acce) {
        _scroll_speed += prm_acce;
    }
    /**
     * 最も直近のスクロールしているシーンを探して取得。 .
     * 検索範囲は 自シーン＋親シーン。
     * スクロール関数ポインタ _pFuncScrolling が nullptr でなければ、スクロールしていると判断。
     * @return 直近のスクロールしているシーン、無ければ nullptr
     */
    DefaultScene* getNearestScrollingScene();

    /**
     * 最も直近の WallScene を探して取得。 .
     * 検索範囲は 自シーン＋親シーン。
     * WallScene はX軸の負の方向スクロールしていることが将来保証されている。
     * _pFuncScrolling が nullptr であろうとなかろうと、関係はなく、WallScene ならばそれを返す。
     * @return 直近のWallScene
     */
    WallScene* getNearestWallScene();

    virtual ~DefaultScene();
};

}
#endif /*GGAFLIB_DEFAULTSCENE_H_*/
