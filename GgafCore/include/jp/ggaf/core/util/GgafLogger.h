#ifndef GGAFLOGGER_H_
#define GGAFLOGGER_H_
namespace GgafCore {

/**
 * ÉçÉOÉNÉâÉX
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafLogger {

public:
    static void writeln(std::stringstream& prm_ssmsg);
    static void write(std::stringstream& prm_ssmsg);
};

}
#endif /*GGAFLOGGER_H_*/
