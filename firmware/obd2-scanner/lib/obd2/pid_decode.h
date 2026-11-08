#pragma once
#include <stdint.h>

constexpr int COOLANT_TEMP_OFFSET_C = 40;

constexpr float RPM_UNITS_PER_RPM = 4.0f;

inline float decodePercent(uint8_t rawData) {
    return rawData * 100.0f / 255.0f;
}

inline int decodeCoolantTempC(uint8_t rawData) {
    return int(rawData) - COOLANT_TEMP_OFFSET_C;
}

inline int decodeSpeedKmh(uint8_t rawData) {
    return rawData;
}

inline float decodeEngineRpm(uint8_t highData, uint8_t lowData) {
    uint16_t raw = (uint16_t(highData) << 8) | lowData;
    return raw / RPM_UNITS_PER_RPM;
}

inline float decodeEngineLoadPercent(uint8_t rawData) {
    return decodePercent(rawData);
}

inline float decodeThrottlePercent(uint8_t rawData) {
    return decodePercent(rawData);
}

inline float decodeModuleVoltageV(uint8_t highData, uint8_t lowData) {
    uint16_t raw = (uint16_t(highData) << 8) | lowData;
    return raw / 1000.0f;
}