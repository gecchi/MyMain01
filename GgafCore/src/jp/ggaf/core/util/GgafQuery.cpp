#include "stdafx.h"

using namespace GgafCore;

GgafQuery::GgafQuery() : GgafCore::GgafObject() {
}

void GgafQuery::importFromFile(std::string prm_file_name) {
    std::ifstream ifs(prm_file_name.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("GgafQuery "<<prm_file_name<<" が開けません");
    }
    GgafRecord* r;
    std::string line; // ファイルから読み込んだテキストを入れる
    int n = 0;
    std::vector<std::string> header;
    int header_num = 0;
    while (getline(ifs, line)) { // 一行ずつ読み込み
        if (line.length() < 1) {
            //空行は飛ばす
            continue;
        }
        if (n == 0) {
            //ヘッダ行として読み込む
            header = GgafQuery::split(line);
            header_num = header.size();
            n++;
            continue;
        } else {
            r = NEW GgafRecord();
            //通常データ行
            std::vector<std::string> data = GgafQuery::split(line);
            for (int j = 0; j < header_num; j++) {
                r->insert( GgafRecord::value_type( header[j], data[j]) );
            }
            addRow(r);
            n++;
        }
    }
}

void GgafQuery::exportToFile(std::string prm_file_name) {
#ifdef MY_DEBUG
    if (getCount() == 0) {
        _TRACE_("GgafQuery#exportToFile: 書きだすデータがありません");
    }
#endif
    std::ofstream ofs(prm_file_name.c_str());
    int header_num = _lstTtable[0]->size();
    std::string* header = NEW std::string[header_num];

    for (int i = 0; i < (int)getCount(); i++) {
        GgafRecord* r = _lstTtable[i];
        if (i == 0) {
            //ヘッダ文字列出力
            int c = 0;
            GgafRecord::iterator it = r->begin();
            while( it != r->end() ) {
                if (it == r->begin()) {
                    ofs << ((*it).first);
                } else {
                    ofs << "\t" << ((*it).first);
                }
                header[c] = (*it).first;
                ++it; c++;
            }
            ofs << std::endl;
        }

        for (int j = 0; j < header_num; j++) {
            if (j == 0) {
                ofs << (*r)[header[j]];
            } else {
                ofs << "\t" << (*r)[header[j]];
            }
        }
        ofs << std::endl;
    }

    GGAF_DELETEARR(header);
}

size_t GgafQuery::getCount() {
    return _lstTtable.size();
}

bool GgafQuery::hasRecord() {
    if (getCount() == 0) {
        return false;
    } else {
        return true;
    }
}

std::string GgafQuery::getVal(std::string& prm_col, int prm_index) {
    GgafRecord* r = _lstTtable[prm_index];
    if (0 < r->count(prm_col)) {
        return ((*r)[prm_col]);
    } else {
        return "";
    }
}
std::string GgafQuery::getVal(const char* prm_col, int prm_index) {
    GgafRecord* r = _lstTtable[prm_index];
    if (0 < r->count(prm_col)) {
        return ((*r)[prm_col]);
    } else {
        return "";
    }
}

void GgafQuery::setVal(std::string& prm_col, int prm_index, std::string& prm_val) {
    GgafRecord* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}
void GgafQuery::setVal(const char* prm_col, int prm_index, std::string& prm_val) {
    GgafRecord* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}
void GgafQuery::setVal(std::string& prm_col, int prm_index, const char* prm_val) {
    GgafRecord* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}
void GgafQuery::setVal(const char* prm_col, int prm_index, const char* prm_val) {
    GgafRecord* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}

GgafRecord* GgafQuery::getRecord(int prm_index) {
    return _lstTtable[prm_index];
}

