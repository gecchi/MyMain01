#ifndef PREDRAWSCENE_H_
#define PREDRAWSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * 事前表示シーン .
 * ゲームの前に各モデルのキャラを１キャラずつ出力し、
 * モデルクラスをプリロードしておく。
 * @version 1.00
 * @since 2010/04/20
 * @author Masatoshi Tsuge
 */
class PreDrawScene : public VvScene<GgafLib::DefaultScene> {

public:
    enum {
        PHASE_READY ,
        PHASE_DISP ,
        PHASE_CALM_DOWN ,
        PHASE_WAIT ,
        PHASE_BANPEI,
    };

    int order_id_begin_;
    int order_id_end_;
    int _id_;

public:
    PreDrawScene(const char* prm_name);
    void onReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~PreDrawScene();
};

}
#endif /*PREDRAWSCENE_H_*/
