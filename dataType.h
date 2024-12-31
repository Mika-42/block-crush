//
// Created by Matis on 16/12/2024.
//

#ifndef DATATYPE_H
#define DATATYPE_H

/**
 * Cet en-tête permet l'utilisation de 'size_t'
 * qui est un typedef (redéfinition de type) du type
 * 'unsigned long long int' qui correspond à un entier
 * non signé de 64-bits
 */
#include <stddef.h>

/**
 * Cet en-tête permet de connaitre l'extréma d'un type
 */
#include <limits.h>

/**
 * @note	Ici, on utilisera le mot clé 'constexpr' qui est une
 *			nouveauté du C23, il nous permet d'évaluer une constante
 *			à la compilation et non à l'exécution comme le fait 'const'
 *			sa valeur est donc immuable et ne peut être modifiée par une
 *			conversion de type explicite.
 *			Aussi, les variables déclarées 'constexpr' peuvent servir à
 *			déclarer la taille d'un tableau.
 *			De plus, on va préférer 'constexpr' à un 'define' car on obtient
 *			plus de précision sur la constante et le sens qu'elle a dans
 *			le code puisqu'elle est dotée d'un type. De même un 'define'
 *			peut être modifié dans le code en faisant un 'undef' puis en
 *			redéfinissant la macro avec la valeur souhaitée. Cependant, ce
 *			n'est pas le comportement souhaité dans ce cas
 */

/**
 * @var		constexpr size_t MaxPlayers
 *
 * @brief	Constante globale indiquant le nombre maximal de joueurs
 */
constexpr size_t MaxPlayers = 256;

/**
 * @var		constexpr size_t rushModeTimeInterval_s
 *
 * @brief	Constante globale indiquant l'intervalle de temps en  seconde du mode Rush
 */
constexpr size_t rushModeTimeInterval_s = 15; //todo

/**
 * @var		constexpr char Letter[4]
 *
 * @brief	Constante globale représente les lettres possibles dans la grille
 */
constexpr char Letter[4] = "HOAX";

/**
 * @var		constexpr size_t maxRow
 *
 * @brief	Constante globale indiquant le nombre maximal de lignes autorisé
 */
constexpr size_t maxRow = 6;

/**
 * @var		constexpr size_t minRow
 *
 * @brief	Constante globale indiquant le nombre minimal de lignes autorisé
 */
constexpr size_t minRow = 4;

/**
 * @var		constexpr size_t maxCol
 *
 * @brief	Constante globale indiquant le nombre maximal de colonnes autorisé
 */
constexpr size_t maxCol = 12;

/**
 * @var		constexpr size_t minCol
 *
 * @brief	Constante globale indiquant le nombre minimal de colones autorisé
 */
constexpr size_t minCol = 8;


/**
 * @var		constexpr size_t longestSequencePossible
 *
 * @brief	Constante indiquant la plus longue séquence possible dans une grille
 *
 * @note	La plus grande grille possible est du 12x6 donc 72 éléments
 *			Supposons que la grille soit remplie du meme élément alors
 *			la plus grande séquence possible est 72
 *
 *						A B C D E F G H I J K L
 *					   ┏─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┓
 *					 1 │X│X│X│X│X│X│X│X│X│X│X│X│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 2 │X│X│X│X│X│X│X│X│X│X│X│X│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 3 │X│X│X│X│X│X│X│X│X│X│X│X│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 4 │X│X│X│X│X│X│X│X│X│X│X│X│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 5 │X│X│X│X│X│X│X│X│X│X│X│X│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 6 │X│X│X│X│X│X│X│X│X│X│X│X│
 *					   ┗─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┛
 */
constexpr size_t longestSequencePossible = maxCol * maxRow;

/**
 * @var		constexpr size_t maxSequencePossible
 *
 * @brief	Constante indiquant le maximum de séquence possible
 *
 * @note	La plus grande grille possible est du 12x6 donc 72 éléments
 *			Supposons que la grille soit remplie de manière alternée
 *			le maximum de séquences possible est 72 / 2 = 36
 *
 *						A B C D E F G H I J K L
 *					   ┏─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┓
 *					 1 │X│O│X│O│X│O│X│O│X│O│X│O│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 2 │O│X│O│X│O│X│O│X│O│X│O│X│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 3 │X│O│X│O│X│O│X│O│X│O│X│O│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 4 │O│X│O│X│O│X│O│X│O│X│O│X│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 5 │X│O│X│O│X│O│X│O│X│O│X│O│
 *					   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
 *					 6 │O│X│O│X│O│X│O│X│O│X│O│X│
 *					   ┗─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┛
 */
