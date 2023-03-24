#ifndef STAGE01PARTCLIMAX_H_
#define STAGE01PARTCLIMAX_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "Stage01Part.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ステージデバッグ－最後 .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class Stage01PartClimax : public Stage01Part<GgafLib::DefaultScene> {


public:
    bool waiting_;

    EnemyStraea* pBoss_;

public:
    Stage01PartClimax(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage01PartClimax();
};

}
#endif /*STAGE01PARTCLIMAX_H_*/
