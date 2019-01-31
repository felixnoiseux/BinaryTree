#ifndef ARBREBINAIRE_H__
#define ARBREBINAIRE_H__

template <class T>
class ArbreBinaire
{
public:
	ArbreBinaire();                         // Construit un arbre vide
	~ArbreBinaire();                        // Libere toute la memoire allouée

	void Ajouter(const T& valeur);          // Ajouter un item
	void Enlever(const T& valeur);          // Enlever un item
	bool Contient(const T& valeur);   // Retourne vrai si l'arbre contient l'item recherché
	int Nombre() const;                     // Retourne le nombre d'items dans l'arbre

	const T& Minimum() const;               // Retourne la plus petite valeur
	const T& Maximum() const;               // Retourne la plus grande valeur

	void AfficherCroissant() const;         // Affiche le contenu de l'arbre en ordre croissant (avec un espace entre chaque item)
	void AfficherDecroissant() const;       // Affiche le contenu de l'arbre en ordre décroissant (avec un espace entre chaque item)

private:



	struct Noeud
	{
		T value;
		Noeud* gauche;
		Noeud* droite;

	};

	Noeud* racine = 0;
	Noeud* parent = 0;
	int m_count = 0;

	void DestroyRecursive(Noeud* node);
	void Croissant(Noeud* node) const;
	void Decroissant(Noeud* node) const;
	void EnleverRecursif(Noeud* node , const T& valeur);
	void SupprimerRacine(Noeud * Racine);
	void SupprimerNoeud(Noeud * parent, Noeud * enfant, bool gauche);
	T MinimumNoeud(Noeud * node);


};


#endif

template<class T>
ArbreBinaire<T>::ArbreBinaire()
{
	//TODO : Reverifier

	/*racine = new Noeud;
	parent = racine;*/
}

template<class T>
ArbreBinaire<T>::~ArbreBinaire()
{
	DestroyRecursive(racine);
}

template < class T >
void ArbreBinaire < T > ::Ajouter(const T & valeur)
{

	Noeud * n = new Noeud();

	//Si on a rien dans l'arbre
	if (!racine) {
		n->value = valeur;
		racine = n;
		parent = n;
		m_count++;
	}
	else {
		while (n) {

			//Verifie cote gauche
			if (parent->value > valeur)
			{
				if (parent->gauche)
					parent = parent->gauche;
				else
				{
					//Envoye a gauche
					n->value = valeur;
					parent->gauche = n;
					parent = racine;
					m_count++;
					break;
				}

			}
			//Verifie cote droit
			else if (parent->value < valeur)
			{
				if (parent->droite)
					parent = parent->droite;
				else
				{
					//Envoye a droite
					n->value = valeur;
					parent->droite = n;
					parent = racine;
					m_count++;
					break;
				}
			}
			//Verifie le doublon
			else if (parent->value == valeur)
			{
				delete n;
				std::cout << "Vous avez un doublon. Je l'ai supprimer." << std::endl;
				break;
			}
		}
	}
}

template<class T>
void ArbreBinaire<T>::Enlever(const T & valeur)
{
	//Lorsqu'on supprime on part toujours de la racine
	if (racine != NULL)
		EnleverRecursif(racine, valeur);
	else
		std::cout << "Je ne peut rien enlever , il n'a rien" << std::endl;
}

template<class T>
bool ArbreBinaire<T>::Contient(const T & valeur)
{
	if (racine != NULL)
	{
		Noeud* n = parent;
		int compteur = 0;
		while (n)
		{
			if (valeur == n->value)
				return true;
			else if (compteur >= m_count)
				return false;


			//Verifie si la valeur est du cote gauche ou du cote droite
			//Verifie en partant de la gauche
			if (valeur < n->value)
				if (n->gauche)
					n = n->gauche;
				else
					if (n->droite)
						n = n->droite;

			++compteur;
		}
	}
	else
	{
		std::cout << "Je ne peut pas te dire s'il il le contient , puisque ton arbre est vide" << std::endl;
		return false;
	}
		
}

template<class T>
int ArbreBinaire<T>::Nombre() const
{
	return m_count;
}

template<class T>
const T & ArbreBinaire<T>::Minimum() const
{
	if (racine != NULL)
	{
		Noeud* n = parent;
		while (n)
		{

			if (n->gauche)
				n = n->gauche;
			else
				return n->value;

		}
	}
	else
		return NULL;
}

template<class T>
const T & ArbreBinaire<T>::Maximum() const
{
	if (racine != NULL)
	{
		Noeud* n = parent;
		while (n)
		{

			if (n->droite)
				n = n->droite;
			else
				return n->value;

		}
	}
	else
		return NULL;
}

template<class T>
void ArbreBinaire<T>::AfficherCroissant() const
{	
	if (racine != NULL)
		Croissant(parent);
	else
		std::cout << "Je ne peut pas afficher l'ordre croissant , il a rien dans l'arbre" << std::endl;
}

