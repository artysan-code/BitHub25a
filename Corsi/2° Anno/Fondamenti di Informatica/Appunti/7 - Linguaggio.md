Un linguaggio L è un insieme di parole x che può anche semplicemente essere l’alfabeto $\{0,1\}*$

$L={𝑥∈{0,1}∗:𝑥=𝑦𝑦 𝑐𝑜𝑛 𝑦∈{0,1}∗}$

LÍ {0,1}*

L Í Σ∗ è deciso da T se:

∀𝑥∈Σ∗ 𝑜𝑇(𝑥)= 𝑞𝑎𝑠𝑒 𝑥∈𝐿

𝑞𝑟𝑠𝑒 𝑥∉𝐿

LÍΣ∗ è accettato da 𝑇𝐼 se:

∀𝑥∈Σ∗[𝑜𝑇(𝑥)=𝑞𝑎<− >𝑥∈𝐿]

L è decidibile se $ T : L è deciso da T

L è accettabile se $ 𝑇𝐼 : L è accettabile da 𝑇𝐼

Quindi se chiamiamo con D l’insieme dei linguaggi decidibili e A quelli accettabili allora:

𝐷Í 𝐴

𝐿𝑝𝑝𝑎𝑙,𝐿𝑑𝑝𝑎𝑙,𝐿𝑝𝑎𝑙,𝐿𝑑𝑜𝑝𝑝𝑖𝑎∈𝐷 sappiamo che sono decidibili in quanto abbiamo visto che terminavano SEMPRE in 𝑞𝑎 o in 𝑞𝑟

𝐿𝑝𝑎𝑙→𝑇𝑝𝑎𝑙 prendiamo una sua quintupla <𝑞𝑎𝐼,𝑏,𝑏,𝑞𝑟,𝐹>

<𝑞𝑏𝐼,𝑎,𝑎,𝑞𝑟,𝐹>

Se prendiamo la prima e la modifichiamo:

<𝑞𝑎𝐼,𝑏,𝑏,𝑞𝑎𝐼,𝐹>

Per mandarla in loop

Ora invece di decidere il linguaggio lo accetterà, in quanto in ALCUNI CASI, non terminerà, mentre in altri si (<𝑞𝑏𝐼,𝑎,𝑎,𝑞𝑟,𝐹>)

Dunque, ora 𝐿𝑝𝑎𝑙 sarà decidibile in quanto mi basta anche solo che esista una macchina che lo rende tale.

𝐿∈Σ∗,𝐿𝑐Í Σ∗ 𝐿𝑐={𝑥∈Σ∗:𝑥∉𝐿}

Dove 𝐿𝑐 è parte di ciò che è incluso in Σ∗ ma non in L

THM (teorema):

L è decidibile se e solo se L è accettabile e 𝐿𝑐 è accettabile

Dim. 1:

L è decidibile à $ 𝑇∶∀𝑥∈Σ∗ 𝑜𝑇(𝑥)= 𝑞𝑎𝑠𝑒 𝑥∈𝐿

𝑞𝑟𝑠𝑒 𝑥∉𝐿

Deduciamo:

1. T accetta L à L è accettabile

2. Costruiamo 𝑇𝑐che con input x Î Σ∗: 𝑇𝑐=<Σ,Ω,𝜔0,{𝜔𝑎,𝜔𝑟},𝑃𝑐>

Fase 1. Dallo stato 𝜔0 simula T(x) in 𝑞𝑎 𝑜 𝑞𝑟 Ω={𝜔0,𝜔𝑎,𝜔𝑟,𝑞𝑎,𝑞𝑟}

Fase 2. Dallo stato 𝑞𝑎 termina in 𝜔𝑟

Dallo stato 𝑞𝑟 termina in 𝜔𝑎

Dim. 2:

L è accettabile e 𝐿𝑐 accettabile

$ 𝑇:∀𝑥∈Σ∗[𝑇=𝑞𝑎<− > 𝑥∈𝐿] $𝑇𝑐:𝑥∈Σ∗[𝑇𝑐(𝑥)=𝑞𝑎<− >𝑥∈𝐿𝑐]

