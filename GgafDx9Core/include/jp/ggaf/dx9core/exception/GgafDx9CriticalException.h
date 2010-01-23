#ifndef GGAFDX9CRITICALEXCEPTION_H_
#define GGAFDX9CRITICALEXCEPTION_H_
namespace GgafDx9Core {

#ifdef MY_DEBUG
    #define checkDxException(HR, OKVAL, X) { \
        if (HR != OKVAL) { \
            std::stringstream ss; \
            ss <<__FILE__<<"("<<__LINE__<<") : " << X; \
            throw GgafDx9CriticalException(ss.str(),HR); \
        } \
    }
#else
    #define checkDxException(HR, OKVAL, X)
#endif


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
    virtual ~GgafDx9CriticalException();
};


}
#endif /*GGAFDX9CRITICALEXCEPTION_H_*/
