## Question 2

### (a)
(1) We wish to disprove $\exists a > 1,\space \exists M > 0,\space \forall x \in \mathbb{R} (a^x \geq M)$, where $a,M \in \mathbb{R}$. It suffices to prove the negation. Which is:  

$$\forall a > 1,\space \forall M > 0,\space \exists x\ (a^x < M) $$

(2) Let $a,M \in \mathbb{R}$ be arbitrary, such that $a > 1$ and $M > 0$.

(3) Let $x = \log_a(M-1)$

(4) Then we have,

$$a^x = a^{\log_a(M-1)} = M-1 < M$$
$$\implies a^x < M$$

as needed.

(5) Thus, since $a,M \in \mathbb{R}$, were both arbitrary, we conclude that $\forall a > 1,\space \forall M > 0,\space \exists x\ (a^x < M)$. 

### (b)
(1) We wish to prove $\forall x \in \mathbb{R},\space \forall y \in \mathbb{R}\space ((y-x > 1)\implies (\exists n \in \mathbb{Z}\space (x < n < y)))$. 

(2) Let $x,y \in \mathbb{R}$ be arbitrary, and assume that $y-x > 1$.

(3) Let $n = \lfloor \frac{\lceil x+y \rceil}{2}\rfloor,\space n \in \mathbb{Z}$.

(4) By (2), $y-x > 1 \implies y > x+1$.

(5) Now we have, 
$$n=\lfloor \frac{\lceil x+y \rceil}{2}\rfloor$$
$$\geq \lfloor \frac{x+y}{2}\rfloor$$
$$> \lfloor \frac{x + x + 1}{2}\rfloor \quad , by \space (4)$$
$$= \lfloor \frac{2x+1}{2} \rfloor$$
$$= \lceil \frac{2x}{2} \rceil$$
$$= \lceil x \rceil$$
$$\geq x$$
Therefore, $n > x$.

(6) By (2), $y-x > 1 \implies y-1 > x \implies x < y-1$.

(7) Now we have, 
$$n=\lfloor \frac{\lceil x+y \rceil}{2}\rfloor$$
$$\leq \lceil \frac{\lceil x+y \rceil}{2}\rceil$$
$$= \lceil \frac{x+y}{2}\rceil$$
$$< \lceil \frac{y-1+y}{2}\rceil \quad , by \space (6)$$
$$= \lceil \frac{2y-1}{2}\rceil$$
$$= \lfloor \frac{2y}{2} \rfloor$$
$$= \lfloor y \rfloor$$
$$\leq y$$
Therefore, $n < y$.

(8) By (5) and (7) we get $x < n < y$.  Thus, since $x$ and $y$ were arbitrary, we conclude that
$$\forall x \in \mathbb{R},\space \forall y \in \mathbb{R}\space ((y-x > 1)\implies (\exists n \in \mathbb{Z}\space (x < n < y)))$$


