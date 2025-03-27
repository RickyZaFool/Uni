- Elenco tutte le mosse possibili -> n(c)
    # Ogni Atomo a priori puo provare a muoversi in 4 direzioni, ma in realta scarto gia le mosse con sito di destinazione occupato.
- Associo a ogni mossa possibile un peso -> p_i(c)
    # p_i(c) = exp(-frac{E(c')-E(c)}{kBT}) se E(c') > E(c) dove c' sarebbe la configurazione ottenuta facendo la mossa i.
    # p_i(c) = 1 se E(c') < E(c)
- Definisco il peso totale della configurazione c -> P(c) = Sum(p_i(c))
- estraggo un numero tra 0 e P(c) che va a cadere sul pezzettino di segmento corrispondente a una mossa, eseguo quella mossa.