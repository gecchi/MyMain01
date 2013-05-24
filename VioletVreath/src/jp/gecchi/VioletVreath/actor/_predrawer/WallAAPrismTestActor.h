#ifndef WALLAAPRISMEFFECTACTOR_H_
#define WALLAAPRISMEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/WallAAPrismActor.h"


namespace VioletVreath  {


/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class WallAAPrismTestActor : public GgafLib::WallAAPrismActor {
public:
    WallAAPrismTestActor(const char* prm_name);

    void onCreateModel() override;

    bool isOutOfUniverse() override;

    virtual ~WallAAPrismTestActor() {}
};

}
#endif /*WALLAAPRISMEFFECTACTOR_H_*/
