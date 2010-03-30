// DixSmartPtr.h

// �X�}�[�g�|�C���^�e���v���[�g  v2.24
//  Created by IKD (2010. 3. 18)
//   http://marupeke296.com


// 2007. 2. 11
// �X���b�v�ɑΉ�

// 2007. 3. 1
// ���`�R�s�[�ŃR�s�[�R���X�g���N�^���Ă΂�Ȃ��s����C��
// �����I�A�b�v�L���X�g�y�шÖٓI�A�b�v�L���X�g�Ń_�u���|�C���^���������Ȃ��s����C��

// 2007. 3. 6
// vector�ɑ���ł��Ȃ��o�O���C���i�R�s�[�R���X�g���N�^�̃~�X���C���j

// 2008. 5. 8
// �z��T�|�[�g

// 2008. 6. 30( v2.12 )
// �^�L���X�g����̍ۂɕی상���o�ł���m_isAry�ɃA�N�Z�X�ł��Ȃ��R���p�C���G���[���C��

// 2009. 4. 29( v2.20 )
// �E�B�[�N�|�C���^�ǉ�

// 2009. 5. 4( v2.21 )
// �E�B�[�N�|�C���^�ɃX�}�[�g�|�C���^�̃A�b�v�L���X�g����R���X�g���N�^��ǉ�
// �_�E���L���X�g���\�b�h�̃G���[���C��

// 2010. 1. 8( v.2.22 )
// �ԐڎQ�Ɖ��Z�q�y�уA���[���Z�q��const�֐��ǉ��iconst���t�����֐����ŎQ�Ƃł��Ȃ��o�O������j

// 2010. 1. 15( v2.23 )
// �^�L���X�g����̍ۂɕی상���o�ł���m_isAry�ɃA�N�Z�X�ł��Ȃ��R���p�C���G���[���C��
// �Q�b�^�[���\�b�h�Q��const�t�L

// 2010. 3. 18( v2.24 )
// �E�B�[�N�|�C���^��IsExist���\�b�h���Q�ƃJ�E���g�����Ă��Ȃ������o�O���C��
// ����A�h���X���m�ۂ��Ă����X�}�[�g�|�C���^����x��������A�����œ����A�h���X���m�ۂ��ꂽ�ꍇ��
// �E�B�[�N�|�C���^�ɂ��̃X�}�[�g�|�C���^���������Ȃ��o�O���C��

// 2010, 3. 30( v2.25 )
// NULL��r���Z�q�𐳂��������悤�ɂ���


// �E �o�^���ꂽ�I�u�W�F�N�g�|�C���^�̎g�p�҂����Ȃ��Ȃ����玩���I��delete
// �E �ʏ�̃|�C���^���쉉�Z�q�u*�v�u->�v�u[ ]�v���g����B
// �E �قȂ�I�u�W�F�N�g�|�C���^���o�^���ꂽ��ԂŃA�b�v�L���X�g���ł���
// �E DownCast���\�b�h�ɂ����S�ȃ_�E���L���X�g�T�|�[�g
// �E SwapPtr���\�b�h�ɂ��|�C���^����ւ��̃T�|�[�g
// �E �E�B�[�N�|�C���^�T�|�[�g


#ifndef IKD_DIXSMARTPTR_H
#define IKD_DIXSMARTPTR_H

namespace Dix {

    // �X�}�[�g�|�C���^�e���v���[�g
    template <class T>
    class sp
    {



//	protected:
//		template<class T> friend class wp;

//��̏�������GCC�ł͏o���Ȃ��B�Ƃ肠����public�ŉ���B
//TODO:�e���v���[�g�t�����h�N���X�̕׋�

    public:
//	private:
        unsigned int*	m_pRefCnt;		// �Q�ƃJ�E���^�ւ̃|�C���^
        unsigned int*	m_pWeakCnt;		// �E�B�[�N�J�E���^�ւ̃|�C���^
        T**				m_ppPtr;		// T�^�̃I�u�W�F�N�g�̃_�u���|�C���^
        static T*		m_NullPtr;		// NULL�|�C���^�l
        bool				m_isAry;		// �z�񂩁H


//	private:
        /////////////////
        // �Q�ƃJ�E���^����
        /////
        void AddRef() {
            if ( m_pRefCnt != 0 )
                (*m_pRefCnt)++;
            if ( m_pWeakCnt != 0 )
                (*m_pWeakCnt)++;
        }

