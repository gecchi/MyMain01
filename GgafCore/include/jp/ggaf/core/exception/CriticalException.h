#ifndef GGAF_CORE_CRITICALEXCEPTION_H_
#define GGAF_CORE_CRITICALEXCEPTION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/exception/Exception.h"

#include <sstream>

#define throwCriticalException(X)  do { \
    std::stringstream ss; \
    ss <<__FILE__<<"("<<__LINE__<<") : "<< X; \
    throw GgafCore::CriticalException(ss.str()); \
}while(0)

namespace GgafCore {

/**
 * Core���C�u������p�A���C�u�����Ɩ���O .
 * Core���C�u�����̗��p�ҁi������?�j�͖{�N���X���L���b�`���ăv���O�������X�g�b�v���ĉ������B
 * @version 1.00
 * @since 2007/12/03
 * @author Masatoshi Tsuge
 */
class CriticalException : public Exception {
public:
    CriticalException(std::string prm_message);
    virtual ~CriticalException();
};

}
#endif /*GGAF_CORE_CRITICALEXCEPTION_H_*/
