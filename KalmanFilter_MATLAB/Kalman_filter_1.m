sampleTime = 0.0001;
t = 0:sampleTime:4;
posOri = sin(2*pi*0.5*t);
posNoise = posOri + 0.001*(rand(1,length(t))-0.5);

figure (1)
plot(t,posOri,t,posNoise,'r')
grid on;
title('original position and added noise')
legend('original','added noise')
xlabel('time(s)')
ylabel('rad')
set(gcf,'Color',[1,1,1])


% kalman filter
%x(k+1) = A*x(k) + wk;


velOri = [0, diff(posOri)]/sampleTime;
velNoise = [0, diff(posNoise)]/sampleTime;


dt = sampleTime;
A = [1 dt;0 1];
H = [1 0];
Q = [1 0;0 1000];
R = 0.01;
x = [0 3]';
P = 3*eye(2);

tmpPos = zeros(length(t),1);
tmpVel = zeros(length(t),1);

for i = 1: length(t)

    x_hat = A*x;
    P_hat = A*P*A'+Q;
    
    K = P_hat*H'*inv(H*P_hat*H' + R);
    x = x_hat + K*(posNoise(i)-H*x_hat);
    P = P_hat - K*H*P_hat;
    
    tmpPos(i) = x(1);
    tmpVel(i) = x(2);
end


figure (2)
plot(t, tmpVel, t, velOri, 'r');grid on
legend('Kalman', 'original')
xlabel('time (s)')
ylabel('rad/sec')
set(gcf, 'Color', [1,1,1])