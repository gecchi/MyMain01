#ifndef GGAFDXCRITICALEXCEPTION_H_
#define GGAFDXCRITICALEXCEPTION_H_
namespace GgafDxCore {


/**
 * GgafDxCoreライブラリ専用、ライブラリ業務例外 .
 * GgafDxCoreライブラリの利用者（私だけ?）は本クラスをキャッチしてプログラムをストップして下さい。
 * @version 1.00
 * @since 2008/11/12
 * @author Masatoshi Tsuge
 */
class GgafDxCriticalException : public GgafCore::GgafCriticalException {
public:
    HRESULT _hr;

public:
    GgafDxCriticalException(std::string prm_message, HRESULT prm_hr);
    //オーバーライド
    virtual std::string getMsg();

    static std::string getHresultMsg(HRESULT prm_hr);
    virtual ~GgafDxCriticalException();
};


}
#endif /*GGAFDXCRITICALEXCEPTION_H_*/
