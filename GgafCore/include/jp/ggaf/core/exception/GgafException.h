#ifndef GGAFEXCEPTION_H_
#define GGAFEXCEPTION_H_
namespace GgafCore {

/**
 * 本ライブラリ例外
 * @version 1.00
 * @since 2007/11/20
 * @author Masatoshi Tsuge
 */
class GgafException : public GgafObject {

public:
    std::string _message;
    GgafException(std::string prm_message);
    virtual std::string getMsg();
    virtual ~GgafException();
};

}
#endif /*GGAFEXCEPTION_H_*/
