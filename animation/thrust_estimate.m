clc
m = 1.83; % mass
g = 9.807; % gravity
p = 1.225; % air density
d = 0.2; % diameter of the propeller
l1 = 0.262; % length of the beam from mass
l2 = 0.65; % length of the beam from propeller
q = [-30 -24 -18 -12 0 12 18 24 30]; % angle of seesaw
n = [1130 1585 1700 1500 1675 1990 1900 2123 2295]; 
n = n / 60;
[r,w] = size(n);
f = m * g * cosd(q) * (l1/l2); % force from moment
for i=1:w
 ct(i) = f(i) / (p * (d ^ 4) * (n(i) ^ 2));
end
x = 1:w;
plot(x,f,x,ct);
grid on;
legend('Thrust','Thrust Coefficient');
fprintf('Thrust Forces');
f
fprintf('Thrust Coefficients');
ct
p * (d ^ 4)