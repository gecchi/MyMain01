#include "stdafx.h"
#include "jp/ggaf/core/util/GgafTable.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include <fstream>
#include <cstring>


using namespace GgafCore;

GgafTable::GgafTable() : GgafObject() {
}

void GgafTable::importFromFile(std::string prm_file_name) {
    std::ifstream ifs(prm_file_name.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("GgafTable "<<prm_file_name<<" ���J���܂���");
    }
    GgafRecord* r;
    std::string line; // �t�@�C������ǂݍ��񂾃e�L�X�g������
    int n = 0;
    std::vector<std::string> header;
    int header_num = 0;
    while (getline(ifs, line)) { // ��s���ǂݍ���
        if (line.length() < 1) {
            //��s�͔�΂�
            continue;
        }
        if (n == 0) {
            //�w�b�_�s�Ƃ��ēǂݍ���
            header = GgafTable::split(line);
            header_num = header.size();
            n++;
            continue;
        } else {
            r = NEW GgafRecord();
            //�ʏ�f�[�^�s
            std::vector<std::string> data = GgafTable::split(line);
            for (int j = 0; j < header_num; j++) {
                r->insert( GgafRecord::value_type( header[j], data[j]) );
            }
            addRow(r);
            n++;
        }
    }
}

void GgafTable::exportToFile(std::string prm_file_name) {
#ifdef MY_DEBUG
    if (getCount() == 0) {
        _TRACE_("GgafTable#exportToFile: ���������f�[�^������܂���");
    }
#endif
    std::ofstream ofs(prm_file_name.c_str());
    int header_num = _lstTtable[0]->size();
    std::string* header = NEW std::string[header_num];

    for (int i = 0; i < (int)getCount(); i++) {
        GgafRecord* r = _lstTtable[i];
        if (i == 0) {
            //�w�b�_������o��
            int c = 0;
            GgafRecord::iterator it = r->begin();
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

size_t GgafTable::getCount() {
    return _lstTtable.size();
}

bool GgafTable::hasRecord() {
    if (getCount() == 0) {
        return false;
    } else {
        return true;
    }
}

std::string GgafTable::getVal(std::string& prm_col, int prm_index) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwGgafCriticalException("GgafTable#getVal: ���R�[�h�C���f�b�N�X prm_index="<<prm_index<<" ���A���݂��܂���");
    }
#endif
    GgafRecord* r = _lstTtable[prm_index];
    if (0 < r->count(prm_col)) {
        return ((*r)[prm_col]);
    } else {
        return "";
    }
}
std::string GgafTable::getVal(const char* prm_col, int prm_index) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwGgafCriticalException("GgafTable#getVal: ���R�[�h�C���f�b�N�X prm_index="<<prm_index<<" ���A���݂��܂���");
    }
#endif
    GgafRecord* r = _lstTtable[prm_index];
    if (0 < r->count(prm_col)) {
        return ((*r)[prm_col]);
    } else {
        return "";
    }
}

void GgafTable::setVal(std::string& prm_col, int prm_index, std::string& prm_val) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwGgafCriticalException("GgafTable#setVal: ���R�[�h�C���f�b�N�X prm_index="<<prm_index<<" ���A���݂��܂���");
    }
#endif
    GgafRecord* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}
void GgafTable::setVal(const char* prm_col, int prm_index, std::string& prm_val) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwGgafCriticalException("GgafTable#setVal: ���R�[�h�C���f�b�N�X prm_index="<<prm_index<<" ���A���݂��܂���");
    }
#endif
    GgafRecord* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}
void GgafTable::setVal(std::string& prm_col, int prm_index, const char* prm_val) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwGgafCriticalException("GgafTable#setVal: ���R�[�h�C���f�b�N�X prm_index="<<prm_index<<" ���A���݂��܂���");
    }
#endif
    GgafRecord* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}
void GgafTable::setVal(const char* prm_col, int prm_index, const char* prm_val) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwGgafCriticalException("GgafTable#setVal: ���R�[�h�C���f�b�N�X prm_index="<<prm_index<<" ���A���݂��܂���");
    }
#endif
    GgafRecord* r = _lstTtable[prm_index];
    (*r)[prm_col] = prm_val;
}

