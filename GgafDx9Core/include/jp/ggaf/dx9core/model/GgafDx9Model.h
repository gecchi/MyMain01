#ifndef GGAFDX9MODEL_H_
#define GGAFDX9MODEL_H_

class GgafDx9Model : public GgafObject {
    friend class GgafDx9ModelManager;

protected:
	/** モデル定義の識別名。 */
	string			_model_name;
	/** 次のGgafDx9Modelへのポインタ。終端はNULL */
	GgafDx9Model*	_pModel_Next;

public:

	/** 前回描画Model定義名 */
	static string _s_modelname_lastdraw;

	/**
	 * コンストラクタ<BR>
	 * @param prm_model_name モデル定義の識別名。".x"を追加すると定義Xファイル名になる。
	 */
	GgafDx9Model(string prm_model_name);

	virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target) = 0;

	virtual void restore() = 0;

	virtual void onDeviceLost() = 0;
	/**
	 * デストラクタ<BR>
	 * deleteするのはGgafDx9ModelManagerである<BR>
	 */
	virtual ~GgafDx9Model();		//デストラクタ
};

#endif /*GGAFDX9MODEL_H_*/
