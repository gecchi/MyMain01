#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FontSpriteString::FontSpriteString(char* prm_font_modelname, int prm_iStrLen) : GgafObject() {
//	_font_modelname = prm_font_modelname;
//	_iStrLen = prm_iStrLen;
//	_papFontSpriteActor = NEW FontSpriteActor*[prm_iStrLen];
//	for (int i = 0; i < prm_iStrLen; i++) {
//		FontSpriteActor* pFontSpriteActor = NEW FontSpriteActor("FONTSPRITEACTOR", prm_font_modelname);
//		_papFontSpriteActor[i] = pFontSpriteActor;
//	}
}

void FontSpriteString::draw(int prm_X, int prm_Y, int prm_Z, string prm_string) {
//	int iLen_ParamStr = (int)prm_string.size();
//	int X = prm_X;
//	int Y = prm_Y;
//	const char* paChar = prm_string.c_str();
//	GgafDxSpriteModel* pSpriteModel = GgafDxModelManager::obtainSpriteModel(_font_modelname);
//	for (int i = 0; i < _iStrLen; i++) {
//		if (i < iLen_ParamStr) {
//			if (paChar[i] == '\n') {
//				X = prm_X;
//				Y -= (int)((pSpriteModel->_fSize_SpriteModelHeightPx)*LEN_UNIT);
//				continue;
//			} else {
//				if (paChar[i] - ' ' < 0) {
//					_papFontSpriteActor[i]->_pattno_uvflip_now = (' ' - ' '); //�͈͊O�͋�
//				}
//				_papFontSpriteActor[i]->_pattno_uvflip_now = (paChar[i] - ' '); //�ʏ핶����
//			}
//		} else {
//			break;
//		}
//		_papFontSpriteActor[i]->_X = X;
//		_papFontSpriteActor[i]->_Y = Y;
//		_papFontSpriteActor[i]->_Z = prm_Z;
//		_papFontSpriteActor[i]->draw();
//		X += (int)((pSpriteModel->_fSize_SpriteModelWidthPx) * LEN_UNIT);
//	}
}

FontSpriteString::~FontSpriteString() {
//	for (int i = 0; i < _iStrLen; i ++) {
//		DELETE_IMPOSSIBLE_NULL(_papFontSpriteActor[i]);
//	}
//	DELETEARR_IMPOSSIBLE_NULL(_papFontSpriteActor);

}