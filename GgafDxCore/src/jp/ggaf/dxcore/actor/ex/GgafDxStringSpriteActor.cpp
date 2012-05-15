#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxStringSpriteActor::GgafDxStringSpriteActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat)
: GgafDxSpriteSetActor(prm_name, prm_model, "StringSpriteEffect", "StringSpriteTechnique", prm_pStat, NULL) {

  _class_name = "GgafDxStringSpriteActor";
  _draw_string = NULL;
  _len = 0;
  _len_pack_num = 0;
  _remainder_len = 0;

  _buf = NEW char[1024];
  _buf[0] = '\0';
  //デフォルトの１文字の幅(px)設定
  for (int i = 0; i < 256; i++) {
      _aWidthPx[i] = (int)(_pSpriteSetModel->_fSize_SpriteSetModelWidthPx);
  }
  _chr_width_px = (int)(_pSpriteSetModel->_fSize_SpriteSetModelWidthPx); //１文字の幅(px)
  _chr_height_px = (int)(_pSpriteSetModel->_fSize_SpriteSetModelHeightPx); //１文字の高さ(px)
  _X_offset_align = 0;
  _width_len_px = 0;

  //デフォルトで名前(prm_name)が表示文字列になる
  /*
  if (prm_name != NULL) {
      _draw_string = (char*)prm_name;
      _len = strlen(prm_name);
      _len_pack_num = _len/_pSpriteSetModel->_set_num;
      _remainder_len = _len%_pSpriteSetModel->_set_num;
      if (_align == ALIGN_CENTER) {
          _width_len_px = 0;
          for (int i = 0; i < _len; i++) {
              _width_len_px += _aWidthPx[_draw_string[i]];
          }
      } else {
          _width_len_px = 0;
      }
  }
  */
}

void GgafDxStringSpriteActor::onCreateModel() {

}

void GgafDxStringSpriteActor::update(coord X, coord Y, const char* prm_str) {
  update(prm_str);
  locate(X, Y);
}

void GgafDxStringSpriteActor::update(coord X, coord Y, char* prm_str) {
  update(prm_str);
  locate(X, Y);
}

void GgafDxStringSpriteActor::update(coord X, coord Y, coord Z, const char* prm_str) {
  update(prm_str);
  locate(X, Y, Z);
}

void GgafDxStringSpriteActor::update(coord X, coord Y, coord Z, char* prm_str) {
  update(prm_str);
  locate(X, Y, Z);
}

void GgafDxStringSpriteActor::update(const char* prm_str) {
  if (prm_str == _draw_string) {
      return;
  }
  _draw_string = (char*)prm_str;
  _len = strlen(prm_str);
  _len_pack_num = _len/_pSpriteSetModel->_set_num;
  _remainder_len = _len%_pSpriteSetModel->_set_num;
  if (_align == ALIGN_CENTER) {
      _width_len_px = 0;
      for (int i = 0; i < _len; i++) {
          _width_len_px += _aWidthPx[_draw_string[i]];
      }
  } else {
      _width_len_px = 0;
  }
}

void GgafDxStringSpriteActor::update(char* prm_str) {
  _len = strlen(prm_str);
#ifdef MY_DEBUG
  if (_len > 1024-1) {
      throwGgafCriticalException("GgafDxStringSpriteActor::update 引数文字列数が範囲外です。name="<<getName());
  }
#endif
  _draw_string = _buf;
  strcpy(_draw_string, prm_str);
  _len_pack_num = _len/_pSpriteSetModel->_set_num;
  _remainder_len = _len%_pSpriteSetModel->_set_num;
  if (_align == ALIGN_CENTER) {
      _width_len_px = 0;
      for (int i = 0; i < _len; i++) {
          _width_len_px += _aWidthPx[_draw_string[i]];
      }
  } else {
      _width_len_px = 0;
  }
}


void GgafDxStringSpriteActor::update(coord X, coord Y, const char* prm_str,
                                  GgafDxAlign prm_align,
                                  GgafDxValign prm_valign) {
  update(prm_str, prm_align, prm_valign);
  locate(X, Y);
}

void GgafDxStringSpriteActor::update(coord X, coord Y, char* prm_str,
                                  GgafDxAlign prm_align,
                                  GgafDxValign prm_valign) {
  update(prm_str, prm_align, prm_valign);
  locate(X, Y);
}

void GgafDxStringSpriteActor::update(coord X, coord Y, coord Z, const char* prm_str,
                                  GgafDxAlign prm_align,
                                  GgafDxValign prm_valign) {
  update(prm_str, prm_align, prm_valign);
  locate(X, Y, Z);
}

void GgafDxStringSpriteActor::update(coord X, coord Y, coord Z, char* prm_str,
                                  GgafDxAlign prm_align,
                                  GgafDxValign prm_valign) {
  update(prm_str, prm_align, prm_valign);
  locate(X, Y, Z);
}

void GgafDxStringSpriteActor::update(const char* prm_str,
                                  GgafDxAlign prm_align,
                                  GgafDxValign prm_valign) {
  update(prm_str);
  setAlign(prm_align, prm_valign);
}

