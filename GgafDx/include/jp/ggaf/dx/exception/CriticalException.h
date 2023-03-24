#ifndef GGAF_DX_CRITICALEXCEPTION_H_
#define GGAF_DX_CRITICALEXCEPTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/exception/CriticalException.h"

#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#ifdef MY_DEBUG
    #define checkDxException(HR, OKVAL, X) do { \
        if (HR != OKVAL) { \
            std::stringstream ss; \
            ss <<__FILE__<<"("<<__LINE__<<") : " << FUNC_NAME << " " << X; \
            throw GgafDx::CriticalException(ss.str(),HR); \
        } \
    }while(0)
#else
    #define checkDxException(HR, OKVAL, X)
#endif

#define throwCriticalDxException(HR, X) do { \
    std::stringstream ss; \
    ss <<__FILE__<<"("<<__LINE__<<") : " << FUNC_NAME << " " << X; \
    throw GgafDx::CriticalException(ss.str(),HR); \
}while(0)

namespace GgafDx {

/**
 * Coreライブラリ専用、ライブラリ業務例外 .
 * Coreライブラリの利用者（私だけ?）は本クラスをキャッチしてプログラムをストップして下さい。
 * @version 1.00
 * @since 2008/11/12
 * @author Masatoshi Tsuge
 */
class CriticalException : public GgafCore::CriticalException {
public:
    HRESULT _hr;

public:
    CriticalException(std::string prm_message, HRESULT prm_hr);
    //オーバーライド
    virtual std::string getMsg();

    static std::string getHresultMsg(HRESULT prm_hr);
    virtual ~CriticalException();
};


}
#endif /*GGAF_DX_CRITICALEXCEPTION_H_*/
