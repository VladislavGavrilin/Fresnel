function res = k_n_old(k,T,r1,r2,n,varargin)
% 11.06.2013 Calculate k_n using Fresnel integrals (as in 2005)
% The result is normalized (k_0=1 for r=inf)
% phi0 is in radians.

if ~isempty(varargin)
    phi0 = varargin{1};
else
    phi0 = 0;
end

% exp(1j(A*s^2+B*s))
A = -(k/2)*(1/r2-1/r1);
B = -2*pi*n/T + k*phi0;

% exp(1j*alpha*(s-beta)^2) * exp(1j*gamma)
alpha = A;
beta = B/(2*A);
gamma = -B^2/(4*A);

t1 = beta-T/2; % min/max t=(s-beta)
t2 = beta+T/2;

xMin = t1*sqrt(abs(alpha))*sqrt(2/pi); % min/max x=t*sqrt(alpha)
xMax = t2*sqrt(abs(alpha))*sqrt(2/pi);
amp = exp(1j*gamma)*(1/sqrt(alpha))*sqrt(pi/2)*(1/T);

resRe = mfun('FresnelC',xMax)-mfun('FresnelC',xMin);
resIm = sign(alpha)*(mfun('FresnelS',xMax)-mfun('FresnelS',xMin));

res = amp*(resRe + 1j*resIm);
