#include <SFML/Graphics.hpp>
#include <iostream>
#include "controleur.h"

using namespace sf;

std::vector<Vector2f> ensembleCaseValide;
std::vector<Vector2f> ensemblePionValide;
std::vector<Vector2f> ensemblePCapDeDepl;

bool jeu_en_cours = false;
sf::Texture t_tableDames, t_pion_n, t_pion_b, t_pion_n_d, t_pion_b_d, t_indic_selection, t_masquePionCDC;
sf::Sprite s_indic_selection;
std::vector<Sprite> ensembleImPionValide;
std::vector<Sprite> ensembleImCaseValide;
int sourisX, sourisY;
bool LA_MAIN = true;
bool ia_simp_depl = false;
bool ia_captur_p = false;
bool selec_valide = false;
bool fin_partie = false;
bool partie_gagne = false;
bool HumvsHum = false;

bool h_capture = false;
bool h_deplacem = false;
float delai = 1.5f;

int main()
{
	srand(time(0));
	RenderWindow fenetre(VideoMode(1050, 750), "DAMES");
	fenetre.setFramerateLimit(60);

	Controleur controleurJ(fenetre);

	Clock clock;
	float timer = 0;

	while (fenetre.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event evenement;

		while (fenetre.pollEvent(evenement))
		{
			if (evenement.type == Event::Closed)
			{
				fenetre.close();
				break;
			}

			if (evenement.type == Event::MouseMoved)
			{
				sourisX = evenement.mouseMove.x;
				sourisY = evenement.mouseMove.y;
				if (!jeu_en_cours)
				{
					controleurJ.gestionDplSouris();
				}
			}

			if (evenement.type == Event::MouseButtonPressed && jeu_en_cours && LA_MAIN)
			{
				Mouse::Button button = evenement.mouseButton.button;
				if (button == Mouse::Left) // Bouton gauche
				{
					controleurJ.gestionTour(HUMAIN);
					timer = 0;
				}
			}

			if (evenement.type == Event::MouseButtonPressed && jeu_en_cours && !LA_MAIN && HumvsHum)
			{
				Mouse::Button button = evenement.mouseButton.button;
				if (button == Mouse::Left) // Bouton gauche
				{
					controleurJ.gestionTour(HUMAIN2);
				}
			}

			if (evenement.type == Event::MouseButtonPressed && !jeu_en_cours)
			{
				Mouse::Button button = evenement.mouseButton.button;
				if (button == Mouse::Left) // Bouton gauche
				{
					controleurJ.gestionSelectionSouris();

					if (jeu_en_cours)
					{
						controleurJ.debutJeu();
					}
				}
			}

			/*
				  switch(evenement.type)
				  {
				  case Event::Closed:
					fenetre.close();
					break;


					case Event::MouseMoved:
						{
							sourisX=evenement.mouseMove.x;
							sourisY=evenement.mouseMove.y;
							if(!jeu_en_cours)
							{
								controleurJ.gestionDplSouris();
							}
						}
						break;

				  default:
					break;


				  }

				  //gestion des evenements de la souris
				  if(evenement.type==Event::MouseButtonPressed && !jeu_en_cours)
				  {
					  Mouse::Button button = evenement.mouseButton.button;
					  if (button == Mouse::Left) // Bouton gauche
					  {
						  controleurJ.gestionSelectionSouris();

						  if(jeu_en_cours)
						  {
							  std::cout<<"Debut Jeu"<<std::endl;
							  controleurJ.debutJeu();

						  }
					  }

				  }

				  //


				  */
			/*
			if(evenement.type==Event::MouseButtonPressed && jeu_en_cours && !LA_MAIN)
			{
				Mouse::Button button = evenement.mouseButton.button;
				if (button == Mouse::Left) // Bouton gauche
				{
					controleurJ.gestionTour(HUMAIN2);
					timer=0;

				}

			}
			*/
		}

		if (jeu_en_cours)
		{
			controleurJ.compteurTemps();

			// tour CPU
			if (!LA_MAIN && !HumvsHum && timer > delai)
			{
				timer = 0;
				controleurJ.gestionTour(CPU);
			}

			controleurJ.gestMajD();
			controleurJ.Fin_Jeu();
		}

		fenetre.clear(Color(123, 44, 32));

		if (jeu_en_cours)
		{
			controleurJ.afficheJeu();
		}
		else
		{
			controleurJ.afficheMenu();
		}

		fenetre.display();
	}
	return 0;
}