        /////////////////
        // �Q�ƃJ�E���^����
        /////
        void Release()
        {
            // �Q�ƃJ�E���^����
            if( m_pRefCnt != 0 && ( *m_pRefCnt == 0 || --(*m_pRefCnt) == 0 ) ) {

                if ( m_isAry )
                    delete[] *m_ppPtr;	// �z�񃁃����폜
                else
                    delete *m_ppPtr;	// �P�ʃ������폜

                delete m_ppPtr;
            }

            // �E�B�[�N�J�E���^�`�F�b�N
            if ( m_pWeakCnt != 0 && ( *m_pWeakCnt == 0 || --(*m_pWeakCnt) == 0 ) ) {
                delete m_pWeakCnt;
                delete m_pRefCnt;
            }
        }


    public:
       ///////////////////////
       // �f�t�H���g�R���X�g���N�^
       /////
        explicit sp( T* src=0, int add=0 ) :
            m_pRefCnt	( 0 ),
            m_pWeakCnt	( 0 ),
            m_ppPtr		( 0 )
        {
            SetPtr( src, add );
        }

        //////////////////////////////////////////////
        // �z��t���O�t���f�t�H���g�R���X�g���N�^
        /////
        sp(T* src, bool isAry, int add=0) :
            m_pRefCnt	( 0 ),
            m_pWeakCnt	( 0 ),
            m_ppPtr		( 0 )
        {
            SetPtr( src, isAry, add );
        }

        //////////////////////////////////////
        // �R�s�[�R���X�g���N�^�i���^�R�s�[�j
        /////
        sp( const sp<T> &src ) :
            m_pRefCnt	( 0 ),
            m_pWeakCnt	( 0 ),
            m_ppPtr		( 0 )
        {
            // ���肪NULL�|�C���^�̏ꍇ��
            // �������g����ɂ���
            if ( src.m_pRefCnt == 0 ) {
                Clear();
            } else {
                // ����̃|�C���^�����ׂăR�s�[
                m_pRefCnt  = src.m_pRefCnt;
                m_pWeakCnt = src.m_pWeakCnt;
                m_ppPtr    = src.m_ppPtr;
                m_isAry    = src.IsAry();

                AddRef();
            }
        }

        //////////////////////////////////////
        // �R�s�[�R���X�g���N�^�i�ÖٓI�A�b�v�L���X�g�j
        /////
        template<class T2> sp(sp<T2> &src) :
            m_pRefCnt	( 0 ),
            m_pWeakCnt	( 0 ),
            m_ppPtr		( 0 )
        {
            // ���肪NULL�|�C���^�̏ꍇ��
            // �������g����ɂ���
            if ( src.GetRefPtr() == 0 ) {
                Clear();
            } else {
                m_pRefCnt  = src.GetRefPtr();
                m_pWeakCnt = src.GetWeakCntPtr();
                m_ppPtr    = (T**)src.GetPtrPtr();

                // �^�`�F�b�N�R�s�[
                *m_ppPtr = src.GetPtr();

                m_isAry = src.IsAry();

                AddRef();
            }
        }


        //////////////////////////////////////
        // �R�s�[�R���X�g���N�^�iNULL�����p�j
        /////
        sp(const int nullval) :
            m_pRefCnt	( 0 ),
            m_pWeakCnt	( 0 ),
            m_ppPtr		( 0 ),
            m_isAry		( false )
        {
            // ����ۂɂ���
        }


       ///////////////
       // �f�X�g���N�^
       /////
         virtual ~sp()
          {
             Release();
          }


    //���������Z�q�̃I�[�o�[���[�h����������������������


        /////////////////////////////////
        // =������Z�q�i�����I�R�s�[�j
        /////
        sp<T>& operator =( const sp<T> &src )
        {
            // src��NULL�|�C���^�̏ꍇ��
            // ������ɂ���
            if ( src.m_pRefCnt == 0 ) {
                Clear();
            } else {
                if ( m_pRefCnt != 0 ) {
                    // �����I�u�W�F�N�g���m�̃R�s�[��
                    // �Ӗ����Ȃ��̂ōs��Ȃ��B
                    if ( *src.m_ppPtr == *m_ppPtr )
                        return (*this);
                }

                // �����͑��l�ɂȂ��Ă��܂��̂�
                // �Q�ƃJ�E���^��1����
                Release();

                // ����̃|�C���^���R�s�[
                m_pRefCnt  = src.m_pRefCnt;
                m_pWeakCnt = src.m_pWeakCnt;
                m_ppPtr    = src.m_ppPtr;
                m_isAry    = src.IsAry();
                AddRef();
            }
            return (*this);
        }

