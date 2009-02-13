#ifndef GGAFDX9SQUAREACTORD_H_
#define GGAFDX9SQUAREACTORD_H_
namespace GgafDx9Core {

/**
 * スクエアアクター.
 * GgafDx9UntransformedActor を継承し、スクエア（四角形）を表示するためのアクターです。<BR>
 * デバッグ用の当たり判定領域表示などで利用されます。<BR>
 */
class GgafDx9SquareActor : public GgafDx9UntransformedActor {

private:

public:
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9SquareModel* _pSquareModel;

    GgafDx9SquareActor(const char* prm_name,
                       const char* prm_squaremodel_name,
                       GgafDx9GeometryMover* prm_pGeoMover,
                       GgafDx9GeometryChecker* prm_pGeoChecker);

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDrawMain();

    virtual ~GgafDx9SquareActor(); //デストラクタ

};

}
#endif /*GGAFDX9SQUAREACTORD_H_*/
