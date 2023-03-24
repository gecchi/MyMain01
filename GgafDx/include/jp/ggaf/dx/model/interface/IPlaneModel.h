#ifndef GGAF_DX_IPLANEMODEL_H_
#define GGAF_DX_IPLANEMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

namespace GgafDx {

/**
 * PlaneActor用モデルクラス.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class IPlaneModel {

public:
    float _model_width_px;
    float _model_height_px;
    int _row_texture_split;
    int _col_texture_split;

public:
    /**
     * コンストラクタ<BR>
     */
    IPlaneModel() {
        _model_width_px = 32.0f;
        _model_height_px = 32.0f;
        _row_texture_split = 1;
        _col_texture_split = 1;
    }


    /**
     * デストラクタ<BR>
     * deleteするのはPlaneModelManagerである<BR>
     */
    virtual ~IPlaneModel() {
    }

};

}
#endif /*GGAF_DX_IPLANEMODEL_H_*/
