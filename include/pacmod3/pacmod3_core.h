#ifndef PACMOD3_PACMOD3_CORE_H
#define PACMOD3_PACMOD3_CORE_H

/*
* Unpublished Copyright (c) 2009-2019 AutonomouStuff, LLC, All Rights Reserved.
*
* This file is part of the PACMod v3 ROS driver which is released under the MIT license.
* See file LICENSE included with this software or go to https://opensource.org/licenses/MIT for full license details.
*/

#include <cstring>
#include <sstream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>

namespace AS
{
namespace Drivers
{
namespace PACMod3
{
enum VehicleType
{
  POLARIS_GEM,
  POLARIS_RANGER,
  INTERNATIONAL_PROSTAR_122,
  LEXUS_RX_450H,
  FREIGHTLINER_CASCADIA,
  VEHICLE_4,
  VEHICLE_5,
  VEHICLE_6,
  JUPITER_SPIRIT
};

enum DimLevel
{
  DIM_LEVEL_MIN = 0,
  DIM_LEVEL_1 = 1,
  DIM_LEVEL_2 = 2,
  DIM_LEVEL_3 = 3,
  DIM_LEVEL_4 = 4,
  DIM_LEVEL_5 = 5,
  DIM_LEVEL_6 = 6,
  DIM_LEVEL_7 = 7,
  DIM_LEVEL_8 = 8,
  DIM_LEVEL_9 = 9,
  DIM_LEVEL_10 = 10,
  DIM_LEVEL_11 = 11,
  DIM_LEVEL_MAX = 12
};

enum ComponentType
{
  COMPONENT_TYPE_PACMOD = 0,
  COMPONENT_TYPE_PACMINI = 1,
  COMPONENT_TYPE_PACMICRO = 2
};

enum ComponentFunction
{
  COMPONENT_FUNC_PACMOD = 0,
  COMPONENT_FUNC_STEERING_AND_STEERING_COLUMN = 1,
  COMPONENT_FUNC_ACCELERATOR_AND_BRAKING = 2,
  COMPONENT_FUNC_BRAKING = 3,
  COMPONENT_FUNC_SHIFTING = 4,
  COMPONENT_FUNC_STEERING = 5,
  COMPONENT_FUNC_E_SHIFTER = 6,
  COMPONENT_FUNC_WATCHDOG = 7
};

class Pacmod3TxMsg
{
public:
  static std::shared_ptr<Pacmod3TxMsg> make_message(const uint32_t& can_id);
  virtual void parse(uint8_t *in) = 0;
  virtual bool isSystem();
};

class SystemRptMsg :
  public Pacmod3TxMsg
{
public:
  SystemRptMsg();

  bool isSystem();

  bool enabled;
  bool override_active;
  bool command_output_fault;
  bool input_output_fault;
  bool output_reported_fault;
  bool pacmod_fault;
  bool vehicle_fault;
};

class SystemRptBoolMsg :
  public SystemRptMsg
{
public:
  SystemRptBoolMsg();

  bool manual_input;
  bool command;
  bool output;

  void parse(uint8_t *in);
};

class SystemRptIntMsg :
  public SystemRptMsg
{
public:
  SystemRptIntMsg();

  uint8_t manual_input;
  uint8_t command;
  uint8_t output;

  void parse(uint8_t *in);
};

class SystemRptFloatMsg :
  public SystemRptMsg
{
public:
  SystemRptFloatMsg();

  double manual_input;
  double command;
  double output;

  void parse(uint8_t *in);
};

// TX Messages
class GlobalRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x10;

  bool enabled;
  bool override_active;
  bool fault_active;
  bool config_fault_active;
  bool user_can_timeout;
  bool steering_can_timeout;
  bool brake_can_timeout;
  bool subsystem_can_timeout;
  bool vehicle_can_timeout;
  uint16_t user_can_read_errors;

  void parse(uint8_t *in);
};

class ComponentRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x20;

  ComponentType component_type;
  ComponentFunction component_func;
  uint8_t counter;
  uint8_t complement;
  bool config_fault;

