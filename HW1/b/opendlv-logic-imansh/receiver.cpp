#include <chrono>
#include <iostream>

#include "cluon-complete.hpp"
#include "messages.hpp"


int32_t main(int32_t , char **)
{
	cluon::OD4Session od4(132,[&od4](cluon::data::Envelope &&envelope) noexcept
	{		
		if(envelope.dataType() == 1091)
		{
			opendlv::proxy::GroundSpeedRequest receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSpeedRequest>(std::move(envelope));
			float val = receivedMsg.groundSpeed() * 7.0;
			opendlv::proxy::GroundSpeedReading msg;
			msg.groundSpeed(val);
			od4.send(msg);
		}
	});
	while(true){}
	return 0;
}
