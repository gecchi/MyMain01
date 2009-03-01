#ifndef GGAFTREENODE_H_
#define GGAFTREENODE_H_
/**
 * 要素同士を環状双方向連結リストで繋ぎ、それらの連結リスト達のツリー構造を作ることができる要素クラスです。.
 *
 * ＜解説＞<BR>
 * <PRE>
 * 　　　⇔Ｐ⇔･･･
 * 　　　　↓
 * （Ｅ）⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)
 * 　　　　　　│　└────────────┐
 * 　　　　　　↓　　　　　　　　　　　　　　↓
 * 　　（Ｈ）⇔Ｆ⇔Ｇ⇔Ｈ⇔（Ｆ）　　（Ｌ）⇔Ｉ⇔Ｊ⇔Ｋ⇔Ｌ⇔（Ｉ）
 * 　　　　　　↓　↓　　　　　　　　　　　　　　↓　　　↓
 * 　　　　　　･･･　　　　　　　　　　　　　　　･･･
 * </PRE>
 * 上図のような構造を採る事が出来ます。<BR>
 * 中段の「（Ｅ）⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)」は要素が双方向連結リストで繋がっている事を示しています。<BR>
 * 両端の「（Ｅ）」と「(Ａ)」は、連結リストの先頭と末尾が、お互い連結している事を表しています。（環状になっている）<BR>
 * 自身のインスタンスを「Ｃ」とした場合、「Ｃ」の視点から各要素を次のように呼称、及び定義することとします。<BR>
 * 「Ｃ」･･･自ノード<BR>
 * 「Ａ」･･･先頭(First)ノード。 連結リストの先頭という意味です。_isFirst になっています。<BR>
 * 「Ｅ」･･･末尾(Last)ノード。 連結リストの最後という意味です。_isLast になっています。<BR>
 * 「Ｄ」･･･次(Next)ノード。上図では左から右が正順序としています。_pNext が指しているポインタです。<BR>
 * 「Ｂ」･･･前(Prev)ノード。_pPrev が指しているポインタです。<BR>
 * 「Ｐ」･･･親(Parent)ノード。_pParentが指しているポインタです。全てのノードは直近の親ノードのポインタを持っています。<BR>
 * 「Ｉ，Ｊ，Ｋ，Ｌ」･･･子(Sub)ノードと呼ぶこととします。「Ｉ」は子ノードの先頭ノードと呼び、 _pSubFirst が指しているポインタとなっています。<BR>
 * <BR>
 *
 * <B>【その他用語補足】</B>
 * <TABLE>
 * <TR>
 * <TD>「他ノード」「他」</TD>
 * <TD>自ノード以外のノード全てを指しています。</TD>
 * </TR><TR>
 * <TD>「配下ノード」「配下」</TD>
 * <TD>ノード同士のツリー階層構造上において、自ノード<B>に</B>ぶら下がる全てのノードを指しています。自ノードは含まれません。</TD>
 * </TR><TR>
 * <TD>「自ツリー」</TD>
 * <TD>自ノードを頂点とする、自ノード＋配下ノードで構成されるツリー構造自体を指します。</TD>
 * </TR><TR>
 * <TD>「自ツリーノード」</TD>
 * <TD>自ノードを頂点とする、自ノード＋配下ノードで構成されるツリー構造のノード全てを指します。</TD>
 * </TR><TR>
 * <TD>「自所属ツリー」</TD>
 * <TD>自ノードが含まれているツリー構造の全てを指します。</TD>
 * </TR><TR>
 * <TD>「ノードクラス」</TD>
 * <TD>GgafTreeLinkedListクラスを直接・間接継承しているクラスを指します。</TD>
 * </TR><TR>
 * <TD>「上位」「下位」</TD>
 * <TD>ノードクラスのクラス継承関係を表しています。
 * クラス継承関係の表現は「スーパー」「サブ」又は「親」「子」と言わずに<B>「上位」「下位」</B>で統一することにします。<BR>
 * ＜例＞下位で実装された･･･うんぬん</TD>
 *
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */

