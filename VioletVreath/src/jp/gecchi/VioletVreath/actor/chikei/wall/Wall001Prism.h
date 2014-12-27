#ifndef WALL001PRISM_H_
#define WALL001PRISM_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/WallAAPrismActor.h"

namespace VioletVreath  {

/**
 * �ǃu���b�N(�v���Y���^)���̂P
 * @version 1.00
 * @since 2011/01/09
 * @author Masatoshi Tsuge
 */
class Wall001Prism : public GgafLib::WallAAPrismActor {
public:
    Wall001Prism(const char* prm_name);

    void onCreateModel() override;

    void processBehavior() override;

//    bool isOutOfUniverse() const override;

    virtual ~Wall001Prism() {}
};

}
#endif /*WALL001PRISM_H_*/
