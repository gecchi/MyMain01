#ifndef SPLINESOURCE_H_
#define SPLINESOURCE_H_
namespace GgafDx9LibStg {

/**
 * Splineオブジェクトソース .
 * Spline3Dのラッパーであり、ファイルからの読み込み機能を追加したクラス。
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSource : public GgafCore::GgafObject {

public:

    Spline3D* _pSp;
    double _accuracy;

    bool _is_create_Spline3D;
    SplineSource(char* prm_idstr);

    SplineSource(Spline3D* prm_pSp);

    virtual ~SplineSource();
};

}
#endif /*SPLINESOURCE_H_*/
