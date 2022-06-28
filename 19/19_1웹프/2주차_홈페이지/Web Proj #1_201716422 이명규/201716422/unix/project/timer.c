#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <ncursesw/curses.h>
#include <locale.h>

int min = 0;

void timer()
{
	if (min >= 0)
	{
		attron(COLOR_PAIR(6));
		mvprintw(5, 70, "%d    ", min);//남은 시각 출력
		refresh();

		min--;
	}
}

int createTimer(timer_t *timerID, int tim)
{
	struct sigevent         te;
	struct itimerspec       its;
	struct sigaction        sa;
	int                     sigNo = SIGRTMIN;

	/* Set up signal handler. */
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = timer;     // 타이머 호출시 호출할 함수 
	sigemptyset(&sa.sa_mask);
	min = tim;

	if (sigaction(sigNo, &sa, NULL) == -1)
	{
		printf("sigaction error\n");
		return -1;
	}

	/* Set and enable alarm */
	te.sigev_notify = SIGEV_SIGNAL;
	te.sigev_signo = sigNo;
	te.sigev_value.sival_ptr = timerID;
	timer_create(CLOCK_REALTIME, &te, timerID);

	its.it_interval.tv_sec = 1;
	its.it_interval.tv_nsec = 0;
	its.it_value.tv_sec = 1;

	its.it_value.tv_nsec = 0;
	timer_settime(*timerID, 0, &its, NULL);

	return 0;
}