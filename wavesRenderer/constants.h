#pragma once
unsigned int SCREEN_WIDTH = 800;
unsigned int SCREEN_HEIGHT = 450;
float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
const float FRAME_RATE = 1.f / 60.0f; // seconds (60 Hz)
//const float STAGE_WIDTH = 128.f; // meters
const float STAGE_WIDTH = 128.f; // meters
const float STAGE_HEIGHT = 72.f; // meters
const float SEA_HEIGHT = STAGE_HEIGHT * 0.20f;