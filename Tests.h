#pragma once

#include "AutoBreak.h"
#include <stdexcept>

constexpr void CheckBoolExpression(bool expression, const char* msg)
{
	if (!expression)
		throw std::runtime_error(msg);
}

void TestSpeed()
{
	MockServiceBus bus;
	AutoBrake auto_brake(bus);
	CheckBoolExpression(auto_brake.get_speed_mps() == 0, "speed isn't zero");
}

void TestCollision()
{
	MockServiceBus bus;
	AutoBrake auto_brake(bus);
	CheckBoolExpression(auto_brake.get_collision_threshold_s() == 5, "collision isn't 5");
}

void TestCollisionLess()
{
	MockServiceBus bus;
	AutoBrake auto_brake(bus);
	auto_brake.set_collision_threshold_s(2);
}

void SpeedIsSaved()
{
	MockServiceBus bus;
	AutoBrake auto_brake(bus);
	
	bus.speed_update_callback(SpeedUpdate{ 100 });
	CheckBoolExpression(100 == auto_brake.get_speed_mps(), "speed isn't saved to 100");

	bus.speed_update_callback(SpeedUpdate{ 50 });
	CheckBoolExpression(50 == auto_brake.get_speed_mps(), "speed isn't saved to 50");

	bus.speed_update_callback(SpeedUpdate{ 0 });
	CheckBoolExpression(0 == auto_brake.get_speed_mps(), "speed isn't saved to 0");
}

void AlertWhenImminent()
{
	MockServiceBus bus;
	AutoBrake auto_brake(bus);
	
	auto_brake.set_collision_threshold_s(10);
	bus.speed_update_callback(SpeedUpdate{100});
	bus.car_detected_callback(CarDetected{ 100, 0 });
	CheckBoolExpression(bus.commands_published == 1, "brake commands published not one");

	CheckBoolExpression(bus.last_command.time_to_collision_s == 1,
		"time to collision not computed correctly.");
}