        /////////////////////////////////
        // =������Z�q�i�����I�A�b�v�L���X�g�j
        /////
        template<class T2> sp<T>& operator =( sp<T2> &src )
        {
            // src��NULL�|�C���^�̏ꍇ��
            // ������ɂ���
            if ( src.GetRefPtr() == 0 ) {
                Clear();
            } else {
                if ( m_pRefCnt != 0 ) {
                    // �����I�u�W�F�N�g���m�̃R�s�[��
                    // �Ӗ����Ȃ��̂ōs��Ȃ��B
                    if ( *src.GetPtrPtr() == *m_ppPtr )
                        return (*this);
                }

                // �����͑��l�ɂȂ��Ă��܂��̂�
                // �Q�ƃJ�E���^��1����
                Release();

                // ����̃|�C���^���R�s�[
                m_pRefCnt  = src.GetRefPtr();
                m_pWeakCnt = src.GetWeakCntPtr();
                m_ppPtr    = (T**)src.GetPtrPtr();
                m_isAry    = src.IsAry();

                // �^�`�F�b�N�R�s�[
                *m_ppPtr = src.GetPtr();

                AddRef();
            }

            return (*this);
          }


        /////////////////////////////////
        // =������Z�q(NULL����ɂ�郊�Z�b�g�j
        /////
        sp<T>& operator =( const int nullval )
        {
            // �����͋�Ȑl�ɂȂ��Ă��܂��̂�
            // �Q�ƃJ�E���^��1����
            Clear();
            return (*this);
        }

        ///////////////
        // *�Ԑډ��Z�q
        /////
        T& operator *() {
            return **m_ppPtr;
        }
        T& operator *() const {
            return **m_ppPtr;
        }

        //////////////////////
        // ->�����o�I�����Z�q
        /////
        T* operator ->(){
            return *m_ppPtr;
        }
        T* operator ->() const {
            return *m_ppPtr;
        }

        /////////////////
        // ==��r���Z�q
        /////
        bool operator ==( sp<T>& val ) const {
            if( m_ppPtr != 0 && *m_ppPtr == val.GetPtr() )
                return true;
            if( m_ppPtr == 0 && val.GetPtr() == 0 )
                return true;
            return false;
        }

        bool operator ==( T *val ) const {
            if( m_ppPtr != 0 && *m_ppPtr == val )
                return true;
            return false;
        }

        bool operator ==( const int nul ) const {	// NULL�Ƃ̔�r��p
            if ( m_ppPtr == 0 || *m_ppPtr == 0 )
                return true;
            return false;
        }

        /////////////////
        // !=��r���Z�q
        /////
        bool operator !=( sp<T>& val ) const {
            if( m_ppPtr != 0 && *m_ppPtr != val.GetPtr() )
                return true;
            return false;
        }

        bool operator !=( T *val ) const {
            if( m_ppPtr != 0 && *m_ppPtr != val )
                return true;
            return false;
        }

        bool operator !=( const int nul ) const {	// NULL�Ƃ̔�r��p
            if ( m_ppPtr == 0 || *m_ppPtr == 0 )
                return false;
            return true;
        }

        ///////////////////
        // �z��Q�Ɖ��Z�q
        /////
        T& operator[]( int elem ) const {
            return (*m_ppPtr)[ elem ];
        }

        ///////////////////
        // �|�C���^���Z�q
        /////
        T* operator+( int add ) const {
            return ( *m_ppPtr + add );
        }


    //������ �����o�֐� ����������������������

    public:
        //////////////////////////
        // �|�C���^�̖����I�ȓo�^
        /////
        void SetPtr( T* src = 0, int add = 0 )
        //void SetPtr( T* src = NULL, int add = 0 )
        {
            // �Q�ƃJ�E���^�����炵����ɍď�����
            Release();

            // Src�������̏ꍇ�͂��ׂĂ�NULL�ɂ��܂�
            if ( src == 0 ) {
                Clear();
            } else {
                // Src���L���Ȃ̂ŎQ�ƃJ�E���^�𑝉������܂�
                m_pRefCnt = new unsigned int;
                *m_pRefCnt = add;
                m_pWeakCnt = new unsigned int;
                *m_pWeakCnt = add;
                m_ppPtr = new T*;
                *m_ppPtr = src;

                AddRef();       // �Q�ƃJ�E���^����
            }

            m_isAry = false;
        }