template<class T>
class GgafTreeLinkedList : public GgafObject {

protected:
public:
	/** ノード名 */
	string _name;
	/** クラス名 */
	string _class_name;


	/** 親ノード */
	T* _pParent;
	/** 次ノード */
	T* _pNext;
	/** 前ノード */
	T* _pPrev;
	/** 子ノードの先頭ノード */
	T* _pSubFirst;

	/** 先頭ノードフラグ */
	bool _isFirst;
	/** 末尾ノードフラグ */
	bool _isLast;
	/** ループ用 */
	T* _pNodeTemp;



	/**
	 * コンストラクタ
	 * @param prm_name ノード名称（ユニークにして下さい）
	 */
	GgafTreeLinkedList(string prm_name);

	/**
	 * デストラクタ。自ツリーノードを解放します。 .
	 * 自ノードが子ノードを持つ場合、子ノードを解放してから自身を開放する。<BR>
	 * 自ノードが最終ノードだった場合、自ノードを連結から離脱し、前ノードを最終ノードフラグをセットして、自身を解放する。<BR>
	 * 自ノードが先頭ノードだった場合、自ノードを連結から離脱し、次ノードを親ノード の 子ノードの先頭ノード、さらに 先頭ノードフラグをセットし、自身を解放する。<BR>
	 * 自ノードが中間ノードだった場合、両隣のノードの連結を再構築した後解放する。<BR>
	 * 自ノードの連結が自身を指す（１人ぼっちだった）場合、親ノード の 子ノードの先頭ノード（自分を指していた）をNULLに変更してから解放する。<BR>
	 */
	virtual ~GgafTreeLinkedList();

	/**
	 * ノード名取得 .
	 * @return ノード名称
	 */
	virtual string getName();

	/**
	 * ノード名問い合わせ
	 */
//	virtual bool isNamed(string prm_name);


	/**
	 * １つ上の親ノードを設定する。
	 * @param	prm_pParent	親ノード
	 */
	virtual void setParent(T* prm_pParent);

	/**
	 * 自ツリーノードを連結リストから切り離し、独立する。
	 * @return	T* 自ノードのポインタ
	 *
	 */
	virtual T* tear();

	/**
	 * 最終ノードへ移動する.
	 * 子ノードも道連れにして移動します。自ノードと子ノードの関係は崩れません。<BR>
	 *
	 * ----------------「実行前」
	 * 　　　　親
	 * 　　　　↓
	 * （Ｅ）⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔（Ａ）
	 * -----------------------
	 *        ↓ 上図で自分が「Ｃ」とした場合、次のような状態になる
	 * ----------------「実行後」
	 * 　　　　親
	 * 　　　　↓
	 * （Ｅ）⇔Ａ⇔Ｂ⇔Ｄ⇔Ｅ⇔Ｃ⇔（Ａ）
	 * -----------------------
	 */
	virtual void moveLast();

	/**
	 * 先頭ノードへ移動する
	 * 子ノードも道連れにして移動します。自ノードと子ノードの関係は崩れません。<BR>
	 *
	 * ----------------「実行前」
	 *      親
	 *      ↓
	 * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)
	 * -----------------------
	 *        ↓ 上図で自分が「Ｃ」とした場合、次のような状態になる
	 * ----------------「実行後」
	 *      親
	 *      ↓
	 * (Ｅ)⇔Ｃ⇔Ａ⇔Ｂ⇔Ｄ⇔Ｅ⇔(Ｃ)
	 * -----------------------
	 */
	 virtual void moveFirst();


	/**
	 * 次のノード取得する。
	 * @return	T*	次ノード
	 */
	virtual T* getNext();

	/**
	 * 前のノード取得する。
	 * @return	T*	前ノード
	 */
	virtual T* getPrev();

	/**
	 * １つ上の親ノード取得する。
	 * @return	T*	親ノード
	 */
	virtual T* getParent();

	/**
	 * 親ノードを全て検索し取得する。
	 * 存在しない場合はエラー
	 * @param	prm_parent_name	親ノード名（クラス名）
	 * @return	T*	親ノード
	 */
	virtual T* getParent(string prm_parent_name);

