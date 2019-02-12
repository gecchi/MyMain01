#ifndef GGAF_CORE_LOGGER_H_
#define GGAF_CORE_LOGGER_H_
#include "GgafCommonHeader.h"

#include <sstream>

namespace GgafCore {

/**
 * ���O�N���X
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class Logger {

public:
    static void writeln(std::stringstream& prm_ssmsg);
    static void write(std::stringstream& prm_ssmsg);
};

}
#endif /*GGAF_CORE_LOGGER_H_*/
