# TD 2 à 4 Prévoir la pollution atmosphérique : résolution d'équations différentielles ordinaires

Contexte et objectifs du TD : voir [Intro TD simulation équation d'advection](TD2-5_intro.md)

Nous proposons d'utiliser ce contexte comme fil rouge de nos séances de TD.

# TD 3 Mise en place de l'équation et du schéma numérique

Nous allons maintenant résoudre numériquement l'équation d'advection linéaire :
$\partial_t u+a \partial_x u = 0$ en calculant notre solution discrète sur notre discrétisation en temps créée au TD2 : à chaque pas de temps $u_i^n$, $u_i^n\approx u(x_i,t_n)$. Nous aurons trois étapes pour pouvoir réaliser cette résolution :

- créer une classe pour stocker la solution discrète $u_i^n$
- calculer une condition initiale pour notre problème
- coder notre schéma numérique (un schéma décentré pour commencer) dans notre classe `Equation`

Dans un premier temps le schéma numérique sera directement intégré dans la classe `Equation`.

Dans un deuxième temps, nous pourrons rendre le code plus générique, nous pourrons le rendre indépendant.

## 3.1 Classe `Variable` pour stocker les $u_i$

Pour la discrétisation en espace, vous créerez une classe `Variable` qui vous permettra de stocker et d'accéder au tableau des valeurs de $u_i$. Vous utiliserez par exemple un `std::vector` pour stocker les valeurs dans cette classe. Cette classe nous permettra d'accéder à $u_i$ à partir de l'index $i$ : $u_i = variable[i]$. Cette classe aura besoin de stocker un pointeur vers `IMesh`.

- Le `std::vector` doit être dimensionné et initialisé dans le constructeur de `Variable`. Pour connaître la taille du maillage en $x$, vous ajouterez une méthode `IMesh::x_size()`.
- Afin de pouvoir écrire `u_i = variable[i]`, vous créerez un `operator[]` dans la classe qui prendra en argument l'index $i$ et  vous retournera une référence vers le $i^{ème}$ élément du tableau.

Pour la discrétisation en temps, nous n'avons besoin que de stocker les instants $n$ et $n+1$, nous créerons pour cela deux variables `u_n` et `u_np1` ; `u_np1` étant recopié dans `u_n` en fin d'itération. Dans la méthode `solve` de votre `Problem`, vous instancierez ces deux variables `u_n` et `u_np1`, instances de la classe `Variable`.

## 3.2 Calcul de la condition initiale

Nous allons calculer l'advection d'une Gaussienne. Il vous faudra donc coder cette Gaussienne afin d'initialiser $u_n$ en tout point de l'espace. Je vous rappelle la formule de la Gaussienne :

- $f(x) = \dfrac{1}{\sigma\sqrt{2\pi}}\exp^{-\dfrac{(x-\mu)^2}{2\sigma^2}}$

Afin de calculer la condition initiale, vous créerez une méthode `compute_initial_condition` dans `Equation`. Cette méthode prendra en argument la classe `Variable` ainsi que le maillage `IMesh`. Vous bouclerez sur tous les pas d'espace afin de calculer $u_i = f(x_i)$. Vous aurez donc besoin d'une nouvelle méthode dans `IMesh` qui retourne la valeur de $x_i$ en fonction de $i$ : `IMesh::x_i(int i)`. Vous choisirez comme paramètre de la Gaussienne :

- $\mu = \dfrac{x_{max}-x_{min}}{2}$
- $\sigma = 10 \ \Delta x$

Vous appellerez cette méthode juste avant votre boucle en temps, dans la méthode `solve` de votre `Problem`, en lui passant votre maillage et votre variable $u_n$. Pour utiliser $\pi = 4 \arctan(1)$, la fonction $\arctan$ étant disponible dans l'entête `cmath` (fonction `atan`).

## 3.3 Intégration du schéma numérique dans la classe `Equation`

Nous allons faire une première version du calcul avec un schéma décentré amont dont je vous rappelle la formule :

- $u^{n+1}_i = u^n_i-a\dfrac{\Delta t}{\Delta x} (u^n_i - u^n_{i-1})$

Cette résolution se fera dans la méthode `Equation::compute` où il faudra donc rajouter en argument les variables `u_n` et `u_np1`.
Vous aurez également besoin de la vitesse d'advection $a$. Vous pourrez la stocker comme donnée membre de la classe `Equation`. Pour la calculer, vous utiliserez la condition CFL que nous avons mentionné en introduction des TDs : pour rappel : $CFL = a\frac{\Delta t}{\Delta x} = 0.5$.

Cette méthode calculera votre solution au temps $t_{n+1}$. Vous n'oublierez pas de remettre à jour `u_n` avec les valeurs de `u_np1` à la fin de l'itération.

## 3.4 Bonus

### 3.4.1 Fonction d'initialisation en paramètre

Afin de pouvoir changer la fonction utilisée en condition initiale, nous allons maintenant la passer en paramètre de la méthode `Equation::compute_initial_condition`. La fonction Gaussienne que nous avons précédemment définie sera maintenant passé en argument.

Pour ce faire, vous pourrez coder la Gaussienne dans une $\lambda$-fonction que vous passerez dans un argument template de `compute_initial_condition`.

### 3.4.2 Séparation de l'équation et du schéma numérique

Nous allons découpler le schéma numérique de l'`Equation` afin de pouvoir tester plusieurs schéma pour la même équation. Pour cela nous allons créer une nouvelle méthode `compute_for_scheme` qui prendra en paramètre template le schéma numérique utilisé.

Il faudra donc maintenant créer une classe `Upwind` pour définir notre schéma décentré amont. Cette classe n'aura pas besoin de contenir de données, elle peut simplement avoir une méthode statique `update` qui prendrait en argument les variables `u_n` et `u_np1`, la vitesse d'advection et la discrétisation `IMesh`. La méthode `Equation::compute_for_scheme` sera template et prendra en argument template le type du schéma :

```c++
m_equation.compute_for_scheme<Upwind>(t,mesh,u_n,u_np1);
```

### 3.4.3 Ajout d'un schéma de Lax-Wendroff

Nous allons maintenant pouvoir ajouter un schéma centré sans modifier la classe `Equation`. Il vous faudra ajouter une classe `LaxWendroff`, sur le même modèle que la classe `Upwind`. La méthode `update` de cette nouvelle classe devra permettre de calculer le schéma centré dont nous rappelons la formule :
- $u^{n+1}_i = u^n_i-a\dfrac{\Delta t}{2\Delta x} (u^n_{i+1} - u^n_{i-1}) + a^2 \dfrac{\Delta t^2}{2\Delta x^2}(u^n_{i+1}-2u^n_i+u^n_{i-1})$

### 3.4.4 Rendre le code plus robuste via les concepts

Il est enfin possible de rendre votre code plus robuste en vérifiant, là où vous utilisez des paramètres template, que les objets donnés en paramètre template remplissent le bon contrat, grâce aux **`concept`** introduit en C++20. Vous pouvez vérifier que la classe donnée comme schéma numérique de la méthode `compute` possède bien une méthode `update` et que la fonction passée en argument de la méthode `Equation::compute_initial_condition` possède bien un `operator()`. Pour réaliser cet item il vous faudra un compilateur récent (GCC >= 10 ; Clang >= 10). Voir sur  [cpp reference](https://en.cppreference.com/w/cpp/concepts).
