#ifndef XPMCONNECTION_H_
#define XPMCONNECTION_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/core/util/GgafXpm.h"

namespace VioletVreath {

/**
 * Pixmap(GgafCore::GgafXpm)資源コネクション.
 * @version 1.00
 * @since 2014/10/06
 * @author Masatoshi Tsuge
 */
class XpmConnection : public GgafCore::GgafResourceConnection<GgafCore::GgafXpm> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pSpl3D SplineLineオブジェクト
     */
    XpmConnection(char* prm_idstr, GgafCore::GgafXpm* prm_pSpl3D);

    void processReleaseResource(GgafCore::GgafXpm* prm_pResource);

    virtual ~XpmConnection() {
    }
};

}
#endif /*XPMCONNECTION_H_*/
