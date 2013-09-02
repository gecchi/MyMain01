#ifndef GGAFLIB_SPLINESOURCE_H_
#define GGAFLIB_SPLINESOURCE_H_
#include "jp/ggaf/core/GgafObject.h"

#include <string>

namespace GgafLib {

/**
 * Splineオブジェクトソース .
 * SplineLineのラッパーであり、ファイルからの読み込み機能を追加したクラス。
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSource : public GgafCore::GgafObject {

public:
    SplineLine* _pSp;
    double _accuracy;
    std::string _idstr;
    bool _is_create_SplineLine;

public:
    SplineSource(char* prm_idstr);

    SplineSource(SplineLine* prm_pSp);

    virtual ~SplineSource();
};

}
#endif /*GGAFLIB_SPLINESOURCE_H_*/
