#include "LabelRankFont.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

char LabelRankFont::RANK_1stDeg[][6] = {
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

char LabelRankFont::RANK_10thDeg[][5] = {
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

char LabelRankFont::RANK_100thDeg[][7] = {
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



char LabelRankFont::RANK_1000thDeg[][9] = {
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


char LabelRankFont::RANK_10000thDeg[][46] = {
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



LabelRankFont::LabelRankFont(const char* prm_name) :
        FontBoardActor(prm_name, "70/RankFont")
{
    _class_name = "LabelRankFont";
    tmp_rank_ = 0;
    getAlphaFader()->setRange(0.0, 1.0);
    setAlign(ALIGN_RIGHT, VALIGN_BOTTOM);
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_RANK_UP, "WAVE_RANK_UP");
}

void LabelRankFont::onCreateModel() {
}

void LabelRankFont::initialize() {
    tmp_rank_ = G_RANK_DISP;
}

void LabelRankFont::processBehavior() {
    int rank_level = G_RANK_DISP;
    if (rank_level != tmp_rank_) {
        //ランクアップ！
        char c[65];
        cnvRankStr(rank_level, c);
        update(c);
        tmp_rank_ = rank_level;
        getSeTransmitter()->play(SE_RANK_UP);
        getAlphaFader()->rbeat(20, 10, 0, 10, 3);
    }
    getAlphaFader()->behave();
}

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
        strcat(out, LabelRankFont::RANK_10000thDeg[idx_rank_10000thDeg]);
        prm_rank -= idx_rank_10000thDeg*10000;
    }
    int idx_rank_1000thDeg = prm_rank/1000;
    if (idx_rank_1000thDeg > 0) {
        strcat(out, LabelRankFont::RANK_1000thDeg[idx_rank_1000thDeg]);
        prm_rank -= idx_rank_1000thDeg*1000;
    }
    int idx_rank_100thDeg = prm_rank/100;
    if (idx_rank_100thDeg > 0) {
        strcat(out, LabelRankFont::RANK_100thDeg[idx_rank_100thDeg]);
        prm_rank -= idx_rank_100thDeg*100;
    }
    int idx_rank_10thDeg = prm_rank/10;
    if (idx_rank_10thDeg > 0) {
        strcat(out, LabelRankFont::RANK_10thDeg[idx_rank_10thDeg]);
        prm_rank -= idx_rank_10thDeg*10;
    }
    int idx_rank_1stDeg = prm_rank;
    if (idx_rank_1stDeg > 0) {
        strcat(out, LabelRankFont::RANK_1stDeg[idx_rank_1stDeg]);
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
//
//最大値 99999=PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTLMNOHIJK9:;678+,)*"!!!!
//無限大 UVWXYZ
}

LabelRankFont::~LabelRankFont() {
}

