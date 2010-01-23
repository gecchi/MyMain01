#ifndef GGAFCRITICALEXCEPTION_H_
#define GGAFCRITICALEXCEPTION_H_
namespace GgafCore {

#define throwGgafCriticalException(X) { \
    std::stringstream ss; \
    ss <<__FILE__<<"("<<__LINE__<<") : "<< X; \
    throw GgafCore::GgafCriticalException(ss.str()); \
}


/**
 * GgafCoreライブラリ専用、ライブラリ業務例外 .
 * GgafCoreライブラリの利用者（私だけ?）は本クラスをキャッチしてプログラムをストップして下さい。
 * @version 1.00
 * @since 2007/12/03
 * @author Masatoshi Tsuge
 */
class GgafCriticalException : public GgafCore::GgafException {
public:
    GgafCriticalException(std::string prm_message);
    virtual ~GgafCriticalException();
};

}
#endif /*GGAFCRITICALEXCEPTION_H_*/