void GgafQuery::removeRow(int prm_index) {
#ifdef MY_DEBUG
    if (_lstTtable.size() < prm_index) {
        throwGgafCriticalException(
                "GgafQuery#removeRow: 削除レコードINDEXは存在しません。本クエリsize="<<_lstTtable.size()<<"/引数の削除INDEX="<<prm_index);
    }
#endif
    //TODO:ここでDELETEしないといけない
    GgafRecord* r = _lstTtable[prm_index];
    GGAF_DELETE(r);
    _lstTtable.erase(_lstTtable.begin() + prm_index);
}
void GgafQuery::removeRows(int prm_start_index) {
    removeRows(prm_start_index, getCount()-1);
}
void GgafQuery::removeRows(int prm_start_index, int prm_end_index) {
#ifdef MY_DEBUG
    if (_lstTtable.size() < prm_start_index) {
        throwGgafCriticalException(
                "GgafQuery#removeRows: 削除レコードINDEXは存在しません。本クエリsize="<<_lstTtable.size()<<"/引数prm_start_index="<<prm_start_index);
    }
    if (_lstTtable.size() < prm_end_index) {
        throwGgafCriticalException(
                "GgafQuery#removeRows: 削除レコードINDEXは存在しません。本クエリsize="<<_lstTtable.size()<<"/引数prm_end_index="<<prm_end_index);
    }
#endif
    for (int i = prm_start_index; i <= prm_end_index; i++) {
        GgafRecord* r = _lstTtable[i];
        GGAF_DELETE(r);
    }
    _lstTtable.erase(_lstTtable.begin() + prm_start_index, _lstTtable.begin() + (prm_end_index + 1)); //+1は正しい。
}

void GgafQuery::addRow(GgafRecord* prm_pRow) {
    _lstTtable.push_back(prm_pRow);
}

void GgafQuery::swapIndex(int prm_index_A, int prm_index_B) {
    GgafRecord* pRecordA = _lstTtable[prm_index_A];
    _lstTtable[prm_index_A] = _lstTtable[prm_index_B];
    _lstTtable[prm_index_B] = pRecordA;
}

void GgafQuery::sortBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index, bool prm_blank_is_max) {
    if (prm_begin_index < prm_end_index) {
        GgafRecord* pPivotRecord = _lstTtable[(prm_begin_index + prm_end_index) / 2];
        _lstTtable[(prm_begin_index + prm_end_index) / 2] = _lstTtable[prm_begin_index];
        int p = prm_begin_index;
        bool compFlg;
        const char* val;
        const char* pivot_val;
        for (int i = prm_begin_index + 1; i <= prm_end_index; i++) {
            compFlg = false;
            for (int j = 0; j < prm_col_num;) {
                val = ((*(_lstTtable[i]))[prm_col[j]]).c_str();
                pivot_val = ((*pPivotRecord)[prm_col[j]]).c_str();
                if (*val != '\0' && *pivot_val != '\0') {
                    if (strcmp(val, pivot_val) < 0) {
                        compFlg = true;
                        break;
                    } else if (strcmp(val, pivot_val) == 0) {
                        j++;
                        continue;
                    } else {
                        compFlg = false;
                        break;
                    }
                } else {
                    if (*val == *pivot_val) {
                        j++;
                        continue;
                    } else if (*val == '\0') {
                        if (prm_blank_is_max) {
                            compFlg = false;
                        } else {
                            compFlg = true;
                        }
                        break;
                    } else if (*pivot_val == '\0') {
                        if (prm_blank_is_max) {
                            compFlg = true;
                        } else {
                            compFlg = false;
                        }

                        break;
                    }
                }
            }
            if (compFlg) {
                p = p + 1;
                swapIndex(p, i);
            }
        }
        _lstTtable[prm_begin_index] = _lstTtable[p];
        _lstTtable[p] = pPivotRecord;
        sortBy(prm_col, prm_col_num, prm_begin_index, p - 1, prm_blank_is_max);
        sortBy(prm_col, prm_col_num, p + 1, prm_end_index, prm_blank_is_max);
    }
}

void GgafQuery::sortBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max) {
    if (getCount() > 0) {
        sortBy(prm_col, prm_col_num, 0, _lstTtable.size() - 1, prm_blank_is_max);
    }
}

