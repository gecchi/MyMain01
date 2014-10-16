#ifndef FONT01_H_
#define FONT01_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/StringBoardActor.h"

namespace VVViewer {

/**
 * 情報表示フォント .
 * @version 1.00
 * @since 2014/10/16
 * @author Masatoshi Tsuge
 */
class Font01 : public GgafLib::StringBoardActor {

public:
    Font01(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~Font01();

};

}
#endif /*FONT01_H_*/
