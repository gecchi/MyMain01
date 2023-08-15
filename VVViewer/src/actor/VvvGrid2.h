#ifndef VVVGRID2_H_
#define VVVGRID2_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VVViewer {

/**
 * グリッド .
 * @version 1.00
 * @since 2012/06/26
 * @author Masatoshi Tsuge
 */
class VvvGrid2 : public GgafLib::DefaultBoardActor {
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    VvvGrid2(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VvvGrid2();
};

}
#endif /*VVVGRID2_H_*/