  void parse(uint8_t *in);
};

// System Reports
class AccelRptMsg :
  public SystemRptFloatMsg
{
public:
  static const uint32_t CAN_ID = 0x200;
};

class BrakeRptMsg :
  public SystemRptFloatMsg
{
public:
  static const uint32_t CAN_ID = 0x204;
};

class CruiseControlButtonsRptMsg :
  public SystemRptIntMsg
{
public:
  static const uint32_t CAN_ID = 0x208;
};

class DashControlsLeftRptMsg :
  public SystemRptIntMsg
{
public:
  static const uint32_t CAN_ID = 0x20C;
};

class DashControlsRightRptMsg :
  public SystemRptIntMsg
{
public:
  static const uint32_t CAN_ID = 0x210;
};

class EngineBrakeRptMsg :
  public SystemRptIntMsg
{
  public:
    static const uint32_t CAN_ID;
};

class HazardLightRptMsg :
  public SystemRptBoolMsg
{
public:
  static const uint32_t CAN_ID = 0x214;
};

class HeadlightRptMsg :
  public SystemRptIntMsg
{
public:
  static const uint32_t CAN_ID = 0x218;
};

class HornRptMsg :
  public SystemRptBoolMsg
{
public:
  static const uint32_t CAN_ID = 0x21C;
};

class MarkerLampRptMsg :
  public SystemRptBoolMsg
{
  public:
    static const uint32_t CAN_ID;
};

class MediaControlsRptMsg :
  public SystemRptIntMsg
{
public:
  static const uint32_t CAN_ID = 0x220;
};

class ParkingBrakeRptMsg :
  public SystemRptBoolMsg
{
public:
  static const uint32_t CAN_ID = 0x224;
};

class ShiftRptMsg :
  public SystemRptIntMsg
{
public:
  static const uint32_t CAN_ID = 0x228;
};

class SprayerRptMsg :
  public SystemRptBoolMsg
{
public:
  static const uint32_t CAN_ID;
};

class SteerRptMsg :
  public SystemRptFloatMsg
{
public:
  static const uint32_t CAN_ID = 0x22C;
};

class TurnSignalRptMsg :
  public SystemRptIntMsg
{
public:
  static const uint32_t CAN_ID = 0x230;
};

class RearPassDoorRptMsg :
  public SystemRptIntMsg
{
public:
  static const uint32_t CAN_ID = 0x240;
};
class WiperRptMsg :
  public SystemRptIntMsg
{
public:
  static const uint32_t CAN_ID = 0x234;
};

// System Aux Reports
class AccelAuxRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x300;

  float raw_pedal_pos;
  float raw_pedal_force;
  bool user_interaction;
  bool raw_pedal_pos_is_valid;
  bool raw_pedal_force_is_valid;
  bool user_interaction_is_valid;

  void parse(uint8_t *in);
};

class BrakeAuxRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x304;

  float raw_pedal_pos;
  float raw_pedal_force;
  float raw_brake_pressure;
  bool user_interaction;
  bool brake_on_off;
  bool raw_pedal_pos_is_valid;
  bool raw_pedal_force_is_valid;
  bool raw_brake_pressure_is_valid;
  bool user_interaction_is_valid;
  bool brake_on_off_is_valid;

  void parse(uint8_t *in);
};

class HeadlightAuxRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x318;

  bool headlights_on;
  bool headlights_on_bright;
  bool fog_lights_on;
  uint8_t headlights_mode;
  bool headlights_on_is_valid;
  bool headlights_on_bright_is_valid;
  bool fog_lights_on_is_valid;
  bool headlights_mode_is_valid;

  void parse(uint8_t *in);
};

class ShiftAuxRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x328;

  bool between_gears;
  bool stay_in_neutral_mode;
  bool brake_interlock_active;
  bool speed_interlock_active;
  bool between_gears_is_valid;
  bool stay_in_neutral_mode_is_valid;
  bool brake_interlock_active_is_valid;
  bool speed_interlock_active_is_valid;

  void parse(uint8_t *in);
};

class SteerAuxRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x32C;

  float raw_position;
  float raw_torque;
  float rotation_rate;
  bool user_interaction;
  bool raw_position_is_valid;
  bool raw_torque_is_valid;
  bool rotation_rate_is_valid;
  bool user_interaction_is_valid;

  void parse(uint8_t *in);
};

class TurnAuxRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x330;

  bool driver_blinker_bulb_on;
  bool passenger_blinker_bulb_on;
  bool driver_blinker_bulb_on_is_valid;
  bool passenger_blinker_bulb_on_is_valid;

  void parse(uint8_t *in);
};

class WiperAuxRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x334;

  bool front_wiping;
  bool front_spraying;
  bool rear_wiping;
  bool rear_spraying;
  bool spray_near_empty;
  bool spray_empty;
  bool front_wiping_is_valid;
  bool front_spraying_is_valid;
  bool rear_wiping_is_valid;
  bool rear_spraying_is_valid;
  bool spray_near_empty_is_valid;
  bool spray_empty_is_valid;

  void parse(uint8_t *in);
};

