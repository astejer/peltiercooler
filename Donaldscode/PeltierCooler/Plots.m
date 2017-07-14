% This file is for processing data produced from the PID controller
%% Kp = 100, Ki = 0, Kd = 0 , supply 4V, 1.5A setpoint = 10 C

% write data from serial port to .dat file terminal command
% cat /dev/cu.usbmodem1411 > somefile.dat
% to view -- open in separate tab in terminal
% tail -f somefile.dat

close all; clear all; clc;
mat = csvread('./prop100.csv'); %%% this will give a nx3 matrix
temp = mat(:,1); %% makes this everything from the first column
pwm = mat(:,2);
time = mat(:,3);

% time is in ms -> convert to seconds
time = time/1000;

%Begin plotting:
% figure()
% p1 = plot(time, pwm);
% xlabel('Time (s)');
% ylabel('PWM signal');
% title('PWM output for K_{p} = 100, K_{i} = 0, K_{d} = 0', 'FontSize', 18);
% axis([0 250 0 300]);

figure()
p2 = plot(time, temp);
p2.LineWidth = 2;
p2.Color = 'black';
rl = refline(0, 10);
rl.Color = 'r';
rl.LineStyle = '--';
rl.LineWidth = 2;
%xlabel('time (s)');
%xlabel('Time (s)','FontSize',12,'FontWeight','bold','Color','r')
xlabel('Time (s)','FontSize',18);
ylabel('Temperature (C)', 'FontSize', 18);
title('Temperature for K_{p} = 100, K_{i} = 0, K_{d} = 0', 'FontSize', 18);
axis([0 250 8 25]);

%% Kp = 100, Ki = 0, Kd = 0 , supply 8V, 2.5A setpoint = 10 C

mat2 = csvread('./prop100_2.dat'); %%% this will give a nx3 matrix
temp2 = mat2(:,1); %% makes this everything from the first column
pwm2 = mat2(:,2);
time2 = mat2(:,3);

% time is in ms -> convert to seconds
time2 = time2/1000;

%Begin plotting:
figure(3)
plot(time2, pwm2);
xlabel('time (s)');
ylabel('pwm signal');
title('pwm output for Kp = 100, Ki = 0, Kd = 0 8v 2.5A source');

figure(4)
plot(time2, temp2);
xlabel('time (s)');
ylabel('Temperature (C)');
title('Temperature for Kp = 100, Ki = 0, Kd = 0 8v 2.5A source');

%% Kp = 100, Ki = 25, Kd = 0 , supply 8V, 2.5A setpoint = 0 C

mat = csvread('./exp3.dat'); %%% this will give a nx3 matrix
temp = mat(16:end,1); %% makes this everything from the first column
pwm = mat(16:end,2);
time = mat(16:end,3);

% time is in ms -> convert to seconds
time = time/1000;

%Begin plotting:
figure(5)
p1 = plot(time, pwm);
xlabel('Time (s)');
ylabel('PWM signal');
title('PWM output for K_{p} = 100, K_{i} = 0, K_{d} = 0', 'FontSize', 18);
axis([0 250 0 300]);

figure(6)
p2 = plot(time, temp);
p2.LineWidth = 2;
p2.Color = 'black';
rl = refline(0, 10);
rl.Color = 'r';
rl.LineStyle = '--';
rl.LineWidth = 2;
%xlabel('time (s)');
%xlabel('Time (s)','FontSize',12,'FontWeight','bold','Color','r')
xlabel('Time (s)','FontSize',18);
ylabel('Temperature (C)', 'FontSize', 18);
title('Temperature for K_{p} = 100, K_{i} = 0, K_{d} = 0', 'FontSize', 18);
axis([0 250 8 25]);

%%  Kp = 100, Ki = 25, Kd = 0 , supply 8V, 2.5A setpoint = 12.5 C

mat = csvread('./exp4.dat'); %%% this will give a nx3 matrix
temp = mat(10:end,1); %% makes this everything from the first column
pwm = mat(10:end,2);
time = mat(10:end,3);

% time is in ms -> convert to seconds
time = time/1000;

%Begin plotting:
figure()
p1 = plot(time, pwm);
xlabel('Time (s)');
ylabel('PWM signal');
title('PWM output for K_{p} = 100, K_{i} = 25, K_{d} = 0', 'FontSize', 18);
axis([0 250 0 300]);


figure()
p2 = plot(time, temp);
p2.LineWidth = 2;
p2.Color = 'black';
rl = refline(0, 12.5);
rl.Color = 'r';
rl.LineStyle = '--';
rl.LineWidth = 2;
%xlabel('time (s)');
%xlabel('Time (s)','FontSize',12,'FontWeight','bold','Color','r')
xlabel('Time (s)','FontSize',18);
ylabel('Temperature (C)', 'FontSize', 18);
title('Temperature for K_{p} = 100, K_{i} = 25, K_{d} = 0', 'FontSize', 18);
axis([0 250 10 25]);

%% Kp = 100, Ki = 25, Kd = 15 , supply 8V, 2.5A setpoint = 12.5 C
% 
% mat = csvread('./exp5.dat'); %%% this will give a nx3 matrix
% temp = mat(:,1); %% makes this everything from the first column
% pwm = mat(:,2);
% time = mat(:,3);
% 
% % time is in ms -> convert to seconds
% time = time/1000;
% 
% %Begin plotting:
% figure()
% p1 = plot(time, pwm);
% xlabel('time (s)');
% ylabel('pwm signal');
% title('pwm output for Kp = 100, Ki = 25, Kd = 15 8v 2.5A source');
% 
% figure()
% p2 = plot(time, temp);
% rl = refline(0, 12.5);
% rl.Color = 'r'
% rl.LineStyle = '--'
% xlabel('time (s)');
% ylabel('Temperature (C)');
% title('Temperature for Kp = 100, Ki = 25, Kd = 15 8v 2.5A source');
% axis([0 250 10 25])

%% Kp = 100, Ki = 25, Kd = 50 , supply 8V, 2.5A setpoint = 12.5 C

mat = csvread('./exp5.dat'); %%% this will give a nx3 matrix
temp = mat(15:end,1); %% makes this everything from the first column
pwm = mat(15:end,2);
time = mat(15:end,3);

% time is in ms -> convert to seconds
time = time/1000;

%Begin plotting:
figure()
p1 = plot(time, pwm);
xlabel('time (s)');
ylabel('pwm signal');
title('pwm output for Kp = 100, Ki = 25, Kd = 50 8v 2.5A source');
axis([0 250 0 300]);

figure()
p2 = plot(time, temp);
p2.LineWidth = 2;
p2.Color = 'black';
rl = refline(0, 12.5);
rl.Color = 'r';
rl.LineStyle = '--';
rl.LineWidth = 2;
%xlabel('time (s)');
%xlabel('Time (s)','FontSize',12,'FontWeight','bold','Color','r')
xlabel('Time (s)','FontSize',24)
ylabel('Temperature (C)', 'FontSize', 24);
title('Temperature for K_{p} = 100, K_{i} = 25, K_{d} = 50', 'FontSize', 18);
axis([0 250 10 25])
