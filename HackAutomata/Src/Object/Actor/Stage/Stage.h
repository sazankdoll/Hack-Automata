#pragma once
#include "../ActorBase.h"
class Stage :
    public ActorBase
{
public:
	Stage(void);
	~Stage(void) = default;
	void Load(void) override;
	void Update(void) override;
	void Draw(void) override;

protected:
	

private:


};

