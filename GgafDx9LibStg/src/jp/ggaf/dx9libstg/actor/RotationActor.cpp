#include "stdafx.h"

RotationActor::RotationActor(string prm_name) : GgafDx9UntransformedActor(prm_name, NEW StgMover(this), NEW StgChecker(this))  {
 		_class_name = "RotationActor";
 	    setBumpableOnlySelf(true);
 	    _wasDrawed = true; //���ʂȕ`���h���A
						   //����ɂ��A�`�揇�����X�g�ɓo�^����Ȃ������T�u�A�N�^�[�����ɁA
						   //processDrawMain()���Ă΂�邱�Ƃ͖����B������Ƃ����œK���B
 		_pMover = (StgMover*)_pGeoMover;
 		_pChecker = (StgChecker*)_pGeoChecker;
}
