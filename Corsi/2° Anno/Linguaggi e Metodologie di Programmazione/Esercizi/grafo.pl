link(a,b).
link(b,c).
link(a,e).
link(d,e).
link(c,d).
link(f,e).


# Passo base
path(A,B):-
	link(X,Y).

# Passo induttivo
path(A,B):-
	link(A, Z),
	path(Z, B).
