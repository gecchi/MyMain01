#ifndef GGAF_CORE_SCENECHIEF_H_
#define GGAF_CORE_SCENECHIEF_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * シーンのチーフクラス .
 * シーンクラスとアクターの橋渡しを行う特別なアクター。<BR>
 * シーンクラスとシーンチーフは普通のhasAの関係です。（チーフと団長は階層関係になっています）<BR>
 * 全てのシーン(Sceaneオブジェクト)に必ず１人シーンチーフが居ます。<BR>
 * チーフは、アクター達ツリーの最も頂点に位置します。<BR>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class SceneChief : public Actor {

private:
    /** 現在の所属シーン */
    Scene* _pScene_platform;

private:
    /**
     * 使用不可 .
     */
    SceneChief* extract() override {
        throwCriticalException("SceneChief に extract() は実行できません。name="<<getName());
        return (SceneChief*)nullptr;
    }

    /**
     * 所属シーンを設定する。.
     */
    void setPlatformScene(Scene* prm_pScene_platform) {
        _pScene_platform = prm_pScene_platform;
    }

public:
    SceneChief(Scene* prm_pScene_platform);

    /**
     * 初期処理<BR>
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    void processSettlementBehavior() override {
    }

    void processJudgement() override {
    }
    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }


    void processFinal() override {
    }


    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void throwEventUpperTree(eventval prm_event_val, void* prm_pSource) override;
    void throwEventUpperTree(eventval prm_event_val) override {
        throwEventUpperTree(prm_event_val, this);
    }
    void onHit(const Checker* prm_pOtherChecker, const Actor* prm_pOtherActor) override {
    }

    void remove();

    /**
     * 所属しているシーンを取得。 .
     * @return	Scene*	所属しているシーン
     */
    virtual Scene* getPlatformScene() {
        return _pScene_platform;
    }


    void updateActiveInTheTree() override;

    /**
     * 管理者に謁見 .
     * @return    呼ばれて出てきた管理者
     */
    Caretaker* askCaretaker();

    /**
     * 配下ツリーアクターから、引数の名前を持つアクターを探す .
     * 引数は、アクター名を Util::easy_hash(const char* str) でHASH値に変換した値を渡す。
     * @param prm_name_hash アクター名HASH値
     * @return 最初に発見したアクター／発見できない場合は nullptr
     */
    Actor* search(hashval prm_name_hash);

    virtual ~SceneChief();
};

}
#endif /**GGAF_CORE_SCENECHIEF_H_*/
