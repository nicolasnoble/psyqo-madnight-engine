#include "controller.hh"
#include "../madnight.hh"

void ControllerHelper::init(void) {
  // try and force our controller into analog mode
}

int ControllerHelper::GetNormalizedAnalogStickInput(psyqo::AdvancedPad::Pad pad, uint8_t analog_index) {
  if (!IsPadAnalog(pad))
    return 0;

  auto val = static_cast<int>(g_madnightEngine.m_input.getAdc(pad, analog_index) - 0x80);

  // a centred stick rarely reads exactly 0x80, so drop anything inside the deadzone
  const auto isYAxis = analog_index == LeftStickY || analog_index == RightStickY;
  const int deadzone = isYAxis ? ANALOG_STICK_DEADZONE_Y : ANALOG_STICK_DEADZONE_X;
  if (val > -deadzone && val < deadzone)
    return 0;

  return isYAxis ? -val : val; // normalize y axis so that a positive value is up on the stick
}

bool ControllerHelper::IsPadAnalog(psyqo::AdvancedPad::Pad pad) {
  return g_madnightEngine.m_input.getPadType(pad) == psyqo::AdvancedPad::PadType::AnalogPad;
}