       ////////////////////////////////////////////
       // �|�C���^�̖����I�ȓo�^�i�z��t���O�t���j
       /////
        void SetPtr( T* src, bool isAry, int add = 0)
        {
            // �Q�ƃJ�E���^�����炵����ɍď�����
            Release();
            // Src�������̏ꍇ�͂��ׂĂ�NULL�ɂ��܂�
            if ( src == 0 ) {
                Clear();
            } else {
                // Src���L���Ȃ̂ŎQ�ƃJ�E���^�𑝉������܂�
                m_pRefCnt = new unsigned int;
                *m_pRefCnt = add;
                m_pWeakCnt = new unsigned int;
                *m_pWeakCnt = add;
                m_ppPtr = new T*;
                *m_ppPtr = src;

                AddRef();       // �Q�ƃJ�E���^����
            }
            if ( src ) {
                m_isAry = isAry;
            }
    }

        /////////////////////
        // �N���A
        /////
        void Clear() {
            Release();
            m_pRefCnt  = 0;
            m_pWeakCnt = 0;
            m_ppPtr    = 0;
            m_isAry    = 0;
        }

        /////////////////////
        // �|�C���^�݂̑��o��
        /////
        T* GetPtr() const {
            if ( m_ppPtr == 0 )
                return 0;
            return *m_ppPtr;
        }

        T** GetPtrPtr() const {
            return m_ppPtr;
        }

       /////////////////////
       // �l�擾
       /////
          T& At( int elem = 0 ) const {
              return (*m_ppPtr)[ elem ];
          }

        ///////////////////////////////
        // �Q�ƃJ�E���^�ւ̃|�C���^���擾
        /////
        unsigned int* GetRefPtr() const {
            return m_pRefCnt;
        }

        ///////////////////////////////
        // �Q�ƃJ�E���^�����擾
        /////
        unsigned int GetRefNum() const {
            if ( m_pRefCnt == 0 )
                return 0;
            return *m_pRefCnt;
        }

        ///////////////////////////////
        // �E�B�[�N�|�C���^�J�E���^�ւ̃|�C���^���擾
        /////
        unsigned int* GetWeakCntPtr() const {
            return m_pWeakCnt;
        }

        ///////////////////////////////
        // �E�B�[�N�J�E���^�����擾
        /////
        unsigned int GetWeakNum() const {
            if ( m_pWeakCnt == 0 )
                return 0;
            return *m_pWeakCnt;
        }

        //////////////////////////
        // �_�E���L���X�g�R�s�[
        /////
        template <class T2> bool DownCast( sp<T2> &src )
        {
            if ( src.GetRefPtr() == 0 ) {
                return false;
            }

            // �����̃X�}�[�g�|�C���^�̎��|�C���^���A
            // �����̓o�^���Ă���|�C���^��
            // �_�E���L���X�g�\�ȏꍇ�̓_�E���L���X�g�R�s�[�����s
            T* castPtr = dynamic_cast<T*>( src.GetPtr() );

            if( castPtr ){
                // �_�E���L���X�g����
                // �����͈Ⴄ�l�ɂȂ�̂�
                // �����̎Q�ƃJ�E���^��1����
                Release();

                // �V�����|�C���^�ƎQ�ƃJ�E���^�����L
                m_ppPtr    = (T**)src.GetPtrPtr();
                *m_ppPtr   = castPtr;
                m_pRefCnt  = src.GetRefPtr();
                m_pWeakCnt = src.GetWeakCntPtr();
                m_isAry    = src.IsAry();

                AddRef();
                return true;
            }

            return false;
        }

        ///////////////////////
        // �|�C���^�X���b�v�i�����j
        ///////
        bool SwapPtr( sp<T> &src )
        {
            // �o�����L���|�C���^�ł��鎖��O��ɂ��܂�
            if ( src.GetRefPtr() == 0 || GetRefPtr() == 0 )
                return false;

            // �|�C���^�̌���
            T* pTmp		 = src.GetPtr();
            *src.m_ppPtr = *m_ppPtr;
            *m_ppPtr	 = pTmp;

            // �z��t���O�̌���
            bool tmp	 = src.IsAry();
            src.m_isAry  = m_isAry;
            m_isAry		 = tmp;

            return true;
        }

        ///////////////////////
        // �z��H
        ///////
        bool IsAry() const {
            return m_isAry;
        }
    };

    template <class T>
    T* sp<T>::m_NullPtr = 0;




    // �E�B�[�N�|�C���^
    template <class T>
    class wp
    {
    private:
        unsigned int*	m_pRefCnt;		// �Q�ƃJ�E���^�ւ̃|�C���^
        unsigned int*	m_pWeakCnt;		// �E�B�[�N�J�E���^�ւ̃|�C���^
        T**				m_ppPtr;		// �I�u�W�F�N�g�ւ̃_�u���|�C���^
        static T*		m_NullPtr;		// NULL�|�C���^�l
        bool			m_isAry;		// �z�񂩁H


