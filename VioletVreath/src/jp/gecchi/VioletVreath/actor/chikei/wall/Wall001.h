#ifndef WALL001_H_
#define WALL001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/WallAABActor.h"

namespace VioletVreath  {

/**
 * 壁ブロックその１
 * @version 1.00
 * @since 2010/11/08
 * @author Masatoshi Tsuge
 */
class Wall001 : public GgafLib::WallAABActor {
public:
    Wall001(const char* prm_name);

    void onCreateModel() override;

    void processBehavior() override;
//    bool isOutOfUniverse() override;

    virtual ~Wall001() {}
};

}
#endif /*WALL001_H_*/