	/**
	 * ノードを子ノードとして追加する。
	 * @param	prm_pSub	インスタンス生成済みノードのポインタ
	 */
	virtual void addSubLast(T* prm_pSub);

	/**
	 * 子ノードをノード名称を指定して取得する。
	 * 存在しない場合はエラー
	 * @param	prm_sub_actor_name	子ノード名
	 * @return	T*	最初にヒットした子ノード名に対応する子ノードのポインタ
	 */
	virtual T* getSub(string prm_sub_actor_name);

	/**
	 * 子ノードのグループの先頭ノードを取得する。
	 * 子ノードがひとつも存在しない場合はエラー
	 * @return	T*	子ノードの先頭ノード
	 */
	virtual T* getSubFirst();

	/**
	 * 子ノード存在チェック。
	 * @param	prm_sub_actor_name	子ノード名
	 * @return	bool true:存在する／false:存在しない
	 */
	virtual bool hasSub(string prm_sub_actor_name);

	/**
	 * 先頭ノードか調べる
	 * @return	bool true:先頭ノード／false:先頭ノード以外
	 */
	virtual bool isFirst();

	/**
	 * 末尾ノードか調べる
	 * @return	bool true:末尾ノード／false:末尾ノード以外
	 */
	virtual bool isLast();


};



//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */


template<class T>
GgafTreeLinkedList<T>::GgafTreeLinkedList(string prm_name) : GgafObject() ,
_name("NOT_OBJECT_YET"),
_pParent(NULL),
_pSubFirst(NULL),
_isFirst(false),
_isLast(false)
{
	_pNext = (T*)this;
	_pPrev = (T*)this;
	_name = prm_name;
	TRACE("template<class T> GgafTreeLinkedList<T>::GgafTreeLinkedList("+_name+")");
	_class_name = "GgafTreeLinkedList<T>";

}



template<class T>
T* GgafTreeLinkedList<T>::tear() {
	if (_pParent != NULL) {
		//連結から外す
		T* pMyNext = _pNext;
		T* pMyPrev = _pPrev;
		if (_isFirst && _isLast) {
			//連結が自分のみ場合
			_pParent -> _pSubFirst = NULL;
		} else {
			//連結がから抜け出す場合
			//両隣のノード同士を繋ぎ、自分を指さなくする。
			pMyPrev -> _pNext = pMyNext;
			pMyNext -> _pPrev = pMyPrev;
			if (_isLast) {
				pMyPrev -> _isLast = true;
			}
			if (_isFirst) {
				pMyNext -> _isFirst = true;
				_pParent -> _pSubFirst = pMyNext;
			}
		}
		_pParent = NULL;
		_pNext = (T*)this;
		_pPrev = (T*)this;
		_isFirst = true;
		_isLast = true;
		return (T*)this;
	} else {
		throw_GgafCriticalException("[GgafTreeLinkedList<"<<_class_name<<">::tear()] ＜警告＞ "<<getName()<<"は、何所にも所属していません");
	}

}


template<class T>
void GgafTreeLinkedList<T>::moveLast() {
	if (_isLast) { //既に最終ノードならば何もしない
		return;
	} else if (_isFirst) {  //先頭ノードならば、親の指している先頭ノードを次へずらす
		_pParent -> _pSubFirst = _pNext;
		_pPrev->_isLast = false;
		_isFirst = false;
		_isLast = true;
		_pNext->_isFirst = true;
	} else { //中間ノード時
		//両隣のノード同士を繋ぐ
		_pPrev -> _pNext = _pNext;
		_pNext -> _pPrev = _pPrev;
		//末尾ノードと先頭ノードの間にもぐりこませる
		_pParent -> _pSubFirst -> _pPrev -> _isLast = false;
		_isLast = true;
		_pPrev = _pParent -> _pSubFirst -> _pPrev;
		_pNext = _pParent -> _pSubFirst;
		_pParent -> _pSubFirst -> _pPrev -> _pNext = (T*)this;
		_pParent -> _pSubFirst -> _pPrev = (T*)this;
	}
}




