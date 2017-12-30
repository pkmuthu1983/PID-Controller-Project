# Vehicle steering using PID controller

#### 1. Source code:
'src' directory contains the implementation of the PID controller
(PID.cpp), and optimizer (SGD.cpp). 'build' directory contains the executable
(pid). It can be run as "./pid".

#### 2. Discussion:
The car is controlled using two PID controllers. The first PID controller is
is for adjusting the steering angle (pid), while the second PID controller
(cruise_pid) is for maintaining the speed. The PID gain paramaters (kp, ki, kd)
for both the PID controllers can be found in src/main.cpp.
For the cruise PID controller, I found that speed can be maintained by
using a proportional controller (i.e Ki = Kd = 0), whose output controls the
throttle. Kp was set to 0.05 for cruise_pid.

The parameters (Kp, Ki, Kd) for the steering angle controller were obtained using
manual tuning, and an optimizer (SGD). At first, I tried to use gradient descent
algorithm to find optimal Kp, Ki, and Kd (hence the name SGD), but noticed
several problems with convergence. So, I changed the algorithm to behave more
like the twiddle algorithm. Even this algorithm took long time to converge. So, I
used the numbers from optimizer as a starting point and further fine tuned them
using experimentation. I found that the car was able to drive around a full lap,
when Kp was 0.06, Ki was 0, and Kd was 0.15.

This [video](./videos/pid.mp4) shows a successful run with Kp=0.06, Ki=0,
and Kd=0.15.

##### 2.1. Role of P, I, and D:
The proportional block is meant to steer the car towards the centre whenever the
obesrved error (cte) becomes non-zero. I noticed that a small value of the proportional
gain was insufficient to quickly steer the car back to center.
As Kp was increased, with Ki and Kd set to zero, the car was responding
quickly to errors, but it started oscillating beyond a point, as shown in this
[video](./videos/p_only.mp4). For this run, Kp = 0.06, Ki = 0, and Kd = 0.
And the speed limit (ref_speed variable in src/main.cpp) was set to 20.
It was hard to find a suitable of Kp, such that car will respond quickly and at
the same time does not oscillate.

This is when the derivative block came useful. Increasing the derivaive gain term
Kd helped to dampen the oscillations in steering angle. That is, it helped
to smoothen sharp fluctuations in steering angle, when car was overshooting or
undershooting in response to large errors. When Kd was set to 0.15, the car
was able to steer around curves without any oscillations.
The video [here](./videos/pi_only.mp4) shows the run for Kp=0.06,
Ki=0, and Kd=0.15. Having only the derivative block (i.e Kp = Ki = 0, and Kd > 0),
was not useful either, as the car started moving in a zig-zag fashion. We know
that the derivative only controller will try to keep the rate of change of error
to zero. So, any increase in cte leads to negative value of steering angle, 
thus causing a reduction in cte. This means there is negative rate of change of cte,
which produced positive steer, and so on.

The integral block did not have much noticeable effect, as there was no steady state
error. The cte values fluctuated closely around zero, but there was no positive
or negative bias on an average. So, Ki was set to zero.