    private:
        ///////////////////////
        // �Q�ƃJ�E���^����
        /////
        unsigned int AddRef() {
            if ( m_pWeakCnt == 0 )
                return 0;
            return ++(*m_pWeakCnt);
        }

        ///////////////////////
        // �Q�ƃJ�E���^����
        /////
        unsigned int Release() {
            if ( m_pWeakCnt != 0 ) {
                if ( --(*m_pWeakCnt) == 0 ) {
                    // �E�B�[�N�J�E���^�폜
                    delete m_pWeakCnt;
                    delete m_pRefCnt;
                    return 0;
                }
                return *m_pWeakCnt;
            }
            return 0;
        }

    public:
        ///////////////////////
        // �R���X�g���N�^
        /////
        wp() :
            m_ppPtr     ( 0 ),
            m_pRefCnt   ( 0 ),
            m_pWeakCnt  ( 0 ),
            m_isAry		( false )
        {
        }

        wp( sp<T>& src ) {
            m_ppPtr    = src.GetPtrPtr();
            m_pRefCnt  = src.GetRefPtr();
            m_pWeakCnt = src.GetWeakCntPtr();
            m_isAry = src.IsAry();

            AddRef();
        }

        //////////////////////////////////////
        // �R�s�[�R���X�g���N�^�i���^�R�s�[�j
        /////
        wp( const wp<T> &src )
        {
            // ����̃|�C���^�����ׂăR�s�[
            m_pRefCnt  = src.m_pRefCnt;		// �Q�ƃJ�E���^�|�C���^
            m_pWeakCnt = src.m_pWeakCnt;	// �E�B�[�N�J�E���^�|�C���^
            m_ppPtr    = src.m_ppPtr;       // T�^�_�u���|�C���^
            m_isAry    = src.IsAry();

            // �������g�̎Q�ƃJ�E���^�𑝉�
            AddRef();
        }

        //////////////////////////////////////
        // �R�s�[�R���X�g���N�^�i�ÖٓI�A�b�v�L���X�g�j
        /////
        template<class T2> wp( wp<T2> &src )
        {
            // ����̃|�C���^���R�s�[
            m_pRefCnt  = src.GetRefPtr();
            m_pWeakCnt = src.GetWeakCntPtr();
            m_ppPtr	   = (T**)src.GetPtrPtr();

            // �^�`�F�b�N�R�s�[
            if ( m_ppPtr )
                *m_ppPtr = src.GetPtr();

            m_isAry = src.IsAry();

            // �������g�̎Q�ƃJ�E���^�𑝉�
            AddRef();
        }

        //////////////////////////////////////
        // �R�s�[�R���X�g���N�^�i�X�}�[�g�|�C���^�ÖٓI�A�b�v�L���X�g�j
        /////
        template<class T2> wp( sp<T2> &src ) :
            m_ppPtr     ( 0 ),
            m_pRefCnt   ( 0 ),
            m_pWeakCnt  ( 0 ),
            m_isAry		( false )
        {
            // ���肪NULL�|�C���^�������ꍇ��
            // �������Ŏ�����NULL�|�C���^�ɂȂ�
            if ( src.GetPtr() == 0 ) {
                Clear();
            } else {
                T* p = (T*)dynamic_cast<T*>( src.GetPtr() );
                if ( p != 0 ) {
                    // ����̃|�C���^���R�s�[
                    m_pRefCnt  = src.GetRefPtr();
                    m_pWeakCnt = src.GetWeakCntPtr();
                    m_ppPtr    = (T**)src.GetPtrPtr();

                    m_isAry = src.IsAry();

                    // �V�����������g�̎Q�ƃJ�E���^�𑝉�
                    AddRef();
                }
            }
        }

        //////////////////////////////////////
        // �R�s�[�R���X�g���N�^�iNULL�����p�j
        /////
        wp( const int nullval ) :
            m_ppPtr     ( 0 ),
            m_pRefCnt   ( 0 ),
            m_pWeakCnt  ( 0 ),
            m_isAry		( false )
        {
        }

        ///////////////
        // �f�X�g���N�^
        /////
        virtual ~wp()
        {
            Release();
        }


    //���������Z�q�̃I�[�o�[���[�h����������������������


