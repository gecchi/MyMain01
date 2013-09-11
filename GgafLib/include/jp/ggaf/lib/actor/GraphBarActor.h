#ifndef GRAPHBARACTOR_H_
#define GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace GgafLib {

/**
 * 横の数量バー .
 * （VVのクラスから昇格）
 * @version 1.00
 * @since 2012/09/11
 * @author Masatoshi Tsuge
 */
class GraphBarActor : public DefaultBoardActor {

public:
    /** 内容量 */
    AmountGraph* pAmount_;
    /** 横幅ピクセル */
    float chip_width_;
    float rate_org_chip_width_;
public:
    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    GraphBarActor(const char* prm_name, const char* prm_model, AmountGraph* prm_pAmount);

    void processBehavior() override;
    void processDraw() override;
    virtual ~GraphBarActor();
};

}
#endif /*GRAPHBARACTOR_H_*/

