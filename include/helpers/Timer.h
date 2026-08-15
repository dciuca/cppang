#pragma once
#include "raylib.h"
#include <functional>

/// A countdown timer that optionally repeats and triggers a callback on expiry.
class Timer
{
public:
    /// @param duration  Duration in seconds before the timer expires.
    /// @param repeat    If true, the timer restarts automatically after expiry.
    /// @param autostart If true, the timer starts immediately on construction.
    /// @param func      Callback invoked when the timer expires (may be nullptr).
    Timer(
        int duration,
        bool repeat,
        bool autostart,
        void (*func)(void))
        : duration(duration), repeat(repeat)
    {
        start_time = 0;
        active = false;
        func = func;
        if (autostart)
            activate();
    }
    ~Timer() = default;

    /// Starts (or restarts) the timer from the current time.
    void activate()
    {
        active = true;
        start_time = GetTime();
    };

    /// Stops the timer. If repeat is true, immediately reactivates it.
    void deactivate()
    {
        active = false;
        start_time = 0;
        if (repeat)
            activate();
    };

    /// Must be called every frame. Fires the callback and deactivates when the duration elapses.
    void update()
    {
        if (active)
        {
            if (GetTime() - start_time >= duration)
            {
                if (func && start_time)
                    func();
                deactivate();
            }
        }
    };

private:
    int duration;
    int start_time;
    bool repeat;
    bool active;
    void (*func)(void);
};