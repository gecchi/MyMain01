#include "jp/ggaf/core/util/Table.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include <fstream>
#include <cstring>

using namespace GgafCore;

Table::Table() : Object() {
}

void Table::importFromFile(std::string prm_file_name) {
    std::ifstream ifs(prm_file_name.c_str());
    if (ifs.fail()) {
        throwCriticalException("Table "<<prm_file_name<<" が開けません");
    }
    Record* r;
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
            header = Table::split(line);
            header_num = header.size();
            n++;
            continue;
        } else {
            r = NEW Record();
            //通常データ行
            std::vector<std::string> data = Table::split(line);
            for (int j = 0; j < header_num; j++) {
                r->insert( Record::value_type( header[j], data[j]) );
            }
            addRow(r);
            n++;
        }
    }
}

void Table::exportToFile(std::string prm_file_name) {
#ifdef MY_DEBUG
    if (getCount() == 0) {
        _TRACE_("Table#exportToFile: 書きだすデータがありません");
    }
#endif
    std::ofstream ofs(prm_file_name.c_str());
    int header_num = _lstTtable[0]->size();
    std::string* header = NEW std::string[header_num];

    for (int i = 0; i < (int)getCount(); i++) {
        Record* r = _lstTtable[i];
        if (i == 0) {
            //ヘッダ文字列出力
            int c = 0;
            Record::iterator it = r->begin();
            while ( it != r->end() ) {
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

size_t Table::getCount() const {
    return _lstTtable.size();
}

bool Table::hasRecord() const {
    if (getCount() == 0) {
        return false;
    } else {
        return true;
    }
}

std::string Table::getVal(std::string& prm_col, int prm_index) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwCriticalException("Table#getVal: レコードインデックス prm_index="<<prm_index<<" が、存在しません");
    }
#endif
    Record* r = _lstTtable[prm_index];
    if (0 < r->count(prm_col)) {
        return ((*r)[prm_col]);
    } else {
        return "";
    }
}
std::string Table::getVal(const char* prm_col, int prm_index) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwCriticalException("Table#getVal: レコードインデックス prm_index="<<prm_index<<" が、存在しません");
    }
#endif
    Record* r = _lstTtable[prm_index];
    if (0 < r->count(prm_col)) {
        return ((*r)[prm_col]);
    } else {
        return "";
    }
}

void Table::setVal(std::string& prm_col, int prm_index, std::string& prm_val) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwCriticalException("Table#setVal: レコードインデックス prm_index="<<prm_index<<" が、存在しません");
    }
#endif
    Record* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}
void Table::setVal(const char* prm_col, int prm_index, std::string& prm_val) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwCriticalException("Table#setVal: レコードインデックス prm_index="<<prm_index<<" が、存在しません");
    }
#endif
    Record* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}
void Table::setVal(std::string& prm_col, int prm_index, const char* prm_val) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwCriticalException("Table#setVal: レコードインデックス prm_index="<<prm_index<<" が、存在しません");
    }
#endif
    Record* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}
void Table::setVal(const char* prm_col, int prm_index, const char* prm_val) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwCriticalException("Table#setVal: レコードインデックス prm_index="<<prm_index<<" が、存在しません");
    }
#endif
    Record* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}

Record* Table::getRecord(int prm_index) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwCriticalException("Table#getRecord: レコードインデックス prm_index="<<prm_index<<" が、存在しません");
    }
#endif
    return _lstTtable[prm_index];
}

