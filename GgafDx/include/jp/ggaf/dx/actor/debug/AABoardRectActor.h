#ifndef GGAF_DX_AABOARDRECTACTOR_H_
#define GGAF_DX_AABOARDRECTACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/BoardActor.h"

namespace GgafDx {

/**
 * Board四角 .
 * Board四角を表示するためのアクターです。<BR>
 * @version 1.00
 * @since 2022/10/11
 * @author Masatoshi Tsuge
 */
class AABoardRectActor : public BoardActor {

public:
    AABoardRectActor(const char* prm_name, CollisionChecker* prm_pChecker);

    void drawRect(coord prm_x1, coord prm_y1, coord prm_x2, coord prm_y2);

    virtual ~AABoardRectActor(); //デストラクタ
};

}
#endif /*GGAF_DX_AABOARDRECTACTOR_H_*/