        /////////////////////////////////
        // =������Z�q�i�����I�R�s�[�j
        /////
        wp<T>& operator =( const wp<T> &src )
        {
            // ��������łȂ���΃`�F�b�N��
            if ( m_pWeakCnt != 0 ) {
                // �X�}�[�g�|�C���^���I�u�W�F�N�g��������Ă��Ȃ�
                // �ꍇ��m_ppPtr���L���Ȃ̂Ń`�F�b�N
                if ( src.m_pRefCnt != 0 && *src.m_pRefCnt != 0 ) {
                    // �������g�ւ̑���͕s���ňӖ��������̂�
                    // �s��Ȃ��B
                    if ( src.m_ppPtr != 0 && *src.m_ppPtr == *m_ppPtr )
                        return (*this);
                }

                // �����͑��l�ɂȂ��Ă��܂��̂�
                // �Q�ƃJ�E���^��1����
                Release();
            }

            // ����̃|�C���^���R�s�[
            m_pRefCnt  = src.m_pRefCnt;
            m_pWeakCnt = src.m_pWeakCnt;
            m_ppPtr    = src.m_ppPtr;

            m_isAry    = src.IsAry();

            // �V�����������g�̎Q�ƃJ�E���^�𑝉�
            AddRef();

            return (*this);
        }

        /////////////////////////////////
        // =������Z�q�i�����I�R�s�[�j
        /////
        wp<T>& operator =( sp<T> &src )
        {
            // ��������łȂ���΃`�F�b�N��
            if ( m_pWeakCnt != 0 ) {
                if ( src.GetRefPtr() != 0 && *src.GetRefPtr() != 0 ) {
                    // �������g�ւ̑���͕s���ňӖ��������̂ōs��Ȃ��B
                    // �������A�������Q�Ƃ��Ă���X�}�[�g�|�C���^��
                    // �Q�ƃJ�E���^��0�̏ꍇ�͑����������B
                    if ( GetRefNum() != 0 && src.GetPtrPtr() != 0 && *src.GetPtrPtr() == *m_ppPtr )
                        return (*this);
                }

                // �����͑��l�ɂȂ��Ă��܂��̂�
                // �Q�ƃJ�E���^��1����
                Release();
            }

            // ����̃|�C���^���R�s�[
            m_pRefCnt  = src.GetRefPtr();
            m_pWeakCnt = src.GetWeakCntPtr();
            m_ppPtr    = src.GetPtrPtr();

            m_isAry = src.IsAry();

            // �V�����������g�̎Q�ƃJ�E���^�𑝉�
            AddRef();

            return (*this);
        }


        /////////////////////////////////
        // =������Z�q�i�����I�L���X�g�j
        /////
        template<class T2> wp<T>& operator =( sp<T2> &src ) {

            // ���肪NULL�|�C���^�������ꍇ��
            // �������Ŏ�����NULL�|�C���^�ɂȂ�
            if ( src.GetPtr() == 0 ) {
                Clear();
                return (*this);
            }

            T* p = (T*)dynamic_cast<T*>( src.GetPtr() );
            if ( p == 0 ) {
                return (*this);
            } else {
                // ��������łȂ���΃`�F�b�N��
                if ( m_pWeakCnt != 0 ) {
                    // �X�}�[�g�|�C���^���I�u�W�F�N�g��������Ă��Ȃ�
                    // �ꍇ��m_ppPtr���L���Ȃ̂Ń`�F�b�N
                    if ( src.GetRefPtr() != 0 && *src.GetRefPtr() != 0 ) {
                        // �������g�ւ̑���͕s���ňӖ��������̂�
                        // �s��Ȃ��B
                        if ( src.GetPtrPtr() != 0 && *src.GetPtrPtr() == *m_ppPtr )
                            return (*this);
                    }

                    // �����͑��l�ɂȂ��Ă��܂��̂�
                    // �Q�ƃJ�E���^��1����
                    Release();
                }

                // ����̃|�C���^���R�s�[
                m_pRefCnt  = src.GetRefPtr();
                m_pWeakCnt = src.GetWeakCntPtr();
                m_ppPtr    = (T**)src.GetPtrPtr();

                m_isAry = src.IsAry();

                // �V�����������g�̎Q�ƃJ�E���^�𑝉�
                AddRef();
            }

            return (*this);
        }

