#pragma once
#include "BrakeCommand.h"
#include "SpeedUpdate.h"
#include "CarDetected.h"

#include <functional>

using SpeedUpdateCallback = std::function<void(const SpeedUpdate&)>;
using CarDetectedCallback = std::function<void(const CarDetected&)>;

struct IServiceBus
{
	virtual void publish(const BrakeCommand&) = 0;
	virtual void subscribe(SpeedUpdateCallback) = 0;
	virtual void subscribe(CarDetectedCallback) = 0;
	virtual ~IServiceBus() = default;
};

//mock - имитация
struct MockServiceBus : IServiceBus
{
	void publish(const BrakeCommand& cmd) override
	{
		++commands_published;
		last_command = cmd;
	}
	void subscribe(SpeedUpdateCallback callback) override
	{
		speed_update_callback = callback;
	}
	void subscribe(CarDetectedCallback callback) override
	{
		car_detected_callback = callback;
	}

	BrakeCommand last_command{ 0 };
	int commands_published{ 0 };
	SpeedUpdateCallback speed_update_callback;
	CarDetectedCallback car_detected_callback;
};



//служебная шина
struct ServiceBus : public IServiceBus
{
	void publish(const BrakeCommand&) override;
};