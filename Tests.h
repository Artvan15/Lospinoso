#pragma once

#include "AutoBreak.h"
#include <stdexcept>
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

constexpr void CheckBoolExpression(bool expression, const char* msg)
{
	if (!expression)
		throw std::runtime_error(msg);
}

/* REQUIRE - Test ends immediately, if assert fail
 * CHECK - Test continue to execute
 * REQUIRE_THROWS - exception has to be thrown
 * REQUIRE_THROWS_AS - second param is type of exception that has to be thrown
 * REQUIRE_NOTHROW - no exception has to be thrown
 * Catch::Approx - used to compare float values
 * FAIL - leads to fail test
 * SECTION - separate test in TEST_CASE. Insert former instructions into
 *	every SECTION
 */

TEST_CASE("AutoBrake")
{
	MockServiceBus bus;
	AutoBrake auto_brake(bus);

	SECTION("initializes speed to zero")
	{
		REQUIRE(auto_brake.get_speed_mps() == Catch::Approx(0));
	}

	SECTION("initializes sensitivity to five")
	{
		REQUIRE(auto_brake.get_collision_threshold_s() == Catch::Approx(5));
	}

	SECTION("throws when sensitivity less than one")
	{
		REQUIRE_THROWS(auto_brake.set_collision_threshold_s(0.5));
	}

	SECTION("saves speed after update")
	{
		bus.speed_update_callback(SpeedUpdate{ 100 });
		REQUIRE(100 == auto_brake.get_speed_mps());
		bus.speed_update_callback(SpeedUpdate{ 50 });
		REQUIRE(50 == auto_brake.get_speed_mps());
		bus.speed_update_callback(SpeedUpdate{ 0 });
		REQUIRE(auto_brake.get_speed_mps() == 0);
	}

	SECTION("no alert when not imminent")
	{
		auto_brake.set_collision_threshold_s(2);
		bus.speed_update_callback(SpeedUpdate{ 100 });
		bus.car_detected_callback(CarDetected{ 1000, 50 });
		REQUIRE(bus.commands_published == 0);
	}

	SECTION("alert when imminent")
	{
		auto_brake.set_collision_threshold_s(10);
		bus.speed_update_callback(SpeedUpdate{ 100 });
		bus.car_detected_callback(CarDetected{ 100, 0 });
		REQUIRE(bus.commands_published == 1);
		REQUIRE(bus.last_command.time_to_collision_s == Catch::Approx(1));
	}

	
}