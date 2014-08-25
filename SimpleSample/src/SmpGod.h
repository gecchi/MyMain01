#ifndef SMPGOD_H_
#define SMPGOD_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/DefaultGod.h"

namespace SimpleSample {

/**
 * 神の雛形 .
 * GgafLib::DefaultGod を継承し、神クラスを作成して下さい。<BR>
 * その際、GgafCore::GgafUniverse* createUniverse() をオーバーライド＆実装して下さい。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpGod : public GgafLib::DefaultGod {

public:
    /**
     * コンストラクタ .
     */
    SmpGod();

    /**
     * この世生成方法の実装 .
     * 神クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual ~SmpGod();
};

}
#endif /*SMPGOD_H_*/
