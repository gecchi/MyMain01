#ifndef SPLINESOURCE_H_
#define SPLINESOURCE_H_
namespace GgafDx9LibStg {

/**
 * Splineオブジェクトソース .
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSource : public GgafCore::GgafObject {

public:
    Spline3D* _pSp;
    double _accuracy;
    frame _spent_frame;
    ang_velo _ang_veloRzRyMv;
    std::string _classname;

    SplineSource(char* prm_idstr);

    /**
     * SplineProgram オブジェクトを作成する .
     * 定義ファイルにより、FixedFrameSplineProgram か FixedVelocitySplineProgram の
     * いづれかのオブジェクトを生成し、それを返す。<BR>
     * 内部スプライン座標情報は共通、いくら呼び出してもインスタンスは一つ。<BR>
     * @param prm_pForWhichActor どのアクターの為の SplineProgram なのかを指定
     * @return
     */
//    SplineProgram* createSplineProgram(GgafDx9Core::GgafDx9GeometricActor* prm_pForWhichActor);

    SplineManufacture* createManufacture(GgafDx9Core::GgafDx9GeometricActor* prm_pForWhichActor);

    virtual ~SplineSource();
};

}
#endif /*SPLINESOURCE_H_*/
