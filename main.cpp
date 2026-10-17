#include <array>
#include <cstdint>

extern "C" void board_led_init() __attribute__((weak));
extern "C" void board_led_write(bool on) __attribute__((weak));
extern "C" void board_delay_ms(std::uint32_t ms) __attribute__((weak));

extern "C" void board_led_init() {}
extern "C" void board_led_write(bool) {}
extern "C" void board_delay_ms(std::uint32_t ms)
{
    volatile std::uint32_t ticks = ms * 1200U;
    while (ticks-- > 0U) {
        // busy wait fallback for bare-metal exercises
    }
}

namespace exercise {
constexpr std::array<std::uint16_t, 9> kSosBlinkPatternMs{
    200U, 200U, 200U, 200U, 200U, 600U, 600U, 600U, 600U};

[[noreturn]] void run_sos_blink_forever()
{
    bool led_on = true;

    while (true) {
        for (const auto duration_ms : kSosBlinkPatternMs) {
            board_led_write(led_on);
            board_delay_ms(duration_ms);
            led_on = !led_on;
        }

        board_delay_ms(1200U);
    }
}
} // namespace exercise

int main()
{
    board_led_init();
    exercise::run_sos_blink_forever();
}
