function [u] = SMC(e)
%Sliding mode controller for a motor-propeller system
%   Detailed explanation goes here
%Model
function y=f(x)
        y=-0.08653*x^2-39.902*x;
end
u=-f
end

