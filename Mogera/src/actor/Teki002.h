#ifndef TEKI002_H_
#define TEKI002_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace Mogera {

/**
 * テスト敵キャラクタ .
 * @version 1.00
 * @since 2013/08/30
 * @author Masatoshi Tsuge
 */
class Teki002 : public GgafLib::DefaultMeshActor {

public:
    GgafDxCore::GgafDxAxesMover* pAxMvr_;
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;

    angle angRz_Target_;
    angle angRy_Target_;
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    Teki002(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~Teki002();
};

}
#endif /*TEKI002_H_*/

