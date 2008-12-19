#ifndef GGAFLINKEDLISTRING_H_
#define GGAFLINKEDLISTRING_H_
/**
 * 同一クラス要素の環状双方向連結リストを構築するテンプレートです。.
 *
 * <B>【解説】</B><BR>
 * <PRE>
 * 　･･⇔Ｐ⇔･･･
 * 　　　↓
 * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)
 * 　　　　　　│　└────────────┐
 * 　　　　　　↓　　　　　　　　　　　　　　↓
 * 　　　(Ｈ)⇔Ｆ⇔Ｇ⇔Ｈ⇔(Ｆ)　　　　(Ｌ)⇔Ｉ⇔Ｊ⇔Ｋ⇔Ｌ⇔(Ｉ)
 * 　　　　　　　　↓　↓　　　　　　　　　　　　↓　　　↓
 * 　　　　　　　　　･･･　　　　　　　　　　　　　　　･･･
 * </PRE>
 * 上図のような構造を採る事が出来ます。<BR>
 * 中段の「(Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)」は要素（インスタンス）が環状の双方向でポインタを指しあっている事を示しています。<BR>
 * 両端の「(Ｅ)」と「(Ａ)」は、連結リストの先頭と末尾も、お互い連結している事を明示しています。(環状になっている)<BR>
 * 上図で自身のインスタンスを「Ｃ」とした場合、「Ｃ」の視点から各要素を次のように呼称、及び定義することとします。<BR>
 * <TABLE BORDER="1">
 * <TR><TD>「Ｃ」</TD><TD>自要素</TD></TR>
 * <TR><TD>「Ａ」</TD><TD>先頭(First)要素。 自要素が所属する連結リストの先頭という意味です。「Ａ」 は _isFirst が true になっています。(他要素は false)</TD></TR>
 * <TR><TD>「Ｅ」</TD><TD>末尾(Last)要素。 自要素が所属する連結リストの最後という意味です。「Ｅ」 は _isLast が true になっています。(他の要素は false)</TD></TR>
 * <TR><TD>「Ｄ」</TD><TD>次(Next)要素。上図では左から右が正順序としています。_pNextポインタが指している要素になります。</TD></TR>
 * <TR><TD>「Ｂ」</TD><TD>前(Prev)要素。_pPrev が指しているポインタです。</TD></TR>
 * <TR><TD>「Ｐ」</TD><TD>親(Parent)要素。自要素が所属する連結リストの１つ上の階層の要素です。_pParent ポインタが指している要素です。全ての要素は直近の親要素のポインタを持っています。</TD></TR>
 * <TR><TD>「Ｉ，Ｊ，Ｋ，Ｌ」</TD><TD>「Ｃ」子(Sub)要素と呼びます。</TD></TR>
 * <TR><TD>「Ｉ」</TD><TD> 子要素の中で特に「Ｉ」は子要素の先頭要素と呼び、自要素の _pSubFirst ポインタが指している要素となっています。</TD></TR>
 * </TABLE>
 * <BR>
 *
 * <B>【その他用語補足】</B>
 * <TABLE BORDER="1">
 * <TR>
 * <TD>「他要素」「他」</TD>
 * <TD>自要素以外の要素全てを指しています。</TD>
 * </TR><TR>
 * <TD>「配下要素」「配下」</TD>
 * <TD>要素同士のツリー階層構造上において、自要素<B>に</B>ぶら下がる全ての要素を指しています。自要素は含まれません。</TD>
 * </TR><TR>
 * <TD>「自ツリー」</TD>
 * <TD>自要素を頂点とする、自要素＋配下要素で構成されるツリー構造自体を指します。</TD>
 * </TR><TR>
 * <TD>「自ツリー要素」</TD>
 * <TD>自要素を頂点とする、自要素＋配下要素で構成されるツリー構造の要素全てを指します。</TD>
 * </TR><TR>
 * <TD>「自所属ツリー」</TD>
 * <TD>自要素が含まれているツリー構造の全てを指します。</TD>
 * </TR><TR>
 * <TD>「要素クラス」</TD>
 * <TD>GgafLinkedListRing実装クラス、或いはGgafLinkedListRing実装クラスを直接・間接継承しているクラスを指します。</TD>
 * </TR><TR>
 * <TD>「上位」「下位」</TD>
 * <TD>要素クラスのクラス継承関係を表しています。
 * クラス継承関係の表現は「スーパー」「サブ」又は「親」「子」と言わずに<B>「上位」「下位」</B>で統一することにします。<BR>
 * 「親」「子」と表現した場合はそれぞれ親要素、子要素のツリー構造の事を表現するものとします。（ややこしいですね）<BR>
 * ＜例＞下位で実装された･･･。</TD>
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */

