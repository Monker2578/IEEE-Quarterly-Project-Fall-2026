#include <unity.h>
#include "../../lib/obd2/pid_decode.h"

void setUp() {}
void tearDown() {}

// Coolant Temp (PID 0x05) Tests
void test_coolant_typical() {
    TEST_ASSERT_EQUAL(90, decodeCoolantTempC(130));

}
void test_coolant_lowest() {
    TEST_ASSERT_EQUAL(-40, decodeCoolantTempC(0));
}

void test_coolant_highest() {
    TEST_ASSERT_EQUAL(215, decodeCoolantTempC(255));
}

// Speed (PID 0x0D) Tests
void test_speed_stopped() {
    TEST_ASSERT_EQUAL(0, decodeSpeedKmh(0));
}

void test_speed_typical() {
    TEST_ASSERT_EQUAL(88, decodeSpeedKmh(88));
}

void test_speed_max() {
    TEST_ASSERT_EQUAL(255, decodeSpeedKmh(255));
}

// RPM (PID 0x0C) Tests
void test_rpm_typical() {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 1000.0f, decodeEngineRpm(0x0F, 0xA0));
}

void test_rpm_zero() {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, decodeEngineRpm(0x00, 0x00));
}

void test_rpm_max() {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 16383.75f, decodeEngineRpm(0xFF, 0xFF));
}

void test_rpm_low_data_only() {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 1.0f, decodeEngineRpm(0x00, 0x04));
}

// Throttle (PID 0x11) Tests
void test_throttle_closed() {
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, decodeThrottlePercent(0));
}

void test_throttle_half() {
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 50.2f, decodeThrottlePercent(128));
}

void test_throttle_full() {
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 100.0f, decodeThrottlePercent(255));
}

// Engine Load (PID 0x04) Tests
void test_load_zero() {
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, decodeEngineLoadPercent(0));
}

void test_load_half() {
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 50.2f, decodeEngineLoadPercent(128));
}

void test_load_full() {
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 100.0f, decodeEngineLoadPercent(255));
}

// Battery Voltage (PID 0x42) Tests
void test_voltage_running_car() {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 13.0f, decodeModuleVoltageV(0x32, 0xC8));
}

void test_voltage_zero() {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, decodeModuleVoltageV(0x00, 0x00));
}

void test_voltage_low_data_only() {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, decodeModuleVoltageV(0x03, 0xE8));
}

// Run All Tests
int main() {
    UNITY_BEGIN();

    // Run Coolant Temp (PID 0x05) Tests
    RUN_TEST(test_coolant_typical);
    RUN_TEST(test_coolant_lowest);
    RUN_TEST(test_coolant_highest);

    // Run Speed (PID 0x0D) Tests
    RUN_TEST(test_speed_stopped);
    RUN_TEST(test_speed_typical);
    RUN_TEST(test_speed_max);

    // Run RPM (PID 0x0C) Tests
    RUN_TEST(test_rpm_typical);
    RUN_TEST(test_rpm_zero);
    RUN_TEST(test_rpm_max);
    RUN_TEST(test_rpm_low_data_only);

    // Run Throtte (PID 0x11) Tests
    RUN_TEST(test_throttle_closed);
    RUN_TEST(test_throttle_half);
    RUN_TEST(test_throttle_full);

    // Run Engine Load (PID 0x04) Tests
    RUN_TEST(test_load_zero);
    RUN_TEST(test_load_half);
    RUN_TEST(test_load_full);

    // Run Battery Voltage (PID 0x42) Tests
    RUN_TEST(test_voltage_zero);
    RUN_TEST(test_voltage_running_car);
    RUN_TEST(test_voltage_low_data_only);

    return UNITY_END();
}