#ifndef MYLASERCHIPROTATIONACTOR_H_
#define MYLASERCHIPROTATIONACTOR_H_
namespace MyStg2nd {

class MyLaserChipRotationActor : public GgafDx9LibStg::RotationActor {

public:
    int _num_chip_max;
    int _num_chip_active;
    bool _is_tear_laser;
    MyLaserChip* _pHeadChip;
    MyLaserChip* _pChip_prev_obtain;
    DWORD _lifeframe_prev_obtain;
    int _num_continual_obtain_count;

    GgafDx9Core::GgafDx9SeConnection* _pSeCon_Laser;


	MyLaserChipRotationActor(const char* prm_name);

	virtual void processBehavior();

	virtual void processFinal();
	virtual MyLaserChip* obtain();

 	virtual ~MyLaserChipRotationActor();

};

}
#endif /*MYLASERCHIPROTATIONACTOR_H_*/
