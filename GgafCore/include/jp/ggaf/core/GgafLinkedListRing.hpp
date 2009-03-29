#ifndef GGAFLINKEDLISTRING_H_
#define GGAFLINKEDLISTRING_H_
namespace GgafCore {

/**
 * 要素（同一型インスタンス）の環状双方向連結リストを構築するテンプレートです。.
 *
 * <B>【解説】</B><BR>
 * 連結リストの先頭と末尾が繋がっているということで、『環状』と表現しています。<BR>
 * <PRE STYLE="font-size:18px">
 * 【例】
 * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ*⇔Ｄ⇔Ｅ⇔(Ａ)
 * </PRE>
 * 例えば、５つの要素で上図のような構造を採る事が出来ます。<BR>
 * 『⇔』は、要素（インスタンス）同士がお互いポインタを指しあっている事を示しています。<BR>
 * Ａを先頭要素、Ｅを末尾要素、*はアクティブ要素(カーソルが指しているようなもの)と呼ぶこととします。<BR>
 * ロジック中、addLast() にて一番最初に追加した要素が先頭要素で、最後に追加した要素が末尾要素となります。<BR>
 * 両端の「(Ｅ)」と「(Ａ)」という表記は、連結リストの先頭と末尾も、お互い連結している事を示しています。(環状になっている)<BR>
 * addLast()で１要素だけ追加した場合は次のようになります。<BR>
 * <PRE STYLE="font-size:18px">
 * 【例】
 * (Ａ)⇔Ａ*⇔(Ａ)
 * </PRE>
 * イテレータのような使い方を想定していますが、上図から解るように、hasNext() による判定は存在しません。<BR>
 * <BR>
 * @version 1.00
 * @since 2008/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafLinkedListRing : public GgafObject {

private:

    /**
     * 実際の要素値をラッピングし、ポインタを追加
     */
    class Elem {
    public:
        /** 実際の要素の値 */
        T* _pValue;
        /** 次要素 */
        Elem* _pNext;
        /** 前要素 */
        Elem* _pPrev;
        /** 先頭要素フラグ (自要素が先頭要素の場合 true)*/
        bool _isFirstFlg;
        /** 末尾要素フラグ (自要素が末尾要素の場合 true)*/
        bool _isLastFlg;

        /**
         * コンストラクタ
         * @param prm_pValue 値ポインタ
         */
        Elem(T* prm_pValue) {
            _pValue = prm_pValue;
            _pNext = _pPrev = NULL;
            _isFirstFlg = _isLastFlg = false;
        }

        /**
         * 要素の値を取得
         * @return 要素の値
         */
        T* getVal() {
            return _pValue;
        }

        /**
         * 次の要素を取得
         * @return 次の要素
         */
        Elem* getNext() {
            return _pNext;
        }

        /**
         * 前の要素を取得
         * @return 前の要素
         */
        Elem* getPrev() {
            return _pPrev;
        }

        /**
         * 要素が先頭要素か調べる .
         * @return	bool true:先頭要素／false:先頭要素ではない
         */
        bool isFirst() {
            return _isFirstFlg;
        }

        /**
         * 要素が末尾要素か調べる .
         * @return	bool true:末尾要素／false:末尾要素ではない
         */
        bool isLast() {
            return _isLastFlg;
        }

        /**
         * デストラクタ.
         * 内部保持する要素の値も開放されます。<BR>
         */
        ~Elem() {
            DELETE_IMPOSSIBLE_NULL(_pValue);
        }

    };

protected:
    /** 先頭要素 */
    Elem* _pElemFirst;

    /** アクティブ要素 */
    Elem* _pElemActive;

    /** 要素数 */
    int _num_elem;

public:
    /**
     * コンストラクタ
     */
    GgafLinkedListRing();

    /**
     * デストラクタ.
     * 内部保持する要素の環状双方向連結リストも開放されます。<BR>
     */
    virtual ~GgafLinkedListRing();

    /**
     * アクティブ要素の値（保持している内容）を取得する .
     * @return	アクティブ要素
     */
    T* get();

    /**
     * アクティブ要素を一つ進めた後、その要素の値を取得する .
     * @return 次の要素
     */
    T* next();

    /**
     * アクティブ要素を一つ戻した後、その要素の値を取得する .
     * @return 前の要素
     */
    T* prev();

