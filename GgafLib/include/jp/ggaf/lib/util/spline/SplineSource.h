#ifndef SPLINESOURCE_H_
#define SPLINESOURCE_H_
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
    SplineSource(char* prm_idstr);

    SplineSource(SplineLine* prm_pSp);

    virtual ~SplineSource();
};

}
#endif /*SPLINESOURCE_H_*/
