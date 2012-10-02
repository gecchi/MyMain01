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
 * レコードを削除します。 .
 * @param prm_index レコードindex（0～)
 * @throws GwafInternalException 引数のレコードindexが範囲外
 */
void GgafQuery::removeRow(int prm_index) {
#ifdef MY_DEBUG
    if (_lstTtable.size() < prm_index) {
        throwGgafCriticalException(
                "GgafQuery#removeRow: 削除レコードINDEXは存在しません。本クエリsize="<<_lstTtable.size()<<"/引数の削除INDEX="<<prm_index);
    }
#endif
    _lstTtable.erase(_lstTtable.begin() + prm_index);
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
    _lstTtable.erase(_lstTtable.begin() + prm_start_index, _lstTtable.begin() + (prm_end_index + 1)); //+1は正しい。
}

void GgafQuery::addRow(GgafRecord* prm_pRow) {
    _lstTtable.push_back(prm_pRow);
}
/**
 * AとBのレコードの場所(INDEX)を入れ替えます. <BR>
 * @param prm_index_A 入れ替え対象レコードINDEX A
 * @param prm_index_B 入れ替え対象レコードINDEX B
 */
void GgafQuery::swapIndex(int prm_index_A, int prm_index_B) {
    GgafRecord* pRecordA = _lstTtable[prm_index_A];
    _lstTtable[prm_index_A] = _lstTtable[prm_index_B];
    _lstTtable[prm_index_B] = pRecordA;
}
/**
 * 引数の列の配列順の要素値で、内部レコードを昇順ソートし並べ変えます. <BR>
 * クイックソート使用。<BR>
 * @param prm_col 昇順ソートする順番の列名配列
 * @param prm_col_num 列名配列要素数
 * @param prm_begin_index 開始INDEX
 * @param prm_end_index 終了INDEX
 * @param prm_blank_is_max true:空文字("")を最大値とします／false:空文字("")を最小値とします。
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
//元ネタのJAVA版
//TODO:必要なメソッドから移植していこう！

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
// * SQLのSELECTの結果（クエリ）を格納し、オブジェクトとして扱うことを目的としたクラスです.  <BR>
// * クエリ列名は大文字小文字区別しています.  <BR>
// * @version 0.001.20070313
// * @since 0.001.20070313
// * @author Masatoshi Tsuge
// */
//public class GwafQueryObject implements Serializable {
//
//
//    private static final long serialVersionUID = 8980628699444387817L;
//
//    /** クエリの列名と値のペアをもったMapのListです */
//    public List<Map<String, Object>> _lstTtable = null;
//
//
//    /**
//     * ResultSet よりインスタンスを生成します.  <BR>
//     * ResultSet から全て getObject によりデータを取得します。<BR>
//     * 注意：<BR>
//     * １．件数によってはメモリを圧迫するかも知れません。<BR>
//     * ２．JDBCの完全対応ではないデータベースのデータ型の場合は、精度が落ちるかもしれません。<BR>
//     * getObjectで取得しても問題ないデータ型かどうか確認して下さい。<BR>
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
//     * クエリの列名と値のペアをもったMapのListよりインスタンスを生成します.  <BR>
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
//     * 内部要素０のインスタンスを生成します.  <BR>
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
//     * 本クエリから、指定条件を満たす一部（又は全部)のインデックスを返します.  <BR>
//     * 指定条件は、以下の 条件になります。<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値 ＝第２引数（prm_equalVal)」<BR>
//     * 上記の「＝」は、<B>equals()</B> メソッドによる判定結果がtrueを表します。但し、第２引数が<I>null</I>であった場合は
//     * 保留：equals() メソッドではな<B> 値 == null </B> という判定を行います。<BR>
//     * 第１引数(prm_col)の列名が、自分自身のクエリに存在しない場合は、条件不一致と扱われます（例外にはなりません）。
//     * 判定対象の値の型が一致しない場合は、キャストが不可能（equals()ができない）であれば例外になります。<BR>
//     * @param <T> 判定対象の値の型
//     * @param prm_col 判定対象の列名
//     * @param prm_equalVal 条件値
//     * @return インデックス
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
//     * 本クエリから、indexで指定されたレコード1件をシャローコピーし、新たな GwafQueryObject を生成します.  <BR>
//     * 引数の prm_beginIndex が自分自身の保持する要素数を超える場合、内部要素 0 の GwafQueryObject が生成され
//     * 返されます（例外にはなりません）。<BR>
//     * @param prm_beginIndex 取得index(0～）
//     * @return 指定の１件の要素を持った GwafQueryObject
//     */
//    public GwafQueryObject extract(int prm_beginIndex) {
//        List<Map<String, Object>> lisQuery = new Vector<Map<String, Object>>();
//        lisQuery.add(_lstTtable.get(prm_beginIndex));
//        return new GwafQueryObject(lisQuery);
//    }
//
//    /**
//     * 本クエリから、範囲指定された一部（又は全部）のレコードをシャローコピーした、新たな GwafQueryObject を生成します.  <BR>
//     * 引数の prm_beginIndex が自分自身の保持する要素数を超える場合、あるいは引数の prm_length が 0 の場合、
//     * 内部要素 0 の GwafQueryObject が生成され返されます（例外にはなりません）。
//     * @param prm_beginIndex 範囲指定開始index(0～）
//     * @param prm_length 取得レコード数（0～)
//     * @return 指定領域の要素を持った GwafQueryObject
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
//     * 本クエリから、指定条件を満たす一部（又は全部)のレコードをシャローコピーした、新たな GwafQueryObject を生成します.  <BR>
//     * 指定条件は、以下の 条件になります。<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての文字列表現 ＝第２引数（prm_equalVal)文字列」<BR>
//     * 上記の「＝」は、<B>String#equals()</B> メソッドによる判定結果がtrueを表します。但し、第２引数が<I>null</I>であった場合は
//     * equals() メソッド判定ではなく<B> 値 == null </B> という判定を行います。<BR>
//     * 第１引数(prm_col)の列名が、自分自身のクエリに存在しない場合は、条件不一致と扱われます（例外にはなりません）。
//     * 判定対象の値の型が一致しない場合は、キャストが不可能（equals()ができない）であれば例外になります。<BR>
//     * @param <T> 判定対象の値の型
//     * @param prm_col 判定対象の列名
//     * @param prm_equalVal 条件値
//     * @return 指定条件を満たすレコードを内部保持するGwafQueryObject
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
//     * 本クエリから、指定条件を満たす一部（又は全部)のレコードをシャローコピーした、新たな GwafQueryObject を生成します.  <BR>
//     * 指定条件は、以下の 条件になります。<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値 ＝第２引数（prm_equalVal)」<BR>
//     * 上記の「＝」は、<B>equals()</B> メソッドによる判定結果がtrueを表します。但し、第２引数が<I>null</I>であった場合は
//     * 保留：equals() メソッドではな<B> 値 == null </B> という判定を行います。<BR>
//     * 第１引数(prm_col)の列名が、自分自身のクエリに存在しない場合は、条件不一致と扱われます（例外にはなりません）。
//     * 判定対象の値の型が一致しない場合は、キャストが不可能（equals()ができない）であれば例外になります。<BR>
//     * @param <T> 判定対象の値の型
//     * @param prm_col 判定対象の列名
//     * @param prm_equalVal 条件値
//     * @return 指定条件を満たすレコードを内部保持するGwafQueryObject
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
//     * 本クエリから、指定条件を満たす一部（又は全部)のレコードをシャローコピーした、新たな GwafQueryObject を生成します.  <BR>
//     * 指定条件は、以下の 条件になります。<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値の文字列表現 が 第２引数の正規表現文字列（prm_reg)のパターンに一致する時」<BR>
//     * 第１引数(prm_col)の列名が、自分自身のクエリに存在しない場合は、条件不一致と扱われます（例外にはなりません）。
//     * 第２引数が<I>null</I>であった場合は例外になります。
//     * @param prm_col 判定対象の列名
//     * @param prm_equalVal 条件値
//     * @return 指定条件を満たすレコードを内部保持するGwafQueryObject
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
//            throw new GwafInternalException("GwafQueryObject#extractMuchString: 第２引数の正規表現文字列が null です。");
//        }
//        return new GwafQueryObject(lisQuery);
//    }
//    /**
//     * 本クエリから、指定条件を満たす一部（又は全部)のレコードをシャローコピーした、新たな GwafQueryObject を生成します.  <BR>
//     * 指定条件は、以下に列挙する条件の OR 条件になります。<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値 ＝第２引数の第１要素値（prm_arrEqualVal[0])」<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値 ＝第２引数の第２要素値（prm_arrEqualVal[1])」<BR>
//     * 　　　　　　　　　　　・<BR>
//     * 　　　　　　　　　　　・<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値 ＝第２引数の最終要素値（prm_arrEqualVal[prm_arrEqualVal.length])」
//     * <BR>
//     * 上記の「＝」は、<B>equals()</B> メソッドによる判定結果がtrueを表します。但し、第２引数の要素値が<I>null</I>であった場合は
//     * equals() メソッドではな<B> 値 == null </B> という判定を行います。<BR>
//     * 第２引数(prm_arrEqualVal)自体が<I>null</I>の場合、 内部要素 0 の GwafQueryObject が生成され返されます。
//     * 第１引数(prm_col)の列名が、自分自身のクエリに存在しない場合は、条件不一致と扱われます（例外にはなりません）。
//     * 判定対象の値の型が一致しない場合は、キャストが不可能（equals()ができない）であれば例外になります。<BR>
//     * @param <T> 判定対象の値の型
//     * @param prm_col 判定対象の列名
//     * @param prm_arrEqualVal 条件値の配列
//     * @return 指定条件を満たすレコードを内部保持するGwafQueryObject
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
//     * 本クエリから、指定条件を満たす一部（又は全部)のレコードをシャローコピーした、新たな GwafQueryObject を生成します.  <BR>
//     * 指定条件は、以下の 条件になります。<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値 ≠ 第２引数（prm_equalVal)」<BR>
//     * 上記の「≠」は、<B>equals()</B> メソッドによる判定結果がfalseを表します。但し、第２引数が<I>null</I>であった場合は
//     * equals() メソッドではな<B> 値 != null </B> という判定を行います。<BR>
//     * 第１引数(prm_col)の列名が、自分自身のクエリに存在しない場合は、条件不一致と扱われます（例外にはなりません）。
//     * 判定対象の値の型が一致しない場合は、キャストが不可能（equals()ができない）であれば例外になります。<BR>
//     * @param <T> 判定対象の値の型
//     * @param prm_col 判定対象の列名
//     * @param prm_notEqualVal 条件値
//     * @return 指定条件を満たすレコードを内部保持するGwafQueryObject
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
//     * 本クエリから、指定条件を満たす一部（又は全部)のレコードをシャローコピーした、新たな GwafQueryObject を生成します.  <BR>
//     * 指定条件は、以下に列挙する条件の OR 条件になります。<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値 ≠ 第２引数の第１要素値（prm_arrEqualVal[0])」<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値 ≠ 第２引数の第２要素値（prm_arrEqualVal[1])」<BR>
//     * 　　　　　　　　　　　・<BR>
//     * 　　　　　　　　　　　・<BR>
//     * 「自身の第１引数（prm_col）の列名の全ての値 ≠ 第２引数の最終要素値（prm_arrEqualVal[prm_arrEqualVal.length])」
//     * <BR>
//     * 上記の「≠」は、<B>equals()</B> メソッドによる判定結果がfalseを表します。但し、第２引数の要素値が<I>null</I>であった場合は
//     * equals() メソッドではな<B> 値 != null </B> という判定を行います。<BR>
//     * 第２引数(prm_arrEqualVal)自体が<I>null</I>の場合、 内部要素 0 の GwafQueryObject が生成され返されます。
//     * 第１引数(prm_col)の列名が、自分自身のクエリに存在しない場合は、条件不一致と扱われます（例外にはなりません）。
//     * 判定対象の値の型が一致しない場合は、キャストが不可能（equals()ができない）であれば例外になります。<BR>
//     * @param <T> 判定対象の値の型
//     * @param prm_col 判定対象の列名
//     * @param prm_arrNotEqualVal 条件値の配列
//     * @return 指定条件を満たすレコードを内部保持するGwafQueryObject
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
//                if (max.compareTo(val) < 0 ) { //valが大きい
//                    max = val;
//                } else if (max.compareTo(val) > 0 ) { //valが小さい
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
//                if (min.compareTo(val) < 0 ) { //valが大きい
//
//                } else if (min.compareTo(val) > 0 ) { //valが小さい
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
//                if (max < val ) { //valが大きい
//                    max = val;
//                } else if (max > val ) { //valが小さい
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
//                if (min < val ) { //valが大きい
//
//                } else if (min > val ) { //valが小さい
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
//     * 現在のクエリレコード件数を取得します.  <BR>
//     * @return 件数
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
//     * 指定されたレコード情報を Map で取得します.  <BR>
//     * @param prm_index レコードindex（0～)
//     * @return 指定レコードのMap
//     */
//    public Map<String, Object> getRecord(int prm_index) {
//        return _lstTtable.get(prm_index);
//    }
//
//
//    /**
//     * 指定された列の値を上書きする .
//     * 存在しない列名を指定した場合はエラーになる.
//     * @param <T>
//     * @param prm_col  列名
//     * @param prm_index レコードindex（0～)
//     * @param prm_data 上書きする値
//     * @return
//     * @throws GwafInternalException
//     */
//    public void set(String prm_col, int prm_index, Object prm_data) throws GwafInternalException {
//        Map rec = _lstTtable.get(prm_index);
//        if (rec.containsKey(prm_col)) {
//            rec.put(prm_col, prm_data);
//        } else {
//            throw new GwafInternalException("GwafQueryObject#set ： ＜警告＞レコード"+prm_index+"の行で、存在しない列名["+prm_col+"]の上書きを試みました。");
//        }
//    }
//
//    /**
//     * 列の存在チェック .
//     * 存在する場合 true。
//     * クエリが0 或いは、引数が null の場合 false
//     * @param prm_col チェックする列名
//     * @return 存在する場合 true
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
//     * 指定された列の値が、null 又は toString().equals("") ならば設定、
//     * 既にデータがある場合はセパレータ文字を追加して末尾にデータ追加 .
//     * 存在しない列名、文字列フィールド以外を指定した場合はエラーになる.
//     * @param <T>
//     * @param prm_col  列名
//     * @param prm_index レコードindex（0～)
//     * @param prm_data 値
//     * @param prm_sepa セパレータ
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
//            throw new GwafInternalException("GwafQueryObject#set ： ＜警告＞レコード"+prm_index+"の行で、存在しない列名["+prm_col+"]の上書きを試みました。");
//        }
//    }
//
//    /**
//     * 指定されたレコード情報を上書きコピーする.  <BR>
//     * 追加元レコードに存在しない列名が、引数レコード側に存在した場合はエラーになる.
//     * 追加元レコードに存在しない列名が、引数レコード側に存在した場合はエラーになる.
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
//                throw new GwafInternalException("GwafQueryObject#setRecord ： ＜警告＞レコード"+prm_index+"の行で、存在しない列名["+col_prm+"]の上書きを試みました。");
//            }
//        }
//    }
//
//
//    /**
//     * 指定された列（KEY列）の値が一致したレコードを全て上書きする .
//     * 注意：引数のGwafQueryObjectは破壊されます。<BR>
//     *       これは上書きできたレコードを引数のGwafQueryObjectから順にremove()し、処理を最適化しているためです。<BR>
//     *       したがって、処理後、引数のGwafQueryObjectは上書き出来なかったレコードの余りが残ります。<BR>
//     * @param prm_arr_key_col 上書きを行う条件のKEY列
//     * @param prm_qry 上書きするクエリ
//     * @throws GwafInternalException
//     */
//    public void overwriteEquals(String[] prm_arr_key_col, GwafQueryObject prm_qry) throws GwafInternalException {
//        if (prm_qry == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: 追加レコード prm_qry が null です");
//        }
//        if (prm_qry.getCount() == 0) {
//            return;
//        }
//        //１レコードだけ列存在チェック
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
//            //この時点でエラー。
//            //エラー情報の文字列を作成する。
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
//            throw new GwafInternalException("GwafQueryObject#overwrite: 追加レコード列名と列数が完全一致しませんでした。本クエリ列→"+wk2+"／引数のクエリ列→"+wk1);
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
//                        //OK 上書き対象である可能背を継続
//                    } else {
//                        //上書きを却下
//                        overwrite_able = false;
//                        break;
//                    }
//                }
//                if (overwrite_able) {
//                    //全KEYカラムの値が一致のため上書き
//                    _lstTtable.set(i, prm_qry._lstTtable.get(j));
//                    was_overwrite = true;
//                    while(prm_qry._lstTtable.remove(key_value_prm_qry)); //上書きに使用されたレコードはもう必要ない。
//                    break; //上書きでBreak.
//                           //これは仮に２レコード以上書き可能なKey値がprm_qryに存在しても、
//                           //最初のKey値が採用されることを意味します
//                } else {
//                    //次のprm_qryのレコードへ期待する
//                }
//            }
//            if (was_overwrite) {
//                //上書きしたのであれば何もしない
//            } else {
//                //上書きできなければ追加
//                _lstTtable.add(mapPrmQry);
//            }
//        }
//        //ここで上書き出来なかった引数クエリは余っています
//        _lstTtable.addAll(prm_qry._lstTtable);
//    }
//
//    /**
//     * 指定された列の値を取り出します.  <BR>
//     * 取得値が <I>null</I> であった場合、そのまま<I>null</I> が返されます。<BR>
//     * 引数の列名が存在しなかった場合も <I>null</I> が返されます。
//     * @param <T> 取得値の型
//     * @param prm_col 列名
//     * @param prm_index レコードindex（0～)
//     * @return 取得値 又は <I>null</I>
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
//            GwafDebug.out("GwafQueryObject#get ： ＜警告＞レコード"+prm_index+"の行で、存在しない列名["+prm_col+"]の取得を試みました。");
//            return null;
//        }
//    }
//
//    /**
//     * 指定された列の値を取り出します.  <BR>
//     * 内部で {@link #get(String, int)} で得た結果を取得し、
//     * 取得値が  <I>null</I> であった場合のみ、第３引数の値が返されます。その際、第３引数が <I>null</I>
//     * であった場合は、そのまま<I>null</I> が戻り値になります。<BR>
//     * @param <T> 取得値の型
//     * @param prm_col 列名
//     * @param prm_index レコードindex（0～)
//     * @param prm_obj_ifNull 取得値が<I>null</I> であった場合に返す値
//     * @return 取得値
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
//            GwafDebug.out("GwafQueryObject#getNvl ： ＜情報＞レコード"+prm_index+"の行で、存在しない列名["+prm_col+"]の取得を試みました。");
//            return null;
//        }
//    }
//
//    /**
//     * 指定された列とINDEXの値を文字列に変換して取り出します.  <BR>
//     * 内部で得た結果をtoString()し返します。<BR>
//     * 取得結果が <I>null</I> であった場合、そのまま<I>null</I> が返されます。<BR>
//     * 引数の列名が存在しなかった場合も <I>null</I> が返されます。(※ご注意下さい)<BR>
//     * prm_indexが範囲外であった場合も <I>null</I> が返されます。(※ご注意下さい)<BR>
//     * @param prm_col 列名
//     * @param prm_index レコードindex（0～)
//     * @return 取得文字列 又は <I>null</I>
//     */
//    public String getVal(String prm_col, int prm_index) {
//        Map rec = null;
//        try {
//            rec = _lstTtable.get(prm_index);
//        } catch (IndexOutOfBoundsException e) {
//            //GwafDebug.out("GwafQueryObject#getVal: ＜情報＞(\""+prm_col+"\","+prm_index+")は、Index範囲外です。nullを返しました。");
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
//            //GwafDebug.out("GwafQueryObject#get ： ＜情報＞レコード"+prm_index+"の行で、存在しない列名["+prm_col+"]の取得を試みました。");
//            return null;
//        }
//    }
//
//    /**
//     * 指定された列とINDEXの値を文字列に変換して取り出します.  <BR>
//     * 但し、{@link #getVal(String, int) getVal(String, int)}の結果が <I>null</I> であった場合のみ、第３引数の値を
//     * toString() した値が返されます。その際、第３引数が <I>null</I> であった場合は、そのまま<I>null</I>
//     * が戻り値になります。<BR>
//     * @param prm_col 列名
//     * @param prm_index レコードindex（0～)
//     * @return 取得文字列
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
//     * 指定された列とINDEXの値を数値(Integer)に変換して取り出します.  <BR>
//     * 内部で {@link #getVal(String, int) getVal(String, int)} で得た結果を Integer.parseInt() します。
//     * 但し、{@link #getVal(String, int) getVal(String, int)}の結果が <I>null</I> であった場合、0 が返されます。<BR>
//     * @param prm_col 列名
//     * @param prm_index レコードindex（0～)
//     * @return 取得数値(Integer)
//     * @throws GwafInternalException 数値(Integer)に変換出来ない場合
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
//     * 指定された列とINDEXの値を数値(BigDecimal)に変換して取り出します.  <BR>
//     * 内部で {@link #get(String, int) get(String, int)} で得た結果を文字列に変換し、BigDecimalのコンストラクタに渡しています。
//     * 但し、{@link #get(String, int) get(String, int)}の結果が <I>null</I> であった場合、0 が返されます。<BR>
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
//     * 指定された列とINDEXの値を数値(Integer)に変換して取り出します.  <BR>
//     * 内部で {@link #getVal(String, int) getVal(String, int)} で得た結果を Integer.parseInt() します。
//     * 但し、{@link #getVal(String, int) getVal(String, int)}の結果が  <I>null</I> であった場合、第２引数の
//     * 数値(Integer)が返されます。<BR>
//     * @param prm_col 列名
//     * @param prm_index レコードindex（0～)
//     * @return 取得数値(Integer)
//     * @throws GwafInternalException 数値(Integer)に変換出来ない場合
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
//     * 指定された列とINDEXの値を数値(Integer)に変換して取り出します.  <BR>
//     * 内部で {@link #getVal(String, int) getVal(String, int)} で得た結果を Integer.parseInt() します。
//     * 但し、{@link #getVal(String, int) getVal(String, int)}の結果が  <I>null</I> であった場合と、
//     * 数値変換に失敗した場合は、第３引数の数値(Integer)が返されます。<BR>
//     * @param prm_col 列名
//     * @param prm_index レコードindex（0～)
//     * @param prm_intSubstitute 数値変換に失敗時の数値
//     * @return 取得数値(Integer) or 失敗時の数値
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
//     * 指定された列とINDEXの値を文字列に変換して取り出します.  <BR>
//     * 内部で {@link #getVal(String, int) getVal(String, int)} で得た結果を返しますが、結果が <I>null</I>
//     * であった場合、""(空文字）が返されます。<BR>
//     * さらに、取得結果にトリム処理が行われます。<BR>
//     * @param prm_col 列名
//     * @param prm_index レコードindex（0～)
//     * @return 取得文字列 又は ""(空文字）
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
//     * 内部管理している全列名を配列で取得します. <BR>
//     * 具体的には第１レコード（INDEX=0）の列名を取得し、配列で返します。列名の順番は保証されません。<BR>
//     * 内部保持レコード数が0の場合、空の配列(String[] {})が返されます。<BR>
//     * @return 列名の配列
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
//     * 指定列の値全てを List(Vectorインスタンス) で取得します. <BR>
//     * 指定した列名が存在する場合、内部要素は全て{@link #get(String, int) get(String, int)}で取得され、Listに追加されます。<BR>
//     * 但し、指定した列名が存在しない場合は、<I>null</I> を得るのではなく、処理はスキップされます。
//     * 全てのレコードに指定した列名が存在しない場合、内部要素0の(Vectorインスタンス)が返される事になります。
//     * @param prm_colname 列名
//     * @return 指定列の値の List(Vectorインスタンス)
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
//     * 指定列の値全てを List(Vectorインスタンス) で取得します. <BR>
//     * 指定した列名が存在する場合、内部要素は全て{@link #getNvl(String, int, Object) getNvl(String, int, Object)}で取得され、
//     * Listに追加されます。<BR>
//     * 但し、指定した列名が存在しない場合は、<I>null</I> を得るのではなく処理はスキップされます。
//     * 全てのレコードに指定した列名が存在しない場合、内部要素0の(Vectorインスタンス)が返される事になります。
//     * @param <T>
//     * @param prm_colname 列名
//     * @param prm_obj_ifValNull  内容の値取得が<I>null</I>であった場合、置き換えてListに格納する値
//     * @return 指定列の値の List(Vectorインスタンス)
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
//     * 本クラスのデータ保持フィールド(クエリの列名と値のペアをもったMapのList)を返します. <BR>
//     * @return データ保持フィールド(クエリの列名と値のペアをもったMapのList)
//     */
//    public List<Map<String, Object>> getListTable() {
//        return _lstTtable;
//    }
//
//    /**
//     * 本クエリに列を１つ追加します. <BR>
//     * 追加する List の size() は、{@link #getCount() #getCount()}と同じである必要があります。
//     * 追加する List の要素数が不一致の場合例外となります。
//     * 但し、列が一つも存在しない場合は、例外とならず、最初に追加した列の要素数が基準となります。
//     * @param prm_colname 追加する列の列名
//     * @param prm_lstColVal 追加する列の値のリスト
//     * @throws GwafInternalException 要素数不一致
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
//                throw new GwafInternalException("GwafQueryObject#addCol: 要素数が不一致です。this.getCount()→"+getCount()+", prm_lstColVal.size()→"+(prm_lstColVal==null?null:prm_lstColVal.size()));
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && getRecord(i).containsKey(prm_colname)) {
//                        GwafDebug.out("＜警告＞GwafQueryObject#addCol: 列["+prm_colname+"]は既に存在しています。意図していますか？");
//                    }
//                    getRecord(i).put(prm_colname, prm_lstColVal.get(i));
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableがnullです");
//        }
//    }
//
//    /**
//     * 本クエリに列を１つ追加します. <BR>
//     * 追加する 配列 の length は、{@link #getCount() #getCount()}と同じである必要があります。
//     * 追加する 配列 の要素数が不一致の場合例外となります。
//     * 但し、列が一つも存在しない場合は、例外とならず、最初に追加した列の要素数が基準となります。
//     * @param prm_colname 追加する列の列名
//     * @param prm_arrColVal 追加する列の値の配列
//     * @throws GwafInternalException 要素数不一致
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
//                throw new GwafInternalException("GwafQueryObject#addCol: 要素数が不一致です。this.getCount()→"+getCount()+", prm_arrColVal.length→"+(prm_arrColVal==null?null:prm_arrColVal.length));
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && getRecord(i).containsKey(prm_colname)) {
//                        GwafDebug.out("＜警告＞GwafQueryObject#addCol: 列["+prm_colname+"]は既に存在しています。意図していますか？");
//                    }
//                    getRecord(i).put(prm_colname, prm_arrColVal[i]);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableがnullです");
//        }
//    }
//
//    /**
//     * 本クエリに列を１つ追加します. <BR>
//     * 追加した列のデータは全て null になります。
//     * @param prm_colname
//     * @throws GwafInternalException
//     */
//    public void addCol(String prm_colname) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableが0件のため追加できません");
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && getRecord(i).containsKey(prm_colname)) {
//                        GwafDebug.out("＜警告＞GwafQueryObject#addCol: 列["+prm_colname+"]は既に存在しています。意図していますか？");
//                    }
//                    getRecord(i).put(prm_colname, null);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableがnullです");
//        }
//    }
//
//    /**
//     * 本クエリに列を１つ追加します. <BR>
//     * 追加した列のデータは全て prm_val になります。
//     * @param prm_colname
//     * @throws GwafInternalException
//     */
//    public void addCol(String prm_colname, Object prm_val) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableが0件のため追加できません");
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && getRecord(i).containsKey(prm_colname)) {
//                        GwafDebug.out("＜警告＞GwafQueryObject#addCol: 列["+prm_colname+"]は既に存在しています。意図していますか？");
//                    }
//                    getRecord(i).put(prm_colname, prm_val);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableがnullです");
//        }
//    }
//
//    /**
//     * 本クエリに列に値をセットします. <BR>
//     * 追加する List の size() は、{@link #getCount() #getCount()}と同じである必要があります。
//     * 追加する List の要素数が不一致の場合例外となります。
//     * また、追加する列が既に存在しなければエラーになります。<BR>
//     * @param prm_colname 追加する列の列名
//     * @param prm_lstColVal 追加する列の値のリスト
//     * @throws GwafInternalException 要素数不一致
//     */
//    public void setCol(String prm_colname, List prm_lstColVal) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: 列["+prm_colname+"]が存在しません。");
//            } else if (getCount() != prm_lstColVal.size()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: 要素数が不一致です。this.getCount()→"+getCount()+", prm_lstColVal.size()→"+(prm_lstColVal==null?null:prm_lstColVal.size()));
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && !getRecord(i).containsKey(prm_colname)) {
//                        throw new GwafInternalException("GwafQueryObject#addCol: 列["+prm_colname+"]が存在しません。");
//                    }
//                    getRecord(i).put(prm_colname, prm_lstColVal.get(i));
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableがnullです");
//        }
//    }
//
//    /**
//     * 本クエリに列に値をセットします. <BR>
//     * 追加する 配列 の length は、{@link #getCount() #getCount()}と同じである必要があります。
//     * 追加する 配列 の要素数が不一致の場合例外となります。
//     * また、追加する列が既に存在しなければエラーになります。<BR>
//     * @param prm_colname 追加する列の列名
//     * @param prm_arrColVal 追加する列の値の配列
//     * @throws GwafInternalException 要素数不一致
//     */
//    public void setCol(String prm_colname, String[] prm_arrColVal) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: 列["+prm_colname+"]が存在しません。");
//            } else if (getCount() != prm_arrColVal.length) {
//                throw new GwafInternalException("GwafQueryObject#addCol: 要素数が不一致です。this.getCount()→"+getCount()+", prm_arrColVal.length→"+(prm_arrColVal==null?null:prm_arrColVal.length));
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && !getRecord(i).containsKey(prm_colname)) {
//                        throw new GwafInternalException("GwafQueryObject#addCol: 列["+prm_colname+"]が存在しません。");
//                    }
//                    getRecord(i).put(prm_colname, prm_arrColVal[i]);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableがnullです");
//        }
//    }
//
//    /**
//     * 本クエリに列に値をセットします. <BR>
//     * 列のデータは全て null になります。
//     * また、追加する列が既に存在しなければエラーになります。<BR>
//     * @param prm_colname
//     * @throws GwafInternalException
//     */
//    public void setColNull(String prm_colname) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableが0件のため追加できません");
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && !getRecord(i).containsKey(prm_colname)) {
//                        throw new GwafInternalException("GwafQueryObject#addCol: 列["+prm_colname+"]が存在しません。");
//                    }
//                    getRecord(i).put(prm_colname, null);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableがnullです");
//        }
//    }
//
//    /**
//     * 本クエリに列に値をセットします. <BR>
//     * 列のデータは全て prm_val になります。
//     * また、追加する列が既に存在しなければエラーになります。<BR>
//     * @param prm_colname
//     * @throws GwafInternalException
//     */
//    public void setCol(String prm_colname, Object prm_val) throws GwafInternalException {
//        if (_lstTtable != null) {
//            if (_lstTtable.isEmpty()) {
//                throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableが0件のため追加できません");
//            } else {
//                for (int i = 0; i < getCount(); i ++) {
//                    if (i == 0 && !getRecord(i).containsKey(prm_colname)) {
//                        throw new GwafInternalException("GwafQueryObject#addCol: 列["+prm_colname+"]が存在しません。");
//                    }
//                    getRecord(i).put(prm_colname, prm_val);
//                }
//            }
//        } else {
//            throw new GwafInternalException("GwafQueryObject#addCol: _lstTtableがnullです");
//        }
//    }
//
//
//
//
//
//    /**
//     * 本クエリ末尾に空レコード(全部null)を追加します。
//     * @return 追加されたindex位置
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
//     * 本クエリの引数指定の位置に空レコード(全部null)を追加します。
//     * @param prm_index 空レコード(全部null)を追加するINDEX
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
//     * 本クエリにレコードを追加します. <BR>
//     * 追加するレコードの列名と数が一致しない場合エラーになります。<BR>
//     * @param prm_mapRow 追加するレコード（列名と値のペア）
//     * @throws GwafInternalException 追加可能列名無し
//     */
//    public void insertRow(int prm_index, Map<String, Object> prm_mapRow) throws GwafInternalException {
//        if (prm_mapRow == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: 追加レコード prm_mapRow が null です");
//        }
//        //列存在チェック
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
//            throw new GwafInternalException("GwafQueryObject#insertRow: 追加レコード列名と列数が完全一致しませんでした。本クエリ列→"+getRecord(0)+"／引数のレコード→"+prm_mapRow);
//        } else {
//            _lstTtable.add(prm_index, prm_mapRow);
//        }
//    }
//
//    /**
//     * 本クエリ末尾にレコードを追加します. <BR>
//     * 追加するレコードの列名と数が一致しない場合エラーになります。<BR>
//     * 自身のクエリが空(初めてのaddRow)である場合、そのレコードが本クエリの列となり受け入れます。<BR>
//     * @param prm_mapRow 追加するレコード（列名と値のペア）
//     * @throws GwafInternalException 追加可能列名無し
//     */
//    public void addRow(Map<String, Object> prm_mapRow) throws GwafInternalException {
//        if (prm_mapRow == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: 追加レコード prm_mapRow が null です");
//        }
//        if (_lstTtable.isEmpty()) {
//            //最初の１行は無条件受け入れ
//            _lstTtable.add(prm_mapRow);
//        } else {
//            //列名一致チェック
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
//                throw new GwafInternalException("GwafQueryObject#addRow: 追加レコード列名と列数が完全一致しませんでした。本クエリ列→"+getRecord(0)+"／引数のレコード→"+prm_mapRow+" iExistNum="+iExistNum+" arrCol.length="+arrCol.length);
//            } else {
//                _lstTtable.add(prm_mapRow);
//            }
//        }
//    }
//
//    /**
//     * 本クエリ末尾にレコードを追加します. <BR>
//     * 追加するレコードの列名と数が一致しない場合エラーになります。<BR>
//     * 自身のクエリが空(初めてのaddRow)である場合、そのレコードが本クエリの列となり受け入れます。<BR>
//     * @param prm_cols 追加する列名の配列
//     * @param prm_values 対応する値の配列
//     * @throws GwafInternalException
//     */
//    public void addRow(String[] prm_cols, Object[] prm_values) throws GwafInternalException {
//        if (prm_cols == null || prm_values == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: 引数が null です。");
//        }
//        Map<String, Object> mapRow = new Hashtable<String, Object>();
//        for (int i = 0; i < prm_cols.length; i++) {
//            mapRow.put(prm_cols[i], prm_values[i]);
//        }
//        addRow(mapRow);
//    }
//
//    /**
//     * 本クエリ末尾にレコードを追加します. <BR>
//     * 自身のクエリが空(初めてのaddRow)である場合、そのレコードが本クエリの列となり受け入れます。<BR>
//     * @param prm_cols 列名
//     * @param prm_values 値
//     * @throws GwafInternalException
//     */
//    public void addRow(String prm_cols, Object prm_values) throws GwafInternalException {
//        addRow(new String[] {prm_cols}, new Object[] {prm_values});
//    }
//
//    /**
//     * 本クエリ末尾にレコードを追加します. <BR>
//     * 追加するレコードの列名配列と数が一致しない場合エラーになります。<BR>
//     * 自身のクエリが空(初めてのaddRow)である場合、そのレコードが本クエリの列となり受け入れます。<BR>
//     * @param prm_cols 追加する列名の配列
//     * @param prm_values 対応する文字列値の配列
//     * @throws GwafInternalException
//     */
//    public void addRow(String[] prm_cols, String[] prm_values) throws GwafInternalException {
//        if (prm_cols == null || prm_values == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: 引数が null です。");
//        }
//        addRow(prm_cols, (Object[])prm_values);
//    }
//
//    public void addRow(String prm_cols, String prm_values) throws GwafInternalException {
//        addRow(new String[] {prm_cols}, new String[] {prm_values});
//    }
//
//    /**
//     * 本クエリ末尾に ResultSet クエリを追加します. <BR>
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
//     * 本クエリ末尾に別クエリを追加します. <BR>
//     * 追加元（自身のクエリ）にデータが存在する場合、追加するクエリとレコードの全ての列名が一致しない場合エラーになります。<BR>
//     * 追加元（自身のクエリ）データが存在しない場合、エラーにはなりません。<BR>
//     * @param prm_qry 自身のクエリ追加するクエリ
//     * @throws GwafInternalException 列名不一致
//     */
//    public void addRow(GwafQueryObject prm_qry) throws GwafInternalException {
//        if (prm_qry == null) {
//            throw new GwafInternalException("GwafQueryObject#addRow: 追加レコード prm_qry が null です");
//        }
//        if (prm_qry.getCount() == 0) {
//            return;
//        }
//        //１レコードだけ列存在チェック
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
//            //この時点でエラー。
//            //エラー情報の文字列を作成する。
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
//            throw new GwafInternalException("GwafQueryObject#addRow: 追加レコード列名と列数が完全一致しませんでした。本クエリ列→"+wk2+"／引数のクエリ列→"+wk1);
//        } else {
//            _lstTtable.addAll(prm_qry.getListTable());
//        }
//    }
//
//    /**
//     * レコードを削除します。 .
//     * 範囲外のIndexを指定するとエラーとなります。
//     *
//     * @param prm_index レコードindex（0～)
//     * @throws GwafInternalException 引数のレコードindexが範囲外
//     */
//    public void removeRow(int prm_index) throws GwafInternalException {
//        if (getListTable().size() < prm_index) {
//            throw new GwafInternalException("GwafQueryObject#removeRow: 削除レコードINDEXは存在しません。本クエリsize="+getListTable().size()+"/引数の削除INDEX="+prm_index);
//        }
//        getListTable().remove(prm_index);
//    }
//
//    /**
//     * 引数の列の要素値で、内部レコードを昇順ソートし並べ変えます.  <BR>
//     * 大小の比較は compareTo() メソッドで行われます、したがって内部要素値は Comparable
//     * である必要があります。<BR>
//     * また、<I>null</I> は最小の値として扱われます。したがって内部要素値に<I>null</I> が存在
//     * する場合、本メソッドでは先頭に移動する事になります。<BR>
//     * @param prm_col 昇順ソートする列名
//     * @throws GwafInternalException ソートが不可能時
//     */
//    public void sortBy(String prm_col) throws GwafInternalException {
//        if (getCount() > 0) {
//            sortBy(new String[] {prm_col});
//        }
//    }
//
//    /**
//     * 引数の列の要素値で、内部レコードを昇順ソートし並べ変えます.  <BR>
//     * 大小の比較は compareTo() メソッドで行われます、したがって内部要素値は Comparable
//     * である必要があります。<BR>
//     * また、<I>null</I> は最小の値として扱うか最大っと扱うか、第２引数のフラグで指定します。
//     * @param prm_col 昇順ソートする列名
//     * @throws GwafInternalException ソートが不可能時
//     */
//    public void sortBy(String prm_col, bool prm_null_is_max) throws GwafInternalException {
//        if (getCount() > 0) {
//            sortBy(new String[] {prm_col}, prm_null_is_max);
//        }
//    }
//
//    /**
//     * 引数の列の要素値で、内部レコードを降順ソートし並べ変えます. <BR>
//     * 大小の比較は compareTo() メソッドで行われます、したがって内部要素値は Comparable
//     * である必要があります。<BR>
//     * また、<I>null</I> は最小の値として扱われます。したがって内部要素値に<I>null</I> が存在
//     * する場合、本メソッドでは先頭に移動する事になります。<BR>
//     * @param prm_col 降順ソートする列名
//     * @param prm_null_is_max true : null は最も大きい値とする／false: nullは最も小さい値とする。
//     * @throws GwafInternalException ソートが不可能時
//     */
//    public void sortDescBy(String prm_col) throws GwafInternalException{
//        if (getCount() > 0) {
//            sortDescBy(new String[] {prm_col});
//        }
//    }
//
//    /**
//     * 引数の列の要素値で、内部レコードを降順ソートし並べ変えます. <BR>
//     * 大小の比較は compareTo() メソッドで行われます、したがって内部要素値は Comparable
//     * である必要があります。<BR>
//     * また、<I>null</I> は最小の値として扱うか最大っと扱うか、第２引数のフラグで指定します。
//     * @param prm_col 降順ソートする列名
//     * @param prm_null_is_max true : null は最も大きい値とする／false: nullは最も小さい値とする。
//     * @throws GwafInternalException ソートが不可能時
//     */
//    public void sortDescBy(String prm_col, bool prm_null_is_max) throws GwafInternalException{
//        if (getCount() > 0) {
//            sortDescBy(new String[] {prm_col}, prm_null_is_max);
//        }
//    }
//
//    /**
//     * 引数の列の配列順の要素値で、内部レコードを昇順ソートし並べ変えます. <BR>
//     * 大小の比較は compareTo() メソッドで行われます、したがって内部要素値は Comparable
//     * である必要があります。<BR>
//     * また、<I>null</I> は最小の値として扱われます。したがって内部要素値に<I>null</I> が存在
//     * する場合、本メソッドでは先頭に移動する事になります。<BR>
//     * @param prm_arrCol 昇順ソートする順番の列名配列
//     * @throws GwafInternalException ソートが不可能時
//     */
//    public void sortBy(String[] prm_arrCol) throws GwafInternalException{
//        if (getCount() > 0) {
//            try {
//                sortBy(prm_arrCol, 0, _lstTtable.size()-1, false);
//            } catch (StackOverflowError e) {
//                e.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: ソート時の再起呼び出しが複雑すぎます。件数を減らしてください。:"+e);
//            }  catch (Exception e2) {
//                e2.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: ソート時に失敗しました。値にComparable以外のオブジェクトが存在する可能性があります。:"+e2);
//            }
//        }
//    }
//
//    /**
//     * 引数の列の配列順の要素値で、内部レコードを昇順ソートし並べ変えます. <BR>
//     * 大小の比較は compareTo() メソッドで行われます、したがって内部要素値は Comparable
//     * である必要があります。<BR>
//     * また、<I>null</I> は最小の値として扱うか最大っと扱うか、第２引数のフラグで指定します。
//     * @param prm_arrCol 昇順ソートする順番の列名配列
//     * @param prm_null_is_max true : null は最も大きい値とする／false: nullは最も小さい値とする。
//     * @throws GwafInternalException ソートが不可能時
//     */
//    public void sortBy(String[] prm_arrCol, bool prm_null_is_max) throws GwafInternalException{
//        if (getCount() > 0) {
//            try {
//                sortBy(prm_arrCol, 0, _lstTtable.size()-1, prm_null_is_max);
//            } catch (StackOverflowError e) {
//                e.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: ソート時の再起呼び出しが複雑すぎます。件数を減らしてください。:"+e);
//            }  catch (Exception e2) {
//                e2.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: ソート時に失敗しました。値にComparable以外のオブジェクトが存在する可能性があります。:"+e2);
//            }
//        }
//    }
//
//    /**
//     * 引数の列の配列順の要素値で、内部レコードを降順ソートし並べ変えます. <BR>
//     * 大小の比較は compareTo() メソッドで行われます、したがって内部要素値は Comparable
//     * である必要があります。<BR>
//     * また、<I>null</I> は最小の値として扱われます。したがって内部要素値に<I>null</I> が存在
//     * する場合、本メソッドでは先頭に移動する事になります。<BR>
//     * @param prm_arrCol 降順ソートする順番の列名配列
//     * @throws GwafInternalException ソートが不可能時
//     */
//    public void sortDescBy(String[] prm_arrCol) throws GwafInternalException {
//        if (getCount() > 0) {
//            try {
//                sortDescBy(prm_arrCol, 0, _lstTtable.size()-1, false);
//            } catch (StackOverflowError e) {
//                e.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: ソート時の再起呼び出しが複雑すぎます。件数を減らしてください。:"+e);
//            }  catch (Exception e2) {
//                e2.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: ソート時に失敗しました。値にComparable以外のオブジェクトが存在する可能性があります。:"+e2);
//            }
//        }
//    }
//
//    /**
//     * 引数の列の配列順の要素値で、内部レコードを降順ソートし並べ変えます. <BR>
//     * 大小の比較は compareTo() メソッドで行われます、したがって内部要素値は Comparable
//     * である必要があります。<BR>
//     * また、<I>null</I> は最小の値として扱うか最大っと扱うか、第２引数のフラグで指定します。
//     * @param prm_arrCol 降順ソートする順番の列名配列
//     * @param prm_null_is_max true:nullを最大値とします／false:nullを最小値とします。
//     * @throws GwafInternalException ソートが不可能時
//     */
//    public void sortDescBy(String[] prm_arrCol, bool prm_null_is_max) throws GwafInternalException {
//        if (getCount() > 0) {
//            try {
//                sortDescBy(prm_arrCol, 0, _lstTtable.size()-1, prm_null_is_max);
//            } catch (StackOverflowError e) {
//                e.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: ソート時の再起呼び出しが複雑すぎます。件数を減らしてください。:"+e);
//            }  catch (Exception e2) {
//                e2.printStackTrace();
//                throw new GwafInternalException("GwafQueryObject#sortDescBy: ソート時に失敗しました。値にComparable以外のオブジェクトが存在する可能性があります。:"+e2);
//            }
//        }
//    }
//
//    /**
//     * 引数の列の配列順の要素値で、内部レコードを昇順ソートし並べ変えます. <BR>
//     * クイックソート使用。<BR>
//     * @param prm_arrCol 昇順ソートする順番の列名配列
//     * @param prm_begin_index 開始INDEX
//     * @param prm_end_index 終了INDEX
//     * @param prm_null_is_max true:nullを最大値とします／false:nullを最小値とします。
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
//     * 引数の列の配列順の要素値で、内部レコードを降順ソートし並べ変えます. <BR>
//     * クイックソート使用。<BR>
//     * @param prm_arrCol 降順ソートする順番の列名配列
//     * @param prm_begin_index 開始INDEX
//     * @param prm_end_index 終了INDEX
//     * @param prm_null_is_max true:nullを最大値とします／false:nullを最小値とします。
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
//     * ２つの GwafQueryObject オブジェクトを外部結合して、新たな GwafQueryObject を返す。 .
//     * １つ目の GwafQueryObject の結合のキーとなると、colkey_q2 ２つ目の GwafQueryObject の結合のキーとなる列が<BR>
//     * 文字列で等しい場合に結合となります。<BR>
//     * また、作成された新しい GwafQueryObject には、colkey_q1+"&"+colkey_q2 という列が増えており、<BR>
//     * これにはキーとなる列が必ず入っています。
//     * @param q1 １つ目の GwafQueryObject オブジェクト
//     * @param colkey_q1 １つ目の GwafQueryObject の結合のキーとなる列
//     * @param q2 ２つ目の GwafQueryObject オブジェクト
//     * @param colkey_q2 ２つ目の GwafQueryObject の結合のキーとなる列
//     * @return 外部結合された新たなGwafQueryObject
//     */
//    public static GwafQueryObject joinFullOuter(GwafQueryObject q1, String colkey_q1, GwafQueryObject q2, String colkey_q2, int option) {
//        TreeMap<String, Map<String, Object>> mapResult = new TreeMap<String, Map<String, Object>>();
//        String[] cols1 = q1.getColNames();
//        String[] cols2 = q2.getColNames();
//        for (int index_q1 = 0; index_q1 < q1.getCount(); index_q1++) {
//
//            //空の結合レコードを１行作成
//            Map<String, Object> mapRec = new HashMap<String, Object>();
//            for (int i = 0; i < cols1.length; i++) {
//                mapRec.put(cols1[i], null);
//            }
//            for (int i = 0; i < cols2.length; i++) {
//                mapRec.put(cols2[i], null);
//            }
//            mapRec.put(colkey_q1+"&"+colkey_q2, null);
//
//            //データ登録
//            for (int i = 0; i < cols1.length; i++) {
//                mapRec.put(cols1[i], q1.get(cols1[i], index_q1));
//            }
//            mapRec.put(colkey_q1+"&"+colkey_q2, q1.getStr(colkey_q1, index_q1)); //キー
//
//            //1行あがり
//            mapResult.put(q1.getStr(colkey_q1, index_q1), mapRec);
//       }
//
//       for (int index_q2 = 0; index_q2 < q2.getCount(); index_q2++) {
//           Map<String, Object> mapRec;
//           String colkey_val_q2 = q2.getStr(colkey_q2, index_q2);
//           if (mapResult.containsKey(colkey_val_q2)) {
//               //q1で登録してれば、それをに上書き
//               mapRec = mapResult.get(colkey_val_q2);
//           } else {
//               //無ければ空の結合レコードを１行作成
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
//           //データ登録
//           for (int i = 0; i < cols2.length; i++) {
//               mapRec.put(cols2[i], q2.get(cols2[i], index_q2));
//           }
//           if (mapRec.get(colkey_q1+"&"+colkey_q2) ==  null) {
//               mapRec.put(colkey_q1+"&"+colkey_q2, q2.getStr(colkey_q2, index_q2)); //キー
//           }
//
//           //1行あがり
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
//     * AとBのレコードの場所(INDEX)を入れ替えます. <BR>
//     * @param prm_index_A 入れ替え対象レコードINDEX A
//     * @param prm_index_B 入れ替え対象レコードINDEX B
//     */
//    public void swapIndex(int prm_index_A, int prm_index_B)  {
//        Map pRecordA = _lstTtable.get(prm_index_A);
//        _lstTtable.set(prm_index_A, _lstTtable.get(prm_index_B));
//        _lstTtable.set(prm_index_B, pRecordA);
//    }
//
//    /**
//     * データの内容取得. <BR>
//     * @return 文字列表現のデータの内容
//     */
//    public String dump() {
//        if (null == _lstTtable) {
//            return "_lstTtableがnullです";
//        } else if (_lstTtable.isEmpty()) {
//            return "_lstTtableがEmptyです";
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