    /**
     * アクティブ要素がリストの末尾であるか判定する .
     * @return true:末尾である／false:そうでは無い
     */
    bool isLast();

    /**
     * アクティブ要素がリストの先頭であるか判定する .
     * @return true:末尾である／false:そうでは無い
     */
    bool isFirst();

    /**
     * 引数要素を、末尾(_isLastFlg が true)として追加する .
     * 追加される場所は以下の図のようになります。<BR>
     *<PRE STYLE="font-size:18px">
     * ----------------「実行前」
     * (Ｋ)⇔Ｉ*⇔Ｊ⇔Ｋ⇔(Ｉ)
     * -----------------------
     * 　　　　↓ 上図は３要素からなる環状リストです。「Ｋ」が末尾要素です。
     * 　　　　↓ ここに要素「Ｘ」addLast すると下図のような状態になり、
     * 　　　　↓ 要素「Ｘ」が新たな末尾要素になります。
     * ----------------「実行後」
     * (Ｘ)⇔Ｉ*⇔Ｊ⇔Ｋ⇔Ｘ⇔(Ｉ)
     * -----------------------
     * </PRE>
     * 初めてのaddLastは、引数のオブジェクトはにアクティブ要素なり、<BR>
     * ２回目以降addLastを行なってもにアクティブ要素は影響されません。<BR>
     *
     * @param   prm_pSub    インスタンス生成済み要素のポインタ
     */
    virtual void addLast(T* prm_pSub);

};

//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */

template<class T>
GgafLinkedListRing<T>::GgafLinkedListRing() :
    GgafObject() {
    _num_elem = 0;
    _pElemActive = NULL;
    _pElemFirst = NULL;
}

template<class T>
T* GgafLinkedListRing<T>::get() {
    if (_pElemActive == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::get()] Error! アクティブ要素がNULLです");
    }
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::next() {
    if (_pElemActive == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::next()] Error! アクティブ要素がNULLです");
    }
    _pElemActive = _pElemActive->_pNext;
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::prev() {
    if (_pElemActive == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::prev()] Error! アクティブ要素がNULLです");
    }
    _pElemActive = _pElemActive->prev;
    return _pElemActive->_pValue;
}

template<class T>
void GgafLinkedListRing<T>::addLast(T* prm_pSub) {
    if (prm_pSub == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! 引数がNULLです");
    }
    static Elem* pElem;
    static Elem* pLastElem;
    pElem = NEW Elem(prm_pSub);

    pElem->_isLastFlg = true;

    if (_pElemFirst == NULL) {
        //最初の１つ
        pElem->_isFirstFlg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        //２つ目以降
        pElem->_isFirstFlg = false;
        pLastElem = _pElemFirst->_pPrev;
        pLastElem->_isLastFlg = false;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = _pElemFirst;
        _pElemFirst->_pPrev = pElem;
    }
    _num_elem++;

}

template<class T>
bool GgafLinkedListRing<T>::isLast() {
    return _pElemActive->_isLastFlg;
}

template<class T>
bool GgafLinkedListRing<T>::isFirst() {
    return _pElemActive->_isFirstFlg;
}

template<class T>
GgafLinkedListRing<T>::~GgafLinkedListRing() {
    //自分に子がある場合
    if (_pElemFirst) {
        //まず子をdelete
        if (_num_elem == 1) {
            //子要素は１つの場合
            DELETE_IMPOSSIBLE_NULL(_pElemFirst);
            _pElemFirst = NULL;
            _pElemActive = NULL;
            _num_elem = 0;

        } else {
            //子要素は２つ以上の場合
            Elem* pLast = _pElemFirst->_pPrev;
            Elem* pLastPrev = pLast->_pPrev;
            while (true) {
                DELETE_IMPOSSIBLE_NULL(pLast); //末尾からdelete
                if (pLastPrev->_isFirstFlg) {
                    DELETE_IMPOSSIBLE_NULL(_pElemFirst); //pSubLastPrev == _pSubFirst である
                    _pElemFirst = NULL;
                    _pElemActive = NULL;
                    _num_elem = 0;
                    break;
                }
                pLast = pLastPrev;
                pLastPrev = pLastPrev->_pPrev;
            }
        }
    }
}

}
#endif /*GGAFLINKEDLISTRING_H_*/
