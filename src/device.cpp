#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include "device.h"
#include "users.h"
#include "labworker.h"

vector<Device> Device::devices;

// Constructor
Device::Device(int _id, const string &_name, DeviceStatus _status)
    : id(_id), name(_name), status(_status) {}

void Device::setDeviceStatus(int deviceId, Device::DeviceStatus newStatus)
{
    for (size_t i = 0; i < Device::devices.size(); i++)
    {
        if (Device::devices[i].getId() == deviceId)
        {
            Device::devices[i].setStatus(newStatus);
            return;
        }
    }
    cout << "Not found device" << endl;
}

void Device::createDevice(int deviceId, const string &deviceName, Device::DeviceStatus deviceStatus)
{
    for (size_t i = 0; i < Device::devices.size(); i++)
    {
        if (Device::devices[i].getId() == deviceId)
        {
            cout << "Hata: This id is already in use." << endl;
            return;
        }
    }

    Device newDevice(deviceId, deviceName, deviceStatus);
    addDevice(newDevice);
}

void Device::addDevice(const Device &existingDevice)
{
    Device::devices.push_back(existingDevice);
    writeDevicesToFile(Device::devices);
}

void Device::writeDevicesToFile(const vector<Device> &devices)
{
    ofstream file("devices.txt");
    if (!file.is_open())
    {
        cerr << "Error: Could not open the file for writing." << endl;
        return;
    }

    for (size_t i = 0; i < devices.size(); ++i)
    {
        file << "Device ID: " << devices[i].getId() << "\n";
        file << "Name: " << devices[i].getName() << "\n";
        file << "Status: " << Device::deviceStatusToString(devices[i].getStatus()) << "\n";
        file << "-------------------------\n";
    }
}

string Device::deviceStatusToString(Device::DeviceStatus status)
{
    switch (status)
    {
    case Device::DeviceStatus::inUse:
        return "inUse";
    case Device::DeviceStatus::broken:
        return "broken";
    case Device::DeviceStatus::usable:
        return "usable";
    }

    return "";
}

void Device::removeDeviceByAdmin(int deviceID, int adminId)
{
    for (size_t i = 0; i < User::numberOfUsers; i++)
    {
        if (User::users[i].getIsAdmin())
        {
            for (size_t j = 0; j < Device::devices.size(); ++j)
            {
                if (Device::devices[j].getId() == deviceID)
                {
                    // Remove the device in memory
                    devices - (deviceID);
                    ofstream file("devices.txt");
                    if (!file.is_open())
                    {
                        cerr << "Error: Could not open the file for writing." << endl;
                        return;
                    }

                    for (size_t k = 0; k < Device::devices.size(); ++k)
                    {
                        file << "Device ID: " << Device::devices[k].getId() << "\n";
                        file << "Name: " << Device::devices[k].getName() << "\n";
                        file << "Status: " << deviceStatusToString(Device::devices[k].getStatus()) << "\n";
                        file << "-------------------------\n";
                    }

                    cout << "Device deleted." << endl;
                    return;
                }
            }
        }
    }

    cout << "You are not allowed to delete devices." << endl;
}

vector<Device> &operator-(vector<Device> &devices, int deviceId)
{
    auto it = find_if(devices.begin(), devices.end(),
                      [deviceId](const Device &d)
                      { return d.getId() == deviceId; });

    if (it != devices.end())
    {
        devices.erase(it);
        cout << "Device with ID " << deviceId << " has been deleted." << endl;
    }
    else
    {
        cout << "Device with ID " << deviceId << " not found." << endl;
    }

    return devices;
}

void Device::updateDeviceStatus(int labWorkerID, int deviceID, Device::DeviceStatus newStatus)
{
    for (size_t i = 0; i < Device::devices.size(); ++i)
    {
        if (Device::devices[i].getId() == deviceID)
        {
            Device::devices[i].setStatus(newStatus);
            Device::writeDevicesToFile(Device::devices);
            cout << "Device status updated for ID " << deviceID << " by lab worker ID " << labWorkerID << "." << endl;
            return;
        }
    }

    cout << "Device with ID " << deviceID << " not found in the file." << endl;
}

// Getter metodu
int Device::getId() const
{
    return id;
}

// Getter metodu
string Device::getName() const
{
    return name;
}

// Getter metodu
Device::DeviceStatus Device::getStatus() const
{
    return status;
}

// Setter metodu
void Device::setStatus(DeviceStatus newStatus)
{
    status = newStatus;
}