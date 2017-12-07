#ifndef SMPWORLDMEDIATOR_H_
#define SMPWORLDMEDIATOR_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"

namespace SimpleSample {

/**
 * 仲介者 .
 * @version 1.00
 * @since 2017/12/07
 * @author Masatoshi Tsuge
 */
class SmpWorldMediator : public GgafLib::DefaultSceneMediator {

public:
    /** テストキャラ */
    SmpActor* pActor_;

    /**
     * コンストラクタ
     * @param prm_pSmpWorld
     * @return
     */
    SmpWorldMediator(GgafLib::DefaultScene* prm_pSmpWorld);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~SmpWorldMediator();
};

}
#endif /*SMPWORLDMEDIATOR_H_*/

