/*
  This file is part of the ArduinoBLE library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _BLE_DEVICE_H_
#define _BLE_DEVICE_H_

#include <Arduino.h>

#include "BLEService.h"

enum BLEDeviceEvent {
  BLEConnected = 0,
  BLEDisconnected = 1,
  BLEDiscovered = 2,

  BLEDeviceLastEvent
};

#define BLE_PHY_ALL_N           0x03
#define BLE_PHY_TX_MASK         0x01
#define BLE_PHY_RX_MASK         0x02
#define BLE_PHY_1MBPS           0x01
#define BLE_PHY_2MBPS           0x02
#define BLE_PHY_CODED           0x04
#define BLE_PHY_NOT_SET         0x00
#define BLE_PHYS_SUPPORTED      (BLE_PHY_1MBPS | BLE_PHY_2MBPS | BLE_PHY_CODED)
#define BLE_PHY_OPTS_NONE       0x00
#define BLE_PHY_OPTS_S2         0x01
#define BLE_PHY_OPTS_S8         0x02

class BLEDevice;

typedef void (*BLEDeviceEventHandler)(BLEDevice device);

class BLEDevice {
public:
  BLEDevice();
  virtual ~BLEDevice();

  virtual void poll();
  virtual void poll(unsigned long timeout);

  virtual bool connected() const;
  virtual bool disconnect();

  virtual String address() const;

  bool hasLocalName() const;
    
  bool hasAdvertisedServiceUuid() const;
  bool hasAdvertisedServiceUuid(int index) const;
  int advertisedServiceUuidCount() const;

  String localName() const;
  String advertisedServiceUuid() const;
  String advertisedServiceUuid(int index) const;

  virtual int rssi();
  virtual int phys(uint8_t* tx, uint8_t* rx);
  virtual int setLongRange(bool longRange = true);

  bool connect();
  bool discoverAttributes();
  bool discoverService(const char* serviceUuid);

  virtual operator bool() const;
  virtual bool operator==(const BLEDevice& rhs) const;
  virtual bool operator!=(const BLEDevice& rhs) const;

  String deviceName();
  int appearance();

  int serviceCount() const; 
  bool hasService(const char* uuid) const;
  bool hasService(const char* uuid, int index) const;
  BLEService service(int index) const;
  BLEService service(const char * uuid) const;
  BLEService service(const char * uuid, int index) const;
  int characteristicCount() const;
  bool hasCharacteristic(const char* uuid) const;
  bool hasCharacteristic(const char* uuid, int index) const;
  BLECharacteristic characteristic(int index) const;
  BLECharacteristic characteristic(const char * uuid) const;
  BLECharacteristic characteristic(const char * uuid, int index) const;

protected:
  friend class ATTClass;
  friend class GAPClass;

  BLEDevice(uint8_t addressType, uint8_t address[6]);

protected:
  friend class GAPClass;

  bool hasAddress(uint8_t addressType, uint8_t address[6]);

  void setAdvertisementData(uint8_t type, uint8_t eirDataLength, uint8_t eirData[], int8_t rssi);
  void setScanResponseData(uint8_t eirDataLength, uint8_t eirData[], int8_t rssi);

  bool discovered();

private:
  uint8_t _addressType;
  uint8_t _address[6];
  uint8_t _advertisementTypeMask;
  uint8_t _eirDataLength;
  uint8_t _eirData[31 * 2];
  int8_t _rssi;
};

#endif