template<class T>
class GgafLinkedListRing : public GgafObject {

protected:

	class Elem {
	public:
		/** 要素の値 */
		T* _pValue;
		/** 次要素 */
		Elem* _pNext;
		/** 前要素 */
		Elem* _pPrev;
		/** 先頭要素フラグ (自要素が先頭要素の場合 true)*/
		bool _isFirst;
		/** 末尾要素フラグ (自要素が末尾要素の場合 true)*/
		bool _isLast;


		Elem(T* prm_pValue){
			_pValue = prm_pValue;
			_pNext = _pPrev = NULL;
			_isFirst = _isLast = false;
		};

		T* getVal() {
			return _pValue;
		}

		Elem* getNext() {
			return _pNext;
		};

		Elem* getPrev() {
			return _pPrev;
		};

		/**
		 * 要素が先頭要素か調べる .
		 * @return	bool true:先頭要素／false:先頭要素ではない
		 */
		bool isFirst() {
			return _isFirst;
		};

		/**
		 * 要素が末尾要素か調べる .
		 * @return	bool true:末尾要素／false:末尾要素ではない
		 */
		bool isLast() {
			return _isLast;
		};

		~Elem(){
			DELETE_IMPOSSIBLE_NULL(_pValue);
		};

	};

public:

	/** 先頭要素 */
	Elem* _pFirst;

	/** アクティブ要素 */
	Elem* _pActive;

	/** 要素数 */
	int _iElemNum;

	/**
	 * コンストラクタ
	 * @param prm_pElem コピー可能な構造体やクラスのポインタ
	 */
//	GgafLinkedListRing(int prm_iNum);

	GgafLinkedListRing();

	/**
	 * デストラクタ。自ツリー要素を解放します。 .
	 * 自要素が子要素を持つ場合、子要素を解放してから自身を開放する。<BR>
	 * 自要素が最終要素だった場合、自要素を連結から離脱し、前要素を最終要素フラグをセットして、自身を解放する。<BR>
	 * 自要素が先頭要素だった場合、自要素を連結から離脱し、次要素を親要素 の 子要素の先頭要素、さらに 先頭要素フラグをセットし、自身を解放する。<BR>
	 * 自要素が中間要素だった場合、両隣の要素の連結を再構築した後解放する。<BR>
	 * 自要素の連結が自身を指す（１人ぼっちだった）場合、親要素 の 子要素の先頭要素（自分を指していた）をNULLに変更してから解放する。<BR>
	 */
	virtual ~GgafLinkedListRing();

//
//	/**
//	 * 自ツリー要素を連結リストから切り離し、独立する。 .
//	 * 切り離され穴が開いた部分は、周りの要素が穴を埋めます（再連結します）<BR>
//	 * 自要素に子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
//	 * @return	T* 自要素のポインタ
//	 */
//	virtual T* tear();
//
//	/**
//	 * アクティブ要素を、最終要素へ移動する .
//	 *<PRE>
//	 * ----------------「実行前」
//	 * （Ｅ）⇔Ａ⇔Ｂ⇔Ｃ*⇔Ｄ⇔Ｅ⇔（Ａ）
//	 * -----------------------
//	 *        ↓ 上図でアクティブ要素を「Ｃ」とした場合、次のような状態になる
//	 *        ↓ ( * はアクティブ要素である事を表します。)
//	 * ----------------「実行後」
//	 * （Ｅ）⇔Ａ⇔Ｂ⇔Ｄ*⇔Ｅ⇔Ｃ⇔（Ａ）
//	 * -----------------------
//	 * </PRE>
//	 */
//	virtual void moveLast();
//
//	/**
//	 * アクティブ要素を、先頭要素へ移動する .
//	 *<PRE>
//	 * ----------------「実行前」
//	 * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ*⇔Ｄ⇔Ｅ⇔(Ａ)
//	 * -----------------------
//	 *        ↓ 上図でアクティブ要素を「Ｃ」とした場合、次のような状態になる
//	 *        ↓ ( * はアクティブ要素である事を表します。)
//	 * ----------------「実行後」
//	 * (Ｅ)⇔Ｃ⇔Ａ⇔Ｂ*⇔Ｄ⇔Ｅ⇔(Ｃ)
//	 * -----------------------
//	 * </PRE>
//	 */
//	virtual void moveFirst();


	/**
	 * アクティブ要素の値を取得する。
	 * @return	アクティブ要素
	 */
	T* get();

	/**
	 * アクティブ要素を一つ進めた後、その要素の値を取得する。
	 * @return 次の要素
	 */
	T* next();

	/**
	 * アクティブ要素を一つ戻した後、その要素の値を取得する。
	 * @return 前の要素
	 */
	T* prev();

	bool isLast();

