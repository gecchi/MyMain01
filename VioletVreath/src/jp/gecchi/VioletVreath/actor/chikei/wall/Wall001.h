#ifndef WALL001_H_
#define WALL001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/WallAABActor.h"

namespace VioletVreath  {

/**
 * ƒíœ—\’è„
 * •ÇƒuƒƒbƒN‚»‚Ì‚P
 * @version 1.00
 * @since 2010/11/08
 * @author Masatoshi Tsuge
 */
class Wall001 : public GgafLib::WallAABActor {
public:
    Wall001(const char* prm_name);

    void onCreateModel() override;

    void processBehavior() override;
//    bool isOutOfSpacetime() const override;

    virtual ~Wall001() {}
};

}
#endif /*WALL001_H_*/
