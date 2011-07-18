#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

char LabelRankFont::RANK_1stDeg[10][6] = {
                                      ""     ,
                                      "!"    ,
                                      "!!"   ,
                                      "!!!"  ,
                                      "!!!!" ,
                                      "\""    ,
                                      "\"!"   ,
                                      "\"!!"  ,
                                      "\"!!!" ,
                                      "\"!!!!"
            };

char LabelRankFont::RANK_10thDeg[10][5] = {
                                       ""    ,
                                       "#$"  ,
                                       "%&"  ,
                                       "'("  ,
                                       ")*"  ,
                                       "+,"  ,
                                       "+,#$",
                                       "+,%&",
                                       "+,'(",
                                       "+,)*"
            };

char LabelRankFont::RANK_100thDeg[10][7] = {
                                        ""      ,
                                        "-./"   ,
                                        "012"   ,
                                        "345"   ,
                                        "678"   ,
                                        "9:;"   ,
                                        "9:;-./",
                                        "9:;012",
                                        "9:;345",
                                        "9:;678"
                                 };



char LabelRankFont::RANK_1000thDeg[10][9] = {
                                         ""        ,
                                         "<=>?"    ,
                                         "@ABC"    ,
                                         "DEFG"    ,
                                         "HIJK"    ,
                                         "LMNO"    ,
                                         "LMNO<=>?",
                                         "LMNO@ABC",
                                         "LMNODEFG",
                                         "LMNOHIJK"
                                  };


char LabelRankFont::RANK_10000thDeg[10][46] = {
                                           ""    ,
                                           "PQRST"                                        ,
                                           "PQRSTPQRST"                                   ,
                                           "PQRSTPQRSTPQRST"                              ,
                                           "PQRSTPQRSTPQRSTPQRST"                         ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRST"                    ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRST"               ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST"          ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST"     ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST"
            };

char LabelRankFont::RANK_INF[] = "UVWXYZ";

enum {
    RANKFONT_PROG_NOMALDISP = 1,
    RANKFONT_PROG_RANKUP       ,
};

void LabelRankFont::cnvRankStr(int prm_rank, char* out) {
    out[0] = '\0';
    if (prm_rank <= 0) {
        strcat(out, "");
        return;
    }
    if (prm_rank > 100000) {
        strcat(out, RANK_INF);
        return;
    }
    int idx_rank_10000thDeg = prm_rank/10000;
    if (idx_rank_10000thDeg > 0) {
        strcat(out, RANK_10000thDeg[idx_rank_10000thDeg]);
        prm_rank -= idx_rank_10000thDeg*10000;
    }
    int idx_rank_1000thDeg = prm_rank/1000;
    if (idx_rank_1000thDeg > 0) {
        strcat(out, RANK_1000thDeg[idx_rank_1000thDeg]);
        prm_rank -= idx_rank_1000thDeg*1000;
    }
    int idx_rank_100thDeg = prm_rank/100;
    if (idx_rank_100thDeg > 0) {
        strcat(out, RANK_100thDeg[idx_rank_100thDeg]);
        prm_rank -= idx_rank_100thDeg*100;
    }
    int idx_rank_10thDeg = prm_rank/10;
    if (idx_rank_10thDeg > 0) {
        strcat(out, RANK_10thDeg[idx_rank_10thDeg]);
        prm_rank -= idx_rank_10thDeg*10;
    }
    int idx_rank_1stDeg = prm_rank;
    if (idx_rank_1stDeg > 0) {
        strcat(out, RANK_1stDeg[idx_rank_1stDeg]);
        prm_rank -= idx_rank_1stDeg;
    }

//    1     !    10   #$    100    -./    1000     ,-./    10000                                         PQRST
//    2    !!    20   %&    200    012    2000     @ABC    20000                                    PQRSTPQRST
//    3   !!!    30   '(    300    345    3000     DEFG    30000                               PQRSTPQRSTPQRST
//    4  !!!!    40   )*    400    678    4000     HIJK    40000                          PQRSTPQRSTPQRSTPQRST
//    5     "    50   +,    500    9:;    5000     LMNO    50000                     PQRSTPQRSTPQRSTPQRSTPQRST
//    6    "!    60 +,#$    600 9:;-./    6000 LMNO,-./    60000                PQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//    7   "!!    70 +,%&    700 9:;012    7000 LMNO@ABC    70000           PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//    8  "!!!    80 +,'(    800 9:;345    8000 LMNODEFG    80000      PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//    9 "!!!!    90 +,)*    900 9:;678    9000 LMNOHIJK    90000 PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//無限大 UVWXYZ
}


