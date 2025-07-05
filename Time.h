#ifndef TIME_H
#define TIME_H

class Timer
{
private:
	int start_tick_;
	int paused_tick_;
	
	bool is_started_;
	bool is_paused_;
public:
	Timer();
	void start();
	void stop();
	void paused();
	void unpaused();

	int get_ticks();

	bool is_started();
	bool is_paused();
};

#endif // !TIME_H
