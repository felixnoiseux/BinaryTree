#include <iostream>
#include "ArbreBinaire.h";
#include <string>;
int main()
{
	ArbreBinaire<int> arbre;
	arbre.Ajouter(13);
	arbre.Ajouter(28);
	arbre.Ajouter(14);
	arbre.Ajouter(33);
	arbre.Ajouter(10);
	arbre.Ajouter(2);

	if (arbre.Contient(1))
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	std::cout << "Le nombre d'item : " << arbre.Nombre() << std::endl;
	std::cout << "Maximum : "<< arbre.Maximum() << std::endl;
	std::cout << "Minimum : " << arbre.Minimum() << std::endl;
	arbre.AfficherCroissant();
	std::cout << "--------------------------" << std::endl;
	arbre.AfficherDecroissant();
	arbre.Enlever(11);
	std::cout << "--------------------------" << std::endl;
	arbre.AfficherDecroissant();
	system("pause");
}