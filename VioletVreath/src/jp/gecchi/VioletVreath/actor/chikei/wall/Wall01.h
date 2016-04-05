#ifndef WALL01_H_
#define WALL01_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/wall/CubeMapMassWallActor.h"

namespace VioletVreath  {

/**
 * ï«ÉuÉçÉbÉNÇªÇÃÇP
 * @version 1.00
 * @since 2010/11/08
 * @author Masatoshi Tsuge
 */
class Wall01 : public GgafLib::CubeMapMassWallActor {
public:
    Wall01(const char* prm_name);

    void onCreateModel() override;

    void processBehavior() override;
//    bool isOutOfSpacetime() const override;

    virtual ~Wall01() {}
};

}
#endif /*WALL01_H_*/
