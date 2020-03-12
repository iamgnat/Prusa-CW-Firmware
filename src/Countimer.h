#pragma once

#include <Arduino.h>

#define COUNTIMER_MAX_MINUTES_SECONDS 59

typedef void(*timer_callback)(void);

class Countimer {
public:
	enum CountType {
		COUNT_NONE = 0,
		COUNT_UP = 1,
		COUNT_DOWN = 2
	};

	Countimer(CountType countType);

	// Set up counter time(hours, minutes, seconds) for existing timer.
	void setCounter(uint8_t hours, uint8_t minutes, uint8_t seconds);

	// Returns timer's current hours.
	uint16_t getCurrentHours();

	// Returns timer's current minutes.
	uint8_t getCurrentMinutes();

	// Returns timer's current seconds.
	uint8_t getCurrentSeconds();

	void setInterval(timer_callback callback, uint32_t interval);

	// Returns true if counter is completed, otherwise returns false.
	bool isCounterCompleted();

	// Returns true if counter is still running, otherwise returns false.
	bool isCounterRunning();

	// Returns true if timer is stopped, otherwise returns false.
	bool isStopped();

	// Run timer. This is main method.
	// If you want to start timer after run, you have to invoke start() method.
	void run();

	// Starting timer.
	void start();

	// Stopping timer.
	void stop();

	// Pausing timer.
	void pause();

	// Restart timer.
	void restart();

private:
	// Counting up timer.
	void countDown();
	
	void callback();
	void complete();

	// Counting down timer.
	void countUp();

	uint32_t _interval;
	uint32_t _previousMillis;

	// Stores current counter value in milliseconds.
	uint32_t _currentCountTime;
	uint32_t _startCountTime;

	// Stores cached user's time.
	uint32_t _countTime;

	// Function to execute.
	timer_callback _callback;

	// Function to execute when timer is complete.
	timer_callback _onComplete;
	bool _isCounterCompleted;
	bool _isStopped;
	CountType _countType;
};