void Table::removeRow(int prm_index) {
#ifdef MY_DEBUG
    if ((int)(_lstTtable.size()) < prm_index) {
        throwCriticalException(
                "Table#removeRow: 削除レコードINDEXは存在しません。本クエリsize="<<_lstTtable.size()<<"/引数の削除INDEX="<<prm_index);
    }
#endif
    //TODO:ここでDELETEしないといけない
    Record* r = _lstTtable[prm_index];
    GGAF_DELETE(r);
    _lstTtable.erase(_lstTtable.begin() + prm_index);
}
void Table::removeRows(int prm_start_index) {
    removeRows(prm_start_index, getCount()-1);
}
void Table::removeRows(int prm_start_index, int prm_end_index) {
#ifdef MY_DEBUG
    if ((int)(_lstTtable.size()) < prm_start_index) {
        throwCriticalException(
                "Table#removeRows: 削除レコードINDEXは存在しません。本クエリsize="<<_lstTtable.size()<<"/引数prm_start_index="<<prm_start_index);
    }
    if ((int)(_lstTtable.size()) < prm_end_index) {
        throwCriticalException(
                "Table#removeRows: 削除レコードINDEXは存在しません。本クエリsize="<<_lstTtable.size()<<"/引数prm_end_index="<<prm_end_index);
    }
#endif
    for (int i = prm_start_index; i <= prm_end_index; i++) {
        Record* r = _lstTtable[i];
        GGAF_DELETE(r);
    }
    _lstTtable.erase(_lstTtable.begin() + prm_start_index, _lstTtable.begin() + (prm_end_index + 1)); //+1は正しい。
}

void Table::addRow(Record* prm_pRow) {
    _lstTtable.push_back(prm_pRow);
}

void Table::addNewRow() {
    Record* pRow = NEW Record();
    _lstTtable.push_back(pRow);
}


void Table::swapIndex(int prm_index_A, int prm_index_B) {
    Record* pRecordA = _lstTtable[prm_index_A];
    _lstTtable[prm_index_A] = _lstTtable[prm_index_B];
    _lstTtable[prm_index_B] = pRecordA;
}

void Table::sortBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index, bool prm_blank_is_max) {
    if (prm_begin_index < prm_end_index) {
        Record* pPivotRecord = _lstTtable[(prm_begin_index + prm_end_index) / 2];
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

void Table::sortBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max) {
    if (getCount() > 0) {
        sortBy(prm_col, prm_col_num, 0, _lstTtable.size() - 1, prm_blank_is_max);
    }
}

void Table::sortBy(const char* prm_col, bool prm_blank_is_max) {
    std::string col[1] = { prm_col };
    sortBy(col, 1, prm_blank_is_max);
}

void Table::sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max) {
    std::string col[2] = { prm_col1, prm_col2 };
    sortBy(col, 2, prm_blank_is_max);
}

void Table::sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max) {
    std::string col[3] = { prm_col1, prm_col2, prm_col3 };
    sortBy(col, 3, prm_blank_is_max);
}
void Table::sortDescBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
                bool prm_blank_is_max) {
    if (prm_begin_index < prm_end_index) {
        Record* pPivotRecord = _lstTtable[(prm_begin_index + prm_end_index) / 2];
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

void Table::sortDescBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max) {
    if (getCount() > 0) {
        sortDescBy(prm_col, prm_col_num, 0, _lstTtable.size() - 1, prm_blank_is_max);
    }
}

void Table::sortDescBy(const char* prm_col, bool prm_blank_is_max) {
    std::string col[1] = { prm_col };
    sortDescBy(col, 1, prm_blank_is_max);
}

void Table::sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max) {
    std::string col[2] = { prm_col1, prm_col2 };
    sortDescBy(col, 2, prm_blank_is_max);
}

void Table::sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max) {
    std::string col[3] = { prm_col1, prm_col2, prm_col3 };
    sortDescBy(col, 3, prm_blank_is_max);
}

void Table::dump() {
    for (int i = 0; i < (int)_lstTtable.size(); i++) {
        Record* r = _lstTtable[i];
        _TRACE_N_("["<<i<<"]=");
        Record::iterator it = r->begin();
        while (it != r->end()) {
            _TRACE_N_("\""<<(*it).first << "\"=>\"" << (*it).second<<"\"\t");
            ++it;
        }
        _TRACE_N_("\n");
    }
}

Table::~Table() {
    for (int i = 0; i < (int)getCount(); i++) {
        Record* r = _lstTtable[i];
        GGAF_DELETE(r);
    }
}


