#pragma once
#ifndef IMP_TIMER_H
#define IMP_TIMER_H
class ImpTimer
{
public:
	ImpTimer();
	~ImpTimer();
	void start();
	void stop();
	void paused();
	void unpaused();

	int get_ticks();
	
	bool is_started_();
	bool is_paused_();
private:
	int start_tick;
	int pause_tick;

	bool is_paused;
	bool is_started;
};
#endif // !IMP_TIMER_H