Costruiamo 𝑇′′ : con input 𝑥∈Σ∗

Fase 1. Simula T(x) : se termina in 𝑞𝑎allora accetta

Fase 2. Simula 𝑇𝑐(𝑥): se termina in 𝑞𝑎 allora rigetta

Questo però non è corretto in quanto quando accetta non si saprà cosa deve fare.

È quindi meglio fare una simulazione a scatola aperta:

Fase 1. Simula una ISTRUZIONE di T(x): se porta in 𝑞𝑎-> accetta, altrimenti fase 2

Fase 2. Simula una ISTRUZIONE di 𝑇𝑐(𝑥) se porta in 𝑞𝑎-> rigetta, altrimenti fase 1

In questo modo crea un loop tra fase 1 e 2 fino a quando una delle istruzioni simulata in una delle due fasi, accetta

Esercizio 𝐿1 ∩𝐿2, 𝐿1 ∪𝐿2

f : Σ1∗→Σ2∗

f è totale se è definita ∀𝑥∈Σ1∗

se ∀𝑥∈Σ1∗[∃𝑓(𝑥)]

f è calcolabile se $ T trasduttore:

∀𝑥∈Σ1∗,:𝑓(𝑥) se e soltanto se f(x) definita

[𝑜𝑇(𝑥)=𝑓(𝑥)]

Dato 𝐿⊆Σ∗

∀𝑥∈Σ∗ Χ𝐿(𝑥)=1 𝑠𝑒 𝑥∈𝐿

0 𝑠𝑒 𝑥∉𝐿

Χ𝐿:Σ∗→{0,1}

Se ∃𝑇χ⇒∃𝑇𝐿

Data: f : Σ1∗→ Σ2∗

𝐿𝑓={(𝑥,𝑦)∈Σ1∗ ×Σ2∗:𝑦=𝑓(𝑥)}

Se f è calcolabile ⇒∃𝑇𝑓:∀𝑥∶∃𝑓(𝑥)[ 𝑜𝑇(𝑥)=𝑓(𝑥)]

Costruisco 𝑇𝐿: con input (x,y)

1. Simula 𝑇𝑓(𝑥) scrivendo f(x) sul secondo nastro

2. Se f(x) = y allora termina in 𝑞𝑎

Altrimenti termina in 𝑞𝑟

Quindi questa macchina accetta L

Se f è calcolabile e totale ⇒∃𝑇𝑓:∀𝑥∶[ 𝑜𝑇(𝑥)=𝑓(𝑥)]

Costruisco 𝑇𝐿: con input (x,y)

1. Simula 𝑇𝑓(𝑥) scrivendo f(x) sul secondo nastro

2. Se f(x) = y allora termina in 𝑞𝑎

Altrimenti termina in 𝑞𝑟

Quindi questa macchina decide L

Se 𝐿𝑓 è decidibile ⇒∃𝑇:∀(𝑥,𝑦)∈Σ1∗×Σ2∗[ 𝑜𝑇(𝑥,𝑦)=𝑞𝑎𝑠𝑒 𝑦=𝑓(𝑥)

𝑞𝑟 altrimenti

Costruisco 𝑇𝑓: con input x su N1

Su N2 ß 1

Su N3 ß 𝑆11−𝑆21…−𝑆𝑘1

𝑓𝑜𝑟 𝑦 scritta su N3 simuliamo 𝑇𝐿(𝑥,𝑦): se 𝑞𝑎⇒ scriviamo y sul nastro di output e

terminiamo

Altrimenti N2 +1 e si torna su N3

Quindi avuto l’input x, inizierò scrivendo su N2 0, poi 1 e scriverò tutte le parole di lunghezza N2 su N3; quindi, se termino in 𝑞𝑎allora scriverò y su nastro di output, altrimenti ritorna a N2 e aumenterà di 1 il valore e continuerà.

Quindi se f è definita in x, prima o poi si troverà la y e prima o poi terminerò, il problema è che se f non è definita la computazione potrebbe mai terminare.