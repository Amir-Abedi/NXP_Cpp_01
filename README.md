# NXP_C-_01

Small C++ exercises for the NXP FRDM-MCXN947 board.

## Included exercise

- `main.cpp`: a simple "fun" SOS LED blink loop.
  - The app calls three weak board hooks you can override with MCUXpresso SDK code:
    - `board_led_init()`
    - `board_led_write(bool on)`
    - `board_delay_ms(uint32_t ms)`

This keeps the example easy to start and customize for side projects.

## Build notes

- If you compile with MCUXpresso SDK board support, provide strong implementations for the three board hooks above.
- A fallback implementation is included so the file can be compiled as plain C++ during early experimentation.

Host compile sanity check:

```bash
g++ -std=c++17 -Wall -Wextra -Werror -c main.cpp -o /tmp/main.o
```
