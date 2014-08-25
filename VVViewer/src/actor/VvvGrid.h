#ifndef VVVGRID_H_
#define VVVGRID_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VVViewer {

/**
 * グリッド .
 * @version 1.00
 * @since 2012/06/26
 * @author Masatoshi Tsuge
 */
class VvvGrid : public GgafLib::DefaultSpriteActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    VvvGrid(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VvvGrid();
};

}
#endif /*VVVGRID_H_*/