void GgafDxStringSpriteActor::update(char* prm_str,
                                  GgafDxAlign prm_align,
                                  GgafDxValign prm_valign) {
  update(prm_str);
  setAlign(prm_align, prm_valign);
}

void GgafDxStringSpriteActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
  _align = prm_align;
  _valign = prm_valign;
  if (_align == ALIGN_CENTER) {
      _width_len_px = 0;
      for (int i = 0; i < _len; i++) {
          _width_len_px += _aWidthPx[_draw_string[i]];
      }
  } else {
      _width_len_px = 0;
  }
}


void GgafDxStringSpriteActor::processSettlementBehavior() {
}


void GgafDxStringSpriteActor::processDraw() {
  if (_len == 0) {
      return;
  }
  ID3DXEffect* pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
  HRESULT hr;
  pixcoord y = C_PX(_Y);

  if (_valign == VALIGN_MIDDLE) {
      //OK
  } else if (_valign == VALIGN_TOP) {
      y = y - (_chr_height_px/2);
  } else {
      //VALIGN_BOTTOM
      y = y + (_chr_height_px/2);
  }

  hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_alpha[0], _alpha); //注意：アルファは文字ごとは不可
  checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw SetFloat(_ah_alpha) に失敗しました。");

  if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
      int strindex, pattno;
      pixcoord x = C_PX(_X) - (_width_len_px/2);
      pixcoord x_tmp = x;
      float u,v;
      for (int pack = 0; pack < _len_pack_num+(_remainder_len == 0 ? 0 : 1); pack++) {
          _draw_set_num = pack < _len_pack_num ? _pSpriteSetModel->_set_num : _remainder_len;
          for (int i = 0; i < _draw_set_num; i++) {
              strindex = pack * _pSpriteSetModel->_set_num + i;
              if (_draw_string[strindex] == '\0') {
                  break;
//                } if (_draw_string[strindex] == '\n') {
//                    x = C_PX(_X) - (_width_len_px/2);
//                    x_tmp = x;
//                    y += _chr_height_px;
//                    hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_transformed_Y[i], y);
//                    checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw SetFloat(_ah_transformed_Y) に失敗しました。");
//                    continue;
              } else if (_draw_string[strindex]  - ' ' > '_'  || _draw_string[strindex] - ' ' < 0) {
                  pattno = '?' - ' '; //範囲外は"?"を表示
              } else {
                  pattno = _draw_string[strindex] - ' '; //通常文字列
              }
              //プロポーショナルな幅計算
              int w = ((_chr_width_px - _aWidthPx[(unsigned char)(_draw_string[strindex])]) / 2);
              x = x_tmp - w;
              x_tmp = x + _chr_width_px - w;
              hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_X[i], PX_C(x));
              checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw SetFloat(_ah_transformed_X) に失敗しました。");
              _pUvFlipper->getUV(pattno, u, v);
              hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_offset_u[i], u);
              checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() SetFloat(_h_offset_u) に失敗しました。");
              hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_offset_v[i], v);
              checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() SetFloat(_h_offset_v) に失敗しました。");
          }
          _pSpriteSetModel->draw(this, _draw_set_num);
      }
  } else if (_align == ALIGN_RIGHT) {
      int strindex, pattno;
      pixcoord x = C_PX(_X);//-_aWidthPx[_len-1];
      pixcoord x_tmp = x;
      float u,v;
      for (int pack = 0; pack < _len_pack_num+(_remainder_len == 0 ? 0 : 1); pack++) {
          _draw_set_num = pack < _len_pack_num ? _pSpriteSetModel->_set_num : _remainder_len;
          for (int i = 0; i < _draw_set_num; i++) {
              strindex = _len - (pack * _pSpriteSetModel->_set_num + i) - 1;
              if (_draw_string[strindex] == '\0') {
                  break;
//                } if (_draw_string[strindex] == '\n') {
//                    x = C_PX(_X);
//                    x_tmp = x;
//                    y -= _chr_height_px;
//                    hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_transformed_Y[i], y);
//                    checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw SetFloat(_ah_transformed_Y) に失敗しました。");
//                    continue;
              } else if (_draw_string[strindex]  - ' ' > '_'  || _draw_string[strindex] - ' ' < 0) {
                  pattno = '?' - ' '; //範囲外は"?"を表示
              } else {
                  pattno = _draw_string[strindex] - ' '; //通常文字列
              }
              //プロポーショナルな幅計算
              int w = ((_chr_width_px - _aWidthPx[(unsigned char)(_draw_string[strindex])]) / 2);
              x = x_tmp - (w + _aWidthPx[(unsigned char)(_draw_string[strindex])]);
              x_tmp = x + w;
              hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_X[i], PX_C(x));
              checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw SetFloat(_ah_transformed_X) に失敗しました。");
              _pUvFlipper->getUV(pattno, u, v);
              hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_offset_u[i], u);
              checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() SetFloat(_h_offset_u) に失敗しました。");
              hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_offset_v[i], v);
              checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() SetFloat(_h_offset_v) に失敗しました。");
          }
          _pSpriteSetModel->draw(this, _draw_set_num);
      }
  }
}

GgafDxStringSpriteActor::~GgafDxStringSpriteActor() {
  DELETE_IMPOSSIBLE_NULL(_buf);
}
