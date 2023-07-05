/*
    This file is a part of the wiringBone library
    Copyright (C) 2015 Abhraneel Bera

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#ifndef TWI_H
#define TWI_H

#include <I2c.h>

static void (*twi_onSlaveTransmit)(void);
static void (*twi_onSlaveReceive)(uint8_t*, int);

I2c i2cBus;

void twi_init(){}

uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
  if(length == 0)
  {
    return 0;
  }
  else
  {
    i2cBus.initI2C_RW(1, address, 0);
    ssize_t rtn = i2cBus.writeBytes(data, length);
    if (rtn == -1){
      perror("i2c: Failed to write bytes");
      return 1;
    }
    i2cBus.closeI2C();
    return 0;
  }
}

uint8_t twi_readFrom(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop)
{
  i2cBus.initI2C_RW(1, address, 0);
  ssize_t rtn = i2cBus.readBytes(data, length);
  if (rtn == -1){
    perror("i2c: Failed to read bytes");
    return 0;
  }
  i2cBus.closeI2C();
  return (uint8_t) rtn;
}

uint8_t twi_transmit(const uint8_t* data, uint8_t length)
{
  // Function for slave mode. Not required.
  // Dummy
  return 0;
}

void twi_attachSlaveRxEvent( void (*function)(uint8_t*, int) )
{
  twi_onSlaveReceive = function;
}

void twi_attachSlaveTxEvent( void (*function)(void) )
{
  twi_onSlaveTransmit = function;
}

void setWriteError()
{
  // Dummy
}
#endif