#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


QueryRanking::QueryRanking() : GgafQuery() {
}
void QueryRanking::init() {
    if (PathFileExists(QUERYRANKING_FILE) ) {
        importFromFile(QUERYRANKING_FILE);
    } else {
        std::string default_name = std::string(QUERYRANKING_NAME_LEN, '.');
        for (int i = 0; i < QUERYRANKING_RECORD_NUM; i++) {
            addRow(default_name, (i+1)*1000);
        }
    }
    sort();
}

void QueryRanking::addRow(std::string& prm_name, int prm_score) {
    GgafRecord* r = NEW GgafRecord();
    (*r)["NAME"]    = prm_name;
    (*r)["SCORE"]   = UTIL::padZeroStr(prm_score, QUERYRANKING_SCORE_LEN);
    (*r)["REGDATE"] = UTIL::getSystemDateTimeStr();
    GgafQuery::addRow(r);
}

void QueryRanking::sort() {
    sortDescBy("SCORE","DATE",false);
    if (getCount() > QUERYRANKING_RECORD_NUM) {
        removeRows(QUERYRANKING_RECORD_NUM);
    }
}

bool QueryRanking::isRankIn(int prm_score) {
    std::string str_last_score = getVal("SCORE", getCount()-1);  //現在のハイスコアの最低スコア
    int last_score = STOI(str_last_score);
    if (prm_score > last_score) {
        return true;
    } else {
        return false;
    }
}

void QueryRanking::save() {
    exportToFile(QUERYRANKING_FILE);
}

QueryRanking::~QueryRanking() {
}
