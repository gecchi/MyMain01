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
    static void writeln(std::string prm_msg);
    static void write(std::string prm_msg);
};

}
#endif /*GGAFLOGGER_H_*/
