#ifndef VVWORLD_H_
#define VVWORLD_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "scene/VvSpacetime.h"
#include "jp/ggaf/core/util/GgafLinearTreeRounder.hpp"
#include "jp/ggaf/lib/util/Quantity.hpp"
#include "jp/ggaf/lib/util/VirtualButton.h"

namespace VioletVrain {

/**
 * 世界シーンの雛形 .
 * GgafLib::DefaultScene を継承してシーンクラスを作成して下さい。<BR>
 * 本サンプルでは「世界」シーンと名づけました。<BR>
 * processBehavior() をオーバーライドし、毎フレームの処理を記述します。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvWorld : public GgafLib::DefaultScene {

public:
    /** 入力受付 */
    GgafLib::VirtualButton vb_;

    TrialAndErrScene* pTrialAndErrScene_;

    GgafLib::QuadtreeRounder* pHitCheckRounder_;
    /**
     * コンストラクタ .
     * @param prm_name 名称
     */
    VvWorld(const char* prm_name);

    /**
     * 世界シーンの初期処理 .
     */
    void initialize() override;

    /**
     * 世界シーンの振る舞い処理 .
     */
    void processBehavior() override;

    void processJudgement() override;

    virtual ~VvWorld();
};

}

#endif /*VVWORLD_H_*/
