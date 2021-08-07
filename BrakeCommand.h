#pragma once

//in case of collision, publish Brake_command to service bus
struct BrakeCommand
{
	double time_to_collision_s;
};