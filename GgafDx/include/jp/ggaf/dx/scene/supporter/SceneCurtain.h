#ifndef GGAF_DX_SCENECURTAIN_H_
#define GGAF_DX_SCENECURTAIN_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/core/util/Curtain.hpp"

namespace GgafDx {

/**
 * シーンのカーテン .
 * @version 1.00
 * @since 2017/11/17
 * @author Masatoshi Tsuge
 */
class SceneCurtain : public GgafCore::Curtain<float> {

private:
    /** [r]カーテンを取り付けるシーン */
    Scene* _pDxScene;

public:

    /**
     * コンストラクタ .
     * @param prm_pScene カーテンを取り付けるシーン
     */
    SceneCurtain(Scene* prm_pScene,
                       float prm_curtain_rail_length,
                       float prm_min_position,
                       float prm_max_position);

    Scene* getScene() {
        return _pDxScene;
    }
    /**
     * シーンの最上位から見て、カーテンの位置（閉まってい部分）を取得 .
     * @return カーテンの位置
     */
    virtual float getCurtainPositionFromTopScene();

    virtual void behave() override;

    virtual ~SceneCurtain();
};

}
#endif /*GGAF_DX_SCENECURTAIN_H_*/

