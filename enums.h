#pragma once
#ifndef DEF_ENUMS
#define DEF_ENUMS

enum
{
	col_A,
	col_B,
	col_C,
	col_D,
	col_E,
	col_F,
	col_G,
	col_H,
	col_I,
	col_J
};
enum
{
	row_1,
	row_2,
	row_3,
	row_4,
	row_5,
	row_6,
	row_7,
	row_8,
	row_9,
	row_10
};
enum
{
	pion_N,
	pion_B,
	dame_N,
	dame_B
};
enum
{
	CPU,
	HUMAIN,
	HUMAIN2
};

enum TypeMenu
{
	MenuPrincipale,
	MenuNvlPartie,
	MenuInstructions,
	MenuApropos
};

enum TypeJeu
{
	HUMAINvsHUMAIN,
	HUMAINvsIA
};

enum
{
	AUCUN_EL_ACT,
	NP_ACTIF,
	I_ACTIF,
	AP_ACTIF,
	Q_ACTIF,
	JHvsH_ACTIF,
	JHvsIA_ACTIF,
	R_ACTIF
};

enum EtatH
{
	Demarre,
	EnPause
};

#endif // DEF_ENUMS
