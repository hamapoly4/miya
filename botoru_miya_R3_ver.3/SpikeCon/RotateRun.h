#ifndef ___CLASS_ROTATERUN_R
#define ___CLASS_ROTATERUN_R	// インクルードカード

#include "abstract_run.h"

class RotateRun : public Run {
private:
	enum Rota { RIGHT, LEFT, };
	unsigned char mrota;

public:
	RotateRun(unsigned char rota, int pwm = 60);
	~RotateRun();

	void run();
};

#endif // ___CLASS_ROTATERUN
