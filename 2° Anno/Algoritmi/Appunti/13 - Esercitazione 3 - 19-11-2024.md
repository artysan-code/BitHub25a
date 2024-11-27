### Problema 1
Avendo un albero binario T di n nodi e ogni nodo ha:
- valore $val(v)>0$
- colore $col(v)\in\{R,N\}$

Bisogna trovare il valore del cammino rosso di tipo radice-nodo di valore massimo

#### Definizione
Il valore di un cammino e' la somma dei valori dei nodi del cammino

#### Definizione
Un cammino e' rosso se tutti i suoi nodi sono di colore rosso

T viene rappresentato con record e puntatori:

|               P | (v)$\nearrow$   |
| --------------: | :-------------- |
|         val (v) | col(v)          |
| $\swarrow$sx(v) | dx(v)$\searrow$ |
#### Soluzione
MaxRosso(v)
restituisce il valore del cammino rosso di valore massimo di tipo v-discendente di v

- informazione che vengono "dal basso", calcolate rispetto al sottoalbero con radice v;
- possono essere usate per "passare informazioni" al padre di v

```
MaxRosso(v)
if v=null then return 0
if col(v)=N return 0
return val(v)+max{MaxRosso(sx(v)),MaxRosso(dx(v))}
```

complessita':
$O(n)$ dato che effettuiamo solamente una visita

### Problema 2
Avendo un albero binario T di n nodi (rappresentato con record e puntatori) e un intero $h\geq 0$

trovare il numero di nodi di T con profondità almeno h

#### Definizione
la profondità di un nodo e' la distanza (# di archi) dalla radice