void GgafQuery::sortBy(const char* prm_col, bool prm_blank_is_max) {
    std::string col[1] = { prm_col };
    sortBy(col, 1, prm_blank_is_max);
}

void GgafQuery::sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max) {
    std::string col[2] = { prm_col1, prm_col2 };
    sortBy(col, 2, prm_blank_is_max);
}

void GgafQuery::sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max) {
    std::string col[3] = { prm_col1, prm_col2, prm_col3 };
    sortBy(col, 3, prm_blank_is_max);
}
void GgafQuery::sortDescBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
                bool prm_blank_is_max) {
    if (prm_begin_index < prm_end_index) {
        GgafRecord* pPivotRecord = _lstTtable[(prm_begin_index + prm_end_index) / 2];
        _lstTtable[(prm_begin_index + prm_end_index) / 2] = _lstTtable[prm_begin_index];
        int p = prm_begin_index;
        bool compFlg;
        const char* val;
        const char* pivot_val;
        for (int i = prm_begin_index + 1; i <= prm_end_index; i++) {
            compFlg = false;
            for (int j = 0; j < prm_col_num;) {
                val = ((*(_lstTtable[i]))[prm_col[j]]).c_str();
                pivot_val = ((*pPivotRecord)[prm_col[j]]).c_str();
                if (*val != '\0' && *pivot_val != '\0') {
                    if (strcmp(val, pivot_val) < 0) {
                        compFlg = false;
                        break;
                    } else if (strcmp(val, pivot_val) == 0) {
                        j++;
                        continue;
                    } else {
                        compFlg = true;
                        break;
                    }
                } else {
                    if (*val == *pivot_val) {
                        j++;
                        continue;
                    } else if (*val == '\0') {
                        if (prm_blank_is_max) {
                            compFlg = true;
                        } else {
                            compFlg = false;
                        }
                        break;
                    } else if (*pivot_val == '\0') {
                        if (prm_blank_is_max) {
                            compFlg = false;
                        } else {
                            compFlg = true;
                        }

                        break;
                    }
                }
            }
            if (compFlg) {
                p = p + 1;
                swapIndex(p, i);
            }
        }
        _lstTtable[prm_begin_index] = _lstTtable[p];
        _lstTtable[p] = pPivotRecord;
        sortDescBy(prm_col, prm_col_num, prm_begin_index, p - 1, prm_blank_is_max);
        sortDescBy(prm_col, prm_col_num, p + 1, prm_end_index, prm_blank_is_max);
    }
}

void GgafQuery::sortDescBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max) {
    if (getCount() > 0) {
        sortDescBy(prm_col, prm_col_num, 0, _lstTtable.size() - 1, prm_blank_is_max);
    }
}

void GgafQuery::sortDescBy(const char* prm_col, bool prm_blank_is_max) {
    std::string col[1] = { prm_col };
    sortDescBy(col, 1, prm_blank_is_max);
}

void GgafQuery::sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max) {
    std::string col[2] = { prm_col1, prm_col2 };
    sortDescBy(col, 2, prm_blank_is_max);
}

void GgafQuery::sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max) {
    std::string col[3] = { prm_col1, prm_col2, prm_col3 };
    sortDescBy(col, 3, prm_blank_is_max);
}

void GgafQuery::dump() {
    for (int i = 0; i < (int)_lstTtable.size(); i++) {
        GgafRecord* r = _lstTtable[i];
        _TEXT_("["<<i<<"]=");
        GgafRecord::iterator it = r->begin();
        while (it != r->end()) {
            _TEXT_("\""<<(*it).first << "\"=>\"" << (*it).second<<"\"\t");
            ++it;
        }
        _TEXT_("\n");
    }
}

GgafQuery::~GgafQuery() {
    for (int i = 0; i < (int)getCount(); i++) {
        GgafRecord* r = _lstTtable[i];
        GGAF_DELETE(r);
    }
}