GgafRecord* GgafTable::getRecord(int prm_index) {
#ifdef MY_DEBUG
    if (((int)getCount()) < prm_index+1) {
        throwGgafCriticalException("GgafTable#getRecord: ���R�[�h�C���f�b�N�X prm_index="<<prm_index<<" ���A���݂��܂���");
    }
#endif
    return _lstTtable[prm_index];
}

void GgafTable::removeRow(int prm_index) {
#ifdef MY_DEBUG
    if ((int)(_lstTtable.size()) < prm_index) {
        throwGgafCriticalException(
                "GgafTable#removeRow: �폜���R�[�hINDEX�͑��݂��܂���B�{�N�G��size="<<_lstTtable.size()<<"/�����̍폜INDEX="<<prm_index);
    }
#endif
    //TODO:������DELETE���Ȃ��Ƃ����Ȃ�
    GgafRecord* r = _lstTtable[prm_index];
    GGAF_DELETE(r);
    _lstTtable.erase(_lstTtable.begin() + prm_index);
}
void GgafTable::removeRows(int prm_start_index) {
    removeRows(prm_start_index, getCount()-1);
}
void GgafTable::removeRows(int prm_start_index, int prm_end_index) {
#ifdef MY_DEBUG
    if ((int)(_lstTtable.size()) < prm_start_index) {
        throwGgafCriticalException(
                "GgafTable#removeRows: �폜���R�[�hINDEX�͑��݂��܂���B�{�N�G��size="<<_lstTtable.size()<<"/����prm_start_index="<<prm_start_index);
    }
    if ((int)(_lstTtable.size()) < prm_end_index) {
        throwGgafCriticalException(
                "GgafTable#removeRows: �폜���R�[�hINDEX�͑��݂��܂���B�{�N�G��size="<<_lstTtable.size()<<"/����prm_end_index="<<prm_end_index);
    }
#endif
    for (int i = prm_start_index; i <= prm_end_index; i++) {
        GgafRecord* r = _lstTtable[i];
        GGAF_DELETE(r);
    }
    _lstTtable.erase(_lstTtable.begin() + prm_start_index, _lstTtable.begin() + (prm_end_index + 1)); //+1�͐������B
}

void GgafTable::addRow(GgafRecord* prm_pRow) {
    _lstTtable.push_back(prm_pRow);
}

void GgafTable::addNewRow() {
    GgafRecord* pRow = NEW GgafRecord();
    _lstTtable.push_back(pRow);
}


void GgafTable::swapIndex(int prm_index_A, int prm_index_B) {
    GgafRecord* pRecordA = _lstTtable[prm_index_A];
    _lstTtable[prm_index_A] = _lstTtable[prm_index_B];
    _lstTtable[prm_index_B] = pRecordA;
}

void GgafTable::sortBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index, bool prm_blank_is_max) {
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

void GgafTable::sortBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max) {
    if (getCount() > 0) {
        sortBy(prm_col, prm_col_num, 0, _lstTtable.size() - 1, prm_blank_is_max);
    }
}

void GgafTable::sortBy(const char* prm_col, bool prm_blank_is_max) {
    std::string col[1] = { prm_col };
    sortBy(col, 1, prm_blank_is_max);
}

void GgafTable::sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max) {
    std::string col[2] = { prm_col1, prm_col2 };
    sortBy(col, 2, prm_blank_is_max);
}

void GgafTable::sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max) {
    std::string col[3] = { prm_col1, prm_col2, prm_col3 };
    sortBy(col, 3, prm_blank_is_max);
}
void GgafTable::sortDescBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
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

void GgafTable::sortDescBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max) {
    if (getCount() > 0) {
        sortDescBy(prm_col, prm_col_num, 0, _lstTtable.size() - 1, prm_blank_is_max);
    }
}

void GgafTable::sortDescBy(const char* prm_col, bool prm_blank_is_max) {
    std::string col[1] = { prm_col };
    sortDescBy(col, 1, prm_blank_is_max);
}

void GgafTable::sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max) {
    std::string col[2] = { prm_col1, prm_col2 };
    sortDescBy(col, 2, prm_blank_is_max);
}

void GgafTable::sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max) {
    std::string col[3] = { prm_col1, prm_col2, prm_col3 };
    sortDescBy(col, 3, prm_blank_is_max);
}

void GgafTable::dump() {
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

GgafTable::~GgafTable() {
    for (int i = 0; i < (int)getCount(); i++) {
        GgafRecord* r = _lstTtable[i];
        GGAF_DELETE(r);
    }
}


