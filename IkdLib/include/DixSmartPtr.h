// DixSmartPtr.h

// スマートポインタテンプレート  v2.11
//  Created by IKD (2008. 6. 30)
//   http://marupeke296.com

// 2007. 3. 6
// vectorに代入できないバグを修正（コピーコンストラクタのミスを修正）

// 2007. 3. 1
// 同形コピーでコピーコンストラクタが呼ばれない不具合を修正
// 明示的アップキャスト及び暗黙的アップキャストでダブルポインタが代入されない不具合を修正

// 2007. 2. 11
// スワップに対応

// 2008. 5. 8
// 配列サポート

// 2008. 6. 30
// 型キャスト代入の際に保護メンバであるm_isAryにアクセスできないコンパイルエラーを修正


// ・ 登録されたオブジェクトポインタの使用者がいなくなったら自動的にdelete
// ・ 通常のポインタ操作演算子「*」「->」「[ ]」が使える。
// ・ 異なるオブジェクトポインタが登録された状態でアップキャストができる
// ・ DownCastメソッドによる安全なダウンキャストサポート
// ・ SwapPtrメソッドによるポインタ入れ替えのサポート

#ifndef IKD_DIXSMARTPTR_H
#define IKD_DIXSMARTPTR_H

namespace Dix {
	template <class T>
	class sp
	{
	private:
	   unsigned int *m_pRefCnt;   // 参照カウンタへのポインタ
	   T** m_ppPtr;             // T型のオブジェクトのダブルポインタ
	   static T* m_NullPtr;		// NULLポインタ値
	   bool m_isAry;			// 配列か？

	private:
	   /////////////////
	   // 参照カウンタ増加
	   /////
		  void AddRef(){(*m_pRefCnt)++;}

	   /////////////////
	   // 参照カウンタ減少
	   /////
		  void Release()
		  {
			 if(--(*m_pRefCnt) == 0){
				 if ( m_isAry )
					 delete[] *m_ppPtr;	// 配列メモリ削除
				 else
					 delete *m_ppPtr;	// 単位メモリ削除
				 delete m_ppPtr;
				 delete m_pRefCnt;
			 }
		  }

	public:
       ///////////////////////
	   // デフォルトコンストラクタ
	   /////
		  explicit sp(T* src=0, int add=0)
		  {
			 m_pRefCnt = new unsigned int;
			 *m_pRefCnt = add;
			 m_ppPtr = new T*;
			 m_NullPtr = 0;
			 if(src)
				 *m_ppPtr = src;
			 else
				 *m_ppPtr = m_NullPtr;   // NULLポインタを入れておく
			 AddRef();       // 参照カウンタ増加
			 m_isAry = false;
		  }

       //////////////////////////////////////////////
	   // 配列フラグ付きデフォルトコンストラクタ
	   /////
		  sp(T* src, bool isAry, int add=0)
		  {
			 m_pRefCnt = new unsigned int;
			 *m_pRefCnt = add;
			 m_ppPtr = new T*;
			 m_NullPtr = 0;
			 if(src)
				 *m_ppPtr = src;
			 else
				 *m_ppPtr = m_NullPtr;   // NULLポインタを入れておく
			 AddRef();       // 参照カウンタ増加
			 m_isAry = isAry;
		  }

	   //////////////////////////////////////
	   // コピーコンストラクタ（同型コピー）
	   /////
		  sp(const sp<T> &src)
		  {
			 // 相手のポインタをすべてコピー
			 m_pRefCnt = src.m_pRefCnt;   // 参照カウンタポインタ
			 m_ppPtr = src.m_ppPtr;       // T型ダブルポインタ
			 m_isAry = src.m_isAry;

			 // 自分自身の参照カウンタを増加
			 AddRef();
		  }

	  //////////////////////////////////////
	   // コピーコンストラクタ（暗黙的アップキャスト）
	   /////
		  template<class T2> sp(sp<T2> &src)
		  {
			 // 相手のダブルポインタをコピー
			 m_pRefCnt = src.GetRefPtr();
			 m_ppPtr = (T**)src.GetPtrPtr();

			 // 型チェックコピー
			 *m_ppPtr = src.GetPtr();

			 m_isAry = src.isAry();m_isAry;

			 // 自分自身の参照カウンタを増加
			 AddRef();
		  }


	   //////////////////////////////////////
	   // コピーコンストラクタ（NULL代入代用）
	   /////
		  sp(const int nullval)
		  {
			 m_pRefCnt = new unsigned int;
			 *m_pRefCnt = 0;
			 m_ppPtr = new T*;
			 *m_ppPtr = m_NullPtr;
			 AddRef();       // 参照カウンタ増加
			 m_isAry = false;
		  }


	   ///////////////
	   // デストラクタ
	   /////
		 virtual ~sp()
		  {
			 Release();
		  }


	//■■■演算子のオーバーロード■■■■■■■■■■■


	   /////////////////////////////////
	   // =代入演算子（明示的コピー）
	   /////
		  sp<T>& operator =(const sp<T> &src)
		  {
			 // 自分自身への代入は不正で意味が無いので
			 // 行わない。
			 if(*src.m_ppPtr == *m_ppPtr)
				return (*this);

			  // 自分は他人になってしまうので
			 // 参照カウンタを1つ減少
			 Release();

			 // 相手のポインタをコピー
			 m_pRefCnt = src.m_pRefCnt;
			 m_ppPtr = src.m_ppPtr;

			 m_isAry = src.m_isAry;

			 // 新しい自分自身の参照カウンタを増加
			 AddRef();

			 return (*this);
		  }


