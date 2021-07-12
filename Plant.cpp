#include "Plant.h"


namespace organisms
{
	void Plant::action()
	{
	}


	void Plant::collision()
	{
		bool alreadyTaken = false;
		int defender = -1;
		int ataccker = -1;
		for (int i = 0; i < (int)this->world->getAllOrganisms().size(); i++)
		{
			if (this == this->world->getAllOrganisms()[i])
			{
				ataccker = i;
			}
			else if (this->location.x == this->world->getAllOrganisms()[i]->getLocation().x && 
				this->location.y == this->world->getAllOrganisms()[i]->getLocation().y)
			{
				defender = i;
				alreadyTaken = true;
			}
		}
		if (alreadyTaken)
		{
			std::cout << this->world->getAllOrganisms()[defender]->getName() << " ate " << this->name << std::endl;
			if (this->name == "WolfBerries")
				this->world->getAllOrganisms().erase(this->world->getAllOrganisms().begin() + defender);
			this->world->getAllOrganisms().erase(this->world->getAllOrganisms().begin() + ataccker);
		}
	}
}
