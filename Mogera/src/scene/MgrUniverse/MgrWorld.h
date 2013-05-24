#ifndef MGRWORLD_H_
#define MGRWORLD_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "scene/MgrUniverse.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

namespace Mogera {

#ifdef P_UNIVERSE
    #define P_WORLD ((Mogera::MgrWorld*)(P_UNIVERSE->pWorld_))
#else
    #error P_UNIVERSE isnt define
#endif

/**
 * 世界シーンの雛形 .
 * GgafLib::DefaultScene を継承してシーンクラスを作成して下さい。<BR>
 * 本サンプルでは「世界」シーンと名づけました。<BR>
 * processBehavior() をオーバーライドし、毎フレームの処理を記述します。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrWorld : public GgafLib::DefaultScene {

public:
    /** 入力受付 */
    GgafLib::VirtualButton vb_;
    /** テストキャラ */
    MgrActor* pActor_;

    /**
     * コンストラクタ .
     * @param prm_name 名称
     */
    MgrWorld(const char* prm_name);

    /**
     * 世界シーンの初期処理 .
     */
    void initialize() override;

    /**
     * 世界シーンの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~MgrWorld();
};

}
#endif /*MGRWORLD_H_*/
