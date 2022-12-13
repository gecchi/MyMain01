#ifndef MGRSPACETIME_H_
#define MGRSPACETIME_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "actor/camera/MgrCamera.h"

namespace Mogera {

/**
 * 「この世」の雛形 .
 * GgafLib::DefaultSpacetime を継承し「この世」クラスを作成して下さい。
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrSpacetime : public GgafLib::DefaultSpacetime {

public:
    MgrWorld* pWorld_;

    MgrCameraWorker* pActiveCamWorker_;

    /** 入力受付 */
    GgafLib::VirtualButton* pVb_;
public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    MgrSpacetime(const char* prm_name, MgrCamera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override;

    void processJudgement() override;

    virtual MgrCamera* getCamera() override { //共変の戻り値
        return (MgrCamera*)_pCamera;
    }

    virtual ~MgrSpacetime();
};

}
#endif /*MGRSPACETIME_H_*/
