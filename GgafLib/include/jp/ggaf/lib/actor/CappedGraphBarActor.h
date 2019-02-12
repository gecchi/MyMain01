#ifndef GGAF_LIB_CAPPEDGRAPHBARACTOR_H_
#define GGAF_LIB_CAPPEDGRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/GraphBarActor.h"

namespace GgafLib {

/**
 * 数量バー(両端テクスチャ有り) .
 * テクスチャの番号は、 <=> の "<" の番号に合わせること。
 * @version 1.00
 * @since 2013/09/17
 * @author Masatoshi Tsuge
 */
class CappedGraphBarActor : public GraphBarActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @param prm_model
     * @param prm_pQty
     */
    CappedGraphBarActor(const char* prm_name, const char* prm_model, Quantity<int, pixcoord>* prm_pQty);

    /**
     * コンストラクタ
     * @param prm_name
     * @param prm_model
     * @param prm_pQty
     */
    CappedGraphBarActor(const char* prm_name, const char* prm_model);

    void processDraw() override;

    virtual ~CappedGraphBarActor();
};

}
#endif /*GGAF_LIB_CAPPEDGRAPHBARACTOR_H_*/

