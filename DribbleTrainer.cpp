#include "pch.h"
#include "DribbleTrainer.h"


BAKKESMOD_PLUGIN(DribbleTrainer, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

bool activate = false;
int count = -1;
int resetTimer;

void DribbleTrainer::onLoad()
{
	_globalCvarManager = cvarManager;

	// on/off button
	cvarManager->registerNotifier("DribbleTrainer::on_off", [this](std::vector<std::string> args) {
		if (!activate)
		{
			activate = true;
			count = 20;
		}
		else
			activate = false;
		}, "", PERMISSION_ALL);

	// reset button
	cvarManager->registerNotifier("DribbleTrainer::reset_ball", [this](std::vector<std::string> args) {
		if (activate)
			ManualReset();
		}, "", PERMISSION_ALL);

	this->loadHooks();
}

void DribbleTrainer::InitialSetup()
{
	// null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from controller, deactivating dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from controller, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from controller, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from controller, deactivating dribble trainer");
			activate = false;
			return;
		}
	}

	// set ball and car
	car.SetLocation({ 0, -400, car.GetLocation().Z });
	ball.SetLocation({ 0, 0, ball.GetLocation().Z });
	car.SetRotation({ 0, 16384, 0 });
	car.SetVelocity({ 0, 0 ,0 });
	ball.SetVelocity({ 0, 0, 0 });
	car.SetAngularVelocity({ 0, 0, 0 }, false);
	ball.SetAngularVelocity({ 0, 0, 0 }, false);
}

void DribbleTrainer::Controller()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from controller, deactivating dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from controller, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from controller, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from controller, deactivating dribble trainer");
			activate = false;
			return;
		}
	}

	// reset if ball is too far away from car
	if ((abs(abs(car.GetLocation().X) - abs(ball.GetLocation().X)) + abs(abs(car.GetLocation().Y) - abs(ball.GetLocation().Y)) > ResetDistanceSetting()))
		ResetBall();

	// move car and ball to opposite side of field if about to hit a wall
	if (car.GetLocation().Y > 4200 || ball.GetLocation().Y > 4200)
		FrontReset();
	if (car.GetLocation().Y < -4200 || ball.GetLocation().Y < -4200)
		BackReset();
	if (car.GetLocation().X > 3100 || ball.GetLocation().X > 3100)
		LeftReset();
	if (car.GetLocation().X < -3100 || ball.GetLocation().X < -3100)
		RightReset();

}

void DribbleTrainer::FrontReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from FrontReset, deactivating dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from FrontReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from FrontReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from FrontReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}

	// set ball and car
	car.SetLocation(Vector{ car.GetLocation().X, car.GetLocation().Y - 7000, car.GetLocation().Z });
	ball.SetLocation(Vector{ ball.GetLocation().X, ball.GetLocation().Y - 7000, ball.GetLocation().Z });
}

void DribbleTrainer::BackReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from BackReset, deactivating dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from BackReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from BackReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from BackReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	
	// set ball and car
	car.SetLocation(Vector{ car.GetLocation().X, car.GetLocation().Y + 7000, car.GetLocation().Z });
	ball.SetLocation(Vector{ ball.GetLocation().X, ball.GetLocation().Y + 7000, ball.GetLocation().Z });
}

void DribbleTrainer::LeftReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from LeftReset, deactivating dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from LeftReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from LeftReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from LeftReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}

	// set ball and car
	car.SetLocation(Vector{ car.GetLocation().X - 5000, car.GetLocation().Y, car.GetLocation().Z });
	ball.SetLocation(Vector{ ball.GetLocation().X - 5000, ball.GetLocation().Y, ball.GetLocation().Z });
}

void DribbleTrainer::RightReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from RightReset, deactivating dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from RightReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from RightReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from RightReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}

	// set ball and car
	car.SetLocation(Vector{ car.GetLocation().X + 5000, car.GetLocation().Y, car.GetLocation().Z });
	ball.SetLocation(Vector{ ball.GetLocation().X + 5000, ball.GetLocation().Y, ball.GetLocation().Z });
}

void DribbleTrainer::ResetBall()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from RightReset, deactivating dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from RightReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from RightReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from RightReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}

	// reset ball and car
	car.SetLocation({ car.GetLocation().X, car.GetLocation().Y, 19.0f });
	ball.SetLocation(Vector{ car.GetLocation().X + float(car.GetVelocity().X / 100.0), car.GetLocation().Y + float(car.GetVelocity().Y / 100.0), ball.GetRadius() * 2.0f});
	ball.SetVelocity(car.GetVelocity());
	if (abs(abs(car.GetVelocity().X) + abs(car.GetVelocity().Y)) > 2000)
	{ // slow down ball and car if going fast
		car.SetVelocity({ float(car.GetVelocity().X / 1.5), float(car.GetVelocity().Y / 1.5), 0.0f });
		ball.SetVelocity({ float(ball.GetVelocity().X / 1.5), float(ball.GetVelocity().Y / 1.5), 0.0f });
	}
	else
	{ // don't slow down if not going fast
		car.SetVelocity(Vector{ car.GetVelocity().X, car.GetVelocity().Y, 0.0f });
		ball.SetVelocity(Vector{ ball.GetVelocity().X, ball.GetVelocity().Y, 0.0f });
	}
	car.SetAngularVelocity({ 0.0f, 0.0f, 0.0f }, false);
	ball.SetAngularVelocity({ 0.0f, 0.0f, 0.0f, }, false);
	car.SetRotation({ 0, int(std::atan2(car.GetVelocity().Y, car.GetVelocity().X) * 180 / 3.14159 * 182.0444444), 0 });
	resetTimer = CalibrationSetting();
}

void DribbleTrainer::ManualReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from ManualReset, deactivating dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from ManualReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from ManualReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from ManualReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}

	// set position of ball and car
	car.SetLocation({ 0, -400, 19.0f });
	ball.SetLocation({ 0, 0, ball.GetRadius() });
	car.SetRotation({ 0, 16384, 0 });
	car.SetVelocity({ 0, 0 ,0 });
	ball.SetVelocity({ 0, 0, 0 });
	car.SetAngularVelocity({ 0, 0, 0 }, false);
	ball.SetAngularVelocity({ 0, 0, 0 }, false);
}

void DribbleTrainer::ResetCalibration()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from RightReset, deactivating dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from RightReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from RightReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from RightReset, deactivating dribble trainer");
			activate = false;
			return;
		}
	}

	ball.SetVelocity(car.GetVelocity());
}

void DribbleTrainer::loadHooks()
{
	gameWrapper->HookEvent("Function TAGame.EngineShare_TA.EventPostPhysicsStep",
		[this](std::string eventName) {
			if (activate)
			{
				if (count > 0)
					InitialSetup();
				if (count == 0)
					ManualReset();
				if (count > -1)
					count--;
				if (count == -1)
					Controller();
				if (resetTimer > 0)
				{
					ResetCalibration();
					resetTimer--;
				}
			}
		});

	// deactivate plugin if freeplay is reset
	gameWrapper->HookEvent("Function TAGame.FreeplayCommands_TA.ResetTraining",
		[this](std::string eventName) {
			activate = false;
		});
}
