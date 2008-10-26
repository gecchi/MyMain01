#include "stdafx.h"

RotationActor::RotationActor(string prm_name) : GgafDx9UntransformedActor(prm_name, NEW StgMover(this), NEW StgChecker(this))  {
 		_class_name = "RotationActor";
 	    setBumpableOnlySelf(true);
 	    _wasDrawed = true; //無駄な描画を防ぐ、
						   //これにより、描画順序リストに登録されなかったサブアクターたちに、
						   //processDrawMain()が呼ばれることは無い。ちょっとだけ最適化。
 		_pMover = (StgMover*)_pGeoMover;
 		_pChecker = (StgChecker*)_pGeoChecker;
}