        /////////////////////////////////
        // =������Z�q�i�����I�A�b�v�L���X�g�j
        /////
        template<class T2> wp<T>& operator =( wp<T2> &src )
        {
            // ��������łȂ���΃`�F�b�N��
            if ( m_pWeakCnt != 0 ) {
                // �X�}�[�g�|�C���^���I�u�W�F�N�g��������Ă��Ȃ�
                // �ꍇ��m_ppPtr���L���Ȃ̂Ń`�F�b�N
                if ( src.m_pRefCnt != 0 && *src.m_pRefCnt != 0 ) {
                    // �������g�ւ̑���͕s���ňӖ��������̂�
                    // �s��Ȃ��B
                    if ( src.m_ppPtr != 0 && *src.m_ppPtr == *m_ppPtr )
                        return (*this);
                }

                // �����͑��l�ɂȂ��Ă��܂��̂�
                // �Q�ƃJ�E���^��1����
                Release();
            }

            // ����̃|�C���^���R�s�[
            m_pRefCnt = src.GetRefPtr();
            m_pWeakCnt = src.GetWeakCntPtr();
            m_ppPtr = (T**)src.GetPtrPtr();

            // �^�`�F�b�N�R�s�[
            if ( m_ppPtr )
                *m_ppPtr = src.GetPtr();

            m_isAry = src.IsAry();

            // �V�����������g�̎Q�ƃJ�E���^�𑝉�
            AddRef();

            return (*this);
        }

        /////////////////
        // ==��r���Z�q
        /////
        bool operator ==( sp<T>& val ) const {
            if( m_ppPtr != 0 && *m_ppPtr == val.GetPtr() )
                return true;
            if( m_ppPtr == 0 && val.GetPtr() == 0 )
                return true;
            return false;
        }

        bool operator ==( wp<T>& val ) const {
            if( m_ppPtr != 0 && *m_ppPtr == val.GetPtr() )
                return true;
            if( m_ppPtr == 0 && val.GetPtr() == 0 )
                return true;
            return false;
        }

        bool operator ==( const int nul ) const {	// NULL�Ƃ̔�r��p
            if ( m_ppPtr == 0 || *m_ppPtr == 0 )
                return true;
            return false;
        }

        /////////////////
        // !=��r���Z�q
        /////
        bool operator !=( sp<T>& val ) const {
            if( m_ppPtr != 0 && *m_ppPtr != val.GetPtr() )
                return true;
            return false;
        }

        bool operator !=( wp<T>& val ) const {
            if( m_ppPtr != 0 && *m_ppPtr != val.GetPtr() )
                return true;
            return false;
        }

        bool operator !=( const int nul ) const {	// NULL�Ƃ̔�r��p
            if ( m_ppPtr == 0 || *m_ppPtr == 0 )
                return false;
            return true;
        }

        ///////////////////
        // �z��Q�Ɖ��Z�q
        /////
        T& operator[]( int elem ) const {
            return (*m_ppPtr)[ elem ];
        }

        ///////////////////
        // �|�C���^���Z�q
        /////
        T* operator+( int add ) const {
            return ( *m_ppPtr + add );
        }

        ///////////////
        // *�Ԑډ��Z�q
        /////
        T& operator *() const {
            return **m_ppPtr;
        }

        //////////////////////
        // ->�����o�I�����Z�q
        /////
        T* operator ->() const {
            return m_ppPtr ? *m_ppPtr : 0;
        }


    //������ �����o�֐� ����������������������

    public:
        /////////////////////
        // �X�}�[�g�|�C���^�쐬
        /////
        sp<T> GetSmartPtr() {

            sp<T> tmp;
            if ( m_pRefCnt == 0 || *m_pRefCnt == 0 ) {
                return tmp;
            }

            tmp.m_ppPtr = GetPtrPtr();
            tmp.m_pRefCnt = m_pRefCnt;
            tmp.m_pWeakCnt = m_pWeakCnt;
            tmp.m_isAry = m_isAry;

            tmp.AddRef();

            return tmp;
        }

        /////////////////////
        // �N���A
        /////
        void Clear() {
            Release();
            m_pRefCnt = 0;
            m_pWeakCnt = 0;
            m_ppPtr = 0;
            m_NullPtr = 0;
            m_isAry = false;
        }

        /////////////////////
        // �|�C���^�݂̑��o��
        /////
        T* GetPtr() const {
            // �I�u�W�F�N�g�����łɍ폜����Ă���ꍇ��NULL��Ԃ�
            if ( m_pRefCnt == 0 || *m_pRefCnt == 0 )
                return 0;
            return *m_ppPtr;
        }

        T** GetPtrPtr() const {
            return m_ppPtr;
        }

        /////////////////////
        // �l�擾
        /////
        T& At( int elem = 0 ) const {
            return (*m_ppPtr)[ elem ];
        }