	bool isFirst();

//
//	/**
//	 * アクティブ要素を一つ進めた後、その要素の値を取得する。
//	 * @return	T*	次要素
//	 */
//	virtual T* nextVal();
//
//	/**
//	 * アクティブ要素を一つ戻した後、その要素の値を取得する。
//	 * @return	T*	前要素
//	 */
//	virtual T* prevVal();
//
	/**
	 * 引数要素を、末尾(_isLast が true)として追加する .
	 * 追加される場所は以下の図のようになります。<BR>
	 *<PRE>
	 * ----------------「実行前」
	 * (Ｋ)⇔Ｉ⇔Ｊ⇔Ｋ⇔(Ｉ)
	 * -----------------------
	 *        ↓ 上図は３要素からなる環状リストです。「Ｋ」が末尾要素です。
	 *        ↓ ここに要素「Ｘ」addLast すると下図のような状態になり、
	 *        ↓ 要素「Ｘ」が新たな末尾要素になります。
	 * ----------------「実行後」
	 * (Ｘ)⇔Ｉ⇔Ｊ⇔Ｋ⇔Ｘ⇔(Ｉ)
	 * -----------------------
	 * </PRE>
	 *
	 * @param	prm_pSub	インスタンス生成済み要素のポインタ
	 */
	virtual void addLast(T* prm_pSub);



};



//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */

template<class T>
GgafLinkedListRing<T>::GgafLinkedListRing() : GgafObject() {
	_iElemNum = 0;
	_pActive = NULL;
	_pFirst = NULL;
}

template<class T>
T* GgafLinkedListRing<T>::get() {
	if (_pActive == NULL) {
		throw_GgafCriticalException("[GgafLinkedListRing::get()] Error! アクティブ要素がNULLです");
	}
	return _pActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::next() {
	if (_pActive == NULL) {
		throw_GgafCriticalException("[GgafLinkedListRing::next()] Error! アクティブ要素がNULLです");
	}
	_pActive = _pActive -> _pNext;
	return _pActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::prev() {
	if (_pActive == NULL) {
		throw_GgafCriticalException("[GgafLinkedListRing::prev()] Error! アクティブ要素がNULLです");
	}
	_pActive = _pActive -> prev;
	return _pActive->_pValue;
}

template<class T>
void GgafLinkedListRing<T>::addLast(T* prm_pSub) {
	if (prm_pSub == NULL) {
		throw_GgafCriticalException("[GgafLinkedListRing::addLast()] Error! 引数がNULLです");
	}
	static Elem* pElem;
	static Elem* pLastElem;
	pElem = NEW Elem(prm_pSub);

	pElem -> _isLast = true;

	if (_pFirst == NULL) {
		//最初の１つ
		pElem->_isFirst = true;
		pElem->_pNext = pElem;
		pElem->_pPrev = pElem;
		_pActive = pElem;
	} else {
		//２つ目以降
		pElem -> _isFirst = false;
		pLastElem = _pFirst->_pPrev;
		pLastElem->_isLast = false;
		pLastElem->_pNext = pElem;
		pElem->_pPrev = pLastElem;
		pElem->_pNext = _pFirst;
		_pFirst->_pPrev = pElem;
	}
	_iElemNum++;

}

template<class T>
bool GgafLinkedListRing<T>::isLast() {
	return _pActive->_isLast;
}

template<class T>
bool GgafLinkedListRing<T>::isFirst() {
	return _pActive->_isFirst;
}

template<class T>
GgafLinkedListRing<T>::~GgafLinkedListRing() {
	//自分に子がある場合
	if (_pFirst) {
		//まず子をdelete
		if (_iElemNum == 1) {
			//子要素は１つの場合
			DELETE_IMPOSSIBLE_NULL(_pFirst);
			_pFirst = NULL;
			_pActive = NULL;
			_iElemNum = 0;

		} else {
			//子要素は２つ以上の場合
			Elem* pLast = _pFirst -> _pPrev;
			Elem* pLastPrev = pLast -> _pPrev;
			while(true) {
				DELETE_IMPOSSIBLE_NULL(pLast); //末尾からdelete
				if (pLastPrev -> _isFirst) {
					DELETE_IMPOSSIBLE_NULL(_pFirst); //pSubLastPrev == _pSubFirst である
					_pFirst = NULL;
					_pActive = NULL;
					_iElemNum = 0;
					break;
				}
				pLast = pLastPrev;
				pLastPrev = pLastPrev -> _pPrev;
			}
		}
	}


//	_TRACE_("...deleted GgafLinkedListRing("<<_name<<") ID="<<_id);
	_TRACE_("...deleted GgafLinkedListRing()");
}

#endif /*GGAFLINKEDLISTRING_H_*/