constexpr size_t maxSequencePossible = longestSequencePossible / 2;

/**
 * @note	L'instruction 'typedef' permet de définir un type
 *			de donnée non primitif (différent de char, int, etc.)
 *			dans ce cas précis, il nous permet d'éviter la redondance
 *			du mot 'struct' lors de la définition d'une variable.
 */

/**
 * @brief	Représente des coordonnées 2D
 */
typedef struct {
	 size_t row; /**< Numéro de ligne */
	 size_t col; /**< Numéro de colonne */
} Coordinate;

/**
 * @note	Dans ce projet, on crée des tableaux avec les tailles
 *			maximales possibles afin d'éviter l'allocation dynamique.
 *			Compte tenu de la taille du projet, l'utilisation de
 *			'malloc'/'calloc' et 'free' n'est pas pertinente, car elle
 *			introduit des problèmes dans le code :
 *
 * @note	1. La faille humaine : l'oublie de la libération de la mémoire
 *				après l'allocation est une source d'erreur
 *
 * @note	2. La faille matérielle : il arrive que l'allocation échoue,
 *			ce qui nécessite la prise en compte d'un cas supplémentaire.
 *
 * @note	3. La lisibilité du code : celle-ci se verrait nettement diminuée
 *			à cause des nombreux tests de vérification pour savoir si on ne
 *			manipule pas un pointeur vide.
 *
 * @note	Puisque les grilles sont relativement petites, allouer statiquement
 *			de la mémoire que l'on n'utilisera pas est préférable à la gestion
 *			de bogue avec une allocation dynamique.
 */

/**
 * @brief	Représente une séquence de coordonnées
 */
typedef struct {
	Coordinate data[longestSequencePossible];
	size_t length;
	bool empty;
} Sequence;

/**
 * @brief	Représente la grille de jeu
 */
typedef struct {
	const size_t columns;				/**< Nombre de colonnes dans la grille. */
	const size_t rows;				/**< Nombre de lignes dans la grille. */
	char data[maxRow][maxCol];	/**< Matrice pour stocker les données de la grille. */
} Grid;

/**
 * @brief	Enumération représentant le code d'erreur
 *
 * @note	L'instruction ' : size_t' permet de préciser
 *			le type numérique de l'énumération
 */
typedef enum : size_t {
	SUCCESS = 0,		/**< Aucune erreur. */
	GENERIC_ERROR,		/**< Erreur générique à renvoyer dans un cas quelconque. */
	GRID_SIZE_ERROR,	/**< Erreur liée aux dimensions de la grille */
} ErrorCode;

/**
 * @brief	Enumération représentant le mode de jeu
 */
typedef enum {
	PUZZLE, /**< Mode puzzle */
	RUSH,	/**< Mode rush */
	NONE,	/**< Aucun mode sélectionné */
} GameMode;

/**
 * @brief	Représente le score d'un joueur
 *
 * @note	'__attribute__((__packed__))' assure que les données sont contigus
 *			en mémoire afin de récupérer des chunks de données.
 *
 *			Dans la mémoire la structure aura cette forme :
 *
 *		       1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20
 *		     ┌───────────────────────────────────────────────────────────────────────────────┐
 *		     │                                    username                                   │
 *		     ├───────────────┬───────────────────────────────┬───────────────────────────────┤
 *			 │     score     │             gridCol           │            gridRow            │
 *		     └───────────────┴───────────────────────────────┴───────────────────────────────┘
 */
typedef struct __attribute__((__packed__)) {
	char username[20];	// 160 bits = 20 bytes
	unsigned int score; //  32 bits =  4 bytes
	size_t gridCol;		//  64 bits =  8 bytes
	size_t gridRow;		//  64 bits =  8 bytes
} UserScore;

#endif //DATATYPE_H
