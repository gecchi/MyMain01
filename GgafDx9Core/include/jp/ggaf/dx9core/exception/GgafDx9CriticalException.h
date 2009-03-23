#ifndef GGAFDX9CRITICALEXCEPTION_H_
#define GGAFDX9CRITICALEXCEPTION_H_
namespace GgafDx9Core {


/**
 * GgafCoreライブラリ専用、ライブラリ業務例外 .
 * GgafCoreライブラリの利用者（私だけ）は本クラスをキャッチしてプログラムをストップして下さい。
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
#ifdef OREDEBUG
#define potentialDx9Exception(HR, OKVAL, X) {if (HR != OKVAL) {std::stringstream ss; ss <<__FILE__<<"("<<__LINE__<<") : " << X; throw GgafDx9CriticalException(ss.str(),HR); } }
#else
#define potentialDx9Exception(HR, OKVAL, X)
#endif

class GgafDx9CriticalException  : public GgafCore::GgafCriticalException {
public:
	HRESULT _hr;
	GgafDx9CriticalException(std::string prm_message, HRESULT prm_hr);
	//オーバーライド
	virtual std::string getMsg();
	virtual ~GgafDx9CriticalException();
};


}
#endif /*GGAFDX9CRITICALEXCEPTION_H_*/
