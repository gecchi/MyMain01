#ifndef GGAF_CORE_EXCEPTION_H_
#define GGAF_CORE_EXCEPTION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>

namespace GgafCore {

/**
 * �{���C�u������O
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class Exception : public Object {

public:
    std::string _message;

public:
    explicit Exception(std::string prm_message);
    virtual std::string getMsg();
    virtual ~Exception();
};

}
#endif /*GGAF_CORE_EXCEPTION_H_*/