template<class T>
void ArbreBinaire<T>::AfficherDecroissant() const
{
	if (racine != NULL)
		Decroissant(parent);
	else
		std::cout << "Je ne peut pas afficher l'ordre decroissant , il a rien dans l'arbre" << std::endl;
}

template<class T>
void ArbreBinaire<T>::DestroyRecursive(Noeud* node)
{
	if (node)
	{
		DestroyRecursive(node->gauche);
		DestroyRecursive(node->droite);
		delete node;
	}
}

template<class T>
void ArbreBinaire<T>::Croissant(Noeud * node) const
{
	Noeud* n = node;
	if (n != NULL)
	{
		if (n->gauche)
			Croissant(n->gauche);

			std::cout << n->value << std::endl;

			if (n->droite)
				Croissant(n->droite);
	}
	else
	{
		std::cout << "T'as rien dans ton schema man" << std::endl;
	}
}

template<class T>
void ArbreBinaire<T>::Decroissant(Noeud * node) const
{
	Noeud* n = node;
	if (n != NULL)
	{
		if (n->droite)
			Decroissant(n->droite);

		std::cout << n->value << std::endl;

		if (n->gauche)
			Decroissant(n->gauche);
	}
	else
	{
		std::cout << "T'as rien dans ton schema man" << std::endl;
	}
}

template<class T>
void ArbreBinaire<T>::EnleverRecursif(Noeud * node , const T& valeur)
{
	//Initialement il pointe sur le noeud parent
	Noeud * n = node;

	if (n != NULL)
	{
		if (racine->value == valeur)
		{
			//Supression de la racine,  on refait l'arbre
			SupprimerRacine(racine);
		}
		else 
		{
			//Verifie a gauche
			if (valeur < n->value && n->gauche)
			{
				if (n->gauche->value == valeur)
					SupprimerNoeud(n, n->gauche, true);
				else
					EnleverRecursif(n->gauche, valeur);


			}
			//Verifie a droite
			else if (valeur > n->value && n->droite)
			{
				if (n->droite->value == valeur)
					SupprimerNoeud(n, n->droite, false);
				else
					EnleverRecursif(n->droite, valeur);

			}
			else
				std::cout << "Aucune valeur de ce type est stocke dans l'arbre" << std::endl;


		}
	}
	else
	{
		std::cout << "Tu dois obligatoirement avoir un arbre pour pouvoir utiliser ma fonction de supression" << std::endl;
	}
	



}

template<class T>
void ArbreBinaire<T>::SupprimerRacine(Noeud * Racine)
{
	if (Racine != NULL)
	{
		Noeud * n = Racine;
		T nouvelleValeur = 0;
		//Si la racine n'as pas d'enfant
		if (n->droite == NULL && n->gauche == NULL)
		{
			racine = NULL;
			delete n;
		}
		else if (n->droite == NULL && n->gauche != NULL)
		{
			racine = racine->gauche;
			delete n;
		}
		else if (n->droite != NULL && n->gauche == NULL)
		{
			racine = racine->droite;
			delete n;
		}
		//Si la racine a deux enfants
		else
		{
			nouvelleValeur = MinimumNoeud(n->droite);
			//On enleve la valeur den dessous par la placer au dessus
			Enlever(nouvelleValeur);
			n->value = nouvelleValeur;
		}
	}
	else
	{
		std::cout << "Tu ne peut pas supprimer ta racine , commence par avoir un arbre" << std::endl;
	}
}

template<class T>
void ArbreBinaire<T>::SupprimerNoeud(Noeud * parent, Noeud * enfant, bool gauche)
{
	if (racine != NULL)
	{
		Noeud * n = enfant;
		Noeud * sup;
		T petitdroit = 0;

		//Jai le droit de supprimer
		if (n->gauche == NULL && n->droite == NULL)
		{
			sup = n;
			if (gauche)
				parent->gauche = NULL;
			else
				parent->droite = NULL;
			delete sup;
		}
		else if (n->gauche == NULL && n->droite != NULL)
		{
			T nouvelleValeur = 0;
			nouvelleValeur =  MinimumNoeud(n->droite);
			Enlever(nouvelleValeur);
			n->value = nouvelleValeur;
		}
		else if (n->gauche != NULL && n->droite == NULL)
		{
			T nouvelleValeur = 0;
			nouvelleValeur = MinimumNoeud(n->gauche);
			Enlever(nouvelleValeur);
			n->value = nouvelleValeur;
		}
		else if (n->gauche != NULL && n->droite != NULL)
		{
			SupprimerRacine(n);
		}
	}
}

template<class T>
T ArbreBinaire<T>::MinimumNoeud(Noeud * node)
{
	Noeud * n = node;

	if (racine == NULL)
	{
		std::cout << "l'arbre est vide !!!" << std::endl;
		return -1000;
	}
	else
	{
		if (n->gauche != NULL)
			MinimumNoeud(n->gauche);
		else
			return n->value;
	}
}





