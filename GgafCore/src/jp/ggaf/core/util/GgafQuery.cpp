#include "stdafx.h"

using namespace GgafCore;

GgafQuery::GgafQuery() : GgafCore::GgafObject() {
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

std::string GgafQuery::get(const char* prm_col, int prm_index) {
    GgafRecord* r = _lstTtable[prm_index];
    if (0 < r->count(prm_col)) {
        return ((*r)[prm_col]);
    } else {
        return "";
    }
}

GgafRecord* GgafQuery::getRecord(int prm_index) {
    return _lstTtable[prm_index];
}
/**
 * ���R�[�h���폜���܂��B .
 * @param prm_index ���R�[�hindex�i0�`)
 * @throws GwafInternalException �����̃��R�[�hindex���͈͊O
 */
void GgafQuery::removeRow(int prm_index) {
#ifdef MY_DEBUG
    if (_lstTtable.size() < prm_index) {
        throwGgafCriticalException(
                "GgafQuery#removeRow: �폜���R�[�hINDEX�͑��݂��܂���B�{�N�G��size="<<_lstTtable.size()<<"/�����̍폜INDEX="<<prm_index);
    }
#endif
    _lstTtable.erase(_lstTtable.begin() + prm_index);
}

void GgafQuery::removeRows(int prm_start_index, int prm_end_index) {
#ifdef MY_DEBUG
    if (_lstTtable.size() < prm_start_index) {
        throwGgafCriticalException(
                "GgafQuery#removeRows: �폜���R�[�hINDEX�͑��݂��܂���B�{�N�G��size="<<_lstTtable.size()<<"/����prm_start_index="<<prm_start_index);
    }
    if (_lstTtable.size() < prm_end_index) {
        throwGgafCriticalException(
                "GgafQuery#removeRows: �폜���R�[�hINDEX�͑��݂��܂���B�{�N�G��size="<<_lstTtable.size()<<"/����prm_end_index="<<prm_end_index);
    }
#endif
    _lstTtable.erase(_lstTtable.begin() + prm_start_index, _lstTtable.begin() + (prm_end_index + 1)); //+1�͐������B
}

void GgafQuery::addRow(GgafRecord* prm_pRow) {
    _lstTtable.push_back(prm_pRow);
}
/**
 * A��B�̃��R�[�h�̏ꏊ(INDEX)�����ւ��܂�. <BR>
 * @param prm_index_A ����ւ��Ώۃ��R�[�hINDEX A
 * @param prm_index_B ����ւ��Ώۃ��R�[�hINDEX B
 */
void GgafQuery::swapIndex(int prm_index_A, int prm_index_B) {
    GgafRecord* pRecordA = _lstTtable[prm_index_A];
    _lstTtable[prm_index_A] = _lstTtable[prm_index_B];
    _lstTtable[prm_index_B] = pRecordA;
}
/**
 * �����̗�̔z�񏇂̗v�f�l�ŁA�������R�[�h�������\�[�g�����וς��܂�. <BR>
 * �N�C�b�N�\�[�g�g�p�B<BR>
 * @param prm_col �����\�[�g���鏇�Ԃ̗񖼔z��
 * @param prm_col_num �񖼔z��v�f��
 * @param prm_begin_index �J�nINDEX
 * @param prm_end_index �I��INDEX
 * @param prm_blank_is_max true:�󕶎�("")���ő�l�Ƃ��܂��^false:�󕶎�("")���ŏ��l�Ƃ��܂��B
 */
void GgafQuery::sortBy(const char* prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index, bool prm_blank_is_max) {
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

void GgafQuery::sortBy(const char* prm_col[], int prm_col_num, bool prm_blank_is_max) {
    if (getCount() > 0) {
        sortBy(prm_col, prm_col_num, 0, _lstTtable.size() - 1, prm_blank_is_max);
    }
}

void GgafQuery::sortBy(const char* prm_col, bool prm_blank_is_max) {
    const char* col[1] = { prm_col };
    sortBy(col, 1, prm_blank_is_max);
}

void GgafQuery::sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max) {
    const char* col[2] = { prm_col1, prm_col2 };
    sortBy(col, 2, prm_blank_is_max);
}

void GgafQuery::sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max) {
    const char* col[3] = { prm_col1, prm_col2, prm_col3 };
    sortBy(col, 3, prm_blank_is_max);
}
void GgafQuery::sortDescBy(const char* prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
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

void GgafQuery::sortDescBy(const char* prm_col[], int prm_col_num, bool prm_blank_is_max) {
    if (getCount() > 0) {
        sortDescBy(prm_col, prm_col_num, 0, _lstTtable.size() - 1, prm_blank_is_max);
    }
}

void GgafQuery::sortDescBy(const char* prm_col, bool prm_blank_is_max) {
    const char* col[1] = { prm_col };
    sortDescBy(col, 1, prm_blank_is_max);
}

void GgafQuery::sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max) {
    const char* col[2] = { prm_col1, prm_col2 };
    sortDescBy(col, 2, prm_blank_is_max);
}

void GgafQuery::sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max) {
    const char* col[3] = { prm_col1, prm_col2, prm_col3 };
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
        DELETE_IMPOSSIBLE_NULL(r);
    }
}

//2012/10/02
//���l�^��JAVA��
//TODO:�K�v�ȃ��\�b�h����ڐA���Ă������I

