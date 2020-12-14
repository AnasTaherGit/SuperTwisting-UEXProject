function u  = SMC(Wd,Wr)
%Sliding mode controller for a motor-propeller system
%Model
function y=f(x)
        y=-0.08653*x^2-39.902*x;
end
e=Wr-Wd;
mu=20;
%beta=0.00015;
%sigma=1;
Ku=6338.1;
u=-f(Wr)-Ku*mu*sign(e)*abs(e);
end

