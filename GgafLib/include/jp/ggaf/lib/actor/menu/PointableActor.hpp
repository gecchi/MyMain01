#ifndef GGAF_LIB_POINTABLEACTOR_H_
#define GGAF_LIB_POINTABLEACTOR_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/core/util/LinkedListRing.hpp"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"
#include "jp/ggaf/lib/actor/DefaultFramedBoardActor.h"
#include "jp/ggaf/lib/actor/menu/PointableActor.hpp"
#include "jp/ggaf/lib/actor/FontBoardActor.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"


namespace GgafLib {

/**
 * �}�E�X�Ń|�C���g�\�ȃA�N�^�[ .
 * @tparam T ��̂̃��j���[�ƂȂ�A�N�^�[�̌^
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class PointableActor : public T {

protected:
    /**
     * �R���X�g���N�^ .
     * �y���Ӂz��������񊈓���Ԃ��f�t�H���g�Ƃ��Ă��܂��B<BR>
     * ��̓I�ɂ� T::inactivateImmed(); ���R�[�����Ă��܂��B
     * @param prm_name
     * @param prm_model ���f�����ʖ�
     */
    PointableActor(const char* prm_name, const char* prm_model);


    /**
     * ��ԃt���O�X�V��ǉ��̂��߃I�[�o�[���C�h .
     * ������ T::nextFrame(); ���R�[�����Ă��܂��B
     */
    virtual void nextFrame() override;


    /**
     * ���j���[�̐U�镑�� .
     * �J�[�\���̈ړ��y�сA���j���[�A�C�e���ƃJ�[�\�������j���[�̕�̍��W�ɒǏ]������
     * �����������ς݂ł��B<BR>
     * ���j���[�̐U�镑����ǉ�����ꍇ�́A�I�[�o�[���C�h���āA
     * �������ɏ�� processBehavior() ���Ăяo���̂�Y��Ȃ��悤�ɁB<BR>
     */
    virtual void processBehavior() override;

    virtual ~PointableActor();
};


template<class T>
PointableActor<T>::PointableActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model) {
    T::_class_name = "PointableActor";
}

template<class T>
void PointableActor<T>::nextFrame() {
    T::nextFrame();
}

template<class T>
void PointableActor<T>::processBehavior() {

}


template<class T>
PointableActor<T>::~PointableActor() {
}

}
#endif /*GGAF_LIB_MENUACTOR_H_*/