//package jp.gwaf.core.util;
//
//import java.io.Serializable;
//import java.math.BigDecimal;
//import java.sql.ResultSet;
//import java.sql.ResultSetMetaData;
//import java.sql.SQLException;
//import java.util.HashMap;
//import java.util.Hashtable;
//import java.util.Iterator;
//import java.util.List;
//import java.util.Map;
//import java.util.Set;
//import java.util.TreeMap;
//import java.util.Vector;
//
//import jp.gwaf.core.GwafConst;
//import jp.gwaf.core.exception.GwafInternalException;
//import jp.gwaf.core.exception.GwafSqlException;
//
///**
// * SQL��SELECT�̌��ʁi�N�G���j���i�[���A�I�u�W�F�N�g�Ƃ��Ĉ������Ƃ�ړI�Ƃ����N���X�ł�.  <BR>
// * �N�G���񖼂͑啶����������ʂ��Ă��܂�.  <BR>
// * @version 0.001.20070313
// * @since 0.001.20070313
// * @author Masatoshi Tsuge
// */
//public class GwafQueryObject implements Serializable {
//
//
//    private static final long serialVersionUID = 8980628699444387817L;
//
//    /** �N�G���̗񖼂ƒl�̃y�A��������Map��List�ł� */
//    public List<Map<String, Object>> _lstTtable = null;
//
//
//    /**
//     * ResultSet ���C���X�^���X�𐶐����܂�.  <BR>
//     * ResultSet ����S�� getObject �ɂ��f�[�^���擾���܂��B<BR>
//     * ���ӁF<BR>
//     * �P�D�����ɂ���Ă̓��������������邩���m��܂���B<BR>
//     * �Q�DJDBC�̊��S�Ή��ł͂Ȃ��f�[�^�x�[�X�̃f�[�^�^�̏ꍇ�́A���x�������邩������܂���B<BR>
//     * getObject�Ŏ擾���Ă����Ȃ��f�[�^�^���ǂ����m�F���ĉ������B<BR>
//     * @param prm_rs
//     * @throws GwafSqlException
//     */
//    public GwafQueryObject(ResultSet prm_rs) throws GwafSqlException {
//        _lstTtable = new Vector<Map<String, Object>>();
//        try {
//            ResultSetMetaData meta = prm_rs.getMetaData();
//            for (int i = 0; prm_rs.next() == true; i++) {
//                Map<String, Object> mapRec = new HashMap<String, Object>();
//                int cols = meta.getColumnCount();
//                for(int j = 1; j <= cols; j++) {
//                    mapRec.put(meta.getColumnName(j), prm_rs.getObject(j));
//                }
//                _lstTtable.add(mapRec);
//            }
//        } catch (SQLException e) {
//            throw new GwafSqlException(e);
//        }
//    }
//
//    /**
//     * �N�G���̗񖼂ƒl�̃y�A��������Map��List���C���X�^���X�𐶐����܂�.  <BR>
//     * @param prm_lst
//     */
//    public GwafQueryObject(List<Map<String, Object>> prm_lst) {
//        _lstTtable = prm_lst;
//    }
//
////    @Override
////    public GwafQueryObject clone() {
////        Vector<Map<String, Object>> lstTtableNew = new Vector<Map<String, Object>>();
////        String[] cols = getColNames();
////        for (int i = 0; i < _lstTtable.size(); i++) {
////            Map<String, Object> mapRec = new HashMap<String, Object>();
////            for (int j = 0; j < cols.length; j++) {
////                mapRec.put(cols[j], new String(get(cols[j], j)));
////            }
////
////        }
////        mapRec.put
////
////
////    }
//
//
//    /**
//     * �����v�f�O�̃C���X�^���X�𐶐����܂�.  <BR>
//     */
//    public GwafQueryObject() {
//        _lstTtable = new Vector<Map<String, Object>>();
//    }
//
//
//    public bool hasRecord() {
//        if (getCount() == 0) {
//            return false;
//        } else {
//            return true;
//        }
//    }
//
//
//
//    /**
//     * �{�N�G������A�w������𖞂����ꕔ�i���͑S��)�̃C���f�b�N�X��Ԃ��܂�.  <BR>
//     * �w������́A�ȉ��� �����ɂȂ�܂��B<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l ����Q�����iprm_equalVal)�v<BR>
//     * ��L�́u���v�́A<B>equals()</B> ���\�b�h�ɂ�锻�茋�ʂ�true��\���܂��B�A���A��Q������<I>null</I>�ł������ꍇ��
//     * �ۗ��Fequals() ���\�b�h�ł͂�<B> �l == null </B> �Ƃ���������s���܂��B<BR>
//     * ��P����(prm_col)�̗񖼂��A�������g�̃N�G���ɑ��݂��Ȃ��ꍇ�́A�����s��v�ƈ����܂��i��O�ɂ͂Ȃ�܂���j�B
//     * ����Ώۂ̒l�̌^����v���Ȃ��ꍇ�́A�L���X�g���s�\�iequals()���ł��Ȃ��j�ł���Η�O�ɂȂ�܂��B<BR>
//     * @param <T> ����Ώۂ̒l�̌^
//     * @param prm_col ����Ώۂ̗�
//     * @param prm_equalVal �����l
//     * @return �C���f�b�N�X
//     */
//    public <T> int indexOf(String prm_col, T prm_equalVal) {
//        Map<String, Object> map;
//        for (int i = 0; i < _lstTtable.size(); i++) {
//            map = _lstTtable.get(i);
//            if (map.containsKey(prm_col)) {
//                T val = (T)map.get(prm_col);
//                if (prm_equalVal == null) {
//                    if (val == null) {
//                        return i;
//                    }
//                } else {
//                    if (prm_equalVal.equals(val)) {
//                        return i;
//                    }
//                }
//            }
//        }
//        return -1;
//    }
//
//    /**
//     * �{�N�G������Aindex�Ŏw�肳�ꂽ���R�[�h1�����V�����[�R�s�[���A�V���� GwafQueryObject �𐶐����܂�.  <BR>
//     * ������ prm_beginIndex ���������g�̕ێ�����v�f���𒴂���ꍇ�A�����v�f 0 �� GwafQueryObject ����������
//     * �Ԃ���܂��i��O�ɂ͂Ȃ�܂���j�B<BR>
//     * @param prm_beginIndex �擾index(0�`�j
//     * @return �w��̂P���̗v�f�������� GwafQueryObject
//     */
//    public GwafQueryObject extract(int prm_beginIndex) {
//        List<Map<String, Object>> lisQuery = new Vector<Map<String, Object>>();
//        lisQuery.add(_lstTtable.get(prm_beginIndex));
//        return new GwafQueryObject(lisQuery);
//    }
//
//    /**
//     * �{�N�G������A�͈͎w�肳�ꂽ�ꕔ�i���͑S���j�̃��R�[�h���V�����[�R�s�[�����A�V���� GwafQueryObject �𐶐����܂�.  <BR>
//     * ������ prm_beginIndex ���������g�̕ێ�����v�f���𒴂���ꍇ�A���邢�͈����� prm_length �� 0 �̏ꍇ�A
//     * �����v�f 0 �� GwafQueryObject ����������Ԃ���܂��i��O�ɂ͂Ȃ�܂���j�B
//     * @param prm_beginIndex �͈͎w��J�nindex(0�`�j
//     * @param prm_length �擾���R�[�h���i0�`)
//     * @return �w��̈�̗v�f�������� GwafQueryObject
//     */
//    public GwafQueryObject extract(int prm_beginIndex, int prm_length) {
//        List<Map<String, Object>> lisQuery = new Vector<Map<String, Object>>();
//        for (int i = prm_beginIndex; i < prm_beginIndex+prm_length; i++) {
//            lisQuery.add(_lstTtable.get(i));
//        }
//        return new GwafQueryObject(lisQuery);
//    }
//
//    /**
//     * �{�N�G������A�w������𖞂����ꕔ�i���͑S��)�̃��R�[�h���V�����[�R�s�[�����A�V���� GwafQueryObject �𐶐����܂�.  <BR>
//     * �w������́A�ȉ��� �����ɂȂ�܂��B<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̕�����\�� ����Q�����iprm_equalVal)������v<BR>
//     * ��L�́u���v�́A<B>String#equals()</B> ���\�b�h�ɂ�锻�茋�ʂ�true��\���܂��B�A���A��Q������<I>null</I>�ł������ꍇ��
//     * equals() ���\�b�h����ł͂Ȃ�<B> �l == null </B> �Ƃ���������s���܂��B<BR>
//     * ��P����(prm_col)�̗񖼂��A�������g�̃N�G���ɑ��݂��Ȃ��ꍇ�́A�����s��v�ƈ����܂��i��O�ɂ͂Ȃ�܂���j�B
//     * ����Ώۂ̒l�̌^����v���Ȃ��ꍇ�́A�L���X�g���s�\�iequals()���ł��Ȃ��j�ł���Η�O�ɂȂ�܂��B<BR>
//     * @param <T> ����Ώۂ̒l�̌^
//     * @param prm_col ����Ώۂ̗�
//     * @param prm_equalVal �����l
//     * @return �w������𖞂������R�[�h������ێ�����GwafQueryObject
//     */
//    public <T> GwafQueryObject extractStrEquals(String prm_col, String prm_equalVal) {
//        List<Map<String, Object>> lisQuery = new Vector<Map<String, Object>>();
//        Map<String, Object> map;
//        for (int i = 0; i < _lstTtable.size(); i++) {
//            map = _lstTtable.get(i);
//            if (map.containsKey(prm_col)) {
//                Object val = map.get(prm_col);
//                if (prm_equalVal == null) {
//                    if (val == null) {
//                        lisQuery.add(_lstTtable.get(i));
//                    }
//                } else {
//                    if (prm_equalVal.equals(val.toString())) {
//                        lisQuery.add(_lstTtable.get(i));
//                    }
//                }
//            }
//        }
//        return new GwafQueryObject(lisQuery);
//    }
//
//
//    /**
//     * �{�N�G������A�w������𖞂����ꕔ�i���͑S��)�̃��R�[�h���V�����[�R�s�[�����A�V���� GwafQueryObject �𐶐����܂�.  <BR>
//     * �w������́A�ȉ��� �����ɂȂ�܂��B<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l ����Q�����iprm_equalVal)�v<BR>
//     * ��L�́u���v�́A<B>equals()</B> ���\�b�h�ɂ�锻�茋�ʂ�true��\���܂��B�A���A��Q������<I>null</I>�ł������ꍇ��
//     * �ۗ��Fequals() ���\�b�h�ł͂�<B> �l == null </B> �Ƃ���������s���܂��B<BR>
//     * ��P����(prm_col)�̗񖼂��A�������g�̃N�G���ɑ��݂��Ȃ��ꍇ�́A�����s��v�ƈ����܂��i��O�ɂ͂Ȃ�܂���j�B
//     * ����Ώۂ̒l�̌^����v���Ȃ��ꍇ�́A�L���X�g���s�\�iequals()���ł��Ȃ��j�ł���Η�O�ɂȂ�܂��B<BR>
//     * @param <T> ����Ώۂ̒l�̌^
//     * @param prm_col ����Ώۂ̗�
//     * @param prm_equalVal �����l
//     * @return �w������𖞂������R�[�h������ێ�����GwafQueryObject
//     */
//    public <T> GwafQueryObject extractEquals(String prm_col, T prm_equalVal) {
//        List<Map<String, Object>> lisQuery = new Vector<Map<String, Object>>();
//        Map<String, Object> map;
//        for (int i = 0; i < _lstTtable.size(); i++) {
//            map = _lstTtable.get(i);
//            if (map.containsKey(prm_col)) {
//                T val = (T)map.get(prm_col);
//                if (prm_equalVal == null) {
//                    if (val == null) {
//                        lisQuery.add(_lstTtable.get(i));
//                    }
//                } else {
//                    if (prm_equalVal.equals(val)) {
//                        lisQuery.add(_lstTtable.get(i));
//                    }
//                }
//            }
//        }
//        return new GwafQueryObject(lisQuery);
//    }
//
//    /**
//     * �{�N�G������A�w������𖞂����ꕔ�i���͑S��)�̃��R�[�h���V�����[�R�s�[�����A�V���� GwafQueryObject �𐶐����܂�.  <BR>
//     * �w������́A�ȉ��� �����ɂȂ�܂��B<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l�̕�����\�� �� ��Q�����̐��K�\��������iprm_reg)�̃p�^�[���Ɉ�v���鎞�v<BR>
//     * ��P����(prm_col)�̗񖼂��A�������g�̃N�G���ɑ��݂��Ȃ��ꍇ�́A�����s��v�ƈ����܂��i��O�ɂ͂Ȃ�܂���j�B
//     * ��Q������<I>null</I>�ł������ꍇ�͗�O�ɂȂ�܂��B
//     * @param prm_col ����Ώۂ̗�
//     * @param prm_equalVal �����l
//     * @return �w������𖞂������R�[�h������ێ�����GwafQueryObject
//     */
//    public GwafQueryObject extractMuchString(String prm_col, String prm_reg) throws GwafInternalException {
//        List<Map<String, Object>> lisQuery = new Vector<Map<String, Object>>();
//        if (prm_reg != null) {
//            Map<String, Object> map;
//            for (int i = 0; i < _lstTtable.size(); i++) {
//                map = _lstTtable.get(i);
//                if (map.containsKey(prm_col)) {
//                    String val = map.get(prm_col).toString();
//                    if (GwafStringUtil.chkMatch(val, prm_reg)) {
//                        lisQuery.add(_lstTtable.get(i));
//                    }
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#extractMuchString: ��Q�����̐��K�\�������� null �ł��B");
//        }
//        return new GwafQueryObject(lisQuery);
//    }
//    /**
//     * �{�N�G������A�w������𖞂����ꕔ�i���͑S��)�̃��R�[�h���V�����[�R�s�[�����A�V���� GwafQueryObject �𐶐����܂�.  <BR>
//     * �w������́A�ȉ��ɗ񋓂�������� OR �����ɂȂ�܂��B<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l ����Q�����̑�P�v�f�l�iprm_arrEqualVal[0])�v<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l ����Q�����̑�Q�v�f�l�iprm_arrEqualVal[1])�v<BR>
//     * �@�@�@�@�@�@�@�@�@�@�@�E<BR>
//     * �@�@�@�@�@�@�@�@�@�@�@�E<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l ����Q�����̍ŏI�v�f�l�iprm_arrEqualVal[prm_arrEqualVal.length])�v
//     * <BR>
//     * ��L�́u���v�́A<B>equals()</B> ���\�b�h�ɂ�锻�茋�ʂ�true��\���܂��B�A���A��Q�����̗v�f�l��<I>null</I>�ł������ꍇ��
//     * equals() ���\�b�h�ł͂�<B> �l == null </B> �Ƃ���������s���܂��B<BR>
//     * ��Q����(prm_arrEqualVal)���̂�<I>null</I>�̏ꍇ�A �����v�f 0 �� GwafQueryObject ����������Ԃ���܂��B
//     * ��P����(prm_col)�̗񖼂��A�������g�̃N�G���ɑ��݂��Ȃ��ꍇ�́A�����s��v�ƈ����܂��i��O�ɂ͂Ȃ�܂���j�B
//     * ����Ώۂ̒l�̌^����v���Ȃ��ꍇ�́A�L���X�g���s�\�iequals()���ł��Ȃ��j�ł���Η�O�ɂȂ�܂��B<BR>
//     * @param <T> ����Ώۂ̒l�̌^
//     * @param prm_col ����Ώۂ̗�
//     * @param prm_arrEqualVal �����l�̔z��
//     * @return �w������𖞂������R�[�h������ێ�����GwafQueryObject
//     */
//    public <T> GwafQueryObject extractAnyEquals(String prm_col, T[] prm_arrEqualVal) {
//        List<Map<String, Object>> lisQuery = new Vector<Map<String, Object>>();
//        if (prm_arrEqualVal != null) {
//            Map<String, Object> map;
//            for (int i = 0; i < _lstTtable.size(); i++) {
//                map = _lstTtable.get(i);
//                if (map.containsKey(prm_col)) {
//                    for (int j = 0; j < prm_arrEqualVal.length; j++) {
//                        T val = (T)map.get(prm_col);
//                        if (prm_arrEqualVal[j] == null) {
//                            if (val == null) {
//                                lisQuery.add(_lstTtable.get(i));
//                            }
//                        } else {
//                            if (prm_arrEqualVal.equals(val)) {
//                                lisQuery.add(_lstTtable.get(i));
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        return new GwafQueryObject(lisQuery);
//    }
//
//    /**
//     * �{�N�G������A�w������𖞂����ꕔ�i���͑S��)�̃��R�[�h���V�����[�R�s�[�����A�V���� GwafQueryObject �𐶐����܂�.  <BR>
//     * �w������́A�ȉ��� �����ɂȂ�܂��B<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l �� ��Q�����iprm_equalVal)�v<BR>
//     * ��L�́u���v�́A<B>equals()</B> ���\�b�h�ɂ�锻�茋�ʂ�false��\���܂��B�A���A��Q������<I>null</I>�ł������ꍇ��
//     * equals() ���\�b�h�ł͂�<B> �l != null </B> �Ƃ���������s���܂��B<BR>
//     * ��P����(prm_col)�̗񖼂��A�������g�̃N�G���ɑ��݂��Ȃ��ꍇ�́A�����s��v�ƈ����܂��i��O�ɂ͂Ȃ�܂���j�B
//     * ����Ώۂ̒l�̌^����v���Ȃ��ꍇ�́A�L���X�g���s�\�iequals()���ł��Ȃ��j�ł���Η�O�ɂȂ�܂��B<BR>
//     * @param <T> ����Ώۂ̒l�̌^
//     * @param prm_col ����Ώۂ̗�
//     * @param prm_notEqualVal �����l
//     * @return �w������𖞂������R�[�h������ێ�����GwafQueryObject
//     */
//    public <T> GwafQueryObject extractNotEquals(String prm_col, T prm_notEqualVal) {
//        List<Map<String, Object>> lisQuery = new Vector<Map<String, Object>>();
//        Map<String, Object> map;
//        for (int i = 0; i < _lstTtable.size(); i++) {
//            map = _lstTtable.get(i);
//            if (map.containsKey(prm_col)) {
//                T val = (T)map.get(prm_col);
//                if (prm_notEqualVal == null) {
//                    if (val != null) {
//                        lisQuery.add(_lstTtable.get(i));
//                    }
//                } else {
//                    if (!prm_notEqualVal.equals(val)) {
//                        lisQuery.add(_lstTtable.get(i));
//                    }
//                }
//            }
//        }
//        return new GwafQueryObject(lisQuery);
//    }
//
//    /**
//     * �{�N�G������A�w������𖞂����ꕔ�i���͑S��)�̃��R�[�h���V�����[�R�s�[�����A�V���� GwafQueryObject �𐶐����܂�.  <BR>
//     * �w������́A�ȉ��ɗ񋓂�������� OR �����ɂȂ�܂��B<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l �� ��Q�����̑�P�v�f�l�iprm_arrEqualVal[0])�v<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l �� ��Q�����̑�Q�v�f�l�iprm_arrEqualVal[1])�v<BR>
//     * �@�@�@�@�@�@�@�@�@�@�@�E<BR>
//     * �@�@�@�@�@�@�@�@�@�@�@�E<BR>
//     * �u���g�̑�P�����iprm_col�j�̗񖼂̑S�Ă̒l �� ��Q�����̍ŏI�v�f�l�iprm_arrEqualVal[prm_arrEqualVal.length])�v
//     * <BR>
//     * ��L�́u���v�́A<B>equals()</B> ���\�b�h�ɂ�锻�茋�ʂ�false��\���܂��B�A���A��Q�����̗v�f�l��<I>null</I>�ł������ꍇ��
//     * equals() ���\�b�h�ł͂�<B> �l != null </B> �Ƃ���������s���܂��B<BR>
//     * ��Q����(prm_arrEqualVal)���̂�<I>null</I>�̏ꍇ�A �����v�f 0 �� GwafQueryObject ����������Ԃ���܂��B
//     * ��P����(prm_col)�̗񖼂��A�������g�̃N�G���ɑ��݂��Ȃ��ꍇ�́A�����s��v�ƈ����܂��i��O�ɂ͂Ȃ�܂���j�B
//     * ����Ώۂ̒l�̌^����v���Ȃ��ꍇ�́A�L���X�g���s�\�iequals()���ł��Ȃ��j�ł���Η�O�ɂȂ�܂��B<BR>
//     * @param <T> ����Ώۂ̒l�̌^
//     * @param prm_col ����Ώۂ̗�
//     * @param prm_arrNotEqualVal �����l�̔z��
//     * @return �w������𖞂������R�[�h������ێ�����GwafQueryObject
//     */
//    public <T> GwafQueryObject extractAnyNotEquals(String prm_col, T[] prm_arrNotEqualVal) {
//        List<Map<String, Object>> lisQuery = new Vector<Map<String, Object>>();
//        if (prm_arrNotEqualVal != null) {
//            Map<String, Object> map;
//            for (int i = 0; i < _lstTtable.size(); i++) {
//                map = _lstTtable.get(i);
//                if (map.containsKey(prm_col)) {
//                    for (int j = 0; j < prm_arrNotEqualVal.length; j++) {
//                        T val = (T)map.get(prm_col);
//                        if (prm_arrNotEqualVal[j] == null) {
//                            if (val != null) {
//                                lisQuery.add(_lstTtable.get(i));
//                            }
//                        } else {
//                            if (!prm_arrNotEqualVal.equals(val)) {
//                                lisQuery.add(_lstTtable.get(i));
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        return new GwafQueryObject(lisQuery);
//    }
//
//
//
//    public String getMaxStr(String prm_col) {
//        Map<String, Object> map;
//        String max = "";
//        for (int i = 0; i < _lstTtable.size(); i++) {
//            map = _lstTtable.get(i);
//            if (map.containsKey(prm_col)) {
//                String val = (String)map.get(prm_col);
//                if (max.compareTo(val) < 0 ) { //val���傫��
//                    max = val;
//                } else if (max.compareTo(val) > 0 ) { //val��������
//
//                } else {
//
//                }
//            }
//        }
//        return max;
//    }
//
//    public String getMinStr(String prm_col) {
//        Map<String, Object> map;
//        String min = "";
//        for (int i = 0; i < _lstTtable.size(); i++) {
//            map = _lstTtable.get(i);
//            if (map.containsKey(prm_col)) {
//                String val = (String)map.get(prm_col);
//                if (min.compareTo(val) < 0 ) { //val���傫��
//
//                } else if (min.compareTo(val) > 0 ) { //val��������
//                    min = val;
//                } else {
//
//                }
//            }
//        }
//        return min;
//    }
//
//
//    public int getMaxNum(String prm_col) {
//        Map<String, Object> map;
//        int max = Integer.MIN_VALUE;
//        for (int i = 0; i < _lstTtable.size(); i++) {
//            map = _lstTtable.get(i);
//            if (map.containsKey(prm_col)) {
//                int val = (Integer)map.get(prm_col);
//                if (max < val ) { //val���傫��
//                    max = val;
//                } else if (max > val ) { //val��������
//
//                } else {
//
//                }
//            }
//        }
//        return max;
//    }
//
//
//
//    public int getMinNum(String prm_col) {
//        Map<String, Object> map;
//        int min = Integer.MAX_VALUE;
//        for (int i = 0; i < _lstTtable.size(); i++) {
//            map = _lstTtable.get(i);
//            if (map.containsKey(prm_col)) {
//                int val = (Integer)map.get(prm_col);
//                if (min < val ) { //val���傫��
//
//                } else if (min > val ) { //val��������
//                    min = val;
//                } else {
//
//                }
//            }
//        }
//        return min;
//    }
//
//
//    /**
//     * ���݂̃N�G�����R�[�h�������擾���܂�.  <BR>
//     * @return ����
//     */
//    public int getCount() {
//        if (_lstTtable == null) {
//            return 0;
//        } else if (_lstTtable.isEmpty()) {
//            return 0;
//        } else {
//            return _lstTtable.size();
//        }
//    }
//
//    /**
//     * �w�肳�ꂽ���R�[�h���� Map �Ŏ擾���܂�.  <BR>
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @return �w�背�R�[�h��Map
//     */
//    public Map<String, Object> getRecord(int prm_index) {
//        return _lstTtable.get(prm_index);
//    }
//
//
//    /**
//     * �w�肳�ꂽ��̒l���㏑������ .
//     * ���݂��Ȃ��񖼂��w�肵���ꍇ�̓G���[�ɂȂ�.
//     * @param <T>
//     * @param prm_col  ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @param prm_data �㏑������l
//     * @return
//     * @throws GwafInternalException
//     */
//    public void set(String prm_col, int prm_index, Object prm_data) throws GwafInternalException {
//        Map rec = _lstTtable.get(prm_index);
//        if (rec.containsKey(prm_col)) {
//            rec.put(prm_col, prm_data);
//        } else {
//            throw new GwafInternalException("GwafQueryObject#set �F ���x�������R�[�h"+prm_index+"�̍s�ŁA���݂��Ȃ���["+prm_col+"]�̏㏑�������݂܂����B");
//        }
//    }
//
//    /**
//     * ��̑��݃`�F�b�N .
//     * ���݂���ꍇ true�B
//     * �N�G����0 �����́A������ null �̏ꍇ false
//     * @param prm_col �`�F�b�N�����
//     * @return ���݂���ꍇ true
//     * @throws GwafInternalException
//     */
//    public bool isExistCol(String prm_col) throws GwafInternalException {
//        if (prm_col == null || getCount() == 0) {
//            return false;
//        } else {
//            Map rec = _lstTtable.get(0);
//            if (rec.containsKey(prm_col)) {
//                return true;
//            } else {
//                return false;
//            }
//        }
//
//    }
//
//
//    /**
//     * �w�肳�ꂽ��̒l���Anull ���� toString().equals("") �Ȃ�ΐݒ�A
//     * ���Ƀf�[�^������ꍇ�̓Z�p���[�^������ǉ����Ė����Ƀf�[�^�ǉ� .
//     * ���݂��Ȃ��񖼁A������t�B�[���h�ȊO���w�肵���ꍇ�̓G���[�ɂȂ�.
//     * @param <T>
//     * @param prm_col  ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @param prm_data �l
//     * @param prm_sepa �Z�p���[�^
//     * @return
//     * @throws GwafInternalException
//     */
//    public void setDataTail(String prm_col, int prm_index, String prm_data, String prm_sepa) throws GwafInternalException {
//        Map rec = _lstTtable.get(prm_index);
//        if (rec.containsKey(prm_col)) {
//            if (rec.get(prm_col) == null || rec.get(prm_col).toString().equals("")) {
//                rec.put(prm_col, prm_data);
//            } else {
//                rec.put(prm_col, rec.get(prm_col).toString()+prm_sepa+prm_data);
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#set �F ���x�������R�[�h"+prm_index+"�̍s�ŁA���݂��Ȃ���["+prm_col+"]�̏㏑�������݂܂����B");
//        }
//    }
//
//    /**
//     * �w�肳�ꂽ���R�[�h�����㏑���R�s�[����.  <BR>
//     * �ǉ������R�[�h�ɑ��݂��Ȃ��񖼂��A�������R�[�h���ɑ��݂����ꍇ�̓G���[�ɂȂ�.
//     * �ǉ������R�[�h�ɑ��݂��Ȃ��񖼂��A�������R�[�h���ɑ��݂����ꍇ�̓G���[�ɂȂ�.
//     * @param prm_index
//     */
//    public void setRecord(int prm_index, Map<String, Object> prm_mapRow) throws GwafInternalException {
//        Map rec = _lstTtable.get(prm_index);
//        Set<String> setCol_prm = prm_mapRow.keySet();
//        Iterator<String> iteCol_prm = setCol_prm.iterator();
//        String col_prm;
//        for (int i = 0; iteCol_prm.hasNext(); i++) {
//            col_prm = iteCol_prm.next();
//            if (rec.containsKey(col_prm)) {
//                rec.put(col_prm, prm_mapRow.get(col_prm));
//            } else {
//                throw new GwafInternalException("GwafQueryObject#setRecord �F ���x�������R�[�h"+prm_index+"�̍s�ŁA���݂��Ȃ���["+col_prm+"]�̏㏑�������݂܂����B");
//            }
//        }
//    }
//
//
//    /**
//     * �w�肳�ꂽ��iKEY��j�̒l����v�������R�[�h��S�ď㏑������ .
//     * ���ӁF������GwafQueryObject�͔j�󂳂�܂��B<BR>
//     *       ����͏㏑���ł������R�[�h��������GwafQueryObject���珇��remove()���A�������œK�����Ă��邽�߂ł��B<BR>
//     *       ���������āA������A������GwafQueryObject�͏㏑���o���Ȃ��������R�[�h�̗]�肪�c��܂��B<BR>
//     * @param prm_arr_key_col �㏑�����s��������KEY��
//     * @param prm_qry �㏑������N�G��
//     * @throws GwafInternalException
//     */
//    public void overwriteEquals(String[] prm_arr_key_col, GwafQueryObject prm_qry) throws GwafInternalException {
//        if (prm_qry == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: �ǉ����R�[�h prm_qry �� null �ł�");
//        }
//        if (prm_qry.getCount() == 0) {
//            return;
//        }
//        //�P���R�[�h�����񑶍݃`�F�b�N
//        String[] arrCol = getColNames();
//        String[] arrCol_param = prm_qry.getColNames();
//
//        int iExistNum = 0;
//        for (int i = 0; i < arrCol_param.length; i++) {
//            for (int j = 0; j < arrCol.length; j++) {
//                if (arrCol[j].equals(arrCol_param[i])) {
//                    iExistNum++;
//                    break;
//                }
//            }
//        }
//        if (iExistNum != arrCol.length) {
//            //���̎��_�ŃG���[�B
//            //�G���[���̕�������쐬����B
//            String wk1 = "{";
//            for (int i = 0; i < arrCol_param.length; i++) {
//                wk1 = wk1 + " ["+i+"]="+arrCol_param[i];
//            }
//            wk1 = wk1 + "}";
//            String wk2 = "{";
//            for (int i = 0; i < arrCol.length; i++) {
//                wk2 = wk2 + " ["+i+"]="+arrCol[i];
//            }
//            wk2 = wk2 + "}";
//            throw new GwafInternalException("GwafQueryObject#overwrite: �ǉ����R�[�h�񖼂Ɨ񐔂����S��v���܂���ł����B�{�N�G����"+wk2+"�^�����̃N�G����"+wk1);
//        }
//        int init_base_qry_size = _lstTtable.size();
//        Map<String,Object> mapBaseQry = null;
//        Map<String,Object> mapPrmQry = null;
//        Object key_value_base_qry = null;
//        Object key_value_prm_qry = null;
//        bool was_overwrite = false;
//        for (int i = 0; i < init_base_qry_size; i++) {
//            was_overwrite = false;
//            mapBaseQry = _lstTtable.get(i);
//            for (int j = 0; j < prm_qry._lstTtable.size(); j++) {
//                bool overwrite_able = true;
//                mapPrmQry = prm_qry._lstTtable.get(j);
//                for (int n = 0; n < prm_arr_key_col.length; n++) {
//                    key_value_base_qry = mapBaseQry.get(prm_arr_key_col[n]);
//                    key_value_prm_qry  = mapPrmQry.get(prm_arr_key_col[n]);
//                    if (key_value_base_qry != null && key_value_prm_qry != null &&
//                            key_value_base_qry.equals(key_value_prm_qry)) {
//                        //OK �㏑���Ώۂł���\�w���p��
//                    } else {
//                        //�㏑�����p��
//                        overwrite_able = false;
//                        break;
//                    }
//                }
//                if (overwrite_able) {
//                    //�SKEY�J�����̒l����v�̂��ߏ㏑��
//                    _lstTtable.set(i, prm_qry._lstTtable.get(j));
//                    was_overwrite = true;
//                    while(prm_qry._lstTtable.remove(key_value_prm_qry)); //�㏑���Ɏg�p���ꂽ���R�[�h�͂����K�v�Ȃ��B
//                    break; //�㏑����Break.
//                           //����͉��ɂQ���R�[�h�ȏ㏑���\��Key�l��prm_qry�ɑ��݂��Ă��A
//                           //�ŏ���Key�l���̗p����邱�Ƃ��Ӗ����܂�
//                } else {
//                    //����prm_qry�̃��R�[�h�֊��҂���
//                }
//            }
//            if (was_overwrite) {
//                //�㏑�������̂ł���Ή������Ȃ�
//            } else {
//                //�㏑���ł��Ȃ���Βǉ�
//                _lstTtable.add(mapPrmQry);
//            }
//        }
//        //�����ŏ㏑���o���Ȃ����������N�G���͗]���Ă��܂�
//        _lstTtable.addAll(prm_qry._lstTtable);
//    }
//
//    /**
//     * �w�肳�ꂽ��̒l�����o���܂�.  <BR>
//     * �擾�l�� <I>null</I> �ł������ꍇ�A���̂܂�<I>null</I> ���Ԃ���܂��B<BR>
//     * �����̗񖼂����݂��Ȃ������ꍇ�� <I>null</I> ���Ԃ���܂��B
//     * @param <T> �擾�l�̌^
//     * @param prm_col ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @return �擾�l ���� <I>null</I>
//     */
//    public <T> T get(String prm_col, int prm_index) {
//        Map rec = _lstTtable.get(prm_index);
//        if (rec.containsKey(prm_col)) {
//            Object val = rec.get(prm_col);
//            if (val == null) {
//                return null;
//            } else {
//                return (T)val;
//            }
//        } else {
//            GwafDebug.out("GwafQueryObject#get �F ���x�������R�[�h"+prm_index+"�̍s�ŁA���݂��Ȃ���["+prm_col+"]�̎擾�����݂܂����B");
//            return null;
//        }
//    }
//
//    /**
//     * �w�肳�ꂽ��̒l�����o���܂�.  <BR>
//     * ������ {@link #get(String, int)} �œ������ʂ��擾���A
//     * �擾�l��  <I>null</I> �ł������ꍇ�̂݁A��R�����̒l���Ԃ���܂��B���̍ہA��R������ <I>null</I>
//     * �ł������ꍇ�́A���̂܂�<I>null</I> ���߂�l�ɂȂ�܂��B<BR>
//     * @param <T> �擾�l�̌^
//     * @param prm_col ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @param prm_obj_ifNull �擾�l��<I>null</I> �ł������ꍇ�ɕԂ��l
//     * @return �擾�l
//     */
//    public <T> T getNvl(String prm_col, int prm_index, T prm_obj_ifNull) {
//        Map rec = _lstTtable.get(prm_index);
//        if (rec.containsKey(prm_col)) {
//            Object objVal = rec.get(prm_col);
//            if (objVal == null) {
//                if (prm_obj_ifNull == null) {
//                    return null;
//                } else {
//                    return (T)prm_obj_ifNull;
//                }
//            } else {
//                return (T)objVal;
//            }
//        } else {
//            GwafDebug.out("GwafQueryObject#getNvl �F ����񁄃��R�[�h"+prm_index+"�̍s�ŁA���݂��Ȃ���["+prm_col+"]�̎擾�����݂܂����B");
//            return null;
//        }
//    }
//
//    /**
//     * �w�肳�ꂽ���INDEX�̒l�𕶎���ɕϊ����Ď��o���܂�.  <BR>
//     * �����œ������ʂ�toString()���Ԃ��܂��B<BR>
//     * �擾���ʂ� <I>null</I> �ł������ꍇ�A���̂܂�<I>null</I> ���Ԃ���܂��B<BR>
//     * �����̗񖼂����݂��Ȃ������ꍇ�� <I>null</I> ���Ԃ���܂��B(�������Ӊ�����)<BR>
//     * prm_index���͈͊O�ł������ꍇ�� <I>null</I> ���Ԃ���܂��B(�������Ӊ�����)<BR>
//     * @param prm_col ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @return �擾������ ���� <I>null</I>
//     */
//    public String getVal(String prm_col, int prm_index) {
//        Map rec = null;
//        try {
//            rec = _lstTtable.get(prm_index);
//        } catch (IndexOutOfBoundsException e) {
//            //GwafDebug.out("GwafQueryObject#getVal: �����(\""+prm_col+"\","+prm_index+")�́AIndex�͈͊O�ł��Bnull��Ԃ��܂����B");
//            return null;
//        }
//        if (rec.containsKey(prm_col)) {
//            Object val = rec.get(prm_col);
//            if (val == null) {
//                return null;
//            } else {
//                return val.toString();
//            }
//        } else {
//            //GwafDebug.out("GwafQueryObject#get �F ����񁄃��R�[�h"+prm_index+"�̍s�ŁA���݂��Ȃ���["+prm_col+"]�̎擾�����݂܂����B");
//            return null;
//        }
//    }
//
//    /**
//     * �w�肳�ꂽ���INDEX�̒l�𕶎���ɕϊ����Ď��o���܂�.  <BR>
//     * �A���A{@link #getVal(String, int) getVal(String, int)}�̌��ʂ� <I>null</I> �ł������ꍇ�̂݁A��R�����̒l��
//     * toString() �����l���Ԃ���܂��B���̍ہA��R������ <I>null</I> �ł������ꍇ�́A���̂܂�<I>null</I>
//     * ���߂�l�ɂȂ�܂��B<BR>
//     * @param prm_col ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @return �擾������
//     */
//    public String getValNvl(String prm_col, int prm_index, Object prm_obj_ifNull) {
//        Object objVal = getVal(prm_col, prm_index);
//        if (objVal == null) {
//            if (prm_obj_ifNull == null) {
//                return null;
//            } else {
//                return prm_obj_ifNull.toString();
//            }
//        } else {
//            return objVal.toString();
//        }
//    }
//
//    /**
//     * �w�肳�ꂽ���INDEX�̒l�𐔒l(Integer)�ɕϊ����Ď��o���܂�.  <BR>
//     * ������ {@link #getVal(String, int) getVal(String, int)} �œ������ʂ� Integer.parseInt() ���܂��B
//     * �A���A{@link #getVal(String, int) getVal(String, int)}�̌��ʂ� <I>null</I> �ł������ꍇ�A0 ���Ԃ���܂��B<BR>
//     * @param prm_col ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @return �擾���l(Integer)
//     * @throws GwafInternalException ���l(Integer)�ɕϊ��o���Ȃ��ꍇ
//     */
//    public int getInt(String prm_col, int prm_index) throws GwafInternalException {
//        Object val = get(prm_col, prm_index);
//        if (val == null) {
//            return 0;
//        } else {
//            try {
//                return Integer.parseInt(val.toString());
//            } catch (NumberFormatException e) {
//                throw new GwafInternalException(e);
//            }
//        }
//    }
//
//    /**
//     * �w�肳�ꂽ���INDEX�̒l�𐔒l(BigDecimal)�ɕϊ����Ď��o���܂�.  <BR>
//     * ������ {@link #get(String, int) get(String, int)} �œ������ʂ𕶎���ɕϊ����ABigDecimal�̃R���X�g���N�^�ɓn���Ă��܂��B
//     * �A���A{@link #get(String, int) get(String, int)}�̌��ʂ� <I>null</I> �ł������ꍇ�A0 ���Ԃ���܂��B<BR>
//     * @param prm_col
//     * @param prm_index
//     * @return
//     * @throws GwafInternalException
//     */
//    public BigDecimal getBigDecimal(String prm_col, int prm_index) throws GwafInternalException {
//        Object val = get(prm_col, prm_index);
//        if (val == null) {
//            return new BigDecimal(0);
//        } else {
//            try {
//                return new BigDecimal(val.toString());
//            } catch (Exception e) {
//                throw new GwafInternalException(e);
//            }
//        }
//    }
//
//    public BigDecimal getBigDecimalNvl(String prm_col, int prm_index, BigDecimal prm_bdIfNull) throws GwafInternalException {
//        Object val = get(prm_col, prm_index);
//        if (val == null) {
//            return prm_bdIfNull;
//        } else {
//            try {
//                return new BigDecimal(val.toString());
//            } catch (Exception e) {
//                throw new GwafInternalException(e);
//            }
//        }
//    }
//
//
//    /**
//     * �w�肳�ꂽ���INDEX�̒l�𐔒l(Integer)�ɕϊ����Ď��o���܂�.  <BR>
//     * ������ {@link #getVal(String, int) getVal(String, int)} �œ������ʂ� Integer.parseInt() ���܂��B
//     * �A���A{@link #getVal(String, int) getVal(String, int)}�̌��ʂ�  <I>null</I> �ł������ꍇ�A��Q������
//     * ���l(Integer)���Ԃ���܂��B<BR>
//     * @param prm_col ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @return �擾���l(Integer)
//     * @throws GwafInternalException ���l(Integer)�ɕϊ��o���Ȃ��ꍇ
//     */
//    public int getIntNvl(String prm_col, int prm_index, int prm_intIfNull) throws GwafInternalException {
//        Object val = getVal(prm_col, prm_index);
//        if (val == null) {
//            return prm_intIfNull;
//        } else {
//            try {
//                return Integer.parseInt(val.toString());
//            } catch (NumberFormatException e) {
//                throw new GwafInternalException(e);
//            }
//        }
//    }
//    /**
//     * �w�肳�ꂽ���INDEX�̒l�𐔒l(Integer)�ɕϊ����Ď��o���܂�.  <BR>
//     * ������ {@link #getVal(String, int) getVal(String, int)} �œ������ʂ� Integer.parseInt() ���܂��B
//     * �A���A{@link #getVal(String, int) getVal(String, int)}�̌��ʂ�  <I>null</I> �ł������ꍇ�ƁA
//     * ���l�ϊ��Ɏ��s�����ꍇ�́A��R�����̐��l(Integer)���Ԃ���܂��B<BR>
//     * @param prm_col ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @param prm_intSubstitute ���l�ϊ��Ɏ��s���̐��l
//     * @return �擾���l(Integer) or ���s���̐��l
//     * @throws GwafInternalException
//     */
//    public int getIntAnyway(String prm_col, int prm_index, Integer prm_intSubstitute) throws GwafInternalException {
//        Object val = getVal(prm_col, prm_index);
//        if (val == null) {
//            return prm_intSubstitute;
//        } else {
//            try {
//                return Integer.parseInt(val.toString());
//            } catch (NumberFormatException e) {
//                return prm_intSubstitute;
//            }
//        }
//    }
//
//    public double getDoubleAnyway(String prm_col, int prm_index, Double prm_doubleSubstitute) throws GwafInternalException {
//        Object val = getVal(prm_col, prm_index);
//        if (val == null) {
//            return prm_doubleSubstitute;
//        } else {
//            try {
//                return Double.parseDouble(val.toString());
//            } catch (NumberFormatException e) {
//                return prm_doubleSubstitute;
//            }
//        }
//    }
//
//    /**
//     * �w�肳�ꂽ���INDEX�̒l�𕶎���ɕϊ����Ď��o���܂�.  <BR>
//     * ������ {@link #getVal(String, int) getVal(String, int)} �œ������ʂ�Ԃ��܂����A���ʂ� <I>null</I>
//     * �ł������ꍇ�A""(�󕶎��j���Ԃ���܂��B<BR>
//     * ����ɁA�擾���ʂɃg�����������s���܂��B<BR>
//     * @param prm_col ��
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @return �擾������ ���� ""(�󕶎��j
//     */
//    public String getStr(String prm_col, int prm_index) {
//        String objVal = getVal(prm_col, prm_index);
//        if (objVal == null) {
//            return GwafConst.BLANK;
//        } else {
//            return objVal.toString().trim();
//        }
//    }
//
//    /**
//     * �����Ǘ����Ă���S�񖼂�z��Ŏ擾���܂�. <BR>
//     * ��̓I�ɂ͑�P���R�[�h�iINDEX=0�j�̗񖼂��擾���A�z��ŕԂ��܂��B�񖼂̏��Ԃ͕ۏ؂���܂���B<BR>
//     * �����ێ����R�[�h����0�̏ꍇ�A��̔z��(String[] {})���Ԃ���܂��B<BR>
//     * @return �񖼂̔z��
//     */
//    public String[] getColNames() {
//        if (getCount() == 0) {
//            return new String[] {};
//        } else {
//            Map<String, Object> mapFirst = getRecord(0);
//            Set<String> setKey = mapFirst.keySet();
//            String[] arrKey = new String[setKey.size()];
//            Iterator<String> iteKey = setKey.iterator();
//            for (int i = 0; iteKey.hasNext(); i++) {
//                arrKey[i] = iteKey.next();
//            }
//            return arrKey;
//        }
//    }
//
//    /**
//     * �w���̒l�S�Ă� List(Vector�C���X�^���X) �Ŏ擾���܂�. <BR>
//     * �w�肵���񖼂����݂���ꍇ�A�����v�f�͑S��{@link #get(String, int) get(String, int)}�Ŏ擾����AList�ɒǉ�����܂��B<BR>
//     * �A���A�w�肵���񖼂����݂��Ȃ��ꍇ�́A<I>null</I> �𓾂�̂ł͂Ȃ��A�����̓X�L�b�v����܂��B
//     * �S�Ẵ��R�[�h�Ɏw�肵���񖼂����݂��Ȃ��ꍇ�A�����v�f0��(Vector�C���X�^���X)���Ԃ���鎖�ɂȂ�܂��B
//     * @param prm_colname ��
//     * @return �w���̒l�� List(Vector�C���X�^���X)
//     */
//    public List getCol(String prm_colname) {
//        List<Object> lstArr = new Vector<Object>();
//        for (int i = 0; i < getCount(); i ++) {
//            if (getRecord(i).containsKey(prm_colname)) {
//                lstArr.add(get(prm_colname, i));
//            } else {
//
//            }
//        }
//        return lstArr;
//    }
//
//
//    public <T> List getColEquals(String prm_get_colname, String prm_cond_colname, T prm_cond_equalVal) {
//        List<Object> lstArr = new Vector<Object>();
//        Map<String, Object> rec = null;
//        for (int i = 0; i < getCount(); i ++) {
//            rec = getRecord(i);
//            if (rec.containsKey(prm_get_colname) && rec.containsKey(prm_get_colname) ) {
//                T cond_val = (T)(rec.get(prm_cond_colname));
//                if (prm_cond_equalVal == null) {
//                    if (cond_val == null) {
//                        lstArr.add(rec.get(prm_get_colname));
//                    }
//                } else {
//                    if (prm_cond_equalVal.equals(cond_val)) {
//                        lstArr.add(rec.get(prm_get_colname));
//                    }
//                }
//            } else {
//
//            }
//        }
//        return lstArr;
//    }
//
//    /**
//     * �w���̒l�S�Ă� List(Vector�C���X�^���X) �Ŏ擾���܂�. <BR>
//     * �w�肵���񖼂����݂���ꍇ�A�����v�f�͑S��{@link #getNvl(String, int, Object) getNvl(String, int, Object)}�Ŏ擾����A
//     * List�ɒǉ�����܂��B<BR>
//     * �A���A�w�肵���񖼂����݂��Ȃ��ꍇ�́A<I>null</I> �𓾂�̂ł͂Ȃ������̓X�L�b�v����܂��B
//     * �S�Ẵ��R�[�h�Ɏw�肵���񖼂����݂��Ȃ��ꍇ�A�����v�f0��(Vector�C���X�^���X)���Ԃ���鎖�ɂȂ�܂��B
//     * @param <T>
//     * @param prm_colname ��
//     * @param prm_obj_ifValNull  ���e�̒l�擾��<I>null</I>�ł������ꍇ�A�u��������List�Ɋi�[����l
//     * @return �w���̒l�� List(Vector�C���X�^���X)
//     */
//    public <T> List getColNvl(String prm_colname, T prm_obj_ifValNull) {
//        List<Object> lstArr = new Vector<Object>();
//        for (int i = 0; i < getCount(); i ++) {
//            lstArr.add(getNvl(prm_colname, i, (T)prm_obj_ifValNull));
//        }
//        return lstArr;
//    }
//
//
//    /**
//     * �{�N���X�̃f�[�^�ێ��t�B�[���h(�N�G���̗񖼂ƒl�̃y�A��������Map��List)��Ԃ��܂�. <BR>
//     * @return �f�[�^�ێ��t�B�[���h(�N�G���̗񖼂ƒl�̃y�A��������Map��List)
//     */
//    public List<Map<String, Object>> getListTable() {
//        return _lstTtable;
//    }
//
//    /**
//     * �{�N�G���ɗ���P�ǉ����܂�. <BR>
//     * �ǉ����� List �� size() �́A{@link #getCount() #getCount()}�Ɠ����ł���K�v������܂��B
//     * �ǉ����� List �̗v�f�����s��v�̏ꍇ��O�ƂȂ�܂��B
//     * �A���A�񂪈�����݂��Ȃ��ꍇ�́A��O�ƂȂ炸�A�ŏ��ɒǉ�������̗v�f������ƂȂ�܂��B
//     * @param prm_colname �ǉ������̗�
//     * @param prm_lstColVal �ǉ������̒l�̃��X�g
//     * @throws GwafInternalException �v�f���s��v
//     */
//    public void addCol(String prm_colname, List prm_lstColVal) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                Map<String, Object> mapRecord;
//                for (int i = 0; i < prm_lstColVal.size(); i ++) {
//                    mapRecord = new HashMap<String, Object>();
//                    mapRecord.put(prm_colname, prm_lstColVal.get(i));
//                    _lstTtable.add(mapRecord);
//                }
//            } else if (getCount() != prm_lstColVal.size()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: �v�f�����s��v�ł��Bthis.getCount()��"+getCount()+", prm_lstColVal.size()��"+(prm_lstColVal==null?null:prm_lstColVal.size()));
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && getRecord(i).containsKey(prm_colname)) {
//                        GwafDebug.out("���x����GwafQueryObject#addCol: ��["+prm_colname+"]�͊��ɑ��݂��Ă��܂��B�Ӑ}���Ă��܂����H");
//                    }
//                    getRecord(i).put(prm_colname, prm_lstColVal.get(i));
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��null�ł�");
//        }
//    }
//
//    /**
//     * �{�N�G���ɗ���P�ǉ����܂�. <BR>
//     * �ǉ����� �z�� �� length �́A{@link #getCount() #getCount()}�Ɠ����ł���K�v������܂��B
//     * �ǉ����� �z�� �̗v�f�����s��v�̏ꍇ��O�ƂȂ�܂��B
//     * �A���A�񂪈�����݂��Ȃ��ꍇ�́A��O�ƂȂ炸�A�ŏ��ɒǉ�������̗v�f������ƂȂ�܂��B
//     * @param prm_colname �ǉ������̗�
//     * @param prm_arrColVal �ǉ������̒l�̔z��
//     * @throws GwafInternalException �v�f���s��v
//     */
//    public void addCol(String prm_colname, String[] prm_arrColVal) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                Map<String, Object> mapRecord;
//                for (int i = 0; i < prm_arrColVal.length; i ++) {
//                    mapRecord = new HashMap<String, Object>();
//                    mapRecord.put(prm_colname, prm_arrColVal[i]);
//                    _lstTtable.add(mapRecord);
//                }
//            } else if (getCount() != prm_arrColVal.length) {
//                throw new GwafInternalException("GwafQueryObject#addCol: �v�f�����s��v�ł��Bthis.getCount()��"+getCount()+", prm_arrColVal.length��"+(prm_arrColVal==null?null:prm_arrColVal.length));
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && getRecord(i).containsKey(prm_colname)) {
//                        GwafDebug.out("���x����GwafQueryObject#addCol: ��["+prm_colname+"]�͊��ɑ��݂��Ă��܂��B�Ӑ}���Ă��܂����H");
//                    }
//                    getRecord(i).put(prm_colname, prm_arrColVal[i]);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��null�ł�");
//        }
//    }
//
//    /**
//     * �{�N�G���ɗ���P�ǉ����܂�. <BR>
//     * �ǉ�������̃f�[�^�͑S�� null �ɂȂ�܂��B
//     * @param prm_colname
//     * @throws GwafInternalException
//     */
//    public void addCol(String prm_colname) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��0���̂��ߒǉ��ł��܂���");
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && getRecord(i).containsKey(prm_colname)) {
//                        GwafDebug.out("���x����GwafQueryObject#addCol: ��["+prm_colname+"]�͊��ɑ��݂��Ă��܂��B�Ӑ}���Ă��܂����H");
//                    }
//                    getRecord(i).put(prm_colname, null);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��null�ł�");
//        }
//    }
//
//    /**
//     * �{�N�G���ɗ���P�ǉ����܂�. <BR>
//     * �ǉ�������̃f�[�^�͑S�� prm_val �ɂȂ�܂��B
//     * @param prm_colname
//     * @throws GwafInternalException
//     */
//    public void addCol(String prm_colname, Object prm_val) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��0���̂��ߒǉ��ł��܂���");
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && getRecord(i).containsKey(prm_colname)) {
//                        GwafDebug.out("���x����GwafQueryObject#addCol: ��["+prm_colname+"]�͊��ɑ��݂��Ă��܂��B�Ӑ}���Ă��܂����H");
//                    }
//                    getRecord(i).put(prm_colname, prm_val);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��null�ł�");
//        }
//    }
//
//    /**
//     * �{�N�G���ɗ�ɒl���Z�b�g���܂�. <BR>
//     * �ǉ����� List �� size() �́A{@link #getCount() #getCount()}�Ɠ����ł���K�v������܂��B
//     * �ǉ����� List �̗v�f�����s��v�̏ꍇ��O�ƂȂ�܂��B
//     * �܂��A�ǉ�����񂪊��ɑ��݂��Ȃ���΃G���[�ɂȂ�܂��B<BR>
//     * @param prm_colname �ǉ������̗�
//     * @param prm_lstColVal �ǉ������̒l�̃��X�g
//     * @throws GwafInternalException �v�f���s��v
//     */
//    public void setCol(String prm_colname, List prm_lstColVal) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: ��["+prm_colname+"]�����݂��܂���B");
//            } else if (getCount() != prm_lstColVal.size()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: �v�f�����s��v�ł��Bthis.getCount()��"+getCount()+", prm_lstColVal.size()��"+(prm_lstColVal==null?null:prm_lstColVal.size()));
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && !getRecord(i).containsKey(prm_colname)) {
//                        throw new GwafInternalException("GwafQueryObject#addCol: ��["+prm_colname+"]�����݂��܂���B");
//                    }
//                    getRecord(i).put(prm_colname, prm_lstColVal.get(i));
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��null�ł�");
//        }
//    }
//
//    /**
//     * �{�N�G���ɗ�ɒl���Z�b�g���܂�. <BR>
//     * �ǉ����� �z�� �� length �́A{@link #getCount() #getCount()}�Ɠ����ł���K�v������܂��B
//     * �ǉ����� �z�� �̗v�f�����s��v�̏ꍇ��O�ƂȂ�܂��B
//     * �܂��A�ǉ�����񂪊��ɑ��݂��Ȃ���΃G���[�ɂȂ�܂��B<BR>
//     * @param prm_colname �ǉ������̗�
//     * @param prm_arrColVal �ǉ������̒l�̔z��
//     * @throws GwafInternalException �v�f���s��v
//     */
//    public void setCol(String prm_colname, String[] prm_arrColVal) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: ��["+prm_colname+"]�����݂��܂���B");
//            } else if (getCount() != prm_arrColVal.length) {
//                throw new GwafInternalException("GwafQueryObject#addCol: �v�f�����s��v�ł��Bthis.getCount()��"+getCount()+", prm_arrColVal.length��"+(prm_arrColVal==null?null:prm_arrColVal.length));
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && !getRecord(i).containsKey(prm_colname)) {
//                        throw new GwafInternalException("GwafQueryObject#addCol: ��["+prm_colname+"]�����݂��܂���B");
//                    }
//                    getRecord(i).put(prm_colname, prm_arrColVal[i]);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��null�ł�");
//        }
//    }
//
//    /**
//     * �{�N�G���ɗ�ɒl���Z�b�g���܂�. <BR>
//     * ��̃f�[�^�͑S�� null �ɂȂ�܂��B
//     * �܂��A�ǉ�����񂪊��ɑ��݂��Ȃ���΃G���[�ɂȂ�܂��B<BR>
//     * @param prm_colname
//     * @throws GwafInternalException
//     */
//    public void setColNull(String prm_colname) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��0���̂��ߒǉ��ł��܂���");
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && !getRecord(i).containsKey(prm_colname)) {
//                        throw new GwafInternalException("GwafQueryObject#addCol: ��["+prm_colname+"]�����݂��܂���B");
//                    }
//                    getRecord(i).put(prm_colname, null);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��null�ł�");
//        }
//    }
//
//    /**
//     * �{�N�G���ɗ�ɒl���Z�b�g���܂�. <BR>
//     * ��̃f�[�^�͑S�� prm_val �ɂȂ�܂��B
//     * �܂��A�ǉ�����񂪊��ɑ��݂��Ȃ���΃G���[�ɂȂ�܂��B<BR>
//     * @param prm_colname
//     * @throws GwafInternalException
//     */
//    public void setCol(String prm_colname, Object prm_val) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��0���̂��ߒǉ��ł��܂���");
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && !getRecord(i).containsKey(prm_colname)) {
//                        throw new GwafInternalException("GwafQueryObject#addCol: ��["+prm_colname+"]�����݂��܂���B");
//                    }
//                    getRecord(i).put(prm_colname, prm_val);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtable��null�ł�");
//        }
//    }
//
//
//
//
//
//    /**
//     * �{�N�G�������ɋ󃌃R�[�h(�S��null)��ǉ����܂��B
//     * @return �ǉ����ꂽindex�ʒu
//     * @throws GwafInternalException
//     */
//    public int addNewRow() throws GwafInternalException {
//        String[] cols = getColNames();
//        Map<String, Object> mapRec = new HashMap<String, Object>();
//        for (int i = 0; i < cols.length; i++) {
//            mapRec.put(cols[i], null);
//        }
//        _lstTtable.add(mapRec);
//        return _lstTtable.size()-1;
//    }
//
//    /**
//     * �{�N�G���̈����w��̈ʒu�ɋ󃌃R�[�h(�S��null)��ǉ����܂��B
//     * @param prm_index �󃌃R�[�h(�S��null)��ǉ�����INDEX
//     * @return
//     * @throws GwafInternalException
//     */
//    public void insertNewRow(int prm_index) throws GwafInternalException {
//        String[] cols = getColNames();
//        Map<String, Object> mapRec = new HashMap<String, Object>();
//        for (int i = 0; i < cols.length; i++) {
//            mapRec.put(cols[i], null);
//        }
//        _lstTtable.add(prm_index, mapRec);
//    }
//
//    /**
//     * �{�N�G���Ƀ��R�[�h��ǉ����܂�. <BR>
//     * �ǉ����郌�R�[�h�̗񖼂Ɛ�����v���Ȃ��ꍇ�G���[�ɂȂ�܂��B<BR>
//     * @param prm_mapRow �ǉ����郌�R�[�h�i�񖼂ƒl�̃y�A�j
//     * @throws GwafInternalException �ǉ��\�񖼖���
//     */
//    public void insertRow(int prm_index, Map<String, Object> prm_mapRow) throws GwafInternalException {
//        if (prm_mapRow == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: �ǉ����R�[�h prm_mapRow �� null �ł�");
//        }
//        //�񑶍݃`�F�b�N
//        String[] arrCol = getColNames();
//        Set<String> setCol_prm = prm_mapRow.keySet();
//        Iterator<String> iteCol_prm = setCol_prm.iterator();
//        int iExistNum = 0;
//        String col_prm;
//        for (int i = 0; iteCol_prm.hasNext(); i++) {
//            col_prm = iteCol_prm.next();
//            for (int j = 0; j < arrCol.length; j++) {
//                if (arrCol[j].equals(col_prm)) {
//                    iExistNum++;
//                    break;
//                }
//            }
//        }
//        if (iExistNum != arrCol.length) {
//            throw new GwafInternalException("GwafQueryObject#insertRow: �ǉ����R�[�h�񖼂Ɨ񐔂����S��v���܂���ł����B�{�N�G����"+getRecord(0)+"�^�����̃��R�[�h��"+prm_mapRow);
//        } else {
//            _lstTtable.add(prm_index, prm_mapRow);
//        }
//    }
//
//    /**
//     * �{�N�G�������Ƀ��R�[�h��ǉ����܂�. <BR>
//     * �ǉ����郌�R�[�h�̗񖼂Ɛ�����v���Ȃ��ꍇ�G���[�ɂȂ�܂��B<BR>
//     * ���g�̃N�G������(���߂Ă�addRow)�ł���ꍇ�A���̃��R�[�h���{�N�G���̗�ƂȂ�󂯓���܂��B<BR>
//     * @param prm_mapRow �ǉ����郌�R�[�h�i�񖼂ƒl�̃y�A�j
//     * @throws GwafInternalException �ǉ��\�񖼖���
//     */
//    public void addRow(Map<String, Object> prm_mapRow) throws GwafInternalException {
//        if (prm_mapRow == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: �ǉ����R�[�h prm_mapRow �� null �ł�");
//        }
//        if (_lstTtable.isEmpty()) {
//            //�ŏ��̂P�s�͖������󂯓���
//            _lstTtable.add(prm_mapRow);
//        } else {
//            //�񖼈�v�`�F�b�N
//            String[] arrCol = getColNames();
//            Set<String> setCol_prm = prm_mapRow.keySet();
//            Iterator<String> iteCol_prm = setCol_prm.iterator();
//            int iExistNum = 0;
//            String col_prm;
//            for (int i = 0; iteCol_prm.hasNext(); i++) {
//                col_prm = iteCol_prm.next();
//                for (int j = 0; j < arrCol.length; j++) {
//                    if (arrCol[j].equals(col_prm)) {
//                        iExistNum++;
//                        break;
//                    }
//                }
//            }
//            if (iExistNum != arrCol.length) {
//                throw new GwafInternalException("GwafQueryObject#addRow: �ǉ����R�[�h�񖼂Ɨ񐔂����S��v���܂���ł����B�{�N�G����"+getRecord(0)+"�^�����̃��R�[�h��"+prm_mapRow+" iExistNum="+iExistNum+" arrCol.length="+arrCol.length);
//            } else {
//                _lstTtable.add(prm_mapRow);
//            }
//        }
//    }
//
//    /**
//     * �{�N�G�������Ƀ��R�[�h��ǉ����܂�. <BR>
//     * �ǉ����郌�R�[�h�̗񖼂Ɛ�����v���Ȃ��ꍇ�G���[�ɂȂ�܂��B<BR>
//     * ���g�̃N�G������(���߂Ă�addRow)�ł���ꍇ�A���̃��R�[�h���{�N�G���̗�ƂȂ�󂯓���܂��B<BR>
//     * @param prm_cols �ǉ�����񖼂̔z��
//     * @param prm_values �Ή�����l�̔z��
//     * @throws GwafInternalException
//     */
//    public void addRow(String[] prm_cols, Object[] prm_values) throws GwafInternalException {
//        if (prm_cols == null || prm_values == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: ������ null �ł��B");
//        }
//        Map<String, Object> mapRow = new Hashtable<String, Object>();
//        for (int i = 0; i < prm_cols.length; i++) {
//            mapRow.put(prm_cols[i], prm_values[i]);
//        }
//        addRow(mapRow);
//    }
//
//    /**
//     * �{�N�G�������Ƀ��R�[�h��ǉ����܂�. <BR>
//     * ���g�̃N�G������(���߂Ă�addRow)�ł���ꍇ�A���̃��R�[�h���{�N�G���̗�ƂȂ�󂯓���܂��B<BR>
//     * @param prm_cols ��
//     * @param prm_values �l
//     * @throws GwafInternalException
//     */
//    public void addRow(String prm_cols, Object prm_values) throws GwafInternalException {
//        addRow(new String[] {prm_cols}, new Object[] {prm_values});
//    }
//
//    /**
//     * �{�N�G�������Ƀ��R�[�h��ǉ����܂�. <BR>
//     * �ǉ����郌�R�[�h�̗񖼔z��Ɛ�����v���Ȃ��ꍇ�G���[�ɂȂ�܂��B<BR>
//     * ���g�̃N�G������(���߂Ă�addRow)�ł���ꍇ�A���̃��R�[�h���{�N�G���̗�ƂȂ�󂯓���܂��B<BR>
//     * @param prm_cols �ǉ�����񖼂̔z��
//     * @param prm_values �Ή����镶����l�̔z��
//     * @throws GwafInternalException
//     */
//    public void addRow(String[] prm_cols, String[] prm_values) throws GwafInternalException {
//        if (prm_cols == null || prm_values == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: ������ null �ł��B");
//        }
//        addRow(prm_cols, (Object[])prm_values);
//    }
//
//    public void addRow(String prm_cols, String prm_values) throws GwafInternalException {
//        addRow(new String[] {prm_cols}, new String[] {prm_values});
//    }
//
//    /**
//     * �{�N�G�������� ResultSet �N�G����ǉ����܂�. <BR>
//     * @param prm_rs
//     * @throws GwafSqlException
//     */
//    public void addRow(ResultSet prm_rs) throws GwafSqlException {
//        //_lstTtable = new Vector<Map<String, Object>>();
//        try {
//            ResultSetMetaData meta = prm_rs.getMetaData();
//            for (int i = 0; prm_rs.next() == true; i++) {
//                Map<String, Object> mapRec = new HashMap<String, Object>();
//                int cols = meta.getColumnCount();
//                for(int j = 1; j <= cols; j++) {
//                    mapRec.put(meta.getColumnName(j), prm_rs.getObject(j));
//                }
//                _lstTtable.add(mapRec);
//            }
//        } catch (SQLException e) {
//            throw new GwafSqlException(e);
//        }
//    }
//
//    /**
//     * �{�N�G�������ɕʃN�G����ǉ����܂�. <BR>
//     * �ǉ����i���g�̃N�G���j�Ƀf�[�^�����݂���ꍇ�A�ǉ�����N�G���ƃ��R�[�h�̑S�Ă̗񖼂���v���Ȃ��ꍇ�G���[�ɂȂ�܂��B<BR>
//     * �ǉ����i���g�̃N�G���j�f�[�^�����݂��Ȃ��ꍇ�A�G���[�ɂ͂Ȃ�܂���B<BR>
//     * @param prm_qry ���g�̃N�G���ǉ�����N�G��
//     * @throws GwafInternalException �񖼕s��v
//     */
//    public void addRow(GwafQueryObject prm_qry) throws GwafInternalException {
//        if (prm_qry == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: �ǉ����R�[�h prm_qry �� null �ł�");
//        }
//        if (prm_qry.getCount() == 0) {
//            return;
//        }
//        //�P���R�[�h�����񑶍݃`�F�b�N
//        String[] arrCol = getColNames();
//        String[] arrCol_param = prm_qry.getColNames();
//
//        int iExistNum = 0;
//        for (int i = 0; i < arrCol_param.length; i++) {
//            for (int j = 0; j < arrCol.length; j++) {
//                if (arrCol[j].equals(arrCol_param[i])) {
//                    iExistNum++;
//                    break;
//                }
//            }
//        }
//        if (iExistNum != arrCol.length) {
//            //���̎��_�ŃG���[�B
//            //�G���[���̕�������쐬����B
//            String wk1 = "{";
//            for (int i = 0; i < arrCol_param.length; i++) {
//                wk1 = wk1 + " ["+i+"]="+arrCol_param[i];
//            }
//            wk1 = wk1 + "}";
//            String wk2 = "{";
//            for (int i = 0; i < arrCol.length; i++) {
//                wk2 = wk2 + " ["+i+"]="+arrCol[i];
//            }
//            wk2 = wk2 + "}";
//
//            throw new GwafInternalException("GwafQueryObject#addRow: �ǉ����R�[�h�񖼂Ɨ񐔂����S��v���܂���ł����B�{�N�G����"+wk2+"�^�����̃N�G����"+wk1);
//        } else {
//            _lstTtable.addAll(prm_qry.getListTable());
//        }
//    }
//
//    /**
//     * ���R�[�h���폜���܂��B .
//     * �͈͊O��Index���w�肷��ƃG���[�ƂȂ�܂��B
//     *
//     * @param prm_index ���R�[�hindex�i0�`)
//     * @throws GwafInternalException �����̃��R�[�hindex���͈͊O
//     */
//    public void removeRow(int prm_index) throws GwafInternalException {
//        if (getListTable().size() < prm_index) {
//            throw new GwafInternalException("GwafQueryObject#removeRow: �폜���R�[�hINDEX�͑��݂��܂���B�{�N�G��size="+getListTable().size()+"/�����̍폜INDEX="+prm_index);
//        }
//        getListTable().remove(prm_index);
//    }
//
//    /**
//     * �����̗�̗v�f�l�ŁA�������R�[�h�������\�[�g�����וς��܂�.  <BR>
//     * �召�̔�r�� compareTo() ���\�b�h�ōs���܂��A���������ē����v�f�l�� Comparable
//     * �ł���K�v������܂��B<BR>
//     * �܂��A<I>null</I> �͍ŏ��̒l�Ƃ��Ĉ����܂��B���������ē����v�f�l��<I>null</I> ������
//     * ����ꍇ�A�{���\�b�h�ł͐擪�Ɉړ����鎖�ɂȂ�܂��B<BR>
//     * @param prm_col �����\�[�g�����
//     * @throws GwafInternalException �\�[�g���s�\��
//     */
//    public void sortBy(String prm_col) throws GwafInternalException {
//        if (getCount() > 0) {
//            sortBy(new String[] {prm_col});
//        }
//    }
//
//    /**
//     * �����̗�̗v�f�l�ŁA�������R�[�h�������\�[�g�����וς��܂�.  <BR>
//     * �召�̔�r�� compareTo() ���\�b�h�ōs���܂��A���������ē����v�f�l�� Comparable
//     * �ł���K�v������܂��B<BR>
//     * �܂��A<I>null</I> �͍ŏ��̒l�Ƃ��Ĉ������ő���ƈ������A��Q�����̃t���O�Ŏw�肵�܂��B
//     * @param prm_col �����\�[�g�����
//     * @throws GwafInternalException �\�[�g���s�\��
//     */
//    public void sortBy(String prm_col, bool prm_null_is_max) throws GwafInternalException {
//        if (getCount() > 0) {
//            sortBy(new String[] {prm_col}, prm_null_is_max);
//        }
//    }
//
//    /**
//     * �����̗�̗v�f�l�ŁA�������R�[�h���~���\�[�g�����וς��܂�. <BR>
//     * �召�̔�r�� compareTo() ���\�b�h�ōs���܂��A���������ē����v�f�l�� Comparable
//     * �ł���K�v������܂��B<BR>
//     * �܂��A<I>null</I> �͍ŏ��̒l�Ƃ��Ĉ����܂��B���������ē����v�f�l��<I>null</I> ������
//     * ����ꍇ�A�{���\�b�h�ł͐擪�Ɉړ����鎖�ɂȂ�܂��B<BR>
//     * @param prm_col �~���\�[�g�����
//     * @param prm_null_is_max true : null �͍ł��傫���l�Ƃ���^false: null�͍ł��������l�Ƃ���B
//     * @throws GwafInternalException �\�[�g���s�\��
//     */
//    public void sortDescBy(String prm_col) throws GwafInternalException{
//        if (getCount() > 0) {
//            sortDescBy(new String[] {prm_col});
//        }
//    }
//
//    /**
//     * �����̗�̗v�f�l�ŁA�������R�[�h���~���\�[�g�����וς��܂�. <BR>
//     * �召�̔�r�� compareTo() ���\�b�h�ōs���܂��A���������ē����v�f�l�� Comparable
//     * �ł���K�v������܂��B<BR>
//     * �܂��A<I>null</I> �͍ŏ��̒l�Ƃ��Ĉ������ő���ƈ������A��Q�����̃t���O�Ŏw�肵�܂��B
//     * @param prm_col �~���\�[�g�����
//     * @param prm_null_is_max true : null �͍ł��傫���l�Ƃ���^false: null�͍ł��������l�Ƃ���B
//     * @throws GwafInternalException �\�[�g���s�\��
//     */
//    public void sortDescBy(String prm_col, bool prm_null_is_max) throws GwafInternalException{
//        if (getCount() > 0) {
//            sortDescBy(new String[] {prm_col}, prm_null_is_max);
//        }
//    }
//
//    /**
//     * �����̗�̔z�񏇂̗v�f�l�ŁA�������R�[�h�������\�[�g�����וς��܂�. <BR>
//     * �召�̔�r�� compareTo() ���\�b�h�ōs���܂��A���������ē����v�f�l�� Comparable
//     * �ł���K�v������܂��B<BR>
//     * �܂��A<I>null</I> �͍ŏ��̒l�Ƃ��Ĉ����܂��B���������ē����v�f�l��<I>null</I> ������
//     * ����ꍇ�A�{���\�b�h�ł͐擪�Ɉړ����鎖�ɂȂ�܂��B<BR>
//     * @param prm_arrCol �����\�[�g���鏇�Ԃ̗񖼔z��
//     * @throws GwafInternalException �\�[�g���s�\��
//     */
//    public void sortBy(String[] prm_arrCol) throws GwafInternalException{
//        if (getCount() > 0) {
//            try {
//                sortBy(prm_arrCol, 0, _lstTtable.size()-1, false);
//            } catch (StackOverflowError e) {
//                e.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: �\�[�g���̍ċN�Ăяo�������G�����܂��B���������炵�Ă��������B:"+e);
//            }  catch (Exception e2) {
//                e2.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: �\�[�g���Ɏ��s���܂����B�l��Comparable�ȊO�̃I�u�W�F�N�g�����݂���\��������܂��B:"+e2);
//            }
//        }
//    }
//
//    /**
//     * �����̗�̔z�񏇂̗v�f�l�ŁA�������R�[�h�������\�[�g�����וς��܂�. <BR>
//     * �召�̔�r�� compareTo() ���\�b�h�ōs���܂��A���������ē����v�f�l�� Comparable
//     * �ł���K�v������܂��B<BR>
//     * �܂��A<I>null</I> �͍ŏ��̒l�Ƃ��Ĉ������ő���ƈ������A��Q�����̃t���O�Ŏw�肵�܂��B
//     * @param prm_arrCol �����\�[�g���鏇�Ԃ̗񖼔z��
//     * @param prm_null_is_max true : null �͍ł��傫���l�Ƃ���^false: null�͍ł��������l�Ƃ���B
//     * @throws GwafInternalException �\�[�g���s�\��
//     */
//    public void sortBy(String[] prm_arrCol, bool prm_null_is_max) throws GwafInternalException{
//        if (getCount() > 0) {
//            try {
//                sortBy(prm_arrCol, 0, _lstTtable.size()-1, prm_null_is_max);
//            } catch (StackOverflowError e) {
//                e.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: �\�[�g���̍ċN�Ăяo�������G�����܂��B���������炵�Ă��������B:"+e);
//            }  catch (Exception e2) {
//                e2.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: �\�[�g���Ɏ��s���܂����B�l��Comparable�ȊO�̃I�u�W�F�N�g�����݂���\��������܂��B:"+e2);
//            }
//        }
//    }
//
//    /**
//     * �����̗�̔z�񏇂̗v�f�l�ŁA�������R�[�h���~���\�[�g�����וς��܂�. <BR>
//     * �召�̔�r�� compareTo() ���\�b�h�ōs���܂��A���������ē����v�f�l�� Comparable
//     * �ł���K�v������܂��B<BR>
//     * �܂��A<I>null</I> �͍ŏ��̒l�Ƃ��Ĉ����܂��B���������ē����v�f�l��<I>null</I> ������
//     * ����ꍇ�A�{���\�b�h�ł͐擪�Ɉړ����鎖�ɂȂ�܂��B<BR>
//     * @param prm_arrCol �~���\�[�g���鏇�Ԃ̗񖼔z��
//     * @throws GwafInternalException �\�[�g���s�\��
//     */
//    public void sortDescBy(String[] prm_arrCol) throws GwafInternalException {
//        if (getCount() > 0) {
//            try {
//                sortDescBy(prm_arrCol, 0, _lstTtable.size()-1, false);
//            } catch (StackOverflowError e) {
//                e.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: �\�[�g���̍ċN�Ăяo�������G�����܂��B���������炵�Ă��������B:"+e);
//            }  catch (Exception e2) {
//                e2.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: �\�[�g���Ɏ��s���܂����B�l��Comparable�ȊO�̃I�u�W�F�N�g�����݂���\��������܂��B:"+e2);
//            }
//        }
//    }
//
//    /**
//     * �����̗�̔z�񏇂̗v�f�l�ŁA�������R�[�h���~���\�[�g�����וς��܂�. <BR>
//     * �召�̔�r�� compareTo() ���\�b�h�ōs���܂��A���������ē����v�f�l�� Comparable
//     * �ł���K�v������܂��B<BR>
//     * �܂��A<I>null</I> �͍ŏ��̒l�Ƃ��Ĉ������ő���ƈ������A��Q�����̃t���O�Ŏw�肵�܂��B
//     * @param prm_arrCol �~���\�[�g���鏇�Ԃ̗񖼔z��
//     * @param prm_null_is_max true:null���ő�l�Ƃ��܂��^false:null���ŏ��l�Ƃ��܂��B
//     * @throws GwafInternalException �\�[�g���s�\��
//     */
//    public void sortDescBy(String[] prm_arrCol, bool prm_null_is_max) throws GwafInternalException {
//        if (getCount() > 0) {
//            try {
//                sortDescBy(prm_arrCol, 0, _lstTtable.size()-1, prm_null_is_max);
//            } catch (StackOverflowError e) {
//                e.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: �\�[�g���̍ċN�Ăяo�������G�����܂��B���������炵�Ă��������B:"+e);
//            }  catch (Exception e2) {
//                e2.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: �\�[�g���Ɏ��s���܂����B�l��Comparable�ȊO�̃I�u�W�F�N�g�����݂���\��������܂��B:"+e2);
//            }
//        }
//    }
//
//    /**
//     * �����̗�̔z�񏇂̗v�f�l�ŁA�������R�[�h�������\�[�g�����וς��܂�. <BR>
//     * �N�C�b�N�\�[�g�g�p�B<BR>
//     * @param prm_arrCol �����\�[�g���鏇�Ԃ̗񖼔z��
//     * @param prm_begin_index �J�nINDEX
//     * @param prm_end_index �I��INDEX
//     * @param prm_null_is_max true:null���ő�l�Ƃ��܂��^false:null���ŏ��l�Ƃ��܂��B
//     */
//    public void sortBy(String[] prm_arrCol, int prm_begin_index, int prm_end_index, bool prm_null_is_max) {
//        if (prm_begin_index < prm_end_index) {
//            Map pPivotRecord = _lstTtable.get((prm_begin_index + prm_end_index) / 2);
//            _lstTtable.set((prm_begin_index + prm_end_index) / 2, _lstTtable.get(prm_begin_index));
//            int p = prm_begin_index;
//            bool compFlg;
//            Comparable val;
//            Comparable pivot_val;
//            for (int i = prm_begin_index + 1; i <= prm_end_index; i++) {
//                compFlg = false;
//                for (int j = 0; j < prm_arrCol.length; ) {
//                    val = (Comparable) (_lstTtable.get(i).get(prm_arrCol[j]));
//                    pivot_val = (Comparable) (pPivotRecord.get(prm_arrCol[j]));
//                    if (val != null && pivot_val != null) {
//                        if (val.compareTo(pivot_val) < 0) {
//                            compFlg = true;
//                            break;
//                        } else if (val.compareTo(pivot_val) == 0) {
//                            j++;
//                            continue;
//                        } else {
//                            compFlg = false;
//                            break;
//                        }
//                    } else {
//                        if (val == pivot_val) {
//                            j++;
//                            continue;
//                        } else if (val == null) {
//                            if (prm_null_is_max) {
//                                compFlg = false;
//                            } else {
//                                compFlg = true;
//                            }
//                            break;
//                        } else if (pivot_val == null) {
//                            if (prm_null_is_max) {
//                                compFlg = true;
//                            } else {
//                                compFlg = false;
//                            }
//
//                            break;
//                        }
//                    }
//                }
//                if (compFlg) {
//                    p = p + 1;
//                    swapIndex(p, i);
//                }
//
//                if (i % 1000 == 0) {
//                    System.gc();
//                }
//            }
//            _lstTtable.set(prm_begin_index, _lstTtable.get(p));
//            _lstTtable.set(p, pPivotRecord);
//            sortBy(prm_arrCol, prm_begin_index, p - 1, prm_null_is_max);
//            sortBy(prm_arrCol, p + 1, prm_end_index, prm_null_is_max);
//        }
//    }
//
//    /**
//     * �����̗�̔z�񏇂̗v�f�l�ŁA�������R�[�h���~���\�[�g�����וς��܂�. <BR>
//     * �N�C�b�N�\�[�g�g�p�B<BR>
//     * @param prm_arrCol �~���\�[�g���鏇�Ԃ̗񖼔z��
//     * @param prm_begin_index �J�nINDEX
//     * @param prm_end_index �I��INDEX
//     * @param prm_null_is_max true:null���ő�l�Ƃ��܂��^false:null���ŏ��l�Ƃ��܂��B
//     */
//    public void sortDescBy(String[] prm_arrCol, int prm_begin_index, int prm_end_index, bool prm_null_is_max) {
//        if (prm_begin_index < prm_end_index) {
//            Map pPivotRecord = _lstTtable.get((prm_begin_index + prm_end_index) / 2);
//            _lstTtable.set((prm_begin_index + prm_end_index) / 2, _lstTtable.get(prm_begin_index));
//            int p = prm_begin_index;
//            bool compFlg;
//            Comparable val;
//            Comparable pivot_val;
//            for (int i = prm_begin_index + 1; i <= prm_end_index; i++) {
//                compFlg = false;
//                for (int j = 0; j < prm_arrCol.length; ) {
//                    val = (Comparable) (_lstTtable.get(i).get(prm_arrCol[j]));
//                    pivot_val = (Comparable) (pPivotRecord.get(prm_arrCol[j]));
//                    if (val != null && pivot_val != null) {
//                        if (val.compareTo(pivot_val) > 0) {
//                            compFlg = true;
//                            break;
//                        } else if (val.compareTo(pivot_val) == 0) {
//                            j++;
//                            continue;
//                        } else {
//                            compFlg = false;
//                            break;
//                        }
//                    } else {
//                        if (val == pivot_val) {
//                            j++;
//                            continue;
//                        } else if (val == null) {
//                            if (prm_null_is_max) {
//                                compFlg = true;
//                            } else {
//                                compFlg = false;
//                            }
//                            break;
//                        } else if (pivot_val == null) {
//                            if (prm_null_is_max) {
//                                compFlg = false;
//                            } else {
//                                compFlg = true;
//                            }
//                            break;
//                        }
//                    }
//                }
//                if (compFlg) {
//                    p = p + 1;
//                    swapIndex(p, i);
//                }
//
//                if (i % 1000 == 0) {
//                    System.gc();
//                }
//
//            }
//            _lstTtable.set(prm_begin_index, _lstTtable.get(p));
//            _lstTtable.set(p, pPivotRecord);
//            sortDescBy(prm_arrCol, prm_begin_index, p - 1, prm_null_is_max);
//            sortDescBy(prm_arrCol, p + 1, prm_end_index, prm_null_is_max);
//        }
//    }
//
//    /**
//     * �Q�� GwafQueryObject �I�u�W�F�N�g���O���������āA�V���� GwafQueryObject ��Ԃ��B .
//     * �P�ڂ� GwafQueryObject �̌����̃L�[�ƂȂ�ƁAcolkey_q2 �Q�ڂ� GwafQueryObject �̌����̃L�[�ƂȂ��<BR>
//     * ������œ������ꍇ�Ɍ����ƂȂ�܂��B<BR>
//     * �܂��A�쐬���ꂽ�V���� GwafQueryObject �ɂ́Acolkey_q1+"&"+colkey_q2 �Ƃ����񂪑����Ă���A<BR>
//     * ����ɂ̓L�[�ƂȂ�񂪕K�������Ă��܂��B
//     * @param q1 �P�ڂ� GwafQueryObject �I�u�W�F�N�g
//     * @param colkey_q1 �P�ڂ� GwafQueryObject �̌����̃L�[�ƂȂ��
//     * @param q2 �Q�ڂ� GwafQueryObject �I�u�W�F�N�g
//     * @param colkey_q2 �Q�ڂ� GwafQueryObject �̌����̃L�[�ƂȂ��
//     * @return �O���������ꂽ�V����GwafQueryObject
//     */
//    public static GwafQueryObject joinFullOuter(GwafQueryObject q1, String colkey_q1, GwafQueryObject q2, String colkey_q2, int option) {
//        TreeMap<String, Map<String, Object>> mapResult = new TreeMap<String, Map<String, Object>>();
//        String[] cols1 = q1.getColNames();
//        String[] cols2 = q2.getColNames();
//        for (int index_q1 = 0; index_q1 < q1.getCount(); index_q1++) {
//
//            //��̌������R�[�h���P�s�쐬
//            Map<String, Object> mapRec = new HashMap<String, Object>();
//            for (int i = 0; i < cols1.length; i++) {
//                mapRec.put(cols1[i], null);
//            }
//            for (int i = 0; i < cols2.length; i++) {
//                mapRec.put(cols2[i], null);
//            }
//            mapRec.put(colkey_q1+"&"+colkey_q2, null);
//
//            //�f�[�^�o�^
//            for (int i = 0; i < cols1.length; i++) {
//                mapRec.put(cols1[i], q1.get(cols1[i], index_q1));
//            }
//            mapRec.put(colkey_q1+"&"+colkey_q2, q1.getStr(colkey_q1, index_q1)); //�L�[
//
//            //1�s������
//            mapResult.put(q1.getStr(colkey_q1, index_q1), mapRec);
//       }
//
//       for (int index_q2 = 0; index_q2 < q2.getCount(); index_q2++) {
//           Map<String, Object> mapRec;
//           String colkey_val_q2 = q2.getStr(colkey_q2, index_q2);
//           if (mapResult.containsKey(colkey_val_q2)) {
//               //q1�œo�^���Ă�΁A������ɏ㏑��
//               mapRec = mapResult.get(colkey_val_q2);
//           } else {
//               //������΋�̌������R�[�h���P�s�쐬
//               mapRec = new HashMap<String, Object>();
//
//               for (int i = 0; i < cols1.length; i++) {
//                   mapRec.put(cols1[i], null);
//               }
//
//               for (int i = 0; i < cols2.length; i++) {
//                   mapRec.put(cols2[i], null);
//               }
//               mapRec.put(colkey_q1+"&"+colkey_q2, null);
//           }
//           //�f�[�^�o�^
//           for (int i = 0; i < cols2.length; i++) {
//               mapRec.put(cols2[i], q2.get(cols2[i], index_q2));
//           }
//           if (mapRec.get(colkey_q1+"&"+colkey_q2) ==  null) {
//               mapRec.put(colkey_q1+"&"+colkey_q2, q2.getStr(colkey_q2, index_q2)); //�L�[
//           }
//
//           //1�s������
//           mapResult.put(q2.getStr(colkey_q2, index_q2), mapRec);
//        }
//        GwafQueryObject qryResult = new GwafQueryObject();
//
//
//        Set<String> setCol_key = mapResult.keySet();
//        Iterator<String> iteCol_key = setCol_key.iterator();
//        for (int i = 0; iteCol_key.hasNext(); i++) {
//            String key = iteCol_key.next();
//            Map<String, Object> mapRec = mapResult.get(key);
//            qryResult._lstTtable.add(mapRec);
//        }
//        return qryResult;
//    }
//
//
//    public static GwafQueryObject joinFullOuter(GwafQueryObject q1, String colkey_q1, GwafQueryObject q2, String colkey_q2) {
//         return  GwafQueryObject.joinFullOuter(q1, colkey_q1, q2, colkey_q2, 0);
//    }
//
//
//
//
//
//
//
//    /**
//     * A��B�̃��R�[�h�̏ꏊ(INDEX)�����ւ��܂�. <BR>
//     * @param prm_index_A ����ւ��Ώۃ��R�[�hINDEX A
//     * @param prm_index_B ����ւ��Ώۃ��R�[�hINDEX B
//     */
//    public void swapIndex(int prm_index_A, int prm_index_B)  {
//        Map pRecordA = _lstTtable.get(prm_index_A);
//        _lstTtable.set(prm_index_A, _lstTtable.get(prm_index_B));
//        _lstTtable.set(prm_index_B, pRecordA);
//    }
//
//    /**
//     * �f�[�^�̓��e�擾. <BR>
//     * @return ������\���̃f�[�^�̓��e
//     */
//    public String dump() {
//        if (null == _lstTtable) {
//            return "_lstTtable��null�ł�";
//        } else if (_lstTtable.isEmpty()) {
//            return "_lstTtable��Empty�ł�";
//        } else {
//            StringBuffer buffer = new StringBuffer();
//            for (int i = 0; i < _lstTtable.size(); i++) {
//                Map map = _lstTtable.get(i);
//                buffer.append("["+i+"]="+map+" \n");
//            }
//            return buffer.toString();
//        }
//    }
//
//}

