#ifndef INERFACERADICAL_H_
#define INERFACERADICAL_H_


class InerfaceRadical {

public:

	GgafDx9UntransformedActor* _pActor_Radical;


	InerfaceRadical();

	/**
	 * 親元対象アクター設定
	 * @param prm_pActor
	 */
	void setRadical(GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}

	/**
	 * 親元対象アクター取得
	 * @param prm_pActor
	 */
	GgafDx9UntransformedActor* getRadical( prm_pActor) {
		return _pActor_Radical;
 	}


	virtual ~InerfaceRadical();
};


#endif /*INERFACERADICAL_H_*/

