#ifndef GGAFCRITICALEXCEPTION_H_
#define GGAFCRITICALEXCEPTION_H_

/**
 * GgafCoreライブラリ専用、ライブラリ業務例外 .
 * GgafCoreライブラリの利用者（私だけ）は本クラスをキャッチしてプログラムをストップして下さい。
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
#define throw_GgafCriticalException(X) {std::stringstream ss; ss << X; throw GgafCriticalException(ss.str()); }


class GgafCriticalException : public GgafException {
public:
	GgafCriticalException(string prm_message);
	virtual ~GgafCriticalException();
};


#endif /*GGAFCRITICALEXCEPTION_H_*/