template<class T>
void GgafTreeLinkedList<T>::moveFirst() {
	if (_isFirst) { //既に先頭ノードならば何もしない
		return;
	} else if (_isLast) {  //末尾ノードならば、親の指している先頭ノードを前にずらす
		_pParent -> _pSubFirst = (T*)this;
		_pPrev->_isLast = true;
		_isFirst = true;
		_isLast= false;
		_pNext -> _isFirst = false;
	} else { //中間ノード時
		//両隣のノード同士を繋ぐ
		_pPrev -> _pNext = _pNext;
		_pNext -> _pPrev = _pPrev;
		//末尾ノードと先頭ノードの間にもぐりこませる
		_pParent -> _pSubFirst -> _isFirst = false;
		_isFirst = true;
		_pPrev = _pParent -> _pSubFirst -> _pPrev;
		_pNext = _pParent -> _pSubFirst;
		_pParent -> _pSubFirst -> _pPrev -> _pNext = (T*)this;
		_pParent -> _pSubFirst -> _pPrev = (T*)this;
		_pParent -> _pSubFirst = (T*)this;
	}
}


template<class T>
void GgafTreeLinkedList<T>::setParent(T* prm_pParent) {
	_pParent = prm_pParent;
}

template<class T>
T* GgafTreeLinkedList<T>::getNext() {
	return (T*)_pNext;
}

template<class T>
T* GgafTreeLinkedList<T>::getPrev() {
	return (T*)_pPrev;
}


template<class T>
T* GgafTreeLinkedList<T>::getParent() {
	if (_pParent == NULL) {
		throw_GgafCriticalException("[GgafTreeLinkedList<"<<_class_name<<">::getParent()] Error! 親ノードがありません。");
	}
	return (T*)_pParent;
}


template<class T>
T* GgafTreeLinkedList<T>::getParent(string prm_parent_name) {
	_pNodeTemp = (T*)this;
	while(true) {
		_pNodeTemp = _pNodeTemp->_pParent;
		if (_pNodeTemp == NULL) {
			throw_GgafCriticalException("[GgafTreeLinkedList<"<<_class_name<<">::getParent()] Error! 親ノードがありません。(prm_parent_name="+prm_parent_name+")");
		} else if (_pNodeTemp->_name == prm_parent_name) {
			break;
		}
	}
	return _pNodeTemp;
}

template<class T>
T* GgafTreeLinkedList<T>::getSub(string prm_sub_actor_name) {
	if (_pSubFirst == NULL) {
		throw_GgafCriticalException("[GgafTreeLinkedList<"<<_class_name<<">::getSub()] Error! _pSubFirstがNULLです。");
	}
	_pNodeTemp = _pSubFirst;
	do {
		if(_pNodeTemp -> getName() == prm_sub_actor_name) {
			break;
		}
		if (_pNodeTemp -> _isLast) {
			throw_GgafCriticalException("[GgafTreeLinkedList<"<<_class_name<<">::getSub()] Error! 子ノードは存在しません。(prm_sub_actor_name="+prm_sub_actor_name+")");
		} else {
			_pNodeTemp = _pNodeTemp -> _pNext;
		}
	} while(true);
	return _pNodeTemp;
}

template<class T>
T* GgafTreeLinkedList<T>::getSubFirst() {
	return (T*)_pSubFirst;
}


template<class T>
bool GgafTreeLinkedList<T>::hasSub(string prm_sub_actor_name) {
	if (_pSubFirst == NULL) {
		return false;
	} else {
		_pNodeTemp = _pSubFirst;
		do {
			if(_pNodeTemp -> getName() == prm_sub_actor_name) {
				return true;
			}
			if (_pNodeTemp -> _isLast) {
				return false;
			} else {
				_pNodeTemp = _pNodeTemp -> _pNext;
			}
		} while(true);
	}
}


