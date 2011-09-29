#ifndef GGAFDX9CRITICALEXCEPTION_H_
#define GGAFDX9CRITICALEXCEPTION_H_
namespace GgafDx9Core {


/**
 * GgafDxCoreライブラリ専用、ライブラリ業務例外 .
 * GgafDxCoreライブラリの利用者（私だけ?）は本クラスをキャッチしてプログラムをストップして下さい。
 * @version 1.00
 * @since 2008/11/12
 * @author Masatoshi Tsuge
 */
class GgafDx9CriticalException : public GgafCore::GgafCriticalException {
public:
    HRESULT _hr;
    GgafDx9CriticalException(std::string prm_message, HRESULT prm_hr);
    //オーバーライド
    virtual std::string getMsg();

    static std::string getHresultMsg(HRESULT prm_hr);
    virtual ~GgafDx9CriticalException();
};


}
#endif /*GGAFDX9CRITICALEXCEPTION_H_*/