// Other Reports
class RearLightsRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x418;

  bool brake_lights_on;
  bool brake_lights_on_is_valid;
  bool reverse_lights_on;
  bool reverse_lights_on_is_valid;

  void parse(uint8_t *in);
};

class InteriorLightsRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x416;

  bool front_dome_lights_on;
  bool front_dome_lights_on_is_valid;
  bool rear_dome_lights_on;
  bool rear_dome_lights_on_is_valid;
  bool mood_lights_on;
  bool mood_lights_on_is_valid;
  DimLevel dim_level;
  bool dim_level_is_valid;

  void parse(uint8_t *in);
};

class OccupancyRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x415;

  bool driver_seat_occupied;
  bool driver_seat_occupied_is_valid;
  bool passenger_seat_occupied;
  bool passenger_seat_occupied_is_valid;
  bool rear_seat_occupied;
  bool rear_seat_occupied_is_valid;
  bool driver_seatbelt_buckled;
  bool driver_seatbelt_buckled_is_valid;
  bool passenger_seatbelt_buckled;
  bool passenger_seatbelt_buckled_is_valid;
  bool rear_seatbelt_buckled;
  bool rear_seatbelt_buckled_is_valid;

  void parse(uint8_t *in);
};

class MotorRpt1Msg :
  public Pacmod3TxMsg
{
public:
  double current;
  double position;

  void parse(uint8_t *in);
};

class MotorRpt2Msg :
  public Pacmod3TxMsg
{
public:
  double encoder_temp;
  double motor_temp;
  double velocity;

  void parse(uint8_t *in);
};

class MotorRpt3Msg :
  public Pacmod3TxMsg
{
public:
  double torque_output;
  double torque_input;

  void parse(uint8_t *in);
};

class BrakeMotorRpt1Msg :
  public MotorRpt1Msg
{
public:
  static const uint32_t CAN_ID = 0x401;
};

class BrakeMotorRpt2Msg :
  public MotorRpt2Msg
{
public:
  static const uint32_t CAN_ID = 0x402;
};

class BrakeMotorRpt3Msg :
  public MotorRpt3Msg
{
public:
  static const uint32_t CAN_ID = 0x403;
};

class DateTimeRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x40F;

  uint32_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;

  void parse(uint8_t *in);
};

class DoorRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x417;

  bool driver_door_open;
  bool driver_door_open_is_valid;
  bool passenger_door_open;
  bool passenger_door_open_is_valid;
  bool rear_driver_door_open;
  bool rear_driver_door_open_is_valid;
  bool rear_passenger_door_open;
  bool rear_passenger_door_open_is_valid;
  bool hood_open;
  bool hood_open_is_valid;
  bool trunk_open;
  bool trunk_open_is_valid;
  bool fuel_door_open;
  bool fuel_door_open_is_valid;

  void parse(uint8_t *in);
};

class LatLonHeadingRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x40E;

  int latitude_degrees;
  uint32_t latitude_minutes;
  uint32_t latitude_seconds;
  int longitude_degrees;
  uint32_t longitude_minutes;
  uint32_t longitude_seconds;
  double heading;

  void parse(uint8_t *in);
};

class SteeringPIDRpt1Msg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x408;

  double dt;
  double Kp;
  double Ki;
  double Kd;

  void parse(uint8_t *in);
};

class SteeringPIDRpt2Msg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x409;

  double P_term;
  double I_term;
  double D_term;
  double all_terms;

  void parse(uint8_t *in);
};

class SteeringPIDRpt3Msg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x40A;

  double new_torque;
  double str_angle_desired;
  double str_angle_actual;
  double error;

  void parse(uint8_t *in);
};

class SteeringPIDRpt4Msg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x410;

  double angular_velocity;
  double angular_acceleration;

  void parse(uint8_t *in);
};

class SteerMotorRpt1Msg :
  public MotorRpt1Msg
{
public:
  static const uint32_t CAN_ID = 0x404;
};

class SteerMotorRpt2Msg :
  public MotorRpt2Msg
{
public:
  static const uint32_t CAN_ID = 0x405;
};

class SteerMotorRpt3Msg :
  public MotorRpt3Msg
{
public:
  static const uint32_t CAN_ID = 0x406;
};

class VehicleSpeedRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x400;

  double vehicle_speed;
  bool vehicle_speed_valid;
  uint8_t vehicle_speed_raw[2];

  void parse(uint8_t *in);
};

class VinRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x414;

  std::string mfg_code;
  std::string mfg;
  char model_year_code;
  uint32_t model_year;
  uint32_t serial;

  void parse(uint8_t *in);
};

class YawRateRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x40D;

  double yaw_rate;

  void parse(uint8_t *in);
};

class WheelSpeedRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x407;

  double front_left_wheel_speed;
  double front_right_wheel_speed;
  double rear_left_wheel_speed;
  double rear_right_wheel_speed;

  void parse(uint8_t *in);
};

class DetectedObjectRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x411;

  double front_object_distance_low_res;
  double front_object_distance_high_res;

  void parse(uint8_t *in);
};

class VehicleSpecificRpt1Msg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x412;

  uint8_t shift_pos_1;
  uint8_t shift_pos_2;

  void parse(uint8_t *in);
};

class VehicleDynamicsRptMsg :
  public Pacmod3TxMsg
{
public:
  static const uint32_t CAN_ID = 0x413;

  uint8_t g_forces;
  double brake_torque;

  void parse(uint8_t *in);
};

// RX Messages
class Pacmod3RxMsg
{
public:
  std::vector<uint8_t> data;
};

class SystemCmdBool :
  public Pacmod3RxMsg
{
public:
  static constexpr uint8_t DATA_LENGTH = 2;

  void encode(bool enable,
              bool ignore_overrides,
              bool clear_override,
              bool clear_faults,
              bool cmd);
};

class SystemCmdFloat :
  public Pacmod3RxMsg
{
public:
  static constexpr uint8_t DATA_LENGTH = 3;

  void encode(bool enable,
              bool ignore_overrides,
              bool clear_override,
              bool clear_faults,
              float cmd);
};

class SystemCmdInt :
  public Pacmod3RxMsg
{
public:
  static constexpr uint8_t DATA_LENGTH = 2;

  void encode(bool enable,
              bool ignore_overrides,
              bool clear_override,
              bool clear_faults,
              uint8_t cmd);
};

// System Commands
class AccelCmdMsg :
  public SystemCmdFloat
{
public:
  static const uint32_t CAN_ID = 0x100;
};

class BrakeCmdMsg :
  public SystemCmdFloat
{
public:
  static const uint32_t CAN_ID = 0x104;
};

class CruiseControlButtonsCmdMsg :
  public SystemCmdInt
{
public:
  static const uint32_t CAN_ID = 0x108;
};

class DashControlsLeftCmdMsg :
  public SystemCmdInt
{
public:
  static const uint32_t CAN_ID = 0x10C;
};

class DashControlsRightCmdMsg :
  public SystemCmdInt
{
public:
  static const uint32_t CAN_ID = 0x110;
};

class EngineBrakeCmdMsg :
  public SystemCmdInt
{
  public:
    static const uint32_t CAN_ID;
};

class HazardLightCmdMsg :
  public SystemCmdBool
{
public:
  static const uint32_t CAN_ID = 0x114;
};

class HeadlightCmdMsg :
  public SystemCmdInt
{
public:
  static const uint32_t CAN_ID = 0x118;
};

class HornCmdMsg :
  public SystemCmdBool
{
public:
  static const uint32_t CAN_ID = 0x11C;
};

class MarkerLampCmdMsg :
  public SystemCmdBool
{
  public:
    static const uint32_t CAN_ID;
};

class MediaControlsCmdMsg :
  public SystemCmdInt
{
public:
  static const uint32_t CAN_ID = 0x120;
};

class ParkingBrakeCmdMsg :
  public SystemCmdBool
{
public:
  static const uint32_t CAN_ID = 0x124;
};

class ShiftCmdMsg :
  public SystemCmdInt
{
public:
  static const uint32_t CAN_ID = 0x128;
};

class SprayerCmdMsg :
  public SystemCmdBool
{
public:
  static const uint32_t CAN_ID;
};

class SteerCmdMsg :
  public SystemCmdFloat
{
public:
  static const uint32_t CAN_ID = 0x12C;
  static constexpr uint8_t DATA_LENGTH = 5;

  void encode(bool enabled,
              bool ignore_overrides,
              bool clear_override,
              bool clear_faults,
              float steer_pos,
              float steer_spd);
};

class TurnSignalCmdMsg :
  public SystemCmdInt
{
public:
  static const uint32_t CAN_ID = 0x130;
};

class RearPassDoorCmdMsg :
  public SystemCmdInt
{
public:
  static const uint32_t CAN_ID = 0x140;
};
class WiperCmdMsg :
  public SystemCmdInt
{
public:
  static const uint32_t CAN_ID = 0x134;
};
}  // namespace PACMod3
}  // namespace Drivers
}  // namespace AS

#endif  // PACMOD3_PACMOD3_CORE_H
