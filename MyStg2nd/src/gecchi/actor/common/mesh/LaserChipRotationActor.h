#ifndef LASERCHIPROTATIONACTOR_H_
#define LASERCHIPROTATIONACTOR_H_
namespace MyStg2nd {

class LaserChipRotationActor : public GgafDx9LibStg::RotationActor {

public:
    int _num_chip_max;
    int _num_chip_active;
    bool _is_tear_laser;
    LaserChip* _pChip_prev_obtain;
    DWORD _lifeframe_prev_obtain;
    int _num_continual_obtain_count;

    GgafDx9Core::GgafDx9SeConnection* _pSeCon_Laser;


	LaserChipRotationActor(const char* prm_name);

	virtual void processBehavior();

	virtual void processFinal();
	virtual LaserChip* obtain();
	void addLaserChip(LaserChip* prm_pLaserChip);

 	virtual ~LaserChipRotationActor();

};

}
#endif /*LASERCHIPROTATIONACTOR_H_*/
