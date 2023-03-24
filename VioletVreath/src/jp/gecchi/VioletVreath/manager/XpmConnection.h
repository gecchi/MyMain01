#ifndef XPMCONNECTION_H_
#define XPMCONNECTION_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/core/util/Xpm.h"

namespace VioletVreath {

/**
 * Pixmap(GgafCore::Xpm)資源コネクション.
 * @version 1.00
 * @since 2014/10/06
 * @author Masatoshi Tsuge
 */
class XpmConnection : public GgafCore::ResourceConnection<GgafCore::Xpm> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pResource GgafCore::Xpmオブジェクト
     */
    XpmConnection(const char* prm_idstr, GgafCore::Xpm* prm_pResource);

    void processReleaseResource(GgafCore::Xpm* prm_pResource);

    virtual ~XpmConnection() {
    }
};

}
#endif /*XPMCONNECTION_H_*/