	   /////////////////////////////////
	   // =代入演算子（明示的アップキャスト）
	   /////
		  template<class T2> sp<T>& operator =(sp<T2> &src)
		  {
			 // 自分自身への代入は不正で意味が無いので
			 // 行わない。
			 if(src.GetPtr() == *m_ppPtr)
				return (*this);

			  // 自分は他人になってしまうので
			 // 参照カウンタを1つ減少
			 Release();

			 // 相手のポインタをコピー
			 m_pRefCnt = src.GetRefPtr();
			 m_ppPtr = (T**)src.GetPtrPtr();

			 // 型チェックコピー
			 *m_ppPtr = src.GetPtr();

 			 m_isAry = src.m_isAry;

			 // 新しい自分自身の参照カウンタを増加
			 AddRef();

			 return (*this);
		  }


	   /////////////////////////////////
	   // =代入演算子(NULL代入によるリセット）
	   /////
		  sp<T>& operator =(const int nullval)
		  {
			  // 自分は空な人になってしまうので
			  // 参照カウンタを1つ減少
			  Release();

			  // 新規に自分自身を作る
			  m_pRefCnt = new unsigned int(1);
			  m_ppPtr = new T*;
			  *m_ppPtr = m_NullPtr;
			  m_isAry = false;

			 return (*this);
		  }


	   ///////////////
	   // *間接演算子
	   /////
		  T& operator *(){ return **m_ppPtr;}

	   //////////////////////
	   // ->メンバ選択演算子
	   /////
		  T* operator ->(){ return *m_ppPtr;}

	   /////////////////
	   // ==比較演算子
	   /////
	/*      bool operator ==(int val){
			 if((int)m_pPtr == val)
				return TRUE;
			 return FALSE;
		  }
	*/
		  bool operator ==(T *val){
			 if(*m_ppPtr == val)
				return true;
			 return false;
		  }

	   /////////////////
	   // !=比較演算子
	   /////
	/*      bool operator !=(int val){
			 if((int)m_pPtr != val)
				return TRUE;
			 return FALSE;
		  }
	*/
		  bool operator !=(T *val){
			 if(*m_ppPtr != val)
				return true;
			 return false;
		  }

	  ///////////////////
	  // 配列参照演算子
	  /////
		  T& operator[]( int elem ) {
			 return (*m_ppPtr)[ elem ];
		  }

	  ///////////////////
	  // ポインタ演算子
	  /////
		  T* operator+( int add ) {
			 return (*m_ppPtr + add);
		  }


	//■■■ メンバ関数 ■■■■■■■■■■■

	public:
	   //////////////////////////
	   // ポインタの明示的な登録
	   /////
		  void SetPtr(T* src = ((void *)0), int add=0)
		  {
			 // 参照カウンタを減らした後に再初期化
				Release();
				m_pRefCnt = new unsigned int;
				*m_pRefCnt = add;
				m_ppPtr = new T*;
				if(src)
					*m_ppPtr = src;
				else
					*m_ppPtr = m_NullPtr;
				AddRef();
		  }

	   ////////////////////////////////////////////
	   // ポインタの明示的な登録（配列フラグ付き）
	   /////
		  void SetPtr(T* src, bool isAry, int add=0)
		  {
			 // 参照カウンタを減らした後に再初期化
				Release();
				m_pRefCnt = new unsigned int;
				*m_pRefCnt = add;
				m_ppPtr = new T*;
				if(src) {
					*m_ppPtr = src;
					m_isAry = isAry;
				}
				else {
					*m_ppPtr = m_NullPtr;
					m_isAry = false;
				}
				AddRef();
		  }

	   /////////////////////
	   // ポインタの貸し出し
	   /////
		  T* GetPtr(){return *m_ppPtr;}
		  T** GetPtrPtr(){ return m_ppPtr;}

	   /////////////////////
	   // 値取得
	   /////
		  T& At( int elem = 0 ) {
			  return (*m_ppPtr)[ elem ];
		  }

	   ///////////////////////////////
	   // 参照カウンタへのポインタを取得
	   /////
		  unsigned int* GetRefPtr(){return m_pRefCnt;}

	   //////////////////////////
	   // ダウンキャストコピー
	   /////
		template <class T2> bool DownCast(sp<T2> &src)
		{
			// 引数のスマートポインタの持つポインタが、
			// 自分の登録しているポインタに
			// ダウンキャスト可能な場合はダウンキャストコピーを実行
			T* castPtr = dynamic_cast<T*>(src.GetPtr());
			if(castPtr){
				// ダウンキャスト成功
				// 自分は違う人になるので
				// 既存の参照カウンタを1つ減少
				Release();
				// 新しいポインタと参照カウンタを共有
				m_ppPtr = (T**)src.GetPtrPtr();
				*m_ppPtr = castPtr;
				m_pRefCnt = src.GetRefPtr();

				m_isAry = src.m_isAry;

				// 参照カウンタ増加
				AddRef();
				return true;
			}

			return false;
		}

		///////////////////////
		// ポインタスワップ（交換）
		///////
		void SwapPtr( sp<T> &src )
		{
			// ポインタの交換
			T* pTmp = src.GetPtr();
			*src.m_ppPtr = *m_ppPtr;
			*m_ppPtr = pTmp;

			// 配列フラグの交換
			bool tmp = src.m_isAry;
			src.m_isAry = m_isAry;
			m_isAry = tmp;
		}

		///////////////////////
		// 配列？
		///////
		bool isAry() {
			return m_isAry;
		}
	};

	template <class T>
	T* sp<T>::m_NullPtr = 0;

} // end namespace Dix


#endif // !defined(AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_)
