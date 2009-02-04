#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9PlateActor::GgafDx9PlateActor(char* prm_name, char* prm_spritemodel_name) : GgafDx9TransformedActor(prm_name) {
	_class_name = "GgafDx9PlateActor";
	_pModelLead = (GgafDx9ModelLead*)GgafDx9God::_pModelManager->lead(prm_spritemodel_name);
	_pPlateModel = (GgafDx9PlateModel*)_pModelLead->getResource();
	_iPatternNo_Top     = 0;
	_iPatternNo_Bottom  = _pPlateModel->_iPatternNo_Max;
	_iPatternNo_Active  = 0;
	_paVertex = NEW VERTEX[4];
	_iSize_Vertecs = sizeof(VERTEX)*4;
	_iSize_Vertec_unit = sizeof(VERTEX);

	_paVertex[0].x = 0.0f;
	_paVertex[0].y = 0.0f;
	_paVertex[0].z = 0.0f;
	_paVertex[1].x = 0.0f + _pPlateModel->_fSize_PlateModelWidth;
	_paVertex[1].y = 0.0f;
	_paVertex[1].z = 0.0f;
	_paVertex[2].x = 0.0f;
	_paVertex[2].y = 0.0f + _pPlateModel->_fSize_PlateModelHeight;
	_paVertex[2].z = 0.0f;
	_paVertex[3].x = 0.0f + _pPlateModel->_fSize_PlateModelWidth;
	_paVertex[3].y = 0.0f + _pPlateModel->_fSize_PlateModelHeight;
	_paVertex[3].z = 0.0f;
	static GgafDx9RectUV* pRectUV_Active;
	pRectUV_Active = (_pPlateModel->_paRectUV) + 0;
	_paVertex[0].tu = pRectUV_Active->_aUV[0].tu;
	_paVertex[0].tv = pRectUV_Active->_aUV[0].tv;
	_paVertex[1].tu = pRectUV_Active->_aUV[1].tu;
	_paVertex[1].tv = pRectUV_Active->_aUV[1].tv;
	_paVertex[2].tu = pRectUV_Active->_aUV[2].tu;
	_paVertex[2].tv = pRectUV_Active->_aUV[2].tv;
	_paVertex[3].tu = pRectUV_Active->_aUV[3].tu;
	_paVertex[3].tv = pRectUV_Active->_aUV[3].tv;

  	_paVertex[0].rhw = 1.0f;
	_paVertex[1].rhw = 1.0f;
	_paVertex[2].rhw = 1.0f;
	_paVertex[3].rhw = 1.0f;
	_paVertex[0].color = 0xFFFFFFFF;
	_paVertex[1].color = 0xFFFFFFFF;
	_paVertex[2].color = 0xFFFFFFFF;
	_paVertex[3].color = 0xFFFFFFFF; //‚¢‚é‚Ì‚©??

	_fAlpha = 1.0f;

}


void GgafDx9PlateActor::processDrawMain() {
	_paVertex[0].x = _x;
	_paVertex[0].y = _y;
	_paVertex[0].z = _z;

	_paVertex[1].x = _x + _pPlateModel->_fSize_PlateModelWidth;
	_paVertex[1].y = _y;
	_paVertex[1].z = _z;

	_paVertex[2].x = _x;
	_paVertex[2].y = _y + _pPlateModel->_fSize_PlateModelHeight;
	_paVertex[2].z = _z;

	_paVertex[3].x = _x + _pPlateModel->_fSize_PlateModelWidth;
	_paVertex[3].y = _y + _pPlateModel->_fSize_PlateModelHeight;
	_paVertex[3].z = _z;

	static D3DCOLOR c;
	c = D3DCOLOR_ARGB((int)(_fAlpha*255.0) ,255,255,255);
	_paVertex[0].color = c;
	_paVertex[1].color = c;
	_paVertex[2].color = c;
	_paVertex[3].color = c;


	_pPlateModel->draw(this);
}


void GgafDx9PlateActor::setPatternNo(int prm_iPatternNo) {
	if (_iPatternNo_Active == prm_iPatternNo) {
		return;
	} else {
		_iPatternNo_Active = prm_iPatternNo;
		static GgafDx9RectUV* pRectUV_Active;
		pRectUV_Active = (_pPlateModel->_paRectUV) + prm_iPatternNo;
		_paVertex[0].tu = pRectUV_Active->_aUV[0].tu;
		_paVertex[0].tv = pRectUV_Active->_aUV[0].tv;
		_paVertex[1].tu = pRectUV_Active->_aUV[1].tu;
		_paVertex[1].tv = pRectUV_Active->_aUV[1].tv;
		_paVertex[2].tu = pRectUV_Active->_aUV[2].tu;
		_paVertex[2].tv = pRectUV_Active->_aUV[2].tv;
		_paVertex[3].tu = pRectUV_Active->_aUV[3].tu;
		_paVertex[3].tv = pRectUV_Active->_aUV[3].tv;
	}
}


GgafDx9PlateActor::~GgafDx9PlateActor() {
	RELEASE_SAFETY(_pModelLead);
	DELETEARR_IMPOSSIBLE_NULL(_paVertex);
}
