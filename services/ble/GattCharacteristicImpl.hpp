#ifndef SERVICES_GATT_CHARACTERISTIC_IMPL_HPP
#define SERVICES_GATT_CHARACTERISTIC_IMPL_HPP

#include "services/ble/Gatt.hpp"

namespace services
{
    class GattCharacteristicImpl
        : public GattCharacteristic
    {
    public:
        GattCharacteristicImpl(GattService& service, const GattAttribute::Uuid& type, uint16_t valueLength);
        GattCharacteristicImpl(GattService& service, const GattAttribute::Uuid& type, uint16_t valueLength, Properties properties);
        GattCharacteristicImpl(GattService& service, const GattAttribute::Uuid& type, uint16_t valueLength, Properties properties, Permissions permissions);

        // from GattCharacteristic
        virtual GattAttribute::Uuid Type() const;
        virtual Properties CharacteristicProperties() const;
        virtual Permissions CharacteristicPermissions() const;

        virtual GattAttribute::Handle Handle() const;
        virtual GattAttribute::Handle& Handle();

        virtual uint16_t ValueLength() const;

        virtual void Update(infra::ConstByteRange data, infra::Function<void()> onDone);

        // from GattCharacteristicClientOperationsObserver
        virtual GattAttribute::Handle ServiceHandle() const;
        virtual GattAttribute::Handle CharacteristicHandle() const;

    private:
        const GattService& service;
        GattAttribute attribute;
        uint16_t valueLength;
        Properties properties;
        Permissions permissions;
    };
}

#endif
