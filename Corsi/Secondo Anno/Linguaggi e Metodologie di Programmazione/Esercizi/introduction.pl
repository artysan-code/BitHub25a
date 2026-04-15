persona(mario).
persona(maria).
persona(giacomo).
persona(giulia).
persona('Daria').
persona(giorgio).

figlio(mario, giulia).
figlio(maria, giulia).
figlio(giulia, giacomo).
figlio(maria, maria).
figlio(mario, giorgio).

sofratm(F1, F2):-
	figlio(Genitore, F1),
	figlio(Genitore, F2).
