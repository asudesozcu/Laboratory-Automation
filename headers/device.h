#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Device
{
public:
 static vector<Device> devices;

    enum class DeviceStatus
    {
        inUse,
        broken,
        usable
    };

    // Constructor
    Device(int _id, const string &_name, DeviceStatus _status);

    // Getter ve Setter metotları
    int getId() const;
    string getName() const;
    DeviceStatus getStatus() const;
    void setStatus(DeviceStatus newStatus);

   
    void setDevices(const vector<Device> &newDevices);

    const vector<Device> &getDevices() const;

    // Diğer metotlar
static void setDeviceStatus(int deviceId, Device::DeviceStatus newStatus);
    static void createDevice(int deviceId, const string &deviceName, DeviceStatus deviceStatus);
    static void addDevice(const Device &existingDevice);
    static void updateDeviceStatus(int labWorkerID, int deviceID, DeviceStatus newStatus);
   static void removeDeviceByAdmin(int deviceID, int adminId);
  static  string deviceStatusToString(DeviceStatus status);
   static void writeDevicesToFile(const vector<Device> &devices);
   
   
    friend std::vector<Device>& operator-(std::vector<Device>& devices, int deviceId);



private:
    int id;
    string name;
    DeviceStatus status;
};


#endif // DEVICE_H
