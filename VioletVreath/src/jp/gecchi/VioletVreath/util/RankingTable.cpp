#include "RankingTable.h"

#include <Shlwapi.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

RankingTable::RankingTable() : GgafCore::Table() {
}

void RankingTable::init() {
    if (PathFileExists(RANKINGTABLE_DATA_FILE) ) {
        importFromFile(RANKINGTABLE_DATA_FILE);
    } else {
        std::string default_name = std::string(RANKINGTABLE_NAME_LEN, '.');
        for (int i = 0; i < RANKINGTABLE_RECORD_NUM; i++) {
            addRow(default_name, (i+1)*1000);
        }
    }
    sort();
}

void RankingTable::addRow(std::string& prm_name, int prm_score) {
    GgafCore::Record* r = NEW GgafCore::Record();
    (*r)["NAME"]    = prm_name;
    (*r)["SCORE"]   = UTIL::padZeroStr(prm_score, RANKINGTABLE_SCORELEN);
    (*r)["REGDATE"] = UTIL::getSystemDateTimeStr();
    GgafCore::Table::addRow(r);
}

void RankingTable::sort() {
    sortDescBy("SCORE","REGDATE",false);
    if (getCount() > RANKINGTABLE_RECORD_NUM) {
        removeRows(RANKINGTABLE_RECORD_NUM);
    }
}

bool RankingTable::isRankIn(int prm_score) {
    std::string str_last_score = getVal("SCORE", getCount()-1);  //現在のハイスコアの最低スコア
    int last_score = STOI(str_last_score);
    if (prm_score > last_score) {
        return true;
    } else {
        return false;
    }
}

void RankingTable::save() {
    exportToFile(RANKINGTABLE_DATA_FILE);
}

RankingTable::~RankingTable() {
}
