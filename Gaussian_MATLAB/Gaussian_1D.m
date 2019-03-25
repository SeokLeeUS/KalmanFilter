mu  =2;
sigma_sq = 4;

sampleTime = 0.001;
t = 0:sampleTime:20;
y = zeros(length(t),1);
z = zeros(length(t),1);
nu  = 20;
rho_sq = 4;
%mu_p = zeros(length(t),1);
mu_p =1/(sigma_sq+rho_sq)*(rho_sq*mu+sigma_sq*nu);
sigma_sq_p = 1/((1/sigma_sq)+(1/rho_sq));
new_gaussian = zeros(length(t),1);
for i =1:length(t)

    y(i) = (1/sqrt((2*pi*sigma_sq)))*exp(-0.5*(t(i)-mu)^2/sigma_sq);
    z(i) = (1/sqrt((2*pi*rho_sq)))*exp(-0.5*(t(i)-nu)^2/rho_sq);
    new_gaussian(i) = (1/sqrt((2*pi*sigma_sq_p)))*exp(-0.5*(t(i)-mu_p)^2/sigma_sq_p);
   
    
       
end

figure (1)

plot(t,y)
hold on
plot(t,z)
plot(t,new_gaussian)



    