        ///////////////////////////////
        // �Q�ƃJ�E���^�ւ̃|�C���^���擾
        /////
        unsigned int* GetRefPtr() const {
            return m_pRefCnt;
        }

        ///////////////////////////////
        // �Q�ƃJ�E���^�����擾
        /////
        unsigned int GetRefNum() const {
            return IsExist() ? *m_pRefCnt : 0;
        }

        ///////////////////////////////
        // �E�B�[�N�J�E���^�ւ̃|�C���^���擾
        /////
        unsigned int* GetWeakCntPtr() const {
            return m_pWeakCnt;
        }

        ///////////////////////////////
        // �E�B�[�N�J�E���^�����擾
        /////
        unsigned int GetWeakNum() const {
            if ( m_pWeakCnt == 0 )
                return 0;
            return *m_pWeakCnt;
        }

       //////////////////////////
       // sp�_�E���L���X�g�R�s�[
       /////
        template <class T2> bool DownCast( sp<T2> &src )
        {
            // ���肪NULL�|�C���^�������ꍇ��
            // �������Ŏ�����NULL�|�C���^�ɂȂ�
            if ( src.GetPtr() == 0 ) {
                Clear();
                return true;
            }

            // �����̃X�}�[�g�|�C���^�̎��|�C���^���A
            // �����̓o�^���Ă���|�C���^��
            // �_�E���L���X�g�\�ȏꍇ�̓_�E���L���X�g�R�s�[�����s
            T* castPtr = dynamic_cast<T*>( src.GetPtr() );

            if( castPtr ) {

                // �_�E���L���X�g����
                // �����͈Ⴄ�l�ɂȂ�̂�
                // �����̃E�B�[�N�J�E���^��1����
                Release();

                // �V�����|�C���^�ƎQ�ƃJ�E���^�����L
                m_ppPtr = (T**)src.GetPtrPtr();
                if ( m_ppPtr )
                    *m_ppPtr = castPtr;
                m_pRefCnt = src.GetRefPtr();
                m_pWeakCnt = src.GetWeakCntPtr();

                m_isAry = src.IsAry();

                // �Q�ƃJ�E���^����
                AddRef();

                return true;
            }

            return false;
        }

       //////////////////////////
       // �_�E���L���X�g�R�s�[
       /////
        template <class T2> bool DownCast( wp<T2> &src )
        {
            // ���肪NULL�|�C���^�������ꍇ��
            // �������Ŏ�����NULL�|�C���^�ɂȂ�
            if ( src.GetPtr() == 0 ) {
                Clear();
                return true;
            }

            // �����̃E�B�[�N�|�C���^�̎��|�C���^���A
            // �����̓o�^���Ă���|�C���^��
            // �_�E���L���X�g�\�ȏꍇ�̓_�E���L���X�g�R�s�[�����s
            T* castPtr = dynamic_cast<T*>( src.GetPtr() );

            if( castPtr ) {

                // �_�E���L���X�g����
                // �����͈Ⴄ�l�ɂȂ�̂�
                // �����̃E�B�[�N�J�E���^��1����
                Release();

                // �V�����|�C���^�ƎQ�ƃJ�E���^�����L
                m_ppPtr = (T**)src.GetPtrPtr();
                *m_ppPtr = castPtr;
                m_pRefCnt = src.GetRefPtr();
                m_pWeakCnt = src.GetWeakCntPtr();

                m_isAry = src.IsAry();

                // �Q�ƃJ�E���^����
                AddRef();

                return true;
            }

            return false;
        }

        ///////////////////////
        // �|�C���^�X���b�v�i�����j
        ///////
        bool SwapPtr( wp<T> &src )
        {
            // �o�����L���|�C���^�ł��鎖��O��ɂ��܂�
            if ( src.IsExist() == 0 || IsExist() == 0 )
                return false;

            // �|�C���^�̌���
            T* pTmp = src.GetPtr();
            *src.m_ppPtr = *m_ppPtr;
            *m_ppPtr = pTmp;

            // �z��t���O�̌���
            bool tmp = src.IsAry();
            src.m_isAry = m_isAry;
            m_isAry = tmp;

            return true;
        }

        ///////////////////////
        // ���̂����݂��Ă�H
        ///////
        bool IsExist() const {
            return (!m_pRefCnt || (*m_pRefCnt == 0)) ? false : true;
        }

        ///////////////////////
        // �z��H
        ///////
        bool IsAry() const {
            return m_isAry;
        }
    };


    template <class T>
    T* wp<T>::m_NullPtr = 0;

} // end namespace Dix


#endif // !defined(AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_)
