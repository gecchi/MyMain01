#ifndef WALLAABEFFECTACTOR_H_
#define WALLAABEFFECTACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/WallAABActor.h"


namespace VioletVreath  {


/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class WallAABTestActor : public GgafLib::WallAABActor {
public:
    WallAABTestActor(const char* prm_name);

    void onCreateModel() override;

    bool isOutOfSpacetime() const override;

    virtual ~WallAABTestActor() {}
};

}
#endif /*WALLAABEFFECTACTOR_H_*/
