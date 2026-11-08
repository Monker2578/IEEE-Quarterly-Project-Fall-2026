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
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 1000f, decodeEngineRpm(0x0F, 0xA0));
}

void test_rpm_zero() {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, decodeEngineRpm(0x00, 0x00));
}

