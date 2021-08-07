#pragma once

#include "SpeedUpdate.h"
#include "CarDetected.h"
#include "BrakeCommand.h"
#include "ServiceBus.h"

#include <stdexcept>

struct AutoBrake
{
	AutoBrake(IServiceBus& bus)
		: collision_threshold_s(5),
		  speed_mps(0)
	{
		bus.subscribe([this](const SpeedUpdate& speed_update)
			{
				speed_mps = speed_update.velocity_mps;
			});

		bus.subscribe([this, &bus](const CarDetected& car_detected)
			{
				const double relative_speed = speed_mps - car_detected.velocity_mps;
				if (relative_speed <= 0) return;

				const double time_collision = car_detected.distance_m / relative_speed;
				if (time_collision > collision_threshold_s) return;

				bus.publish(BrakeCommand{ time_collision });

			});
	}
	
	void set_collision_threshold_s(double x)
	{
		if (x < 1)
		{
			throw std::invalid_argument("collision is less than 1");
		}
		collision_threshold_s = x;
	}
	double get_collision_threshold_s() const
	{
		return collision_threshold_s;
	}
	double get_speed_mps() const
	{
		return speed_mps;
	}
private:
	double collision_threshold_s;
	double speed_mps;
};
//AutoBrake наблюдает за событиями SpeedUpdate и CarDetected на служебной шине
//save reference to 'publish' method in ServiceBus class
