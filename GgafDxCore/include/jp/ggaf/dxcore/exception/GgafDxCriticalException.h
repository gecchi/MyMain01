#ifndef GGAFDXCORE_GGAFDXCRITICALEXCEPTION_H_
#define GGAFDXCORE_GGAFDXCRITICALEXCEPTION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"

#include <windows.h>

#ifdef MY_DEBUG
    #define checkDxException(HR, OKVAL, X) do { \
        if (HR != OKVAL) { \
            std::stringstream ss; \
            ss <<__FILE__<<"("<<__LINE__<<") : " << X; \
            throw GgafDxCore::GgafDxCriticalException(ss.str(),HR); \
        } \
    }while(0)
#else
    #define checkDxException(HR, OKVAL, X)
#endif

#define throwGgafDxCriticalException(HR, X) do { \
    std::stringstream ss; \
    ss <<__FILE__<<"("<<__LINE__<<") : " << X; \
    throw GgafDxCore::GgafDxCriticalException(ss.str(),HR); \
}while(0)

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
#endif /*GGAFDXCORE_GGAFDXCRITICALEXCEPTION_H_*/
