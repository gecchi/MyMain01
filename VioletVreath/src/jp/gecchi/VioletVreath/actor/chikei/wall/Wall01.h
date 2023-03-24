#ifndef WALL01_H_
#define WALL01_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
//#include "jp/ggaf/lib/actor/wall/MassWallActor.h"
#include "jp/gecchi/VioletVreath/actor/VvChikeiActor.hpp"
#include "jp/ggaf/lib/actor/wall/CubeMapMassWallActor.h"

namespace VioletVreath  {

/**
 * ï«ÉuÉçÉbÉNÇªÇÃÇP
 * @version 1.00
 * @since 2010/11/08
 * @author Masatoshi Tsuge
 */
class Wall01 : public VvChikeiActor<GgafLib::CubeMapMassWallActor> {
//class Wall01 : public GgafLib::MassWallActor {
public:
    Wall01(const char* prm_name);

    void onCreateModel() override;
    void onActive() override;
    void processBehavior() override;
//    bool isOutOfSpacetime() const override;

    virtual ~Wall01() {}
};

}
#endif /*WALL01_H_*/
