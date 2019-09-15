#ifndef WINDWAKER_H
#define WINDWAKER_H

#define FAR __attribute__((longcall))

#pragma pack(1)
#include "main.dol.h"
#pragma pack()

// Que dieu bénisse le polymorphisme
void onEventBit__11dSv_event_cFUs(void *, unsigned); // Marque un évènement du jeu comme déjà vu
void init__10dSv_save_cFv(); // initialise une nouvelle partie
void SetR__8cM3dGSphFf(void*, float); // SetR comme SetRadius, change le rayon d'une sphère
void SetC__8cM3dGSphFRC4cXyz(void *, void*); // SetCenter, change le centre d'une sphère

// Ajoute une hitbox au gestionnaire de hitbox. Le premier argument est l'addresse du gestionnaire.
// Le deuxième argument est un pointeur vers tout objet dérivant de cCcD_Obj
void Set__4cCcSFP8cCcD_Obj(void*, void*);
// Pas sur de à quoi ca sert, mais ca ne coute ""rien""
void Set__12dCcMassS_MngFP8cCcD_ObjUc(void*, void*, char);

// Copie les propriété d'une sphère source vers une sphère destination. Le jeu utilise deux types
// de sphère... Premier arg = destination
void Set__8dCcD_SphFRC11dCcD_SrcSph(void*, void*);

extern unsigned char effect_manager[];
extern unsigned char collision_manager[];
extern unsigned char mass_manager[];

typedef struct {
	unsigned char pad[0x1f8];
	cXyz pos;
} __attribute((packed)) arrow;


// Génère l'effet d'explosion
void setBombSmoke(void *,
				  unsigned short,
				  cXyz const *,
				  short const *,
				  cXyz const *,
				  unsigned char);

// Génère l'effet d'explosion
void set(void *,
		 unsigned char,
		 unsigned short,
		 void const *,
		 void const *,
		 void const *,
		 unsigned char,
		 void *,
		 signed char,
		 void const *,
		 void const *,
		 void const *);

// donne un objet dans l'inventaire
void execItemGet(unsigned char id);

void se_explode(void*); // joue le son de l'explosion. Prend en parametre l'acteur qui provoque l'explosion
void Init__9dCcD_SttsFiiP10fopAc_ac_c(void*, char, char, void*);

void dCcD_GStts_ctor(void*); // constructeur de dCcD_GStts
void dCcD_GObjInf_ctor(void*); // constructeur de dCcD_GObjInf

// main original du jeu
FAR int main(int argc, char **argv);

// point d'entrée original du dol
extern void original_entry();

#endif /* WINDWAKER_H */