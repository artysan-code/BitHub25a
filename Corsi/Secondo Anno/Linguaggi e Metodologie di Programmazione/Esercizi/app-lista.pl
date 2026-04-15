appartiene(H,[H|_]).
appartiene(H,[_|T]):-
	appartiene(H,T).

concatenata([],L2,L2).
concatenata([E|T1],L2,[E|T12]):-
	contatenata(T1,L2,T12).

rivoltata(L,RL).
