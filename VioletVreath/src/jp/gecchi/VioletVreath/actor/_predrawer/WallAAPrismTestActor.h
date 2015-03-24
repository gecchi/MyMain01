#ifndef WALLAAPRISMEFFECTACTOR_H_
#define WALLAAPRISMEFFECTACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/WallAAPrismActor.h"


namespace VioletVreath  {


/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class WallAAPrismTestActor : public GgafLib::WallAAPrismActor {
public:
    WallAAPrismTestActor(const char* prm_name);

    void onCreateModel() override;

    bool isOutOfSpacetime() const override;

    virtual ~WallAAPrismTestActor() {}
};

}
#endif /*WALLAAPRISMEFFECTACTOR_H_*/
