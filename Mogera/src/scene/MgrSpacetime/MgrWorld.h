#ifndef MGRWORLD_H_
#define MGRWORLD_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "scene/MgrSpacetime.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

namespace Mogera {



/**
 * 世界シーンの雛形 .
 * GgafLib::DefaultScene を継承してシーンクラスを作成して下さい。<BR>
 * 本サンプルでは「世界」シーンと名づけました。<BR>
 * processBehavior() をオーバーライドし、毎フレームの処理を記述します。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrWorld : public GgafLib::DefaultScene {

public:

//    GgafLib::OctreeRounder* pHitCheckRounder_;
//    GgafLib::QuadtreeRounder_b* pHitCheckRounder_b_;

    DefaultScene* pTestScene_;
    DefaultScene* pTrialAndErrScene_;

    PointerTest* pPointerTest_;


    /**
     * コンストラクタ .
     * @param prm_name 名称
     */
    MgrWorld(const char* prm_name);

    /**
     * 世界シーンの初期処理 .
     */
    void initialize() override;

    /**
     * 世界シーンの振る舞い処理 .
     */
    void processBehavior() override;

    void processJudgement() override;

    virtual ~MgrWorld();
};

}

#endif /*MGRWORLD_H_*/
