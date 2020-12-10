function u  = SMC(S,Wd,Wr)
%Sliding mode controller for a motor-propeller system
%Model
function y=f(x)
        y=-0.08653*x^2-39.902*x;
end
e=Wd-Wr;
mu=0.02;
beta=0.00015;
sigma=10;
u=-f(Wr)-sigma*e-(mu+beta)*sign(S);
end

