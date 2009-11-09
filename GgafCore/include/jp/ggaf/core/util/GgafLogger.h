#ifndef GGAFLOGGER_H_
#define GGAFLOGGER_H_
namespace GgafCore {

class GgafLogger {

public:
    static void writeln(std::string prm_msg);
    static void write(std::string prm_msg);
};

}
#endif /*GGAFLOGGER_H_*/
