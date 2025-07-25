# Fondamenti e vettori
L'algebra lineare non è altro che la **fusione** tra l'algebra (la manipolazione di equazioni e sistemi) e la geometria (lo studio di punti, rette, piani e forme nello spazio). Ogni concetto algebrico ha una controparte geometrica e viceversa.
## Vettori, operazioni, coordinate
Somma di vettori: $$(v+w)=(v_{x},v_{y})+(w_{x},w_{y})=(v_{x}+w_{x}),(v_{y}+w_{y})$$
Moltiplicazione per scalare$: $$k\cdot v=k\cdot(v_{x},v_{y})=(k\cdot v_{x},k\cdot v_{y})$$
## Equazioni di rette e piani
### Forma parametrica
Retta: $$P(t)=P_{0}+t\cdot v$$
Parti da un punto noto della retta ($P_{0}$), e muoviti lungo la direzione del vettore $v$. Il parametro $t$ ti dice "quanti passi" fare in quella direzione.

Piano: $$P(s,t)=P_{0}+s\cdot v+t\cdot w$$
Parti da un punto $P_{0}$ e sei libero di muoverti lungo due direzioni indipendenti ($v$ e $w$)

### Forma Cartesiana

Retta in $\mathrm{R}^{2}$: $$ax + by + c = 0$$
Piano in $\mathrm{R}^{3}$: $$ax + by + cz + d = 0$$
L'insieme di tutti i punti $(x, y, z)$  le cui coordinate soddisfano questa singola equazione. Il vettore $n = (a, b, c)$ è il **vettore normale** (perpendicolare) al piano


Rappresentano due filosofie opposte per descrivere un oggetto.
- **Parametrica (generativa):** Ti do gli ingredienti $(P_{0}, v, w)$ e le istruzioni per _costruire_ tutti i punti. È una visione dall'interno.
- **Cartesiana (restrittiva):** Ti do una regola $(ax + ... + d = 0)$ e verifico se un punto appartiene all'insieme o no. È una visione dall'esterno.
- **Connessione Profonda:** L'equazione cartesiana di un piano $a(x-x₀) + b(y-y₀) + c(z-z₀) = 0$ è equivalente a dire che il prodotto scalare tra il vettore normale $n = (a, b, c)$ e un qualsiasi vettore $(P - P₀)$ che giace sul piano è zero: $n ⋅ (P - P₀) = 0$. Questo significa che sono perpendicolari.

# Spazi vettoriali
L'obiettivo qui è generalizzare le regole che abbiamo visto in $\mathrm{R}^{2}$ e $\mathrm{R}^{3}$ a contesti molto più ampi.
## Spazio e sottospazio
### Spazio vettoriale
È un insieme $V$ di vettori su cui sono definite due operazioni (somma tra vettori e prodotto per scalare) che rispettano 8 **regole fondamentali**: 
- Chiusura della Somma: 
  Se $u$ e $v$ sono in $V$, allora anche la loro somma $u+v$ deve essere in$V$.
- Proprietà Associativa: 
  $(u+v)+w=u+(v+w)$
- Proprietà Commutativa: 
  $u+v=v+u$
- Esistenza dell'Elemento Neutro (Vettore Nullo):
  Esiste un vettore speciale, il **vettore nullo** $0V$​, tale che per ogni vettore $v$ in $V$ si ha: $v+0V​=v$.
- Esistenza dell'Opposto:
  Per ogni vettore $v$ in $V$, esiste un vettore opposto $−v$ tale che: $v+(−v)=0V$​.
- Chiusura del Prodotto per Scalare:
  Se $v$ è in $V$ e $k$ è uno scalare, allora anche il prodotto $k⋅v$ deve essere in $V$.
- Proprietà Distributiva (rispetto alla somma di vettori):
  $k⋅(u+v)=k⋅u+k⋅v$
- Proprietà Distributiva (rispetto alla somma di scalari):
  $(k+h)⋅v=k⋅v+h⋅v$
- Proprietà Associativa (del prodotto per scalare):
  $(k⋅h)⋅v=k⋅(h⋅v)$
- Esistenza dell'Elemento Neutro della Moltiplicazione:
  Lo scalare 1 agisce come elemento neutro: $1⋅v=v$.

### Sottospazio vettoriale
È un sottoinsieme $W$ di uno spazio vettoriale $V$ che è a sua volta uno spazio vettoriale. Per verificarlo, non devi controllare tutti gli 8 assiomi. Bastano 3 condizioni:
- Contiene il vettore nullo:
  $0\in W$
- Chiuso rispetto alla somma:
  Se $w_{1},w_{2}\in W$, allora $w_{1}+w_{2}\in W$.
- Chiuso rispetto al prodotto per scalare:
  Se $w\in W$ e $k$ è uno scalare, allora $k\cdot w\in W$.

## Combinazioni lineari e sottospazio generato
### Combinazione lineare
È una somma pesata di vettori. Dati i vettori $v_{1},v_{2},\dots,v_{k}$ e gli scalari $c_{1},c_{2},\dots,c_{k}$, una loro combinazione lineare è:$$w=c_{1}v_{1}+c_{2}v_{2}+\dots+c_{k}v_{k}$$
### Sottospazio generato (Span)
Lo $Span(v_{1},\dots,v_{k})$ è l'insieme di **tutte le possibili** combinazioni lineari che puoi formare con i vettori $v_{1},\dots,v_{k}$.
È l'insieme di tutti i punti che puoi raggiungere partendo dall'origine e potendoti muovere solo nelle direzioni $v_{1},\dots,v_{k}$.
Lo Span di un vettore non nullo è la **retta** passante per l'origine con quella direzione.
Lo Span di due vettori non paralleli è il **piano** passante per l'origine che li contiene.

>**Teorema chiave:** 
>Lo $Span(v_{1},\dots,v_{k})$ è sempre un **sottospazio vettoriale**.