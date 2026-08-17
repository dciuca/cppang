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
        elapsed = 0;
        active = false;
        this->func = func;
        if (autostart)
            activate();
    }
    ~Timer() = default;

    /// Returns true if the timer is currently active (counting down).
    bool isActive() const { return active; };

    /// Returns the remaining time in seconds, or 0 if inactive.
    float GetTimeLeft() const { return active ? duration - elapsed - (GetTime() - start_time) : 0; };

    /// Starts (or restarts) the timer from the current time.
    void activate()
    {
        elapsed = 0;
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
            if (elapsed + (GetTime() - start_time) >= duration)
            {
                if (func && start_time)
                    func();
                deactivate();
            }
        }
    };

    // pause() — freeze current elapsed
    void pause()
    {
        if (!active)
            return;
        elapsed += GetTime() - start_time;
        active = false;
    }

    // resume() — restart start_time from now, elapsed carries the history
    void resume()
    {
        if (active)
            return;
        start_time = GetTime();
        active = true;
    }

private:
    int duration;
    double start_time;
    double elapsed;
    bool repeat;
    bool active;
    void (*func)(void);
};