#ifndef GGAFDX9CRITICALEXCEPTION_H_
#define GGAFDX9CRITICALEXCEPTION_H_
namespace GgafDx9Core {


/**
 * GgafCoreライブラリ専用、ライブラリ業務例外 .
 * GgafCoreライブラリの利用者（私だけ）は本クラスをキャッチしてプログラムをストップして下さい。
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
#define throw_GgafDx9CriticalException(X, HR) {std::stringstream ss; ss << X; throw GgafDx9CriticalException(ss.str(),HR); }


class GgafDx9CriticalException : public GgafCore::GgafCriticalException {
public:
	HRESULT _hr;
	GgafDx9CriticalException(string prm_message, HRESULT prm_hr);
	//オーバーライド
	virtual string getMsg();
	virtual ~GgafDx9CriticalException();
};


}
#endif /*GGAFDX9CRITICALEXCEPTION_H_*/
