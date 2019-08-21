#include "dac8568.h"
//#include <iostream>
#include <stdio.h>

DAC_MSG_OBJECT msg_obj;


// Setup function to initialize the DAC8568
// control_field - Choose between flexible and static mode.
// data_field - Select which reference mode is being used.  If using static mode, this must = 0.
// feature_field - Select the control field for reference mode.  If using flexible mode, this must = 0.
uint32_t DAC8568_Setup(CONTROL_SETUP_MODE control_field, INTERNAL_REF_COMM_DATA data_field, INTERNAL_REF_COMM_FEATURE feature_field) {
  //Prefix always 0b0XXX
  msg_obj.prefix = PREFIX_DONT_CARE;

  msg_obj.control = control_field;
  
  //Address 0bXXXX for Setup
  msg_obj.address = ADDRESS_DONT_CARE;

  msg_obj.data = data_field;
  msg_obj.feature = feature_field;

  return *(uint32_t*)& msg_obj;
}

// Function to power up or power down DAC channel function.  
// data_field_power - Select weather to power up a DAC channel or to power it off with selected impedence.
// channel_field - Select which channels to power on/off.  For example (POWER_DAC_A | POWER_DAC_B | POWER_DAC_C) for channel_field would apply to DAC channels A,B, and C.
uint32_t DAC8568_Power_Up_Down(POWER_UP_DOWN_DAC data_field_power, uint8_t channel_field) {
  //Prefix always 0b0XXX
  msg_obj.prefix = PREFIX_DONT_CARE;

  msg_obj.control = CONTROL_POWER_DOWN_COMM;

  //Address 0bXXXX for setup.  Power Up/Down Address controlled by Data and Feature bits.
  msg_obj.address = ADDRESS_DONT_CARE;

  //OR the data field to combine the bits to select power on or off.
  msg_obj.data = data_field_power | (channel_field >> 4);
  msg_obj.feature = channel_field;

  return *(uint32_t*)& msg_obj;
}

// Function to write to the DAC's input register.  
// address_field - Select the DAC's address.  BROADCAST will set the value to every DAC channel.
// data_field - Value from 0 to 65,535.
uint32_t DAC8568_Write_Input_Reg(CHANNEL_SELECT address_field, uint16_t data_field) {
  //Prefix always 0b0XXX
  msg_obj.prefix = PREFIX_DONT_CARE;

  msg_obj.control = CONTROL_WRITE_TO_INPUT_REGISTER;

  msg_obj.address = address_field;

  msg_obj.data = data_field;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}

// Function to update the selected DAC register
// address_field - Select which DAC address to update.  Broadcast will update all DAC registers.
// data_field - Value from 0 to 65,535.
uint32_t DAC8568_Update_Dac_Reg(CHANNEL_SELECT address_field, uint16_t data_field) {
  //Prefix always 0b0XXX
  msg_obj.prefix = PREFIX_DONT_CARE;

  msg_obj.control = CONTROL_UPDATE_DAC_REGISTER;

  msg_obj.address = address_field;

  msg_obj.data = data_field;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}

// Function to write to the clear code register.  
// feature_field - Select which mode of clear to use.  Choose between 4 modes.
uint32_t DAC8568_Write_Clear_Code_Reg(CLEAR_CODE_FEATURE feature_field) {
  //Prefix always 0b0XXX
  msg_obj.prefix = PREFIX_DONT_CARE;
  msg_obj.control = CONTROL_DONT_CARE;
  msg_obj.address = ADDRESS_DONT_CARE;
  msg_obj.data = DATA_DONT_CARE;

  msg_obj.feature = feature_field;

  return *(uint32_t*)& msg_obj;
}

// Function to write to the LDAC register. 
// channel_field - Select which channels to load the LDAC register for.  Example: (LDAC_REG_A | LDAC_REG_C | LDAC_REG_E) for channel_field will load just those channel registers.
uint32_t DAC8568_Load_DAC(uint8_t channel_field) {
  msg_obj.prefix = PREFIX_DONT_CARE;
  msg_obj.control = CONTROL_WRITE_TO_LDAC_REG;
  msg_obj.address = ADDRESS_DONT_CARE;
  msg_obj.data = channel_field >> 4;
  msg_obj.feature = channel_field;

  return *(uint32_t*)& msg_obj;
}

// Function to software reset the DAC8568.  (Power-on-reset).
uint32_t DAC8568_Reset() {
  msg_obj.prefix = PREFIX_DONT_CARE;
  msg_obj.control = CONTROL_SOFTWARE_RESET;
  msg_obj.address = ADDRESS_DONT_CARE;
  msg_obj.data = DATA_DONT_CARE;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}

// Function to write to selected DAC input register and updates all DAC registers
// address_field - Address field for selecting which DAC channel to write to.  BROADCAST will write value to all channels.
// data_field - Data value between 0 and 65,535.  
uint32_t DAC8568_Write_Input_Reg_And_Update_All(CHANNEL_SELECT address_field, uint16_t data_field) {
  msg_obj.prefix = PREFIX_DONT_CARE;
  msg_obj.control = CONTROL_WRITE_TO_DAC_CH_AND_UPDATE_ALL_REG;
  msg_obj.address = address_field;
  msg_obj.data = data_field;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}

// Function to write to selected DAC input and update only the respective DAC register.
// address_field - Address field for selecting which DAC channel to write to.  BROADCAST will write value to all channels. (Same functionality as updating all DAC channels.
// data_field - Data value between 0 and 65,535.
uint32_t DAC8568_Write_Input_Reg_And_Update_Single(CHANNEL_SELECT address_field, uint16_t data_field) {
  msg_obj.prefix = PREFIX_DONT_CARE;
  msg_obj.control = CONTROL_WRITE_TO_DAC_CH_AND_UPDATE_SINGLE_REG;
  msg_obj.address = address_field;
  msg_obj.data = data_field;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}
