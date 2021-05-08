#include <global.h>
#include <Canbus.h>
#include <mcp2515_defs.h>
#include <mcp2515.h>
#include <defaults.h>
#include <can.h>
#include <Arduino.h>

int can_setup(){

  // Initialise MCP2515 CAN controller
  // Return 1 if success 0 if fail
  return !mcp2515_init(0);
}

unsigned int _combined_data(uint8_t data[], unsigned int firstIndex)
{
    return (data[firstIndex] << 8) + data[firstIndex + 1];
}

unsigned int can_read(unsigned int addr) {
 
  while(1) {
    // Read Message
    tCAN r_message;
    if (mcp2515_check_message()) 
    {
      if (mcp2515_get_message(&r_message)) 
      {
        switch(r_message.id) 
        { 
          case 0x65D: // brake temp front left, front right, rear left, rear right
            // brake temp front left
            switch(addr)
            {
                case ADDR_BRAKE_TEMP_FRONT_LEFT:  // brake temp front left
                    return _combined_data(r_message.data, 0);
                case ADDR_BRAKE_TEMP_FRONT_RIGHT:  // brake temp front right
                    return _combined_data(r_message.data, 2);
                case ADDR_BRAKE_TEMP_REAR_LEFT: // brake temp rear left
                    return _combined_data(r_message.data, 4);
                case ADDR_BRAKE_TEMP_REAR_RIGHT: // brake temp rear right
                    return _combined_data(r_message.data, 6);
                    
            }
            break;
          case 0x655: // brake pressure front, brake pressure rear, coolant pressure, power steering pressure           
            
            switch(addr)
            {
                case ADDR_BRAKE_PRESSURE_REAR: // brake pressure rear
                    return _combined_data(r_message.data, 2);
                case ADDR_BRAKE_PRESSURE_FRONT: // brake pressure front
                    return _combined_data(r_message.data, 0);          
            }

          case 0x648: // wheel speed front left, front right, back left, back right

            switch(addr)
            {
                case ADDR_WHEEL_SPEED_FRONT_LEFT: // wheel speed front left
                    return _combined_data(r_message.data, 0);
                case ADDR_WHEEL_SPEED_FRONT_RIGHT: // wheel speed front right
                    return _combined_data(r_message.data, 2);
                case ADDR_WHEEL_SPEED_REAR_LEFT: // wheel speed rear left
                    return _combined_data(r_message.data, 4);
                case ADDR_WHEEL_SPEED_REAR_RIGHT: // wheel speed rear right
                    return _combined_data(r_message.data, 6);
            }
            
          case 0x640: // engine speed, throttle position, manifold air pressure, manifold air temperature
            // engine speed
            switch(addr)
            {
                case ADDR_ENGINE_SPEED: // engine speed
                    return _combined_data(r_message.data, 0);
                case ADDR_MANIFOLD_AIR_PRESSURE: // manifold air pressure
                    return _combined_data(r_message.data, 2);
                case ADDR_MANIFOLD_AIR_TEMP: // manifold air temp
                    return _combined_data(r_message.data, 4);
                case ADDR_THROTTLE_POSITION: // throttle position
                    return _combined_data(r_message.data, 6);
            }
            
            

          case 0x649: 
            switch(addr)
            {
                case ADDR_ENGINE_OIL_TEMP: // engine oil temp
                    return r_message.data[1];
                case ADDR_COOLANT_TEMP: // coolant temp
                    return r_message.data[0];
            }

          case 0x644:
            switch(addr)
            {
                case ADDR_OIL_PRESSURE: // oil pressure
                    return _combined_data(r_message.data, 6);
            }
    
          case 0x64E: 
            switch(addr)
            {
                case ADDR_NEUTRAL_GEAR_SWITCH: // neutral gear switch
                    return r_message.data[4] & 128; // deci number for 10000000
            }
            
          case 0x64D:
            switch(addr)
            {
                case ADDR_GEAR: // gear
                    return r_message.data[4] & 0b00001111;
            }
          case 0x631:
            switch(addr)
            {
                case ADDR_CAR_STATUS_BIT: // car status bit  
                    return r_message.data[0]; 
            }
        }
      }
    }
    else
    {
      return NULL;
    }
  }
}

