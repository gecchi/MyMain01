#ifndef SMPSPACETIME_H_
#define SMPSPACETIME_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

namespace SimpleSample {

/**
 * 「この世」の雛形 .
 * GgafLib::DefaultSpacetime を継承し「この世」クラスを作成して下さい。
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpSpacetime : public GgafLib::DefaultSpacetime {

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~SmpSpacetime();
};

}
#endif /*SMPSPACETIME_H_*/
