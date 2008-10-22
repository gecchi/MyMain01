#ifndef GGAFDX9UNTRANSFORMEDACTOR_H_
#define GGAFDX9UNTRANSFORMEDACTOR_H_

class GgafDx9UntransformedActor : public GgafDx9MainActor {

private:


public:

	/** ワールドX座標 */
	int _X;
	/** ワールドY座標 */
	int _Y;
	/** ワールドZ座標 */
	int _Z;
//	/** フレーム毎ワールドX座標の増分 */
//	int _incX;
//	/** フレーム毎ワールドY座標の増分 */
//	int _incY;
//	/** フレーム毎ワールドZ座標の増分 */
//	int _incZ;

	/** ワールドX軸回転角 */
	int _RX;
	/** ワールドY軸回転角 */
	int _RY;
	/** ワールドZ軸回転角 */
	int _RZ;
//	/** フレーム毎ワールドX軸回転角の増分 */
//	int _incRX;
//	/** フレーム毎ワールドY軸回転角の増分 */
//	int _incRY;
//	/** フレーム毎ワールドZ軸回転角の増分 */
//	int _incRZ;

	/** ワールドX軸方向倍率 */
	int _SX;
	/** ワールドY軸方向倍率 */
	int _SY;
	/** ワールドZ軸方向倍率 */
	int _SZ;

	//補足
	//【_X, _Y, _Z の単位について】
	//　採り得る値は DirectX9のワールド座標(float)*1000 の値である。
	//　描画の直前に 1000 で除算され平行移動のワールド変換に使用される。
	//　なんでかというと整数で座標計算して少しでも速くしたいため。
	//【_RX, _RY, _RZ の単位について】
	//　独自単位の「アングル値」を採る。「アングル値」とは 0~360000 の値で、1000倍の精度の角度値である。
	//　円周角と同じく3時の方向を0とし、反時計回りにアングル値は増えるものとする。直角の値は90000、水平は180000である。
	//【_SX, _SY, _SZ の単位について】
	//　描画の直前に 1000 で除算され、スケールのワールド変換に使用される。
	//　1000が１倍のスケール意味する。


	GgafDx9GeometryMover* _pGeoMover;

	GgafDx9GeometryChecker* _pGeoChecker;


	const int _X_OffScreenLeft;
	const int _X_OffScreenRight;
	const int _Y_OffScreenTop;
	const int _Y_OffScreenBottom;


	/**
	 * コンストラクタ<BR>
	 * @param	prm_name 識別名
	 */
	GgafDx9UntransformedActor(string prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	virtual GgafDx9UntransformedActor* getPrev() {
		return (GgafDx9UntransformedActor*)GgafActor::getPrev();
	}

	virtual GgafDx9UntransformedActor* getNext() {
		return (GgafDx9UntransformedActor*)GgafActor::getNext();
	}

	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent);

	virtual bool isOffScreen() { return false; }

	virtual void setGeometry(int X, int Y, int Z) {
		_X = X;
		_Y = Y;
		_Z = Z;
	}

	/**
	 * _Zの値により、大まかにレンダリング順序を設定する。
	 * 任意の優先順位でレンダリングしたい場合は、このメソッドをオーバーライドし
	 * GgafWorld::_apActorDrawDepthLevel_first[n] の好きな n に addSubLast(this) を行って下さい。
	 * 但し 0 ≦ n ＜ MAX_DRAW_DEPTH_LEVEL
	 */
	virtual void processDrawPrior();

	virtual ~GgafDx9UntransformedActor();		//デストラクタ


};


#endif /*GGAFDX9UNTRANSFORMEDACTOR_H_*/
