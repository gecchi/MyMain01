#ifndef GGAFCRITICALEXCEPTION_H_
#define GGAFCRITICALEXCEPTION_H_
namespace GgafCore {


/**
 * GgafCoreライブラリ専用、ライブラリ業務例外 .
 * GgafCoreライブラリの利用者（私だけ）は本クラスをキャッチしてプログラムをストップして下さい。
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
#define throw_GgafCriticalException(X) {std::stringstream ss; ss << X; throw GgafCore::GgafCriticalException(ss.str()); }


class GgafCriticalException : public GgafCore::GgafException {
public:
	GgafCriticalException(std::string prm_message);
	virtual ~GgafCriticalException();
};


}
#endif /*GGAFCRITICALEXCEPTION_H_*/
