function StringDev
  % Parametri fisici
  L = 10;
  % Delta x, Delta t
  N   = 101;  
  x   = linspace(0.0,L,N); 
  dx  = x(2)-x(1);
  dt  = 0.1;
  v=dx/dt;
  %caso densitÃ  costante e vp costante
  vp=v*10;
  %caso densitÃ  variabile
  %densitÃ  variabile
  %dens(1:N)=1+x(1:N);   
  %velocitÃ  nel caso di densitÃ  variabile
  %vp(1:N)=v*30*(T./dens(1:N)).^0.5; 


  % Impulso iniziale
  %gaussiana al centro
  %P=3*exp(-0.5 * ((x - 0.5*L).^2) /((2*0.05*L).^2));
  %gaussiana non centrata al centro
  P=3*exp(-0.5 * ((x - 0.2*L).^2) /((2*0.05*L).^2));  
  

  % caso densitÃ  costante
  Pn(2:N-1)=P(2:N-1)+(v*v)/(2*(vp*vp))*(P(1:N-2)+P(3:N)-2*P(2:N-1));  
  % caso di densitÃ  variabile
  %Pn(2:N-1)=P(2:N-1)+(v.^2)./(2*(vp(2:N-1).^2)).*(P(1:N-2)+P(3:N)-2*P(2:N-1));
  
  Pn(1)=0;
  Pn(N)=0;
  
  % Evoluzione temporale
  tempo=[];
  step = 1 ;
  
  % Evoluzione temporale
  t    = 0; tend = 10000;
  while t<tend
    
    plot(x,P);
    axis equal;
    tempo(step)=t;
    % caso di densitÃ  costante
    Y(2:N-1)=2*Pn(2:N-1)-P(2:N-1)+(v*v)/(2*(vp*vp))*(Pn(1:N-2)+Pn(3:N)-2*Pn(2:N-1));
    % caso di densitÃ  variabile
    %Y(2:N-1)=2*Pn(2:N-1)-P(2:N-1)+(v^2)./(2*(vp(2:N-1).^2)).*(Pn(1:N-2)+Pn(3:N)-2*Pn(2:N-1));
   
    Y(1)=0;
    Y(N)=0;
    P(1:N)=Pn(1:N);
    Pn(1:N)=Y(1:N);

    drawnow limitrate nocallbacks
  
    t = t+dt;
    step=step+1;
  end
end