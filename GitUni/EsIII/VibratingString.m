function VibratingString
  % definition of the system
  v = 10; % differential equation parameter
  L = 10;  
  N = 100;
  x = linspace(0.0,L,N);
  dx  = x(2)-x(1);
  dt = 0.7 * (dx/v);

  % omogeneous density:
  v1 = x*0 + dx/dt;
  % non omogeneous density. To make it simple, my implementation of choice has just two distinct density values
  %{
  v1 = x*0;
  v1(1:50) = dx/dt;
  v1(50:N) = 0.5*dx/dt;
  %}

  U = x*0; %trivial non perturbation case
  
  % initialization of the perturbation: non origin centered gaussian
  %{
  center = 30; % in percentage points of the whole lenght
  U = 3*exp(-0.5 * ((x - (center/100)*L).^2) /((2*0.05*L).^2));
  %}
  % initialization of the perturbation: sinewave
  %{
  n_of_peaks = 2;
  U = 3*sin((x*n_of_peaks*pi)/L); 
  %}
  % initialization of auxiliary arrays
  U_prec = U;
  U_new = U*0;

  % omogeneous density case
  U(2:N-1)=U_prec(2:N-1)+(v*v)./(2*(v1(2:N-1).*v1(2:N-1))).*(U_prec(1:N-2)+U_prec(3:N)-2*U_prec(2:N-1));

  t    = 0; tend = 10;
  while t<tend
    U_new(2:N-1)=2*U(2:N-1)-U_prec(2:N-1)+(v*v)./(2*(v1(2:N-1).*v1(2:N-1))).*(U(1:N-2)+U(3:N)-2*U(2:N-1));
    plot(x,U_new);
    axis equal;
    drawnow limitrate nocallbacks;
    U_prec = U;
    U = U_new;
    t = t+dt;
  end
end