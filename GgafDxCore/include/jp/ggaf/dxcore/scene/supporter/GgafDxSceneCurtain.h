#ifndef GGAFDXCORE_GGAFDXSCENECURTAIN_H_
#define GGAFDXCORE_GGAFDXSCENECURTAIN_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/util/GgafCurtain.hpp"

namespace GgafDxCore {

/**
 * シーンのカーテン .
 * @version 1.00
 * @since 2017/11/17
 * @author Masatoshi Tsuge
 */
class GgafDxSceneCurtain : public GgafCore::GgafCurtain<float> {

private:
    /** [r]カーテンを取り付けるシーン */
    GgafDxScene* _pDxScene;

public:

    /**
     * コンストラクタ .
     * @param prm_pScene カーテンを取り付けるシーン
     */
    GgafDxSceneCurtain(GgafDxScene* prm_pScene,
                       float prm_curtain_rail_length,
                       float prm_min_position,
                       float prm_max_position);

    GgafDxScene* getScene() {
        return _pDxScene;
    }
    /**
     * シーンの最上位から見て、カーテンの位置（閉まってい部分）を取得 .
     * @return カーテンの位置
     */
    virtual float getCurtainPositionFromTopScene();

    virtual void behave() override;

    virtual ~GgafDxSceneCurtain();
};

}
#endif /*GGAFDXCORE_GGAFDXSCENECURTAIN_H_*/

