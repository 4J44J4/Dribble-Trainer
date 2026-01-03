#include "pch.h"
#include "DribbleTrainer.h"
#include "ImGui/imgui_internal.h"
#include "wtypes.h"

int calibrationTimer = 65;
int resetDistance = 1400;

// settings menu
void DribbleTrainer::RenderSettings()
{
	ImGui::TextUnformatted("To use the plugin, go to the bindings tab, and set binds for the commands 'DribbleTrainer::on_off', and 'DribbleTrainer::reset_ball'.");
	ImGui::TextUnformatted("The first turns the plugin on and off, and the second resets the plugin to the starting position.");
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SliderInt("Calibration", &calibrationTimer, 0, 360);
	ImGui::TextUnformatted(" ^ Controls how long the ball will match the player's movement when the ball gets reset above the player's car (120 = 1 second).");
	ImGui::NewLine();
	ImGui::SliderInt("Reset Distance", &resetDistance, 100, 3000);
	ImGui::TextUnformatted(" ^ Controls how far away the ball must be from the car to be auto-reset.");
}

int DribbleTrainer::CalibrationSetting()
{
	return calibrationTimer;
}

int DribbleTrainer::ResetDistanceSetting()
{
	return resetDistance;
}