template<class T>
void GgafTreeLinkedList<T>::addSubLast(T* prm_pSub) {
	if (prm_pSub->_pParent != NULL) {
		throw_GgafCriticalException("[GgafTreeLinkedList<"<<_class_name<<">::addSubLast()] Error! ノードは既に所属しています(this="<<_name<<"/prm_pSub="+prm_pSub->getName()+")");
	}
	prm_pSub -> _pParent = (T*)this;
	prm_pSub -> _isLast = true;
	//prm_pSub -> _pScene_Platform = _pScene_Platform;

	if (_pSubFirst == NULL) {
		prm_pSub -> _isFirst = true;
		_pSubFirst = prm_pSub;
		_pSubFirst->_pNext = prm_pSub;
		_pSubFirst->_pPrev = prm_pSub;
	} else {
		prm_pSub -> _isFirst = false;
		T* pSubLast = _pSubFirst->_pPrev;
		pSubLast -> _isLast = false;
		pSubLast->_pNext = prm_pSub;
		prm_pSub->_pPrev = pSubLast;
		prm_pSub->_pNext = _pSubFirst;
		_pSubFirst->_pPrev = prm_pSub;
	}

}


template<class T>
string GgafTreeLinkedList<T>::getName() {
	return _name;
}
/*
template<class T>
bool GgafTreeLinkedList<T>::isNamed(string prm_name) {
	string::size_type iLen = prm_name.length();
	if (prm_name.rfind('*') == iLen-1) {}


	return _name;
}
*/

template<class T>
bool GgafTreeLinkedList<T>::isLast() {
	return _isLast;
}

template<class T>
bool GgafTreeLinkedList<T>::isFirst() {
	return _isFirst;
}

template<class T>
GgafTreeLinkedList<T>::~GgafTreeLinkedList() {
	_TRACE_("~GgafTreeLinkedList<"<<_class_name<<">() "+_name+" start-->");
	//自ノードのメンバの解放

//	if (_isAlive) {
//		_TRACE_("template<class T> GgafTreeLinkedList<T>::~GgafTreeLinkedList() "+_name+"：_isAliveはtrueおかしいクマー");
//	}

	//→現在の所無し


	//自分に子がある場合
	if (_pSubFirst != NULL) {
		//まずサブをdelete
		if (_pSubFirst->_isLast) {
			//子ノードは１つの場合
			delete (_pSubFirst);
			_pSubFirst = NULL;
		} else {
			//子ノードは２つ以上の場合
			T* pSubLast = _pSubFirst -> _pPrev;
			T* pSubLastPrev = pSubLast -> _pPrev;
			while(true) {
				delete (pSubLast); //末尾からdelete
				if (pSubLastPrev -> _isFirst) {
					delete (_pSubFirst); //pSubLastPrev == _pSubFirst である
					_pSubFirst = NULL;
					break;
				}
				pSubLast = pSubLastPrev;
				pSubLastPrev = pSubLastPrev -> _pPrev;
			}
		}
	}

	//自分に子ない場合
	if (_pParent != NULL) {
		//連結から外す
		T* pMyNext = _pNext;
		T* pMyPrev = _pPrev;
		if (_isFirst && _isLast) {
			//連結が自分のみ場合
			_pParent -> _pSubFirst = NULL;
			_pParent = NULL;
			_pNext = (T*)this;
			_pPrev = (T*)this;
			_pSubFirst = NULL;
		} else {
			//連結がから抜け出す場合
			//両隣のノード同士を繋ぎ、自分を指さなくする。
			pMyPrev -> _pNext = pMyNext;
			pMyNext -> _pPrev = pMyPrev;
			if (_isLast) {
				pMyPrev -> _isLast = true;
			}
			if (_isFirst) {
				pMyNext -> _isFirst = true;
				_pParent -> _pSubFirst = pMyNext;

			}
			_pParent = NULL;
			_pNext = (T*)this;
			_pPrev = (T*)this;
			_pSubFirst = NULL;
			_isFirst = true;
			_isLast = true;
		}
	}
	_TRACE_("~GgafTreeLinkedList<"<<_class_name<<">() "+_name+" <---end");
}

#endif /*GGAFTREENODE_H_*/