LabelRankFont::LabelRankFont(const char* prm_name) :
        StringBoardActor(prm_name, "RankFont")
{
    _class_name = "LabelRankFont";
    useProgress(RANKFONT_PROG_RANKUP);
}

void LabelRankFont::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.01, 0.5, 5.0);
    _pModel->_pTextureBlinker->setBlink(1.0);
}

void LabelRankFont::initialize() {
    _rank = (int)(_RANK_*1000000);
    _tmp_rank = _rank;
    _pProg->set(RANKFONT_PROG_NOMALDISP);
    _draw_string = _buf;
}

void LabelRankFont::processBehavior() {
    if (GgafDx9Input::isPushedDownKey(DIK_R)) {
        _RANK_+=0.0001;
    }

    _rank = (int)(_RANK_*100000);
    if (_rank > _tmp_rank) {
        cnvRankStr(_rank, _draw_string);
        _len = strlen(_draw_string);
        _len_pack_num = _len/_pBoardSetModel->_set_num;
        _remainder_len = _len%_pBoardSetModel->_set_num;
        _pProg->set(RANKFONT_PROG_RANKUP);
        _tmp_rank = _rank;
    }


    switch (_pProg->get()) {
        case RANKFONT_PROG_NOMALDISP: {
            if (_pProg->isJustChanged()) {
                _pModel->_pTextureBlinker->intoTargetBlinkLinerUntil(1.0, 5);
            }
            break;
        }

        case RANKFONT_PROG_RANKUP: {
            if (_pProg->isJustChanged()) {
                _pModel->_pTextureBlinker->beat(10, 10, 1, 3);
            }
            if (_pModel->_pTextureBlinker->_method == NOBLINK) {
                _pProg->change(RANKFONT_PROG_NOMALDISP);
            }
            break;
        }
        default:
            break;
    }
}

void LabelRankFont::processDraw() {
    if (_len == 0) {
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;

    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[0], float(cnvCoordApp2Pix(_Y)));
    checkDxException(hr, D3D_OK, "LabelRankFont::processDraw SetFloat(_ahTransformedY) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[0], float(cnvCoordApp2Pix(_Z)));
    checkDxException(hr, D3D_OK, "LabelRankFont::processDraw SetFloat(_ahDepthZ) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[0], _fAlpha);
    checkDxException(hr, D3D_OK, "LabelRankFont::processDraw SetFloat(_ahAlpha) に失敗しました。");
    int strindex, pattno;
    pixcoord x = cnvCoordApp2Pix(_X) - (_chr_width_px * _len); //右詰にするため _chr_width_px*_len をマイナス
    float u,v;
    for (int pack = 0; pack < _len_pack_num+(_remainder_len == 0 ? 0 : 1); pack++) {
        _draw_set_num = pack < _len_pack_num ? _pBoardSetModel->_set_num : _remainder_len;
        for (int i = 0; i < _draw_set_num; i++) {
            strindex = pack * _pBoardSetModel->_set_num + i;
            if (_draw_string[strindex] == '\0') {
                break;
            } else if (_draw_string[strindex] - ' ' < 0) {
                pattno = '?' - ' '; //範囲外は"?"を表示
            } else {
                pattno = _draw_string[strindex] - ' '; //通常文字列
            }
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], float(x));
            checkDxException(hr, D3D_OK, "LabelRankFont::processDraw SetFloat(_ahTransformedX) に失敗しました。");
            _pUvFlipper->getUV(pattno, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], u);
            checkDxException(hr, D3D_OK, "LabelRankFont::processDraw SetFloat(_hOffsetU) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], v);
            checkDxException(hr, D3D_OK, "LabelRankFont::processDraw SetFloat(_hOffsetV) に失敗しました。");
            x += _chr_width_px;
        }
        _pBoardSetModel->draw(this, _draw_set_num);
    }
}

LabelRankFont::~LabelRankFont() {
}

