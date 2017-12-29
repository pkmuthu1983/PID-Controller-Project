** Vehicle steering using PID controller **

#### 1. Source code:
'src' directory contains the implementation of the PID controller
(PID.cpp), and optimizer (SGD.cpp). 'build' directory contains the executable
(pid). It can be run as "./pid Kp Ki Kd ref_speed". For ex, "./pid 0.06
0.001 0.15 20" will maintain the car at 20mph, while steering the car
successfully.

#### 2. Description:
The car is controlled using two PID controllers. The first PID controller is
is for adjusting the steering angle (pid), while the second PID controller
(cruise_pid) is for maintaining the speed. The PID gain paramaters (kp, ki, kd)
for the steering angle PID controller can be inputted as arguments to the
executable. For the second PID controller, which mantains speed, these parameters
are hardcoded. After experimentation, I found that speed can be maintained by
using a proportional controller (i.e Ki = Kd = 0), whose output controls the
throttle. Kp was set to 0.0.5 for cruise_pid.

The parameters (Kp, Ki, Kd) for the steering angle controller is obtained using
manual tuning, and an optimizer (SGD). At first, I tried to use gradient descent
algorithm to find optimal Kp, Ki, and Kd (hence the name SGD), but noticed
several problems with convergence. So, I changed the algorithm to behave more
like the twiddle algorithm. Even this algorithm took long time to converge. So, I
used the numbers from optimizer as a starting point and further fine tuned them
using experimentation.

I found that the car was able to drive around a full lap, when Kp was 0.06,
Ki was 0.001, and Kd was 0.15. When Ki and Kd were zero, the car was responding
quickly to errors, and started oscillating beyond a point as shown in this
[video](./videos/p_only.mp4). For this run, Kp = 0.06, Ki = 0, and Kd = 0.

Next, I increased Kd until the oscillations settled down. When Kd was 0.15, the
car was able to steer around the curves, and at the same time it was not
oscillating. The video [here](./videos/pi_only.mp4) shows the run for Kp=0.06,
Ki=0, and Kd=0.15.

Finally, I adjusted Ki. Ki did not have much noticeable effect. However,
a small non-zero value of Ki helps in maintaining the car towards the center of
lane most of the time. That is, the integral term seemed to keep the error close to
zero in the long run. This [video](./videos/pid.mp4) shows a successful run with
Kp=0.06, Ki=0.001, Kd=0.15.
