I have an assignment question . We need to simulate FCFS scheduling algorithm using C on linux OS.
This is what I need to do
Write a program to simulate FCFS scheduling algorithm using pipes for inter process communication.

1. Let the parent program be the scheduler.

2. It takes as input the number of processes to be scheduled. For each process there is additional
information of arrival time and burst time. According to FCFS, the scheduler must schedule the
process that enters with the least timestamp first and continue in the order of arrival of
processes.

3.Initially the time in scheduler is 0.

4.For simplicity of time management assume 1 tick of time to be simulated by sleep (10).

5.Scheduler increments time until the time = arrival time of the first process

6.The scheduler must schedule the processes that have arrived in the order of their arrival times.

7.For each process to be scheduled, scheduler:
	i)Creates two pipes Pipe_sched and Pipe_child, forks a child process.
	ii)Pipe_sched from communication from sched to child, Pipe_child for communication
		from child to sched
	iii)Scheduler writes on Pipe_sched, parameters: arrival time and burst time of the new
		process.
	iv)The scheduler must on wait for the process to complete.
	v)Child process reads the parameters on Pipe_Sched and increments time by simulating
		time tick with sleep (10) until burst time has elapsed.
	vi)On completion Child process must send current timestamp to scheduler (parent
		process) by writing on to the pipe Pipe_child.
	vii)The scheduler updates it current time upon reaching from Pipe_Child as the time
		returned by the process and continues scheduling other process
		After the simulation of all the processes, the scheduler program must compute the average
		wait time Average wait time and generate the Gant chart and exit.

I understand the concept of fork() and wait(). 
but I am having problems implementing this program using exec() (which will contain the code for the child process entering the scheduler) and i am havin problem with pipes(We have to use unnamed pipes)
