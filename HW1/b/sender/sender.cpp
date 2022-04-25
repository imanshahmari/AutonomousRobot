#include <chrono>
#include <iostream>

#include "cluon-complete.hpp"
#include "messages.hpp"

int32_t main(int32_t, char **)
{	
	cluon::OD4Session od4(132,[&od4](cluon::data::Envelope &&envelope) noexcept
	{		
		if(envelope.dataType() == 1046)
		{
			opendlv::proxy::GroundSpeedReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSpeedReading>(std::move(envelope));
			std::cout<<"Received number is "<< receivedMsg.groundSpeed() << std::endl;
		}
	});

	while(true)
	{
		float value;
		std::cout << "Enter a number to check: " << std::endl;
		std::cin >> value;
		opendlv::proxy::GroundSpeedRequest msg;
		msg.groundSpeed(value);
		od4.send(msg);
	}

	return 0;
}
