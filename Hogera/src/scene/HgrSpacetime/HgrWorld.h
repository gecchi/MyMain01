#ifndef HGRWORLD_H_
#define HGRWORLD_H_
#include "Hogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "scene/HgrSpacetime.h"
#include "jp/ggaf/core/util/lineartree/LinearTreeRounder.hpp"
#include "jp/ggaf/lib/util/Quantity.hpp"
#include "jp/ggaf/lib/util/VirtualButton.h"

namespace Hogera {

/**
 * 世界シーンの雛形 .
 * GgafLib::DefaultScene を継承してシーンクラスを作成して下さい。<BR>
 * 本サンプルでは「世界」シーンと名づけました。<BR>
 * processBehavior() をオーバーライドし、毎フレームの処理を記述します。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class HgrWorld : public GgafLib::DefaultScene {

public:
    /** 入力受付 */
    GgafLib::VirtualButton vb_;

    TrialAndErrScene* pTrialAndErrScene_;

//    GgafLib::QuadtreeRounder* pHitCheckRounder_;
    /**
     * コンストラクタ .
     * @param prm_name 名称
     */
    HgrWorld(const char* prm_name);

    /**
     * 世界シーンの初期処理 .
     */
    void initialize() override;

    /**
     * 世界シーンの振る舞い処理 .
     */
    void processBehavior() override;

    void processJudgement() override;

    virtual ~HgrWorld();
};

}

#endif /*HGRWORLD_H_*/
