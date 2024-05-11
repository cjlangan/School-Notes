# COMP 2080 Summer 2024 - Assignment 1
- **Name**: Connor Langan
- **Student Number**: 7993941

## Question 1
$$\forall{p}\in \mathbb{N}\quad \forall{q}\in \mathbb{N}\quad p\neq q \ (P(p) \ \land \ P(q)) \implies \forall r \in \mathbb{N}\ ((\frac{q^p-1}{q-1})\neq (\frac{p^q-1}{p-1}) \times r)$$

## Question 2

### (a)

#### Proof:
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

#### Proof:
(1) We wish to prove $\forall x \in \mathbb{R},\space \forall y \in \mathbb{R}\space ((y-x > 1)\implies (\exists n \in \mathbb{Z}\space (x < n < y)))$. 

(2) Let $x,y \in \mathbb{R}$ be arbitrary, and assume that $y-x > 1$.

(3) Notice that either $x \not \in \mathbb{Z}$, or $x \in \mathbb{Z}$. We proceed by cases.

(4) Note that from (2), $y - x > 1 \implies x+1 < y$

(5) Case 1: If $x \not \in \mathbb{Z}$, let $n = \lceil x \rceil$. 

Now, $n= \lceil x \rceil > x\space$, so, $\space n > x$. And by (4), $n = \lceil x \rceil < x+1 < y$. So, $n < y$. 

Therefore, $x < n < y$, as needed.

(6) Case 2: If $x \in \mathbb{Z}$, let $n= x+1$. 

Now, $n=x+1 > x\space$, so, $\space n > x$. And by (4), $n=x+1 < y\space$, so $\space n < y$.

Therefore, $x < n < y$, as needed.

(7) In either case, since $x$ and $y$ were arbitrary, $x < n < y$, as needed. Thus, 
$$\forall x \in \mathbb{R},\space \forall y \in \mathbb{R}\space ((y-x > 1)\implies (\exists n \in \mathbb{Z}\space (x < n < y)))$$

## Question 3

#### Proof:
(1) Let P(n) be the predicate that $\sum_{k=2}^n \frac{1}{k^2-1} = \frac{3}{4} - \frac{2n+1}{2n(n+1)}$. We will prove using mathematical induction that $\forall n \in \mathbb{N},\space n \geq 2$, P(n).

(2) Base Case: When $n=2$, we have
$$\sum_{k=2}^2 \frac{1}{k^2-1} = \frac{1}{2^2-1} = \frac{1}{3}\quad and\quad \frac{3}{4}-\frac{2(2)+1}{2(2)(2+1)} = \frac{3}{4}-\frac{5}{12} = \frac{9}{12}-\frac{5}{12} = \frac{1}{3}$$

Thus, P(2) is true.

(3) Induction Step: Let $n \in \mathbb{N}$ be arbitrary and assume P(n). We will prove P(n+1), which states
$$\sum_{k=2}^{n+1} \frac{1}{k^2-1} = \frac{3}{4} - \frac{2(n+1)+1}{2(n+1)((n+1)+1)}$$

(4) We have,
$$\sum_{k=2}^{n+1} \frac{1}{k^2-1} = (\sum_{k=2}^n \frac{1}{k^2-1})\space+\frac{1}{(n+2)^2-1}$$
$$= \frac{3}{4} - \frac{2n+1}{2n(n+1)}+\frac{1}{(n+2)^2-1}\quad , by\quad I.H$$
$$= \frac{3}{4} - \frac{2n+1}{2n^2+2n}+\frac{1}{n^2+2n}$$
$$= \frac{3}{4} - \frac{2n+1}{2n(n+1)}+\frac{1}{n(n+2)}$$
$$= \frac{3}{4} - \frac{(2n+1)(n+2)}{2n(n+1)(n+2)}+\frac{2(n+1)}{2n(n+1)(n+2)}$$
$$= \frac{3}{4} - \frac{2n^2+5n+2}{2n(n+1)(n+2)}+\frac{2(n+1)}{2n(n+1)(n+2)}$$
$$= \frac{3}{4} + \frac{-2n^2-5n-2 + 2n + 2}{2n(n+1)(n+2)}$$
$$= \frac{3}{4} + \frac{-2n^2-3n}{2n(n+1)(n+2)}$$
$$= \frac{3}{4} - \frac{2n+3}{2(n+1)(n+2)}$$
$$= \frac{3}{4} - \frac{2(n+1)+1}{2(n+1)((n+1)+2)}$$
as needed.

(5) Thus, since P(2) is true, and P(n) $\implies$ P(n+1), by the principle of mathematical induction, we conclude that $\forall n \geq 2,\space n \in \mathbb{N}$, P(n).

## Question 4

#### Proof:
(1) Define the sequence of numbers $a_n$ for all positive integers as follows:
$$a_1=-10,\space a_2=2, \space and \quad \forall n \geq 3, \space a_n=a_{n-1}+12a_{n-2}$$

(2) Let P(n) be the predicate that $a_n=2(-3)^n-4^n$. We will prove using strong mathematical induction that $\forall n \in \mathbb{N}$, P(n).

(3) Base Case: When $n=1$ we have $a_1=-10$ and $2(-3)^1-4^1 = -10$. Thus P(1) is true.

(4) Base Case: When $n=2$ we have $a_2=2$ and $2(-3)^2-4^2 = 18-16=2$. Thus P(2) is true.

(5) Induction Step: Let $n \geq 2$ be arbitrary, and assume that $\forall k \leq n$, 
$$a_{k}=2(-3)^{k}-4^{k}$$
We will prove P(n+1), which states
$$a_{n+1}=2(-3)^{n+1}-4^{n+1}$$

(6) We have, 
$$a_{n+1} = a_{n}+12a_{n-1}$$
$$a_{n+1} = 2(-3)^{n}-4^{n}+12(2(-3)^{n-1}-4^{n-1})\quad , by\quad I.H$$
$$a_{n+1} = 2(-3)^{n}-4^{n}+24(-3)^{n-1}-12(4)^{n-1}$$
$$a_{n+1} = 2(-3)^{n}-4^{n}-8(-3)^{n}-3(4)^{n}$$
$$a_{n+1} = -6(-3)^{n}-4(4)^{n}$$
$$a_{n+1} = 2(-3)^{n+1}-4^{n+1}$$
as needed.

(7) Thus, since P(1) and P(2) are true, and $\forall k \leq n$, P(k) $\implies$ P(n+1), by the principle of strong mathematical induction, we conclude that $\forall n \in \mathbb{N}, \space a_n = 2(-3)^n-4^n$.
