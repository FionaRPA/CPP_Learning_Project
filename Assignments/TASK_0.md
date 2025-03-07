# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.

> *La méthode responsable des inputs est void TowerSimulation::create_keystrokes() const.*  

Sur quelle touche faut-il appuyer pour ajouter un avion ?

> *Pour ajouter un avion, il faut appuyer sur la touche `C`.*  

Comment faire pour quitter le programme ?

> *Pour quitter le programme, il faut appuyer sur la touche `X` ou  `Q`.*  

A quoi sert la touche `F` ?

> *La touche `F` sert à mettre ou à enlever la fenêtre du mode plein écran.*  

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?

> *L'avion atterit, il va sur la case blanche, attend et redécole puis il vole en attendant d'effectuer une nouvelle fois ses opérations en boucle.*  

Quelles informations s'affichent dans la console ?

> *Dans la console, on voit le nom de l'avion qui atterit, lorsque qu'il arrive à sa base, lorsqu'il est près à repartir et lorsqu'il a décollé.*  

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

> *Lorsque l'on lance quatres avions, on voit qu'ils ne peuvent aller que trois par trois sur le plateau vu qu'il n'y a que trois terminaux. En attendant qu'il y ait de la place, il continue de tourner autour du plateau.*  
  
    
    
## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.
- AircraftType → Classe représentant les différents types d’avions et leur caractéristiques.
- Aircraft → Classe qui représente un avion. Il pourra être afficher et il pourra bouger.
- Airport → Classe qui gère l'aéroport avec son AirportType, ses terminals et sa tower.
- AirportType → Classe qui contient tout les information sur un aéroport.
- Config → Classe qui contient toute les configurations du programme.
- Geometry → Classe représentant les calculs géométriques nécessaires pour le bon fonctionnement du programme.
- Runway → Classe représentant les pistes de décollage et d’atterrissage.
- Terminal → Classe qui gère le terminal, stocke l'avion courant qu'il a et le supprime lorsqu'il s'en
va, il peut contenir un avion à la fois maximum.
- TowerSimuation → Classe qui s'occupe de simuler notre programme avec la création des aéroports, des avions…
- Tower → Classe qui représente le comportement de la tour de contrôle. Gérer si un avion est atterrit, s’il peut atterrir.
- Waypoint → Classe qui représente les points de cheminements. Permet de savoir si un avion est dans les airs ou dans un terminal.


Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.

- `Tower`
    - WaypointQueue get_instructions(Aircraft& aircraft);
    Donne les instructions en fonctions de ou est l'avion et de ce qu'il veut faire.
    - void arrived_at_terminal(const Aircraft& aircraft);
    Permet de lancer le service lorsque l'avion arrive sur un terminal.

- `Aircaft`
    - const std::string& get_flight_num() const;
    Permet de récupérer le numéro de vol de l'avion.
    - float distance_to(const Point3D& p) const;
    Permet de calculer la distance entre le point p en paramètre et la positionde l'avion.
    - void display() const override;
    Permet d'afficher l'avion.
    - void move() override;  
    Permet de s'occuper du déplacement en fonction de ce qu'il fait ou ce qu'il peut faire.

- `Airport`
    - Tower& get_tower();
    Permet de récupérer la tour qui s'occupe de l'aéroport.
    - void display() const override;
    Permet d'afficher l'aéroport.void move() override;  
    Appelle la fonction move pour chacun des terminals de l'aéroport.

- `Terminal`
    - bool in_use() const;
    Permet de voir si il y a un avion sur le terminal ou si il est libre.
    - bool is_servicing() const;
    Permet de savoir si un terminal est en service.
    - void assign_craft(const Aircraft& aircraft);
    Permet d'assigner un avion à un terminal.
    - void start_service(const Aircraft& aircraft);
    Fonction qui indique le démarage du service d'un avion et initialise la progression du serive à 0.
    - void finish_service();
    Permet de libérer a place s'il il n'y a plus d'avion dans le terminal et d'anoncer avec un message que le service est fini pour l'avion qui vient de partir.
    - void move() override;
    Cette fonction avance le service de l'avion.


Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?  
> *Les classes impliqués dans la génération du chemin d'avion sont Aircraft, Tower et Waypoint. La
fonction qui gère le chemin de l'avion est Tower::get_instructions(Aircraft& aircraft), donc toute les
fonctions appelé dedans gère le déplacement d'un avion.*

Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.
> *using WaypointQueue = std::deque<Waypoint>;
Le conteneur utilisé pour représenter les chemins est std::deque car les opérations utilisées sont en
complexités constantes.*

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

2) Identifiez quelle variable contrôle le framerate de la simulation.\
Le framerate correspond au temps de rafraichissement du programme, c'est-à-dire le nombre de fois où les éléments du programme seront mis à jour (ajout de nouvel avion à la simulation, déplacement, etc) en une seconde.\
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Assurez-vous qu'à la place, il soit supprimé de la `move_queue`.\
Pour tester, il suffit de dézoomer et de vérifier que les avions suffisament éloignés ne bougent plus.
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.\
Essayez maintenant de supprimer complètement l'avion du programme lorsque vous le retirez de la `move_queue`.\
En dézoomant, vous devriez maintenant constater que les avions disparaissent maintenant de l'écran.

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference constante ?
Pourquoi n'est-il pas possible d'éviter la copie du `Point3D` passé en paramètre ?

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
