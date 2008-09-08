#ifndef GGAFDX9SQUAREACTORD_H_
#define GGAFDX9SQUAREACTORD_H_


class GgafDx9SquareActor : public GgafDx9UntransformedActor {

private:


public:
	GgafDx9SquareModel* _pSquareModel;

	GgafDx9SquareActor(string prm_name, string prm_squaremodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9SquareActor();		//デストラクタ




};


#endif /*GGAFDX9SQUAREACTORD_H_*/
