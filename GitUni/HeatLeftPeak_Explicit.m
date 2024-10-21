function HeatLeftPeak_Explicit
  % Parametri fisici
  eta = 0.30;  L = 0.5; kappa = 10;
  % Delta x, Delta t
  N   = 101;  
  x   = linspace(0.0,L,N); 
  dx  = x(2)-x(1);
  dt  = (eta*dx^2)/kappa;
  % Impulso di calore iniziale
  T0           = 20;
  DeltaT       = 80;
  T            = ones(1,N)*T0;
  T(1)         = T0+DeltaT;
  % Evoluzione temporale
  t    = 0; tend = 1e-3;
  while t<tend
    plot(x,T);
    % T_0 = ... (per aggiornare T(1))
    % Update T(1:N-1), attenzione:
    % - conflitto tra aggiornamento T(1) e 
    %   T(2:N-1)
    % Metodo esplicito
    % Salvataggio t e T (per un punto x_term della sbarra) e loro disegnp
    drawnow limitrate nocallbacks
    t = t+dt;
  end
  % Grafico T(x_term) vs t
end